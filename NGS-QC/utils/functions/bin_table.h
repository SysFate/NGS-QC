
typedef struct s_table_row {
    char* chr;
    unsigned long start;
    unsigned long end;
    unsigned int v100;
    unsigned int v90;
    unsigned int v70;
    unsigned int v50;
    float s90;
    float s70;
    float s50;
    float s90m;
    float s70m;
    float s50m;
    struct s_table_row* next;
} table_row;


typedef struct s_bin_table {
    struct s_table_row* rows;
    struct s_table_row* head;
    unsigned int size;
} bin_table;

void destroy_bin_table();

table_row* add_bin_table_row(table_row* current_row,
                                      char* chrname,
                                      unsigned long start,
                                      unsigned long end,
                                      unsigned int v100,
                                      unsigned int v90,
                                      unsigned int v70,
                                      unsigned int v50);

unsigned int hash_coor(char* s);

struct nlist* lookup(char* s);

struct nlist* put(char* name);

void destroy_coor_hash();

void read_bin_table(FILE* fp_in);

void build_bin_table(FILE* fp_in,
                     FILE* fp_out,
                     unsigned int window_size,
                     unsigned char store_table,
                     unsigned char no_header);

