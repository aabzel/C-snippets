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
