// C programming language handy functions

time_t convertDateToUnixTime (RTC_TimeTypeDef const inTime,
                              RTC_DateTypeDef const inDate) {
    uint32_t y, m, d, t;

    // Year
    y = inDate.Year;
    // Month of year
    m = inDate.Month;
    // Day of month
    d = inDate.Date;

    // January and February are counted as months 13 and 14 of the previous year
    if (m <= 2) {
        m += 12;
        y -= 1;
    }

    // Convert years to days
    t = (365 * y) + (y / 4) - (y / 100) + (y / 400);
    // Convert months to days
    t += (30 * m) + (3 * (m + 1) / 5) + d;
    // Unix time starts on January 1st, 1970
    t -= 719561;
    // Convert days to seconds
    t *= 86400;
    // Add hours, minutes and seconds
    t += (3600 * inTime.Hours) + (60 * inTime.Minutes) + inTime.Seconds;

    // Return Unix time
    return t;
}


void convertUnixTimeToDate (uint32_t t, RTC_TimeTypeDef *outTime,
                            RTC_DateTypeDef *outDate) {
    uint32_t a, b, c, d, e, f;
    // Negative Unix time values are not supported
    if (t < 1) {
        t = 0;
    }
    // Retrieve hours, minutes and seconds
    outTime->Seconds = t % 60;
    t /= 60;
    outTime->Minutes = t % 60;
    t /= 60;
    outTime->Hours = t % 24;
    t /= 24;
    // Convert Unix time to date
    a = (uint32_t) ((4 * t + 102032) / 146097 + 15);
    b = (uint32_t) (t + 2442113 + a - (a / 4));
    c = (20 * b - 2442) / 7305;
    d = b - 365 * c - (c / 4);
    e = d * 1000 / 30601;
    f = d - e * 30 - e * 601 / 1000;
    // January and February are counted as months 13 and 14 of the previous year
    if (e <= 13) {
        c -= 4716;
        e -= 1;
    } else {
        c -= 4715;
        e -= 13;
    }
    // Retrieve year, month and day
    outDate->Year = c;
    outDate->Month = e;
    outDate->Date = f;
    // Calculate day of week
    outDate->WeekDay = computeDayOfWeek (c, e, f);
}

/**
 * @brief Calculate day of week
 * @param[in] y Year
 * @param[in] m Month of year (in range 1 to 12)
 * @param[in] d Day of month (in range 1 to 31)
 * @return Day of week (in range 1 to 7)
 **/

static uint8_t computeDayOfWeek (uint16_t y, uint8_t m, uint8_t d) {
    uint32_t h, j, k;

    // January and February are counted as months 13 and 14 of the previous year
    if (m <= 2) {
        m += 12;
        y -= 1;
    }

    // J is the century
    j = y / 100;
    // K the year of the century
    k = y % 100;

    // Compute H using Zeller's congruence
    h = d + (26 * (m + 1) / 10) + k + (k / 4) + (5 * j) + (j / 4);

    // Return the day of the week
    return ((h + 5) % 7) + 1;
}


void explore_byte_order (void)
{
    unsigned short x = 1;       /* 0x0001 */
    int result;
    result = *((unsigned char *) &x);

    if (0 == result) {
        printf ("\nbig-endian");
    } else {
        // less significant byte first
        printf ("\nlittle-endian");     // esp32 is little endian
    }
}

uint16_t reverse_byte_order_uint16 (const uint16_t in2byteVal)
{
    uint16_t swapped = 0;
    swapped = (in2byteVal >> 8) | (in2byteVal << 8);
    return swapped;
}

uint32_t reverse_byte_order_uint32 (const uint32_t in4byteVal)
{
    uint32_t retval;
    retval = in4byteVal & 0xFF;
    retval = (retval << 8) | ((in4byteVal >> 8) & 0xFF);
    retval = (retval << 8) | ((in4byteVal >> 16) & 0xFF);
    retval = (retval << 8) | ((in4byteVal >> 24) & 0xFF);
    return retval;
}

uint8_t get_low_byte_from_word(const uint16_t word16bit)
{
    uint8_t result = 0;
    result = 0x00FF & word16bit;
    return result;
}

uint8_t get_hi_byte_from_word(const uint16_t word16bit)
{
    uint8_t result = 0;
    result = (0x00FF & (word16bit>>8));
    return result;
}

uint32_t pack_ipv4 (const uint8_t ipAddrByte1, const uint8_t ipAddrByte2,
                    const uint8_t ipAddrByte3, const uint8_t ipAddrByte4)
{
    uint8_t ipAddr[4] =
        { ipAddrByte1, ipAddrByte2, ipAddrByte3, ipAddrByte4 };
    uint32_t ipv4bytesLe, ipv4bytesBe;
    memcpy (&ipv4bytesLe, ipAddr, 4);
    ipv4bytesBe = reverse_byte_order_uint32 (ipv4bytesLe);
    return ipv4bytesBe;
}

