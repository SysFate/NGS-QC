#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

#include "lib/genome.h"
#include "lib/str_tools.h"
#include "lib/bit_array.h"

#include "functions/integrity.h"
#include "functions/issorted.h"
#include "functions/unique.h"
#include "functions/pileup.h"
#include "functions/rewrite.h"
#include "functions/wig.h"
#include "functions/bin_table.h"
#include "functions/bin_table_rep.h"
#include "functions/sort.h"
#include "functions/elong_read.h"
#include "functions/local_bg.h"
#include "functions/plot_bin_table.h"
#include "functions/globalQC.h"


#define true 1
#define false 0

// Last change: 11-10-2014
// gcc -Wall -Wextra -posix -Werror -std=c99 -D_POSIX_C_SOURCE=2001  NGSQC_bed_utils.c lib/str_tools.c lib/genome.c lib/bit_array.c lib/median.c functions/integrity.c functions/issorted.c functions/rewrite.c functions/unique.c functions/wig.c functions/sort.c functions/pileup.c functions/bin_table.c functions/bin_table_rep.c functions/elong_read.c functions/local_bg.c functions/plot_bin_table.c functions/globalQC.c -lpthread -o NGSQC_bed_utils_test -lm
// valgrind -v --tool=memcheck --leak-check=full ./bed_utils.out tiny.bed

const char version[32] = "0.44";
const int sampling_array[3] = {50,70,90};


void print_usage() {
    fprintf(stdout, "ngsqc_bed_utils: a set of tools for BED files.\n\n\
Version: %s\n\n\
usage: bed_utils [bin_table|bin_table_rep|elong_read|integrity|pileup|plot_bin_table|rewrite|issorted|sort|unique|wig]\
 bed_file [ARGUMENT] [OPTION]\n\n", version);
    fprintf(stdout, "Tasks:\n\n\
\tbin_table:\t\tcompute the bin table for 3 samplings values\n\
\t\t\t\t(90%%, 70%%, 50%%).\n\
\tbin_table_rep:\t\tcompute the bin table for 3 samplings values\n\
\t\t\t\t(90%%, 70%%, 50%%) and for n replicate.\n\
\tcount_reads:\t\tCount the number of read of FILE (BED format).\n\
\telong_read:\t\tElong reads of the BED file keeping the sorting\n\
\t\t\t\torder is preserved.\n\
\tglobalQC:\t\tCompute global indicators from a bin table file.\n\
\tglobalQCrep:\t\tCompute global indicators from a rep bin table file.\n\
\tintegrity:\t\tchecks is the bed file is well formatted for the\n\
\t\t\t\tNGSQC (at least 6 columns).\n\
\tlocal_bg:\t\tcompute local_bg pattern.\n\
\tpileup:\t\t\tcompute the read count found in the genome chop up\n\
\t\t\t\twith a specifiy window size.\n\
\tplot_bin_table:\t\tPlot bin 50%% 70%% 90%% dispersion.\n\
\trewrite:\t\treformat the BED file on the stdout depending on the\n\
\t\t\t\terror code returned by \"integrity\".\n\
\tsort:\t\t\tsort the BED file on the stdout.\n\
\tissorted:\t\ttests if the BED file is sorted based on the chrm,\n\
\t\t\t\tstart and strand columns.\n\
\tunique:\t\t\treturns the number of unique reads or displays the\n\
\t\t\t\tunique reads.\n\
\twig:\t\t\tConvert the BED file to WIG file.\n\n\
type [TASK] -h for more detailed help.\n\n");
}


