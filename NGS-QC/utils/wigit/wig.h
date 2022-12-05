/* 
 * File:   wig.h
 * Author: blum
 *
 * Created on 14 avril 2015, 16:55
 */

#ifndef WIG_H
#define	WIG_H

struct chromSection {
    unsigned int *val;
    unsigned int *val2;
    unsigned long size;
};

void create_wigs(char *in_name, int extsize, int span, int issorted, int nodup, struct genomeInfo *genome, struct dictRegion **regions);

int regions_sorted(char *in_name, int extsize, int span, struct genomeInfo *genome, struct dictRegion **regions);

int genomewide_sorted(char *in_name, int extsize, int span, struct genomeInfo *genome, int nodup);

void flush_section(char *chrm, int span, struct chromSection *section, int nodup);

#endif	/* WIG_H */