/*
 * outArray 1.1.1.1(7byte)....... 255.255.255.255 (15byte)
 * 7<*outArrayLen<15   
 * */
int unpack_ipv4 ( uint32_t ipAddr, char *outArray, int *outArrayLen)
{
    unsigned char *ipAddrBytes;
    char ipTempAddrArray[20] = {0};
    ipAddrBytes = (unsigned char *) &ipAddr;
    sprintf(ipTempAddrArray,"%d.%d.%d.%d", (int)ipAddrBytes[0], 
                                       (int)ipAddrBytes[1],
                                       (int)ipAddrBytes[2], 
                                       (int)ipAddrBytes[3]);
    int len = strlen(ipTempAddrArray);
    
    if ((7<=len) && (len<=15)) {
        strcpy(outArray, ipTempAddrArray);
        *outArrayLen = len;
    } else {
        return 1;
    }
    return 0;
}

int mac_bin_to_str (unsigned char *macBinIn, char *macStrOut, int sizeOfMacStr)
{
    if (macBinIn == NULL) {
        return 1;
    }
    if (macStrOut == NULL) {
        return 2;
    }

    if(sizeOfMacStr < 20){
    	return 3;
    }
    snprintf ((char *) macStrOut, sizeOfMacStr,
              "%02x:%02x:%02x:%02x:%02x:%02x",
              macBinIn[0], macBinIn[1], macBinIn[2],
              macBinIn[3], macBinIn[4], macBinIn[5]);

    return 0;
}


void uint16_to_str (const uint16_t inValue, char *outStr)
{
    if (outStr) {
        sprintf(outStr, "%04X", inValue);
    }
}

void print_array (const unsigned char* inArray,
                  const unsigned short arrayLen)
{
	printf("\n[");
	for (int i=0; i < arrayLen; i++) {
		printf ("%02x ",inArray[i]);
	}
	printf("]");
	printf("\n[");
	for (int i=0; i < arrayLen; i++) {
		printf("%c",inArray[i]);
	}
	printf("]");
}





/* return 0 if character contains only hex digit , else return 1*/
int is_hex_digit (const char character) {
    if (('A' <= character && character <= 'F') || \
        ('a' <= character && character <= 'f') || \
        ('0' <= character && character <= '9')) {
        return 0;
    } else {
        return 1;
    }
}


/* return 0 if IP string is valid,
 * return positive number if error */
int is_valid_ip (char *inIpStr, unsigned char *outOctets)
{
	//printf("\n is_valid_ip...\n");
	//printf("\n inIpStr: %s \n", inIpStr);
	int dotCnt = 0;
	int octetCnt = 0;
	int valOct[4] = {256,256,256,256};
	char curNumStr [10] = "";

	if (inIpStr == NULL){
		return 1;
	}
	int lenOfStr = strlen(inIpStr);
	//printf("\n lenOfStr: %d \n", lenOfStr);

    int j = 0;
	for (j = 0; j < lenOfStr+1; j++) {

		char curChar = inIpStr[j];
		//printf("\n curChar: %c        \n", curChar);
		if ('.' == curChar) {
			dotCnt++;
			//printf("\n curNumStr: %s \n", curNumStr);
			valOct[octetCnt] = atoi(curNumStr);
			if (255 < valOct[octetCnt]) {
				return 4;
			}
			strcpy(curNumStr,"");
			octetCnt++;
		} else if ('\0' == curChar) {
			//printf("\n curNumStr: %s \n", curNumStr);
			valOct[octetCnt] = atoi(curNumStr);
			if (255 < valOct[octetCnt]) {
				return 4;
			}
			strcpy(curNumStr, "");
			octetCnt++;
		} else if ( !valid_digit(curChar) ) {
			char strDigit[2] = {curChar, '\0'};
			strcat(curNumStr, strDigit);
		} else {
			return 3;
		}
	}
	//printf("\n dotCnt: %d \n", dotCnt);
	if ( dotCnt != 3 )
		return 5;
	outOctets[0]=(unsigned char) valOct[0];  
	outOctets[1]=(unsigned char) valOct[1];  
	outOctets[2]=(unsigned char) valOct[2];  
	outOctets[3]=(unsigned char) valOct[3];  
	return 0;
}


/* return 0 if string is a regex  (0[x][0-9a-fA-F]{2}) ,
 * return positive number if error */
