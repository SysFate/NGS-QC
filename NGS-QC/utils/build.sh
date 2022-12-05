#!/bin/bash

gcc -Wall -Wextra -posix -Werror -std=c99 -D_POSIX_C_SOURCE=2001  NGSQC_bed_utils.c lib/str_tools.c lib/genome.c lib/bit_array.c lib/median.c functions/integrity.c functions/issorted.c functions/rewrite.c functions/unique.c functions/wig.c functions/sort.c functions/pileup.c functions/bin_table.c functions/bin_table_rep.c functions/elong_read.c functions/local_bg.c functions/plot_bin_table.c functions/globalQC.c -lpthread -o NGSQC_bed_utils -lm
chmod +x NGSQC_bed_utils

cd wigit
gcc -Wall -Wextra common.c genome.c region.c wig.c wigit.c -o wigit
chmod +x wigit