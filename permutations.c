#include "permutations.h"

#include "algorithms.h"
#include "arrays.h"
#include "linked_list.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_permut (int *in_current_array, int in_curr_arr_size, int pos, int *alf, int alf_size, int total_num) {
    if (in_curr_arr_size == total_num) {
        printf ("\n");
        print_curr_array (in_current_array, in_curr_arr_size);
        free (in_current_array);
        in_current_array = NULL;
    }

    if (pos < total_num) {
        for (int i = 0; i < alf_size; i++) {
            // print_indent (pos);
            // printf("%d",alf[i]);
            int *currentArray = add_val_to_end_array (in_current_array, in_curr_arr_size, alf[i]);
            if (NULL!=currentArray) {
                print_permut (currentArray, in_curr_arr_size + 1, pos + 1, alf, alf_size, total_num);
            } else {
                printf ("\nUnable to alloc memory");
            }
        }
    } else {
        // printf("\n");
    }
}


void permute_from_set (int total_num, int *alf, int alf_size) {
    printf ("\n");
    print_permut (NULL, 0, 0, alf, alf_size, total_num);
}

// static int curPermutationNumber = 0;
/*in_current_array will be freed in here*/
/*inIndexArrayRemain will be freed outside */
bool print_permutations_ll (int *in_current_array, int in_curr_arr_size, int *inIndexArrayRemain, int remainSize,
                            int totalSize, // amount of item in permutation
                            int targetPermutIndex, int startIndex, int endIndex, int *outArray) {

#if DEBUG_CURR_ARRAY
    printf ("\n cur array: ");
    print_curr_array (in_current_array, in_curr_arr_size);
    printf ("\n");
#endif
    bool res = false;
    int *indexArrayTemp;
    int *indexArrayNew;
    if (remainSize < 0) {
        printf ("%s Error %d\n", __FUNCTION__, 3);
        return false;
    }
    int range = endIndex - startIndex + 1;
#if PRINT_PERMUTATIONS_LL
    if (2 == range) {
        printf ("%s Debug range %d\n", __FUNCTION__, range);
    }
#endif
    if (false == is_in_range (targetPermutIndex, startIndex, endIndex)) {
        free (in_current_array);
        return false;
    } else {
#if DEBUG_IND_RANGE
        printf (" -> [%d<=%d<=%d] range %d", startIndex, targetPermutIndex, endIndex, range);
#endif
    }
    if (0 == remainSize) {
        // printf ("remainSize 0 \n");
        // free(inIndexArrayRemain);
    }
    if (in_curr_arr_size < 0) {
        printf ("%s Error %d\n", __FUNCTION__, 1);
        return false;
    }
    if ((NULL == in_current_array)) {
        printf ("%s Error %d\n", __FUNCTION__, 2);
        return false;
    }

    if (in_curr_arr_size == totalSize) {
#if DEBUG_ARRAY
        printf ("\n number %d", curPermutationNumber);
        print_curr_array (in_current_array, in_curr_arr_size);
#endif

        if ((NULL != outArray) && (targetPermutIndex == startIndex)) {
            // printf ("\n ");
            memcpy (outArray, in_current_array, in_curr_arr_size * sizeof (int));
            free (in_current_array);
            free (inIndexArrayRemain);
            return true;
        }
    }
    int stepInd = 0;

    if (0 < remainSize) {
        if (remainSize <= range) {
            // is divided?
            if (0 == (range % remainSize)) {
                if ((1 == range) && (range == remainSize)) {
                    stepInd = 0;
                } else {
                    stepInd = range / remainSize;
                }
            } else {
#if DEBUG_PRINT_PERMUTATIONS_LL
                printf ("\n remainSize %d range %d startInd %d endInd %d target %d", remainSize, range, startIndex,
                        endIndex, targetPermutIndex);
#endif
                return false;
            }
        } else {
#if DEBUG_PRINT_PERMUTATIONS_LL
            printf ("\n remainSize %d range %d", remainSize, range);
#endif
            return false;
        }
    } else {
        return true;
    }
#if DEBUG_PRINT_PERMUTATIONS_LL
    printf ("\n range %d remainSize %d stepInd %d", range, remainSize, stepInd);
#endif

    for (int i = 0; i < remainSize; i++) {
        indexArrayTemp = (int *)memdup ((void *)inIndexArrayRemain, remainSize * sizeof (int));
        if (indexArrayTemp) {
            int *currentArray = add_val_to_end_array (in_current_array, in_curr_arr_size, indexArrayTemp[i]);
            if (currentArray) {
#if DEBUG_PRINT_PERMUTATIONS_LL
                printf ("\n");
                print_curr_array (currentArray, in_curr_arr_size + 1);
                printf ("\n");
#endif
                indexArrayNew = remove_int_from_arr (indexArrayTemp, remainSize, i);
                // indexArrayNew will be freed in print_permutations_ll
                int startInd = startIndex;
                int endInd = startIndex;
                if (0 < stepInd) {
                    startInd = startIndex + (i * stepInd);             // 0
                    endInd = startIndex + (i * stepInd) + stepInd - 1; //
                }
                if (true == is_in_range (targetPermutIndex, startInd, endInd)) {
                    res = print_permutations_ll (currentArray, in_curr_arr_size + 1, indexArrayNew, remainSize - 1,
                                                 totalSize, targetPermutIndex, startInd, endInd, outArray);
                } else {
                    free (currentArray);
                }

                if (indexArrayNew) {
                    free (indexArrayNew);
                }
                if (true == res) {
                    return true;
                }
            }
        }
    }
    free (in_current_array);
    return res;
}
// 4: 1....24     6    (1 7 13 19)
// 5: 1....120    24   (1 25 49 73 97 )
bool get_i_permutation_of_n (int maxNumOfElement, uint32_t permutIndex, int *array) {
    bool res = false;
    if (1 == maxNumOfElement) {
        (*array) = 0;
        return true;
    }
    uint32_t amountOfpermutations = factorial (maxNumOfElement);
    int indexStep = amountOfpermutations / maxNumOfElement; // 24/4 = 6
    if (permutIndex < amountOfpermutations) {
        int *indexArray;
        int *indexArrayNew;
        for (int i = 0; i < maxNumOfElement; i++) {
            indexArray = generate_num_array_malloc (maxNumOfElement);
            if (indexArray) {
                int *currentArray = add_val_to_end_array (NULL, 0, indexArray[i]);
                // indexArray will be freed in remove_int_from_arr
                indexArrayNew = remove_int_from_arr (indexArray, maxNumOfElement, i);
                if (indexArrayNew) {
                    // currentArray will be freed in print_permutations_ll
                    int indexStart = i * indexStep;               // 0
                    int indexEnd = i * indexStep + indexStep - 1; // 5
                    if (true == is_in_range (permutIndex, indexStart, indexEnd)) {
                        res = print_permutations_ll (currentArray, 1, indexArrayNew, maxNumOfElement - 1,
                                                     maxNumOfElement, permutIndex, indexStart, indexEnd, array);
                    }

                    free (indexArrayNew);
                    if (true == res) {
                        return true;
                    }
                }
            }
        }
    } else {
        printf ("there is no such permutation %d", permutIndex);
    }
    return res;
}

