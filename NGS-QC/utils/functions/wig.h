
struct s_region_info {
    char* chrm;
    unsigned long start;
    unsigned long end;
    unsigned char same_chr_next_region;
} region_info;

void parse_region_list(char* region_list);

void bed_to_wig(FILE* fp_in, FILE* fp_out, unsigned int window_size, unsigned int extend_size, unsigned char no_header, unsigned char wbinary);
