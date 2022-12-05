
struct chrm_entry {
    char *name; 
    unsigned long size;
    unsigned char used;
    struct chrm_entry *next;
};

unsigned int hash(char* s);

struct chrm_entry* lookup_chrm(char* s);

struct chrm_entry* put_chrm(char* name, unsigned long size);

int compare(const void *a, const void *b);

void get_chrom_size(FILE* fp_genome);

void fill_used_chrm(char* chrm_used);
