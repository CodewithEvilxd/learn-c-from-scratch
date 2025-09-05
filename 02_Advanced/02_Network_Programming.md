# 🌐 Advanced C: Network Programming & Socket Communication

## Building Distributed Systems and Network Applications

---

## 🎯 Learning Objectives

- Master socket programming for TCP/UDP communication
- Understand client-server architecture patterns
- Learn network protocols and data serialization
- Implement secure network communication
- Build scalable network servers
- Handle network errors and timeouts

---

## 📖 Network Programming Fundamentals

**Network programming** involves writing programs that communicate over computer networks using protocols like TCP/IP. C provides low-level socket APIs for building robust network applications.

### **Key Concepts:**
- Socket programming (TCP/UDP)
- Client-server architecture
- Network protocols and serialization
- Asynchronous I/O and event-driven programming
- Security and encryption
- Scalability and performance optimization

---

## 🔌 TCP Socket Programming

### **1. Basic TCP Server**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define BACKLOG 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, BACKLOG) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept connection
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        printf("Accepted connection from %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Handle client
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Received: %s", buffer);

            // Echo back
            write(client_fd, buffer, bytes_read);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
```

### **2. Basic TCP Client**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[] = "Hello from client!";

    // Create socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Send message
    if (write(client_fd, message, strlen(message)) == -1) {
        perror("write");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Receive response
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Server response: %s", buffer);
    }

    close(client_fd);
    return 0;
}
```

### **3. Multi-Client TCP Server with Threads**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define BACKLOG 10
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 100

typedef struct {
    int client_fd;
    struct sockaddr_in client_addr;
} client_info_t;

void* handle_client(void* arg) {
    client_info_t* client_info = (client_info_t*)arg;
    int client_fd = client_info->client_fd;
    char buffer[BUFFER_SIZE];
    char client_ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &client_info->client_addr.sin_addr,
              client_ip, sizeof(client_ip));

    printf("Thread handling client %s:%d\n", client_ip,
           ntohs(client_info->client_addr.sin_port));

    while (1) {
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                printf("Client %s disconnected\n", client_ip);
            } else {
                perror("read");
            }
            break;
        }

        buffer[bytes_read] = '\0';
        printf("Received from %s: %s", client_ip, buffer);

        // Echo back
        if (write(client_fd, buffer, bytes_read) == -1) {
            perror("write");
            break;
        }
    }

    close(client_fd);
    free(client_info);
    return NULL;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t thread_id;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, BACKLOG) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Multi-threaded server listening on port %d\n", PORT);

    while (1) {
        // Accept connection
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        // Create client info
        client_info_t* client_info = malloc(sizeof(client_info_t));
        if (client_info == NULL) {
            perror("malloc");
            close(client_fd);
            continue;
        }

        client_info->client_fd = client_fd;
        client_info->client_addr = client_addr;

        // Create thread for client
        if (pthread_create(&thread_id, NULL, handle_client, client_info) != 0) {
            perror("pthread_create");
            close(client_fd);
            free(client_info);
            continue;
        }

        // Detach thread
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}
```

---

## 📡 UDP Socket Programming

### **1. UDP Server**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create UDP socket
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("UDP server listening on port %d\n", PORT);

    while (1) {
        // Receive data
        ssize_t bytes_read = recvfrom(server_fd, buffer, sizeof(buffer) - 1, 0,
                                    (struct sockaddr*)&client_addr, &client_len);
        if (bytes_read == -1) {
            perror("recvfrom");
            continue;
        }

        buffer[bytes_read] = '\0';

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

        printf("Received from %s:%d: %s", client_ip,
               ntohs(client_addr.sin_port), buffer);

        // Echo back
        if (sendto(server_fd, buffer, bytes_read, 0,
                  (struct sockaddr*)&client_addr, client_len) == -1) {
            perror("sendto");
        }
    }

    close(server_fd);
    return 0;
}
```

