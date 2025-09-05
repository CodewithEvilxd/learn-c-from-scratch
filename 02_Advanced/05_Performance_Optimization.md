# ⚡ Advanced C: Performance Optimization & Profiling

## Mastering High-Performance C Programming Techniques

---

## 🎯 Learning Objectives

- Master performance profiling and benchmarking
- Understand memory optimization techniques
- Learn CPU cache optimization strategies
- Implement algorithmic optimizations
- Master compiler optimizations and intrinsics
- Build high-performance concurrent applications

---

## 📖 Performance Analysis Fundamentals

**Performance optimization** involves identifying bottlenecks and improving code efficiency. C provides low-level control for maximum performance.

### **Key Concepts:**
- Profiling and benchmarking
- Memory access patterns
- CPU cache optimization
- Algorithm complexity analysis
- Compiler optimizations
- SIMD and vectorization

---

## 📊 Profiling and Benchmarking

### **1. Basic Timing and Profiling**

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// High-resolution timing
typedef struct {
    struct timeval start;
    struct timeval end;
} Timer;

void timer_start(Timer* timer) {
    gettimeofday(&timer->start, NULL);
}

double timer_stop(Timer* timer) {
    gettimeofday(&timer->end, NULL);

    double start_time = timer->start.tv_sec + timer->start.tv_usec / 1000000.0;
    double end_time = timer->end.tv_sec + timer->end.tv_usec / 1000000.0;

    return end_time - start_time;
}

// Benchmarking function
typedef struct {
    const char* name;
    void (*function)(void);
    double time_taken;
} Benchmark;

void run_benchmark(Benchmark* bench) {
    Timer timer;
    timer_start(&timer);

    bench->function();

    bench->time_taken = timer_stop(&timer);
    printf("%s: %.6f seconds\n", bench->name, bench->time_taken);
}

// Example functions to benchmark
void slow_function() {
    volatile long long sum = 0;
    for (long long i = 0; i < 10000000; i++) {
        sum += i;
    }
}

void fast_function() {
    volatile long long sum = 0;
    for (long long i = 0; i < 10000000; i += 4) {
        sum += i;
        sum += i + 1;
        sum += i + 2;
        sum += i + 3;
    }
}

int main() {
    Benchmark benchmarks[] = {
        {"Slow function", slow_function},
        {"Fast function", fast_function}
    };

    for (int i = 0; i < 2; i++) {
        run_benchmark(&benchmarks[i]);
    }

    return 0;
}
```

### **2. CPU Performance Counters**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

// Read CPU cycle counter (x86/AMD64)
static inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

// Performance measurement with cycles
typedef struct {
    uint64_t start_cycles;
    uint64_t end_cycles;
} CycleTimer;

void cycle_timer_start(CycleTimer* timer) {
    timer->start_cycles = rdtsc();
}

uint64_t cycle_timer_stop(CycleTimer* timer) {
    timer->end_cycles = rdtsc();
    return timer->end_cycles - timer->start_cycles;
}

// Cache performance analysis
void analyze_cache_performance() {
    const int ARRAY_SIZE = 1024 * 1024;  // 1M elements
    int* array = malloc(ARRAY_SIZE * sizeof(int));

    if (!array) {
        perror("malloc");
        return;
    }

    // Initialize array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    CycleTimer timer;

    // Sequential access (good cache performance)
    cycle_timer_start(&timer);
    volatile int sum1 = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum1 += array[i];
    }
    uint64_t sequential_cycles = cycle_timer_stop(&timer);

    // Random access (poor cache performance)
    cycle_timer_start(&timer);
    volatile int sum2 = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int index = rand() % ARRAY_SIZE;
        sum2 += array[index];
    }
    uint64_t random_cycles = cycle_timer_stop(&timer);

    printf("Sequential access: %llu cycles\n", sequential_cycles);
    printf("Random access: %llu cycles\n", random_cycles);
    printf("Cache performance ratio: %.2f\n",
           (double)random_cycles / sequential_cycles);

    free(array);
}

int main() {
    printf("Cache Performance Analysis:\n");
    analyze_cache_performance();

    return 0;
}
```

