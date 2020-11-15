#include "test_validate_ip_address.h"

#include "uTests.h"

bool test_valid_ip_address (void) {
    printf ("\n%s()", __FUNCTION__);
    uint32_t ip4_val;
    uint8_t ip16_val[16];
    EXPECT_EQ_STR ("IPv4", validIPAddress ("172.16.204.1"));
    EXPECT_EQ_STR ("IPv4", validIPAddress ("192.0.0.1"));
    EXPECT_EQ_STR ("Neither", validIPAddress ("2001:0db8:85a3:00000:0:8A2E:0370:7334"));
    EXPECT_FALSE (try_strl2ipv4 ("12..33.4", 8, &ip4_val));
    EXPECT_FALSE (try_strl2ipv6 ("12::33:4:0:0:0:0", 16, &ip16_val));
    EXPECT_EQ_STR ("Neither", validIPAddress ("01.01.01.01"));
    EXPECT_EQ_STR ("Neither", validIPAddress ("12..33.4"));
    EXPECT_EQ_STR ("IPv4", validIPAddress ("172.16.254.1"));
    EXPECT_EQ_STR ("IPv6", validIPAddress ("2001:0db8:85a3:0:0:8A2E:0370:7334"));
    return true;
}