// given number N
// print all permutations for (1,2,..,N)
bool print_permutations (int N) {
    bool res = false;
    res = get_i_permutation_of_n (N, 0, NULL);
    return res;
}

list_node_t *permutllHead = NULL;

/* Function to print permutations of string
 This function takes three parameters:
 1. String
 2. Starting index of the string
 3. Ending index of the string. */
void permute_ll (char *string, int left, int right) {
    int index = 0;
    if (left == right) {
        printf ("%s\n", string);

    } else {
        for (index = left; index <= right; index++) {
            swap_char ((string + left), (string + index));
            permute_ll (string, left + 1, right);
            swap_char ((string + left), (string + index)); // backtrack
        }
    }
}


void permutation (int n) {
    if (0 < n) {
        char *numString = NULL;
        numString = generate_num_string (n);
        if (NULL != numString) {
            permute (numString);
            free (numString);
        }
    }
}



#define DEBUG_IS_PERMUTATED 0
bool is_permutation (int *arr1, int *arr2, int sizeOfArr) {
    bool res = false;
#if DEBUG_IS_PERMUTATED
    printf ("\nArr1: ");
    print_curr_array (arr1, sizeOfArr);
    printf ("Arr2: ");
    print_curr_array (arr2, sizeOfArr);
#endif
    int amOfBytes = sizeof (int) * sizeOfArr;

    int *locArr1 = NULL;
    int *locArr2 = NULL;

    locArr1 = malloc (amOfBytes);
    if (locArr1) {
        memcpy (locArr1, arr1, amOfBytes);
        qsort (locArr1, sizeOfArr, sizeof (int), cmp_int);
    }

    locArr2 = malloc (amOfBytes);
    if (locArr2) {
        memcpy (locArr2, arr2, amOfBytes);
        qsort (locArr2, sizeOfArr, sizeof (int), cmp_int);
    }

    if (locArr1 && locArr2) {
        int ret = memcmp (locArr1, locArr2, amOfBytes);
        if (0 == ret) {
#if DEBUG_IS_PERMUTATED
            printf ("\nPermutated arrays!");
#endif
            res = true;
        }
        free (locArr1);
        free (locArr2);
    }
    return res;
}

#if 0
bool is_permutated_element_in_list (list_node_t *pHead, int *inArr, int arrSize) {
#if DEBUG_PERMUT_ELEN_IN_LIST
    int static cnt = 0;
    printf ("\n%s() %d", __FUNCTION__,++cnt);
#endif
    bool res = false;
    list_node_t *curNode = pHead;
    if (curNode) {
        while (NULL != curNode) {
            if (arrSize == curNode->data.arrSize) {
                res = is_permutation (curNode->data.pArr, inArr, arrSize);
                if (true == res) {
#if DEBUG_PERMUT_ELEN_IN_LIST
                    printf ("\nList contained permutated array");
#endif
                    break;
                }
            } else {
#if DEBUG_IS_PERMUT
                printf ("\nsize of array unmatch inArrSize %d arrCurSize %d", arrSize, curNode->data.arrSize);
#endif
            }
            curNode = curNode->nextNode;
        }
    }
    return res;
}

