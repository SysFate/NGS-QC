#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bin_table.h"
#include "../lib/str_tools.h"

#define true 1
#define false 0

extern struct s_bin_table* bt;

void compute_indicators(FILE* fp_in,
                        FILE* fp_out,
                        unsigned int threshold,
                        char* samtable,
                        char* bedtrack,
                        char* wigtrack,
                        unsigned char memory) {

    if (!memory) {
        char line[1024];

        char* ptr;
        char* ptrend;
        int lenptr;

        long start_pos;
        long end_pos;
        unsigned int s100;
        unsigned int s90;
        unsigned int s70;
        unsigned int s50;

        char chrname[128] = "";
        char token[128] = "";

        struct s_table_row* row_tmp;

        //create the big table in memory
        bt = malloc(sizeof(struct s_bin_table));
        bt->size = 0;

        while(fgets(line, 1024, fp_in) != NULL) {
            if (line[0] == '\n' || line[1] == '\n') {
                continue;
            }

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
            start_pos = atol(token);
            if (start_pos < 0) {
                start_pos = 0;
            }
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            end_pos = atol(token);

            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            s100 = atol(token);

            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            s90 = atol(token);

            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            s70 = atol(token);

            ptr = ptrend+1;

            ptrend = strchr(ptr, '\n');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            s50 = atol(token);

            //add elem to the bin table
            row_tmp = bt->rows;
            bt->rows = add_bin_table_row(row_tmp,
                                         strdup(chrname),
                                         start_pos,
                                         end_pos,
                                         s100,
                                         s90,
                                         s70,
                                         s50);

            if (bt->size == 0) {
                bt->head = bt->rows;
            }
            bt->size++;
        }
    }

    unsigned char write_bed_track = 0;
    unsigned char write_sam_table = 0;
    unsigned char write_wig_track = 0;

    FILE* fp_samtable = NULL;
    FILE* fp_bedtrack = NULL;
    FILE* fp_wigtrack = NULL;

    if (strlen(samtable) != 0) {
        fp_samtable = fopen(samtable, "w");
        if (fp_samtable == NULL) {
            fprintf(stderr, "Error: cannot create the samtable file.\n\n");
            destroy_bin_table();
            exit(1);
        }
        write_sam_table = 1;
    }

    if (strlen(bedtrack) != 0) {
        fp_bedtrack = fopen(bedtrack, "w");
        if (fp_bedtrack == NULL) {
            fprintf(stderr, "Error: cannot create the bedtrack file.\n\n");
            destroy_bin_table();
            exit(1);
        }
        write_bed_track = 1;
        fprintf(fp_bedtrack, "track name=localQC_indicators description=\"local QC indicators\" visibility=2 itemRgb=\"On\"\n");
    }

    if (strlen(wigtrack)) {
        write_wig_track = 1;
    }

    int bin_wo_bgs = 0;

    int nb_row_S90_2 = 0;
    int nb_row_S90_5 = 0;
    int nb_row_S90_10 = 0;
    
    int nb_row_all_2 = 0;
    int nb_row_all_5 = 0;
    int nb_row_all_10 = 0;

    float ratio_S90_vs_total_2 = 0;
    float ratio_S90_vs_total_5 = 0;
    float ratio_S90_vs_total_10 = 0;

    float ratio_all_vs_total_2 = 0;
    float ratio_all_vs_total_5 = 0;
    float ratio_all_vs_total_10 = 0;

    //float ratio_2 = 0;
    //float ratio_5 = 0;
    //float ratio_10 = 0;

    table_row* rows = bt->head;
    char* curr_chrm = NULL;
    char wig_file[4096] = "";

    if (bt->size == 0) {
        fprintf(stderr, "Error: bin table empty, cannot compute indicators.\n\n");
        destroy_bin_table();
        exit(1);
    }

    while(rows != NULL) {

        rows->s90 = ((float)(100 * rows->v90)/rows->v100);
        rows->s70 = ((float)(100 * rows->v70)/rows->v100);
        rows->s50 = ((float)(100 * rows->v50)/rows->v100);
        rows->s90m = 90 - rows->s90;
        rows->s70m = 70 - rows->s70;
        rows->s50m = 50 - rows->s50;

        if (rows->v100 >= threshold) {
            bin_wo_bgs += 1;
            if (fabsf(rows->s50m) < 10 && fabsf(rows->s70m) < 10 && fabsf(rows->s90m) < 10) {
                nb_row_all_10++;
                if (write_sam_table) {
                    fprintf(fp_samtable, "%s\t%ld\t%ld\t%d\t%d\t%d\t%d\t%f\t%f\t%f\n", rows->chr, rows->start, 
                            rows->end, rows->v100, rows->v90, rows->v70, rows->v50, rows->s90m, rows->s70m, rows->s50m);
                }
                if (write_bed_track) {
                    fprintf(fp_bedtrack, "%s\t%ld\t%ld\t.\t%f\t.\t0\t0\t%d,0,0\n", rows->chr, rows->start, 
                            rows->end, rows->s50m, (int)(25.5*(10-fabsf(rows->s50m))));
                }
                if (write_wig_track) {
                    if (curr_chrm == NULL || strcmp(curr_chrm, rows->chr) != 0) {
                        if (curr_chrm != NULL) {
                            fclose(fp_wigtrack);
                        }
                        sprintf(wig_file, "%s/%s_s50_10pc.wig", wigtrack, rows->chr);
                        fp_wigtrack = fopen(wig_file, "w");
                        if (fp_bedtrack == NULL) {
                            fprintf(stderr, "Error: cannot create the bedtrack file.\n\n");
                            destroy_bin_table();
                            exit(1);
                        }
                        fprintf(fp_wigtrack, "track type=wiggle_0 name=\"local_QC_indicators\" \
description=\"local QC indicators\"\nvariableStep chrom=%s\n", rows->chr);
                        
                    }
                    fprintf(fp_wigtrack, "%ld\t%f\n", (rows->start + 1), 10-fabsf(rows->s50m));
                    curr_chrm = rows->chr;
                }
                if (fabsf(rows->s50m) < 5 && fabsf(rows->s70m) < 5 && fabsf(rows->s90m) < 5) {
                    nb_row_all_5++;
                    if (fabsf(rows->s50m) < 2.5 && fabsf(rows->s70m) < 2.5 && fabsf(rows->s90m) < 2.5) {
                        nb_row_all_2++;
                    }
                }
            }
            if (fabsf(rows->s90m) < 10) {
                nb_row_S90_10++;
                if (fabsf(rows->s90m) < 5) {
                    nb_row_S90_5++;
                    if (fabsf(rows->s90m) < 2.5) {
                        nb_row_S90_2++;
                    }
                }
            }
        }
        rows = rows->next;
    }

    if (write_sam_table) {
        fclose(fp_samtable);
    }
    if (write_bed_track) {
        fclose(fp_bedtrack);
    }
    if (write_wig_track) {
        fclose(fp_wigtrack);
    }



    ratio_S90_vs_total_2 = 100 * ((float)nb_row_S90_2/bt->size);
    ratio_S90_vs_total_5 = 100 * ((float)nb_row_S90_5/bt->size);
    ratio_S90_vs_total_10 = 100 * ((float)nb_row_S90_10/bt->size);

    ratio_all_vs_total_2 = 100 * ((float)nb_row_all_2/bt->size);
    ratio_all_vs_total_5 = 100 * ((float)nb_row_all_5/bt->size);
    ratio_all_vs_total_10 = 100 * ((float)nb_row_all_10/bt->size);


    fprintf(fp_out, "Bins\t%d\n", bt->size);
    fprintf(fp_out, "Threshold\t%d\n", threshold);
    fprintf(fp_out, "Bins w/o background\t%d\n", bin_wo_bgs);
    fprintf(fp_out, "DenQC_s90_2.5pc\t%f\n", ratio_S90_vs_total_2);
    fprintf(fp_out, "DenQC_s90_5pc\t%f\n", ratio_S90_vs_total_5);
    fprintf(fp_out, "DenQC_s90_10pc\t%f\n", ratio_S90_vs_total_10);
    fprintf(fp_out, "DenQC_s50_2.5pc\t%f\n", ratio_all_vs_total_2);
    fprintf(fp_out, "DenQC_s50_5pc\t%f\n", ratio_all_vs_total_5);
    fprintf(fp_out, "DenQC_s50_10pc\t%f\n", ratio_all_vs_total_10);


    if (ratio_all_vs_total_2 != 0) {
        fprintf(fp_out, "SimQC_2.5pc\t%f\n", ratio_S90_vs_total_2/ratio_all_vs_total_2);
    } else {
        fprintf(fp_out, "SimQC_2.5pc\tinf\n");
    }

    if (ratio_all_vs_total_5 != 0) {
        fprintf(fp_out, "SimQC_5pc\t%f\n", ratio_S90_vs_total_5/ratio_all_vs_total_5);
    } else {
        fprintf(fp_out, "SimQC_5pc\tinf\n");
    }

    if (ratio_all_vs_total_10 != 0) {
        fprintf(fp_out, "SimQC_10pc\t%f\n", ratio_S90_vs_total_10/ratio_all_vs_total_10);
    } else {
        fprintf(fp_out, "SimQC_10pc\tinf\n");
    }

    return;
}


