# 🚀 Advanced C: System Programming & Low-Level Operations

## Mastering System Calls, Memory Management, and Kernel Interactions

---

## 🎯 Learning Objectives

- Master Unix/Linux system calls and kernel interfaces
- Understand process management and inter-process communication
- Learn advanced memory mapping and shared memory
- Implement signal handling and asynchronous operations
- Master file system operations and device I/O
- Understand system performance monitoring and optimization

---

## 📖 System Programming Fundamentals

**System programming** involves writing code that interacts directly with the operating system kernel, hardware devices, and system resources. It requires deep understanding of OS internals and low-level programming concepts.

### **Key Concepts:**
- System calls and kernel interfaces
- Process and thread management
- Memory mapping and virtual memory
- Signal handling and asynchronous I/O
- Device drivers and hardware interaction
- System performance and monitoring

---

## 🔧 System Calls and Kernel Interfaces

### **1. Basic System Calls**

```c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    // File operations
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Read %zd bytes\n", bytes_read);
    close(fd);

    // Process information
    pid_t pid = getpid();
    pid_t ppid = getppid();
    uid_t uid = getuid();

    printf("PID: %d, PPID: %d, UID: %d\n", pid, ppid, uid);

    return 0;
}
```

### **2. Process Management**

```c
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process: PID=%d, PPID=%d\n", getpid(), getppid());
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl");  // Only reached if execl fails
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal: %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
```

### **3. Advanced Process Control**

```c
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 8192

int child_function(void* arg) {
    printf("Child thread in new process: %s\n", (char*)arg);
    return 0;
}

int main() {
    // Clone system call for thread creation
    char* stack = malloc(STACK_SIZE);
    char* stack_top = stack + STACK_SIZE;

    pid_t pid = clone(child_function, stack_top,
                     CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND,
                     "Hello from cloned process");

    if (pid == -1) {
        perror("clone");
        free(stack);
        exit(EXIT_FAILURE);
    }

    printf("Parent: Created process %d\n", pid);

    waitpid(pid, NULL, 0);
    free(stack);

    return 0;
}
```

---

## 📊 Memory Mapping and Shared Memory

### **1. Memory-Mapped Files**

```c
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char* filename = "example.txt";
    const char* message = "Hello, Memory-Mapped World!";

    // Create and open file
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write initial content
    write(fd, message, strlen(message));

    // Get file size
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Memory map the file
    char* mapped = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE,
                       MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Modify the memory-mapped content
    mapped[0] = 'h';  // Change 'H' to 'h'

    // Sync changes to disk
    if (msync(mapped, sb.st_size, MS_SYNC) == -1) {
        perror("msync");
    }

    printf("Modified content: %.25s\n", mapped);

    // Unmap and close
    munmap(mapped, sb.st_size);
    close(fd);

    return 0;
}
```

### **2. Shared Memory Between Processes**

```c
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE 1024

int main() {
    // Create shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Set size of shared memory
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        char* shared_memory = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE,
                                  MAP_SHARED, shm_fd, 0);
        if (shared_memory == MAP_FAILED) {
            perror("mmap child");
            exit(EXIT_FAILURE);
        }

        printf("Child reading: %s\n", shared_memory);

        // Modify shared memory
        strcpy(shared_memory, "Modified by child process");

        munmap(shared_memory, SHM_SIZE);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        char* shared_memory = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE,
                                  MAP_SHARED, shm_fd, 0);
        if (shared_memory == MAP_FAILED) {
            perror("mmap parent");
            exit(EXIT_FAILURE);
        }

        // Write to shared memory
        strcpy(shared_memory, "Hello from parent process");

        // Wait for child
        wait(NULL);

        printf("Parent reading after child: %s\n", shared_memory);

        munmap(shared_memory, SHM_SIZE);
        shm_unlink(SHM_NAME);
    }

    return 0;
}
```

### **3. Anonymous Memory Mapping**

