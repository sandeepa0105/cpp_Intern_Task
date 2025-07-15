#define _WIN32_WINNT 0x0601  // Windows 7 or later
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <chrono>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }

    const int PORT = 8080;
    const int BUFFER_SIZE = 1024;

    // Create socket
    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Set socket to non-blocking mode
    u_long mode = 1; // 1 to enable non-blocking socket
    iResult = ioctlsocket(sockfd, FIONBIO, &mode);
    if (iResult != NO_ERROR) {
        std::cerr << "Failed to set non-blocking mode: " << iResult << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Setup server address struct
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket
    iResult = bind(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (iResult == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    std::cout << "UDP server listening on port " << PORT << "...\n";

    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddr{};
    int clientLen = sizeof(clientAddr);

    while (true) {
        int bytesReceived = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (sockaddr*)&clientAddr, &clientLen);
        if (bytesReceived == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err == WSAEWOULDBLOCK) {
                // No data available, just continue or do other tasks
                std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Avoid busy waiting
                continue;
            } else {
                std::cerr << "recvfrom failed: " << err << std::endl;
                break;
            }
        }

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0'; // Null-terminate received data

            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);

            std::cout << "Received from " << clientIP << ":" << ntohs(clientAddr.sin_port)
                      << " -> " << buffer << std::endl;
        }
    }

    // Cleanup
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
