#include "genome.h"

struct genomeInfo *TAIR10() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("Chr1");
	chrm1->size = 30427671;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("Chr2");
	chrm2->size = 50125960;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("Chr3");
	chrm3->size = 73585790;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("Chr4");
	chrm4->size = 92170846;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("Chr5");
	chrm5->size = 119146348;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chloroplast");
	chrm6->size = 119300826;
	HASH_ADD_STR(genome, chrm, chrm6);
	return genome;
}

struct genomeInfo *ce10() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chrI");
	chrm1->size = 15072423;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chrII");
	chrm2->size = 15279345;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chrIII");
	chrm3->size = 13783700;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chrIV");
	chrm4->size = 17493793;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chrM");
	chrm5->size = 13794;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chrV");
	chrm6->size = 20924149;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chrX");
	chrm7->size = 17718866;
	HASH_ADD_STR(genome, chrm, chrm7);
	return genome;
}

struct genomeInfo *ce4() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chrI");
	chrm1->size = 15072419;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chrII");
	chrm2->size = 15279316;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chrIII");
	chrm3->size = 13783681;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chrIV");
	chrm4->size = 17493784;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chrM");
	chrm5->size = 13794;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chrV");
	chrm6->size = 20919398;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chrX");
	chrm7->size = 17718852;
	HASH_ADD_STR(genome, chrm, chrm7);
	return genome;
}

struct genomeInfo *ce6() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chrI");
	chrm1->size = 15072421;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chrII");
	chrm2->size = 15279323;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chrIII");
	chrm3->size = 13783681;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chrIV");
	chrm4->size = 17493785;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chrM");
	chrm5->size = 13794;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chrV");
	chrm6->size = 20919568;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chrX");
	chrm7->size = 17718854;
	HASH_ADD_STR(genome, chrm, chrm7);
	return genome;
}

struct genomeInfo *danRer5() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 56204684;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 42379582;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 44616367;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 47523734;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 53547397;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 56522864;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 46629432;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 53070661;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 52310423;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 49281368;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 46181231;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 54366722;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 56528676;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr21");
	chrm14->size = 46057314;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr22");
	chrm15->size = 38981829;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr23");
	chrm16->size = 46388020;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr24");
	chrm17->size = 40293347;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr25");
	chrm18->size = 32876240;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr3");
	chrm19->size = 62931207;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr4");
	chrm20->size = 42602441;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr5");
	chrm21->size = 70371393;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr6");
	chrm22->size = 59200669;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chr7");
	chrm23->size = 70262009;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chr8");
	chrm24->size = 56456705;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chr9");
	chrm25->size = 51490918;
	HASH_ADD_STR(genome, chrm, chrm25);

	struct genomeInfo *chrm26 = malloc(sizeof(struct genomeInfo));
	chrm26->chrm = strdup("chrM");
	chrm26->size = 16596;
	HASH_ADD_STR(genome, chrm, chrm26);
	return genome;
}

struct genomeInfo *danRer6() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 59305620;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 43467561;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 44116856;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 46853116;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 50748729;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 52930158;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 47237297;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 51890894;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 49469313;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 49271716;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 48708673;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 58009534;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 51884995;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr21");
	chrm14->size = 47572505;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr22");
	chrm15->size = 41415389;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr23");
	chrm16->size = 44714728;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr24");
	chrm17->size = 40403431;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr25");
	chrm18->size = 38768535;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr3");
	chrm19->size = 60907308;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr4");
	chrm20->size = 71658100;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr5");
	chrm21->size = 74451498;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr6");
	chrm22->size = 61647013;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chr7");
	chrm23->size = 76918211;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chr8");
	chrm24->size = 55568185;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chr9");
	chrm25->size = 54736511;
	HASH_ADD_STR(genome, chrm, chrm25);

	struct genomeInfo *chrm26 = malloc(sizeof(struct genomeInfo));
	chrm26->chrm = strdup("chrM");
	chrm26->size = 16596;
	HASH_ADD_STR(genome, chrm, chrm26);
	return genome;
}

