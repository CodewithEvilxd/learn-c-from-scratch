# 💬 TCP Client-Server Chat Application
## Real-time messaging system with multiple clients

---

## 📋 Project Overview

This project implements a complete TCP-based client-server chat application in C. The server handles multiple concurrent clients using threading, while clients can send and receive messages in real-time. This demonstrates network programming, multi-threading, and inter-process communication concepts.

## 🎯 Learning Objectives

- Understand TCP socket programming
- Learn multi-threaded server design
- Practice client-server architecture
- Implement real-time communication
- Learn network error handling

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Platform**: Linux/Unix (POSIX compliant)
- **Libraries**: POSIX sockets, threads
- **Compiler**: GCC with networking support

## 📁 Project Structure

```
chat_application/
├── src/
│   ├── server.c         # Multi-threaded chat server
│   ├── client.c         # Chat client
│   ├── common.c         # Shared utilities
│   └── main.c          # Program entry point
├── include/
│   ├── server.h
│   ├── client.h
│   └── common.h
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Common Definitions**

```c
// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define MAX_USERNAME 32

typedef struct {
    int socket_fd;
    char username[MAX_USERNAME];
    struct sockaddr_in address;
} ClientInfo;

typedef struct {
    ClientInfo clients[MAX_CLIENTS];
    int client_count;
    pthread_mutex_t mutex;
} ServerState;

// Function prototypes
void error(const char* msg);
void trim_newline(char* str);
int setup_server_socket(int port);
void broadcast_message(ServerState* state, const char* message, int sender_socket);

#endif
```

```c
// common.c
#include "common.h"

void error(const char* msg) {
    perror(msg);
    exit(1);
}

void trim_newline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int setup_server_socket(int port) {
    int server_fd;
    struct sockaddr_in server_addr;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error("Socket creation failed");
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        error("Bind failed");
    }

    // Listen for connections
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        error("Listen failed");
    }

    return server_fd;
}
```

### **Step 2: Multi-threaded Server**

```c
// server.h
#ifndef SERVER_H
#define SERVER_H

#include "common.h"

void* handle_client(void* arg);
void add_client(ServerState* state, int client_socket, struct sockaddr_in client_addr);
void remove_client(ServerState* state, int client_socket);
void broadcast_message(ServerState* state, const char* message, int sender_socket);

#endif
```

```c
// server.c
#include "server.h"

void add_client(ServerState* state, int client_socket, struct sockaddr_in client_addr) {
    pthread_mutex_lock(&state->mutex);

    if (state->client_count >= MAX_CLIENTS) {
        close(client_socket);
        pthread_mutex_unlock(&state->mutex);
        return;
    }

    state->clients[state->client_count].socket_fd = client_socket;
    state->clients[state->client_count].address = client_addr;
    state->client_count++;

    pthread_mutex_unlock(&state->mutex);
}

void remove_client(ServerState* state, int client_socket) {
    pthread_mutex_lock(&state->mutex);

    for (int i = 0; i < state->client_count; i++) {
        if (state->clients[i].socket_fd == client_socket) {
            // Broadcast departure message
            char leave_msg[BUFFER_SIZE];
            sprintf(leave_msg, "User %s has left the chat\n",
                   state->clients[i].username);
            broadcast_message(state, leave_msg, -1);

            // Remove client
            close(client_socket);
            for (int j = i; j < state->client_count - 1; j++) {
                state->clients[j] = state->clients[j + 1];
            }
            state->client_count--;
            break;
        }
    }

    pthread_mutex_unlock(&state->mutex);
}

void broadcast_message(ServerState* state, const char* message, int sender_socket) {
    pthread_mutex_lock(&state->mutex);

    for (int i = 0; i < state->client_count; i++) {
        if (state->clients[i].socket_fd != sender_socket) {
            send(state->clients[i].socket_fd, message, strlen(message), 0);
        }
    }

    pthread_mutex_unlock(&state->mutex);
}

void* handle_client(void* arg) {
    ServerState* state = (ServerState*)arg;
    char buffer[BUFFER_SIZE];
    char username[MAX_USERNAME];

    // Receive username
    memset(buffer, 0, BUFFER_SIZE);
    recv(state->clients[state->client_count - 1].socket_fd, buffer, BUFFER_SIZE, 0);
    trim_newline(buffer);
    strcpy(username, buffer);
    strcpy(state->clients[state->client_count - 1].username, username);

    // Broadcast join message
    char join_msg[BUFFER_SIZE];
    sprintf(join_msg, "User %s has joined the chat\n", username);
    broadcast_message(state, join_msg, -1);

    // Send welcome message
    char welcome_msg[BUFFER_SIZE];
    sprintf(welcome_msg, "Welcome to the chat, %s!\n", username);
    send(state->clients[state->client_count - 1].socket_fd, welcome_msg, strlen(welcome_msg), 0);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(state->clients[state->client_count - 1].socket_fd,
                                buffer, BUFFER_SIZE, 0);

        if (bytes_received <= 0) {
            // Client disconnected
            remove_client(state, state->clients[state->client_count - 1].socket_fd);
            break;
        }

        trim_newline(buffer);

        if (strlen(buffer) > 0) {
            // Format message with username
            char formatted_msg[BUFFER_SIZE + MAX_USERNAME + 10];
            sprintf(formatted_msg, "[%s]: %s\n", username, buffer);

            // Broadcast to all clients
            broadcast_message(state, formatted_msg,
                            state->clients[state->client_count - 1].socket_fd);
        }
    }

    return NULL;
}
```

### **Step 3: Client Implementation**

```c
// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

