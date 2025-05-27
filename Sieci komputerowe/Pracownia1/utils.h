// Michał Włodarczak 340854

#ifndef UTILS_H
#define UTILS_H

#include <netinet/ip_icmp.h>

//  Funkcja do obliczania checksum w ICMP (wzięta z pliku icmp_checksum.c)
u_int16_t compute_checksum(const void *buff, int length);

// Tworzy pakiet ICMP Echo Request
void create_icmp_packet(struct icmp *icmp_hdr, int seq);

#endif
