#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/genome.h"

extern char **chrm_array;
extern int chrm_num;


void pileup(FILE* fp_in, FILE* fp_out, unsigned int window_size, unsigned int extend_size, unsigned char no_header, unsigned char zero_fill) {

    char line[1024];
    char chrname[128] = "";
    char current_chrm[128] = "";
    long start_pos;
    unsigned long end_pos;
    char strand;

    char* ptr;
    char* ptrend;

    unsigned long last_index;
    unsigned long last_index_fb;
    unsigned long start_window;
    unsigned long end_window;
    unsigned long start_pos_window;
    unsigned long current_chrm_size = 0;
    unsigned long current_chrm_size_fb = 0;

    unsigned int read_length = 0;
    int distance = 0;

    unsigned int r = 0, i = 0, v;
    unsigned int threshold = 1;
    if (zero_fill)
        threshold = 0;

    int lenptr;
    char token[128] = "";

    int* current_array_int = NULL;
    int chrm_array_index = 0;

    //strcpy(chrm_array[10], "Chr2");

    //for (int l = 0; l < chrm_num; l++) {
    //    printf("%s\n", chrm_array[l]);
    //}

    //printf("------------\n");


    //for (int l = 0; l < chrm_num; l++) {
    //    printf("%s\n", chrm_array[l]);
    //}
 
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

            if (lookup_chrm(chrname) == NULL) {
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

            if (extend_size != 0) {
                read_length = end_pos - start_pos;
                distance = extend_size - read_length;

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

                if (strand == '+') {
                    end_pos = end_pos + distance;
                } else {
                    start_pos = start_pos - distance;
                    if (start_pos < 0)
                        start_pos = 0;
                }
            }

            if (strcmp(chrname, current_chrm) == 0) {

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
            } else {

                if (zero_fill) {
                    while (chrm_array_index < chrm_num && strcmp(chrname, chrm_array[chrm_array_index]) != 0) {
                        if (strcmp(current_chrm, chrm_array[chrm_array_index]) == 0) {
                            ++chrm_array_index;
                            break;
                        }
                        current_chrm_size_fb = lookup_chrm(chrm_array[chrm_array_index])->size;
                        last_index_fb = current_chrm_size_fb / window_size;
                        for (i = 0; i < last_index_fb + 1; i++) {
                            start_pos_window = i * window_size;
                            fprintf(fp_out, "%s\t%ld\t0\n", chrm_array[chrm_array_index], start_pos_window);
                        }
                        ++chrm_array_index;
                    }
                }

                if (strncmp(current_chrm, "", 1) != 0) {
                    for (i = 0; i < last_index + 1; i++) {
                        v = current_array_int[i];
                        if (v >= threshold) {
                            start_pos_window = i * window_size;
                            fprintf(fp_out, "%s\t%ld\t%d\n", current_chrm, start_pos_window, v);
                        }
                    }
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
            }
        }
    }

    //write the last chrmosome info if any

    if (zero_fill) {
        while (chrm_array_index < chrm_num && strcmp(chrname, chrm_array[chrm_array_index]) != 0) {
            if (strcmp(current_chrm, chrm_array[chrm_array_index]) == 0) {
                ++chrm_array_index;
                break;
            }
            current_chrm_size_fb = lookup_chrm(chrm_array[chrm_array_index])->size;
            last_index_fb = current_chrm_size_fb / window_size;
            for (i = 0; i < last_index_fb + 1; i++) {
                start_pos_window = i * window_size;
                fprintf(fp_out, "%s\t%ld\t0\n", chrm_array[chrm_array_index], start_pos_window);
            }
            ++chrm_array_index;
        }
    }

    if (strncmp(current_chrm, "", 1) != 0) {
        for (i = 0; i < last_index + 1; i++) {
            v = current_array_int[i];
            if (v >= threshold) {
                start_pos_window = i * window_size;
                fprintf(fp_out, "%s\t%ld\t%d\n", current_chrm, start_pos_window, v);
            }
        }
        ++chrm_array_index;
    }

    if (zero_fill) {
        while (chrm_array_index < chrm_num) {
            current_chrm_size_fb = lookup_chrm(chrm_array[chrm_array_index])->size;
            last_index_fb = current_chrm_size_fb / window_size;
            for (i = 0; i < last_index_fb + 1; i++) {
                start_pos_window = i * window_size;
                fprintf(fp_out, "%s\t%ld\t0\n", chrm_array[chrm_array_index], start_pos_window);
            }
            ++chrm_array_index;
        }
    }

    if (current_array_int != NULL) {
        free(current_array_int);
    }

    return;
}