struct genomeInfo *danRer7() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 60348388;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 46591166;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 46661319;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 50697278;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 54093808;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 53733891;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 47442429;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 58780683;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 53984731;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 49877488;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 50254551;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 60300536;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 55952140;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr21");
	chrm14->size = 44544065;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr22");
	chrm15->size = 42261000;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr23");
	chrm16->size = 46386876;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr24");
	chrm17->size = 43947580;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr25");
	chrm18->size = 38499472;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr3");
	chrm19->size = 63268876;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr4");
	chrm20->size = 62094675;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr5");
	chrm21->size = 75682077;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr6");
	chrm22->size = 59938731;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chr7");
	chrm23->size = 77276063;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chr8");
	chrm24->size = 56184765;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chr9");
	chrm25->size = 58232459;
	HASH_ADD_STR(genome, chrm, chrm25);

	struct genomeInfo *chrm26 = malloc(sizeof(struct genomeInfo));
	chrm26->chrm = strdup("chrM");
	chrm26->size = 16596;
	HASH_ADD_STR(genome, chrm, chrm26);
	return genome;
}

struct genomeInfo *dm2() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr2L");
	chrm1->size = 22407834;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr2R");
	chrm2->size = 20766785;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr2h");
	chrm3->size = 1694122;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr3L");
	chrm4->size = 23771897;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr3R");
	chrm5->size = 27905053;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr3h");
	chrm6->size = 2955737;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr4");
	chrm7->size = 1281640;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr4h");
	chrm8->size = 88110;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chrM");
	chrm9->size = 19517;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chrU");
	chrm10->size = 8724946;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chrX");
	chrm11->size = 22224390;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chrXh");
	chrm12->size = 359526;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chrYh");
	chrm13->size = 396896;
	HASH_ADD_STR(genome, chrm, chrm13);
	return genome;
}

struct genomeInfo *dm3() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr2L");
	chrm1->size = 23011544;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr2LHet");
	chrm2->size = 368872;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr2R");
	chrm3->size = 21146708;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr2RHet");
	chrm4->size = 3288761;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr3L");
	chrm5->size = 24543557;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr3LHet");
	chrm6->size = 2555491;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr3R");
	chrm7->size = 27905053;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr3RHet");
	chrm8->size = 2517507;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr4");
	chrm9->size = 1351857;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chrM");
	chrm10->size = 19517;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chrU");
	chrm11->size = 10049037;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chrUextra");
	chrm12->size = 29004656;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chrX");
	chrm13->size = 22422827;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chrXHet");
	chrm14->size = 204112;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chrYHet");
	chrm15->size = 347038;
	HASH_ADD_STR(genome, chrm, chrm15);
	return genome;
}

struct genomeInfo *galGal4() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 195276750;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 19911089;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 19401079;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 19897011;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 17760035;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 15161805;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 12656803;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 535270;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 10454150;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 11219875;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 9983394;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 148809762;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 14302601;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr21");
	chrm14->size = 6802778;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr22");
	chrm15->size = 4081097;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr23");
	chrm16->size = 5723239;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr24");
	chrm17->size = 6323281;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr25");
	chrm18->size = 2191139;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr26");
	chrm19->size = 5329985;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr27");
	chrm20->size = 5209285;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr28");
	chrm21->size = 4742627;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr3");
	chrm22->size = 110447801;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chr32");
	chrm23->size = 1028;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chr4");
	chrm24->size = 90216835;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chr5");
	chrm25->size = 59580361;
	HASH_ADD_STR(genome, chrm, chrm25);

	struct genomeInfo *chrm26 = malloc(sizeof(struct genomeInfo));
	chrm26->chrm = strdup("chr6");
	chrm26->size = 34951654;
	HASH_ADD_STR(genome, chrm, chrm26);

	struct genomeInfo *chrm27 = malloc(sizeof(struct genomeInfo));
	chrm27->chrm = strdup("chr7");
	chrm27->size = 36245040;
	HASH_ADD_STR(genome, chrm, chrm27);

	struct genomeInfo *chrm28 = malloc(sizeof(struct genomeInfo));
	chrm28->chrm = strdup("chr8");
	chrm28->size = 28767244;
	HASH_ADD_STR(genome, chrm, chrm28);

	struct genomeInfo *chrm29 = malloc(sizeof(struct genomeInfo));
	chrm29->chrm = strdup("chr9");
	chrm29->size = 23441680;
	HASH_ADD_STR(genome, chrm, chrm29);

	struct genomeInfo *chrm30 = malloc(sizeof(struct genomeInfo));
	chrm30->chrm = strdup("chrLGE64");
	chrm30->size = 799899;
	HASH_ADD_STR(genome, chrm, chrm30);

	struct genomeInfo *chrm31 = malloc(sizeof(struct genomeInfo));
	chrm31->chrm = strdup("chrM");
	chrm31->size = 16775;
	HASH_ADD_STR(genome, chrm, chrm31);

	struct genomeInfo *chrm32 = malloc(sizeof(struct genomeInfo));
	chrm32->chrm = strdup("chrW");
	chrm32->size = 1248174;
	HASH_ADD_STR(genome, chrm, chrm32);

	struct genomeInfo *chrm33 = malloc(sizeof(struct genomeInfo));
	chrm33->chrm = strdup("chrZ");
	chrm33->size = 82363669;
	HASH_ADD_STR(genome, chrm, chrm33);
	return genome;
}

