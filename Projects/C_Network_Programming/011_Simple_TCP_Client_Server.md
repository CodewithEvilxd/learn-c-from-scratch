# 🌐 **Project 11: TCP Client-Server Chat Application**
## 🎯 **Real-time Network Communication with Multi-threading**

---

## 📋 **Project Overview**

**English:** A complete TCP client-server chat application in C that enables real-time communication between multiple clients, featuring multi-threading, message broadcasting, and connection management.

**Hinglish:** Ek complete TCP client-server chat application jo C mein bani hai, jisme multiple clients ke beech real-time communication enable hoti hai, multi-threading, message broadcasting, aur connection management ke saath.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Socket programming fundamentals
- Multi-threading concepts
- Network communication protocols
- Client-server architecture
- Concurrent programming

✅ **Network Concepts:**
- TCP/IP protocol understanding
- Port and socket management
- Connection handling
- Data transmission
- Network error handling

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Core network logic | Handles socket operations and threading |
| **Socket Library** | Network communication | TCP socket creation and management |
| **Thread Library** | Concurrent processing | Multi-threaded client handling |
| **Network APIs** | System networking | OS-level network functions |

---

## 📁 **Project Structure**

```
TCPChat/
├── include/
│   ├── server.h
│   ├── client.h
│   └── common.h
├── src/
│   ├── server.c
│   ├── client.c
│   ├── common.c
│   └── main.c
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Common Definitions**

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
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define MAX_USERNAME 50

typedef struct {
    int socket_fd;
    char username[MAX_USERNAME];
    int active;
} ClientInfo;

#endif
```

### **2. Server Implementation**

```c
// server.h
#ifndef SERVER_H
#define SERVER_H

#include "common.h"

// Server functions
int setup_server();
void *handle_client(void *arg);
void broadcast_message(char *message, int sender_socket);
void remove_client(int client_socket);
int get_client_count();

#endif
```

```c
// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "server.h"

ClientInfo clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Setup server socket
int setup_server() {
    int server_fd;
    struct sockaddr_in address;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return -1;
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return -1;
    }

    printf("Server listening on port %d\n", PORT);
    return server_fd;
}

// Handle individual client
void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[BUFFER_SIZE];
    char username[MAX_USERNAME];
    int bytes_read;

    // Get username
    bytes_read = read(client_socket, username, MAX_USERNAME);
    if (bytes_read <= 0) {
        close(client_socket);
        return NULL;
    }
    username[bytes_read] = '\0';

    // Add client to list
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!clients[i].active) {
            clients[i].socket_fd = client_socket;
            strcpy(clients[i].username, username);
            clients[i].active = 1;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    // Broadcast join message
    char join_msg[BUFFER_SIZE];
    sprintf(join_msg, "%s joined the chat\n", username);
    broadcast_message(join_msg, client_socket);

    // Handle messages
    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';

        // Format message with username
        char message[BUFFER_SIZE + MAX_USERNAME + 10];
        sprintf(message, "%s: %s", username, buffer);

        // Broadcast to all clients
        broadcast_message(message, client_socket);
    }

    // Client disconnected
    char leave_msg[BUFFER_SIZE];
    sprintf(leave_msg, "%s left the chat\n", username);
    broadcast_message(leave_msg, client_socket);

    // Remove client
    remove_client(client_socket);
    close(client_socket);

    return NULL;
}

// Broadcast message to all clients
void broadcast_message(char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active && clients[i].socket_fd != sender_socket) {
            send(clients[i].socket_fd, message, strlen(message), 0);
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

// Remove client from list
void remove_client(int client_socket) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].socket_fd == client_socket) {
            clients[i].active = 0;
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}
```

### **3. Client Implementation**

```c
// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

// Client functions
int connect_to_server(const char *server_ip);
void *receive_messages(void *arg);
void send_message(int socket_fd, const char *message);

#endif
```

```c
// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "client.h"

// Connect to server
int connect_to_server(const char *server_ip) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    return sock;
}

// Receive messages from server
void *receive_messages(void *arg) {
    int socket_fd = *(int *)arg;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(socket_fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    return NULL;
}

// Send message to server
void send_message(int socket_fd, const char *message) {
    send(socket_fd, message, strlen(message), 0);
}
```

### **4. Main Programs**

```c
// main.c - Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "server.h"

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t thread_id;

    // Initialize clients array
    memset(clients, 0, sizeof(clients));

    // Setup server
    server_fd = setup_server();
    if (server_fd < 0) {
        return 1;
    }

    printf("Chat server started. Waiting for connections...\n");

    while (1) {
        // Accept new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New client connected\n");

        // Create thread for new client
        if (pthread_create(&thread_id, NULL, handle_client, (void *)&new_socket) < 0) {
            perror("Thread creation failed");
            close(new_socket);
        }

        // Detach thread
        pthread_detach(thread_id);
    }

    return 0;
}

// Client main program would be in separate file
int main_client() {
    int sock;
    char username[MAX_USERNAME];
    char message[BUFFER_SIZE];
    pthread_t recv_thread;

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter server IP: ");
    char server_ip[20];
    scanf("%s", server_ip);

    // Connect to server
    sock = connect_to_server(server_ip);
    if (sock < 0) {
        return 1;
    }

    // Send username
    send(sock, username, strlen(username), 0);

    // Start receiving thread
    pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock);
    pthread_detach(recv_thread);

    // Send messages
    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0;

        if (strcmp(message, "/quit") == 0) {
            break;
        }

        send_message(sock, message);
    }

    close(sock);
    return 0;
}
```

---

## 🎯 **Features Implemented**

### **Network Features**
- ✅ TCP socket communication
- ✅ Multi-client support
- ✅ Real-time message broadcasting
- ✅ Connection management
- ✅ Multi-threading

### **Chat Features**
- ✅ User authentication
- ✅ Message broadcasting
- ✅ Join/leave notifications
- ✅ Concurrent client handling
- ✅ Graceful disconnection

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "TCP Chat Application - Real-time Network Communication"
- **Hinglish:** "TCP Chat Application - Real-time Network Communication"

### **Slide 2: What We Built**
- ✅ Complete client-server chat system
- ✅ Multi-threaded server architecture
- ✅ TCP socket communication
- ✅ Real-time message broadcasting
- ✅ Multiple client support

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 10

typedef struct {
    int socket_fd;
    char username[50];
    int active;
} ClientInfo;

// Core functions
int setup_server();
void *handle_client(void *arg);
void broadcast_message(char *message, int sender_socket);
int connect_to_server(const char *server_ip);
```

### **Slide 4: Network Operations**
```c
// Socket programming essentials
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
bind(server_fd, (struct sockaddr *)&address, sizeof(address));
listen(server_fd, 3);
int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

// Client connection
int sock = socket(AF_INET, SOCK_STREAM, 0);
connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Socket programming
- ✅ Multi-threading
- ✅ Network protocols
- ✅ Client-server architecture
- ✅ Concurrent programming

### **Network Concepts:**
- ✅ TCP/IP communication
- ✅ Socket management
- ✅ Connection handling
- ✅ Data transmission
- ✅ Thread synchronization

---

## 📞 **Contact & Support**

**Project Developer:** Network Programming Student
**Email:** network@studentproject.com
**GitHub:** https://github.com/c-network/tcp-chat

---

**🌐 This TCP chat application demonstrates real-time network programming and multi-threaded server architecture in C, perfect for understanding client-server communication and concurrent programming.**