### **2. UDP Client**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[] = "Hello from UDP client!";

    // Create UDP socket
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Send message
    if (sendto(client_fd, message, strlen(message), 0,
              (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("sendto");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to server\n");

    // Receive response
    socklen_t server_len = sizeof(server_addr);
    ssize_t bytes_read = recvfrom(client_fd, buffer, sizeof(buffer) - 1, 0,
                                (struct sockaddr*)&server_addr, &server_len);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Server response: %s", buffer);
    } else {
        perror("recvfrom");
    }

    close(client_fd);
    return 0;
}
```

---

## 🔐 Secure Network Communication

### **1. SSL/TLS with OpenSSL**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8443
#define CERT_FILE "server.crt"
#define KEY_FILE "server.key"

SSL_CTX* create_ssl_context() {
    const SSL_METHOD* method = TLS_server_method();
    SSL_CTX* ctx = SSL_CTX_new(method);

    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void configure_ssl_context(SSL_CTX* ctx) {
    // Load certificate
    if (SSL_CTX_use_certificate_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // Load private key
    if (SSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // Verify private key
    if (!SSL_CTX_check_private_key(ctx)) {
        fprintf(stderr, "Private key does not match certificate\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Initialize OpenSSL
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    // Create SSL context
    SSL_CTX* ctx = create_ssl_context();
    configure_ssl_context(ctx);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind and listen
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 10);

    printf("HTTPS server listening on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        // Create SSL connection
        SSL* ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client_fd);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        } else {
            char buffer[1024];
            int bytes = SSL_read(ssl, buffer, sizeof(buffer));
            if (bytes > 0) {
                buffer[bytes] = '\0';
                printf("Received: %s", buffer);

                // Send response
                const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from HTTPS server!";
                SSL_write(ssl, response, strlen(response));
            }
        }

        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client_fd);
    }

    SSL_CTX_free(ctx);
    close(server_fd);
    return 0;
}
```

### **2. Data Serialization**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Message structure
typedef struct {
    uint32_t id;
    uint16_t type;
    uint16_t length;
    char data[];
} __attribute__((packed)) Message;

// Serialize message
size_t serialize_message(const Message* msg, uint8_t* buffer, size_t buffer_size) {
    size_t required_size = sizeof(Message) + msg->length;

    if (buffer_size < required_size) {
        return 0;  // Buffer too small
    }

    // Copy header
    memcpy(buffer, msg, sizeof(Message));

    // Copy data
    memcpy(buffer + sizeof(Message), msg->data, msg->length);

    return required_size;
}

// Deserialize message
Message* deserialize_message(const uint8_t* buffer, size_t buffer_size) {
    if (buffer_size < sizeof(Message)) {
        return NULL;
    }

    const Message* header = (const Message*)buffer;
    size_t required_size = sizeof(Message) + header->length;

    if (buffer_size < required_size) {
        return NULL;
    }

    // Allocate message
    Message* msg = malloc(required_size);
    if (msg == NULL) {
        return NULL;
    }

    // Copy data
    memcpy(msg, buffer, required_size);

    return msg;
}

// Send message over network
int send_message(int socket_fd, const Message* msg) {
    uint8_t buffer[4096];
    size_t size = serialize_message(msg, buffer, sizeof(buffer));

    if (size == 0) {
        return -1;
    }

    // Send size first
    uint32_t net_size = htonl(size);
    if (send(socket_fd, &net_size, sizeof(net_size), 0) != sizeof(net_size)) {
        return -1;
    }

    // Send message
    if (send(socket_fd, buffer, size, 0) != (ssize_t)size) {
        return -1;
    }

    return 0;
}

// Receive message from network
Message* receive_message(int socket_fd) {
    // Receive size
    uint32_t net_size;
    if (recv(socket_fd, &net_size, sizeof(net_size), 0) != sizeof(net_size)) {
        return NULL;
    }

    size_t size = ntohl(net_size);
    if (size > 1024 * 1024) {  // 1MB limit
        return NULL;
    }

    uint8_t* buffer = malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    // Receive message
    if (recv(socket_fd, buffer, size, 0) != (ssize_t)size) {
        free(buffer);
        return NULL;
    }

    Message* msg = deserialize_message(buffer, size);
    free(buffer);

    return msg;
}

int main() {
    // Create a message
    const char* data = "Hello, Network!";
    size_t data_len = strlen(data);

    Message* msg = malloc(sizeof(Message) + data_len);
    if (msg == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    msg->id = 12345;
    msg->type = 1;
    msg->length = data_len;
    memcpy(msg->data, data, data_len);

    // Serialize
    uint8_t buffer[1024];
    size_t serialized_size = serialize_message(msg, buffer, sizeof(buffer));
    printf("Serialized size: %zu bytes\n", serialized_size);

    // Deserialize
    Message* deserialized = deserialize_message(buffer, serialized_size);
    if (deserialized) {
        printf("Deserialized message: ID=%u, Type=%u, Data='%.*s'\n",
               deserialized->id, deserialized->type,
               deserialized->length, deserialized->data);
        free(deserialized);
    }

    free(msg);
    return 0;
}
```

---

## ⚡ Asynchronous Network Programming

### **1. Non-blocking I/O**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    fd_set read_fds, active_fds;
    int max_fd;

    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set non-blocking
    if (set_nonblocking(server_fd) == -1) {
        perror("set_nonblocking");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind and listen
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, BACKLOG);

    // Initialize fd sets
    FD_ZERO(&active_fds);
    FD_SET(server_fd, &active_fds);
    max_fd = server_fd;

    printf("Non-blocking server started on port %d\n", PORT);

    while (1) {
        read_fds = active_fds;

        // Wait for activity
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (activity == -1) {
            perror("select");
            continue;
        }

        // Check server socket
        if (FD_ISSET(server_fd, &read_fds)) {
            client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
            if (client_fd != -1) {
                set_nonblocking(client_fd);
                FD_SET(client_fd, &active_fds);
                if (client_fd > max_fd) max_fd = client_fd;

                printf("New connection from %s:%d\n",
                       inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            }
        }

        // Check client sockets
        for (int fd = server_fd + 1; fd <= max_fd; fd++) {
            if (FD_ISSET(fd, &read_fds)) {
                char buffer[BUFFER_SIZE];
                ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

                if (bytes_read <= 0) {
                    // Connection closed or error
                    close(fd);
                    FD_CLR(fd, &active_fds);
                    printf("Client disconnected\n");
                } else {
                    buffer[bytes_read] = '\0';
                    printf("Received: %s", buffer);

                    // Echo back
                    write(fd, buffer, bytes_read);
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
```

### **2. Event-Driven Server with epoll**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#define PORT 8080
#define MAX_EVENTS 64
#define BUFFER_SIZE 1024

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    int server_fd, epoll_fd;
    struct sockaddr_in server_addr;
    struct epoll_event event, events[MAX_EVENTS];

    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    set_nonblocking(server_fd);

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, SOMAXCONN);

    // Create epoll instance
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // Add server socket to epoll
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }

    printf("Event-driven server started on port %d\n", PORT);

    while (1) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        for (int i = 0; i < num_events; i++) {
            if (events[i].data.fd == server_fd) {
                // New connection
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

                if (client_fd != -1) {
                    set_nonblocking(client_fd);

                    event.events = EPOLLIN | EPOLLET;  // Edge-triggered
                    event.data.fd = client_fd;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);

                    printf("New connection from %s:%d\n",
                           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                }
            } else {
                // Client data
                int client_fd = events[i].data.fd;
                char buffer[BUFFER_SIZE];

                ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
                if (bytes_read <= 0) {
                    // Connection closed
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
                    close(client_fd);
                    printf("Client disconnected\n");
                } else {
                    buffer[bytes_read] = '\0';
                    printf("Received: %s", buffer);

                    // Echo back
                    write(client_fd, buffer, bytes_read);
                }
            }
        }
    }

    close(epoll_fd);
    close(server_fd);
    return 0;
}
```

---

## 📊 Network Protocols and Serialization

### **1. HTTP Server Implementation**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 4096

// HTTP Response structure
typedef struct {
    int status_code;
    char* status_text;
    char* content_type;
    char* body;
    size_t body_length;
} HttpResponse;

// Parse HTTP request
void parse_http_request(const char* request, char* method, char* path) {
    sscanf(request, "%s %s", method, path);
}

// Create HTTP response
char* create_http_response(HttpResponse* response) {
    char* response_str = malloc(BUFFER_SIZE);
    if (response_str == NULL) return NULL;

    time_t now = time(NULL);
    struct tm* time_info = gmtime(&now);
    char date[64];
    strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S GMT", time_info);

    snprintf(response_str, BUFFER_SIZE,
             "HTTP/1.1 %d %s\r\n"
             "Date: %s\r\n"
             "Server: C-HTTP-Server/1.0\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%s",
             response->status_code, response->status_text,
             date, response->content_type,
             response->body_length, response->body);

    return response_str;
}

// Handle HTTP request
HttpResponse* handle_request(const char* method, const char* path) {
    HttpResponse* response = calloc(1, sizeof(HttpResponse));

    if (strcmp(method, "GET") == 0) {
        if (strcmp(path, "/") == 0) {
            response->status_code = 200;
            response->status_text = "OK";
            response->content_type = "text/html";
            response->body = "<html><body><h1>Hello from C HTTP Server!</h1></body></html>";
            response->body_length = strlen(response->body);
        } else if (strcmp(path, "/time") == 0) {
            response->status_code = 200;
            response->status_text = "OK";
            response->content_type = "text/plain";

            time_t now = time(NULL);
            response->body = ctime(&now);
            response->body_length = strlen(response->body);
        } else {
            response->status_code = 404;
            response->status_text = "Not Found";
            response->content_type = "text/plain";
            response->body = "404 Not Found";
            response->body_length = strlen(response->body);
        }
    } else {
        response->status_code = 405;
        response->status_text = "Method Not Allowed";
        response->content_type = "text/plain";
        response->body = "405 Method Not Allowed";
        response->body_length = strlen(response->body);
    }

    return response;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind and listen
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 10);

    printf("HTTP server listening on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';

            char method[16], path[256];
            parse_http_request(buffer, method, path);

            printf("Request: %s %s\n", method, path);

            HttpResponse* response = handle_request(method, path);
            char* response_str = create_http_response(response);

            if (response_str) {
                write(client_fd, response_str, strlen(response_str));
                free(response_str);
            }

            free(response);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
```

