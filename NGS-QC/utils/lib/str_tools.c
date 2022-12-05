#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <errno.h>
#include <string.h>

/* duplicate string */
char* strdup(char* s) {
    char* p;
    p = (char*) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
       strcpy(p, s);
    return p;
}

/* trim string */
void trim_space(char* source) {
    char* i = source;
    char* j = source;
    while(*j != 0) {
        *i = *j++;
        if(*i != ' ')
            i++;
    }
    *i = 0;
}


void remove_trailing_zero(char *s) {
    char *p;
    p = s+strlen(s)-1;
    while (*p == '0')
        *p-- = '\0';
    if (*p == '.')
        *p = '\0';
}


float get_float_arg(char* numerical_string, float min, float max) {
    char* endptr;
    float f;

    f = strtof(numerical_string, &endptr);
    
    if ((errno == ERANGE && (f == FLT_MAX || f == FLT_MIN))
           || (errno != 0 && f == 0)) {
        errno = 42;
    } else {
        if (endptr == numerical_string) {
            errno = 42;
        } else if (*endptr != '\0') {
            errno = 42;
        } else {
            if (f < min || f > max)
                errno = 42;
        }
    }

    return f;
}


int get_int_arg(char* numerical_string, int min, int max) {
    char* endptr;
    long v;

    v = strtol(numerical_string, &endptr, 10);
        
    if ((errno == ERANGE && (v == INT_MAX || v == INT_MIN))
           || (errno != 0 && v == 0)) {
        errno = 42;
    } else {
        if (endptr == numerical_string) {
            errno = 42;
        } else if (*endptr != '\0') {
            errno = 42;
        } else {
            if (v < min || v > max)
                errno = 42;
        }
    }

    return v;
}


unsigned long get_bedline_count(FILE* fp) {
    char line[1024];
    unsigned long read_count = 0;

    while(fgets(line, 1024, fp) != NULL) {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        }
        if (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0) {
            read_count++;
        }
    }
    return read_count;
}

