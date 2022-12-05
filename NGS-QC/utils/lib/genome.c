#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "genome.h"
#include "str_tools.h"

#define HASHSIZE 101

/* store genome chrm data */
struct chrm_entry* chrm_hashtab[HASHSIZE];
char **chrm_array;
unsigned int chrm_num;


/* hash: form hash value for string s */
unsigned int hash(char* s) {
    unsigned int hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}


struct chrm_entry* lookup_chrm(char* s) {
    struct chrm_entry* ce;
    for (ce = chrm_hashtab[hash(s)]; ce != NULL; ce = ce->next)
        if (strcmp(s, ce->name) == 0)
          return ce; /* found */
    return NULL; /* not found */
}


/* install: put (name, defn) in hashtab */
struct chrm_entry* put_chrm(char* name, unsigned long size) {
    struct chrm_entry *ce;
    unsigned int hashval;
    if ((ce = lookup_chrm(name)) == NULL) { /* not found */
        ce = (struct chrm_entry*)malloc(sizeof(*ce));
        if (ce == NULL) {
            return NULL;
        } else {
            ce->name = strdup(name);
            if (ce->name == NULL) {
                 return NULL;
            }
        }
        hashval = hash(name);
        ce->next = chrm_hashtab[hashval];
        chrm_hashtab[hashval] = ce;
    }
    ce->size = size;
    if (ce->size == 0) {
       return NULL;
    }
    ce->used = 0;
    return ce;
}


void destroy_chrm_entry(struct chrm_entry* cm) {
    free(cm->name);
    free(cm);
}


void remove_chrm(char* name) {
    struct chrm_entry* ce = NULL;
    struct chrm_entry* ceb = NULL;
    for (ce = chrm_hashtab[hash(name)]; ce != NULL; ce = ce->next)
        if (strcmp(name, ce->name) == 0) {
            if (ceb != NULL) {
                ceb->next = ce->next;
            }
            destroy_chrm_entry(ce);
            return;
        }
        ceb = ce;
    return;
}


void destroy_chrm_entry_hash() {
    struct chrm_entry* tmp;
    struct chrm_entry* next;
    for (int i = 0; i < HASHSIZE; i++) {
        tmp = chrm_hashtab[i];
        while(tmp != NULL) {
            next = tmp->next;
            destroy_chrm_entry(tmp);
            tmp = next;
        }
        chrm_hashtab[i] = NULL;
    }
}


int compare(const void *a, const void *b) {
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}


//####################################################################################

void get_chrom_size(FILE* fp_genome) {

    /* max nbr of chrmosomes */
    char line[1024];
    char* chrname;
    unsigned char error = 0;
    int i = 0;
    char* token;
    char* ssize;
    unsigned long int size;
    extern int errno;

    char chrm_arr_tmp[100][64];
    
    while(fgets(line, 1024, fp_genome) != NULL)    {
        if (line[0] != '\n' && line[1] != '\n') {
            token = strtok(line,"\t");
            if (token == NULL || strlen(token) == 0) {
                error = 1;
                break;
            }
            chrname = strdup(token);

            token = strtok(NULL,"\t");
            if (token == NULL || strlen(token) == 0) {
                error = 1;
                break;
            }

            size = strtoul(token, &ssize, 10);
            trim_space(token);

            if (errno == ERANGE || (errno != 0 && size == 0)) {
                error = 1;
                break;
            }
            if (ssize == token) {
                error = 1;
                break;
            }
            if (*ssize != '\0' && *ssize != '\n') {
                error = 1;
                break;
            }
            if (size < 1) {
                error = 1;
                break;
            }

            if (put_chrm(chrname, size) == NULL) {
                error = 1;
                break;
            }
            strcpy(chrm_arr_tmp[i], chrname);
            i++;
        }
    }

    chrm_array = malloc(i * sizeof(char*));
    for (int k = 0; k < i; k++) {
        chrm_array[k] = strdup(chrm_arr_tmp[k]);
    }
    chrm_num = i;

    qsort(chrm_array, chrm_num, sizeof(char *), compare);

    if (error == 1 || i == 0) {
        fprintf(stderr, "Error: cannot read chromosome information, the assembly file seems to be invalid.\n\
Are you sure the file is tab-delimited?\n");
        fclose(fp_genome);
        exit(1);
    }

    return;
}



void fill_used_chrm(char* chrm_used) {

    char* ptrend;
    char* sub_ptrend;
    char* strtolptr;
    char token[1024] = "";
    char chrname[256] = "";
    int lenptr;
    int sub_lenptr;
    int i = 0;
    unsigned long size = 0;
    extern int errno;

    while ((ptrend = strchr (chrm_used, ',')) != NULL) {
        lenptr = ptrend-chrm_used;
        if (lenptr == 0) {
            chrm_used++;
            continue;
        }

        if (lenptr > 1024)
            lenptr = 1024;
        
        strncpy(token, chrm_used, lenptr);
        token[lenptr] = '\0';

        sub_ptrend = strchr(token, ':');
        //printf("sub_ptrend: -%s-\n", sub_ptrend);
        if (sub_ptrend == NULL) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        sub_lenptr = sub_ptrend-token;
        if (sub_lenptr == 0) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        strncpy(chrname, token, sub_lenptr);
        chrname[sub_lenptr] = '\0';
        trim_space(chrname);
        if (strlen(chrname) == 0) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        sub_ptrend++;
        if (strlen(sub_ptrend) == 0) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        size = strtoul(sub_ptrend, &strtolptr, 10);

        if (errno == ERANGE || (errno != 0 && size == 0)) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }
        if (sub_ptrend == strtolptr) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }
        if (*strtolptr != '\0') {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }
        if (size < 1) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        if (put_chrm(chrname, size) == NULL) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }
        chrm_used = ptrend+1;
        i++;
    }

    if (strlen(chrm_used) > 0) {
        lenptr = strlen(chrm_used);
        strncpy(token, chrm_used, lenptr);
        token[lenptr] = '\0';
        sub_ptrend = strchr(token, ':');
        if (sub_ptrend == NULL) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        sub_lenptr = sub_ptrend-token;
        if (sub_lenptr == 0) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        strncpy(chrname, token, sub_lenptr);
        chrname[sub_lenptr] = '\0';
        trim_space(chrname);
        if (strlen(chrname) == 0) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        sub_ptrend++;
        if (strlen(sub_ptrend) == 0) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        size = strtoul(sub_ptrend, &strtolptr, 10);

        if (errno == ERANGE || (errno != 0 && size == 0)) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }
        if (sub_ptrend == strtolptr) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }
        if (*strtolptr != '\0') {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }
        if (size < 1) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }

        if (put_chrm(chrname, size) == NULL) {
            fprintf(stderr, "Error: invalid chromosome string.\n\n");
            exit(1);
        }
        i++;
    }

    if (i == 0) {
        fprintf(stderr, "Error: empty chromosome used string.\n\n");
        exit(1);
    }

    return;
}

