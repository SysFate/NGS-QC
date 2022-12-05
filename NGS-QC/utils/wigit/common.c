#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


int chop_by_space(char *in, char *outArray[], int outSize) {
    int recordCount = 0;
    char c;
    for (;;) {
        if (outArray != NULL && recordCount >= outSize)
            break;

        /* Skip initial separators. */
        while (isspace(*in)) ++in;
        if (*in == 0)
            break;

        /* Store start of word and look for end of word. */
        if (outArray != NULL)
            outArray[recordCount] = in;
        recordCount += 1;
        for (;;) {
            if ((c = *in) == 0)
                break;
            if (isspace(c))
                break;
            ++in;
        }
        if (*in == 0)
            break;

        /* Tag end of word with zero. */
        if (outArray != NULL)
            *in = 0;
        /* And skip over the zero. */
        in += 1;
    }
    return recordCount;
}

FILE *try_open(char *path, char *mode) {
    FILE *f;
    
    if (equals(path, "-"))
        return stdin;
    if ((f = fopen(path, mode)) == NULL) {
        fprintf(stderr, "No such file %s\n", path);
        exit(1);
    }
    return f;
}

long tolong(char *string) {
    char *ptr;
    long value;
    
    value = strtol(string, &ptr, 10);
    if (ptr == string) {
        fprintf(stderr, "Invalid: requires an integer\n");
        exit(1);
    }
    return value;
}

char *lower(char *string) {
    char c;
    char *substring = string;
    for (;;) {
        if ((c = *substring) == 0) break;
        *substring++ = tolower(c);
    }
    return string;
}

void rtrim(char *str) {
    /**
     * 
     * @param str
     */
    size_t n;
    n = strlen(str);
    while (n > 0 && isspace((unsigned char)str[n - 1])) {
        n--;
    }
    str[n] = '\0';
}
 
void ltrim(char *str) {
    /**
     * 
     * @param str
     */
    size_t n;
    n = 0;
    while (str[n] != '\0' && isspace((unsigned char)str[n])) {
        n++;
    }
    memmove(str, str + n, strlen(str) - n + 1);
}
 
void trim(char *str) {
    /**
     * 
     * @param str
     */
    rtrim(str);
    ltrim(str);
}

void strupper(char *string) {
    /**
     * 
     * @param string
     */
    int i = 0;
    while (string[i]) {
        string[i] = toupper(string[i]);
        ++i;
    }
}