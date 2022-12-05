
struct s_linebuffer* add_buffer_item(char* chrname, unsigned long start_pos, unsigned long end_pos, unsigned char strand);

void destroy_buffer(struct s_linebuffer* head);

void write_and_sort_extend_reads(FILE* fp_in, FILE* fp_out, unsigned int elongation_size, unsigned char no_header);
