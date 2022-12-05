#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "sort.h"
#include "../lib/genome.h"
#include "../lib/str_tools.h"

#define HASHSIZE 101
struct s_bed_chrm* bed_chrm_hash[HASHSIZE];
extern struct chrm_entry* chrm_hashtab[HASHSIZE];
extern char **chrm_array;
extern unsigned int chrm_num;
//unsigned char recur_level = 0;


/*void print_buffer(struct s_bed_line* head) {
    struct s_bed_line* row_tmp = head;
    printf("stderr,line content: \n");
    while(row_tmp != NULL) {
        fprintf(stderr,"%ld\t%ld\t%c\n", row_tmp->start_pos, row_tmp->end_pos, row_tmp->strand);
        row_tmp = row_tmp->next;
    }
    printf("\n");
}*/


/*void print_chrinfo(struct s_bed_chrm* bc) {
    fprintf(stderr, "Chrm info:\n");
    fprintf(stderr, "Chrm name: %s\n", bc->chrom);
    fprintf(stderr, "Line count: %d\n", bc->line_nbr);
    //print_buffer(bc->head_array);
}*/


struct s_bed_line* add_line(unsigned long start_pos, unsigned long end_pos, unsigned char strand) {
    struct s_bed_line* new_line_data = (struct s_bed_line*)malloc(sizeof(struct s_bed_line));
    if (new_line_data == NULL) {
        fprintf(stderr, "Error: cannot store BED line data.\n");
        exit(1);
    }
    new_line_data->next = NULL;
    new_line_data->start_pos = start_pos;
    new_line_data->end_pos = end_pos;
    new_line_data->strand = strand;
    return new_line_data;
}


void destroy_line_data(struct s_bed_line* ld) {
    ld->next = NULL;
    free(ld);
    ld = NULL;
}


void destroy_chrm_bed_entry(struct s_bed_chrm* bc) {
    free(bc->chrom);
    bc->array_line = NULL;
    if (bc->head_array != NULL) {
        struct s_bed_line* current_bl = bc->head_array;
        struct s_bed_line* next;
        while (current_bl != NULL) {
            next = current_bl->next;
            destroy_line_data(current_bl);
            current_bl = next;
        }
    }
    free(bc);
}


struct s_bed_chrm* lookup_bed_chrm(char* s) {
    struct s_bed_chrm* bc;
    for (bc = bed_chrm_hash[hash(s)]; bc != NULL; bc = bc->next)
        if (strcmp(s, bc->chrom) == 0)
          return bc; /* found */
    return NULL; /* not found */
}


struct s_bed_chrm* put_bed_chrm(char* name) {
    struct s_bed_chrm *bc;
    unsigned int hashval;
    if ((bc = lookup_bed_chrm(name)) == NULL) { /* not found */
        bc = (struct s_bed_chrm*)malloc(sizeof(*bc));
        bc->head_array = NULL;
        bc->array_line = NULL;
        if (bc == NULL) {
            return NULL;
        } else {
            bc->chrom = strdup(name);
            if (bc->chrom == NULL) {
                 return NULL;
            }
        }
        hashval = hash(name);
        bc->next = bed_chrm_hash[hashval]; // ????
        bed_chrm_hash[hashval] = bc;
    } else { /* already there */
        if (bc->head_array != NULL) {
            struct s_bed_line* current_bl = bc->head_array;
            struct s_bed_line* next;
            while (current_bl != NULL) {
                next = current_bl->next;
                destroy_line_data(current_bl);
                current_bl = next;
            }
        }
    }
    bc->line_nbr = 0;
    return bc;
}


void destroy_chrm_bed_entry_hash() {
    struct s_bed_chrm* tmp;
    struct s_bed_chrm* next;
    for (int i = 0; i < HASHSIZE; i++) {
        tmp = bed_chrm_hash[i];
        while(tmp != NULL) {
            next = tmp->next;
            destroy_chrm_bed_entry(tmp);
            tmp = next;
        }
        bed_chrm_hash[i] = NULL;
    }
}



int cmp(struct s_bed_line* a, struct s_bed_line* b) {
    int res = a->start_pos - b->start_pos;
    return res == 0 ? a->strand - b->strand : res;
    //if (res == 0)
    //    return a->strand - b->strand;
    //return res;
}

/*
 * This is the actual sort function. Notice that it returns the new
 * head of the list. (It has to, because the head will not
 * generally be the same element after the sort.) So unlike sorting
 * an array, where you can do
 * 
 *     sort(myarray);
 * 
 * you now have to do
 * 
 *     list = listsort(mylist);
 */
struct s_bed_line* listsort(struct s_bed_line* list) {

    struct s_bed_line *p, *q, *e, *tail;
    int insize, nmerges, psize, qsize, i;

    /*
     * Silly special case: if `list' was passed in as NULL, return
     * NULL immediately.
     */

