#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bin_table.h"
#include "../lib/str_tools.h"
#include "../lib/genome.h"
#include "../lib/bit_array.h"
#include "plot_bin_table.h"


struct nlist {
    char* name;
    struct nlist* next;
};


/* bin_table (linked list) */
struct s_bin_table* bt;


/* hash for QC coordinate (plot) */
struct nlist* coor_hashtab[20000000];


void destroy_bin_table() {
    struct s_table_row* rows = bt->head;
    struct s_table_row* tmp;
    while (rows != NULL) {
        tmp = rows->next;
        rows->next = NULL;
        free(rows->chr);
        free(rows);
        rows = tmp;
    }
    /*for (size_t i = 0; i < bt->size; i++) {
        //printf("%zd\n", i);
        //printf("%zd\n", sizeof(rows[i]));
        free((&rows[i])->chr);
        //free(&rows[i]);
    }*/
    free(bt);
}


table_row* add_bin_table_row(table_row* current_row,
                                      char* chrname,
                                      unsigned long start,
                                      unsigned long end,
                                      unsigned int v100,
                                      unsigned int v90,
                                      unsigned int v70,
                                      unsigned int v50) {

    table_row* new_row = malloc(sizeof(struct s_table_row));
    if (new_row == NULL) {
        fprintf(stderr, "Error: cannot allocate memory block for the bin table.\n");
        destroy_array_ba();
        destroy_bin_table();
        exit(1);
    }
    new_row->next = NULL;
    new_row->chr = chrname;
    new_row->start = start;
    new_row->end = end;
    new_row->v100 = v100;
    new_row->v90 = v90;
    new_row->v70 = v70;
    new_row->v50 = v50;
    if (current_row != NULL) {
        current_row->next = new_row;
    }

    return new_row;
}

// ##################################################################################3
// hash coordinate plot

/* hash: form hash value for string s */
unsigned int hash_coor(char* s) {
    unsigned int hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % 20000000;
}


/* lookup: look for s in hashtab */
struct nlist* lookup(char* s) {
    struct nlist *np;
    for (np = coor_hashtab[hash_coor(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          return np; /* found */
    return NULL; /* not found */
}


/* install: put (name, defn) in hashtab */
struct nlist* put(char* name) {
    struct nlist* np;
    unsigned int hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist*)malloc(sizeof(*np));
        if (np == NULL) {
            return NULL;
        } else {
            np->name = strdup(name);
            if (np->name == NULL) {
                 return NULL;
            }
        }
        hashval = hash_coor(name);
        np->next = coor_hashtab[hashval];
        coor_hashtab[hashval] = np;
    }
    return np;
}


void destroy_coor_hash() {
    struct nlist* tmp;
    struct nlist* next;
    for (int i = 0; i < 20000000; i++) {
        tmp = coor_hashtab[i];
        while(tmp != NULL) {
            next = tmp->next;
            free(tmp->name);
            free(tmp);
            tmp = next;
        }
        coor_hashtab[i] = NULL;
    }
}

//####################################################################################


void read_bin_table(FILE* fp_in) {
    char line[1024];

    char* ptr;
    char* ptrend;
    int lenptr;

    long start_pos;
    long end_pos;
    unsigned int s100;
    unsigned int s90;
    unsigned int s70;
    unsigned int s50;

    char chrname[128] = "";
    char token[128] = "";


    struct s_table_row* row_tmp;

    //create the big table in memory
    bt = malloc(sizeof(struct s_bin_table));
    bt->size = 0;

    while(fgets(line, 1024, fp_in) != NULL) {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        }

        ptr = line;
        ptrend = strchr(ptr, '\t');
        lenptr = ptrend-ptr;
        strncpy(chrname, ptr, lenptr);
        chrname[lenptr] = '\0';

        ptr = ptrend+1;

        ptrend = strchr(ptr, '\t');
        lenptr = ptrend-ptr;
        strncpy(token, ptr, lenptr);
        token[lenptr] = '\0';
        start_pos = atol(token);
        if (start_pos < 0) {
            start_pos = 0;
        }
        ptr = ptrend+1;

        ptrend = strchr(ptr, '\t');
        lenptr = ptrend-ptr;
        strncpy(token, ptr, lenptr);
        token[lenptr] = '\0';
        end_pos = atol(token);

        ptr = ptrend+1;

        ptrend = strchr(ptr, '\t');
        lenptr = ptrend-ptr;
        strncpy(token, ptr, lenptr);
        token[lenptr] = '\0';
        s100 = atol(token);

        ptr = ptrend+1;

        ptrend = strchr(ptr, '\t');
        lenptr = ptrend-ptr;
        strncpy(token, ptr, lenptr);
        token[lenptr] = '\0';
        s90 = atol(token);

        ptr = ptrend+1;

        ptrend = strchr(ptr, '\t');
        lenptr = ptrend-ptr;
        strncpy(token, ptr, lenptr);
        token[lenptr] = '\0';
        s70 = atol(token);

        ptr = ptrend+1;

        ptrend = strchr(ptr, '\n');
        lenptr = ptrend-ptr;
        strncpy(token, ptr, lenptr);
        token[lenptr] = '\0';
        s50 = atol(token);

        //add elem to the bin table
        row_tmp = bt->rows;
        bt->rows = add_bin_table_row(row_tmp,
                                     strdup(chrname),
                                     start_pos,
                                     end_pos,
                                     s100,
                                     s90,
                                     s70,
                                     s50);

        if (bt->size == 0) {
            bt->head = bt->rows;
        }
        bt->size++;

        //printf("%s %ld %ld %d %d %d %d\n", chrname, start_pos, end_pos, s100, s90, s70, s50);
        //printf("-%d-\n", s50);

    }