---

## 🎯 Best Practices for Network Programming

### **1. Error Handling**
```c
// Robust error handling
int safe_send(int sockfd, const void* buffer, size_t length) {
    size_t sent = 0;

    while (sent < length) {
        ssize_t result = send(sockfd, (char*)buffer + sent, length - sent, 0);

        if (result == -1) {
            if (errno == EINTR) continue;  // Interrupted, retry
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // Would block, handle asynchronously
                return sent;
            }
            return -1;  // Real error
        }

        sent += result;
    }

    return sent;
}
```

### **2. Connection Management**
```c
// Connection pooling
#define MAX_CONNECTIONS 100

typedef struct {
    int socket_fd;
    time_t last_used;
    int in_use;
} Connection;

Connection connection_pool[MAX_CONNECTIONS];

int get_connection(const char* host, int port) {
    // Find available connection
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (!connection_pool[i].in_use) {
            // Create new connection
            connection_pool[i].socket_fd = create_connection(host, port);
            connection_pool[i].in_use = 1;
            connection_pool[i].last_used = time(NULL);
            return i;
        }
    }
    return -1;  // No available connections
}

void release_connection(int conn_id) {
    if (conn_id >= 0 && conn_id < MAX_CONNECTIONS) {
        connection_pool[conn_id].in_use = 0;
        connection_pool[conn_id].last_used = time(NULL);
    }
}
```

