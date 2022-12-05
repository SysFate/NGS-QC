#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

struct genomeInfo {
	char *chrm;
	long size;
	UT_hash_handle hh;
};

struct genomeInfo *TAIR10();
struct genomeInfo *ce10();
struct genomeInfo *ce4();
struct genomeInfo *ce6();
struct genomeInfo *danRer5();
struct genomeInfo *danRer6();
struct genomeInfo *danRer7();
struct genomeInfo *dm2();
struct genomeInfo *dm3();
struct genomeInfo *galGal4();
struct genomeInfo *hg17();
struct genomeInfo *hg18();
struct genomeInfo *hg19();
struct genomeInfo *hg38();
struct genomeInfo *mm10();
struct genomeInfo *mm8();
struct genomeInfo *mm9();
struct genomeInfo *panTro4();
struct genomeInfo *rn3();
struct genomeInfo *rn4();
struct genomeInfo *rn5();
struct genomeInfo *sacCer3();
struct genomeInfo *get_genome(char *string);
void delete_genome(struct genomeInfo *genome);
void show_genomes();
