// Michał Włodarczak 340854

#ifndef SENDER_H
#define SENDER_H

#include <chrono>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>

// Wysyła pakiet ICMP i zwraca znacznik czasowy
std::chrono::high_resolution_clock::time_point send_icmp(int sock_fd, struct sockaddr_in *dest_addr, int seq);

#endif