struct genomeInfo *hg17() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 245522847;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 135413628;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 134452384;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 132449811;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 114142980;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 106368585;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 100338915;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 88827254;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 78774742;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 76117153;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 63811651;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 243018229;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 62435964;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr21");
	chrm14->size = 46944323;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr22");
	chrm15->size = 49554710;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr3");
	chrm16->size = 199505740;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr4");
	chrm17->size = 191411218;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr5");
	chrm18->size = 180857866;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr6");
	chrm19->size = 170975699;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr7");
	chrm20->size = 158628139;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr8");
	chrm21->size = 146274826;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr9");
	chrm22->size = 138429268;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chrM");
	chrm23->size = 16571;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chrX");
	chrm24->size = 154824264;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chrY");
	chrm25->size = 57701691;
	HASH_ADD_STR(genome, chrm, chrm25);
	return genome;
}

struct genomeInfo *hg18() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 247249719;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 135374737;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 134452384;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 132349534;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 114142980;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 106368585;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 100338915;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 88827254;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 78774742;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 76117153;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 63811651;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 242951149;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 62435964;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr21");
	chrm14->size = 46944323;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr22");
	chrm15->size = 49691432;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr3");
	chrm16->size = 199501827;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr4");
	chrm17->size = 191273063;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr5");
	chrm18->size = 180857866;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr6");
	chrm19->size = 170899992;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr7");
	chrm20->size = 158821424;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr8");
	chrm21->size = 146274826;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr9");
	chrm22->size = 140273252;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chrM");
	chrm23->size = 16571;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chrX");
	chrm24->size = 154913754;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chrY");
	chrm25->size = 57772954;
	HASH_ADD_STR(genome, chrm, chrm25);
	return genome;
}

struct genomeInfo *hg19() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 249250621;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 135534747;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 135006516;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 133851895;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 115169878;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 107349540;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 102531392;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 90354753;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 81195210;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 78077248;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 59128983;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 243199373;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 63025520;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr21");
	chrm14->size = 48129895;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr22");
	chrm15->size = 51304566;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr3");
	chrm16->size = 198022430;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr4");
	chrm17->size = 191154276;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr5");
	chrm18->size = 180915260;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr6");
	chrm19->size = 171115067;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr7");
	chrm20->size = 159138663;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr8");
	chrm21->size = 146364022;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr9");
	chrm22->size = 141213431;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chrM");
	chrm23->size = 16571;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chrX");
	chrm24->size = 155270560;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chrY");
	chrm25->size = 59373566;
	HASH_ADD_STR(genome, chrm, chrm25);
	return genome;
}

struct genomeInfo *hg38() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 248956422;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 133797422;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 135086622;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 133275309;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 114364328;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 107043718;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 101991189;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 90338345;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 83257441;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 80373285;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 58617616;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 242193529;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 64444167;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr21");
	chrm14->size = 46709983;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr22");
	chrm15->size = 50818468;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr3");
	chrm16->size = 198295559;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr4");
	chrm17->size = 190214555;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr5");
	chrm18->size = 181538259;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr6");
	chrm19->size = 170805979;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr7");
	chrm20->size = 159345973;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr8");
	chrm21->size = 145138636;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr9");
	chrm22->size = 138394717;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chrM");
	chrm23->size = 16569;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chrX");
	chrm24->size = 156040895;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chrY");
	chrm25->size = 57227415;
	HASH_ADD_STR(genome, chrm, chrm25);
	return genome;
}

struct genomeInfo *mm10() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 195471971;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 130694993;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 122082543;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 120129022;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 120421639;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 124902244;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 104043685;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 98207768;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 94987271;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 90702639;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 61431566;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 182113224;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr3");
	chrm13->size = 160039680;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr4");
	chrm14->size = 156508116;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr5");
	chrm15->size = 151834684;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr6");
	chrm16->size = 149736546;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr7");
	chrm17->size = 145441459;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr8");
	chrm18->size = 129401213;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr9");
	chrm19->size = 124595110;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chrM");
	chrm20->size = 16299;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chrX");
	chrm21->size = 171031299;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chrY");
	chrm22->size = 91744698;
	HASH_ADD_STR(genome, chrm, chrm22);
	return genome;
}

