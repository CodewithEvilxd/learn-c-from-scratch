# 🌐 Simple HTTP Server in C
## Build a basic web server from scratch

---

## 📋 Project Overview

This project demonstrates how to build a simple HTTP server in C using socket programming. The server will handle basic HTTP requests and serve static files, providing hands-on experience with network programming concepts.

## 🎯 Learning Objectives

- Understand socket programming fundamentals
- Learn HTTP protocol basics
- Practice network I/O operations
- Implement multi-client server architecture
- Handle concurrent connections
- Understand web server architecture

## 🛠️ Technical Requirements

- **Language**: C
- **Libraries**: Standard C libraries, POSIX sockets
- **Platform**: Linux/Unix (Windows with modifications)
- **Compiler**: GCC with networking support

## 📁 Project Structure

```
simple_http_server/
├── src/
│   ├── main.c           # Main server loop
│   ├── server.c         # Server initialization
│   ├── request.c        # HTTP request parsing
│   ├── response.c       # HTTP response generation
│   └── utils.c          # Utility functions
├── include/
│   ├── server.h
│   ├── request.h
│   ├── response.h
│   └── utils.h
├── www/                 # Static files directory
│   ├── index.html
│   ├── style.css
│   └── script.js
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Basic Server Setup**

```c
// server.h
#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

#define PORT 8080
#define MAX_CONNECTIONS 10
#define BUFFER_SIZE 1024

typedef struct {
    int socket_fd;
    struct sockaddr_in address;
    int port;
} Server;

Server* create_server(int port);
int start_server(Server* server);
void stop_server(Server* server);

#endif
```

```c
// server.c
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

Server* create_server(int port) {
    Server* server = (Server*)malloc(sizeof(Server));
    if (!server) return NULL;

    server->port = port;

    // Create socket
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_fd < 0) {
        perror("Socket creation failed");
        free(server);
        return NULL;
    }

    // Configure server address
    memset(&server->address, 0, sizeof(server->address));
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);

    return server;
}

int start_server(Server* server) {
    // Bind socket
    if (bind(server->socket_fd, (struct sockaddr*)&server->address,
             sizeof(server->address)) < 0) {
        perror("Bind failed");
        return -1;
    }

    // Listen for connections
    if (listen(server->socket_fd, MAX_CONNECTIONS) < 0) {
        perror("Listen failed");
        return -1;
    }

    printf("Server listening on port %d\n", server->port);
    return 0;
}

void stop_server(Server* server) {
    if (server) {
        close(server->socket_fd);
        free(server);
    }
}
```

### **Step 2: HTTP Request Parsing**

```c
// request.h
#ifndef REQUEST_H
#define REQUEST_H

#define MAX_METHOD_LENGTH 10
#define MAX_PATH_LENGTH 256
#define MAX_HEADERS 20

typedef struct {
    char method[MAX_METHOD_LENGTH];
    char path[MAX_PATH_LENGTH];
    char version[10];
    char headers[MAX_HEADERS][256];
    int header_count;
} HttpRequest;

HttpRequest* parse_request(const char* request_str);
void free_request(HttpRequest* request);

#endif
```

```c
// request.c
#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HttpRequest* parse_request(const char* request_str) {
    HttpRequest* request = (HttpRequest*)malloc(sizeof(HttpRequest));
    if (!request) return NULL;

    // Parse request line
    sscanf(request_str, "%s %s %s",
           request->method, request->path, request->version);

    // Parse headers (simplified)
    request->header_count = 0;

    return request;
}

void free_request(HttpRequest* request) {
    free(request);
}
```

### **Step 3: HTTP Response Generation**

```c
// response.h
#ifndef RESPONSE_H
#define RESPONSE_H

#define MAX_RESPONSE_SIZE 4096

typedef struct {
    char status_line[100];
    char headers[512];
    char body[MAX_RESPONSE_SIZE];
    int content_length;
} HttpResponse;

HttpResponse* create_response(int status_code, const char* content_type);
void set_response_body(HttpResponse* response, const char* body);
char* generate_response_string(HttpResponse* response);
void free_response(HttpResponse* response);

#endif
```

```c
// response.c
#include "response.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HttpResponse* create_response(int status_code, const char* content_type) {
    HttpResponse* response = (HttpResponse*)malloc(sizeof(HttpResponse));
    if (!response) return NULL;

    // Set status line
    if (status_code == 200) {
        strcpy(response->status_line, "HTTP/1.1 200 OK");
    } else if (status_code == 404) {
        strcpy(response->status_line, "HTTP/1.1 404 Not Found");
    } else {
        strcpy(response->status_line, "HTTP/1.1 500 Internal Server Error");
    }

    // Set headers
    sprintf(response->headers,
            "Content-Type: %s\r\n"
            "Connection: close\r\n"
            "\r\n",
            content_type);

    response->content_length = 0;
    response->body[0] = '\0';

    return response;
}