```c
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 4096

int main() {
    // Allocate anonymous memory
    void* addr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("Allocated memory at: %p\n", addr);

    // Use the memory
    strcpy((char*)addr, "Hello, Anonymous Memory!");
    printf("Content: %s\n", (char*)addr);

    // Protect memory (make it read-only)
    if (mprotect(addr, PAGE_SIZE, PROT_READ) == -1) {
        perror("mprotect");
    }

    // Try to write (this should cause segmentation fault)
    // strcpy((char*)addr, "This will crash");  // Uncomment to test

    printf("Memory protection changed to read-only\n");

    // Unmap memory
    munmap(addr, PAGE_SIZE);

    return 0;
}
```

---

## 📡 Signal Handling and Asynchronous Operations

### **1. Advanced Signal Handling**

```c
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

volatile sig_atomic_t signal_count = 0;
volatile sig_atomic_t last_signal = 0;

void signal_handler(int signum) {
    signal_count++;
    last_signal = signum;

    // Safe operations only in signal handlers
    // No printf, malloc, etc.
}

void advanced_signal_handler(int signum, siginfo_t* info, void* context) {
    printf("Signal %d received from PID: %d\n", signum, info->si_pid);
    printf("Signal code: %d\n", info->si_code);
}

int main() {
    // Block all signals initially
    sigset_t block_mask;
    sigfillset(&block_mask);

    if (sigprocmask(SIG_BLOCK, &block_mask, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    // Set up signal handler
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Set up advanced signal handler
    struct sigaction sa_advanced;
    sa_advanced.sa_sigaction = advanced_signal_handler;
    sigemptyset(&sa_advanced.sa_mask);
    sa_advanced.sa_flags = SA_SIGINFO;

    if (sigaction(SIGUSR1, &sa_advanced, NULL) == -1) {
        perror("sigaction advanced");
        exit(EXIT_FAILURE);
    }

    // Unblock SIGINT
    sigset_t unblock_mask;
    sigemptyset(&unblock_mask);
    sigaddset(&unblock_mask, SIGINT);

    if (sigprocmask(SIG_UNBLOCK, &unblock_mask, NULL) == -1) {
        perror("sigprocmask unblock");
        exit(EXIT_FAILURE);
    }

    printf("Process PID: %d\n", getpid());
    printf("Send SIGINT (Ctrl+C) or SIGUSR1 to test\n");

    // Wait for signals
    while (signal_count < 3) {
        pause();
        printf("Received signal %d, total count: %d\n", last_signal, signal_count);
    }

    printf("Received 3 signals, exiting...\n");
    return 0;
}
```

### **2. Timer Signals and Alarms**

```c
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t timer_expired = 0;

void timer_handler(int signum) {
    timer_expired = 1;
    printf("Timer expired!\n");
}

int main() {
    // Set up timer signal handler
    signal(SIGALRM, timer_handler);

    // Set alarm for 5 seconds
    alarm(5);
    printf("Alarm set for 5 seconds\n");

    // Wait for alarm
    while (!timer_expired) {
        pause();
    }

    // Use setitimer for more precise timing
    struct itimerval timer;
    timer.it_value.tv_sec = 2;     // Initial delay
    timer.it_value.tv_usec = 500000; // 500ms
    timer.it_interval.tv_sec = 1;  // Repeat every 1 second
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("Precise timer set\n");

    // Reset counter
    timer_expired = 0;

    // Wait for 3 timer events
    for (int i = 0; i < 3; i++) {
        timer_expired = 0;
        while (!timer_expired) {
            pause();
        }
    }

    // Cancel timer
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);

    printf("Timer cancelled\n");

    return 0;
}
```

---

## 🔌 Device I/O and Hardware Interaction

### **1. Character Device Operations**

```c
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>  // For console operations
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open console device
    int console_fd = open("/dev/console", O_RDWR);
    if (console_fd == -1) {
        perror("open console");
        exit(EXIT_FAILURE);
    }

    // Get console mode
    int mode;
    if (ioctl(console_fd, KDGKBMODE, &mode) == -1) {
        perror("ioctl KDGKBMODE");
        close(console_fd);
        exit(EXIT_FAILURE);
    }

    printf("Current keyboard mode: %d\n", mode);

    // Set raw mode (for direct key input)
    if (ioctl(console_fd, KDSKBMODE, K_RAW) == -1) {
        perror("ioctl KDSKBMODE");
        close(console_fd);
        exit(EXIT_FAILURE);
    }

    printf("Console set to raw mode\n");

    // Read raw keyboard input
    char buffer[16];
    ssize_t n = read(console_fd, buffer, sizeof(buffer));
    if (n > 0) {
        printf("Raw keyboard data: ");
        for (int i = 0; i < n; i++) {
            printf("%02x ", (unsigned char)buffer[i]);
        }
        printf("\n");
    }

    // Restore original mode
    ioctl(console_fd, KDSKBMODE, mode);
    close(console_fd);

    return 0;
}
```