struct genomeInfo *mm8() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 197069962;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 129959148;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 121798632;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 120463159;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 120614378;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 123978870;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 103492577;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 98252459;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 95177420;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 90736837;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 61321190;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 181976762;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr3");
	chrm13->size = 159872112;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr4");
	chrm14->size = 155029701;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr5");
	chrm15->size = 152003063;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr6");
	chrm16->size = 149525685;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr7");
	chrm17->size = 145134094;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr8");
	chrm18->size = 132085098;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr9");
	chrm19->size = 124000669;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chrM");
	chrm20->size = 16299;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chrX");
	chrm21->size = 165556469;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chrY");
	chrm22->size = 16029404;
	HASH_ADD_STR(genome, chrm, chrm22);
	return genome;
}

struct genomeInfo *mm9() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 197195432;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 129993255;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 121843856;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 121257530;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 120284312;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 125194864;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 103494974;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 98319150;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 95272651;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 90772031;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 61342430;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 181748087;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr3");
	chrm13->size = 159599783;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr4");
	chrm14->size = 155630120;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr5");
	chrm15->size = 152537259;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr6");
	chrm16->size = 149517037;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr7");
	chrm17->size = 152524553;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr8");
	chrm18->size = 131738871;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr9");
	chrm19->size = 124076172;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chrM");
	chrm20->size = 16299;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chrX");
	chrm21->size = 166650296;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chrY");
	chrm22->size = 15902555;
	HASH_ADD_STR(genome, chrm, chrm22);
	return genome;
}

struct genomeInfo *panTro4() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 228333871;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 133524379;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 133121534;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 134246214;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 115123233;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 106544938;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 99548318;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 89983829;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 82630442;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 76611499;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 63644993;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr20");
	chrm12->size = 61729293;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr21");
	chrm13->size = 32799110;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr22");
	chrm14->size = 49737984;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr2A");
	chrm15->size = 113622374;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr2B");
	chrm16->size = 247518478;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr3");
	chrm17->size = 202329955;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr4");
	chrm18->size = 193495092;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr5");
	chrm19->size = 182651097;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr6");
	chrm20->size = 172623881;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chr7");
	chrm21->size = 161824586;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chr8");
	chrm22->size = 143986469;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chr9");
	chrm23->size = 137840987;
	HASH_ADD_STR(genome, chrm, chrm23);

	struct genomeInfo *chrm24 = malloc(sizeof(struct genomeInfo));
	chrm24->chrm = strdup("chrM");
	chrm24->size = 16554;
	HASH_ADD_STR(genome, chrm, chrm24);

	struct genomeInfo *chrm25 = malloc(sizeof(struct genomeInfo));
	chrm25->chrm = strdup("chrX");
	chrm25->size = 156848144;
	HASH_ADD_STR(genome, chrm, chrm25);

	struct genomeInfo *chrm26 = malloc(sizeof(struct genomeInfo));
	chrm26->chrm = strdup("chrY");
	chrm26->size = 26342871;
	HASH_ADD_STR(genome, chrm, chrm26);
	return genome;
}

struct genomeInfo *rn3() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 268121971;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 110733352;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 87800381;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 46649226;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 111348958;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 112220682;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 109774626;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 90224819;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 97307196;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 87338544;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 59223525;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 258222147;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 55296979;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr3");
	chrm14->size = 170969371;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr4");
	chrm15->size = 187371129;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr5");
	chrm16->size = 173106704;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr6");
	chrm17->size = 147642806;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr7");
	chrm18->size = 143082968;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr8");
	chrm19->size = 129061546;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr9");
	chrm20->size = 113649943;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chrUn");
	chrm21->size = 75822765;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chrX");
	chrm22->size = 160775580;
	HASH_ADD_STR(genome, chrm, chrm22);
	return genome;
}

struct genomeInfo *rn4() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 267910886;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 110718848;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 87759784;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 46782294;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 111154910;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 112194335;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 109758846;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 90238779;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 97296363;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 87265094;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 59218465;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 258207540;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 55268282;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr3");
	chrm14->size = 171063335;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr4");
	chrm15->size = 187126005;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr5");
	chrm16->size = 173096209;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr6");
	chrm17->size = 147636619;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr7");
	chrm18->size = 143002779;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr8");
	chrm19->size = 129041809;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr9");
	chrm20->size = 113440463;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chrM");
	chrm21->size = 16300;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chrUn");
	chrm22->size = 75822765;
	HASH_ADD_STR(genome, chrm, chrm22);

	struct genomeInfo *chrm23 = malloc(sizeof(struct genomeInfo));
	chrm23->chrm = strdup("chrX");
	chrm23->size = 160699376;
	HASH_ADD_STR(genome, chrm, chrm23);
	return genome;
}

