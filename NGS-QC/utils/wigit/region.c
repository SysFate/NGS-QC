#include "region.h"

void find_regions(char *string, struct dictRegion **regions) {
    char delim[] = ":";
    char *cp, *chrm, *ptr1, *ptr2, *token;
    long start, end;
    int i;
    
    struct dictRegion *d;
    
    for (i = 0, cp = string; ; ++i, cp = NULL) {
        token = strtok_r(cp, delim, &ptr1);
        if (token == NULL)
            break;
        else if (i == 0)
            chrm = token;
        else if (i == 1) {
            start = strtol(token, &ptr2, 10);
            if (ptr2 == token || start < 0)
                break;
        } else if (i == 2) {
            end = strtol(token, &ptr2, 10);
            if (ptr2 == token || end <= start)
                break;
            
            HASH_FIND_STR(*regions, chrm, d);
            if (d) {
                d->regions[d->nregions].start = start;
                d->regions[d->nregions].end = end;
                ++d->nregions;
            } else {
                struct dictRegion *nr = malloc(sizeof(struct dictRegion));
                nr->chrm = strdup(chrm);
                nr->nregions = 1;
                nr->regions[0].start = start;
                nr->regions[0].end = end;
                HASH_ADD_STR(*regions, chrm, nr);
            }
        }
    }
}

void delete_regions(struct dictRegion **regions) {
    struct dictRegion *c, *tmp;
    HASH_ITER(hh, *regions, c, tmp) {
        free(c->chrm);
        HASH_DEL(*regions, c);
        free(c);
    }
}