### **2. GPIO Programming (Raspberry Pi example)**

```c
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// GPIO register offsets (BCM2835)
#define GPIO_BASE 0x20200000
#define GPIO_SET_OFFSET 0x1C
#define GPIO_CLR_OFFSET 0x28
#define GPIO_FSEL_OFFSET 0x00

// GPIO pin numbers
#define GPIO_PIN 17

int main() {
    // Open /dev/mem
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd == -1) {
        perror("open /dev/mem");
        exit(EXIT_FAILURE);
    }

    // Map GPIO registers
    void* gpio_map = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                         MAP_SHARED, mem_fd, GPIO_BASE);
    if (gpio_map == MAP_FAILED) {
        perror("mmap");
        close(mem_fd);
        exit(EXIT_FAILURE);
    }

    volatile uint32_t* gpio = (volatile uint32_t*)gpio_map;

    // Configure GPIO pin as output
    uint32_t fsel_reg = GPIO_FSEL_OFFSET + (GPIO_PIN / 10) * 4;
    uint32_t fsel_shift = (GPIO_PIN % 10) * 3;
    gpio[fsel_reg / 4] &= ~(7 << fsel_shift);  // Clear bits
    gpio[fsel_reg / 4] |= (1 << fsel_shift);   // Set as output

    printf("GPIO pin %d configured as output\n", GPIO_PIN);

    // Blink LED
    for (int i = 0; i < 10; i++) {
        // Turn on
        gpio[GPIO_SET_OFFSET / 4] = (1 << GPIO_PIN);
        usleep(500000);  // 500ms

        // Turn off
        gpio[GPIO_CLR_OFFSET / 4] = (1 << GPIO_PIN);
        usleep(500000);  // 500ms

        printf("Blink %d\n", i + 1);
    }

    // Cleanup
    munmap(gpio_map, 4096);
    close(mem_fd);

    return 0;
}
```

---

## 📈 System Performance Monitoring

### **1. CPU and Memory Statistics**

```c
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>

void print_system_info() {
    struct sysinfo info;

    if (sysinfo(&info) == -1) {
        perror("sysinfo");
        return;
    }

    printf("=== System Information ===\n");
    printf("Uptime: %ld seconds\n", info.uptime);
    printf("Total RAM: %lu MB\n", info.totalram / 1024 / 1024);
    printf("Free RAM: %lu MB\n", info.freeram / 1024 / 1024);
    printf("Shared RAM: %lu MB\n", info.sharedram / 1024 / 1024);
    printf("Buffer RAM: %lu MB\n", info.bufferram / 1024 / 1024);
    printf("Total Swap: %lu MB\n", info.totalswap / 1024 / 1024);
    printf("Free Swap: %lu MB\n", info.freeswap / 1024 / 1024);
    printf("Number of processes: %d\n", info.procs);
}

void print_cpu_usage() {
    static clock_t last_cpu = 0;
    static clock_t last_sys = 0;
    static clock_t last_user = 0;

    struct tms time_sample;
    clock_t current_cpu = times(&time_sample);

    if (last_cpu != 0) {
        clock_t cpu_diff = current_cpu - last_cpu;
        clock_t sys_diff = time_sample.tms_stime - last_sys;
        clock_t user_diff = time_sample.tms_utime - last_user;

        double sys_percent = (double)sys_diff / cpu_diff * 100.0;
        double user_percent = (double)user_diff / cpu_diff * 100.0;

        printf("CPU Usage - System: %.2f%%, User: %.2f%%\n",
               sys_percent, user_percent);
    }

    last_cpu = current_cpu;
    last_sys = time_sample.tms_stime;
    last_user = time_sample.tms_utime;
}

int main() {
    print_system_info();

    printf("\n=== CPU Usage Monitoring ===\n");
    printf("Monitoring CPU usage for 5 seconds...\n");

    for (int i = 0; i < 5; i++) {
        print_cpu_usage();
        sleep(1);
    }

    return 0;
}
```

