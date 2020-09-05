#ifndef __ARRAY_H
#define __ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool concatenate_array (uint8_t *out_fin_array, uint32_t fin_array_len, uint8_t *in_array1, uint32_t in_array1_len,
                        uint8_t *in_array2, uint32_t in_array2_len);

void *memdup (const void *mem, size_t sizeByte);
int *generate_num_array_malloc (int n);
int *singleNumber (int *nums, int numsSize, int *const returnSize);
bool is_correct_permutation (int *arraOfIndex, int n, int maxVal);
bool is_single_zero (int *const arr, int sizeOfArr, int indexToArr);
int findMaxConsecutiveOnes (int *nums, int numsSize);
int findMaxConsecutiveOnesFlip1 (int *nums, int length);
int findMaxConOnesDel1 (int *const array, int length);
void print_array_to_file_pointer (FILE *filePointer, int *array, int size);
void print_array_to_filename (char *filename, int *array, int size);
int count_max_amout_of_one_after_del (int *arr, int sizeOfArr);
int *remove_int_from_arr (int *inArr, int arrSize, int delIndex);
int *add_val_to_end_array (int *inArr, int arrSize, int val);
void print_curr_array (int *alphabet, int sizeOfAlphabet);
void print_mem (unsigned char *alphabet, int sizeOfAlphabet);
void print_array_of_diff_arrays (int **arrOfArr, int amountOfLine, int *colSizes);
void print_array_of_arrays (int **arrOfArr, int amountOfLine, int amountOfCol);
uint64_t sum_arr (uint32_t *arr, uint32_t size);
float calc_avarage (uint32_t *arr, uint32_t size);
bool test_single_number (void);

#ifdef __cplusplus
}
#endif

#endif /* __ARRAYS_H */