    return;
}


void build_bin_table(FILE* fp_in,
                     FILE* fp_out,
                     unsigned int window_size,
                     unsigned char store_table,
                     unsigned char no_header) {
    char line[1024];

    char* ptr;
    char* ptrend;
    int lenptr;

    long start_pos;
    long end_pos;
    unsigned long start_window;
    unsigned long end_window;
    unsigned long start_pos_window;
    unsigned long end_pos_window;
    unsigned long line_nb = 0;

    char chrname[128] = "";
    char token[128] = "";
    char current_chrm[128] = "";
    unsigned long current_chrm_size = 0;
    unsigned int last_index = 0, i = 0;

    int* current_array_pos_s100 = NULL;
    int* current_array_pos_s50 = NULL;
    int* current_array_pos_s70 = NULL;
    int* current_array_pos_s90 = NULL;


    struct s_table_row* row_tmp;
    //create the big table in memory
    //Table_row* array_bt = malloc(bin_table_size * sizeof(Table_row));
    bt = malloc(sizeof(struct s_bin_table));
    bt->head = NULL;
    bt->size = 0;
    //struct s_table_row* array_bt = malloc(bin_table_size * sizeof(struct s_table_row));
    //struct s_table_row* array_bt = bt->head;

    while(fgets(line, 1024, fp_in) != NULL) {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        } else if (no_header || (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0)) {
            //printf("%s\n", line);
            ptr = line;
            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(chrname, ptr, lenptr);
            chrname[lenptr] = '\0';

            ++line_nb;
            //ignore line with unwanted chrm

            if (lookup_chrm(chrname) == NULL) {
                continue;
            }
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            start_pos = atol(token);
            if (start_pos < 0) {
                start_pos = 0;
            }
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            end_pos = atol(token) - 1;

            if (strcmp(chrname, current_chrm) == 0) {

                start_window = start_pos / window_size;
                if (start_window > last_index) {
                    fprintf(stderr, "Error: Coordinate out of bound: %s\t%ld.\n", chrname, start_pos);
                    destroy_array_ba();
                    //destroy_chrm_entry_hash();
                    //fprintf(stderr, "test1\n");
                    //fprintf(stderr, "bt-size = %d\n", bt->size);
                    destroy_bin_table();
                    destroy_coor_hash();
                    if (current_array_pos_s100 != NULL) {
                        free(current_array_pos_s100);
                        free(current_array_pos_s50);
                        free(current_array_pos_s70);
                        free(current_array_pos_s90);
                    }
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }
                end_window = end_pos / window_size;
                if (end_window > last_index) {
                    end_window = last_index;
                }

                current_array_pos_s100[start_window] += 1;
                if (!test_bit(array_ba->ba1, line_nb)) {
                    current_array_pos_s50[start_window] += 1;
                }
                if (!test_bit(array_ba->ba2, line_nb)) {
                    current_array_pos_s70[start_window] += 1;
                }
                if (!test_bit(array_ba->ba3, line_nb)) {
                    current_array_pos_s90[start_window] += 1;
                }
                if (start_window != end_window) {
                    current_array_pos_s100[end_window] += 1;
                    if (!test_bit(array_ba->ba1, line_nb)) {
                        current_array_pos_s50[end_window] += 1;
                    }
                    if (!test_bit(array_ba->ba2, line_nb)) {
                        current_array_pos_s70[end_window] += 1;
                    }
                    if (!test_bit(array_ba->ba3, line_nb)) {
                        current_array_pos_s90[end_window] += 1;
                    }
                }
            } else {
                //printf("%s\t%ld\n", current_chrm, start_pos);
                if (strncmp(current_chrm, "", 1) != 0) {
                    //printf("last index: %d\n", last_index);
                    //printf("last bin: %d\n", last_index * window_size);
                    //printf("crash bin: chr12\t128325500\n");

                    for (i = 0; i < last_index + 1; i++) {
                        int v = current_array_pos_s100[i];
                        if (v != 0) {
                            start_pos_window = i * window_size;

                            if (i == last_index) {
                                end_pos_window = current_chrm_size;
                            } else {
                                end_pos_window = start_pos_window + window_size;
                            }
                            //add elem to the bin table
                            if (store_table) {
                                row_tmp = bt->rows;
                                bt->rows = add_bin_table_row(row_tmp,
                                                             strdup(current_chrm),
                                                             start_pos_window,
                                                             end_pos_window,
                                                             v,
                                                             current_array_pos_s90[i],
                                                             current_array_pos_s70[i],
                                                             current_array_pos_s50[i]);

                                if (bt->size == 0) {
                                    bt->head = bt->rows;
                                }
                                bt->size++;
                            }

                            fprintf(fp_out, "%s\t%ld\t%ld\t%d\t%d\t%d\t%d\n",
                                current_chrm, start_pos_window, end_pos_window,
                                v, current_array_pos_s90[i], current_array_pos_s70[i], current_array_pos_s50[i]);
                        }
                    }
                }
                //printf("test2\n");
                strcpy(current_chrm, chrname);
                current_chrm_size = lookup_chrm(chrname)->size;
                if (current_array_pos_s100 != NULL) {
                    free(current_array_pos_s100);
                    free(current_array_pos_s50);
                    free(current_array_pos_s70);
                    free(current_array_pos_s90);
                }
                //printf("test3\n");
                //printf("ccs: %ld\n", (current_chrm_size / window_size) + 1);
                last_index = current_chrm_size / window_size;
                current_array_pos_s100 = calloc((last_index + 1), sizeof(int));
                if (current_array_pos_s100 == NULL) {
                    fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s100.\n");
                    destroy_array_ba();
                    //destroy_chrm_entry_hash();
                    destroy_bin_table();
                    destroy_coor_hash();
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }
                current_array_pos_s50 = calloc((last_index + 1), sizeof(int));
                if (current_array_pos_s50 == NULL) {
                    fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s50.\n");
                    destroy_array_ba();
                    //destroy_chrm_entry_hash();
                    destroy_bin_table();
                    destroy_coor_hash();
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }
                current_array_pos_s70 = calloc((last_index + 1), sizeof(int));
                if (current_array_pos_s70 == NULL) {
                    fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s70.\n");
                    destroy_array_ba();
                    //destroy_chrm_entry_hash();
                    destroy_bin_table();
                    destroy_coor_hash();
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }
                current_array_pos_s90 = calloc((last_index + 1), sizeof(int));
                if (current_array_pos_s90 == NULL) {
                    fprintf(stderr, "Error: cannot allocate memory block for current_array_pos_s90.\n");
                    destroy_array_ba();
                    //destroy_chrm_entry_hash();
                    destroy_bin_table();
                    destroy_coor_hash();
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }

                //add this line to the bin table
                start_window = start_pos / window_size;
                if (start_window > last_index) {
                    fprintf(stderr, "Error: Coordinate out of bound: %s\t%ld.\n", chrname, start_pos);
                    destroy_array_ba();
                    //destroy_chrm_entry_hash();
                    destroy_bin_table();
                    destroy_coor_hash();
                    if (current_array_pos_s100 != NULL) {
                        free(current_array_pos_s100);
                        free(current_array_pos_s50);
                        free(current_array_pos_s70);
                        free(current_array_pos_s90);
                    }
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(1);
                }

                //printf("test4\n");
                end_window = end_pos / window_size;
                if (end_window > last_index) {
                    end_window = last_index;
                }

                //printf("start_pos: %ld\n", start_window);
                current_array_pos_s100[start_window] += 1;
                if (!test_bit(array_ba->ba1, line_nb)) {
                    current_array_pos_s50[start_window] += 1;
                }
                if (!test_bit(array_ba->ba2, line_nb)) {
                    current_array_pos_s70[start_window] += 1;
                }
                if (!test_bit(array_ba->ba3, line_nb)) {
                    current_array_pos_s90[start_window] += 1;
                }
                if (start_window != end_window) {
                    current_array_pos_s100[end_window] += 1;
                    if (!test_bit(array_ba->ba1, line_nb)) {
                        current_array_pos_s50[end_window] += 1;
                    }
                    if (!test_bit(array_ba->ba2, line_nb)) {
                        current_array_pos_s70[end_window] += 1;
                    }
                    if (!test_bit(array_ba->ba3, line_nb)) {
                        current_array_pos_s90[end_window] += 1;
                    }
                }
                //printf("test5\n");
            }
        }
    }

    //write the last chrmosome info if any
    if (strncmp(current_chrm, "", 1) != 0) {
        for (i = 0; i < last_index + 1; i++) {
            int v = current_array_pos_s100[i];
            if (v != 0) {
                start_pos_window = i * window_size;

                if (i == last_index) {
                    end_pos_window = current_chrm_size;
                } else {
                    end_pos_window = start_pos_window + window_size;
                }

                if (store_table) {
                    //add elem to the bin table
                    row_tmp = bt->rows;
                    bt->rows = add_bin_table_row(row_tmp,
                                                 strdup(current_chrm),
                                                 start_pos_window,
                                                 end_pos_window,
                                                 v,
                                                 current_array_pos_s90[i],
                                                 current_array_pos_s70[i],
                                                 current_array_pos_s50[i]);
                    if (bt->size == 0) {
                        bt->head = bt->rows;
                    }
                    bt->size++;
                }

                //write the table
                fprintf(fp_out, "%s\t%ld\t%ld\t%d\t%d\t%d\t%d\n",
                    current_chrm, start_pos_window, end_pos_window,
                    v, current_array_pos_s90[i], current_array_pos_s70[i], current_array_pos_s50[i]);
            }
        }
    }

    if (current_array_pos_s100 != NULL) {
        free(current_array_pos_s100);
        free(current_array_pos_s50);
        free(current_array_pos_s70);
        free(current_array_pos_s90);
    }
    destroy_array_ba();
    //destroy_chrm_entry_hash();

    return;
}


