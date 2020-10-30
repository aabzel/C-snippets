/*
 *
 * This is a file with some utility
 * functions mainly needed to boost readability in driver code.
 *
 * */
#include "bit_utils.h"

/*
 * Function returns the number of set bits in binary  (Hamming weight)
 * representation of positive integer val
 * TODO: we can boost time of calculation by creating look up table for byte->am of bit
 *       It will reqire 512 byte of flash for 8bit value.
 *
 * */

uint8_t count_set_bits (uint32_t const inVal32bit) {
    uint8_t sum = 0;
    uint32_t val32bit = inVal32bit;
    while (0u != val32bit) {
        sum++;
        val32bit &= (val32bit - 1u);
    }
    return sum;
}

/*
 *  Odd (Amount of 1 bits is 1 3 5 7 9 and so 31)
 *  even (Amount of 1 bits is 2 4 6 8 10 and so 32)
 *
 *  returns 1 if the parity in inValue is Odd
 *  (Amount of 1 bits is 1 3 5 7 9 and so 31)
 *
 *  inVal        bit        setBit  parity        return
 *  0          > 00       > 0  >    PARITY_EVEN   false
 *  1          > 01       > 1  >    PARITY_ODD    true
 *  2          > 10       > 1  >    PARITY_ODD    true
 *  3          > 11       > 2  >    PARITY_EVEN   false
 *  178        > 10110010 > 4  >    PARITY_EVEN   false
 *  0xFFFFFFFF > 1..111   > 32 >    PARITY_EVEN   false
 *  0xFFFFFFFE > 11..10   > 31 >    PARITY_ODD    true
 */
bool is_parity_odd (uint32_t const inVal) {
    bool otRet = false;
    uint8_t cntOnes = 0u;
    /*count set bits*/
    cntOnes = count_set_bits (inVal);
    if (0u < (cntOnes & 1u)) {
        otRet = true; /*(Amount of 1 bits is 1 3 5 7 9 and so 31)*/
    } else {
        otRet = false; /*(Amount of 1 bits is 2 4 6 8 10 and so 32)*/
    }

    return otRet;
}

/*
 return 0 if value contains only 1 bit set
 1, 2 4 8 16 32 64 128 512 ....
 */
bool is_power_of_two (uint32_t const val) {
    bool outRetPt = false;
    /*check power of two*/
    if (0u == (val & (val - 1u))) {
        /*only one bit set in the value */
        outRetPt = true;
    }
    if (0u == val) {
        outRetPt = false;
    }
    return outRetPt;
}


uint64_t swap_bits(uint64_t in_val) {
    uint64_t out_val = 0U;
    for (uint16_t i = 0U; i<64U; i++) {
        if ( (((uint64_t)1U)<<i)==((((uint64_t)1U)<<i)&in_val) ) {
            out_val |= (((uint64_t)1)<<(63U-i));
        }
    }

    return out_val;
}



int swap_dec (int in_x) {
    int64_t rev_dec = 0;
    int64_t x = (int64_t)in_x;
#ifdef DEBUG
    printf ("\nx=%d", x);
#endif
    int sign = 1;
    if (0 == x) {
        return 0;
    }
    if (x < 0) {
        x = -x;
        sign = -1;
    }
    uint8_t arr[13];
    memset (arr, 0xFF, sizeof (arr));
    int cnt = 0;
    uint8_t digit = 0;
    while (0 < x) {
        digit = x % 10;
#ifdef DEBUG
        printf ("\n[%d]=%d ", cnt, digit);
#endif
        arr[cnt] = digit;
        x = x / 10;
        cnt++;
    }
#ifdef DEBUG
    printf ("\n");
#endif
    // cnt - rank of x
    int rank = cnt - 1;
    if (0 <= rank) {
        rev_dec = 0;
        for (int i = (rank); 0 <= i; i--) {
            int64_t power = powi (10, (rank - i));
            int64_t incriment = ((int64_t)arr[i]) * (int64_t)power;
#ifdef DEBUG
            printf ("\narr[%d]=%d power %I64d %I64d", i, arr[i], power, incriment);
#endif
            rev_dec += incriment;
        }
    }
#ifdef DEBUG
    printf ("\nrev_dec=%I64d", rev_dec);
#endif
    if (2147483647 < rev_dec) {
        rev_dec = 0;
    }
#ifdef DEBUG
    printf ("\nlim rev_dec=%I64d", rev_dec);
#endif
    rev_dec = rev_dec * sign;
    return rev_dec;
}