    if (!list)
        return NULL;

    insize = 1;

    while (1) {
        p = list;
        list = NULL;
        tail = NULL;

        nmerges = 0;  /* count number of merges we do in this pass */

        while (p) {
            nmerges++;  /* there exists a merge to be done */
            //fprintf(stderr, "nmerges %d\n", nmerges);
            /* step `insize' places along from p */
            q = p;
            psize = 0;
            for (i = 0; i < insize; i++) {
                psize++;
                q = q->next;
                if (!q) break;
            }

            /* if q hasn't fallen off end, we have two lists to merge */
            qsize = insize;

            /* now we have two lists; merge them */
            while (psize > 0 || (qsize > 0 && q)) {
                /* decide whether next element of merge comes from p or q */
                if (psize == 0) {
                    /* p is empty; e must come from q. */
                    e = q; q = q->next; qsize--;
                } else if (qsize == 0 || !q) {
                    /* q is empty; e must come from p. */
                    e = p; p = p->next; psize--;
                } else if (cmp(p,q) <= 0) {
                    /* First element of p is lower (or same);
                     * e must come from p. */
                    e = p; p = p->next; psize--;
                } else {
                    /* First element of q is lower; e must come from q. */
                    e = q; q = q->next; qsize--;
                }
                /* add the next element to the merged list */
                if (tail) {
                    tail->next = e;
                } else {
                    list = e;
                }
                tail = e;
            }
            /* now p has stepped `insize' places along, and q has too */
            p = q;
        }
        tail->next = NULL;

        /* If we have done only one merge, we're finished. */
        if (nmerges <= 1)   /* allow for nmerges==0, the empty list case */
            return list;

        /* Otherwise repeat, merging lists twice the size */
        insize *= 2;
    }
}


void *pool_sort_bed(void *x) {
    struct s_thread_job job;
    struct s_bed_chrm* bc;
    job = *((struct s_thread_job *) x);

    //fprintf(stderr, "Hi from thread %d!\n", job.thread_id);

    for (unsigned int j = 0; j < chrm_num && job.index_chrm_to_sort[j] != -1; j++) {
        bc = bed_chrm_hash[job.index_chrm_to_sort[j]];
        bc->head_array = listsort(bc->head_array);
    }

    return NULL;
}


void sort_bed(unsigned char core_nb) {
    //struct s_bed_line* bl;

    struct s_bed_chrm* bc;
    //int j = 0;

    unsigned char nbr_threads = core_nb;
    pthread_t threads[nbr_threads];
    int thread_do_job, rc;
    unsigned int k = 0;

    unsigned long min_line_to_process = 0;

    //fprintf(stderr, "core_nb %d\n", core_nb);
    //fprintf(stderr, "nbr_threads %d\n", nbr_threads);
    if (nbr_threads == 1) {
        //fprintf(stderr, "test\n");
        for (int i = 0; i < HASHSIZE; i++) {
            if (bed_chrm_hash[i] != NULL && bed_chrm_hash[i]->line_nbr > 1) {
                //fprintf(stderr, "%ld\n", bed_chrm_hash[i]->line_nbr);
                bc = bed_chrm_hash[i];
                bc->head_array = listsort(bc->head_array);
            }
        }
    } else {
        struct s_thread_job list_jobs[nbr_threads];
        for (int i = 0; i < nbr_threads; i++) {
            list_jobs[i].thread_id = i+1;
            list_jobs[i].index_chrm_to_sort = malloc(sizeof(int) * chrm_num);
            for (unsigned int j = 0; j < chrm_num; j++)
                list_jobs[i].index_chrm_to_sort[j] = -1;
            list_jobs[i].nbr_line_to_sort = 0;
        }

        for (int i = 0; i < HASHSIZE; i++) {
            if (bed_chrm_hash[i] != NULL && bed_chrm_hash[i]->line_nbr > 1) {
                //print_chrinfo(bed_chrm_hash[i]);
                for (int j = 0; j < nbr_threads; j++) {
                    if (list_jobs[j].nbr_line_to_sort == 0) {
                        thread_do_job = j;
                        break;
                    } else {
                        if (j == 0) {
                            min_line_to_process = list_jobs[j].nbr_line_to_sort;
                            thread_do_job = j;
                        } else {
                            if (min_line_to_process > list_jobs[j].nbr_line_to_sort) {
                                min_line_to_process = list_jobs[j].nbr_line_to_sort;
                                thread_do_job = j;
                            }
                        }
                    }
                }

                //fprintf(stderr, "i = %d, thread_do_job = %d\n", i ,thread_do_job);
                list_jobs[thread_do_job].nbr_line_to_sort += bed_chrm_hash[i]->line_nbr;
                for (k = 0; k < chrm_num && list_jobs[thread_do_job].index_chrm_to_sort[k] != -1; k++);
                    list_jobs[thread_do_job].index_chrm_to_sort[k] = i;
            }
        }


        //for (int j = 0; j < nbr_threads; j++) {
            //fprintf(stderr, "thread #%d\n", list_jobs[j].thread_id);
            //for (unsigned int i = 0; i < chrm_num; i++) {
                //if (list_jobs[j].index_chrm_to_sort[i] != -1)
                    //fprintf(stderr, "%d |", list_jobs[j].index_chrm_to_sort[i]);
            //}
            //fprintf(stderr, "\n");
            //fprintf(stderr, "line to process #%ld\n", list_jobs[j].nbr_line_to_sort);
        //}

        for (k = 0; k < nbr_threads; k++) {
            rc = pthread_create(&threads[k], NULL, pool_sort_bed, (void *)&list_jobs[k]);
        }

        /* wait for threads to finish */
        for (k = 0; k < nbr_threads; k++) {
            rc = pthread_join(threads[k], NULL);
        }

        if (rc) {
        }
    }
    return;
}



