/* 
 * File:   wigit.c
 * Author: blum
 *
 * Created on 14 avril 2015, 16:54
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "genome.h"
#include "region.h"
#include "wig.h"

#define EXTSIZE 150
#define SPAN 20


void usage() {
    fprintf(stderr, "\nUsage: wigit <file.bed> [<region1> <region2>...] [options]\n\n");
    fprintf(stderr, "Region:\t<chr>:<start>:<end>\n\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "\t--sorted\tConsider the file as sorted (use less memory)\n");
    fprintf(stderr, "\t--nodup\tPrint the read intensity with AND WITHOUT PCR duplicate reads\n");
    fprintf(stderr, "\t-g\tGenome assembly\n");
    fprintf(stderr, "\t--ext\tElongation (default: %u)\n", EXTSIZE);
    fprintf(stderr, "\t--span\tWiggles length (default: %u)\n", SPAN);    
}

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        usage();
        return (EXIT_FAILURE);
    }
    
    int i;
    int issorted = 0;
    int extsize = EXTSIZE;
    int span = SPAN;
    int nodup = 0;
    int genome_wide = 1;
    struct genomeInfo *genome = NULL;
    struct dictRegion *regions = NULL;
    
    for (i = 1; i < argc; ++i) {
        if (equals(argv[i], "-h") || equals(argv[i], "--help")) {
            usage();
            return (EXIT_SUCCESS);
        }
    }
    
    for (i = 2; i < argc; ++i) {
        if (equals(argv[i], "--sorted"))
            issorted = 1;
        else if (equals(argv[i], "--nodup"))
            nodup = 1;
        else if (equals(argv[i], "--ext") && ++i < argc)
            extsize = tolong(argv[i]);
        else if (equals(argv[i], "--span") && ++i < argc)
            span = tolong(argv[i]);
        else if (equals(argv[i], "-g") && ++i < argc) {
            genome = get_genome(lower(argv[i]));
            
            if (genome == NULL) {
                fprintf(stderr, "Invalid genome %s\n", argv[i]);
                show_genomes();
                return (EXIT_FAILURE);
            }
        } else {
            find_regions(argv[i], &regions);
        }
    }
    
    create_wigs(argv[1], extsize, span, issorted, nodup, genome, &regions);
    
    delete_genome(genome);
    delete_regions(&regions);
    
    return (EXIT_SUCCESS);
}

