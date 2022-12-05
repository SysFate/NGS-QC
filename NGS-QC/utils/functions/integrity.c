#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../lib/genome.h"

#define true 1
#define false 0

/* check bed file integrity */
void check_bed_file_integrity(FILE* fp, unsigned char get_tmru) {
    char line[1024];
    
    long start = 0;
    long end = 0;
    int read_size = 0;
    int prev_read_size = 0;
    unsigned long total_read_size = 0;
    unsigned long reads = 0;
    unsigned long header_reads = 0;
    unsigned long ureads = 0;

    int min_read_size = 9999;
    int max_read_size = 1;

    float reads_length_mean = 0;
    int dif_read_size = false;

    int error_code = 0;
    int line_len = 0;

    char* ptr;
    char* ptrend;

    char strptr_buf[128] = "";

    int lenptr = 0;
    extern int errno;
    char* token;
    int l4p; // true if the is 4p for the current line
    int hl4p = false; //true if one ligne with 4 fields only
    int l5p; // true if the is 5p for the current line
    int hl5p = false; //true if one ligne with 5 fields only

    int sp; //space count
    int vpl; // true if current line has more than 3 space separator
    int hvpl = false; // true if one line has space delimiter

    int vl = false; // true if one ligne is corretly formatted

    //struct s_bedinfo* bed_info = (struct s_bedinfo*)malloc(sizeof(struct s_bedinfo));

    int used_chrm_alloc = 1024;
    char* used_chrm = (char*)malloc(used_chrm_alloc * sizeof(char));

    struct chrm_entry* ce;

    //error code:
    // 0 the file is okay
    // 1 invalid line(s)
    // 2 strand is in the 4 position
    // 4 strand is in the 5 position
    // 8 space delimiter strand is in the 6 position
    // 16 space delimiter, strand is in the 4 position
    // 32 space delimiter, strand is in the 5 position
    // any other value means different formatted line

    while(fgets(line, 1024, fp) != NULL) {
        //printf("%s", line);
        line_len = strlen(line);
        //strip the carriage return
        if (line[line_len-1] == '\n') {
            if (line[line_len-2] == '\r') {
                line[line_len-2] = '\0';
            } else {
                line[line_len-1] = '\0';
            }
        }

        if (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0) {
            reads++;
            ptr = line;
            vpl = false;
            //parse chrmname -----------------
            if ((ptrend = strchr(ptr, '\t')) == NULL) {
                //no tab character found
                //replace spaces by tab
                sp = 0;
                while ((ptrend = strchr (ptr, ' ')) != NULL) {
                    *ptrend++ = '\t';
                    sp++;
                }
                if (sp < 3) {
                    // no tab delimited and less than 3 space character, abord
                    error_code = 1;
                    break;
                }
                // space have been replace by tab
                vpl = true;
                hvpl = true;
                // get the chrmname again
                ptr = line;
                ptrend = strchr(ptr, '\t');
            }

            //different separator line
            if (hvpl && !vpl) {
                error_code |= 64;
                break;
            }
            lenptr = ptrend-ptr;
            if (lenptr == 0) {
                //empty chrmname, abord
                error_code = 1;
                break;
            }
            strncpy(strptr_buf, ptr, lenptr);
            strptr_buf[lenptr] = '\0';

            //store the chrm used
            if ((ce = lookup_chrm(strptr_buf)) == NULL) {
                ce = put_chrm(strptr_buf, 1); //1 is the size, not used
                ce->used = 1;
                while (((int)strlen(strptr_buf) + (int)strlen(used_chrm) + 1) > used_chrm_alloc) {
                    used_chrm_alloc *= 2;
                    if ((used_chrm = realloc(used_chrm, used_chrm_alloc)) == NULL) {
                        fprintf(stderr, "Error: cannot allocate user_chrm memory.\n");
                        exit(1);
                    }
                }
                strcat(strptr_buf, ",");
                strcat(used_chrm, strptr_buf);
            } else if (get_tmru) {
                if (ce->used == 0) {
                    ce->used = 1;
                    while (((int)strlen(strptr_buf) + (int)strlen(used_chrm) + 1) > used_chrm_alloc) {
                        used_chrm_alloc *= 2;
                        if ((used_chrm = realloc(used_chrm, used_chrm_alloc)) == NULL) {
                            fprintf(stderr, "Error: cannot allocate user_chrm memory.\n");
                            exit(1);
                        }
                    }
                    strcat(strptr_buf, ",");
                    strcat(used_chrm, strptr_buf);
                }

                if (ce->size != 1) {
                    ureads++;
                }
            }

            ptr = ptrend+1;
            //parse start position -----------
            if ((ptrend = strchr(ptr, '\t')) == NULL) {
                //no more field, abord
                error_code = 1;
                break;
            }
            lenptr = ptrend-ptr;
            strncpy(strptr_buf, ptr, lenptr);
            strptr_buf[lenptr] = '\0';
            start = strtoul(strptr_buf, &token, 10);
            if (*token != 0 || errno != 0 || start < 0) {
                //invalid numeric value for start position, abord
                error_code = 1;
                break;
            }

            ptr = ptrend+1;
            //parse end position -------------
            if ((ptrend = strchr(ptr, '\t')) == NULL) {
                //no more field, abord
                error_code = 1;
                break;
            }
            lenptr = ptrend-ptr;
            strncpy(strptr_buf, ptr, lenptr);
            strptr_buf[lenptr] = '\0';
            end = strtoul(strptr_buf, &token, 10);
            if (*token != 0 || errno != 0 || end < 0) {
                //invalid numeric value for end position, abord
                error_code = 1;
                break;
            }
            //compute read length
            if ((read_size = (end - start)) < 1) {
                error_code = 1;
                break;
            }
            if (!dif_read_size && prev_read_size != 0 && read_size != prev_read_size) {
                dif_read_size = true;
            }
            total_read_size += read_size;
            prev_read_size = read_size;

            if (read_size < min_read_size) {
                min_read_size = read_size;
            }

            if (read_size > max_read_size) {
                max_read_size = read_size;
            }

            ptr = ptrend+1;
            // read ID -------------------
            if ((ptrend = strchr(ptr, '\t')) == NULL) {
                //no more field test if strand field
                if (strlen(ptr) == 1 && (*ptr == '+' || *ptr == '-')) {
                    // strand at 4 pos
                    if (vpl) {
                        error_code |= 16;
                    } else {
                        error_code |= 2;
                    }
                    hl4p = true;
                    continue;
                } else {
                    error_code = 1;
                    break;
                }
            }
            //test if the line is longer than other
            l4p = false;
            if ((ptrend-ptr) == 1 && (*ptr == '+' || *ptr == '-')) {
                // strand at pos 4, but keep going parsing until field 6th
                l4p = true;
            }
            if (hl4p && !l4p) {
                error_code |= 64;
                break;
            }
            if (hl4p) {
                continue;
            }
            ptr = ptrend+1;
            //parsing score ------------------
            if ((ptrend = strchr(ptr, '\t')) == NULL) {
                if (strlen(ptr) == 1 && (*ptr == '+' || *ptr == '-')) {
                    // strand at 5 pos
                    if (vpl) {
                        error_code |= 32;
                    } else {
                        error_code |= 4;
                    }
                    hl5p = true;
                } else if (l4p) {
                    if (vpl) {
                        error_code |= 16;
                    } else {
                        error_code |= 2;
                    }
                    hl4p = true;
                } else {
                    error_code = 1;
                    break;
                }
                continue;
            }
            //test if the line is longer than other
            l5p = false;
            if ((ptrend-ptr) == 1 && (*ptr == '+' || *ptr == '-')) {
                // strand at pos 5, but keep going parsing until field 6th
                l5p = true;
            }
            if (hl5p && !l5p) {
                error_code |= 64;
                break;
            }
            if (hl5p) {
                continue;
            }
            ptr = ptrend+1;
            //parse strand -----------------
            if ((ptrend = strchr(ptr, '\t')) == NULL) {
                if (!(strlen(ptr) == 1 && (*ptr == '+' || *ptr == '-'))) {
                    if (l4p) {
                        if (vpl) {
                            error_code |= 32;
                        } else {
                            error_code |= 2;
                        }
                    } else if (l5p) {
                        if (vpl) {
                            error_code |= 16;
                        } else {
                            error_code |= 4;
                        }
                    } else {
                        error_code = 1;
                        break;
                    }
                    continue;
                }
                if (vpl) {
                    if (vl) {
                        error_code |= 64;
                        break;
                    } else {
                        error_code |= 8;
                    }
                } else {
                    vl = true;
                }
            } else {
                if (!((ptrend-ptr) == 1 && (*ptr == '+' || *ptr == '-'))) {
                    error_code = 1;
                    break;
                }
                // valid line
                // get a value for vpl also
                if (vpl) {
                    if (vl) {
                        error_code |= 64;
                        break;
                    } else {
                        error_code |= 8;
                    }
                } else {
                    vl = true;
                }
            }
        } else {
            header_reads++;
        }
    }

    //get reads length mean
    reads_length_mean = total_read_size/(float)reads;

    //fix chrm used string
    if (strlen(used_chrm) > 0) {
        used_chrm[strlen(used_chrm)-1] = '\0';
    } else {
        strcpy(used_chrm, "-");
    }

    fprintf(stdout, "%d\t%ld\t%ld\t%f\t%d\t%d\t%d\t%ld\t%s\t%s\n", \
        error_code, reads, ureads, reads_length_mean, dif_read_size, min_read_size, max_read_size, header_reads, used_chrm, line);

}
