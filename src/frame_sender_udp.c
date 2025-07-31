// read from stdin in the format:
// 4 byte float timestamp
// row*col bytes from stdin.
// wait appropriate amount of time, then send
// the byte buffer over udp.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <getopt.h>

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 9600
#define DEFAULT_COLUMNS 40
#define ROWS 25

float get_time_sec() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(int argc, char *argv[]) {
    const char *ip_addr = DEFAULT_IP;
    int port = DEFAULT_PORT;
    int columns = DEFAULT_COLUMNS;

    // Parse command-line flags
    int opt;
    while ((opt = getopt(argc, argv, "a:p:c:")) != -1) {
        switch (opt) {
            case 'a': ip_addr = optarg; break;
            case 'p': port = atoi(optarg); break;
            case 'c': columns = atoi(optarg); break;
            default:
                fprintf(stderr, "Usage: %s [-a address] [-p port] [-c columns]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    int bytes_per_frame = ROWS * columns;
    uint8_t *buffer = malloc(bytes_per_frame);
    if (!buffer) {
        perror("malloc");
        return 1;
    }

    // Setup UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    inet_pton(AF_INET, ip_addr, &dest.sin_addr);

    float start_time = get_time_sec();
    float last_timestamp = 0.0f;
    float frame_interval = 0.0f;  // updated after first frame

    while (1) {
        float timestamp;
        if (fread(&timestamp, sizeof(float), 1, stdin) != 1) break;
        if (fread(buffer, 1, bytes_per_frame, stdin) != bytes_per_frame) break;

        float now = get_time_sec();
        float elapsed = now - start_time;

        // Timestamp went backwards — reset clock
        if (timestamp < last_timestamp) {
            start_time = now - timestamp;
            elapsed = timestamp;
        }

        // Estimate frame interval after first valid pair
        if (frame_interval == 0.0f && last_timestamp > 0.0f) {
            frame_interval = timestamp - last_timestamp;
            if (frame_interval < 0.01f) frame_interval = 0.04f;  // fallback to ~25 fps
        }

        last_timestamp = timestamp;

        if (elapsed >= timestamp + frame_interval) {
            // We're a full frame behind — drop this one
            fprintf(stderr, "Dropping frame at timestamp %.3f (%.3f behind)\n", timestamp, elapsed - timestamp);
            continue;
        }

        while ((now = get_time_sec()) < start_time + timestamp) {
            usleep(1000); // sleep for 1ms
        }

        sendto(sock, buffer, bytes_per_frame, 0, (struct sockaddr *)&dest, sizeof(dest));
    }

    close(sock);
    free(buffer);
    return 0;
}
