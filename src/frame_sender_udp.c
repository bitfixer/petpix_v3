// read from stdin in the format:
// 4 byte float timestamp
// row*col bytes from stdin.
// wait appropriate amount of time, then send
// the byte buffer over udp.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <getopt.h>

#define DEFAULT_IP       "127.0.0.1"
#define DEFAULT_PORT     9600
#define DEFAULT_COLUMNS  40
#define ROWS             25

float get_elapsed_seconds(struct timespec start) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (now.tv_sec - start.tv_sec) + (now.tv_nsec - start.tv_nsec) / 1e9f;
}

void sleep_until(float target_seconds, struct timespec start) {
    while (1) {
        float elapsed = get_elapsed_seconds(start);
        if (elapsed >= target_seconds) break;
        usleep(1000); // sleep 1 ms
    }
}

int main(int argc, char *argv[]) {
    char ip[64] = DEFAULT_IP;
    int port = DEFAULT_PORT;
    int columns = DEFAULT_COLUMNS;
    int opt;

    while ((opt = getopt(argc, argv, "a:p:c:")) != -1) {
        switch (opt) {
            case 'a':
                strncpy(ip, optarg, sizeof(ip) - 1);
                ip[sizeof(ip) - 1] = '\0';
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 'c':
                columns = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-a address] [-p port] [-c columns]\n", argv[0]);
                return 1;
        }
    }

    int bytes_per_frame = columns * ROWS;
    uint8_t *buffer = malloc(bytes_per_frame);
    if (!buffer) {
        perror("malloc");
        return 1;
    }

    // Setup UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        free(buffer);
        return 1;
    }

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    if (inet_aton(ip, &dest.sin_addr) == 0) {
        fprintf(stderr, "Invalid IP address: %s\n", ip);
        close(sock);
        free(buffer);
        return 1;
    }

    // Timer initialization
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    float last_timestamp = 0.0f;

    while (1) {
        float timestamp;
        size_t ts_read = fread(&timestamp, sizeof(float), 1, stdin);
        if (ts_read != 1) break;

        if (timestamp < last_timestamp) {
            // Reset time tracking
            clock_gettime(CLOCK_MONOTONIC, &start_time);
        }
        last_timestamp = timestamp;

        size_t data_read = fread(buffer, 1, bytes_per_frame, stdin);
        if (data_read != (size_t)bytes_per_frame) break;

        sleep_until(timestamp, start_time);

        ssize_t sent = sendto(sock, buffer, bytes_per_frame, 0,
                              (struct sockaddr*)&dest, sizeof(dest));
        if (sent != bytes_per_frame) {
            perror("sendto");
            break;
        }
    }

    close(sock);
    free(buffer);
    return 0;
}
