#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "wig.h"
#include "../lib/genome.h"
#include "../lib/str_tools.h"

/*struct chrm_entry {
    char *name;
    unsigned long size;
    struct chrm_entry *next;
};*/


//extern unsigned int chrm_num;

struct s_region_info region_array[50];
unsigned char region_stored = 0;

void parse_region_list(char* region_list) {
    
    /* region structure
       chr1:5000-45000,chr2:60000-785000*/
    char* ptr;
    char* ptrend;
    char* sub_ptrend;
    char* stlptr;
    char token[1024] = "";
    char sstart[256] = "";
    char chrname[256] = "";
    char* prev_chrmname = NULL;
    int lenptr;
    int sub_lenptr;
    int i = 0, cs = 0;
    unsigned long start = 0;
    unsigned long end = 0;
    unsigned long prev_start = 0;
    unsigned long prev_end = 0;
    unsigned long chrm_end;

    struct chrm_entry* ce;

    while ((ptrend = strchr (region_list, ',')) != NULL) {
        lenptr = ptrend-region_list;
        if (lenptr == 0) {
            region_list++;
            continue;
        }

        if (lenptr > 1024) {
            fprintf(stderr, "Warning: region data truncated to 1024 characters.");
            lenptr = 1024;
        }
        
        strncpy(token, region_list, lenptr);
        ptr = token;
        token[lenptr] = '\0';

        sub_ptrend = strchr(token, ':');
        sub_lenptr = sub_ptrend-token;

        if (sub_ptrend == NULL) {
            fprintf(stderr, "Error: invalid chromosome region.\n");
            fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
            exit(1);
        }
        if (sub_lenptr == 0) {
            fprintf(stderr, "Error: invalid chromosome region.\n");
            fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
            exit(1);
        }

        strncpy(chrname, token, sub_lenptr);
        chrname[sub_lenptr] = '\0';
        trim_space(chrname);

        if (strlen(chrname) == 0) {
            fprintf(stderr, "Error: invalid chromosome region.\n");
            fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
            exit(1);
        }

        if ((ce = lookup_chrm(chrname)) != NULL) {
            chrm_end = ce->size;
            if (prev_chrmname != NULL) {
                cs = strcmp(chrname, prev_chrmname);
                if (cs == 0) {
                    region_array[i-1].same_chr_next_region = 1;
                } else if (ce->used != 0) {
                    fprintf(stderr, "Error: invalid chromosome region.\n");
                    fprintf(stderr, "The regions must be sorted.\n\n");
                    exit(1);
                } else {
                    ce->used = 1;
                }
            } else {
                ce->used = 1;
            }

            ptr+=sub_lenptr+1; //pointer on the character after the :
            strncpy(token, ptr, lenptr); // rewrite token, remove the chr from the token
            ptr=token; // reset the ptr (it moves during the strncopy)
            sub_ptrend = token;// reset the sub_ptrend pointer to serach the '-' char

            sub_ptrend = strchr(token, '-');
            sub_lenptr = sub_ptrend-token;

            if (sub_ptrend == NULL) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
                exit(1);
            }
            if (sub_lenptr == 0) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
                exit(1);
            }

            strncpy(sstart, token, sub_lenptr);
            sstart[sub_lenptr] = '\0';
            trim_space(sstart);
            start = strtoul(sstart, &stlptr, 10);

            if (errno == ERANGE || (errno != 0 && start == 0)) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid start position value.\n\n");
                exit(1);
            }
            if (stlptr == sstart) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid start position value.\n\n");
                exit(1);
            }
            if (*stlptr != '\0') {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid start position value.\n\n");
                exit(1);
            }
            if (start >= chrm_end) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The region starts outside the chromosome.\n\n");
                exit(1);
            }
            if (prev_start != 0 && cs == 0 && start <= prev_end) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The regions must be sorted.\n\n");
                exit(1);
            }

            ptr+=sub_lenptr+1; //pointer on the character after the -
            strncpy(token, ptr, lenptr); // copy the end pos to token
            end = strtoul(token, &stlptr, 10);

            if (errno == ERANGE || (errno != 0 && end == 0)) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid end position value.\n\n");
                exit(1);
            }
            if (stlptr == token) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid end position value.\n\n");
                exit(1);
            }
            if (*stlptr != '\0') {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid end position value.\n\n");
                exit(1);
            }
            if (errno != 0 || end < 1) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid end position value.\n\n");
                exit(1);
            }
            if (end <= start) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The regions range must be positif.\n\n");
                exit(1);
            }

            region_array[i].chrm = strdup(chrname);
            region_array[i].start = start;
            region_array[i].end = end;

            prev_chrmname = region_array[i].chrm;
            prev_start = start;
            prev_end = end;

            region_list = ptrend+1;
            i++;

            if (i == 50) {
                fprintf(stderr, "Error: too many chromosome regions.\n");
                fprintf(stderr, "You must provide 50 regions max.\n\n");
                exit(1);
            }
        }
    }

    if (strlen(region_list) > 0) {
        lenptr = strlen(region_list);

        if (lenptr > 1024) {
            fprintf(stderr, "Warning: region data truncated to 1024 characters.");
            lenptr = 1024;
        }

        strncpy(token, region_list, lenptr);
        ptr = token;
        token[lenptr] = '\0';

        sub_ptrend = strchr(token, ':');
        sub_lenptr = sub_ptrend-token;

        if (sub_ptrend == NULL) {
            fprintf(stderr, "Error: invalid chromosome region.\n");
            fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
            exit(1);
        }
        if (sub_lenptr == 0) {
            fprintf(stderr, "Error: invalid chromosome region.\n");
            fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
            exit(1);
        }

        strncpy(chrname, token, sub_lenptr);
        chrname[sub_lenptr] = '\0';
        trim_space(chrname);

        if (strlen(chrname) == 0) {
            fprintf(stderr, "Error: invalid chromosome region.\n");
            fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
            exit(1);
        }

        if ((ce = lookup_chrm(chrname)) != NULL) {
            chrm_end = ce->size;
            if (prev_chrmname != NULL) {
                cs = strcmp(chrname, prev_chrmname);
                if (cs == 0) {
                    region_array[i-1].same_chr_next_region = 1;
                } else if (ce->used != 0) {
                    fprintf(stderr, "Error: invalid chromosome region.\n");
                    fprintf(stderr, "The regions must be sorted.\n\n");
                    exit(1);
                } else {
                    ce->used = 1;
                }
            } else {
                ce->used = 1;
            }

            ptr+=sub_lenptr+1; //pointer on the character after the :
            strncpy(token, ptr, lenptr); // rewrite token, remove the chr from the token
            ptr=token; // reset the ptr (it moves during the strncopy)
            sub_ptrend = token;// reset the sub_ptrend pointer to search the '-' char

            sub_ptrend = strchr(token, '-');
            sub_lenptr = sub_ptrend-token;

            if (sub_ptrend == NULL) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
                exit(1);
            }

            if (sub_lenptr == 0) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The regions must be formatted as \"chrA:startposA-endposA, chrA:startposB-endposB\".\n\n");
                exit(1);
            }

            strncpy(sstart, token, sub_lenptr);
            sstart[sub_lenptr] = '\0';
            trim_space(sstart);
            start = strtoul(sstart, &stlptr, 10);


            if (errno == ERANGE || (errno != 0 && start == 0)) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid start position value.\n\n");
                exit(1);
            }
            if (stlptr == sstart) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid start position value.\n\n");
                exit(1);
            }
            if (*stlptr != '\0') {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid start position value.\n\n");
                exit(1);
            }
            if (start >= chrm_end) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The region starts outside the chromosome.\n\n");
                exit(1);
            }
            if (prev_start != 0 && cs == 0 && start <= prev_end) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The regions must be sorted.\n\n");
                exit(1);
            }

            ptr+=sub_lenptr+1; //pointer on the character after the -
            strncpy(token, ptr, lenptr); // copy the end pos to token
            end = strtoul(token, &stlptr, 10);

            if (errno == ERANGE || (errno != 0 && end == 0)) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid end position value.\n\n");
                exit(1);
            }
            if (stlptr == token) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid end position value.\n\n");
                exit(1);
            }
            if (*stlptr != '\0') {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid end position value.\n\n");
                exit(1);
            }
            if (errno != 0 || end < 1) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "Invalid end position value.\n\n");
                exit(1);
            }
            if (end <= start) {
                fprintf(stderr, "Error: invalid chromosome region.\n");
                fprintf(stderr, "The regions range must be positif.\n\n");
                exit(1);
            }

            region_array[i].chrm = strdup(chrname);
            region_array[i].start = start;
            region_array[i].end = end;

            prev_chrmname = chrname;
            prev_start = start;
            prev_end = end;

            i++;
        }
    }

    if (i == 0) {
        fprintf(stderr, "Error: empty chromosome used region.\n");
        fprintf(stderr, "Be sure the region match chromosomes in the genome file.\n\n");
        exit(1);
    }

    region_stored = i;

    // for (int j = 0; j < region_stored; j++) {
    //    printf("%s\n", region_array[j].chrm);
    //    printf("%lu\n", region_array[j].start);
    //    printf("%lu\n", region_array[j].end);
    //} 

    return;
}