struct genomeInfo *rn5() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chr1");
	chrm1->size = 290094216;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chr10");
	chrm2->size = 112200500;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chr11");
	chrm3->size = 93518069;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chr12");
	chrm4->size = 54450796;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chr13");
	chrm5->size = 118718031;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chr14");
	chrm6->size = 115151701;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chr15");
	chrm7->size = 114627140;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chr16");
	chrm8->size = 90051983;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chr17");
	chrm9->size = 92503511;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chr18");
	chrm10->size = 87229863;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chr19");
	chrm11->size = 72914587;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chr2");
	chrm12->size = 285068071;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chr20");
	chrm13->size = 57791882;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chr3");
	chrm14->size = 183740530;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chr4");
	chrm15->size = 248343840;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chr5");
	chrm16->size = 177180328;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chr6");
	chrm17->size = 156897508;
	HASH_ADD_STR(genome, chrm, chrm17);

	struct genomeInfo *chrm18 = malloc(sizeof(struct genomeInfo));
	chrm18->chrm = strdup("chr7");
	chrm18->size = 143501887;
	HASH_ADD_STR(genome, chrm, chrm18);

	struct genomeInfo *chrm19 = malloc(sizeof(struct genomeInfo));
	chrm19->chrm = strdup("chr8");
	chrm19->size = 132457389;
	HASH_ADD_STR(genome, chrm, chrm19);

	struct genomeInfo *chrm20 = malloc(sizeof(struct genomeInfo));
	chrm20->chrm = strdup("chr9");
	chrm20->size = 121549591;
	HASH_ADD_STR(genome, chrm, chrm20);

	struct genomeInfo *chrm21 = malloc(sizeof(struct genomeInfo));
	chrm21->chrm = strdup("chrM");
	chrm21->size = 16313;
	HASH_ADD_STR(genome, chrm, chrm21);

	struct genomeInfo *chrm22 = malloc(sizeof(struct genomeInfo));
	chrm22->chrm = strdup("chrX");
	chrm22->size = 154597545;
	HASH_ADD_STR(genome, chrm, chrm22);
	return genome;
}

struct genomeInfo *sacCer3() {
	struct genomeInfo *genome = NULL;

	struct genomeInfo *chrm1 = malloc(sizeof(struct genomeInfo));
	chrm1->chrm = strdup("chrI");
	chrm1->size = 230218;
	HASH_ADD_STR(genome, chrm, chrm1);

	struct genomeInfo *chrm2 = malloc(sizeof(struct genomeInfo));
	chrm2->chrm = strdup("chrII");
	chrm2->size = 813184;
	HASH_ADD_STR(genome, chrm, chrm2);

	struct genomeInfo *chrm3 = malloc(sizeof(struct genomeInfo));
	chrm3->chrm = strdup("chrIII");
	chrm3->size = 316620;
	HASH_ADD_STR(genome, chrm, chrm3);

	struct genomeInfo *chrm4 = malloc(sizeof(struct genomeInfo));
	chrm4->chrm = strdup("chrIV");
	chrm4->size = 1531933;
	HASH_ADD_STR(genome, chrm, chrm4);

	struct genomeInfo *chrm5 = malloc(sizeof(struct genomeInfo));
	chrm5->chrm = strdup("chrIX");
	chrm5->size = 439888;
	HASH_ADD_STR(genome, chrm, chrm5);

	struct genomeInfo *chrm6 = malloc(sizeof(struct genomeInfo));
	chrm6->chrm = strdup("chrM");
	chrm6->size = 85779;
	HASH_ADD_STR(genome, chrm, chrm6);

	struct genomeInfo *chrm7 = malloc(sizeof(struct genomeInfo));
	chrm7->chrm = strdup("chrV");
	chrm7->size = 576874;
	HASH_ADD_STR(genome, chrm, chrm7);

	struct genomeInfo *chrm8 = malloc(sizeof(struct genomeInfo));
	chrm8->chrm = strdup("chrVI");
	chrm8->size = 270161;
	HASH_ADD_STR(genome, chrm, chrm8);

