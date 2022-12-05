#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/genome.h"

#define true 1
#define false 0


void check_bed_file_sorted(FILE* fp_in, unsigned char no_header) {

    char line[1024];
    char chrname[32] = "";
    char tmp_chrname[32] = "";
    unsigned long start;
    unsigned long tmp_start = -999999999;
    unsigned char strand;
    unsigned char tmp_strand;

    unsigned int reads = 0;

    char* ptr;
    char* ptrend;

    int cs = 0;
    int lenptr;

    char token[32] = "";

    unsigned int dif_strand = false;
    unsigned int sorted = 1;

    struct chrm_entry* ce;

    while(fgets(line, 1024, fp_in) != NULL) {
        //printf("%s",line);
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        } else if (no_header || (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0)) {
            ptr = line;
            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(chrname, ptr, lenptr);
            chrname[lenptr] = '\0';
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            start = atol(token);

            cs = strcmp(chrname, tmp_chrname);
            //if (cs < 0) { /* chrm not sorted (may not work it sorted base on chrm number, chr9 > chr10 > chr1) */
            //    sorted = 0;
            //    break; 
            /*} else*/ if (cs != 0) { /* different chr */
                if ((ce = lookup_chrm(chrname)) != NULL) { /* if the chrm already exists in the dict, file is unsorted */
                    sorted = 0;
                    break;
                } else {
                     ce = put_chrm(chrname, 1);
                }
            } else {
                if (start < tmp_start) {
                    sorted = 0;
                    break;
                } else if (reads == 0) {
                    ce = put_chrm(chrname, 1); /* first line case*/
                } else if (start == tmp_start) {
                    //check if the strand is different
                    //get the strand
                    ptr = ptrend+1;
                    ptrend = strchr(ptr, '\t');
                    ptr = ptrend+1;
                    ptrend = strchr(ptr, '\t');
                    ptr = ptrend+1;
                    ptrend = strchr(ptr, '\t');
                    ptr = ptrend+1;
                    ptrend = strchr(ptr, '\t');
                    if (ptrend == NULL) {
                        if (*ptr == '+') {
                            strand = 0;
                        } else {
                            strand = 1;
                        }
                    } else {
                        lenptr = ptrend-ptr;
                        strncpy(token, ptr, lenptr);
                        //token[lenptr] = '\0';
                        if (token[0] == '+') {
                            strand = 0;
                        } else {
                            strand = 1;
                        }
                    }
                    if (tmp_strand != strand) {
                        if (dif_strand) {
                            /* if the strand is different and if was different before e.g:
                             * chr1 100 200 tag 0 +
                             * chr1 100 200 tag 0 -
                             * chr1 100 200 tag 0 +
                             * the file is not sorted
                             */
                            sorted = 0;
                            break;
                        }
                        dif_strand = true;
                    }
                    strcpy(tmp_chrname, chrname);
                    tmp_start = start;
                    tmp_strand = strand;
                    reads++;
                    continue;
                } else {
                    /* reset */
                    dif_strand = false;
                }

            }
            //get the strand
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            if (ptrend == NULL) {
                if (*ptr == '+') {
                    strand = 0;
                } else {
                    strand = 1;
                }
            } else {
                lenptr = ptrend-ptr;
                strncpy(token, ptr, lenptr);
                //token[lenptr] = '\0';
                if (token[0] == '+') {
                    strand = 0;
                } else {
                    strand = 1;
                }
            }
            strcpy(tmp_chrname, chrname);
            tmp_start = start;
            tmp_strand = strand;
            reads++;
        }
    }

    printf("%d\n", sorted);
    return;
}

