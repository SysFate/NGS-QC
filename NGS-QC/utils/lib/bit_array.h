
typedef unsigned char bit;

/* struct used for bit arrays*/
struct s_array_ba {
    bit* ba1;
    bit* ba2;
    bit* ba3;
};

/* struct of 3 bit arrays */
struct s_array_ba* array_ba;

/* up to 10 replicates */
struct s_array_ba* rep_array_ba[10];

void destroy_array_ba();

void destroy_rep_array_ba();

bit* build_bit_array(bit* bit_array, unsigned long n);

bit test_bit(bit arr[], unsigned long n);

void change_bit(bit arr[], unsigned long elem, int value);

void get_sampling_line_index(unsigned long total_reads, const int* sampling_array);

void get_sampling_line_index_rep(unsigned long total_reads, const int* sampling_array, unsigned char rep_number);
