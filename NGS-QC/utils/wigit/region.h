/* 
 * File:   region.h
 * Author: blum
 *
 * Created on 14 avril 2015, 16:56
 */

#ifndef REGION_H
#define	REGION_H

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

struct genomicRegion {
    unsigned long start;
    unsigned long end;
};

struct dictRegion {
    char *chrm;
    unsigned int nregions;
    struct genomicRegion regions[20];
    UT_hash_handle hh;
};

void delete_regions(struct dictRegion **regions);

void find_regions(char *string, struct dictRegion **regions);

#endif	/* REGION_H */

