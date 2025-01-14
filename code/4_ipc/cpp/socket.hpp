#pragma once

#include <iostream>
#include <thread>

// Include platform-specific headers
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#else
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
#endif

void initialize_sockets()
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        exit(1);
    }
#endif
}

void cleanup_sockets()
{
#ifdef _WIN32
    WSACleanup();
#endif
}

void close_socket(SOCKET sock)
{
#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
}

class ClientSocket
{
public:
    // Delete copy operations
    ClientSocket(const ClientSocket &) = delete;
    ClientSocket &operator=(const ClientSocket &) = delete;

    // Implement move operations
    ClientSocket(ClientSocket &&other) noexcept : socket(other.socket)
    {
        other.socket = INVALID_SOCKET; // Important: null out the old socket
    }

    ClientSocket(SOCKET socket) : socket(socket)
    {
    }

    ~ClientSocket()
    {
        close_socket(socket);
    }

    bool send_data(const uint8_t *data, int length)
    {
        if (send(socket, (const char *)data, length, 0) == SOCKET_ERROR)
        {
            return false;
        }
        return true;
    }

    int recv_data(uint8_t *buffer, int buffer_size)
    {
        int bytes_received = recv(socket, (char *)buffer, buffer_size, 0);
        if (bytes_received <= 0)
        {
            return SOCKET_ERROR;
        }
        return bytes_received;
    }

public:
    SOCKET socket;
};

class SocketServer
{
public:
    SocketServer(int port)
    {
        initialize_sockets();

        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == INVALID_SOCKET)
        {
            std::cerr << "Failed to create socket\n";
            cleanup_sockets();
            exit(1);
        }

        // Define server address
        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        // Bind socket
        if (bind(server_socket, (sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR)
        {
            std::cerr << "Binding failed\n";
            close_socket(server_socket);
            cleanup_sockets();
            exit(1);
        }

        // Listen for incoming connections
        if (listen(server_socket, 3) == SOCKET_ERROR)
        {
            std::cerr << "Listening failed\n";
            close_socket(server_socket);
            cleanup_sockets();
            exit(1);
        }

        std::cout << "Server is listening on port " << port << "\n";
    }

    ~SocketServer()
    {
        close_socket(server_socket);
        cleanup_sockets();
    }

    std::optional<ClientSocket> accept_connection()
    {
        sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        SOCKET client_socket = accept(server_socket, (sockaddr *)&client_address, &client_len);
        if (client_socket == INVALID_SOCKET)
        {
            std::cerr << "Failed to accept connection\n";
            return std::nullopt;
        }

        return std::make_optional(ClientSocket(client_socket));
    }

private:
    SOCKET server_socket;
};
