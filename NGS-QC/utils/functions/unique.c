#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/genome.h"


/* count number of unique reads and print unique reads line on stdout if asked */
void check_unique_read(FILE* fp_in, FILE* fp_out, unsigned char no_header, unsigned char write_file) {

    char line[1024];
    char chrname[32] = "";
    unsigned long start;
    unsigned long end;
    char strand;

    char prev_chrname[32] = "";
    unsigned long prev_start = -999999999;
    unsigned long prev_end  = -999999999;
    char prev_strand = 0;

    unsigned int unique_read = 0;
    unsigned int reads = 0;
    unsigned int h_reads = 0;

    char* ptr;
    char* ptrend;

    int lenptr;
    char token[32] = "";

    int used_chrm_alloc = 1024;
    char* used_chrm = (char*)malloc(used_chrm_alloc * sizeof(char));


    while(fgets(line, 1024, fp_in) != NULL) {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        } else if (no_header || (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0)) {
            reads++;
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
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            end = atol(token);

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

            if (strcmp(chrname, prev_chrname) == 0) {
                if (start == prev_start && end == prev_end && strand == prev_strand) {
                    continue;
                }
            } else {
                while (((int)strlen(chrname) + (int)strlen(used_chrm) + 1) > used_chrm_alloc) {
                    used_chrm_alloc *= 2;
                    if ((used_chrm = realloc(used_chrm, used_chrm_alloc)) == NULL) {
                        fprintf(stderr, "Error: cannot allocate user_chrm memory.\n");
                        fclose(fp_in);
                        fclose(fp_out);
                        exit(1);
                    }
                }
                strcat(used_chrm, chrname);
                strcat(used_chrm, ",");
            }

            unique_read++;

            if (write_file) {
                fprintf(fp_out, "%s\t%ld\t%ld\t\t\t%c\n", chrname, start, end, strand);
            }

            strcpy(prev_chrname, chrname);
            prev_start = start;
            prev_end = end;
            prev_strand = strand;
        } else {
            h_reads++;
        }
    }

    //fix chrm used string
    if (strlen(used_chrm) > 0) {
        used_chrm[strlen(used_chrm)-1] = '\0';
    } else {
        strcpy(used_chrm, "-");
    }

    fprintf(stderr, "%d\t%d\t%d\t%s\n", reads, unique_read, h_reads, used_chrm);

    return;
}
