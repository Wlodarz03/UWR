// Michał Włodarczak 340854

#include "receiver.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <iostream>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <map>
#include <vector>
#include <chrono>

using namespace std;

map<string, vector<int>> receive_icmp(int sock_fd, int ttl, chrono::high_resolution_clock::time_point timestamps[3]) {
    map<string, vector<int>> responses;
    uint8_t buffer[IP_MAXPACKET];

    int received_count = 0;
    auto start_time = chrono::high_resolution_clock::now();

    while (received_count < 3) {
        int remaining_time = 1000 - chrono::duration_cast<chrono::milliseconds>(
            chrono::high_resolution_clock::now() - start_time).count();
        
        if (remaining_time <= 0) break;

        struct pollfd pfd{sock_fd, POLLIN, 0};
        int ret = poll(&pfd, 1, remaining_time);

        if (ret > 0) {
            struct sockaddr_in addr{};
            socklen_t addr_len = sizeof(addr);

            ssize_t packet_len = recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addr_len);
            auto end = chrono::high_resolution_clock::now();
            if (packet_len < 0) {
                perror("Błąd w recvfrom");
                continue;
            }

            string ip = inet_ntoa(addr.sin_addr);

            struct ip *ip_header = (struct ip *)buffer;
            ssize_t ip_header_len = ip_header->ip_hl * 4;
            struct icmp *icmp_header = (struct icmp *)(buffer + ip_header_len);

            if (icmp_header->icmp_type == ICMP_ECHOREPLY) {
                int seq = ntohs(icmp_header->icmp_seq);
                if (ntohs(icmp_header->icmp_id) == getpid() % 0xFFFF && seq >= 10 * ttl && seq < 10 * ttl + 3) {
                    int index = seq - (10 * ttl);
                    int rtt = chrono::duration_cast<chrono::milliseconds>(end - timestamps[index]).count();
                    responses[ip].push_back(rtt);
                    received_count++;
                }
            }
            else if (icmp_header->icmp_type == ICMP_TIME_EXCEEDED) {
                struct ip *original_ip_header = (struct ip *)(buffer + ip_header_len + sizeof(struct icmphdr));
                struct icmp *original_icmp_header = (struct icmp *)((uint8_t *)original_ip_header + original_ip_header->ip_hl * 4);

                int seq = ntohs(original_icmp_header->icmp_seq);
                if (ntohs(original_icmp_header->icmp_id) == getpid() % 0xFFFF && seq >= 10 * ttl && seq < 10 * ttl + 3) {
                    int index = seq - (10 * ttl);
                    int rtt = chrono::duration_cast<chrono::milliseconds>(end - timestamps[index]).count();
                    responses[ip].push_back(rtt);
                    received_count++;
                }
            }
        }
    }

    return responses;
}