### **2. Process Resource Usage**

```c
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void print_resource_usage() {
    struct rusage usage;

    if (getrusage(RUSAGE_SELF, &usage) == -1) {
        perror("getrusage");
        return;
    }

    printf("=== Resource Usage ===\n");
    printf("User CPU time: %ld.%06ld seconds\n",
           usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System CPU time: %ld.%06ld seconds\n",
           usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    printf("Maximum resident set size: %ld KB\n", usage.ru_maxrss);
    printf("Page faults: %ld\n", usage.ru_majflt);
    printf("Page reclaims: %ld\n", usage.ru_minflt);
    printf("Context switches: %ld\n", usage.ru_nvcsw + usage.ru_nivcsw);
    printf("Signals received: %ld\n", usage.ru_nsignals);
}

void demonstrate_resource_limits() {
    struct rlimit limit;

    // Get current limits
    if (getrlimit(RLIMIT_CPU, &limit) == -1) {
        perror("getrlimit CPU");
        return;
    }

    printf("CPU time limit: %ld seconds\n", limit.rlim_cur);

    if (getrlimit(RLIMIT_DATA, &limit) == -1) {
        perror("getrlimit DATA");
        return;
    }

    printf("Data segment size limit: %ld bytes\n", limit.rlim_cur);

    // Set a CPU time limit (example)
    limit.rlim_cur = 10;  // 10 seconds
    limit.rlim_max = 20;  // 20 seconds

    if (setrlimit(RLIMIT_CPU, &limit) == -1) {
        perror("setrlimit CPU");
    } else {
        printf("CPU time limit set to 10 seconds\n");
    }
}

int main() {
    printf("Initial resource usage:\n");
    print_resource_usage();

    // Perform some work
    volatile long long sum = 0;
    for (long long i = 0; i < 100000000; i++) {
        sum += i;
    }

    printf("\nAfter computation:\n");
    print_resource_usage();

    demonstrate_resource_limits();

    return 0;
}
```

---

## 🔐 Security Considerations in System Programming

### **1. Secure System Calls**

```c
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Secure file operations
int secure_open(const char* filename, int flags, mode_t mode) {
    // Validate input
    if (filename == NULL || strlen(filename) == 0) {
        return -1;
    }

    // Use O_NOFOLLOW to prevent symlink attacks
    flags |= O_NOFOLLOW;

    // Use O_CLOEXEC to prevent file descriptor leaks
    flags |= O_CLOEXEC;

    int fd = open(filename, flags, mode);
    if (fd == -1) {
        perror("secure_open");
        return -1;
    }

    return fd;
}

// Secure memory operations
void* secure_malloc(size_t size) {
    if (size == 0 || size > 1024 * 1024 * 1024) {  // 1GB limit
        return NULL;
    }

    void* ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }

    // Initialize to zero for security
    memset(ptr, 0, size);
    return ptr;
}

// Secure string operations
size_t secure_strncpy(char* dest, const char* src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }

    size_t src_len = strlen(src);
    size_t copy_len = (src_len < dest_size - 1) ? src_len : dest_size - 1;

    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';

    return copy_len;
}

int main() {
    // Secure file operations
    int fd = secure_open("secure_file.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        const char* data = "Secure data";
        write(fd, data, strlen(data));
        close(fd);
        printf("Secure file operation completed\n");
    }

    // Secure memory allocation
    char* buffer = (char*)secure_malloc(1024);
    if (buffer != NULL) {
        secure_strncpy(buffer, "Secure string", 1024);
        printf("Secure buffer: %s\n", buffer);
        free(buffer);
    }

    return 0;
}
```

---

## 🎯 Best Practices for System Programming

### **1. Error Handling**
```c
// Comprehensive error handling
#define CHECK_SYSCALL(call) \
    do { \
        if ((call) == -1) { \
            perror(#call); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

int main() {
    CHECK_SYSCALL(chdir("/tmp"));
    int fd = open("test.txt", O_RDONLY);
    CHECK_SYSCALL(fd);
    // Continue with operations...
}
```