void write_bed(FILE* fp_out) {
    struct s_bed_chrm* bc;
    struct s_bed_line* p;

    for (unsigned int i = 0; i < chrm_num; i++) {
        bc = lookup_bed_chrm(chrm_array[i]);
        if (bc != NULL && bc->line_nbr != 0) {
            //fprintf(stderr, "%s | %s | %d ------\n", chrm_array[i], bc->chrom, bc->line_nbr);
            p = bc->head_array;
            while (p != NULL) {
                //j++;
                fprintf(fp_out, "%s\t%ld\t%ld\tt\t0\t%c\n", chrm_array[i], p->start_pos, p->end_pos, p->strand);
                p = p->next;
            }
            //fprintf(stderr, "%s | %s |%d------\n", chrm_array[i], bc->chrom, j);
        }
    }
}


void split_bed_file(FILE* fp_in, FILE* fp_out, unsigned char core_nb, unsigned char no_header) {

    char line[1024];

    char* ptr;
    char* ptrend;
    int lenptr;

    char chrname[32] = "";
    unsigned char strand;

    unsigned long start, end;

    char token[32] = "";

    struct s_bed_chrm* bc;
    //struct s_bed_line* bl;
    struct s_bed_line* cur;
    /* copy the chromosome hash to the bed_chrm hash*/
    struct chrm_entry* tmp;
    for (int i = 0; i < HASHSIZE; i++) {
        tmp = chrm_hashtab[i];
        while(tmp != NULL) {
            //printf("%s\n", tmp->name);
            bc = put_bed_chrm(tmp->name);
            if (bc == NULL) {
                fprintf(stderr, "Error: cannot create hash for chromosomes.\n");
                exit(1);
            }
            tmp = tmp->next;
        }
    }

    //printf("-----\n");

    /* struct s_bed_chrm* tmp2;
    for (int i = 0; i < HASHSIZE; i++) {
        tmp2 = bed_chrm_hash[i];
        while(tmp2 != NULL) {
            //printf("%s\n", tmp2->chrom);
            tmp2 = tmp2->next;
        }
    } */

    //printf("start read file\n");
    //fprintf(stderr, " start parse\n");

    while(fgets(line, 1024, fp_in) != NULL) {
        //printf("%s", line);
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        } else if (no_header || (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0)) {
            ptr = line;
            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(chrname, ptr, lenptr);
            chrname[lenptr] = '\0';
            ptr = ptrend+1;

            if ((bc = lookup_bed_chrm(chrname)) == NULL) {
                //fprintf(stderr,"continue -- \n");
                continue;
            }

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            start = atol(token);
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            end = atol(token);

            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            ptr = ptrend+1;
            ptrend = strchr(ptr, '\t');
            if (ptrend == NULL) {
                if (*ptr == '+') {
                    strand = '+';
                } else {
                    strand = '-';
                }
            } else {
                lenptr = ptrend-ptr;
                strncpy(token, ptr, lenptr);
                token[lenptr] = '\0';
                if (token[0] == '+') {
                    strand = '+';
                } else {
                    strand = '-';
                }
            }

            //printf("TEST0\n");



            //printf("TEST1\n");
            cur = bc->array_line;
            bc->array_line = add_line(start, end, strand);

            if (bc->line_nbr != 0) {
                cur->next = bc->array_line;
                //bl = cur;
            } else {
                //fprintf(stderr,"chrom %s 0 line\n", bc->chrom);
                bc->head_array = bc->array_line;
                //bl = bc->head_array;
            }
            bc->line_nbr++;

        }
    }

    //fprintf(stderr, " start sort\n");

    sort_bed(core_nb);

    //fprintf(stderr, " start write\n");

    write_bed(fp_out);

    destroy_chrm_bed_entry_hash();

    return;
}

