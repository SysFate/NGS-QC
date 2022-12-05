

void compute_indicators(FILE* fp_in,
                        FILE* fp_out,
                        unsigned int threshold,
                        char* samtable,
                        char* bedtrack,
                        char* wigtrack,
                        unsigned char memory);


void compute_indicators_replicate(FILE* fp_in,
                        FILE* fp_out,
                        unsigned int threshold,
                        unsigned char rep_number,
                        unsigned char valid_rep);
