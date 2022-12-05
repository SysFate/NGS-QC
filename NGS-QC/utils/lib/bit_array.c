#include <stdlib.h>
#include <time.h>
//#include <stdio.h>

#include "bit_array.h"

#define true 1
#define false 0

#ifdef CHAR_BIT
   #define BITS_SZ (CHAR_BIT)
#else
   //static size_t bits_size(void);
   size_t BITS_SZ = 0;  /* until it is initialized by ba_init() */
 
   static size_t bits_size(void) {
      size_t i;
      bit v = (bit)~0;

      for (i=1; (v = v >> 1) > 0; i++)
         ;
      return (i);
   }
#endif

void destroy_array_ba() {
    free(array_ba->ba1);
    array_ba->ba1 = NULL;
    free(array_ba->ba2);
    array_ba->ba2 = NULL;
    free(array_ba->ba3);
    array_ba->ba3 = NULL;
    free(array_ba);
    array_ba = NULL;
}

void destroy_rep_array_ba() {
    for (int i = 0; i < 10; i++) {
        if (rep_array_ba[i] != NULL) {
            free(rep_array_ba[i]->ba1);
            rep_array_ba[i]->ba1 = NULL;
            free(rep_array_ba[i]->ba2);
            rep_array_ba[i]->ba2 = NULL;
            free(rep_array_ba[i]->ba3);
            rep_array_ba[i]->ba3 = NULL;
        }
        free(rep_array_ba[i]);
        rep_array_ba[i] = NULL;
    }
}


bit* build_bit_array(bit* bit_array, unsigned long n) {
    int realn = 0;
    #ifndef BITS_SZ
        if (!BITS_SZ) {
            BITS_SZ = bits_size();
        }
    #endif
    realn =  n/(BITS_SZ)  +  1 - (0 == (n %(BITS_SZ)));
    bit_array = ((bit *)calloc(realn, sizeof(bit)));

    //printf("realn %d\n", realn);
    return bit_array;
}


bit test_bit(bit arr[], unsigned long n) {
    return ((arr[n / BITS_SZ] & (1 << (n % BITS_SZ))) != 0);
}


void change_bit(bit arr[], unsigned long elem, int value) {
    //printf("change octet n: %zd\n", elem);
    //printf("bit value: %d\n", testBit(arr, elem));
    if (value) {
        arr[elem / BITS_SZ] |= (1 << (elem % BITS_SZ));
    } else {
        arr[elem / BITS_SZ] &= ~(1 << (elem % BITS_SZ));
    }
}


void get_sampling_line_index(unsigned long total_reads, const int* sampling_array) {
    array_ba = (struct s_array_ba*)malloc(sizeof(struct s_array_ba));
    int i, s;
    unsigned long read_to_not_sample, j, k;

    for (i = 0; i < 3; i++) {
        s = sampling_array[i];
        read_to_not_sample = (total_reads * (100-s))/100.0;

        bit* current_ba;

        if (i == 0)
            current_ba = array_ba->ba1;
        else if (i == 1)
            current_ba = array_ba->ba2;
        else
            current_ba = array_ba->ba3;

        current_ba = build_bit_array(current_ba, total_reads);

        //change s% of the bit aray to true
        for (j = 0; j < read_to_not_sample; j++) {
            change_bit(current_ba, j, true);
        }


        //shuffle the bit array
        if (read_to_not_sample > 1) {
            srand(time(NULL)+i);
            for (k = 0; k < total_reads - 1; k++) {
              j = k + rand() / (RAND_MAX / (total_reads - k) + 1);
              bit t = test_bit(current_ba, j);
              change_bit(current_ba, j, test_bit(current_ba, k));
              change_bit(current_ba, k, t);
            }
        }

        if (i == 0)
            array_ba->ba1 = current_ba;
        else if (i == 1)
            array_ba->ba2 = current_ba;
        else
            array_ba->ba3 = current_ba;
    }
}


void get_sampling_line_index_rep(unsigned long total_reads, const int* sampling_array, unsigned char rep_number) {
    //array_ba = (struct s_array_ba*)malloc(sizeof(struct s_array_ba));
    int i, s, r;
    unsigned long read_to_not_sample, j, k;

    for (r = 0; r < rep_number; r++) {
        rep_array_ba[r] = (struct s_array_ba*)malloc(sizeof(struct s_array_ba));
        for (i = 0; i < 3; i++) {
            s = sampling_array[i];
            read_to_not_sample = (total_reads * (100-s))/100.0;
            bit* current_ba;

            if (i == 0)
                current_ba = rep_array_ba[r]->ba1;
            else if (i == 1)
                current_ba = rep_array_ba[r]->ba2;
            else
                current_ba = rep_array_ba[r]->ba3;

            current_ba = build_bit_array(current_ba, total_reads);

            //change s% of the bit aray to true
            for (j = 0; j < read_to_not_sample; j++) {
                change_bit(current_ba, j, true);
            }

            //shuffle the bit array
            if (read_to_not_sample > 1) {
                srand(time(NULL)+i+r);
                for (k = 0; k < total_reads - 1; k++) {
                  j = k + rand() / (RAND_MAX / (total_reads - k) + 1);
                  bit t = test_bit(current_ba, j);
                  change_bit(current_ba, j, test_bit(current_ba, k));
                  change_bit(current_ba, k, t);
                }
            }

            if (i == 0)
                rep_array_ba[r]->ba1 = current_ba;
            else if (i == 1)
                rep_array_ba[r]->ba2 = current_ba;
            else
                rep_array_ba[r]->ba3 = current_ba;
        }
    }
}

