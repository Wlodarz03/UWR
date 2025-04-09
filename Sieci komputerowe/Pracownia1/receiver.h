// Michał Włodarczak 340854

#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>
#include <vector>
#include <map>
#include <netinet/ip_icmp.h>
#include <chrono>

// Odbiera odpowiedź ICMP i zwraca mapę adresów IP do ich czasów RTT
std::map<std::string, std::vector<int>> receive_icmp(int sock_fd, int ttl, std::chrono::high_resolution_clock::time_point timestamps[3]);

#endif
