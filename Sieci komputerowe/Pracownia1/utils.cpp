// Michał Włodarczak 340854

#include "utils.h"
#include <cstring>
#include <cassert>
#include <unistd.h>

u_int16_t compute_checksum(const void *buff, int length) {
    const u_int16_t* ptr = (const u_int16_t*) buff;
    u_int32_t sum = 0;
    
    assert(length % 2 == 0);  

    for (; length > 0; length -= 2) {
        sum += *ptr++;
    }
    
    sum = (sum >> 16U) + (sum & 0xFFFFU); 
    return ~(sum + (sum >> 16U));         
}

void create_icmp_packet(struct icmp *icmp_hdr, int seq) {
    memset(icmp_hdr, 0, sizeof(struct icmp));
    icmp_hdr->icmp_type = ICMP_ECHO;
    icmp_hdr->icmp_code = 0;
    icmp_hdr->icmp_id = htons(getpid() % 0xFFFF);
    icmp_hdr->icmp_seq = htons(seq);
    icmp_hdr->icmp_cksum = compute_checksum(icmp_hdr, sizeof(struct icmp));
}
