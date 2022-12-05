
struct s_bed_line {
    unsigned long start_pos;
    unsigned long end_pos;
    unsigned char strand;
    struct s_bed_line* next;
} bed_line;


struct s_bed_chrm {
    char* chrom;
    unsigned int line_nbr;
    struct s_bed_line* head_array;
    struct s_bed_line* array_line;
    struct s_bed_chrm* next;
} bed_chrm;


struct s_thread_job {
    unsigned char thread_id;
    int* index_chrm_to_sort;
    unsigned long nbr_line_to_sort;
} thread_job;


void print_buffer(struct s_bed_line* head);

void print_chrinfo(struct s_bed_chrm* bc);

struct s_bed_line* add_line(unsigned long start_pos, unsigned long end_pos, unsigned char strand);

void destroy_line_data(struct s_bed_line* ld);

void destroy_chrm_bed_entry(struct s_bed_chrm* bc);

struct s_bed_chrm* lookup_bed_chrm(char* s);

struct s_bed_chrm* put_bed_chrm(char* name);

void destroy_chrm_bed_entry_hash();

void split_bed_file(FILE* fp_in, FILE* fp_out, unsigned char core_nb, unsigned char no_header);

int cmp(struct s_bed_line* a, struct s_bed_line* b);

struct s_bed_line* listsort(struct s_bed_line* list);

