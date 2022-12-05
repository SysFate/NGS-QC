#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/median.h"
#include "../lib/genome.h"

//extern unsigned int median(int l, unsigned int * p, unsigned int kthmin);



void build_local_bg_table(FILE*  fp_in,
                     FILE* fp_out,
                     unsigned int large_window_size,
                     unsigned int window_size,
                     float kthminf,
                     unsigned char no_header) {

    char line[1024];

    char* ptr;
    char* ptrend;
    int lenptr;

    long start_pos;
    long end_pos;
    unsigned long start_window;
    unsigned long prev_start_window;
    unsigned int sub_start_window;
    unsigned long end_window;
    unsigned int sub_end_window;
    unsigned long start_pos_window;
    unsigned long end_pos_window;
    unsigned long line_nb = 0;

    char chrname[128] = "";
    char token[128] = "";
    char current_chrm[128] = "";
    char strand[2];
    unsigned long current_chrm_size = 0;
    unsigned int last_index = 0;

    unsigned int read_length = 0;
    unsigned int i = 0;
    unsigned int* intensities = NULL;
    unsigned int outside_intensity = 0;


    unsigned int sub_windows = large_window_size / window_size;

    int kthmin = (sub_windows-1) * kthminf;

    //printf("%d\n", (int)(((sub_windows-1) * kthminf) + 0.5));
    kthmin = (sub_windows) - (int)(((sub_windows-1) * kthminf) + 0.5);


    //exit(0);
    //printf("sub_windows: %d\n", sub_windows);
    unsigned int last_sub_index;
    unsigned int sub_intensities[sub_windows];
    for (; i < sub_windows; i++) {
        sub_intensities[i] = 0;
        //printf("%d - ", sub_intensities[i]);
    }
    //i = 0;


    while(fgets(line, 1024, fp_in) != NULL) {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        } else if (no_header || (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0)) {
            ptr = line;
            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(chrname, ptr, lenptr);
            chrname[lenptr] = '\0';

            //ignore line with unwanted chrm
            ++line_nb;
            if (lookup_chrm(chrname) == NULL) {
                continue;
            }
            ptr = ptrend+1;

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

            for (i = 0; i < 3; i++) {
                ptr = ptrend+1;
                ptrend = strchr(ptr, '\t');
            }

            if (ptrend == NULL) {
                strand[0] = *ptr;
                strand[1] = '\0';
            } else {
                strncpy(strand, ptr, 1);
                strand[1] = '\0';
            }

            read_length = end_pos - start_pos;

            /*if (read_length < elongation_size) {
                if (strand[0] ==  '+') {
                    //end_pos += elongation_size - read_length;
                    end_pos = start_pos + elongation_size;
                } else {
                    //start_pos -=  elongation_size - read_length;
                    start_pos = end_pos - elongation_size;
                }
            } else */

            if (window_size < read_length) {
                //printf("%s", line);
                //printf("read_length %d\n", read_length);
                fprintf(stderr, "Error: window size must be greater than the read size.\n");
                fprintf(stderr, "Line: %s\n", line);
                if (intensities != NULL) {
                    free(intensities);
                }
                fclose(fp_in);
                fclose(fp_out);
                exit(1);
            }

            //printf("start pos %ld\n", start_pos);
            //printf("end pos %ld\n", end_pos);

            if (start_pos < 0) {
                start_pos = 0;
            }

            if (strcmp(chrname, current_chrm) == 0) {
                //second to last line of a chrm
                start_window = start_pos / large_window_size;
                sub_start_window = (start_pos % large_window_size) / window_size;

                if (start_window > last_index || (start_window == last_index && sub_start_window > last_sub_index)) {
                    fprintf(stderr, "Error: Coordinate out of bound: %s\t%ld.\n", chrname, start_pos);
                    if (intensities != NULL) {
                        free(intensities);
                    }
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }
                end_window = end_pos / large_window_size;
                sub_end_window = (end_pos % large_window_size) / window_size;
                //printf("%ld\t%d\t%ld\t%d\n", start_window, sub_start_window, end_window, sub_end_window);
                if (end_window > last_index) {
                    //printf("end_window too high\n");
                    end_window = last_index;
                    if (sub_end_window > last_sub_index) {
                        //printf("sub_end_window too high\n");
                        sub_end_window = last_sub_index;
                    }
                }
                
                // ???
                //if (sub_start_window == sub_windows-1 && sub_end_window == 0) {
                //    sub_end_window = sub_windows;
                //}


                //printf("incr %d\t%d\n", sub_start_window, sub_end_window);
                //write_last_int = false;
                if (start_window != prev_start_window) {
                    //printf("%s", line);
                    //printf("sub_intensities array:\n");
                    //for (i = 0; i < sub_windows; i++) {
                    //    printf("%d - ", sub_intensities[i]);
                    //}
                    //printf("\n");
                    //printf("median: %d\n", median(sub_windows, sub_intensities));
                    //printf("writting start_window: %ld\n", prev_start_window);
                    intensities[prev_start_window] = median(sub_windows, sub_intensities, kthmin);
                    //fflush(stdout);
                    //printf("new sub_intensities array:\n");
                    sub_intensities[0] = outside_intensity;
                    //printf("outside_intensity %d\n", outside_intensity);
                    //printf("%d - ", sub_intensities[0]);
                    for (i = 1; i < sub_windows; i++) {
                        sub_intensities[i] = 0;
                        //printf("%d - ", sub_intensities[i]);
                    }
                    outside_intensity = 0;
                    //printf("\n");
                    //write_last_int = true;
                    sub_intensities[sub_start_window] += 1;
                    if (sub_start_window != sub_end_window && sub_end_window != 0) {
                        sub_intensities[sub_end_window] += 1;
                    }
                } else {
                    sub_intensities[sub_start_window] += 1;
                    //printf("sub_start_window: %d\n", sub_start_window);
                    //printf("sub_end_window: %d\n", sub_end_window);
                    if (sub_start_window != sub_end_window) {
                        if (sub_end_window == 0) {
                            outside_intensity += 1;
                        } else {
                            sub_intensities[sub_end_window] += 1;
                        }
                    }
                }
                //printf("write last: %d\n", write_last_int);
                //printf("start_window: %d\n", start_window);
                prev_start_window = start_window;
                //intensities[start_window] += 1;
                //if (start_window != end_window) {
                //    intensities[end_window] += 1;
                //}
            } else {
                if (strncmp(current_chrm, "", 1) != 0) { /* case false for the first line of the file*/
                    //printf("last index: %d\n", last_index);
                    //printf("last bin: %d\n", last_index * window_size);
                    //printf("crash bin: chr12\t128325500\n");

                    //printf("last sub_intensities array:\n");
                    //for (i = 0; i < sub_windows; i++) {
                        //printf("%d - ", sub_intensities[i]);
                    //}
                    //printf("\n");
                    //printf("sub_end_window+1: %d\n", sub_end_window+1);
                    //printf("median: %d\n", median(sub_end_window+1, sub_intensities));
                    //printf("writting start_window: %d\n", prev_start_window);
                    intensities[prev_start_window] = median(sub_end_window+1, sub_intensities, (sub_end_window+1) - (int)(((sub_end_window) * kthminf) + 0.5));
                    //fflush(stdout);
                    //printf("new sub_intensities array:\n");
                    //printf("outside_intensity %d", outside_intensity);
                    //printf("\n");

                    for (i = 0; i < last_index + 1; i++) {
                        int v = intensities[i];
                        if (v > 0) {
                            start_pos_window = i * large_window_size;
                            if (i == last_index) {
                                end_pos_window = current_chrm_size;
                            } else {
                                end_pos_window = start_pos_window + large_window_size;
                            }

                            //write the table line anyway for R
                            fprintf(fp_out, "%s\t%ld\t%ld\t%d\n",
                                current_chrm, start_pos_window, end_pos_window,
                                v);
                        }
                    }
                }
                //printf("test2\n");
                strcpy(current_chrm, chrname);
                current_chrm_size = lookup_chrm(chrname)->size;
                if (intensities != NULL) {
                    free(intensities);
                }
                //printf("test3\n");
                //printf("ccs: %ld\n", (current_chrm_size / window_size) + 1);
                intensities = calloc(((current_chrm_size / large_window_size) + 1), sizeof(unsigned int));
                if (intensities == NULL) {
                    fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s100.\n");
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }

                //printf("current_chrm_size: %ld\n", current_chrm_size);
                //printf("large_window_size: %d\n", large_window_size);
                //float a = current_chrm_size / (float)large_window_size;
                //printf("a: %f\n", a);
                last_index = current_chrm_size / large_window_size;
                //printf("last_index: %d\n", last_index);
                //printf("last_coor: %d\n", last_index * large_window_size);
                last_sub_index = (current_chrm_size % large_window_size) / window_size;
                //printf("last_sub_index: %d\n", last_sub_index);
                //add this line to the bin table
                start_window = start_pos / large_window_size;
                sub_start_window = (start_pos % large_window_size) / window_size;
                if (start_window > last_index) {
                    fprintf(stderr, "Error: Coordinate out of bound: %s\t%ld.\n", chrname, start_pos);
                    if (intensities != NULL) {
                        free(intensities);
                    }
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }

                //printf("test4\n");
                end_window = end_pos / large_window_size;
                sub_end_window = (end_pos % large_window_size) / window_size;
                //printf("%ld\t%d\t%ld\t%d\n", start_window, sub_start_window, end_window, sub_end_window);
                if (end_window > last_index) {
                    //printf("end_window too high\n");
                    end_window = last_index;
                    if (sub_end_window > last_sub_index) {
                        //printf("sub_end_window too high\n");
                        sub_end_window = last_sub_index;
                    }
                }

                //printf("start_pos: %ld\n", start_window);
                // optimize check sub_start_window != sub_end_window before
                sub_intensities[sub_start_window] += 1;
                if (sub_start_window != sub_end_window) {
                    sub_intensities[sub_end_window] += 1;
                }

                //printf("incr %d\t%d\n", sub_start_window, sub_end_window);
                // first line of each chrmosome
                if (sub_end_window == last_sub_index) {
                    //compute median only if we reach the last sub index
                    // this considere that the first line is not in the last largebin of the chromosome
                    // the median is obviouly 0 unless the number of sub_window < 3 it is 1
                    if (sub_windows == 1) {
                        intensities[start_window] = 1;
                    } else if (sub_windows == 2) {
                        intensities[start_window] = 1;
                    } else {
                        intensities[start_window] = 0;
                    }
                }

                /*if (line_nb != 1 && start_window != prev_start_window) {
                    printf("sub_intensities array:\n");
                    for (i = 0; i < sub_windows+1; i++) {
                        printf("%d - ", sub_intensities[i]);
                    }
                    printf("\n");
                    fflush(stdout);
                    intensities[start_window] = median(sub_windows, sub_intensities);
                    printf("new sub_intensities array:\n");
                    sub_intensities[0] = sub_intensities[--i];
                    //printf("%d - ", sub_intensities[0]);
                    for (i = 1; i < sub_windows+1; i++) {
                        sub_intensities[i] = 0;
                        //printf("%d - ", sub_intensities[i]);
                    }
                    //printf("\n");
                }*/

                prev_start_window = start_window;
                //printf("test5\n");
            }
        }
    }

    //write the last chrmosome info if any
    if (strncmp(current_chrm, "", 1) != 0) {
        //printf("print last chrm\n");

        //printf("last sub_intensities array:\n");
        //for (i = 0; i < sub_windows; i++) {
            //printf("%d - ", sub_intensities[i]);
        //}
        //printf("\n");
        //printf("sub_end_window+1: %d\n", sub_end_window+1);
        //printf("median: %d\n", median(sub_end_window+1, sub_intensities));
        //printf("writting start_window: %ld\n", prev_start_window);
        intensities[prev_start_window] = median(sub_end_window+1, sub_intensities, (sub_end_window+1) - (int)(((sub_end_window) * kthminf) + 0.5));
        //fflush(stdout);
        //printf("new sub_intensities array:\n");
        //printf("outside_intensity %d", outside_intensity);
        //printf("\n");


        //printf("test4\n");
        //printf("last index: %d\n", last_index);
        for (i = 0; i < last_index + 1; i++) {
            int v = intensities[i];
            if (v > 0) {
                start_pos_window = i * large_window_size;
                //printf("start_pos_window %ld\n", start_pos_window);

                if (i == last_index) {
                    end_pos_window = current_chrm_size;
                } else {
                    end_pos_window = start_pos_window + large_window_size;
                }

                //write the table line anyway for R
                fprintf(fp_out, "%s\t%ld\t%ld\t%d\n",
                    current_chrm, start_pos_window, end_pos_window, v);
            }
        }
    }

    if (intensities != NULL) {
        free(intensities);
    }

    return;
}