void print_help(char* type) {
    if (strcmp(type, "bin_table") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: bin_table\n\n\
usage: without --plot option:\n\nngsqc_bed_utils [bin_table] bed_file genome_file window_size\n\n\
usage: with --plot or --globalQC option:\n\nngsqc_bed_utils [bin_table] bed_file genome_file window_size bgs_threshold output_dir\n\n", stdout);

/*    fputs(stdout, "ARGUMENTS:\n\n\
bed_file:\n\tthe input BED file path.\n\tUse the keyword 'stdin' to read standard input.\n\n\
genome_file:\n\tmust contains the size of the chromosomes.\n\tThe expected format is:\n\
\t\tchr1\t249250621\n\t\tchr10\t135534747\n\t\tchr11\t135006516\n\t\t...\n\
\n\tthe TAB charactere must be used as separator.\n\
\tREMARK: the chromosomes present in the BED file\n\tbut missing in the genome file will be ignored\n\tduring the process.\n\n\
window_size:\n\tthe size of the window scanning the genome.\n\tUse 500 for the NGSQC generator.\n\n\
bgs_threshold:\n\tthe computed background subtraction threshold.\n\tA positive integer is expected.\n\n", stdout);*/

        fputs("OPTIONS:\n\n\
\t--bed-track\tuse with option --globalQC.\n\t\t\twrite bed track to FILE\n\
\t--both-mode\tuse with option --plot.\n\t\t\tproduce two plot images (w and w/o bgs). Default is 'bgs'\n\
\t--chrm-dict\tuse specify chrm info instead of genome file\n\
\t--globalQC\t\tcompute globalQC indicators\n\
\t--gnuplot-path\tspecify the gnuplot line command\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\
\t--plot\t\tplot the bin dispersion (PNG)\n\
\t--read-count\tspecify the number of reads in the input BED\n\t\t\t\
if not used, the input file is readed before processing\n\
\t--sam-table\tuse with option --globalQC.\n\t\t\twrite sam table to FILE\n\
\t--wigs\t\tuse with option --globalQC.\n\t\t\twrite localQC wig formatted to DIRECTORY\n\n", stdout);

    } else if (strcmp(type, "bin_table_rep") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: bin_table_rep\n\n\
usage: ngsqc_bed_utils [bin_table_rep] bed_file genome_file window_size bgs_threshold replicate_nb\n\n", stdout);


        fputs("OPTIONS:\n\n\
\t--chrm-dict\tuse specify chrm info instead of genome file\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\
\t--read-count\tspecify the number of read in the input BED\n\t\t\t\
if not used, the input file is read before processing\n\n", stdout);


        fputs("DISPLAY (stderr):\n\n\
\tbin_count, bin_count_bgs, bin_count_10perc\n\n", stdout);

    } else if (strcmp(type, "count_read") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: count_read\n\n\
usage: ngsqc_bed_utils [count_read] bed_file\n\n", stdout);

    } else if (strcmp(type, "elong_read") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: elong_read\n\n\
usage: ngsqc_bed_utils [elong_read] bed_file extend_size\n\n", stdout);


        fputs("OPTIONS:\n\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\n", stdout);

    } else if (strcmp(type, "globalQC") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: globalQC\n\n\
usage: ngsqc_bed_utils [globalQC] bin_table threshold\n\n", stdout);


        fputs("OPTIONS:\n\n\
\t--bed-track\twrite bed track to FILE\n\
\t--sam-table\twrite sam table to FILE\n\
\t--wigs\t\twrite localQC wig formatted to DIRECTORY\n\
\t-o\t\twrite result to FILE instead of standard output\n\n", stdout);

    } else if (strcmp(type, "globalQCrep") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: globalQCrep\n\n\
usage: ngsqc_bed_utils [globalQCrep] bin_table threshold rep_number valid_rep\n\n", stdout);


        fputs("OPTIONS:\n\n\
\t-o\t\twrite result to FILE instead of standard output\n\n", stdout);

    } else if (strcmp(type, "integrity") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Tasks: integrity\n\n\
usage: ngsqc_bed_utils [integrity] bed_file\n\n", stdout);

    /*fprintf(stdout, "Check if the input BED file is formatted\nfollowing the UCSC specification:\n\
http://genome.ucsc.edu/FAQ/FAQformat.html#format1.\n\
The BED file must constains at least the first 6 columns:\n[chrname] [start coord]\
 [end coord] [tag name] [score] [strand].\nThe delimiter must be the TAB character.\n\n");*/

fputs("OPTIONS:\n\n\
\t--chrm-file\tuse genome file to get the real TMR count in the bed FILE\n\
\t--chrm-dict\tuse this genome dictionnary instead of the genome file\n\n", stdout);

        fputs("DISPLAY :\n\n\
\terror_code, read_count, real_read_count (when genome given), mean_reads_length, variable_read_size (0/1), \
min_read_length, max_read_length, header_reads, used_chrm, last_line_processed\n\n", stdout);

    } else if (strcmp(type, "local_bg") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: local_bg\n\n\
usage: ngsqc_bed_utils [local_bg] bed_file genome_file large_window_size window_size kthmax\n\n", stdout);

        fputs("OPTIONS:\n\n\
\t--chrm-dict\tuse specify genome chrm instead of genome file\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\n", stdout);

    } else if (strcmp(type, "pileup") == 0) {
        fprintf(stdout, "ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: pileup\n\n\
usage:\n\nngsqc_bed_utils [pileup] bed_file genome_file window_size extend_size\n\n");

    /*fprintf(stdout, "Extend and count the number of read per bin_size.\nalong the genome file.\n\n");

    fprintf(stdout, "ARGUMENTS:\n\n\
bed_file:\n\tthe input BED file path.\n\tUse the keyword 'stdin' to read standard input.\n\n\
genome_file:\n\tmust contains the size of the chromosomes.\n\tThe expected format is:\n\
\t\tchr1\t249250621\n\t\tchr10\t135534747\n\t\tchr11\t135006516\n\t\t...\n\
\n\tthe TAB charactere must be used as separator.\n\
\tREMARK: the chromosomes present in the BED file\n\tbut missing in the genome file will be ignored\n\tduring the process.\n\n\
window_size:\n\tthe size of the window scanning the genome.\n\n\
extend size:\n\telongate the read up to the specify size.\n\tA positive integer is expected.\n\n");*/

        fprintf(stdout, "OPTIONS:\n\n\
\t--chrm-dict\tuse specify genome chrm instead of genome file\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\
\t--zero-fill\tdo not remove windows with 0 reads\n\n");

    } else if (strcmp(type, "plot_bin_table") == 0) {
        fprintf(stdout, "ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: plot_bin_table\n\n\
usage:\n\nngsqc_bed_utils [plot_bin_table] bed_file threshold output_dir\n\n");

        fputs("OPTIONS:\n\n\
\t--both-mode\tproduce two plot images (w and w/o bgs). Default is 'bgs'\n\
\t--gnuplot-path\tspecify the gnuplot line command.\n\n", stdout);

    } else if (strcmp(type, "rewrite") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: local_bg\n\n\
usage: ngsqc_bed_utils [rewrite] bed_file error_code\n\n", stdout);

        fputs("OPTIONS:\n\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\n", stdout);

    } else if (strcmp(type, "sort") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: sort\n\n\
usage: ngsqc_bed_utils [sort] bed_file genome_file\n\n", stdout);

        fputs("OPTIONS:\n\n\
\t-c\t\tspecify the number of threads\n\
\t--chrm-dict\tuse specify genome chrm instead of genome file\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\n", stdout);

    } else if (strcmp(type, "issorted") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: issorted\n\n\
usage: ngsqc_bed_utils [issorted] bed_file\n\n", stdout);

        fputs("OPTIONS:\n\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\n", stdout);

        fputs("DISPLAY:\n\n\
\t'1' if the file is sorted, '0' instead\n\n", stdout);

    } else if (strcmp(type, "unique") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: unique\n\n\
usage: ngsqc_bed_utils [unique] bed_file\n\n", stdout);

        fputs("OPTIONS:\n\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\
\t--write\t\tenable write to FILE / standard output\n\n", stdout);

        fputs("DISPLAY (stderr):\n\n\
\t'reads_count unique_read_count header_reads_count used_chrm'\n\n", stdout);


    } else if (strcmp(type, "wig") == 0) {
        fputs("ngsqc_bed_utils: a set a tools for BED files.\n\n\
Task: wig\n\n\
usage: ngsqc_bed_utils [wig] bed_file genome_file window_size extend_size\n\n", stdout);

        fputs("OPTIONS:\n\n\
\t--chrm-dict\tuse specify genome chrm instead of genome file\n\
\t--no-header\tskip the search for BED header lines (run faster)\n\
\t-o\t\twrite result to FILE instead of standard output\n\n", stdout);

    } else {
        print_usage();
    }
}


