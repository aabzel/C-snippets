#include "validate_ip_address.h"

#include "convert.h"

char *validIPAddress (char *IP) {
    bool res;
#ifdef DEBUG_VALID_IP
    printf ("\n%s()", __FUNCTION__);
#endif
    char *ip_type = "Neither";
    int32_t len = strlen (IP);
    uint32_t ip_val;
    uint16_t ip6_val[8];
    res = try_strl2ipv4 (IP, len, &ip_val);
    if (true == res) {
        ip_type = "IPv4";
    }
    res = try_strl2ipv6 (IP, len, ip6_val);
    if (true == res) {
        ip_type = "IPv6";
    }
    return ip_type;
}