### **3. Security Considerations**
```c
// Input validation
int validate_hostname(const char* hostname) {
    if (hostname == NULL || strlen(hostname) == 0 || strlen(hostname) > 253) {
        return 0;
    }

    // Check for valid characters
    for (const char* p = hostname; *p; p++) {
        if (!isalnum(*p) && *p != '-' && *p != '.') {
            return 0;
        }
    }

    return 1;
}

// Secure socket options
int setup_secure_socket(int sockfd) {
    // Disable Nagle's algorithm for low latency
    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));

    // Set keepalive
    setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag));

    // Set timeouts
    struct timeval timeout = {30, 0};  // 30 seconds
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    return 0;
}
```

---

## 📝 Practice Exercises

### **Exercise 1: TCP Communication**
- Build a simple chat application with multiple clients
- Implement file transfer over TCP sockets
- Create a basic HTTP proxy server

### **Exercise 2: UDP Applications**
- Develop a DNS client using UDP
- Build a real-time multiplayer game server
- Implement a syslog client for remote logging

### **Exercise 3: Security**
- Add SSL/TLS encryption to TCP server
- Implement authentication and authorization
- Create secure data serialization with encryption

### **Exercise 4: Performance**
- Optimize server for high concurrency
- Implement connection pooling
- Add compression to network protocols

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the difference between TCP and UDP?
a) TCP is connection-oriented, UDP is connectionless
b) TCP guarantees delivery, UDP does not
c) TCP is faster than UDP
d) Both A and B

### **Question 2:**
Which function is used to create a socket?
a) `create_socket()`
b) `socket()`
c) `new_socket()`
d) `open_socket()`

### **Question 3:**
What does `bind()` function do?
a) Connects to a remote server
b) Associates socket with local address
c) Sends data over network
d) Receives data from network

### **Question 4:**
Which port is typically used for HTTPS?
a) 80
b) 443
c) 8080
d) 8443

### **Question 5:**
What is the purpose of `select()` in network programming?
a) Choose network interface
b) Wait for multiple file descriptors
c) Select protocol type
d) Choose IP address

---

## 🔗 Additional Resources

### **Network Programming**
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [Unix Network Programming](https://www.amazon.com/Unix-Network-Programming-Interprocess-Communications/dp/0131411551)
- [TCP/IP Illustrated](https://www.amazon.com/TCP-IP-Illustrated-Vol-Implementation/dp/0201633469)

### **Further Reading**
- [RFC Documents](https://tools.ietf.org/rfc/)
- [POSIX Socket API](https://pubs.opengroup.org/onlinepubs/9699919799/)
- [OpenSSL Documentation](https://www.openssl.org/docs/)

---

## 🎯 Next Steps

**Congratulations!** You've mastered:
- ✅ TCP and UDP socket programming
- ✅ Client-server architecture
- ✅ Secure network communication
- ✅ Asynchronous I/O and event-driven programming
- ✅ Network protocols and serialization
- ✅ Performance optimization techniques

**Next Lesson Preview:**
- Multi-threading and concurrency
- Database integration and SQL
- Web API development
- Containerization with Docker
- Cloud deployment strategies

---

**🚀 Ready to explore multi-threading?**

[⬅️ Previous: System Programming](01_System_Programming.md) | [Next: Multi-threading](03_Multi_threading.md)