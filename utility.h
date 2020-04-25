
/** 
* @file   
* @brief 
* 
* @author Aleksandr Barunin
* 
* @date  Feb 2019
*/

#ifndef __UTILITY_H
#define __UTILITY_H

#include <stdint.h>

#define   MAX(A,B)     ((A) <= (B) ? (B) : (A))
#define   MIN(a,b)     ((a) <= (b) ? (a) : (b))

time_t convertDateToUnixTime (RTC_TimeTypeDef const inTime,
                              RTC_DateTypeDef const inDate) ;
void convertUnixTimeToDate (uint32_t t, RTC_TimeTypeDef *outTime,
                            RTC_DateTypeDef *outDate) ;
static uint8_t computeDayOfWeek (uint16_t y, uint8_t m, uint8_t d) ;
void explore_byte_order (void);
uint16_t reverse_byte_order_uint16 (const uint16_t in2byteVal);
uint32_t reverse_byte_order_uint32 (const uint32_t in4byteVal);
uint8_t get_low_byte_from_word(const uint16_t word16bit);
uint8_t get_hi_byte_from_word(const uint16_t word16bit);
uint32_t pack_ipv4 (const uint8_t ipAddrByte1, const uint8_t ipAddrByte2,
                    const uint8_t ipAddrByte3, const uint8_t ipAddrByte4);
int unpack_ipv4 ( uint32_t ipAddr, char *outArray, int *outArrayLen);
int mac_bin_to_str (unsigned char *macBinIn, char *macStrOut, int sizeOfMacStr);
void uint16_to_str (const uint16_t inValue, char *outStr);
void print_array (const unsigned char* inArray,
                  const unsigned short arrayLen);
int is_hex_digit (const char character) ;
int is_valid_ip (char *inIpStr, unsigned char *outOctets);
int is_valid_hex_byte (char const * const inByteStr) ;
int my_memcmp(const unsigned char *inArray1,
		      const unsigned char *inArray2,
			  int size);
int find_prev_node (struct Node_t *curNode, //in
                    struct Node_t **prevNode, // out
                    int *prevNodeCnt) ;// out 
int is_hex_digit (const char character) ;
int is_raw_hex_string (char const * const inByteStr, int const lenOfStr) ;
int hex_str_to_bin_array (const char * const inStrWithHex, int const inLenOfhexStr,
		                  uint8_t * const outBinStr, int const inSizeOfBinStr) ;
bool is_digit_str (const char  str[]) ;
bool is_valid_digit (const char character) ;
char *uint32_to_bin_str (uint32_t const inVal32bit) ;
uint32_t is_power_of_two (uint32_t const val) ;
uint32_t is_one_bit_in_mask (uint32_t const randMask) ;
const char *str_case_str (const char * const text, const char * const pattern) ;
uint8_t is_parity_odd (uint32_t const inVal) ;
uint8_t count_set_bits (uint32_t const inVal32bit) ;
char *file_name_from_path (char  * const fullPath) ;
uint32_t calc_sum_of_bytes (uint8_t const inArray [], uint32_t const lenOfArray) ;
bool extract_byte (uint32_t const inValue, uint8_t const inByte, uint8_t * const outByte) ;
uint32_t is_big_endian (void) ;
bool test_stack_dirr (void) ;
bool str2uppercase (char * const inOutStr) ;
bool  toLowerCase (char *  inOutStr) ;
bool is_stack_addr_decreases (uint8_t * const val) ;


#endif /* __UTILITY_H */