### **2. Resource Management**
```c
// RAII-like resource management
typedef struct {
    int fd;
    char* buffer;
    size_t buffer_size;
} FileHandle;

FileHandle* create_file_handle(const char* filename) {
    FileHandle* handle = calloc(1, sizeof(FileHandle));
    if (handle == NULL) return NULL;

    handle->fd = open(filename, O_RDONLY);
    if (handle->fd == -1) {
        free(handle);
        return NULL;
    }

    handle->buffer_size = 4096;
    handle->buffer = malloc(handle->buffer_size);
    if (handle->buffer == NULL) {
        close(handle->fd);
        free(handle);
        return NULL;
    }

    return handle;
}

void destroy_file_handle(FileHandle* handle) {
    if (handle == NULL) return;

    if (handle->buffer) free(handle->buffer);
    if (handle->fd != -1) close(handle->fd);
    free(handle);
}
```

### **3. Performance Optimization**
```c
// Optimized I/O operations
#define BUFFER_SIZE 8192

ssize_t optimized_read(int fd, void* buffer, size_t count) {
    size_t total_read = 0;

    while (total_read < count) {
        size_t to_read = count - total_read;
        if (to_read > BUFFER_SIZE) to_read = BUFFER_SIZE;

        ssize_t bytes_read = read(fd, (char*)buffer + total_read, to_read);
        if (bytes_read == -1) {
            if (errno == EINTR) continue;  // Interrupted, retry
            return -1;
        }
        if (bytes_read == 0) break;  // EOF

        total_read += bytes_read;
    }

    return total_read;
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Process Management**
- Implement a process pool for parallel computation
- Create a daemon process with proper signal handling
- Build a simple job scheduler using fork() and exec()

### **Exercise 2: Memory Mapping**
- Implement a memory-mapped file database
- Create a shared memory message queue
- Build a memory-mapped circular buffer

### **Exercise 3: Signal Handling**
- Implement a signal-based timer system
- Create a signal handler for graceful shutdown
- Build a signal-based inter-process communication system

### **Exercise 4: Device I/O**
- Write a character device driver interface
- Implement GPIO control for embedded systems
- Create a serial port communication program

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the primary difference between `fork()` and `clone()`?
a) fork() creates a new process, clone() creates a thread
b) fork() is POSIX, clone() is Linux-specific
c) fork() shares memory, clone() doesn't
d) fork() is deprecated, clone() is modern

### **Question 2:**
Which system call is used for memory-mapped I/O?
a) mmap()
b) malloc()
c) read()
d) open()

### **Question 3:**
What does the `O_CLOEXEC` flag do?
a) Closes file on exec()
b) Enables caching
c) Sets exclusive access
d) Enables compression

### **Question 4:**
Which signal is sent when a child process terminates?
a) SIGCHLD
b) SIGTERM
c) SIGHUP
d) SIGKILL

### **Question 5:**
What is the purpose of `mprotect()`?
a) Change memory protection
b) Allocate memory
c) Free memory
d) Copy memory

---

## 🔗 Additional Resources

### **System Programming**
- [Linux System Programming](https://www.amazon.com/Linux-System-Programming-Talking-Directly/dp/1449339530)
- [Advanced Programming in the UNIX Environment](https://www.amazon.com/Advanced-Programming-UNIX-Environment-3rd/dp/0321637739)
- [The Linux Programming Interface](https://www.amazon.com/Linux-Programming-Interface-System-Handbook/dp/1593272200)

### **Further Reading**
- [Linux man pages](https://man7.org/linux/man-pages/)
- [POSIX specification](https://pubs.opengroup.org/onlinepubs/9699919799/)
- [Kernel documentation](https://www.kernel.org/doc/)

---

## 🎯 Next Steps

**Congratulations!** You've mastered:
- ✅ System calls and kernel interfaces
- ✅ Process and memory management
- ✅ Signal handling and asynchronous operations
- ✅ Device I/O and hardware interaction
- ✅ System performance monitoring
- ✅ Security considerations

**Next Lesson Preview:**
- Network programming with sockets
- Multi-threading and concurrency
- Database integration
- Web API development
- Containerization and deployment

---

**🚀 Ready to explore network programming?**

[⬅️ Back to Course Overview](../README.md) | [Next: Network Programming ➡️](02_Network_Programming.md)