#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../lib/genome.h"
#include "../lib/str_tools.h"
#include "../lib/bit_array.h"

#define true 1
#define false 0

// ##################################################################################


void build_bin_table_rep(FILE* fp_in,
                     FILE* fp_out,
                     unsigned int window_size,
                     unsigned char rep_number,
                     unsigned int threshold,
                     unsigned char no_header) {

    char line[1024];

    char* ptr;
    char* ptrend;
    int lenptr;

    long start_pos;
    long end_pos;
    unsigned long start_window;
    unsigned long end_window;
    unsigned long start_pos_window;
    unsigned long end_pos_window;
    unsigned long line_nb = 0;

    char chrname[128] = "";
    char token[128] = "";
    char current_chrm[128] = "";
    unsigned long current_chrm_size = 0;
    unsigned int last_index = 0;

    int bin_count = 0;
    int bin_count_bgs = 0;
    //int bin_count_10perc = 0;

    int* current_array_pos_s100 = NULL;
    int* current_array_pos_s90[rep_number];
    int* current_array_pos_s70[rep_number];
    int* current_array_pos_s50[rep_number];
    //int qc_array_size = 3 * rep_number;
    //float qc_val[qc_array_size];

    /*char bdo = false;
    float s90;
    float s70;
    float s50;
    float s90m;
    float s70m;
    float s50m;*/

    for (int r = 0; r < rep_number; r++) {
        current_array_pos_s50[r] = NULL;
        current_array_pos_s70[r] = NULL;
        current_array_pos_s90[r] = NULL;
    }

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
            if (start_pos < 0) {
                start_pos = 0;
            }
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            end_pos = atol(token) - 1;

            if (strcmp(chrname, current_chrm) == 0) {

                start_window = start_pos / window_size;
                if (start_window > last_index) {
                    fprintf(stderr, "Error: Coordinate out of bound: %s\t%ld.\n", chrname, start_pos);
                    destroy_rep_array_ba();
                    //destroy_chrm_entry_hash();
                    if (current_array_pos_s100 != NULL) {
                        free(current_array_pos_s100);
                        for (int r = 0; r < rep_number; r++) {
                            free(current_array_pos_s50[r]);
                            free(current_array_pos_s70[r]);
                            free(current_array_pos_s90[r]);
                        }
                    }
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }
                end_window = end_pos / window_size;
                if (end_window > last_index) {
                    end_window = last_index;
                }


                current_array_pos_s100[start_window] += 1;
                for (int r = 0; r < rep_number; r++) {
                    if (!test_bit(rep_array_ba[r]->ba1, line_nb)) {
                        current_array_pos_s50[r][start_window] += 1;
                    }
                    if (!test_bit(rep_array_ba[r]->ba2, line_nb)) {
                        current_array_pos_s70[r][start_window] += 1;
                    }
                    if (!test_bit(rep_array_ba[r]->ba3, line_nb)) {
                        current_array_pos_s90[r][start_window] += 1;
                    }
                }
                if (start_window != end_window) {
                    current_array_pos_s100[end_window] += 1;
                    for (int r = 0; r < rep_number; r++) {
                        if (!test_bit(rep_array_ba[r]->ba1, line_nb)) {
                            current_array_pos_s50[r][end_window] += 1;
                        }
                        if (!test_bit(rep_array_ba[r]->ba2, line_nb)) {
                            current_array_pos_s70[r][end_window] += 1;
                        }
                        if (!test_bit(rep_array_ba[r]->ba3, line_nb)) {
                            current_array_pos_s90[r][end_window] += 1;
                        }
                    }
                }
            } else {
                if (strncmp(current_chrm, "", 1) != 0) {
                    //printf("last index: %d\n", last_index);
                    //printf("last bin: %d\n", last_index * window_size);
                    //printf("crash bin: chr12\t128325500\n");

                    for (unsigned int i = 0; i < last_index + 1; i++) {
                        unsigned int v = current_array_pos_s100[i];
                        bin_count++;
                        if (v >= threshold) {
                            bin_count_bgs++;
                            start_pos_window = i * window_size;

                            if (i == last_index) {
                                end_pos_window = current_chrm_size;
                            } else {
                                end_pos_window = start_pos_window + window_size;
                            }

                            //bdo = false;

                            /*for (int r = 0; r < rep_number; r++) {
                                s90 = ((float)(100 * current_array_pos_s90[r][i])/v);
                                //qc_val[r] = s90;
                                s90m = s90 - 90;
                                //qc_val[r + (3 * rep_number)] = s90m;
                                qc_val[r] = s90m;

                                s70 = ((float)(100 * current_array_pos_s70[r][i])/v);
                                //qc_val[r + rep_number] = s70;
                                s70m = s70 - 70;
                                //qc_val[r + (4 * rep_number)] = s70m;
                                qc_val[r + rep_number] = s70m;

                                s50 = ((float)(100 * current_array_pos_s50[r][i])/v);
                                //qc_val[r + (rep_number * 2)] = s50;
                                s50m = s50 - 50;
                                //qc_val[r + (5 * rep_number)] = s50m;
                                qc_val[r + (rep_number * 2)] = s50m;

                                if (!bdo && fabs(s50m) < 10 && fabs(s70m) < 10 && fabs(s90m) < 10) {
                                    bdo = true;
                                }
                            }*/

                            //if (bdo) {
                            //    bin_count_10perc++;
                                fprintf(fp_out, "%s\t%ld\t%ld\t%d\t", current_chrm, start_pos_window, end_pos_window, v);
                                for (int r = 0; r < rep_number; r++) {
                                    fprintf(fp_out, "%d\t", current_array_pos_s90[r][i]);
                                }
                                for (int r = 0; r < rep_number; r++) {
                                    fprintf(fp_out, "%d\t", current_array_pos_s70[r][i]);
                                }
                                for (int r = 0; r < rep_number - 1; r++) {
                                    fprintf(fp_out, "%d\t", current_array_pos_s50[r][i]);
                                }
                                fprintf(fp_out, "%d\n", current_array_pos_s50[rep_number - 1][i]);
                             //   for (int j = 0; j < qc_array_size - 1; j++) {
                             //       fprintf(fp_out, "%.4f\t", qc_val[j]);
                             //  }
                             //   fprintf(fp_out, "%.4f\n", qc_val[qc_array_size - 1]);
                            //}
                        }
                    }
                }
                //printf("test2\n");
                strcpy(current_chrm, chrname);
                current_chrm_size = lookup_chrm(chrname)->size;
                if (current_array_pos_s100 != NULL) {
                    free(current_array_pos_s100);
                    for (int r = 0; r < rep_number; r++) {
                        free(current_array_pos_s50[r]);
                        free(current_array_pos_s70[r]);
                        free(current_array_pos_s90[r]);
                    }
                }
                //printf("test3\n");
                //printf("%d\n", window_size);
                //printf("ccs: %ld\n", (current_chrm_size / window_size) + 1);
                current_array_pos_s100 = calloc(((current_chrm_size / window_size) + 1), sizeof(int));
                if (current_array_pos_s100 == NULL) {
                    fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s100.\n");
                    exit(1);
                }
                for (int r = 0; r < rep_number; r++) {
                    current_array_pos_s50[r] = calloc(((current_chrm_size / window_size) + 1), sizeof(int));
                    if (current_array_pos_s50[r] == NULL) {
                        fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s50.\n");
                        exit(1);
                    }
                    current_array_pos_s70[r] = calloc(((current_chrm_size / window_size) + 1), sizeof(int));
                    if (current_array_pos_s70[r] == NULL) {
                        fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s70.\n");
                        exit(1);
                    }
                    current_array_pos_s90[r] = calloc(((current_chrm_size / window_size) + 1), sizeof(int));
                    if (current_array_pos_s90[r] == NULL) {
                        fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s90.\n");
                        exit(1);
                    }
                }
                //printf("test4\n");

                last_index = current_chrm_size / window_size;
                //printf("last_index : %s %d\n", chrname, last_index);
                //add this line to the bin table
                start_window = start_pos / window_size;
                if (start_window > last_index) {
                    fprintf(stderr, "Error: Coordinate out of bound: %s\t%ld.\n", chrname, start_pos);
                    destroy_rep_array_ba();
                    //destroy_chrm_entry_hash();
                    if (current_array_pos_s100 != NULL) {
                        free(current_array_pos_s100);
                        for (int r = 0; r < rep_number; r++) {
                            free(current_array_pos_s50[r]);
                            free(current_array_pos_s70[r]);
                            free(current_array_pos_s90[r]);
                        }
                    }
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }

                //printf("test5\n");
                end_window = end_pos / window_size;
                if (end_window > last_index) {
                    end_window = last_index;
                }

                //printf("start_pos: %ld\n", start_window);
                current_array_pos_s100[start_window] += 1;
                for (int r = 0; r < rep_number; r++) {
                    if (!test_bit(rep_array_ba[r]->ba1, line_nb)) {
                        current_array_pos_s50[r][start_window] += 1;
                    }
                    if (!test_bit(rep_array_ba[r]->ba2, line_nb)) {
                        current_array_pos_s70[r][start_window] += 1;
                    }
                    if (!test_bit(rep_array_ba[r]->ba3, line_nb)) {
                        current_array_pos_s90[r][start_window] += 1;
                    }
                }
                if (start_window != end_window) {
                   current_array_pos_s100[end_window] += 1;
                    for (int r = 0; r < rep_number; r++) {
                        if (!test_bit(rep_array_ba[r]->ba1, line_nb)) {
                            current_array_pos_s50[r][end_window] += 1;
                        }
                        if (!test_bit(rep_array_ba[r]->ba2, line_nb)) {
                            current_array_pos_s70[r][end_window] += 1;
                        }
                        if (!test_bit(rep_array_ba[r]->ba3, line_nb)) {
                            current_array_pos_s90[r][end_window] += 1;
                        }
                    }
                }
                //printf("test6\n");
            }
        } else {
            continue;
        }
    }

    //write the last chrmosome info if any
    if (strncmp(current_chrm, "", 1) != 0) {
        //printf("test7\n");
        for (unsigned int i = 0; i < last_index + 1; i++) {
            unsigned int v = current_array_pos_s100[i];
            bin_count++;
            if (v >= threshold) {
                bin_count_bgs++;
                start_pos_window = i * window_size;

                if (i == last_index) {
                    end_pos_window = current_chrm_size;
                } else {
                    end_pos_window = start_pos_window + window_size;
                }

                /*for (int r = 0; r < rep_number; r++) {
                    s90 = ((float)(100 * current_array_pos_s90[r][i])/v);
                    //qc_val[r] = s90;
                    s90m = s90 - 90;
                    //qc_val[r + (3 * rep_number)] = s90m;
                    qc_val[r] = s90m;

                    s70 = ((float)(100 * current_array_pos_s70[r][i])/v);
                    //qc_val[r + rep_number] = s70;
                    s70m = s70 - 70;
                    //qc_val[r + (4 * rep_number)] = s70m;
                    qc_val[r + rep_number] = s70m;

                    s50 = ((float)(100 * current_array_pos_s50[r][i])/v);
                    //qc_val[r + (rep_number * 2)] = s50;
                    s50m = s50 - 50;
                    //qc_val[r + (5 * rep_number)] = s50m;
                    qc_val[r + (rep_number * 2)] = s50m;

                    if (!bdo && fabs(s50m) < 10 && fabs(s70m) < 10 && fabs(s90m) < 10) {
                        bdo = true;
                    }
                }*/

                //if (bdo) {
                //    bin_count_10perc++;
                    fprintf(fp_out, "%s\t%ld\t%ld\t%d\t", current_chrm, start_pos_window, end_pos_window, v);
                    for (int r = 0; r < rep_number; r++) {
                        fprintf(fp_out, "%d\t", current_array_pos_s90[r][i]);
                    }
                    for (int r = 0; r < rep_number; r++) {
                        fprintf(fp_out, "%d\t", current_array_pos_s70[r][i]);
                    }
                    for (int r = 0; r < rep_number - 1; r++) {
                        fprintf(fp_out, "%d\t", current_array_pos_s50[r][i]);
                    }
                    fprintf(fp_out, "%d\n", current_array_pos_s50[rep_number - 1][i]);
                 //   for (int j = 0; j < qc_array_size - 1; j++) {
                 //       fprintf(fp_out, "%.4f\t", qc_val[j]);
                 //   }
                 //   fprintf(fp_out, "%.4f\n", qc_val[qc_array_size - 1]);
                //}
            }
        }
    }

    //free ressources
    if (current_array_pos_s100 != NULL) {
        free(current_array_pos_s100);
        for (int r = 0; r < rep_number; r++) {
            free(current_array_pos_s50[r]);
            free(current_array_pos_s70[r]);
            free(current_array_pos_s90[r]);
        }
    }
    destroy_rep_array_ba();
    //destroy_chrm_entry_hash();


    if (bin_count_bgs == 0) {
        fprintf(stderr, "Error: empty sam table.\n");
        exit(1);
    }

    fprintf(stderr, "%d %d\n", bin_count, bin_count_bgs);

    return;
}