int is_valid_hex_byte (char const * const inByteStr) {
	int len;
	len = strlen(inByteStr);
	if (5<=len) {
		return 3;
	}
    if ('0' != inByteStr[0]) {
    	return 1;
    }
    if ('x' != inByteStr[1]) {
    	return 2;
    }
    if( is_hex_digit (inByteStr[2]) ) {
    	return 4;
    }
    if( is_hex_digit (inByteStr[3]) ) {
    	return 5;
    }

    return 0;
}


// ret 0 if arrays are equal
// ret 1.....size if arrays are not equal
int my_memcmp(const unsigned char *inArray1,
		      const unsigned char *inArray2,
			  int size)
{
	printf("\nsize of array: %d ", size);
	int res = 0;
	for (int i=0; i<size; i++) {
		if (inArray1[i]!=inArray2[i]) {
			printf("\ni %d",i);
			printf("\ninArray1[%d] %x(%c)",i,inArray1[i],inArray1[i]);
			printf("\ninArray2[%d] %x(%c)",i,inArray2[i],inArray2[i]);
			return i+1;
		}
	}
	return res;
}






struct Node_t {
    int data;
    struct Node_t *nextNode;
};// 8 byte

// Find previous node of single linked list based on full RAM review.
int find_prev_node (struct Node_t *curNode, //in
                    struct Node_t **prevNode, // out
                    int *prevNodeCnt) // out 
{
  struct Node_t *runNode = NULL;
  *prevNode = NULL;
  *prevNodeCnt = 0;
  int sizeofNode = sizeof(struct Node_t );
  for (int addr = FIRST_SRAM_ADDR; addr <= LAST_SRAM_ADDR-sizeofNode; addr++){
      runNode = ( struct Node_t*) addr;
      if(runNode->nextNode == curNode){
	  *prevNode = runNode;
          *prevNodeCnt++;
      }
  }
  if ( 1<*prevNodeCnt ) {
      return 2; // error several prev nodes
  }else if (1==*prevNodeCnt ){
      return 0; // success
  }else{
      return 1; // error lack of prev nodes
  }
}


/* return 0 if character contains only hex digit , else return 1*/
int is_hex_digit (const char character) {
    if (('A' <= character && character <= 'F') || \
        ('a' <= character && character <= 'f') || \
        ('0' <= character && character <= '9')) {
        return 0;
    } else {
        return 1;
    }
}


//0 - is a hex str
//<0 not a hex str
int is_raw_hex_string (char const * const inByteStr, int const lenOfStr) {
    int lenRead;
    if (!inByteStr) {
    	return 1;
    }
    if(!lenOfStr){
    	return 2;
    }
    lenRead = strlen(inByteStr);
    if ( lenRead != lenOfStr ) {
        return 3;
    }
    for (int i=0; i<lenOfStr; i++) {
        if ( is_hex_digit (inByteStr[i]) ) {
            return i+4;
        }
    }
    return 0;
}


//convert string with hex values to byte array in C
int hex_str_to_bin_array (const char * const inStrWithHex, int const inLenOfhexStr,
		                  uint8_t * const outBinStr, int const inSizeOfBinStr) {
	int ret;
	if(!inSizeOfBinStr || !inLenOfhexStr){
	    return 1;
	}

	if (inLenOfhexStr != (inSizeOfBinStr*2)) {
	    return 2;
	}

	if(!inStrWithHex  || !outBinStr){
		return 3;
	}
	ret = is_raw_hex_string (inStrWithHex, inLenOfhexStr);
	if (ret ){
		return 4;
	}
	for (int i=0; i<inSizeOfBinStr; i++) {
		int byteVal=0;
		int ret=-1;
		char strWhithHexByte[3] ={inStrWithHex[2*i],inStrWithHex[2*i+1],'\0'};
		ret = sscanf(strWhithHexByte,"%02x", &byteVal);
		if (1!=ret ) {
			return i+5;
		}
		outBinStr[i] = (uint8_t)  (0x000000FF & byteVal);
	}

	return 0;
}

/* true - array if digit
 * TODO: add unit test for it
 * */
bool is_digit_str (const char  str[]) {
    bool res = true;
    uint32_t index = 0u;
    while ( ((uint8_t) 0x00u) != ((uint8_t) str[index])) {
        if (false == is_valid_digit (str[index])) {
            res = false;
        }
        index++;
    }

    return res;
}

 
bool is_valid_digit (const char character) {
    bool res = false;
    if (('0' <= character) && (character <= '9')) {
        res = true;
    }
    return res;
}

