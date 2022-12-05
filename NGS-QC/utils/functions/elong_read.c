#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/genome.h"

struct s_linebuffer {
    char* chrname;
    long start_pos;
    unsigned long end_pos;
    unsigned char strand;
    struct s_linebuffer* next;
} linebuffer;


struct s_linebuffer* add_buffer_item(char* chrname, unsigned long start_pos, unsigned long end_pos, unsigned char strand) {
    struct s_linebuffer* new_item_buffer = malloc(sizeof(struct s_linebuffer));
    new_item_buffer->next = NULL;
    new_item_buffer->chrname = malloc(sizeof(char)*(strlen(chrname) + 1));
    strcpy(new_item_buffer->chrname, chrname);
    new_item_buffer->start_pos = start_pos;
    new_item_buffer->end_pos = end_pos;
    new_item_buffer->strand = strand;
     
    return new_item_buffer;
}


void destroy_buffer(struct s_linebuffer* head) {
    struct s_linebuffer* tmp_buffer_item;
    while (head != NULL) {
        tmp_buffer_item = head;
        head = head->next;
        free(tmp_buffer_item->chrname);
        free(tmp_buffer_item);
    }
    head = NULL;
}


void write_and_sort_extend_reads(FILE* fp_in, FILE* fp_out, unsigned int elongation_size, unsigned char no_header) {

    char line[1024];

    char* ptr;
    char* ptrend;
    int lenptr;

    char chrname[128] = "";
    char token[128] = "";
    char tmp_chrname[128] = "";
    char strand[2];
 
    unsigned int i;
    int line_nb;
 
    long start_pos;
    long new_start_pos;
    unsigned long end_pos, new_end_pos;
    //unsigned long chrm_size = 999999999;
    unsigned int read_length;

    struct s_linebuffer* head_buffer1 = NULL;
    struct s_linebuffer* tail_buffer1 = NULL;

    struct s_linebuffer* head_buffer2 = NULL;
    struct s_linebuffer* tail_buffer2 = NULL;

    struct s_linebuffer* tmp_buffer;

    while(fgets(line, 1024, fp_in) != NULL)    {
        if (line[0] == '\n' || line[1] == '\n') {
            continue;
        } else if (no_header || (strncmp(line, "#", 1) != 0 && strncmp(line, "track", 5) != 0 && strncmp(line, "browser", 7) != 0)) {
            //printf("%s", );
            ptr = line;
            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(chrname, ptr, lenptr);
            chrname[lenptr] = '\0';

            //ignore line with unwanted chrm
            ++line_nb;
            //if (lookup_chrm(chrname) == NULL) {
            //    continue;
            //}
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            start_pos = atol(token);
            ptr = ptrend+1;

            ptrend = strchr(ptr, '\t');
            lenptr = ptrend-ptr;
            strncpy(token, ptr, lenptr);
            token[lenptr] = '\0';
            end_pos = atol(token);

            for (i = 0; i < 3; i++) {
                ptr = ptrend+1;
                ptrend = strchr(ptr, '\t');
            }


            if (ptrend == NULL) {
                strand[0] = *ptr;
                strand[1] = '\0';
            } else {
                strncpy(strand, ptr, 1);
                strand[1] = '\0';
            }
            //new chrmosome
            if (strcmp(chrname, tmp_chrname) != 0) {
                //chrm_size = lookup_chrm(chrname)->size;

                if (head_buffer1 != NULL) {
                    while (head_buffer1 != NULL && head_buffer1->start_pos == 0) {
                        fprintf(fp_out, "%s\t%ld\t%ld\ttag0\t0\t%c\n", head_buffer1->chrname, head_buffer1->start_pos, head_buffer1->end_pos, head_buffer1->strand);
                        tmp_buffer = head_buffer1;
                        head_buffer1 = head_buffer1->next;
                        free(tmp_buffer->chrname);
                        free(tmp_buffer);
                    }

                    while (head_buffer2 != NULL || head_buffer1 != NULL) {
                        if (head_buffer1 != NULL && head_buffer2 != NULL) {
                            if (head_buffer2->start_pos <= head_buffer1->start_pos) {
                                fprintf(fp_out, "%s\t%ld\t%ld\ttag1\t0\t%c\n", head_buffer2->chrname, head_buffer2->start_pos, head_buffer2->end_pos, head_buffer2->strand);
                                tmp_buffer = head_buffer2;
                                head_buffer2 = head_buffer2->next;
                                free(tmp_buffer->chrname);
                                free(tmp_buffer);
                            } else {
                                fprintf(fp_out, "%s\t%ld\t%ld\ttag2\t0\t%c\n", head_buffer1->chrname, head_buffer1->start_pos, head_buffer1->end_pos, head_buffer1->strand);
                                tmp_buffer = head_buffer1;
                                head_buffer1 = head_buffer1->next;
                                free(tmp_buffer->chrname);
                                free(tmp_buffer);
                            }
                        } else if (head_buffer1 == NULL) {
                               fprintf(fp_out, "%s\t%ld\t%ld\ttag3\t0\t%c\n", head_buffer2->chrname, head_buffer2->start_pos, head_buffer2->end_pos, head_buffer2->strand);
                                tmp_buffer = head_buffer2;
                                head_buffer2 = head_buffer2->next;
                                free(tmp_buffer->chrname);
                                free(tmp_buffer);
                        } else {
                            fprintf(fp_out, "%s\t%ld\t%ld\ttag4\t0\t%c\n", head_buffer1->chrname, head_buffer1->start_pos, head_buffer1->end_pos, head_buffer1->strand);
                            tmp_buffer = head_buffer1;
                            head_buffer1 = head_buffer1->next;
                            free(tmp_buffer->chrname);
                            free(tmp_buffer);
                        }
                    }
                    tail_buffer2 = NULL;

                } else {
                    while (head_buffer2 != NULL) {
                        fprintf(fp_out, "%s\t%ld\t%ld\ttag5\t0\t%c\n", head_buffer2->chrname, head_buffer2->start_pos, head_buffer2->end_pos, head_buffer2->strand);
                        tmp_buffer = head_buffer2;
                        head_buffer2 = head_buffer2->next;
                        free(tmp_buffer->chrname);
                        free(tmp_buffer);
                    }
                    tail_buffer2 = NULL;
                }
            }

            read_length = end_pos - start_pos;

            if (read_length < elongation_size) {
                if (strand[0] ==  '+') {
                    new_start_pos = start_pos;
                    new_end_pos = start_pos + elongation_size;
                    //if (new_end_pos > chrm_size)
                    //    new_end_pos = chrm_size;
                } else {
                    new_end_pos = end_pos;
                    new_start_pos = end_pos - elongation_size;
                    if (new_start_pos < 0)
                        new_start_pos = 0;
                }
            }

            if (start_pos < elongation_size) {
                strcpy(tmp_chrname, chrname);
                if (strand[0] == '-') {
                    if (tail_buffer1 != NULL) {
                        tmp_buffer = tail_buffer1;
                        tail_buffer1 = add_buffer_item(tmp_chrname, new_start_pos, new_end_pos, strand[0]);
                        tmp_buffer->next = tail_buffer1;
                    } else {
                        tail_buffer1 = add_buffer_item(tmp_chrname, new_start_pos, new_end_pos, strand[0]);
                        head_buffer1 = tail_buffer1;
                    }
                } else {
                    if (tail_buffer2 != NULL) {
                        tmp_buffer = tail_buffer2;
                        tail_buffer2 = add_buffer_item(tmp_chrname, new_start_pos, new_end_pos, strand[0]);
                        tmp_buffer->next = tail_buffer2;
                    } else {
                        tail_buffer2 = add_buffer_item(tmp_chrname, new_start_pos, new_end_pos, strand[0]);
                        head_buffer2 = tail_buffer2;
                    }
                }
            } else {
                while (head_buffer1 != NULL) {
                    fprintf(fp_out, "%s\t%ld\t%ld\ttag6\t0\t%c\n", head_buffer1->chrname, head_buffer1->start_pos, head_buffer1->end_pos, head_buffer1->strand);
                    tmp_buffer = head_buffer1;
                    head_buffer1 = head_buffer1->next;
                    free(tmp_buffer->chrname);
                    free(tmp_buffer);
                }
                tail_buffer1 = NULL;
                if (strand[0] == '-') {
                    while (head_buffer2 != NULL && head_buffer2->start_pos <= new_start_pos) {
                        fprintf(fp_out, "%s\t%ld\t%ld\ttag7\t0\t%c\n", head_buffer2->chrname, head_buffer2->start_pos, head_buffer2->end_pos, head_buffer2->strand);
                        tmp_buffer = head_buffer2;
                        head_buffer2 = head_buffer2->next;
                        if (head_buffer2 == NULL)
                            tail_buffer2 = NULL;
                        free(tmp_buffer->chrname);
                        free(tmp_buffer);
                    }
                    fprintf(fp_out, "%s\t%ld\t%ld\ttag8\t0\t%c\n", chrname, new_start_pos, new_end_pos, strand[0]);
                } else {
                    strcpy(tmp_chrname, chrname);
                    if (tail_buffer2 != NULL) {
                        tmp_buffer = tail_buffer2;
                        tail_buffer2 = add_buffer_item(tmp_chrname, new_start_pos, new_end_pos, strand[0]);
                        tmp_buffer->next = tail_buffer2;
                    } else {
                        tail_buffer2 = add_buffer_item(tmp_chrname, new_start_pos, new_end_pos, strand[0]);
                        head_buffer2 = tail_buffer2;
                    }
                }
            }
        }
    }


    /*while (head_buffer1 != NULL) {
        fprintf(fp_out, "%s\t%ld\t%ld\ttag\t0\t%c\n", head_buffer1->chrname, head_buffer1->start_pos, head_buffer1->end_pos, head_buffer1->strand);
        tmp_buffer = head_buffer1;
        head_buffer1 = head_buffer1->next;
        free(tmp_buffer->chrname);
        free(tmp_buffer);
    }*/

    while (head_buffer2 != NULL) {
        fprintf(fp_out, "%s\t%ld\t%ld\ttag9\t0\t%c\n", head_buffer2->chrname, head_buffer2->start_pos, head_buffer2->end_pos, head_buffer2->strand);
        tmp_buffer = head_buffer2;
        head_buffer2 = head_buffer2->next;
        free(tmp_buffer->chrname);
        free(tmp_buffer);
    }
    tail_buffer2 = NULL;
    destroy_buffer(head_buffer1);
    destroy_buffer(head_buffer2);

    return;
}