#endif


void assemble_from_alph (int *in_remain_alphabet, int size_of_alphabet, int *in_cur_arr, int in_cur_arrSize,
                         int **solution_array) {
#ifdef DEBUG_PERMUT
    printf ("\n[d] %s(): line %u alphSize: %d\n", __FUNCTION__, __LINE__, size_of_alphabet);
#endif
    static int sol_cnt = 0;
    if (NULL == in_cur_arr) {
        sol_cnt = 0;
    }
    if ((0 == size_of_alphabet) && (NULL == in_remain_alphabet)) {
#ifdef DEBUG_PERMUT
        print_array_to_filename (kitFile, in_cur_arr, in_cur_arrSize);
#endif
        if ((NULL != in_cur_arr) && (0 < in_cur_arrSize)) {
            *(solution_array + sol_cnt) = in_cur_arr;
            sol_cnt++;
#ifdef DEBUG_PERMUT
            printf ("\n[+] solution: %d ", sol_cnt);
            print_array_int (in_cur_arr, in_cur_arrSize);
            // free outside
#endif
        }
    } else if ((0 < size_of_alphabet) && (NULL != in_remain_alphabet)) {
#ifdef DEBUG_PERMUT
        printf ("\n\n[d] in_remain_alphabet: ");
        print_array_int (in_remain_alphabet, size_of_alphabet);
        printf ("\n[d] in_cur_arr: ");
        print_array_int (in_cur_arr, in_cur_arrSize);
#endif
        for (int num_order = 0; num_order < size_of_alphabet; num_order++) {
            int *new_remain_alphabet = (int *)memdup ((void *)in_remain_alphabet, sizeof (int) * size_of_alphabet);
            if (NULL == new_remain_alphabet) {
                printf ("\n Unable to duplicate in alphabet %u ", num_order);
                return;
            }
            int cmp_res = memcmp (new_remain_alphabet, in_remain_alphabet, sizeof (int) * size_of_alphabet);
            if (0 != cmp_res) {
                printf ("\n[!] mem duplicate error");
                return;
            }
#ifdef DEBUG_PERMUT
            printf ("\n[d]    in_remain_alphabet: ");
            print_array_int (in_remain_alphabet, size_of_alphabet);
            printf ("\n[d]    new_remain_alphabet: ");
            print_array_int (new_remain_alphabet, size_of_alphabet);
#endif
            int add_val = new_remain_alphabet[num_order];
#ifdef DEBUG_PERMUT
            printf ("\n[d]    add_val %d\n ", add_val); // wrong val
#endif
            // printf ("\nw[%d]=%d\n", num_order, new_remain_alphabet[num_order]);
            int *cur_array_extended = add_val_to_end_array (in_cur_arr, in_cur_arrSize, add_val);
            // free (in_cur_arr);
            if (NULL != cur_array_extended) {
                // part of the solution allocated
                int *redused_alphabet = remove_int_from_arr (new_remain_alphabet, size_of_alphabet, num_order);
                if (redused_alphabet != new_remain_alphabet) {
                    // printf ("\n remove array val error");
                }
                if (NULL != redused_alphabet) {
                    assemble_from_alph (redused_alphabet, (size_of_alphabet - 1), cur_array_extended,
                                        in_cur_arrSize + 1, solution_array);
                    // free (redused_alphabet);
                } else {
                    assemble_from_alph (NULL, 0, cur_array_extended, in_cur_arrSize + 1, solution_array);
                }
            } else {
                printf ("\n Unable to add val to end %u", num_order);
            }
            if (new_remain_alphabet) {
                free (new_remain_alphabet);
            }
        }
        // if (in_remain_alphabet) {
        //    free (in_remain_alphabet);
        //}
#if DEBUG_PERMUT
        printf ("\n");
#endif
    } else {
        printf ("\n strange error");
    }
}




int **permute (int *array, int numsSize, int *returnSize, int **returnColumnSizes) {
    // printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
    int amount_of_comb = factorial (numsSize);
    (*returnSize) = amount_of_comb;
#ifdef DEBUG_PERMUT
    printf ("\n[d]amount_of_comb %u", amount_of_comb);
    int size_for_sol = amount_of_comb*numsSize * sizeof(int);
    printf ("\n[d]size_for_sol %u", size_for_sol);
#endif
    int **solution;
    solution = (int **)malloc (sizeof (int *) * amount_of_comb);
    assemble_from_alph (array, numsSize, NULL, 0, solution);

    int *columnSizes = (int *)malloc (sizeof (int) * amount_of_comb);
    for (int i = 0; i < amount_of_comb; i++) {
        columnSizes[i] = numsSize;
    }
    *returnColumnSizes = columnSizes;

    return solution;
}