void compute_indicators_replicate(FILE* fp_in,
                        FILE* fp_out,
                        unsigned int threshold,
                        unsigned char rep_number,
                        unsigned char valid_rep) {


    char line[1024];

    char* ptr;
    char* ptrend;
    int lenptr;

    //long start_pos;
    //long end_pos;
    unsigned int tot_bin = 0;
    unsigned int s100;

    float s90ma;
    float s70ma;
    float s50ma;

    //float s90ma[rep_number];
    //float s70ma[rep_number];
    //float s50ma[rep_number];

    char chrname[128] = "";
    char token[128] = "";

    unsigned int bin_wo_bgs = 0;

    unsigned int nb_row_S90_2 = 0;
    unsigned int nb_row_S90_5 = 0;
    unsigned int nb_row_S90_10 = 0;
    unsigned int nb_row_S90_15 = 0;

    unsigned int nb_row_all_2 = 0;
    unsigned int nb_row_all_5 = 0;
    unsigned int nb_row_all_10 = 0;
    unsigned int nb_row_all_15 = 0;

    float ratio_S90_vs_total_2 = 0;
    float ratio_S90_vs_total_5 = 0;
    float ratio_S90_vs_total_10 = 0;
    float ratio_S90_vs_total_15 = 0;

    float ratio_all_vs_total_2 = 0;
    float ratio_all_vs_total_5 = 0;
    float ratio_all_vs_total_10 = 0;
    float ratio_all_vs_total_15 = 0;

    unsigned char cur_valid_disp_15 = 0;
    unsigned char cur_valid_disp_10 = 0;
    unsigned char cur_valid_disp_5 = 0;
    unsigned char cur_valid_disp_2 = 0;

    unsigned char valid_disp_s90_10 = false;
    unsigned char valid_disp_s90_5 = false;
    unsigned char valid_disp_s90_2 = false;

    unsigned char valid_disp_s70_10 = false;
    unsigned char valid_disp_s70_5 = false;
    unsigned char valid_disp_s70_2 = false;

    while(fgets(line, 1024, fp_in) != NULL) {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        }

        ptr = line;
        ptrend = strchr(ptr, '\t');
        lenptr = ptrend-ptr;
        strncpy(chrname, ptr, lenptr);
        chrname[lenptr] = '\0';

        ptr = ptrend+1;

        ptrend = strchr(ptr, '\t');
        //lenptr = ptrend-ptr;
        //strncpy(token, ptr, lenptr);
        //token[lenptr] = '\0';
        //start_pos = atol(token);
        //if (start_pos < 0) {
        //    start_pos = 0;
        //}
        ptr = ptrend+1;

        ptrend = strchr(ptr, '\t');
        //lenptr = ptrend-ptr;
        //strncpy(token, ptr, lenptr);
        //token[lenptr] = '\0';
        //end_pos = atol(token);

        ptr = ptrend+1;

        ptrend = strchr(ptr, '\t');
        lenptr = ptrend-ptr;
        strncpy(token, ptr, lenptr);
        token[lenptr] = '\0';
        s100 = atol(token);

        tot_bin++;

        if (s100 < threshold) {
            continue;
        }

        bin_wo_bgs++;

        valid_disp_s90_10 = false;
        valid_disp_s90_5 = false;
        valid_disp_s90_2 = false;

        valid_disp_s70_10 = false;
        valid_disp_s70_5 = false;
        valid_disp_s70_2 = false;

        cur_valid_disp_15 = 0;
        cur_valid_disp_10 = 0;
        cur_valid_disp_5 = 0;
        cur_valid_disp_2 = 0;
        for (int i = 0; i < rep_number; i++) {
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            s90ma = fabsf(90 - ((float)(100 * atol(token))/s100));
            if (s90ma < 15) {
                cur_valid_disp_15++;
                if (s90ma < 10) {
                    cur_valid_disp_10++;
                    if (s90ma < 5) {
                        cur_valid_disp_5++;
                        if (s90ma < 2.5) {
                            cur_valid_disp_2++;
                        }
                    }
                }
            }
        }

        if (cur_valid_disp_15 < valid_rep) {
            continue;
        }
        nb_row_S90_15++;
        if (cur_valid_disp_10 >= valid_rep) {
            nb_row_S90_10++;
            valid_disp_s90_10 = true;
            if (cur_valid_disp_5 >= valid_rep) {
                nb_row_S90_5++;
                valid_disp_s90_5 = true;
                if (cur_valid_disp_2 >= valid_rep) {
                    nb_row_S90_2++;
                    valid_disp_s90_2 = true;
                }
            }
        }

        cur_valid_disp_15 = 0;
        cur_valid_disp_10 = 0;
        cur_valid_disp_5 = 0;
        cur_valid_disp_2 = 0;
        for (int i = 0; i < rep_number; i++) {
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            s70ma = fabsf(70 - ((float)(100 * atol(token))/s100));
            if (s70ma < 15) {
                cur_valid_disp_15++;
                if (s70ma < 10) {
                    cur_valid_disp_10++;
                    if (s70ma < 5) {
                        cur_valid_disp_5++;
                        if (s70ma < 2.5) {
                            cur_valid_disp_2++;
                        }
                    }
                }
            }
        }

        if (cur_valid_disp_15 < valid_rep) {
            continue;
        }
        if (cur_valid_disp_10 >= valid_rep) {
            valid_disp_s70_10 = true;
            if (cur_valid_disp_5 >= valid_rep) {
                valid_disp_s70_5 = true;
                if (cur_valid_disp_2 >= valid_rep) {
                    valid_disp_s70_2 = true;
                }
            }
        }

        cur_valid_disp_15 = 0;
        cur_valid_disp_10 = 0;
        cur_valid_disp_5 = 0;
        cur_valid_disp_2 = 0;
        for (int i = 0; i < rep_number; i++) {
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            if (ptrend == NULL) {
                ptrend = strchr(ptr, '\n');
            }
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            s50ma = fabsf(50 - ((float)(100 * atol(token))/s100));
            if (s50ma < 15) {
                cur_valid_disp_15++;
                if (s50ma < 10) {
                    cur_valid_disp_10++;
                    if (s50ma < 5) {
                        cur_valid_disp_5++;
                        if (s50ma < 2.5) {
                            cur_valid_disp_2++;
                        }
                    }
                }
            }
        }

        if (cur_valid_disp_15 < valid_rep) {
            continue;
        }
        nb_row_all_15++;
        if (valid_disp_s70_10 && valid_disp_s90_10 && cur_valid_disp_10 >= valid_rep) {
            nb_row_all_10++;
            if (valid_disp_s70_5 && valid_disp_s90_5 && cur_valid_disp_5 >= valid_rep) {
                nb_row_all_5++;
                if (valid_disp_s70_2 && valid_disp_s90_2 && cur_valid_disp_2 >= valid_rep) {
                    nb_row_all_2++;
                }
            }
        }

    }

    ratio_S90_vs_total_2 = 100 * ((float)nb_row_S90_2/tot_bin);
    ratio_S90_vs_total_5 = 100 * ((float)nb_row_S90_5/tot_bin);
    ratio_S90_vs_total_10 = 100 * ((float)nb_row_S90_10/tot_bin);
    ratio_S90_vs_total_15 = 100 * ((float)nb_row_S90_15/tot_bin);

    ratio_all_vs_total_2 = 100 * ((float)nb_row_all_2/tot_bin);
    ratio_all_vs_total_5 = 100 * ((float)nb_row_all_5/tot_bin);
    ratio_all_vs_total_10 = 100 * ((float)nb_row_all_10/tot_bin);
    ratio_all_vs_total_15 = 100 * ((float)nb_row_all_15/tot_bin);


    fprintf(fp_out, "Bins\t%d\n", tot_bin);
    fprintf(fp_out, "Threshold\t%d\n", threshold);
    fprintf(fp_out, "Replicate number\t%d\n", rep_number);
    fprintf(fp_out, "Valid disp\t%d\n", valid_rep);
    fprintf(fp_out, "Bins w/o background\t%d\n", bin_wo_bgs);
    fprintf(fp_out, "Bins_s90_2.5pc\t%d\n", nb_row_S90_2);
    fprintf(fp_out, "Bins_s90_5pc\t%d\n", nb_row_S90_5);
    fprintf(fp_out, "Bins_s90_10pc\t%d\n", nb_row_S90_10);
    fprintf(fp_out, "Bins_s90_15pc\t%d\n", nb_row_S90_15);
    fprintf(fp_out, "Bins_s50_2.5pc\t%d\n", nb_row_all_2);
    fprintf(fp_out, "Bins_s50_5pc\t%d\n", nb_row_all_5);
    fprintf(fp_out, "Bins_s50_10pc\t%d\n", nb_row_all_10);
    fprintf(fp_out, "Bins_s50_15pc\t%d\n", nb_row_all_15);
    fprintf(fp_out, "DenQC_s90_2.5pc\t%f\n", ratio_S90_vs_total_2);
    fprintf(fp_out, "DenQC_s90_5pc\t%f\n", ratio_S90_vs_total_5);
    fprintf(fp_out, "DenQC_s90_10pc\t%f\n", ratio_S90_vs_total_10);
    fprintf(fp_out, "DenQC_s90_15pc\t%f\n", ratio_S90_vs_total_15);
    fprintf(fp_out, "DenQC_s50_2.5pc\t%f\n", ratio_all_vs_total_2);
    fprintf(fp_out, "DenQC_s50_5pc\t%f\n", ratio_all_vs_total_5);
    fprintf(fp_out, "DenQC_s50_10pc\t%f\n", ratio_all_vs_total_10);
    fprintf(fp_out, "DenQC_s50_15pc\t%f\n", ratio_all_vs_total_15);


    if (ratio_all_vs_total_2 != 0) {
        fprintf(fp_out, "SimQC_2.5pc\t%f\n", ratio_S90_vs_total_2/ratio_all_vs_total_2);
    } else {
        fprintf(fp_out, "SimQC_2.5pc\tinf\n");
    }

    if (ratio_all_vs_total_5 != 0) {
        fprintf(fp_out, "SimQC_5pc\t%f\n", ratio_S90_vs_total_5/ratio_all_vs_total_5);
    } else {
        fprintf(fp_out, "SimQC_5pc\tinf\n");
    }

    if (ratio_all_vs_total_10 != 0) {
        fprintf(fp_out, "SimQC_10pc\t%f\n", ratio_S90_vs_total_10/ratio_all_vs_total_10);
    } else {
        fprintf(fp_out, "SimQC_10pc\tinf\n");
    }

    if (ratio_all_vs_total_15 != 0) {
        fprintf(fp_out, "SimQC_15pc\t%f\n", ratio_S90_vs_total_15/ratio_all_vs_total_15);
    } else {
        fprintf(fp_out, "SimQC_15pc\tinf\n");
    }

    return;
}



