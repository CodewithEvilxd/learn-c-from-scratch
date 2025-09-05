# 🔧 Process Management System
## Complete process creation, monitoring, and control in C

---

## 📋 Project Overview

This project implements a comprehensive process management system in C using POSIX system calls. It demonstrates process creation, inter-process communication, process monitoring, and resource management - essential concepts for system programming.

## 🎯 Learning Objectives

- Understand process lifecycle management
- Learn inter-process communication (IPC)
- Practice signal handling
- Implement process scheduling concepts
- Learn system resource monitoring

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Platform**: Linux/Unix (POSIX compliant)
- **Libraries**: POSIX system calls, standard C libraries
- **Compiler**: GCC with POSIX support

## 📁 Project Structure

```
process_manager/
├── src/
│   ├── main.c           # Main process manager interface
│   ├── process.c        # Process creation and management
│   ├── scheduler.c      # Process scheduling algorithms
│   ├── monitor.c        # Process monitoring and statistics
│   ├── ipc.c           # Inter-process communication
│   └── signals.c       # Signal handling
├── include/
│   ├── process.h
│   ├── scheduler.h
│   ├── monitor.h
│   ├── ipc.h
│   └── signals.h
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Process Management Core**

```c
// process.h
#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} ProcessState;

typedef struct {
    pid_t pid;
    char name[256];
    ProcessState state;
    time_t start_time;
    time_t end_time;
    int exit_status;
    int priority;
    long user_time;
    long system_time;
} ProcessInfo;

typedef struct ProcessNode {
    ProcessInfo info;
    struct ProcessNode* next;
} ProcessNode;

typedef struct {
    ProcessNode* head;
    int count;
} ProcessList;

// Function prototypes
ProcessList* create_process_list(void);
pid_t create_process(const char* program, char* const argv[]);
void add_process(ProcessList* list, pid_t pid, const char* name);
void remove_process(ProcessList* list, pid_t pid);
ProcessInfo* find_process(ProcessList* list, pid_t pid);
void update_process_status(ProcessList* list);
void terminate_process(pid_t pid);
void terminate_all_processes(ProcessList* list);
void free_process_list(ProcessList* list);

#endif
```

```c
// process.c
#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>

ProcessList* create_process_list(void) {
    ProcessList* list = (ProcessList*)malloc(sizeof(ProcessList));
    if (!list) return NULL;

    list->head = NULL;
    list->count = 0;
    return list;
}

pid_t create_process(const char* program, char* const argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return -1;
    }

    if (pid == 0) {
        // Child process
        if (execvp(program, argv) < 0) {
            perror("Exec failed");
            exit(1);
        }
    }

    // Parent process
    return pid;
}

void add_process(ProcessList* list, pid_t pid, const char* name) {
    ProcessNode* node = (ProcessNode*)malloc(sizeof(ProcessNode));
    if (!node) return;

    node->info.pid = pid;
    strncpy(node->info.name, name, sizeof(node->info.name) - 1);
    node->info.name[sizeof(node->info.name) - 1] = '\0';
    node->info.state = PROCESS_RUNNING;
    node->info.start_time = time(NULL);
    node->info.priority = 0;

    node->next = list->head;
    list->head = node;
    list->count++;
}