int connect_to_server(const char* server_ip, int port);
void* receive_messages(void* arg);
void send_message(int socket_fd, const char* message);

#endif
```

```c
// client.c
#include "client.h"

int connect_to_server(const char* server_ip, int port) {
    int client_fd;
    struct sockaddr_in server_addr;

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error("Socket creation failed");
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        error("Invalid address");
    }

    // Connect to server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        error("Connection failed");
    }

    return client_fd;
}

void* receive_messages(void* arg) {
    int socket_fd = *(int*)arg;
    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(socket_fd, buffer, BUFFER_SIZE, 0);

        if (bytes_received <= 0) {
            printf("Disconnected from server\n");
            break;
        }

        printf("%s", buffer);
        fflush(stdout);
    }

    return NULL;
}

void send_message(int socket_fd, const char* message) {
    send(socket_fd, message, strlen(message), 0);
}
```

### **Step 4: Main Programs**

```c
// main.c (Server)
#include "server.h"

int main(int argc, char* argv[]) {
    int server_fd, client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    ServerState state;

    // Initialize server state
    state.client_count = 0;
    pthread_mutex_init(&state.mutex, NULL);

    // Setup server socket
    server_fd = setup_server_socket(PORT);
    printf("Chat server started on port %d\n", PORT);
    printf("Waiting for connections...\n");

    while (1) {
        // Accept new connection
        client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New connection from %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Add client to state
        add_client(&state, client_socket, client_addr);

        // Create thread to handle client
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, &state);
        pthread_detach(thread);
    }

    close(server_fd);
    pthread_mutex_destroy(&state.mutex);
    return 0;
}
```

```c
// Client main program
#include "client.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <username>\n", argv[0]);
        exit(1);
    }

    const char* server_ip = argv[1];
    const char* username = argv[2];

    // Connect to server
    int socket_fd = connect_to_server(server_ip, PORT);
    printf("Connected to server %s:%d\n", server_ip, PORT);

    // Send username
    send_message(socket_fd, username);

    // Create thread to receive messages
    pthread_t receive_thread;
    pthread_create(&receive_thread, NULL, receive_messages, &socket_fd);
    pthread_detach(receive_thread);

    // Main loop for sending messages
    char message[BUFFER_SIZE];
    while (1) {
        fgets(message, BUFFER_SIZE, stdin);

        if (strcmp(message, "/quit\n") == 0) {
            break;
        }

        send_message(socket_fd, message);
    }

    close(socket_fd);
    return 0;
}
```

## 🎯 Key Features

### **✅ Core Networking**
- [x] TCP socket communication
- [x] Client-server architecture
- [x] Multi-client support
- [x] Real-time messaging
- [x] Connection handling

### **✅ Advanced Features**
- [x] Multi-threading
- [x] Thread synchronization
- [x] User management
- [x] Message broadcasting
- [x] Error handling

### **🚀 Extensions**
- [ ] Private messaging
- [ ] File transfer
- [ ] User authentication
- [ ] Chat rooms
- [ ] Message history
- [ ] Encryption

## 🧪 Testing and Usage

### **Running the Server**
```bash
# Compile
gcc -o chat_server main.c server.c common.c -pthread

# Run server
./chat_server
```

### **Running Clients**
```bash
# Terminal 1 - Client 1
gcc -o chat_client client.c common.c -pthread
./chat_client 127.0.0.1 Alice

# Terminal 2 - Client 2
./chat_client 127.0.0.1 Bob

# Terminal 3 - Client 3
./chat_client 127.0.0.1 Charlie
```

### **Sample Chat Session**
```
[Alice]: Hello everyone!
[Bob]: Hi Alice!
[Charlie]: Hey folks!
[Alice]: How's everyone doing?
[Bob]: Great! This chat app works perfectly.
User Alice has left the chat
```

## 📊 Technical Learning Outcomes

### **Network Programming Concepts**
- TCP/IP socket programming
- Client-server model
- Multi-threading in network applications
- Synchronization primitives
- Error handling in network code

### **C Programming Skills**
- POSIX thread usage
- Socket API
- Memory management
- String manipulation
- Real-time programming

## 🚀 Advanced Extensions

### **Private Messaging**
```c
void send_private_message(ServerState* state, const char* sender,
                         const char* recipient, const char* message) {
    // Find recipient and send direct message
}
```

### **File Transfer**
```c
void send_file(int socket_fd, const char* filename) {
    // Implement file transfer protocol
    FILE* file = fopen(filename, "rb");
    // Send file in chunks
}
```

### **User Authentication**
```c
typedef struct {
    char username[MAX_USERNAME];
    char password[64];  // Hashed
} UserCredentials;

bool authenticate_user(const char* username, const char* password) {
    // Check credentials against database
}
```

## 📖 References

- **Beej's Guide to Network Programming**
- **UNIX Network Programming** by Stevens
- **POSIX Threads Programming** by Nichols et al.
- **TCP/IP Illustrated** by Stevens

## 🎯 Real-World Applications

- **Chat Applications**: WhatsApp, Discord, Slack
- **Multiplayer Games**: Real-time game communication
- **IoT Systems**: Device-to-server communication
- **Distributed Systems**: Inter-service communication
- **Real-time Collaboration**: Google Docs, Figma

---

**💬 This project demonstrates real-time network communication and multi-threaded server design in C!**