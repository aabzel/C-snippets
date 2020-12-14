#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "linked_list.h"
#include "utils.h"

#include <stdint.h>

#define DEBUG_LET_POS 0
#define DEBUG_ARG 0

//#define F_EPSILON 0.0005f
int sum_digits (int val);
void print_terms (int total_num, int *alf, int alf_size, int sum, int *syllables);
bool swap_int (int *const x, int *const y);
uint32_t factorial (uint32_t n);
bool is_in_range (int val, int lowBound, int upBound);
int update_max (int curMax, int newVal);
int qselect (int *v, int len, int k);
// bool is_power_of_two (int x);
void swap_char (char *const x, char *const y);

short compare (int Data1, int Data2);
int max_int (int val1, int val2);
int min_int (int val1, int val2);
int min3 (int val1, int val2, int val3);

uint32_t average_slow (uint32_t a, uint32_t b);
uint32_t average_quick (uint32_t a, uint32_t b);
bool is_exist (int *arr, size_t n, int val);
int partition_int (int *arr, int l, int r);
int qselect (int *v, int len, int k);
float minf (float val1, float val2);
float min3f (float val1, float val2, float val3);

bool is_float_equal (float a__fife, float b__fife, float epsilon__fife);

int partition (int *arr, int l, int r);
int cmp_int (const void *p1, const void *p2);
void swap_char (char *const x, char *const y);
int *generate_num_array (int n);
char *generate_num_string (int n);
int *twoSum (int *nums, int numsSize, int target, int *returnSize);

#ifdef __cplusplus
}
#endif

#endif /* __ALGORITHMS_H */
