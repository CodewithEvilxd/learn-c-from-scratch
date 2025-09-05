# 🎯 Assignment 3.1: System Programming

## 📋 Problem Statement

Create a C program that demonstrates system-level programming concepts including process management, inter-process communication, signal handling, and system calls. Implement a simple process monitor and IPC system.

## 🎯 Learning Objectives

- Understand system calls and kernel interaction
- Master process creation and management
- Learn inter-process communication
- Implement signal handling
- Work with system resources
- Understand process scheduling

## 📝 Requirements

1. Create and manage child processes
2. Implement inter-process communication
3. Handle signals properly
4. Monitor system resources
5. Create process synchronization
6. Handle system errors

## 💡 Hints

- Use `fork()` to create child processes
- `pipe()` for IPC between related processes
- `signal()` or `sigaction()` for signal handling
- Check return values of system calls
- Handle zombie processes with `wait()`

## 🔧 Solution

```c
// Assignment 3.1: System Programming
// Process management, IPC, and signal handling

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

// Function prototypes
void demonstrate_process_creation();
void demonstrate_pipes();
void demonstrate_signals();
void demonstrate_process_monitoring();
void signal_handler(int signum);
void child_process_task();

// Global variables for signal handling
volatile sig_atomic_t signal_received = 0;
volatile sig_atomic_t child_count = 0;

int main() {
    printf("=== System Programming Demonstration ===\n\n");

    // Set up signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGCHLD, signal_handler);

    demonstrate_process_creation();
    demonstrate_pipes();
    demonstrate_signals();
    demonstrate_process_monitoring();

    printf("System programming demonstration complete!\n");
    return 0;
}

void demonstrate_process_creation() {
    printf("1. Process Creation and Management\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());

        // Child does some work
        for (int i = 0; i < 5; i++) {
            printf("Child: Count %d\n", i + 1);
            sleep(1);
        }

        printf("Child process exiting\n");
        exit(42);  // Exit with status 42
    } else {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        int status;
        waitpid(pid, &status, 0);  // Wait for child

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal: %d\n", WTERMSIG(status));
        }
    }

    printf("\n");
}

void demonstrate_pipes() {
    printf("2. Inter-Process Communication with Pipes\n");

    int pipefd[2];
    char buffer[100];
    const char* message = "Hello from parent process!";

    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) {
        // Child process - reader
        close(pipefd[1]);  // Close write end

        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        close(pipefd[0]);
        exit(0);
    } else {
        // Parent process - writer
        close(pipefd[0]);  // Close read end

        write(pipefd[1], message, strlen(message) + 1);
        printf("Parent sent: %s\n", message);

        close(pipefd[1]);
        wait(NULL);  // Wait for child
    }

    printf("\n");
}

void demonstrate_signals() {
    printf("3. Signal Handling\n");

    printf("Process PID: %d\n", getpid());
    printf("Sending SIGUSR1 to self in 3 seconds...\n");
    printf("You can also send signals from another terminal:\n");
    printf("kill -USR1 %d\n", getpid());
    printf("kill -INT %d\n", getpid());

    // Set up additional signal handlers
    signal(SIGUSR1, signal_handler);
    signal(SIGTERM, signal_handler);

    // Wait for signals
    printf("Waiting for signals... (Press Ctrl+C to exit)\n");

    while (!signal_received) {
        pause();  // Wait for signal
    }

    printf("Signal received, exiting signal demonstration\n\n");
}

void demonstrate_process_monitoring() {
    printf("4. Process Monitoring\n");

    // Create multiple child processes
    const int NUM_CHILDREN = 3;
    pid_t children[NUM_CHILDREN];

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            continue;
        } else if (pid == 0) {
            // Child process
            child_process_task();
            exit(i + 1);
        } else {
            // Parent process
            children[i] = pid;
            child_count++;
            printf("Created child %d with PID %d\n", i + 1, pid);
        }
    }

    // Monitor children
    printf("Monitoring %d child processes...\n", child_count);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (children[i] > 0) {
            int status;
            pid_t result = waitpid(children[i], &status, 0);

            if (result > 0) {
                if (WIFEXITED(status)) {
                    printf("Child %d (PID %d) exited with status %d\n",
                           i + 1, children[i], WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    printf("Child %d (PID %d) terminated by signal %d\n",
                           i + 1, children[i], WTERMSIG(status));
                }
            }
        }
    }

    printf("All children have finished\n\n");
}

void signal_handler(int signum) {
    switch (signum) {
        case SIGINT:
            printf("\nReceived SIGINT (Ctrl+C)\n");
            signal_received = 1;
            break;
        case SIGUSR1:
            printf("Received SIGUSR1\n");
            break;
        case SIGTERM:
            printf("Received SIGTERM\n");
            signal_received = 1;
            break;
        case SIGCHLD:
            child_count--;
            printf("Child process terminated, %d children remaining\n", child_count);
            break;
        default:
            printf("Received signal %d\n", signum);
    }
}

void child_process_task() {
    // Simulate some work
    srand(getpid());  // Seed random number generator
    int work_time = rand() % 5 + 1;  // 1-5 seconds

    printf("Child %d starting work for %d seconds\n", getpid(), work_time);

    for (int i = 0; i < work_time; i++) {
        sleep(1);
        printf("Child %d: %d seconds elapsed\n", getpid(), i + 1);
    }

    printf("Child %d finished work\n", getpid());
}
```

## 📊 Test Cases

### Test Case 1: Process Creation
```
Expected Output:
Parent process: PID = 1234, Child PID = 1235
Child process: PID = 1235, Parent PID = 1234
Child: Count 1
...
Child process exiting
Child exited with status: 42
```

### Test Case 2: Pipes
```
Expected Output:
Parent sent: Hello from parent process!
Child received: Hello from parent process!
```

### Test Case 3: Signals
```
Expected Output:
Process PID: 1234
Waiting for signals...
[After sending signal]
Received SIGUSR1
```

### Test Case 4: Process Monitoring
```
Expected Output:
Created child 1 with PID 1236
Created child 2 with PID 1237
Created child 3 with PID 1238
Child 1236 finished work
Child 1236 (PID 1236) exited with status 1
...
```

## 🔍 Explanation

1. **fork()**: Creates child process identical to parent
2. **pipe()**: Creates communication channel between processes
3. **signal()**: Registers signal handlers for asynchronous events
4. **waitpid()**: Waits for specific child process to terminate
5. **IPC**: Inter-process communication using pipes
6. **Process Management**: Creating, monitoring, and cleaning up processes

## 🎯 Key Concepts Covered

- Process creation and management
- Inter-process communication
- Signal handling and asynchronous events
- Process synchronization
- System call error handling
- Resource management

## 🚀 Extensions

1. Implement shared memory IPC
2. Add process priority management
3. Create a process scheduler
4. Implement message queues
5. Add network IPC capabilities