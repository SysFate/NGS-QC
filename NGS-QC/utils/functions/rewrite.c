#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void rewrite_bed_file(FILE* fp_in, FILE* fp_out, unsigned int error_code, unsigned char no_header) {

    char line[1024];
    unsigned int field = 6;
    char delim = '\t';

    char* ptr;
    char* ptrend;

    char chrname[64];
    char start[64];
    char end[64];
    char strand[2];

    int lenptr;

    unsigned int i;

    if (error_code == 2 || error_code == 16) {
        if (error_code == 16) {
            delim = ' ';
        }
        field = 4;
    } else if (error_code == 4 || error_code == 32) {
        if (error_code == 32) {
            delim = ' ';
        }
        field = 5;
    } else if (error_code == 8) {
        delim = ' ';
    }

    while(fgets(line, 1024, fp_in) != NULL) {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        } else if  (no_header || (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0)) {
            ptr = line;
            ptrend = strchr(ptr, delim);
            lenptr = ptrend-ptr;
            strncpy(chrname, ptr, lenptr);
            chrname[lenptr] = '\0';
            ptr = ptrend+1;

            ptrend = strchr(ptr, delim);
            lenptr = ptrend-ptr;
            strncpy(start, ptr, lenptr);
            start[lenptr] = '\0';
            ptr = ptrend+1;

            ptrend = strchr(ptr, delim);
            lenptr = ptrend-ptr;
            strncpy(end, ptr, lenptr);
            end[lenptr] = '\0';
            
            for (i = 3; i < field; i++) {
                ptr = ptrend+1;
                ptrend = strchr(ptr, delim);
            }

            if (ptrend == NULL) {
                strand[0] = *ptr;
                strand[1] = '\0';
            } else {
                strncpy(strand, ptr, 1);
                strand[1] = '\0';
            }

            fprintf(fp_out, "%s\t%s\t%s\tt\t0\t%c\n", chrname, start, end, strand[0]);
        }
    }

    return;
}