/*
READ line:
CURRENT_REGION = 1
IF CURRENT_REGION:
    WHILE CURRENT_CHRM > CURRENT_REGION.chrm:
        CURRENT_REGION++;

    IF CURRENT_REGION == max:
        EXIT (no region found in the file)

    IF CURRENT_CHRM < CURRENT_REGION.chrm:
        continue

(extend read)

IF CURRENT_REGION:
    IF CURRENT_REGION.start > start_pos
        continue

IF new chrm:

else:
    if first line:
    

*/


void bed_to_wig(FILE* fp_in, FILE* fp_out, unsigned int window_size, unsigned int extend_size, unsigned char no_header, unsigned char wbinary) {

    if (wbinary)
        wbinary = 0;

    char line[1024];
    char chrname[128] = "";
    char current_chrm[128] = "";
    unsigned long start_pos;
    unsigned long end_pos;
    long tmp;
    char strand;

    char* ptr;
    char* ptrend;

    unsigned long last_index = 0;
    unsigned long start_window;
    unsigned long end_window;
    unsigned long start_pos_window;
    unsigned long current_chrm_size = 0;

    unsigned int read_length = 0;
    int distance = 0;

    unsigned int r = 0, i = 0, cur_region = 0;

    int lenptr;
    char token[128] = "";

    int* current_array_int = NULL;
    struct chrm_entry* ce;


    //FILE* fpi;
    //unsigned int offset = 4;

    /*if (!wbinary) {
        fprintf(fp_out, "track type=wiggle_0 name=\"wig track\" description=\"Extended read pileup (%d bp) for every %d bp\"\n", extend_size, window_size);
    } else {
        fpi = fopen("/home/cholley/Documents/index.test", "wb+");
        if (fpi == NULL) {
            fprintf(stderr, "fpi fail\n");
            exit(1);
        }
    }*/

    while(fgets(line, 1024, fp_in) != NULL) {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        } else if (no_header || (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0)) {
            //printf("%s\n", line);

            ptr = line;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(chrname, ptr, lenptr);
            chrname[lenptr] = '\0';
            ptr = ptrend+1;

            //printf("chrm %s\n", chrname);

             /*if (region_stored != 0) {
                while(cur_region != region_stored && (cs = strcmp(region_array[cur_region].chrm, chrname)) < 0) {
                    fprintf(stderr, "cs %d\n,", cs);
                    cur_region++;
                }

                //fprintf(stderr, "cur cs %d\n,", cs);

                if (cur_region == region_stored) {
                    fprintf(stderr, "no region under the first line\n");
                    break;
                }

                if (cs != 0) {
                    continue;
                }

                if (cur_region+1 != region_stored && 
                    strcmp(region_array[cur_region].chrm, region_array[cur_region+1].chrm) == 0) {
                        next_region_same_chrm = 1;
                } else {
                    next_region_same_chrm = 0;
                }

                //printf("(next_region_same_chrm: %d\n", (next_region_same_chrm));

            } else {
                if (lookup_chrm(chrname) == NULL) {
                    continue;
                }
            } */

            if ((ce = lookup_chrm(chrname)) == NULL) {
                continue;
            }

            
            //printf("%s", line);

            if (region_stored != 0 && (region_stored == cur_region || ce->used == 0)) {
                continue;
            }

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            start_pos = atol(token);
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            end_pos = atol(token) - 1;

            //printf("start_pos %ld\n", start_pos);
            //printf("end_pos %ld\n", end_pos);

            
            if (extend_size != 0) {
                read_length = end_pos - start_pos;
                distance = extend_size - read_length;


                //printf("distance %d\n", distance);
                if (distance > 0) {
                    //printf("-- distance %d\n", distance);
                    ptr = ptrend+1;
                    ptrend = strchr(ptr, '\t');
                    ptr = ptrend+1;
                    ptrend = strchr(ptr, '\t');
                    ptr = ptrend+1;
                    ptrend = strchr(ptr, '\t');
                    if (ptrend == NULL) {
                        if (*ptr == '+') {
                            strand = '+';
                        } else {
                            strand = '-';
                        }
                    } else {
                        lenptr = ptrend-ptr;
                        strncpy(token, ptr, lenptr);
                        token[lenptr] = '\0';
                        if (token[0] == '+') {
                            strand = '+';
                        } else {
                            strand = '-';
                        }
                    }
                    
                    //printf("positive distance %d\n", distance);
                    if (strand == '+') {
                        end_pos += distance;
                    } else {
                        tmp = start_pos - distance;
                        if (tmp < 0) {
                            start_pos = 0; 
                        } else {
                            start_pos = tmp;
                        }
                    }
                }
            }

            //if (strcmp(chrname, "chr2") == 0 && start_pos > 20500) {
            //    continue;
            //}

            //printf("new start_pos %ld\n", start_pos);
            //printf("new end_pos %ld\n", end_pos);

            if (region_stored != 0) {

                //printf("cur_region %d\n", cur_region);
                //printf("(next_region_same_chrm: %d\n", (region_array[cur_region].same_chr_next_region));

                if (end_pos < region_array[cur_region].start) {
                    //printf("line skip 1\n");
                    continue;
                }

                //printf("line passed 0 %s", line);

                if (start_pos > region_array[cur_region].end) {
                    //printf("line passed 1 %s", line);

                    if (extend_size == 0 || strand == '-') {
                        if (region_array[cur_region].same_chr_next_region) {
                            if (end_pos < region_array[++cur_region].start) {
                                //printf("line skip 2\n");
                                continue;
                            }
                        } else {
                            cur_region++;
                            //printf("line skip 3\n");
                            continue;
                        }
                    } else {
                        //printf("line skip 4\n");
                        cur_region++;
                        continue;
                    }
                }
            }



            //char subbuff[20];
            //memcpy( subbuff, &line[0], 20);
            //printf("line passed %s | %ld - %ld\n", subbuff, start_pos, end_pos);
            

            if (strcmp(chrname, current_chrm) == 0) {

                //printf("++++\n");

                /*if (region_stored != 0) {

                    while (cur_region+1 != region_stored && strcmp(region_array[cur_region].chrm, region_array[cur_region+1].chrm) == 0
                            && start_pos < region_array[cur_region+1].start)  {
                        fprintf(stderr, "skip region  %d\n", cur_region);
                        cur_region++;
                    }


                    if (start_pos < region_array[cur_region].start) {
                        fprintf(stderr, "skip start %ld\n", start_pos);
                        continue;
                    } else if (end_pos > region_array[cur_region].end) {
                        fprintf(stderr, "skip end %ld\n", end_pos);
                        continue;
                    }
                }*/

                //printf("start_pos %ld / window_size %d : %ld", start_pos, window_size, start_window);
                start_window = start_pos / window_size;
                if (start_window > last_index) {
                    fprintf(stderr, "Error: Coordinate out of bound: %s\t%ld.\n", chrname, start_pos);
                    if (current_array_int != NULL) {
                        free(current_array_int);
                    }
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }

                end_window = end_pos / window_size;
                //printf("end_pos %ld\n", end_pos);
                //printf("window_size %d\n", window_size);
                //printf("end_window %ld\n", end_window);
                if (end_window > last_index) {

                    //printf("last index %ld\n", last_index);

                    end_window = last_index;
                }

                //continue;
                //printf("%ld %ld\n", start_window, end_window);

                for (r = start_window; r <= end_window; r++) {
                    //printf("%d\n",r);
                    current_array_int[r] += 1;
                }

                //printf("write data\n");

            } else {

                if (strncmp(current_chrm, "", 1) != 0) {
                    /*if (wbinary) {

                    struct bin_contents {
                       unsigned int position;
                       unsigned int count;
                    };

                    struct bin_contents bin_rec;


                    

                    char chrm[32] = "";
                    strcpy(chrm, current_chrm);

                        unsigned int span_write_region = 0;
                        unsigned int span_write = 0;
                        unsigned int span_write_tmp = 0;
                        unsigned char size_of_chrm = sizeof(chrm)/sizeof(chrm[0]);
                        //fprintf(fp_out, "variableStep chrom=%s span=%d\n", current_chrm, window_size);
                        for (i = 0; i < last_index; i++) {
                            int v = current_array_int[i];
                            if (v != 0) {
                                start_pos_window = i * window_size;
                                if (start_pos_window % 100000 == 0 && start_pos_window != 0) {
                                    fwrite(&chrm, sizeof(chrm[0]), size_of_chrm, fpi);
                                    fwrite(&start_pos_window, sizeof(unsigned int), 1, fpi);
                                    span_write_region = span_write_tmp - span_write;
                                    fwrite(&span_write_region, sizeof(unsigned int), 1, fpi);
                                    fwrite(&offset, sizeof(unsigned int), 1, fpi);
                                    offset += span_write * 8;
                                    span_write_tmp = span_write;
                                }

                                //write the table line anyway for R
                                fprintf(fp_out, "%ld\t%d\n", start_pos_window+1, v);
                                span_write++;
                            }
                        }

                        //fprintf(stderr, "test4\n");

                        //write the last data in index
                        if (start_pos_window % 100000 != 0) {
                            fwrite(&chrm, sizeof(chrm[0]), size_of_chrm, fpi);
                            //fprintf(stderr, "test3\n");
                            start_pos_window = (start_pos_window / 100000) * 100000;
                            fwrite(&start_pos_window, sizeof(unsigned int), 1, fpi);
                            //fprintf(stderr, "test2\n");
                            span_write = span_write - span_write_tmp;
                            fwrite(&span_write, sizeof(unsigned int), 1, fpi);
                            fwrite(&offset, sizeof(unsigned int), 1, fpi);
                            offset += span_write * 8;
                            //fprintf(stderr, "test1\n");
                        }
                    } else {*/
                        fprintf(fp_out, "variableStep chrom=%s span=%d\n", current_chrm, window_size);
                        for (i = 0; i < last_index; i++) {
                            int v = current_array_int[i];
                            if (v != 0) {
                                start_pos_window = i * window_size;

                                //write the table line anyway for R
                                fprintf(fp_out, "%ld\t%d\n", start_pos_window+1, v);
                            }
                        }
                    //}
                }

                if (region_stored != 0 && region_stored == cur_region) {
                    break;
                }

                strcpy(current_chrm, chrname);
                current_chrm_size = lookup_chrm(chrname)->size;
                last_index = current_chrm_size / window_size;

                if (current_array_int != NULL) {
                    free(current_array_int);
                }


                current_array_int = calloc((last_index + 1), sizeof(int));
                if (current_array_int == NULL) {
                    fprintf(stderr, "Error: cannot allocate memory block for current_array_int.\n");
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }

                //add this line also
                /*if (region_stored != 0) {
                    while (cur_region+1 != region_stored && strcmp(region_array[cur_region].chrm, region_array[cur_region+1].chrm) == 0
                            && start_pos < region_array[cur_region+1].start)  {
                        fprintf(stderr, "skip region  %d\n", cur_region);
                        cur_region++;
                    }

                    if (start_pos < region_array[cur_region].start) {
                        continue;
                    }
                }*/

                start_window = start_pos / window_size;
                if (start_window > last_index) {
                    fprintf(stderr, "Error: Coordinate out of bound: %s\t%ld.\n", chrname, start_pos);
                    if (current_array_int != NULL) {
                        free(current_array_int);
                    }
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }

                end_window = end_pos / window_size;
                if (end_window > last_index) {
                    end_window = last_index;
                }

                for (r = start_window; r <= end_window; r++) {
                    current_array_int[r] += 1;
                }
                //printf("test5\n");
            }
        }
    }

    //write the last chrmosome info if any
    if (strncmp(current_chrm, "", 1) != 0) {

        /*if (wbinary) {

            struct bin_contents {
               unsigned int position;
               unsigned int count;
            };

            struct bin_contents bin_rec;

            char chrm[32] = "";
            strcpy(chrm, current_chrm);
            /char span[32] = "";
            
            //sprintf(span,"%d", window_size);
            //fprintf(stderr, "%s\n", span);
            unsigned int a = 20000;
            unsigned int b = 512;
            unsigned int c = 30000;
            unsigned int d = 1024;
            unsigned int e = 40000;
            unsigned int f = 2048;
            fwrite(&window_size, sizeof(int), 1, fp_out);
            fwrite(chrm, sizeof(chrm[0]), sizeof(chrm)/sizeof(chrm[0]), fp_out);
            fwrite(&a, sizeof(unsigned int), 1, fp_out);
            fwrite(&b, sizeof(unsigned int), 1, fp_out);
            fwrite(&c, sizeof(unsigned int), 1, fp_out);
            fwrite(&d, sizeof(unsigned int), 1, fp_out);
            fwrite(&e, sizeof(unsigned int), 1, fp_out);
            fwrite(&f, sizeof(unsigned int), 1, fp_out);
            //fwrite(&window_size, sizeof(int), 1, fp_out);
            //fwrite(chrm, sizeof(chrm[0]), sizeof(chrm)/sizeof(chrm[0]), fp_out);
            fclose(fp_out);

            fprintf(stderr, "size of uint %lu\n",  sizeof(unsigned int));
            fprintf(stderr, "size of ulong %lu\n",  sizeof(unsigned long));

            fprintf(stderr, "size of struct rec %lu\n", sizeof(struct contents));

            fprintf(stderr, "test1\n");
            fprintf(stderr, "\n\n");
            FILE* fp = fopen("/home/cholley/Documents/wig.test", "rb");
            if (fp == NULL) {
                fprintf(stderr, "fp fail\n");
                exit(1);
            }

            int spanv;

            fprintf(stderr, "test2\n");
            fseek( fp, 44, SEEK_CUR);
            //fprintf(stderr, "test3\n");
            //fread(&spanv, 4, 1, fp);
            //fprintf(stderr,"spanv %d\n", spanv);
            //fread(&chrm, 32, 1, fp);
            //fprintf(stderr,"chrm %s\n", chrm);
            for ( int counter=0; counter < 10 && !feof(fp); counter++)
            {
                fprintf(stderr, "test4\n");
                fread(&rec, sizeof(struct contents), 1, fp);
                fprintf(stderr,"%lu\n", rec.position);
                fprintf(stderr,"%u\n", rec.count);
            }
            exit(1);

            fprintf(stderr, "test\n");

            unsigned int span_write_region = 0;
            unsigned int span_write = 0;
            unsigned int span_write_tmp = 0;
            unsigned char size_of_chrm = sizeof(chrm)/sizeof(chrm[0]);
            //fprintf(fp_out, "variableStep chrom=%s span=%d\n", current_chrm, window_size);
            for (i = 0; i < last_index; i++) {
                int v = current_array_int[i];
                if (v != 0) {
                    start_pos_window = i * window_size;
                    if (start_pos_window % 100000 == 0 && start_pos_window != 0) {
                        fwrite(&chrm, sizeof(chrm[0]), size_of_chrm, fpi);
                        fwrite(&start_pos_window, sizeof(unsigned int), 1, fpi);
                        span_write_region = span_write_tmp - span_write;
                        fwrite(&span_write_region, sizeof(unsigned int), 1, fpi);
                        fwrite(&offset, sizeof(unsigned int), 1, fpi);
                        offset += span_write * 8;
                        span_write_tmp = span_write;
                    }

                    //write the table line anyway for R
                    fprintf(fp_out, "%ld\t%d\n", start_pos_window+1, v);
                    span_write++;
                }
            }

            //fprintf(stderr, "test4\n");

            //write the last data in index
            if (start_pos_window % 100000 != 0) {
                fwrite(&chrm, sizeof(chrm[0]), size_of_chrm, fpi);
                //fprintf(stderr, "test3\n");
                start_pos_window = (start_pos_window / 100000) * 100000;
                fwrite(&start_pos_window, sizeof(unsigned int), 1, fpi);
                //fprintf(stderr, "test2\n");
                span_write = span_write - span_write_tmp;
                fwrite(&span_write, sizeof(unsigned int), 1, fpi);
                fwrite(&offset, sizeof(unsigned int), 1, fpi);
                offset += span_write * 8;
                //fprintf(stderr, "test1\n");
            }

        } else {*/
            fprintf(stdout, "variableStep chrom=%s span=%d\n", current_chrm, window_size);
            for (i = 0; i < last_index; i++) {
                int v = current_array_int[i];
                if (v != 0) {
                    start_pos_window = i * window_size;

                    //write the table line anyway for R
                    fprintf(stdout, "%ld\t%d\n", start_pos_window+1, v);
                }
            }
        //}
    }

    //free ressource
    if (current_array_int != NULL) {
        free(current_array_int);
    }

    /*if (wbinary) {

         fclose(fpi);

        //read the index file
        FILE* fpir = fopen("/home/cholley/Documents/index.test", "rb");
        if (fpir == NULL) {
            fprintf(stderr, "fpir fail\n");
            exit(1);
        }

        struct index_contents {
           char chrm[32];
           unsigned int position;
           unsigned int count;
           unsigned int offset;
        };

        struct index_contents index_rec;
        fprintf(stderr, "size of struct index_rec %lu\n", sizeof(struct index_contents));
        fseek( fpir, 0, SEEK_CUR);

        for ( int counter=0; counter < 10 && !feof(fpir); counter++) {
            fread(&index_rec, sizeof(struct index_contents), 1, fpir);
            fprintf(stderr,"%s\n", index_rec.chrm);
            fprintf(stderr,"%u\n", index_rec.position);
            fprintf(stderr,"%u\n", index_rec.count);
            fprintf(stderr,"%u\n", index_rec.offset);
            fprintf(stderr,"\n");
        }

        fclose(fpir);

    }*/


    return;
}