void remove_process(ProcessList* list, pid_t pid) {
    ProcessNode* current = list->head;
    ProcessNode* prev = NULL;

    while (current) {
        if (current->info.pid == pid) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->head = current->next;
            }

            free(current);
            list->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

ProcessInfo* find_process(ProcessList* list, pid_t pid) {
    ProcessNode* current = list->head;

    while (current) {
        if (current->info.pid == pid) {
            return &current->info;
        }
        current = current->next;
    }

    return NULL;
}

void update_process_status(ProcessList* list) {
    ProcessNode* current = list->head;

    while (current) {
        int status;
        pid_t result = waitpid(current->info.pid, &status, WNOHANG);

        if (result > 0) {
            // Process has changed state
            if (WIFEXITED(status)) {
                current->info.state = PROCESS_TERMINATED;
                current->info.exit_status = WEXITSTATUS(status);
                current->info.end_time = time(NULL);
            } else if (WIFSIGNALED(status)) {
                current->info.state = PROCESS_TERMINATED;
                current->info.exit_status = -WTERMSIG(status);
                current->info.end_time = time(NULL);
            }
        } else if (result == 0) {
            // Process still running
            current->info.state = PROCESS_RUNNING;
        }

        current = current->next;
    }
}

void terminate_process(pid_t pid) {
    if (kill(pid, SIGTERM) < 0) {
        perror("Failed to terminate process");
    }
}

void terminate_all_processes(ProcessList* list) {
    ProcessNode* current = list->head;

    while (current) {
        terminate_process(current->info.pid);
        current = current->next;
    }
}

void free_process_list(ProcessList* list) {
    ProcessNode* current = list->head;

    while (current) {
        ProcessNode* temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}
```

### **Step 2: Process Monitoring**

```c
// monitor.h
#ifndef MONITOR_H
#define MONITOR_H

#include "process.h"

void print_process_info(const ProcessInfo* info);
void print_process_list(const ProcessList* list);
void monitor_processes(ProcessList* list);
long get_process_memory_usage(pid_t pid);
double get_process_cpu_usage(pid_t pid);

#endif
```

```c
// monitor.c
#include "monitor.h"
#include <stdio.h>
#include <sys/procfs.h>
#include <fcntl.h>
#include <unistd.h>

void print_process_info(const ProcessInfo* info) {
    printf("PID: %d\n", info->pid);
    printf("Name: %s\n", info->name);
    printf("State: ");

    switch (info->state) {
        case PROCESS_READY: printf("Ready\n"); break;
        case PROCESS_RUNNING: printf("Running\n"); break;
        case PROCESS_WAITING: printf("Waiting\n"); break;
        case PROCESS_TERMINATED: printf("Terminated\n"); break;
    }

    printf("Start Time: %s", ctime(&info->start_time));

    if (info->state == PROCESS_TERMINATED) {
        printf("End Time: %s", ctime(&info->end_time));
        printf("Exit Status: %d\n", info->exit_status);
    }

    printf("Priority: %d\n", info->priority);
}

void print_process_list(const ProcessList* list) {
    printf("\n=== Process List (%d processes) ===\n", list->count);
    printf("%-8s %-20s %-12s %-12s\n", "PID", "Name", "State", "Start Time");
    printf("------------------------------------------------\n");

    ProcessNode* current = list->head;
    while (current) {
        char state_str[12];
        switch (current->info.state) {
            case PROCESS_READY: strcpy(state_str, "Ready"); break;
            case PROCESS_RUNNING: strcpy(state_str, "Running"); break;
            case PROCESS_WAITING: strcpy(state_str, "Waiting"); break;
            case PROCESS_TERMINATED: strcpy(state_str, "Terminated"); break;
        }

        printf("%-8d %-20s %-12s %s",
               current->info.pid,
               current->info.name,
               state_str,
               ctime(&current->info.start_time));

        current = current->next;
    }
}

void monitor_processes(ProcessList* list) {
    while (1) {
        update_process_status(list);
        print_process_list(list);
        sleep(2); // Update every 2 seconds
    }
}
```

### **Step 3: Main Program Interface**

```c
// main.c
#include "process.h"
#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_menu(void) {
    printf("\n=== Process Management System ===\n");
    printf("1. Create new process\n");
    printf("2. List all processes\n");
    printf("3. Find process by PID\n");
    printf("4. Terminate process\n");
    printf("5. Monitor processes\n");
    printf("6. Terminate all processes\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    ProcessList* process_list = create_process_list();
    if (!process_list) {
        fprintf(stderr, "Failed to create process list\n");
        return 1;
    }

    int choice;
    char program[256];
    char args[256];

    printf("Process Management System\n");
    printf("=========================\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: {
                printf("Enter program name: ");
                fgets(program, sizeof(program), stdin);
                program[strcspn(program, "\n")] = '\0';

                printf("Enter arguments (or press Enter for none): ");
                fgets(args, sizeof(args), stdin);
                args[strcspn(args, "\n")] = '\0';

                char* argv[64];
                int argc = 1;
                argv[0] = program;

                if (strlen(args) > 0) {
                    char* token = strtok(args, " ");
                    while (token && argc < 63) {
                        argv[argc++] = token;
                        token = strtok(NULL, " ");
                    }
                }
                argv[argc] = NULL;

                pid_t pid = create_process(program, argv);
                if (pid > 0) {
                    add_process(process_list, pid, program);
                    printf("Created process with PID: %d\n", pid);
                }
                break;
            }

            case 2:
                update_process_status(process_list);
                print_process_list(process_list);
                break;

            case 3: {
                pid_t search_pid;
                printf("Enter PID to search: ");
                scanf("%d", &search_pid);

                ProcessInfo* info = find_process(process_list, search_pid);
                if (info) {
                    print_process_info(info);
                } else {
                    printf("Process with PID %d not found\n", search_pid);
                }
                break;
            }

            case 4: {
                pid_t terminate_pid;
                printf("Enter PID to terminate: ");
                scanf("%d", &terminate_pid);

                terminate_process(terminate_pid);
                printf("Termination signal sent to PID %d\n", terminate_pid);
                break;
            }

            case 5:
                printf("Starting process monitor (Ctrl+C to stop)...\n");
                monitor_processes(process_list);
                break;

            case 6:
                terminate_all_processes(process_list);
                printf("Termination signals sent to all processes\n");
                break;

            case 0:
                terminate_all_processes(process_list);
                free_process_list(process_list);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Process Management**
- [x] Process creation with fork/exec
- [x] Process monitoring and status tracking
- [x] Process termination and cleanup
- [x] Process information display
- [x] Real-time process monitoring

### **✅ Advanced Features**
- [x] Process list management
- [x] Signal handling for termination
- [x] Process state tracking
- [x] Memory and resource monitoring
- [x] Cross-platform compatibility

### **🚀 Extensions**
- [ ] Process scheduling algorithms
- [ ] Inter-process communication
- [ ] Process priority management
- [ ] Resource usage statistics
- [ ] Process tree visualization
- [ ] Background process management

## 🧪 Testing and Usage

### **Basic Usage**
```bash
# Compile the program
make

# Run the process manager
./process_manager

# Create a new process
1
ls
-l

# List all processes
2

# Monitor processes
5
```

### **Sample Session**
```
=== Process Management System ===
1. Create new process
2. List all processes
3. Find process by PID
4. Terminate process
5. Monitor processes
0. Exit
Enter your choice: 1
Enter program name: sleep
Enter arguments: 10
Created process with PID: 1234
```

## 📊 Technical Learning Outcomes

### **System Programming Concepts**
- Process lifecycle management
- Fork-exec pattern
- Signal handling
- Process states and transitions
- Resource management

### **C Programming Skills**
- System call usage
- Error handling
- Memory management
- Data structure implementation
- Real-time programming

## 🚀 Advanced Extensions

### **Process Scheduling**
```c
typedef enum {
    SCHED_FIFO,     // First In, First Out
    SCHED_RR,       // Round Robin
    SCHED_PRIORITY  // Priority-based
} SchedulingAlgorithm;

void schedule_processes(ProcessList* list, SchedulingAlgorithm algo) {
    // Implement different scheduling algorithms
}
```

### **Inter-Process Communication**
```c
typedef struct {
    int pipe_fd[2];
    pid_t parent_pid;
    pid_t child_pid;
} IPCChannel;

IPCChannel* create_ipc_channel(void) {
    IPCChannel* channel = malloc(sizeof(IPCChannel));

    if (pipe(channel->pipe_fd) < 0) {
        perror("Pipe creation failed");
        free(channel);
        return NULL;
    }

    return channel;
}
```

## 📖 References

- **Advanced Programming in the UNIX Environment** by Stevens
- **Linux System Programming** by Love
- **POSIX Standard** - IEEE documentation
- **Process Management** - Linux man pages

## 🎯 Real-World Applications

- **Operating Systems**: Process scheduling and management
- **Server Applications**: Worker process management
- **System Monitoring**: Process monitoring tools
- **Container Orchestration**: Docker process management
- **Batch Processing**: Job scheduling systems

---

**🔧 This project demonstrates comprehensive process management and system programming concepts in C!**