char *uint32_to_bin_str (uint32_t const inVal32bit) {
    static char outBitStr [33] = "";
    int8_t rBit = 0;
    uint8_t cell = 0u;
    uint32_t mask = 0u;
    for (rBit = 31; 0 <= rBit; rBit--) {
        cell = (((uint8_t) 31u) - ((uint8_t) rBit));
        if (cell < sizeof(outBitStr)) {
            mask = (uint32_t) (((uint32_t) 1u) << ((uint32_t) rBit));
            if (0u != (inVal32bit & mask)) {
                outBitStr [cell] = '1';
            } else {
                outBitStr [cell] = '0';
            }
        }
    }
    return outBitStr;
}


/*
 return 0 if value contains only 1 bit set
 1, 2 4 8 16 32 64 128 512 ....
 */
uint32_t is_power_of_two (uint32_t const val) {
    uint32_t outRetPt = (uint32_t) NOT_ONE_BIT_IN_MASK;
    /*check power of two*/
    if (0u == (val & (val - 1u))) {
        /*only one bit set in the value */
        outRetPt = (uint32_t) ONE_BIT_IN_MASK;
    }
    if (0u == val) {
        outRetPt = (uint32_t) NOT_ONE_BIT_IN_MASK;
    }
    return outRetPt;
}


/*
 return 0 if value contains only 1 bit set
 1, 2 4 8 16 32 64 128 512 ....
 */
uint32_t is_one_bit_in_mask (uint32_t const randMask) {
    uint8_t oneCnt = 0u;
    uint16_t curBit = 0u;
    uint32_t outRetM = (uint32_t) NOT_ONE_BIT_IN_MASK;
    uint32_t tempMask = 0u;
    uint8_t amntOfBits = 8u * sizeof(uint32_t);
    /*TODO detach in separate Counting Bits function*/
    for (curBit = 0u; curBit < amntOfBits; curBit++) {
        tempMask = (uint32_t) (((uint32_t) 1u << (curBit)));
        if (0u < (randMask & tempMask)) {
            /*TODO: reset spot set bit in randMask and check if newVal is 0*/
            /*maybe next iterations are senseless*/
            oneCnt++;
        }
    }
    if (1u == oneCnt) {
        outRetM = (uint32_t) ONE_BIT_IN_MASK;
    }

    return outRetM;
}


/*
 *  Odd (Amount of 1 bits is 1 3 5 7 9 and so 31)
 *  even (Amount of 1 bits is 2 4 6 8 10 and so 32)
 *
 *  returns 1 if the parity in inValue is Odd
 *  (Amount of 1 bits is 1 3 5 7 9 and so 31)
 *
 *  inVal  bit         setBit parity
 *  1     > 01       > 1 >    PARITY_ODD
 *  2     > 10       > 1 >    PARITY_ODD
 *  3     > 11       > 2 >    PARITY_EVEN
 *  178   > 10110010 > 4 >    PARITY_EVEN
 */
uint8_t is_parity_odd (uint32_t const inVal) {
    uint8_t otRet = (uint8_t) PARITY_UNDEF;
    uint8_t cntOnes = 0u;
    /*count set bits*/
    cntOnes = count_set_bits (inVal);
    if (0u < (cntOnes & 1u)) {
        otRet = (uint8_t) PARITY_ODD; /*(Amount of 1 bits is 1 3 5 7 9 and so 31)*/
    } else {
        otRet = (uint8_t) PARITY_EVEN; /*(Amount of 1 bits is 2 4 6 8 10 and so 32)*/
    }

    return otRet;
}



/*
 * Function returns the number of set bits in binary
 * representation of positive integer val
 * TODO: we can boost time of calculation by creating look up table for byte->am of bit
 *       It will reqire 512 byte of flash for 8bit value.
 *
 * */
uint8_t count_set_bits (uint32_t const inVal32bit) {
    uint8_t count = 0u;
    int8_t runBit = 0;
    uint32_t val32bit = inVal32bit;
    for (runBit = 31; 0 <= runBit; runBit--) {
        if (0u != (val32bit & (((uint32_t) 1u) << ((uint32_t) runBit)))) {
            count++;
            val32bit &= (uint32_t) (~((((uint32_t) 1u) << ((uint32_t) runBit))));
            if (0u == val32bit) {
                break;
            }
        }
    }
    return count;
}

/*
 * input:  C:/Job/IO_V4/1_FW/components/lib/spc58_gpio/src/gpio.c
 * return: gpio.c
 *
 * */
char *file_name_from_path (char  * const fullPath) {
    char * pFileNeme = NULL;
    pFileNeme = strrchr (fullPath, (int32_t) '/');
    if (NULL != pFileNeme) {
        pFileNeme = strrchr (fullPath, (int32_t) '/');
        pFileNeme++;
    } else {
        pFileNeme = fullPath;
    }

    return pFileNeme;
}


