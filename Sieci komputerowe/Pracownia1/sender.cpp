// Michał Włodarczak 340854

#include "sender.h"
#include "utils.h"
#include <sys/socket.h>
#include <iostream>

std::chrono::high_resolution_clock::time_point send_icmp(int sock_fd, struct sockaddr_in *dest_addr, int seq) {
    struct icmp icmp_hdr;
    create_icmp_packet(&icmp_hdr, seq);

    auto start_time = std::chrono::high_resolution_clock::now();
    if (sendto(sock_fd, &icmp_hdr, sizeof(icmp_hdr), 0, (struct sockaddr *)dest_addr, sizeof(*dest_addr)) < 0) {
        perror("Błąd w wysyłaniu ICMP");
        exit(1);
    }
    return start_time;
}
