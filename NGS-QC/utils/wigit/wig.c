
#include <stdio.h>

#include "common.h"
#include "genome.h"
#include "region.h"
#include "wig.h"


void flush_section(char *chrm, int span, struct chromSection *section, int nodup) {
    /**
     * Print the wigs in the current section
     * @param chrm      section's chromosome
     * @param span      Data's span (size of a region)
     * @param section   Pointer (?) to section
     * @param nodup     If true (1) will print three columns
     */
    if (section->size) {
        long i;
        printf("variableStep chrom=%s span=%u\n", chrm, span);
        for (i = 0; i < section->size; ++i) {
            if (section->val[i]) {
                if (nodup)
                    printf("%ld\t%d\t%d\n", i*span+1, section->val[i], section->val2[i]);
                else
                    printf("%ld\t%d\n", i*span+1, section->val[i]);
            }
        }
        free(section->val);
        free(section->val2);        
    }
}

int genomewide_sorted(char *in_name, int extsize, int span, struct genomeInfo *genome, int nodup) {
    char buffer[BUFF_SIZE];
    char *str, *token;
    char delim[] = "\t";
    
    char *chrm, strand;
    long start, end;
    
    char prev_chrm[32] = "";
    long prev_start, prev_end;
    
    unsigned int read_length;    
    
    long idx;
    
    int i, isdupe, saw_fw, saw_rv;

    struct chromSection *section = NULL;
    section = malloc(sizeof(struct chromSection));

    struct genomeInfo *g;
    
    FILE *fp = try_open(in_name, "r");
    
    while (fgets(buffer, BUFF_SIZE, fp)) {
        if (strlen(buffer) > 1 && strncmp(buffer, "#", 1) != 0 && strncmp(buffer, "track", 5) != 0 && strncmp(buffer, "browser", 7) != 0) {
        
            for (i = 0, str = buffer; ; ++i) {
                token = strsep(&str, delim);

                if (token == NULL) {
                    // Token is NULL, last element chopped. The last one should be the strand (index 5): there is a problem
                    fclose(fp);
                    return (1);
                } else if (i == 0) {
                    // First element: chromosome
                    chrm = token;

                    if (! equals(chrm, prev_chrm)) {
                        // New chromosome: new section
                        if (strncmp(prev_chrm, "", 1) != 0) {
                            // The previous chromosome wasn't empty: cannot enter here on the first line
                            flush_section(prev_chrm, span, section, nodup);
                        }

                        if (genome) {
                            // A valid genome was provided
                            HASH_FIND_STR(genome, chrm, g);
                            if (g) 
                                // Genome found: use chromosome
                                section->size = g->size / span;
                            else {
                                // Invalid chromsome: skip it
                                section->size = 0;
                                strcpy(prev_chrm, chrm);
                                break;
                            }
                        } else
                            // Accept everything
                            section->size = 300000000 / span;

                        // Allocate the memory (array of zeroed int)
                        section->val = calloc(section->size, sizeof(int));

                        if (section->val == NULL) {
                            // Mem error :()
                            fprintf(stderr, "Couldn't allocate memory\n");
                            fclose(fp);
                            exit(1);
                        }

                        if (nodup) {
                            // Second array's allocation for --nodup option
                            section->val2 = calloc(section->size, sizeof(int));
                            if (section->val2 == NULL) {
                                // Mem error, the return T_T
                                fprintf(stderr, "Couldn't allocate memory\n");
                                fclose(fp);
                                exit(1);
                            }                        
                        }

                    } else if(section->size == 0) {
                        // Same chromosome than previous line, but we want to skipt it
                        strcpy(prev_chrm, chrm);
                        break;
                    }

                } else if (i == 1) {
                    /* 
                     * Start position
                     * The first base is numbered 0. 
                     * See http://genome.ucsc.edu/FAQ/FAQformat.html#format1
                     */                
                    start = atol(token);
                } else if (i == 2) {
                    /* 
                     * End position
                     * The end base is not included (so, -1), 
                     */                
                    end = atol(token);
                    --end;
                } else if (i == 5) {
                    /*
                     * Strand
                     */
                    strand = token[0];

                    if (nodup) {
                        // --nodup otion: verify if this read is a PCR duplicate (if so, isdupe will be set to 1)
                        isdupe = 0;
                        if (equals(chrm, prev_chrm) && prev_start == start && prev_end == end) {
                            if (strand == '+') {
                                if (saw_fw)
                                    isdupe = 1;
                                saw_fw = 1;
                            } else {
                                if (saw_rv)
                                    isdupe = 1;
                                saw_rv = 1;
                            }
                        } else if (strand == '+') {
                            saw_fw = 1;
                            saw_rv = 0;
                        } else {
                            saw_fw = 0;
                            saw_rv = 1;                        
                        }

                        prev_start = start;
                        prev_end = end;
                    }

                    // Extend the read
                    read_length = end - start;
                    if (read_length < extsize) {
                        if (strand == '+')
                            end += extsize - read_length;
                        else {
                            start -= extsize - read_length;
                            if (start < 0) start = 0;
                        }
                    }

                    // Pile-up
                    for (idx = start/span; idx <= end/span; ++idx) {
                        if (idx < section->size) {
                            section->val[idx]++;
                            if (nodup && ! isdupe)
                                section->val2[idx]++;                        
                        }
                    }

                    strcpy(prev_chrm, chrm);
                    break;
                }
            }
        }
    }
    // Flush the last section
    flush_section(prev_chrm, span, section, nodup);
    free(section);
    fclose(fp);    
    
    return (0);
}