void parse_argument(unsigned int uargc, char* argv[]) {
    unsigned int i = 0, j = 0;
    unsigned int choice = 0;

    char* input_file = NULL;
    char* output_file = NULL;
    char* genome_file = NULL;

    char* chrm_dict = NULL;
    char* chrm_region = NULL;

    FILE* fp_in = NULL;
    FILE* fp_out = NULL;
    FILE* fp_genome = NULL;

    extern int errno;

    unsigned int count_arg = 0;

    unsigned char no_header = false;
    unsigned char zero_fill = false;
    unsigned char write_file = false;
    unsigned char plot = false;
    unsigned char both_mode = false;
    unsigned char store_bin_table = false;
    unsigned char globalQC = false;
    unsigned char core_nb = 1;
    unsigned char get_tmru = false;


    unsigned int window_size = 0;
    unsigned int large_window_size = 0;
    unsigned int error_code = 0;
    unsigned int extend_size = 0;
    unsigned int threshold = 0;
    unsigned int rep_number = 0;
    unsigned int valid_rep = 0;
    unsigned long total_reads = 0;
    float kthminf = 0;
    char output_dir[4096] = "";
    char output_wigs[4096] = "";
    char sam_table[4096] = "";
    char bed_track[4096] = "";
    char gnuplot_path[4096] = "gnuplot";

    while (i < uargc) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help(argv[1]);
            exit(0);
        }
        i++;
    }

    if (uargc < 2) {
        print_usage();
        exit(1);
    }

    i = 1;

    if (strcmp(argv[i], "integrity") == 0) {
        choice = 0; /* 'integrity' - 1 argument | 1 options */
        /* argument: [bed file] */
        /*if (uargc != 3) { // max number of argument is 1
            fprintf(stderr, "Error: invalid number of argument.\n\n");
            exit(1);
        }
        if (strcmp(argv[2], "stdin") != 0) {
            input_file = strdup(argv[2]);
        }*/
    } else if (strcmp(argv[i], "issorted") == 0) {
        choice = 1; 
        /* 'issorted' - 1 argument | 1 options */
        /* argument: [bed file] 
           option:   [--no-header] */
    } else if (strcmp(argv[i], "pileup") == 0) {
        choice = 2; 
        /* 'pileup' - 4 arguments | 3 options */
        /* argument: [bed file] [genome_file] [window size] [extend size] */
    } else if (strcmp(argv[i], "rewrite") == 0) {
        choice = 3; 
        /* 'rewrite' - 2 arguments | 2 options */
        /* argument: [bed file] [err_code] */
    } else if (strcmp(argv[i], "unique") == 0) {
        choice = 4; /* 'unique' - 1 arguments | 3 options */
        /* argument: [bed file] */
    } else if (strcmp(argv[i], "wig") == 0) {
        choice = 5; 
        /* 'wig' - 4 arguments | 3 options */
        /* argument: [bed file] [genome file] [window_size] [extend size] */
    } else if (strcmp(argv[i], "bin_table") == 0) {
        choice = 6; 
        /* 'bin_table' - (3 arguments or 5 if --plots | 3 options */
        /* argument: [bed file] [genome file] [window_size] */
        /* argument: [bed file] [genome file] [window_size] [treshold] [output_dir] --plot or --globalQC */
    } else if (strcmp(argv[i], "sort") == 0) { //must be clean a test
        choice = 7; 
        /* 'bin_table' - (2 arguments  | 1 options */
        /* argument: [bed file] [genome file]  */
    } else if (strcmp(argv[i], "bin_table_rep") == 0) { 
        choice = 8; 
        /* 'bin_table_rep' - (5 arguments | 3 options */
        /* argument: [bed file] [genome file] [window_size] [threshold] [rep number]*/
    } else if (strcmp(argv[i], "elong_read") == 0) { //must be clean a test
        choice = 9; 
        /* 'elong_read' - (2 arguments | 2 options */
        /* argument: [bed file] [genome file] [extend_size] */
    } else if (strcmp(argv[i], "local_bg") == 0) { 
        choice = 10; 
        /* 'local_bg' - (6 arguments | 2 options */
        /* argument: [bed file] [genome file] [large_window_size] [window_size] [kthmax] */
    } else if (strcmp(argv[i], "plot_bin_table") == 0) { 
        choice = 11; 
        /* 'plot_bin_table' - (4 arguments | 2 options */
        /* argument: [bed file] [bed_file] [threshold] [output_dir] */
    } else if (strcmp(argv[i], "globalQC") == 0) { 
        choice = 12; 
        /* 'globalQC' - (2 arguments | 4 options */
        /* argument: [bin table] [threshold] */
    } else if (strcmp(argv[i], "count_read") == 0) { 
        choice = 13; 
        if (uargc != 3) { // max number of argument is 1
            fprintf(stderr, "Error: invalid number of argument.\n\n");
            exit(1);
        }
        if (strcmp(argv[2], "stdin") != 0) {
            input_file = strdup(argv[2]);
        }
    } else if (strcmp(argv[i], "globalQCrep") == 0) { 
        choice = 14; 
        /* 'globalQC' - (4 arguments | 1 options */
        /* argument: [bin table] [threshold] [rep_number] [valid_rep] */
    } else {
        fprintf(stderr, "Error: invalid task: '%s'.\n\n", argv[i]);
        print_usage();
        exit(1);
    }

    i = 2; /* skip the task name */

    while (i < uargc) {
        if (choice == 0) {
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--chrm-file") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        genome_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage --chrm-file, missing file_name argument.\n\n");
                        exit(1);
                    }
                    get_tmru = true;
                } else if (strcmp(argv[i], "--chrm-dict") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_dict = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                    get_tmru = true;
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                }
                count_arg++;
            }
        } else if (choice == 1) { /* 'issorted' - 1 argument | 1 options  ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                }
                count_arg++;
            }
        } else if (choice == 2) { /* 'pileup' - 4 arguments | 4 options ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "--zero-fill") == 0) {
                    zero_fill = true;
                } else if (strcmp(argv[i], "--chrm-dict") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_dict = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    genome_file = strdup(argv[i]);
                } else if (count_arg == 2) {
                    window_size = get_int_arg(argv[i], 10, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid window size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 10.\n\n");
                        exit(1);
                    }
                } else if (count_arg == 3) {
                    extend_size = get_int_arg(argv[i], 0, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid extend size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must >= 0.\n\n");
                        exit(1);
                    }
                }
                count_arg++;
            }
        } else if (choice == 3) { /* 'rewrite' - 2 arguments | 2 options ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    error_code = get_int_arg(argv[i], 0, 32);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid error_code, only 0, 2, 4, 8, 16 and 32 are allowed.\n\n");
                        exit(1);
                    } else {
                        if (error_code != 0 && error_code != 2 && error_code != 4 && error_code != 8 &&
                            error_code != 16 && error_code != 32) {
                            fprintf(stderr, "Error: invalid error_code, only 0, 2, 4, 8, 16 and 32 are allowed.\n\n");
                            exit(1);
                        }
                    }
                }
                count_arg++;
            }
        } else if (choice == 4) { /* 'unique' - 1 arguments | 3 options ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--write") == 0) {
                    write_file = true;
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                }
                count_arg++;
            }
        } else if (choice == 5) { /* 'wig' - 4 arguments | 4 options ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--chrm-dict") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_dict = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage --chrm-dict, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--chrm-region") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_region = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage --chrm-region, missing file_name argument.\n\n");
                        exit(1);
                    }
                }else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    genome_file = strdup(argv[i]);
                } else if (count_arg == 2) {
                    window_size = get_int_arg(argv[i], 10, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid window size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 10.\n\n");
                        exit(1);
                    }
                } else if (count_arg == 3) {
                    extend_size = get_int_arg(argv[i], 0, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid extend size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must >= 0.\n\n");
                        exit(1);
                    }
                }
                count_arg++;
            }
        } else if (choice == 6) { /* 'bin_table' - 4 arguments | 4 options ################################### */
            /* look for --plot argument*/
            while (j < uargc) {
                if (strcmp(argv[j], "--plot") == 0) {
                    plot = true;
                    store_bin_table = true;
                } else if (strcmp(argv[j], "--globalQC") == 0) {
                    globalQC = true;
                    store_bin_table = true;
                }
                j++;
            }
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--plot") == 0) {
                    //nothing
                } else if (strcmp(argv[i], "--globalQC") == 0) {
                    //nothing
                } else if (strcmp(argv[i], "--both-mode") == 0) {
                    if (!plot) {
                        fprintf(stderr, "Error: option: '%s' cannot be used without '--plot' option.\n\n", argv[i]);
                        exit(1);
                    }
                    both_mode = true;
                } else if (strcmp(argv[i], "--read-count") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        total_reads = get_int_arg(argv[i], 1, INT_MAX);
                        if (errno != 0) {
                            fprintf(stderr, "Error: invalid readcount value: '%s'.\n", argv[i]);
                            fprintf(stderr, "The value must an integer > 0.\n\n");
                            exit(1);
                        }
                    } else {
                        fprintf(stderr, "Error: invalid usage --read-count, an number is expected.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--chrm-dict") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_dict = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--sam-table") == 0) {
                    if (globalQC) {
                        if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                            strcpy(sam_table, argv[i]);
                        } else {
                            fprintf(stderr, "Error: invalid usage --sam-table, missing file_name argument.\n\n");
                            exit(1);
                        }
                    } else {
                        fprintf(stderr, "Error: option: '%s' cannot be used without '--globalQC' option.\n\n", argv[i]);
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--bed-track") == 0) {
                    if (globalQC) {
                        if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                            strcpy(bed_track, argv[i]);
                        } else {
                            fprintf(stderr, "Error: invalid usage --bed-track missing file_name argument.\n\n");
                            exit(1);
                        }
                    } else {
                        fprintf(stderr, "Error: option: '%s' cannot be used without '--globalQC' option.\n\n", argv[i]);
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--wigs") == 0) {
                    if (globalQC) {
                        if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                            strcpy(output_wigs, argv[i]);
                        } else {
                            fprintf(stderr, "Error: invalid usage --wigs, missing output_dir argument.\n\n");
                            exit(1);
                        }
                    } else {
                        fprintf(stderr, "Error: option: '%s' cannot be used without '--globalQC' option.\n\n", argv[i]);
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--gnuplot-path") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        strcpy(gnuplot_path, argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage --gnuplot-path, missing path argument.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    genome_file = strdup(argv[i]);
                } else if (count_arg == 2) {
                    window_size = get_int_arg(argv[i], 10, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid window size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 10.\n\n");
                        exit(1);
                    }
                } else if ((plot || globalQC) && count_arg == 3) {
                    threshold = get_int_arg(argv[i], 1, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid treshold value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must > 0.\n\n");
                        exit(1);
                    }
                } else if ((plot || globalQC) && count_arg == 4) {
                    strcpy(output_dir, argv[i]);
                    if (strlen(output_dir) == 0) {
                        fprintf(stderr, "Error: invalid output directory.\n\n");
                        exit(1);
                    }
                }
                count_arg++;
            }
        } else if (choice == 7) { /* 'sort' - 2 arguments | 2 options ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "-c") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        core_nb = get_int_arg(argv[i], 1, 25);
                        if (errno != 0) {
                            fprintf(stderr, "Error: invalid readcount value: '%s'.\n", argv[i]);
                            fprintf(stderr, "The value must an integer between 0 and 25.\n\n");
                            exit(1);
                        }
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--chrm-dict") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_dict = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    genome_file = strdup(argv[i]);
                }
                count_arg++;
            }
        } else if (choice == 8) { /* 'bin_table_rep' - 5 arguments | 3 options ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--read-count") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        total_reads = get_int_arg(argv[i], 1, INT_MAX);
                        if (errno != 0) {
                            fprintf(stderr, "Error: invalid readcount value: '%s'.\n", argv[i]);
                            fprintf(stderr, "The value must an integer > 0.\n\n");
                            exit(1);
                        }
                    } else {
                        fprintf(stderr, "Error: invalid usage --readcount, an number is expected.\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--chrm-dict") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_dict = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    genome_file = strdup(argv[i]);
                } else if (count_arg == 2) {
                    window_size = get_int_arg(argv[i], 10, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid window size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 10.\n\n");
                        exit(1);
                    }
                } else if (count_arg == 3) {
                    threshold = get_int_arg(argv[i], 0, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid treshold value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must >= 0.\n\n");
                        exit(1);
                    }
                } else if (count_arg == 4) {
                    rep_number = get_int_arg(argv[i], 2, 10);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid replicate value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must be between 2 and 10.\n\n");
                        exit(1);
                    }
                }
                count_arg++;
            }
        } else if (choice == 9) { /* 'elong_read' - 2 arguments | 2 options ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n");
                        exit(1);
                    }
                }/* else if (strcmp(argv[i], "--chrm-dict") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_dict = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                }*/ else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    extend_size = get_int_arg(argv[i], 0, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid extend size value: '%s'.\n\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 0.\n\n");
                        exit(1);
                    }
                }
                count_arg++;
            }
        } else if (choice == 10) { /* 'local_bg' - 5 arguments | 2 options ################################### */
            /* [bed file] [genome file] [large_window_size] [window_size] [kthmax] */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--no-header") == 0) {
                    no_header = true;
                } else if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--chrm-dict") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        chrm_dict = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    genome_file = strdup(argv[i]);
                } else if (count_arg == 2) {
                    large_window_size = get_int_arg(argv[i], 100, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid extend size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 100.\n\n");
                        exit(1);
                    }
                } else if (count_arg == 3) {
                    window_size = get_int_arg(argv[i], 10, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid extend size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 10.\n\n");
                        exit(1);
                    }
                    if (window_size >= large_window_size) {
                        fprintf(stderr, "Error: invalid window size value. Must be positif and inferior than large window size\n");
                        exit(1);
                    }
                    if (large_window_size % window_size != 0) {
                        fprintf(stderr, "Error: large window size must be a multiple of window size\n");
                        exit(1);
                    }
                } else if (count_arg == 4) {
                    kthminf = get_float_arg(argv[i], 0, 1);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid extend size value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must be between 0 and 1.\n\n");
                        exit(1);
                    }
                }

                count_arg++;
            } 
        } else if (choice == 11) { /* 'plot_bin_table' - 3 arguments | 2 options ################################### */
            /* [bed file] [both_mode] [threshold] [output_dir] */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "--both-mode") == 0) {
                    both_mode = true;
                } else if (strcmp(argv[i], "--gnuplot-path") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        strcpy(gnuplot_path, argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage --gnuplot-path, missing path argument.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                }  else if (count_arg == 1) {
                    threshold = get_int_arg(argv[i], 1, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid threshold value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 1.\n\n");
                        exit(1);
                    }
                } else if (count_arg == 2) {
                   strcpy(output_dir, argv[i]);
                    if (strlen(output_dir) == 0) {
                        fprintf(stderr, "Error: invalid output directory.\n\n");
                        exit(1);
                    }
                }
                count_arg++;
            }
        } else if (choice == 12) { /* 'globalQC' - 2 arguments | 4 options ################################### */
            /* [bin table] */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--sam-table") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        strcpy(sam_table, argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage --sam-table, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--bed-track") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        strcpy(bed_track, argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage --bed-track missing file_name argument.\n\n");
                        exit(1);
                    }
                } else if (strcmp(argv[i], "--wigs") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        strcpy(output_wigs, argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage --wigs, missing output_dir argument.\n\n");
                        exit(1);
                    }
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    threshold = get_int_arg(argv[i], 1, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid threshold value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 1.\n\n");
                        exit(1);
                    }
                }
                count_arg++;
            }
        } else if (choice == 14) { /* 'globalQCrep' - 4 arguments | 1 options ################################### */
            if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) > 1) { /* parsing option */
                if (strcmp(argv[i], "-o") == 0) {
                    if (++i < uargc && strncmp(argv[i], "-", 1) != 0) {
                        output_file = strdup(argv[i]);
                    } else {
                        fprintf(stderr, "Error: invalid usage -o, missing file_name argument.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: invalid option: '%s'.\n\n", argv[i]);
                    exit(1);
                }
            } else {
                if (count_arg == 0) {
                    if (strcmp(argv[i], "stdin") != 0) {
                        input_file = strdup(argv[i]);
                    }
                } else if (count_arg == 1) {
                    threshold = get_int_arg(argv[i], 1, INT_MAX);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid threshold value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must an integer >= 1.\n\n");
                        exit(1);
                    }
                } else if (count_arg == 2) {
                    rep_number = get_int_arg(argv[i], 2, 10);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid replicate value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must be between 2 and 10.\n\n");
                        exit(1);
                    }
                } else if (count_arg == 3) {
                    valid_rep = get_int_arg(argv[i], 1, 10);
                    if (errno != 0) {
                        fprintf(stderr, "Error: invalid replicate value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value must be between 1 and 10.\n\n");
                        exit(1);
                    }
                    if (valid_rep > rep_number) {
                        fprintf(stderr, "Error: invalid replicate value: '%s'.\n", argv[i]);
                        fprintf(stderr, "The value cannot be greater than the number of replicate.\n\n");
                        exit(1);
                    }
                }
                count_arg++;
            }
        }
        i++;
    }

    //fprintf(stderr, "choice: %d\n", choice);
    //fprintf(stderr, "count_arg: %d\n", count_arg);

    unsigned int print_arg_error = false;
    unsigned int test_gnuplot = false;

    if (choice == 1 || choice == 4 || choice == 0) { /* issorted and unique and integrity */
        if (count_arg != 1) {
            print_arg_error = true;
        }
    } else if (choice == 3 || choice == 7 || choice == 12 || choice == 9) { /* rewrite and sort and globalQC */
        if (count_arg != 2) {
            print_arg_error = true;
        }
    } else if (choice == 2 || choice == 5 || choice == 14) { /* pileup and wig and globalQCrep */
        if (count_arg != 4) {
            print_arg_error = true;
        }
    } else if (choice == 11) { /* elong_read and plot_bin_table*/
        if (count_arg != 3) {
            print_arg_error = true;
        }
        test_gnuplot = true;
    } else if (choice == 6) { /* bin_table */
        if (((plot || globalQC) && count_arg != 5) || (!plot && !globalQC && count_arg != 3)) {
            print_arg_error = true;
        } else if (plot) {
            test_gnuplot = true;
        }
    } else if (choice == 8 || choice == 10) { /* bin_table_rep and local_bg */
        if (count_arg != 5) {
            print_arg_error = true;
        }
    }

    if (print_arg_error) {
        fprintf(stderr, "Error: invalid number of argument.\n\n");
        exit(1);
    }


    if (test_gnuplot) {
        /* test is gnuplot is installed*/
        char gnuplot_version[4096] = "";
        strcat(gnuplot_version, gnuplot_path);
        strcat(gnuplot_version, " --version");
        FILE* fp = popen(gnuplot_version, "r");
        if (fp == NULL) {
            perror("ERROR");
            exit(1);
        }

        /* Read the output a line at a time - output it. */
        char poutput[128];
        while (fgets(poutput, sizeof(poutput), fp) != NULL) {
            if (strncmp(poutput, "gnuplot", 7) != 0) {
                fprintf(stderr, "ERROR: Unable to run gnuplot.\n" );
                pclose(fp);
                exit(1);
            }
        }
        pclose(fp);
        if (strlen(poutput) == 0) {
            fprintf(stderr, "ERROR: Unable to run gnuplot.\n" );
            exit(1);
        }
    }

    if (input_file != NULL) {
        /* check the input file */
        fp_in = fopen(input_file, "r");
        if (fp_in == NULL) {
            fprintf(stderr, "Error: cannot open the input file, no such file or directory.\n\n");
            exit(1);
        }
    } else {
        fp_in = stdin;
    }

    if (output_file != NULL) {
        fp_out = fopen(output_file, "w");
        if (fp_out == NULL) {
            fprintf(stderr, "Error: cannot create the output file.\n\n");
            exit(1);
        }
    } else {
        fp_out = stdout;
    }

    if (chrm_dict != NULL) {
        fill_used_chrm(chrm_dict);
     } else if (genome_file != NULL) {
        fp_genome = fopen(genome_file, "r");
        if (fp_genome == NULL) {
            fprintf(stderr, "Error:  cannot open the genome file, no such file or directory.\n\n");
            exit(1);
        }

        /* parse the genome array */
        get_chrom_size(fp_genome);
        fclose(fp_genome);
    }

    switch(choice) {
        case 0:
            check_bed_file_integrity(fp_in, get_tmru);
            break;
        case 1:
            //printf("test");
            check_bed_file_sorted(fp_in, no_header);
            break;
        case 2:
            pileup(fp_in, fp_out, window_size, extend_size, no_header, zero_fill);
            break;
        case 3:
            rewrite_bed_file(fp_in, fp_out, error_code, no_header);
            break;
        case 4:
            check_unique_read(fp_in, fp_out, no_header, write_file);
            break;
        case 5:
            if (chrm_region != NULL) {
                parse_region_list(chrm_region);
            }
            bed_to_wig(fp_in, fp_out, window_size, extend_size, no_header, true);
            break;
        case 6:
            if (total_reads == 0) {
                if (input_file != NULL) {
                    total_reads = get_bedline_count(fp_in);
                    fclose(fp_in);
                    fp_in = fopen(input_file, "r");
                    if (fp_in == NULL) {
                        fprintf(stderr, "Error: cannot open the input file, no such file or directory.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: you must specify the number of expected lines in stdin.\n\n");
                    exit(1);
                }
            }
            get_sampling_line_index(total_reads, sampling_array);
            build_bin_table(fp_in, fp_out, window_size, store_bin_table, no_header);
            if (globalQC) {
                char summary_file[4096] = "";
                strcpy(summary_file, output_dir);
                strcat(summary_file, "/indicators.txt");
                FILE* fp_summary = fopen(summary_file, "w");
                if (fp_summary == NULL) {
                    fprintf(stderr, "Error: cannot create the summary file.\n\n");
                    destroy_bin_table();
                    exit(1);
                }
                compute_indicators(fp_in, fp_summary, threshold, sam_table, bed_track, output_wigs, 1); /* 0 -> memory */
            }
            if (plot) {
                plot_bin_table(NULL, both_mode, threshold, output_dir, gnuplot_path, 1); //true (memory)
                destroy_coor_hash();
            }
            destroy_bin_table();
            break;
        case 7:
            split_bed_file(fp_in, fp_out, core_nb, no_header);
            break;
        case 8:
            if (total_reads == 0) {
                if (input_file != NULL) {
                    total_reads = get_bedline_count(fp_in);
                    fclose(fp_in);
                    fp_in = fopen(input_file, "r");
                    if (fp_in == NULL) {
                        fprintf(stderr, "Error: cannot open the input file, no such file or directory.\n\n");
                        exit(1);
                    }
                } else {
                    fprintf(stderr, "Error: you must specify the number of expected lines in stdin.\n\n");
                    exit(1);
                }
            }
            get_sampling_line_index_rep(total_reads, sampling_array, rep_number);
            build_bin_table_rep(fp_in, fp_out, window_size, rep_number, threshold, no_header);
            break;
        case 9:
            printf("doesn't work\n");
            exit(1);
            write_and_sort_extend_reads(fp_in, fp_out, extend_size, no_header);
            break;
        case 10:
            build_local_bg_table(fp_in, fp_out, large_window_size, window_size, kthminf, no_header);
            break;
        case 11:
            plot_bin_table(fp_in, both_mode, threshold, output_dir, gnuplot_path, 0); /* 0 -> memory */
            destroy_coor_hash();
            destroy_bin_table();
        case 12:
            compute_indicators(fp_in, fp_out, threshold, sam_table, bed_track, output_wigs, 0); /* 0 -> memory */
            destroy_bin_table();
            break;
        case 13:
            total_reads = get_bedline_count(fp_in);
            printf("%ld\n", total_reads);
        case 14:
            compute_indicators_replicate(fp_in, fp_out, threshold, rep_number, valid_rep);
    }

    fclose(fp_in);
    fclose(fp_out);

    return;
}

int main(int argc, char* argv[]) {
    unsigned int uargc = argc;

    parse_argument(uargc, argv);
    //run_case = "";

    return (EXIT_SUCCESS);
}