	struct genomeInfo *chrm9 = malloc(sizeof(struct genomeInfo));
	chrm9->chrm = strdup("chrVII");
	chrm9->size = 1090940;
	HASH_ADD_STR(genome, chrm, chrm9);

	struct genomeInfo *chrm10 = malloc(sizeof(struct genomeInfo));
	chrm10->chrm = strdup("chrVIII");
	chrm10->size = 562643;
	HASH_ADD_STR(genome, chrm, chrm10);

	struct genomeInfo *chrm11 = malloc(sizeof(struct genomeInfo));
	chrm11->chrm = strdup("chrX");
	chrm11->size = 745751;
	HASH_ADD_STR(genome, chrm, chrm11);

	struct genomeInfo *chrm12 = malloc(sizeof(struct genomeInfo));
	chrm12->chrm = strdup("chrXI");
	chrm12->size = 666816;
	HASH_ADD_STR(genome, chrm, chrm12);

	struct genomeInfo *chrm13 = malloc(sizeof(struct genomeInfo));
	chrm13->chrm = strdup("chrXII");
	chrm13->size = 1078177;
	HASH_ADD_STR(genome, chrm, chrm13);

	struct genomeInfo *chrm14 = malloc(sizeof(struct genomeInfo));
	chrm14->chrm = strdup("chrXIII");
	chrm14->size = 924431;
	HASH_ADD_STR(genome, chrm, chrm14);

	struct genomeInfo *chrm15 = malloc(sizeof(struct genomeInfo));
	chrm15->chrm = strdup("chrXIV");
	chrm15->size = 784333;
	HASH_ADD_STR(genome, chrm, chrm15);

	struct genomeInfo *chrm16 = malloc(sizeof(struct genomeInfo));
	chrm16->chrm = strdup("chrXV");
	chrm16->size = 1091291;
	HASH_ADD_STR(genome, chrm, chrm16);

	struct genomeInfo *chrm17 = malloc(sizeof(struct genomeInfo));
	chrm17->chrm = strdup("chrXVI");
	chrm17->size = 948066;
	HASH_ADD_STR(genome, chrm, chrm17);
	return genome;
}

struct genomeInfo *get_genome(char *string) {
	struct genomeInfo *genome = NULL;
	if (strcmp(string, "tair10") == 0)
		genome = TAIR10();
	else if (strcmp(string, "ce10") == 0)
		genome = ce10();
	else if (strcmp(string, "ce4") == 0)
		genome = ce4();
	else if (strcmp(string, "ce6") == 0)
		genome = ce6();
	else if (strcmp(string, "danrer5") == 0)
		genome = danRer5();
	else if (strcmp(string, "danrer6") == 0)
		genome = danRer6();
	else if (strcmp(string, "danrer7") == 0)
		genome = danRer7();
	else if (strcmp(string, "dm2") == 0)
		genome = dm2();
	else if (strcmp(string, "dm3") == 0)
		genome = dm3();
	else if (strcmp(string, "galgal4") == 0)
		genome = galGal4();
	else if (strcmp(string, "hg17") == 0)
		genome = hg17();
	else if (strcmp(string, "hg18") == 0)
		genome = hg18();
	else if (strcmp(string, "hg19") == 0)
		genome = hg19();
	else if (strcmp(string, "hg38") == 0)
		genome = hg38();
	else if (strcmp(string, "mm10") == 0)
		genome = mm10();
	else if (strcmp(string, "mm8") == 0)
		genome = mm8();
	else if (strcmp(string, "mm9") == 0)
		genome = mm9();
	else if (strcmp(string, "pantro4") == 0)
		genome = panTro4();
	else if (strcmp(string, "rn3") == 0)
		genome = rn3();
	else if (strcmp(string, "rn4") == 0)
		genome = rn4();
	else if (strcmp(string, "rn5") == 0)
		genome = rn5();
	else if (strcmp(string, "saccer3") == 0)
		genome = sacCer3();
	return genome;
}

void delete_genome(struct genomeInfo *genome) {
	struct genomeInfo *current, *tmp;
	HASH_ITER(hh, genome, current, tmp) {
		free(current->chrm);
		HASH_DEL(genome, current);
		free(current);
	}
}
void show_genomes() {
	fprintf(stderr, "Available genomes are: TAIR10, ce10, ce4, ce6, danRer5, danRer6, danRer7, dm2, dm3, galGal4, hg17, hg18, hg19, hg38, mm10, mm8, mm9, panTro4, rn3, rn4, rn5, sacCer3");
}