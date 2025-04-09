// Michał Włodarczak 340854

#include <iostream>
#include <cstring>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <map>
#include <vector>

#include "sender.h"
#include "receiver.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Zła ilość argumentów\n";
        return 1;
    }

    struct sockaddr_in dest_addr{};
    dest_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, argv[1], &dest_addr.sin_addr) != 1) {
        cout << "Błąd w adresie docelowym\n";
        return 1;
    }

    int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock_fd < 0) {
        perror("Błąd w tworzeniu gniazda");
        return 1;
    }

    for (int ttl = 1; ttl <= 30; ttl++) {
        if (setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
            perror("Błąd ustawiania TTL");
            return 1;
        }

        high_resolution_clock::time_point timestamps[3];
        for (int i = 0; i < 3; i++) {
            timestamps[i] = send_icmp(sock_fd, &dest_addr, i + 10 * ttl);
        }

        // Odpowiedzi jako adres, z którego odbieramy (string) i czasy rtt każdego z 3 odebranych pakietów
        map<string, vector<int>> responses = receive_icmp(sock_fd, ttl, timestamps);

        cout << ttl << ". ";
        bool isFinished = false;

        if (responses.empty()) {
            cout << "*\n";
        } else {
            for (const auto &[ip, times] : responses) {
                if (ip == argv[1]) {
                    isFinished = true;
                }
                cout << ip << " ";
            }

            bool has_complete_rtt = false;
            int rtt = 0;
            int counter = 0;
            for (const auto &[ip, times] : responses) {
                if (times.size() == 3) {
                    has_complete_rtt = true;
                    int avg_rtt = (times[0] + times[1] + times[2]) / 3;
                    rtt += avg_rtt;
                    counter++;
                }
            }
            if (rtt != 0){
                cout << rtt/counter << "ms\n";
            }

            if (!has_complete_rtt) {
                cout << "???\n";
            }
        }

        if (isFinished) {
            break;
        }
    }

    close(sock_fd);
    return 0;
}