### **3. Memory Bandwidth Testing**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE (1024 * 1024 * 256)  // 256MB
#define ITERATIONS 10

// Memory bandwidth test
double measure_memory_bandwidth(size_t size, int read_write) {
    char* buffer = malloc(size);
    if (!buffer) {
        perror("malloc");
        return 0.0;
    }

    // Initialize buffer
    memset(buffer, 0xAA, size);

    struct timespec start, end;

    if (read_write) {
        // Write test
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int iter = 0; iter < ITERATIONS; iter++) {
            for (size_t i = 0; i < size; i++) {
                buffer[i] = (char)i;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
    } else {
        // Read test
        volatile char temp;
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int iter = 0; iter < ITERATIONS; iter++) {
            for (size_t i = 0; i < size; i++) {
                temp = buffer[i];
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
    }

    double time_taken = (end.tv_sec - start.tv_sec) +
                       (end.tv_nsec - start.tv_nsec) / 1e9;

    free(buffer);

    // Calculate bandwidth in GB/s
    double total_bytes = (double)size * ITERATIONS;
    double bandwidth = total_bytes / time_taken / (1024 * 1024 * 1024);

    return bandwidth;
}

int main() {
    printf("Memory Bandwidth Test\n");
    printf("=====================\n\n");

    size_t test_sizes[] = {
        1024 * 1024,        // 1MB
        1024 * 1024 * 10,   // 10MB
        1024 * 1024 * 100,  // 100MB
        1024 * 1024 * 256   // 256MB
    };

    for (int i = 0; i < 4; i++) {
        size_t size = test_sizes[i];

        double read_bw = measure_memory_bandwidth(size, 0);
        double write_bw = measure_memory_bandwidth(size, 1);

        printf("Size: %zu MB\n", size / (1024 * 1024));
        printf("  Read bandwidth: %.2f GB/s\n", read_bw);
        printf("  Write bandwidth: %.2f GB/s\n", write_bw);
        printf("  Average bandwidth: %.2f GB/s\n", (read_bw + write_bw) / 2);
        printf("\n");
    }

    return 0;
}
```

---

## 🧠 Memory Optimization Techniques

### **1. Cache-Friendly Data Structures**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Cache line size (typical 64 bytes)
#define CACHE_LINE_SIZE 64

// Cache-aligned structure
typedef struct {
    uint64_t data;
    char padding[CACHE_LINE_SIZE - sizeof(uint64_t)];
} __attribute__((aligned(CACHE_LINE_SIZE))) CacheAlignedData;

// Array of structures (AoS) - cache unfriendly
typedef struct {
    float x, y, z;
} Vector3_AoS;

typedef struct {
    Vector3_AoS vectors[1000];
} AoS_Array;

// Structure of arrays (SoA) - cache friendly
typedef struct {
    float x[1000];
    float y[1000];
    float z[1000];
} SoA_Array;

// Process AoS (cache unfriendly)
void process_aos(AoS_Array* arr, int count) {
    for (int i = 0; i < count; i++) {
        arr->vectors[i].x += 1.0f;
        arr->vectors[i].y += 1.0f;
        arr->vectors[i].z += 1.0f;
    }
}

// Process SoA (cache friendly)
void process_soa(SoA_Array* arr, int count) {
    for (int i = 0; i < count; i++) {
        arr->x[i] += 1.0f;
        arr->y[i] += 1.0f;
        arr->z[i] += 1.0f;
    }
}

// Memory prefetching
void prefetch_data(const void* addr) {
    __builtin_prefetch(addr, 0, 3);  // Read prefetch, high locality
}

void process_with_prefetch(float* data, int count) {
    for (int i = 0; i < count; i += 8) {  // Process 8 elements at a time
        // Prefetch next cache line
        if (i + 16 < count) {
            prefetch_data(&data[i + 16]);
        }

        // Process current elements
        for (int j = 0; j < 8 && i + j < count; j++) {
            data[i + j] += 1.0f;
        }
    }
}
```

### **2. Memory Pool Allocator**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define POOL_SIZE 1024
#define BLOCK_SIZE 64

typedef struct MemoryBlock {
    struct MemoryBlock* next;
    uint8_t data[BLOCK_SIZE];
} MemoryBlock;

typedef struct {
    MemoryBlock* free_list;
    MemoryBlock pool[POOL_SIZE];
    size_t allocated_count;
} MemoryPool;

// Initialize memory pool
void pool_init(MemoryPool* pool) {
    pool->free_list = NULL;
    pool->allocated_count = 0;

    // Initialize free list
    for (int i = 0; i < POOL_SIZE; i++) {
        pool->pool[i].next = pool->free_list;
        pool->free_list = &pool->pool[i];
    }
}

// Allocate memory from pool
void* pool_alloc(MemoryPool* pool) {
    if (pool->free_list == NULL) {
        return NULL;  // Pool exhausted
    }

    MemoryBlock* block = pool->free_list;
    pool->free_list = block->next;
    pool->allocated_count++;

    return block->data;
}

// Free memory back to pool
void pool_free(MemoryPool* pool, void* ptr) {
    if (ptr == NULL) return;

    // Calculate block address from data pointer
    MemoryBlock* block = (MemoryBlock*)((uint8_t*)ptr - offsetof(MemoryBlock, data));

    // Add to free list
    block->next = pool->free_list;
    pool->free_list = block;
    pool->allocated_count--;
}

// Get pool statistics
void pool_stats(MemoryPool* pool) {
    printf("Pool Statistics:\n");
    printf("  Total blocks: %d\n", POOL_SIZE);
    printf("  Allocated: %zu\n", pool->allocated_count);
    printf("  Free: %zu\n", POOL_SIZE - pool->allocated_count);
    printf("  Memory usage: %.1f%%\n",
           (double)pool->allocated_count / POOL_SIZE * 100);
}

int main() {
    MemoryPool pool;
    pool_init(&pool);

    // Allocate some memory
    void* ptr1 = pool_alloc(&pool);
    void* ptr2 = pool_alloc(&pool);
    void* ptr3 = pool_alloc(&pool);

    if (ptr1 && ptr2 && ptr3) {
        strcpy((char*)ptr1, "Hello");
        strcpy((char*)ptr2, "World");
        strcpy((char*)ptr3, "Pool");

        printf("Allocated strings:\n");
        printf("  %s\n", (char*)ptr1);
        printf("  %s\n", (char*)ptr2);
        printf("  %s\n", (char*)ptr3);
    }

    pool_stats(&pool);

    // Free some memory
    pool_free(&pool, ptr2);

    printf("\nAfter freeing one block:\n");
    pool_stats(&pool);

    return 0;
}
```

---

## 🚀 CPU Optimization Techniques

### **1. Loop Unrolling and Vectorization**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Standard loop
void standard_loop(int* data, int count) {
    for (int i = 0; i < count; i++) {
        data[i] += 1;
    }
}

// Manual loop unrolling
void unrolled_loop(int* data, int count) {
    int i = 0;
    for (; i <= count - 4; i += 4) {
        data[i] += 1;
        data[i + 1] += 1;
        data[i + 2] += 1;
        data[i + 3] += 1;
    }

    // Handle remaining elements
    for (; i < count; i++) {
        data[i] += 1;
    }
}

// SIMD-like operations (GCC vector extensions)
typedef int v4si __attribute__ ((vector_size (16)));  // 4 integers

void vectorized_add(int* data, int count) {
    int i = 0;
    for (; i <= count - 4; i += 4) {
        v4si* vec_ptr = (v4si*)&data[i];
        v4si vec = *vec_ptr;
        v4si ones = {1, 1, 1, 1};
        *vec_ptr = vec + ones;
    }

    // Handle remaining
    for (; i < count; i++) {
        data[i] += 1;
    }
}

// Branchless programming
int branchless_max(int a, int b) {
    return a ^ ((a ^ b) & -(a < b));
}

int branchless_abs(int x) {
    int mask = x >> (sizeof(int) * 8 - 1);
    return (x + mask) ^ mask;
}

// Lookup table for expensive operations
#define LUT_SIZE 256
static int sin_lut[LUT_SIZE];

void init_sin_lut() {
    for (int i = 0; i < LUT_SIZE; i++) {
        double angle = (double)i / LUT_SIZE * 2 * M_PI;
        sin_lut[i] = (int)(sin(angle) * 1000);  // Scale for integer
    }
}

int fast_sin(int angle) {
    int index = (angle % 360) * LUT_SIZE / 360;
    return sin_lut[index];
}
```

### **2. Instruction-Level Parallelism**

```c
#include <stdio.h>
#include <stdlib.h>

// Instruction scheduling for better ILP
void optimized_matrix_multiply(const float* A, const float* B, float* C,
                              int M, int N, int K) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0.0f;

            // Unroll inner loop for better ILP
            int k = 0;
            for (; k <= K - 4; k += 4) {
                sum += A[i * K + k] * B[k * N + j];
                sum += A[i * K + k + 1] * B[(k + 1) * N + j];
                sum += A[i * K + k + 2] * B[(k + 2) * N + j];
                sum += A[i * K + k + 3] * B[(k + 3) * N + j];
            }

            // Handle remaining elements
            for (; k < K; k++) {
                sum += A[i * K + k] * B[k * N + j];
            }

            C[i * N + j] = sum;
        }
    }
}

// Software pipelining
void pipelined_copy(const int* src, int* dst, int count) {
    if (count < 4) {
        for (int i = 0; i < count; i++) {
            dst[i] = src[i];
        }
        return;
    }

    // Software pipelining: load, process, store
    int i = 0;
    int temp0 = src[i];
    int temp1 = src[i + 1];
    int temp2 = src[i + 2];

    for (; i < count - 3; i += 3) {
        int next_temp = src[i + 3];

        dst[i] = temp0;
        temp0 = temp1;

        dst[i + 1] = temp1;
        temp1 = temp2;

        dst[i + 2] = temp2;
        temp2 = next_temp;
    }

    // Handle remaining
    dst[i] = temp0;
    if (i + 1 < count) dst[i + 1] = temp1;
    if (i + 2 < count) dst[i + 2] = temp2;
}
```

---

## ⚡ Compiler Optimizations

### **1. GCC Optimization Flags**

```c
// Compile with different optimization levels
// gcc -O0 source.c -o program     // No optimization
// gcc -O1 source.c -o program     // Basic optimizations
// gcc -O2 source.c -o program     // Advanced optimizations
// gcc -O3 source.c -o program     // Aggressive optimizations
// gcc -Os source.c -o program     // Optimize for size
// gcc -Ofast source.c -o program  // Fast but non-standard

// Profile-guided optimization
// Step 1: Compile with profiling
// gcc -O2 -fprofile-generate source.c -o program
// ./program  // Run to generate profile data
// Step 2: Compile with profile data
// gcc -O2 -fprofile-use source.c -o program

// Link-time optimization
// gcc -flto -O2 source.c -o program

#include <stdio.h>
#include <stdlib.h>

// Function with optimization hints
__attribute__((hot))  // Tell compiler this function is frequently called
void hot_function(int* data, int count) {
    for (int i = 0; i < count; i++) {
        data[i] *= 2;
    }
}

__attribute__((cold))  // Tell compiler this function is rarely called
void cold_function() {
    printf("This function is rarely called\n");
}

// Pure function (no side effects)
__attribute__((pure))
int pure_function(int x) {
    return x * x + 2 * x + 1;
}

// Const function (result depends only on arguments)
__attribute__((const))
int const_function(int x) {
    return x * 42;
}

// Inline hints
__attribute__((always_inline))
static inline int always_inline_func(int x) {
    return x + 1;
}

__attribute__((noinline))
int noinline_func(int x) {
    return x * 2;
}

// Restrict pointers for better optimization
void process_data(const int* restrict input, int* restrict output, int count) {
    for (int i = 0; i < count; i++) {
        output[i] = input[i] * 2;
    }
}

int main() {
    const int SIZE = 1000000;
    int* data = malloc(SIZE * sizeof(int));

    if (!data) {
        perror("malloc");
        return 1;
    }

    // Initialize data
    for (int i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Hot function will be optimized
    hot_function(data, SIZE);

    // Pure function result can be cached
    int result1 = pure_function(5);
    int result2 = pure_function(5);  // Compiler may optimize this

    // Const function can be evaluated at compile time
    int const_result = const_function(10);

    printf("Pure function results: %d, %d\n", result1, result2);
    printf("Const function result: %d\n", const_result);

    free(data);
    return 0;
}
```

### **2. SIMD Intrinsics**

```c
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>  // AVX intrinsics
#include <xmmintrin.h>  // SSE intrinsics

// SSE vector addition
void sse_add(float* a, float* b, float* result, int count) {
    int i = 0;

    // Process 4 floats at a time
    for (; i <= count - 4; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        __m128 vr = _mm_add_ps(va, vb);
        _mm_storeu_ps(&result[i], vr);
    }

    // Handle remaining elements
    for (; i < count; i++) {
        result[i] = a[i] + b[i];
    }
}

// AVX vector addition
void avx_add(float* a, float* b, float* result, int count) {
    int i = 0;

    // Process 8 floats at a time
    for (; i <= count - 8; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vr = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&result[i], vr);
    }

    // Handle remaining elements with SSE
    for (; i <= count - 4; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        __m128 vr = _mm_add_ps(va, vb);
        _mm_storeu_ps(&result[i], vr);
    }

    // Handle remaining elements
    for (; i < count; i++) {
        result[i] = a[i] + b[i];
    }
}

// Matrix multiplication with SIMD
void simd_matrix_multiply(const float* A, const float* B, float* C,
                         int M, int N, int K) {
    // Initialize result matrix to zero
    memset(C, 0, M * N * sizeof(float));

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            __m256 sum = _mm256_setzero_ps();

            int k = 0;
            for (; k <= K - 8; k += 8) {
                __m256 a = _mm256_loadu_ps(&A[i * K + k]);
                __m256 b = _mm256_set1_ps(B[k * N + j]);
                sum = _mm256_add_ps(sum, _mm256_mul_ps(a, b));
            }

            // Horizontal sum
            float temp[8];
            _mm256_storeu_ps(temp, sum);
            float result = temp[0] + temp[1] + temp[2] + temp[3] +
                          temp[4] + temp[5] + temp[6] + temp[7];

            // Handle remaining elements
            for (; k < K; k++) {
                result += A[i * K + k] * B[k * N + j];
            }

            C[i * N + j] = result;
        }
    }
}

int main() {
    const int SIZE = 1024;
    float* a = aligned_alloc(32, SIZE * sizeof(float));
    float* b = aligned_alloc(32, SIZE * sizeof(float));
    float* result = aligned_alloc(32, SIZE * sizeof(float));

    if (!a || !b || !result) {
        perror("aligned_alloc");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        a[i] = (float)i;
        b[i] = (float)(i * 2);
    }

    // Test SIMD addition
    avx_add(a, b, result, SIZE);

    printf("SIMD addition result (first 8 elements):\n");
    for (int i = 0; i < 8; i++) {
        printf("%.1f ", result[i]);
    }
    printf("\n");

    free(a);
    free(b);
    free(result);

    return 0;
}
```

---

## 🎯 Best Practices for Performance Optimization

### **1. Profiling First**
```c
// Always profile before optimizing
#define PROFILE_FUNCTION(func) \
    do { \
        Timer __timer; \
        timer_start(&__timer); \
        func; \
        double __time = timer_stop(&__timer); \
        printf("%s took %.6f seconds\n", #func, __time); \
    } while (0)

// Usage
PROFILE_FUNCTION(matrix_multiply(A, B, C, size));
```

### **2. Algorithm Complexity**
```c
// Choose algorithms based on complexity
// O(1) - Constant time
int array_access(int* arr, int index) {
    return arr[index];
}

// O(log n) - Logarithmic time
int binary_search(int* arr, int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// O(n) - Linear time
int linear_search(int* arr, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
```

### **3. Memory Access Patterns**
```c
// Good: Sequential access
void good_access_pattern(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] += 1;
        }
    }
}

// Bad: Random access
void bad_access_pattern(int** matrix, int rows, int cols) {
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            matrix[i][j] += 1;  // Poor cache locality
        }
    }
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Profiling and Benchmarking**
- Create a comprehensive benchmarking suite for different algorithms
- Profile memory allocation patterns
- Analyze cache performance for different data structures

### **Exercise 2: Memory Optimization**
- Implement custom memory allocators
- Optimize data structures for cache efficiency
- Create memory pools for frequent allocations

### **Exercise 3: CPU Optimization**
- Implement SIMD operations for image processing
- Optimize matrix operations with blocking
- Create lookup tables for expensive computations

### **Exercise 4: Compiler Optimizations**
- Experiment with different GCC optimization flags
- Implement profile-guided optimization
- Use compiler intrinsics for performance

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the primary goal of performance optimization?
a) Reduce code size
b) Improve execution speed
c) Make code more readable
d) Add more features

### **Question 2:**
Which has better cache performance?
a) Sequential memory access
b) Random memory access
c) Both are the same
d) Depends on the CPU

### **Question 3:**
What does SIMD stand for?
a) Single Instruction, Multiple Data
b) Simple Instruction, Multiple Data
c) Single Instruction, Many Data
d) Simple Instruction, Many Data

### **Question 4:**
Which GCC flag enables the highest optimization level?
a) -O1
b) -O2
c) -O3
d) -Ofast

### **Question 5:**
What is loop unrolling?
a) Removing loops from code
b) Repeating loop body multiple times
c) Optimizing loop conditions
d) Converting loops to recursion

---

## 🔗 Additional Resources

### **Performance Optimization**
- [Computer Systems: A Programmer's Perspective](https://www.amazon.com/Computer-Systems-Programmers-Perspective-3rd/dp/013409266X)
- [What Every Programmer Should Know About Memory](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)
- [Agner Fog's Optimization Manuals](https://www.agner.org/optimize/)

### **Further Reading**
- [GCC Optimization Options](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)
- [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide/)
- [Performance Analysis Tools](https://perf.wiki.kernel.org/)

---

## 🎯 Next Steps

**Congratulations!** You've mastered:
- ✅ Performance profiling and benchmarking
- ✅ Memory optimization techniques
- ✅ CPU cache optimization
- ✅ Compiler optimizations and intrinsics
- ✅ SIMD and vectorization
- ✅ Algorithm complexity analysis

**Next Lesson Preview:**
- Advanced algorithms and data structures
- Competitive programming techniques
- System design patterns
- Code optimization challenges
- Performance tuning methodologies

---

**🚀 Ready to tackle advanced algorithms?**

[⬅️ Previous: Database Integration](04_Database_Integration.md) | [Next: Advanced Algorithms](06_Advanced_Algorithms.md)