int regions_sorted(char *in_name, int extsize, int span, struct genomeInfo *genome, struct dictRegion **regions) {
    char buffer[BUFF_SIZE];
    char *str, *token;
    char delim[] = "\t";
    
    char *chrm, strand;
    long start, end;
    
    char prev_chrm[32] = "";
    long prev_start, prev_end;
    
    unsigned int read_length;    
    
    long idx;
    
    int i;

    struct chromSection *section = NULL;
    section = malloc(sizeof(struct chromSection));

    struct genomeInfo *g;
    struct dictRegion *r;
    
    FILE *fp = try_open(in_name, "r");
    
    while (fgets(buffer, BUFF_SIZE, fp)) {
        if (strlen(buffer) > 1 && strncmp(buffer, "#", 1) != 0 && strncmp(buffer, "track", 5) != 0 && strncmp(buffer, "browser", 7) != 0) {
            
            for (i = 0, str = buffer; ; ++i) {
                token = strsep(&str, delim);

                if (token == NULL) {
                    fclose(fp);
                    return (1);
                } else if (i == 0) {
                    chrm = token;

                    if (! equals(chrm, prev_chrm)) {
                        if (strncmp(prev_chrm, "", 1) != 0) {
                            flush_section(prev_chrm, span, section, 0);

                            /* 
                             * The file is sorted so we won't encounter the previous chromosome: 
                             * we can delete its regions 
                             */                    
                            HASH_FIND_STR(*regions, prev_chrm, r);
                            if (r) {
                                free(r->chrm);
                                HASH_DEL(*regions, r);
                                free(r);
                            }


                            if (! HASH_COUNT(*regions)) {
                                // No more regions
                                fclose(fp);
                                free(section);
                                return (0);
                            }                        
                        }

                        HASH_FIND_STR(*regions, chrm, r);
                        if (! r) {
                            // No regions in the current chromosome
                            section->size = 0;
                            strcpy(prev_chrm, chrm);
                            break;
                        }

                        if (genome) {
                            HASH_FIND_STR(genome, chrm, g);
                            if (g)
                                section->size = g->size / span;
                            else {
                                section->size = 0;
                                strcpy(prev_chrm, chrm);
                                break;
                            }
                        } else {
                            section->size = 300000000 / span;
                        }

                        section->val = calloc(section->size, sizeof(int));

                        if (section->val == NULL) {
                            fprintf(stderr, "Couldn't allocate memory\n");
                            fclose(fp);
                            exit(1);
                        }
                    } else if (section->size == 0) {
                        strcpy(prev_chrm, chrm);
                        break;                    
                    }
                } else if (i == 1) {
                    /* 
                     * The first base is numbered 0. 
                     * See http://genome.ucsc.edu/FAQ/FAQformat.html#format1
                     */                
                    start = atol(token);
                } else if (i == 2) {
                    /* 
                     * The end base is not included (so, -1), 
                     */                
                    end = atol(token);
                    --end;          
                } else if (i == 5) {
                    strand = token[0];

                    read_length = end - start;

                    if (read_length < extsize) {
                        if (strand == '+')
                            end += extsize - read_length;
                        else {
                            start -= extsize - read_length;
                            if (start < 0) start = 0;
                        }
                    }

                    for (i = 0; i < r->nregions; ++i) {
                        // For each rgion we have on the current chromosome
                        if ((r->regions[i].start <= start && start <= r->regions[i].end) || (r->regions[i].start <= end && end <= r->regions[i].end)) {
                             // Read belongs to the region

                            for (idx = start/span; idx <= end/span; ++idx) {
                                if (idx < section->size) {
                                    section->val[idx]++;                        
                                }                            
                            }
                            // Break here for not supporting overlapping)
                        }
                    }             

                    strcpy(prev_chrm, chrm);
                    break;
                }
            }
        }
    }
    flush_section(prev_chrm, span, section, 0);
    free(section);
    fclose(fp);    
    
    return (0);    
}

void create_wigs(char *in_name, int extsize, int span, int issorted, int nodup, struct genomeInfo *genome, struct dictRegion **regions) {
    if (*regions) {
        if (issorted)
            regions_sorted(in_name, extsize, span, genome, regions);
        else
            fprintf(stderr, "No supported\n");
    } else {
        if (issorted)
            genomewide_sorted(in_name, extsize, span, genome, nodup);
        else
            fprintf(stderr, "No supported\n");
    }
    
}
