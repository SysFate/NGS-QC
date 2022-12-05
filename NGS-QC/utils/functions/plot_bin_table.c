#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bin_table.h"
#include "../lib/str_tools.h"

extern struct s_bin_table* bt;

void plot_bin_table(FILE* fp_in,
                    unsigned char both_mode,
                    unsigned int threshold,
                    char* output_dir,
                    char* gnuplot_path,
                    unsigned char memory) {
    int k;

    char green_line_string[1024] = "";
    char script_file_name[4096] = "";
    char data_file_name[4096] = "";
    char output_img[4096]  = "";

    char s90[32];
    char s70[32];
    char s50[32];
    double log2_v100;
    char log2_v100_string[32];
    char key_s90[64] = "";
    char key_s70[64] = "";
    char key_s50[64] = "";

    float max_v100 = 0.0f;
    float pc5_max_v100 = 0.0f;

    char gnuplot_cmd[4096];
    char dispersion_plot[64] = "dispersion_s50_s70_s90";
    char pc_dispersion_plot[64] = "pc_s50_s70_s90";

    int loop_nbr = 1;
    int status = 0; // remove files status
    int threshold_bkp = threshold;

    sprintf(script_file_name, "%s/plot_script.gpl", output_dir);
    sprintf(data_file_name, "%s/plot.dat", output_dir);

    if (!memory) {
        read_bin_table(fp_in);
    }

    if (bt->size == 0) {
        fprintf(stderr, "Warning: the bin table is empty, abord plot.\n");
        exit(1);
    }

    //complete the big table
    table_row* rows = bt->head;
    while(rows != NULL) {
        rows->s90 = ((float)(100 * rows->v90)/rows->v100);
        rows->s70 = ((float)(100 * rows->v70)/rows->v100);
        rows->s50 = ((float)(100 * rows->v50)/rows->v100);
        rows = rows->next;
    }

    //write the plot file
    FILE* fp = fopen(data_file_name, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot create the plot data file.\n");
        destroy_coor_hash();
        destroy_bin_table();
        exit(1);
    }

    //fill all key for S90 for RCI plot
    rows = bt->head;
    while(rows != NULL) {
        rows->s90m = -(rows->s90 - 90);
        snprintf(s90, 32, "%f", rows->s90m);
        remove_trailing_zero(s90);
        log2_v100 = log2(rows->v100);
        if (log2_v100 > max_v100) {
            max_v100 = log2_v100;
        }
        snprintf(log2_v100_string, 32, "%f", log2_v100);
        strcat(key_s90, log2_v100_string);
        strcat(key_s90, s90);
        if (lookup(key_s90) == NULL) {
            if (put(key_s90) == NULL) {
                fprintf(stderr, "Error: cannot use hashtable.\n");
                destroy_coor_hash();
                destroy_bin_table();
                exit(1);
            }
        } else {
            rows->s90m = -1.0;
        }
        *key_s90 = '\0';
        rows = rows->next;
    }

    //fill all key for S70 for RCI plot
    rows = bt->head;
    while(rows != NULL) {
        rows->s70m = -(rows->s70 - 70);
        snprintf(s70, 32, "%f", rows->s70m);
        remove_trailing_zero(s70);
        log2_v100 = log2(rows->v100);
        snprintf(log2_v100_string, 32, "%f", log2_v100);
        strcat(key_s70, log2_v100_string);
        strcat(key_s70, s70);
        if (lookup(key_s70) == NULL) {
            if (put(key_s70) == NULL) {
                fprintf(stderr, "Error: cannot use hashtable.\n");
                destroy_coor_hash();
                destroy_bin_table();
                exit(1);
            }
        } else {
            rows->s70m = -1.0;
        }
        *key_s70 = '\0';
        rows = rows->next;
    }

    //fill all key for S50 for RCI plot
    rows = bt->head;
    while(rows != NULL) {
        rows->s50m = -(rows->s50 - 50);
        snprintf(s50, 32, "%f", rows->s50m);
        remove_trailing_zero(s50);
        log2_v100 = log2(rows->v100);
        snprintf(log2_v100_string, 32, "%f", log2_v100);
        strcat(key_s50, log2_v100_string);
        strcat(key_s50, s50);
        if (lookup(key_s50) == NULL) {
            if (put(key_s50) == NULL) {
                fprintf(stderr, "Error: cannot use hashtable.\n");
                destroy_coor_hash();
                destroy_bin_table();
                exit(1);
            }
        } else {
            rows->s50m = -1.0;
        }
        *key_s50 = '\0';
        rows = rows->next;
    }

    //write RCI plot
    rows = bt->head;
    while(rows != NULL) {
        log2_v100 = log2(rows->v100);
        if (rows->s90m == -1.0) {
            sprintf(s90, "?");
        } else {
            snprintf(s90, 32, "%f", rows->s90m);
            remove_trailing_zero(s90);
        }
        if (rows->s70m == -1.0) {
            sprintf(s70, "?");
        } else {
            snprintf(s70, 32, "%f", rows->s70m);
            remove_trailing_zero(s70);
        }
        if (rows->s50m == -1.0) {
            sprintf(s50, "?");
        } else {
            snprintf(s50, 32, "%f", rows->s50m);
            remove_trailing_zero(s50);
        }
        fprintf(fp, "%g\t%s\t%s\t%s\n", log2_v100, s90, s70, s50);
        rows = rows->next;
    }

    pc5_max_v100 = (5 * max_v100) / 100.0;
    max_v100 = max_v100 + pc5_max_v100;

    fclose(fp);


    //loop for both_mode
    if (both_mode) {
        loop_nbr = 2;
    }

    for (k = 0; k < loop_nbr; k++) {

        if (k == 1) {
            threshold = 0;
        }

        if (threshold == 0) {
            sprintf(output_img, "%s/%s_no_bgs.png", output_dir, dispersion_plot);
            strcpy(green_line_string, "");
        } else {
            sprintf(output_img, "%s/%s_bgs.png", output_dir, dispersion_plot);
            sprintf(green_line_string, "set arrow from %f,-54 to %f,54 nohead lc rgb \"#4D924D\" lw 5;\n", log2(threshold), log2(threshold));
        }


        fp = fopen(script_file_name, "w");
        if (fp == NULL) {
            fprintf(stderr, "Error: cannot create the plot script file.\n");
            destroy_coor_hash();
            destroy_bin_table();
            exit(1);
        }

        fprintf(fp, "set terminal png size 480, 480;\n\
set output \"%s\";\n\
unset key;\n\
set tmargin 3;\n\
set bmargin 4;\n\
set rmargin -2;\n\
set xtics font \", 7\";\n\
set ytics font \", 7\";\n\
set ytics rotate;\n\
set tics nomirror out;\n\
set xtics offset 0,graph 0.02;\n\
set ytics offset graph 0.05,0;\n\
set yrange [-55:55];\n\
set xrange [-%f:%f];\n\
%s\
plot '%s' using 1:4 pt 7 ps 0.8 lc rgb \"red\", '' using 1:3 pt 7 ps 0.8 lc rgb \"blue\", '' using 1:2 pt 7 ps 0.8 lc rgb \"black\"",
output_img, pc5_max_v100, max_v100, green_line_string, data_file_name);

        fclose(fp);

        sprintf(gnuplot_cmd, "%s %s", gnuplot_path, script_file_name);
        fp = popen(gnuplot_cmd, "r");
        if (fp == NULL) {
            fprintf(stderr, "Error: unable to run GNUplot command.\n" );
            destroy_coor_hash();
            destroy_bin_table();
            exit(1);
        }

        int retCode = pclose(fp);
        if (retCode != 0) {
            fprintf(stderr, "Error: gnuplot returned no success status.\n" );
            destroy_coor_hash();
            destroy_bin_table();
            exit(1);
        }

        //status = remove(script_file_name);
        /* if (status != 0) {
            fprintf(stderr, "Error: unable to remove the script plot file.\n" );
            exit(1);
        } */
    }

    //remove the data file
    //status = remove(data_file_name);
    /* if (status != 0) {
        fprintf(stderr, "Error: unable to remove the script data file.\n" );
        exit(1);
    } */

    //clear the hastable
    destroy_coor_hash();

    //fill all key for S90
    rows = bt->head;
    while(rows != NULL) {
        snprintf(s90, 32, "%f", rows->s90);
        remove_trailing_zero(s90);
        log2_v100 = log2(rows->v100);
        snprintf(log2_v100_string, 32, "%f", log2_v100);
        strcat(key_s90, log2_v100_string);
        strcat(key_s90, s90);
        if (lookup(key_s90) == NULL) {
            if (put(key_s90) == NULL) {
                fprintf(stderr, "Error: cannot use hashtable.\n");
                destroy_coor_hash();
                destroy_bin_table();
                exit(1);
            }
        } else {
            rows->s90 = -1.0;
        }
        *key_s90 = '\0';
        rows = rows->next;
    }

    //fill all key for S70
    rows = bt->head;
    while(rows != NULL) {
        snprintf(s70, 32, "%f", rows->s70);
        remove_trailing_zero(s70);
        log2_v100 = log2(rows->v100);
        snprintf(log2_v100_string, 32, "%f", log2_v100);
        strcat(key_s70, log2_v100_string);
        strcat(key_s70, s70);

        if (lookup(key_s70) == NULL) {
            if (put(key_s70) == NULL) {
                fprintf(stderr, "Error: cannot use hashtable.\n");
                destroy_coor_hash();
                destroy_bin_table();
                exit(1);
            }
        } else {
            rows->s70 = -1.0;
        }
        *key_s70 = '\0';
        rows = rows->next;
    }


    //fill all key for S50
    rows = bt->head;
    while(rows != NULL) {
        snprintf(s50, 32, "%f", rows->s50);
        remove_trailing_zero(s50);
        log2_v100 = log2(rows->v100);
        snprintf(log2_v100_string, 32, "%f", log2_v100);
        strcat(key_s50, log2_v100_string);
        strcat(key_s50, s50);

        if (lookup(key_s50) == NULL) {
            if (put(key_s50) == NULL) {
                fprintf(stderr, "Error: cannot use hashtable.\n");
                destroy_coor_hash();
                destroy_bin_table();
                exit(1);
            }
        } else {
            rows->s50 = -1.0;
        }
        *key_s50 = '\0';
        rows = rows->next;
    }

    //write the second plot file
    fp = fopen(data_file_name, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot create the plot data file.\n");
        destroy_coor_hash();
        destroy_bin_table();
        exit(1);
    }

    rows = bt->head;
    while(rows != NULL) {
        if (rows->s90 == -1.0) {
            sprintf(s90, "?");
        } else {
            snprintf(s90, 32, "%f", rows->s90);
            remove_trailing_zero(s90);
        }
        if (rows->s70 == -1.0) {
            sprintf(s70, "?");
        } else {
            snprintf(s70, 32, "%f", rows->s70);
            remove_trailing_zero(s70);
        }
        if (rows->s50 == -1.0) {
            sprintf(s50, "?");
        } else {
            snprintf(s50, 32, "%f", rows->s50);
            remove_trailing_zero(s50);
        }
        fprintf(fp, "%g\t%s\t%s\t%s\n", log2(rows->v100), s90, s70, s50);
        rows = rows->next;
    }
    fclose(fp);


    if (both_mode) {
        threshold = threshold_bkp;
    }

    for (k = 0; k < loop_nbr; k++) {

        if (k == 1) {
            threshold = 0;
        }

        if (threshold == 0) {
            sprintf(output_img, "%s/%s_no_bgs.png", output_dir, pc_dispersion_plot);
            strcpy(green_line_string, "");
        } else {
            sprintf(output_img, "%s/%s_bgs.png", output_dir, pc_dispersion_plot);
            sprintf(green_line_string, "set arrow from %f,-4 to %f,104 nohead lc rgb \"#4D924D\" lw 5;\n", log2(threshold), log2(threshold));
        }

        fp = fopen(script_file_name, "w");
        if (fp == NULL) {
            fprintf(stderr, "Error: cannot create the plot script file.\n");
            destroy_coor_hash();
            destroy_bin_table();
            exit(1);
        }

        fprintf(fp, "set terminal png size 480, 480;\n\
set output \"%s\";\n\
set size square;\n\
set rmargin 0;\n\
set tmargin 0;\n\
#set lmargin 5;\n\
#set bmargin 4;\n\
set key inside right bottom samplen 1;\n\
set xlabel \"Read count (log2)\" offset 0, 1;\n\
set ylabel \"recRCI (%%)\"  offset 3, 0;\n\
set xtics font \", 7\";\n\
set ytics font \", 7\";\n\
set ytics rotate;\n\
set tics nomirror out;\n\
set xtics offset 0,graph 0.02;\n\
set ytics offset graph 0.05,0;\n\
set yrange [-5:105];\n\
set xrange [-%f:%f];\n\
%s\
plot 1/0 ls 13 lw 3 lc rgb \"red\" with points t \"S50\", 1/0 ls 13 lw 3 lc rgb \"blue\" with points t \"S70\", 1/0 ls 13 lw 3 lc rgb \"black\" with points t \"S90\", '%s' using 1:4 pt 7 ps 0.6 lc rgb \"red\" notitle, '' using 1:3 pt 7 ps 0.6 lc rgb \"blue\" notitle, '' using 1:2 pt 7 ps 0.6 lc rgb \"black\" notitle;",
output_img, pc5_max_v100, max_v100, green_line_string, data_file_name);

        fclose(fp);

        sprintf(gnuplot_cmd, "%s %s", gnuplot_path, script_file_name);
        fp = popen(gnuplot_cmd, "r");
        if (fp == NULL) {
            fprintf(stderr, "Error: unable to run GNUplot command.\n" );
            destroy_coor_hash();
            destroy_bin_table();
            exit(1);
        }

        int retCode = pclose(fp);
        if (retCode != 0) {
            fprintf(stderr, "Error: gnuplot returned no success status.\n" );
            destroy_coor_hash();
            destroy_bin_table();
            exit(1);
        }


        status = remove(script_file_name);
        if (status != 0) {
            fprintf(stderr, "Error: unable to remove the script plot file.\n" );
            destroy_coor_hash();
            destroy_bin_table();
            exit(1);
        }
    }

    //remove the data file
    status = remove(data_file_name);
    if (status != 0) {
        fprintf(stderr, "Error: unable to remove the script data file.\n" );
        destroy_coor_hash();
        destroy_bin_table();
        exit(1);
    }

    return;
}

