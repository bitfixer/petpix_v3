#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

constexpr int DEFAULT_COLUMNS = 40;
constexpr int ROWS = 25;
constexpr int FRAME_SIZE = DEFAULT_COLUMNS * ROWS;
constexpr const char* DEFAULT_IP = "127.0.0.1";
constexpr int DEFAULT_PORT = 9600;

int connect_to_server(const string& ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        cerr << "Invalid IP address\n";
        exit(1);
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    return sock;
}

int main(int argc, char* argv[]) {
    string ip = DEFAULT_IP;
    int port = DEFAULT_PORT;
    int columns = DEFAULT_COLUMNS;

    // Parse args: --ip x.x.x.x --port NNNN --columns NN
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--ip") == 0 && i + 1 < argc)
            ip = argv[++i];
        else if (strcmp(argv[i], "--port") == 0 && i + 1 < argc)
            port = atoi(argv[++i]);
        else if (strcmp(argv[i], "--columns") == 0 && i + 1 < argc)
            columns = atoi(argv[++i]);
    }

    const int bytes_per_frame = columns * ROWS;
    uint8_t* buffer = new uint8_t[bytes_per_frame];

    float timestamp = 0.0f;
    float time_offset = 0.0f;
    auto start_time = steady_clock::now();

    int sock = connect_to_server(ip, port);

    while (true) {
        // Read timestamp
        if (!cin.read(reinterpret_cast<char*>(&timestamp), sizeof(float))) break;

        // Read frame
        if (!cin.read(reinterpret_cast<char*>(buffer), bytes_per_frame)) break;

        auto now = steady_clock::now();
        float elapsed = duration<float>(now - start_time).count();

        // Reset timer if timestamp goes backwards
        if (timestamp < time_offset) {
            start_time = now;
            time_offset = timestamp;
            elapsed = 0.0f;
        }

        float wait_until = timestamp - time_offset;

        if (elapsed < wait_until) {
            usleep((wait_until - elapsed) * 1'000'000);
        } else if ((elapsed - wait_until) > (1.0f / 30)) {
            // If more than 1 frame (at ~30fps) late, skip
            continue;
        }

        int sent = send(sock, buffer, bytes_per_frame, 0);
        if (sent != bytes_per_frame) {
            cerr << "Error: failed to send full frame.\n";
            break;
        }
    }

    close(sock);
    delete[] buffer;
    return 0;
}
