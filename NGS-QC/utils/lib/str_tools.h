
char* strdup(char* s);

void trim_space(char* source);

void remove_trailing_zero(char *s);

float get_float_arg(char* numerical_string, float min, float max);

int get_int_arg(char* numerical_string, int min, int max);

unsigned long get_bedline_count(FILE* fp);