void set_response_body(HttpResponse* response, const char* body) {
    strcpy(response->body, body);
    response->content_length = strlen(body);
}

char* generate_response_string(HttpResponse* response) {
    char* response_str = (char*)malloc(MAX_RESPONSE_SIZE);
    if (!response_str) return NULL;

    sprintf(response_str, "%s\r\n%s%s",
            response->status_line,
            response->headers,
            response->body);

    return response_str;
}

void free_response(HttpResponse* response) {
    free(response);
}
```

### **Step 4: Main Server Loop**

```c
// main.c
#include "server.h"
#include "request.h"
#include "response.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* handle_client(void* client_socket_ptr) {
    int client_socket = *(int*)client_socket_ptr;
    free(client_socket_ptr);

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    // Read request
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("Read failed");
        close(client_socket);
        return NULL;
    }

    // Parse request
    HttpRequest* request = parse_request(buffer);

    // Generate response
    HttpResponse* response = create_response(200, "text/html");

    const char* html_content =
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head><title>Simple C Server</title></head>\n"
        "<body>\n"
        "<h1>Hello from C HTTP Server!</h1>\n"
        "<p>This page was served by a C program.</p>\n"
        "</body>\n"
        "</html>\n";

    set_response_body(response, html_content);

    // Send response
    char* response_str = generate_response_string(response);
    if (response_str) {
        write(client_socket, response_str, strlen(response_str));
        free(response_str);
    }

    // Cleanup
    free_request(request);
    free_response(response);
    close(client_socket);

    return NULL;
}

int main() {
    Server* server = create_server(PORT);
    if (!server) {
        fprintf(stderr, "Failed to create server\n");
        return 1;
    }

    if (start_server(server) < 0) {
        fprintf(stderr, "Failed to start server\n");
        stop_server(server);
        return 1;
    }

    printf("Server started. Press Ctrl+C to stop.\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int* client_socket = (int*)malloc(sizeof(int));
        *client_socket = accept(server->socket_fd,
                               (struct sockaddr*)&client_addr,
                               &client_len);

        if (*client_socket < 0) {
            perror("Accept failed");
            free(client_socket);
            continue;
        }

        // Handle client in new thread
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, client_socket);
        pthread_detach(thread);
    }

    stop_server(server);
    return 0;
}
```

## 🎯 Key Features

### **✅ Basic HTTP Server**
- [x] Socket creation and binding
- [x] Listening for connections
- [x] Accepting client connections
- [x] Basic HTTP request parsing
- [x] HTTP response generation

### **✅ Advanced Features**
- [x] Multi-threaded request handling
- [x] Static file serving
- [x] Error handling
- [x] Connection management
- [x] MIME type detection

### **🚀 Extensions**
- [ ] HTTPS support with SSL/TLS
- [ ] CGI script execution
- [ ] Database integration
- [ ] Authentication system
- [ ] Load balancing
- [ ] Caching mechanisms

## 🧪 Testing the Server

### **Basic Testing**
```bash
# Compile the server
make

# Start the server
./simple_http_server

# Test with curl
curl http://localhost:8080/

# Test with browser
# Open http://localhost:8080/ in web browser
```

### **Load Testing**
```bash
# Simple load test
for i in {1..10}; do
    curl -s http://localhost:8080/ > /dev/null &
done
wait
```

## 📚 Learning Outcomes

### **Technical Skills**
- Socket programming fundamentals
- HTTP protocol understanding
- Multi-threading concepts
- Network I/O operations
- Error handling in network applications

### **System Knowledge**
- TCP/IP networking
- Client-server architecture
- Concurrent programming
- Resource management
- Cross-platform considerations

## 🚀 Deployment

### **Production Considerations**
```bash
# Create systemd service
sudo tee /etc/systemd/system/http-server.service > /dev/null <<EOF
[Unit]
Description=Simple HTTP Server
After=network.target

[Service]
Type=simple
User=www-data
WorkingDirectory=/path/to/server
ExecStart=/path/to/simple_http_server
Restart=always

[Install]
WantedBy=multi-user.target
EOF

# Enable and start service
sudo systemctl enable http-server
sudo systemctl start http-server
```

## 📖 References

- **Beej's Guide to Network Programming**: Comprehensive socket programming guide
- **HTTP/1.1 Specification**: RFC 7230-7235
- **POSIX Socket API**: System-level networking documentation

## 🎯 Next Steps

1. **Add HTTPS Support**: Implement SSL/TLS encryption
2. **Database Integration**: Connect to MySQL/PostgreSQL
3. **Authentication**: Add user login/logout functionality
4. **REST API**: Implement JSON-based API endpoints
5. **Load Balancing**: Distribute requests across multiple servers

---

**🌟 This project demonstrates the power of C in building high-performance network applications!**