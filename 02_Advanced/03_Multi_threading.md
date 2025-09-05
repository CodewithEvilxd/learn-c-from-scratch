# 🧵 Advanced C: Multi-threading & Concurrency

## Building Concurrent and Parallel Applications

---

## 🎯 Learning Objectives

- Master POSIX threads (pthreads) programming
- Understand synchronization primitives and thread safety
- Learn concurrent data structures and algorithms
- Implement producer-consumer patterns
- Master thread pools and work queues
- Handle race conditions and deadlocks

---

## 📖 Multi-threading Fundamentals

**Multi-threading** allows programs to execute multiple threads concurrently, improving performance and responsiveness. In C, we use POSIX threads (pthreads) for multi-threading.

### **Key Concepts:**
- Thread creation and management
- Synchronization (mutexes, condition variables)
- Thread safety and race conditions
- Deadlock prevention
- Thread pools and work queues
- Concurrent data structures

---

## 🧵 POSIX Threads (pthreads)

### **1. Basic Thread Creation**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// Thread function
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d: Hello from thread!\n", thread_id);

    // Simulate work
    sleep(1);

    printf("Thread %d: Work completed\n", thread_id);

    // Return thread ID
    int* result = malloc(sizeof(int));
    *result = thread_id * 10;
    return result;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    printf("Main thread: All threads created\n");

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        void* thread_result;
        pthread_join(threads[i], &thread_result);

        if (thread_result != NULL) {
            printf("Thread %d returned: %d\n", i, *(int*)thread_result);
            free(thread_result);
        }
    }

    printf("Main thread: All threads completed\n");
    return 0;
}
```

### **2. Thread Attributes and Scheduling**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

void* high_priority_thread(void* arg) {
    printf("High priority thread running\n");

    // Set real-time scheduling
    struct sched_param param;
    param.sched_priority = 50;

    if (pthread_setschedparam(pthread_self(), SCHED_RR, &param) != 0) {
        perror("pthread_setschedparam");
    }

    for (int i = 0; i < 5; i++) {
        printf("High priority: %d\n", i);
        usleep(100000);  // 100ms
    }

    return NULL;
}

void* low_priority_thread(void* arg) {
    printf("Low priority thread running\n");

    for (int i = 0; i < 5; i++) {
        printf("Low priority: %d\n", i);
        usleep(100000);  // 100ms
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_attr_t attr;

    // Initialize thread attributes
    pthread_attr_init(&attr);

    // Set detached state
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Set stack size
    pthread_attr_setstacksize(&attr, 1024 * 1024);  // 1MB

    // Create high priority thread
    pthread_create(&thread1, &attr, high_priority_thread, NULL);

    // Create low priority thread
    pthread_create(&thread2, &attr, low_priority_thread, NULL);

    // Clean up attributes
    pthread_attr_destroy(&attr);

    // Since threads are detached, we don't need to join them
    sleep(2);  // Wait for threads to complete

    printf("Main thread exiting\n");
    return 0;
}
```

---

## 🔒 Synchronization Primitives

### **1. Mutexes (Mutual Exclusion)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 100000

int shared_counter = 0;
pthread_mutex_t counter_mutex;

// Thread function
void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        // Lock mutex before accessing shared resource
        pthread_mutex_lock(&counter_mutex);

        shared_counter++;

        // Unlock mutex after operation
        pthread_mutex_unlock(&counter_mutex);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize mutex
    if (pthread_mutex_init(&counter_mutex, NULL) != 0) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d (expected: %d)\n",
           shared_counter, NUM_THREADS * NUM_INCREMENTS);

    // Destroy mutex
    pthread_mutex_destroy(&counter_mutex);

    return 0;
}
```

### **2. Read-Write Locks**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define NUM_OPERATIONS 10

int shared_data = 0;
pthread_rwlock_t rwlock;

// Reader thread
void* reader_function(void* arg) {
    int reader_id = *(int*)arg;

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Acquire read lock
        pthread_rwlock_rdlock(&rwlock);

        printf("Reader %d: Read value %d\n", reader_id, shared_data);

        // Simulate reading time
        usleep(rand() % 100000);

        // Release read lock
        pthread_rwlock_unlock(&rwlock);

        usleep(rand() % 200000);  // Wait before next read
    }

    return NULL;
}

// Writer thread
void* writer_function(void* arg) {
    int writer_id = *(int*)arg;

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Acquire write lock
        pthread_rwlock_wrlock(&rwlock);

        shared_data++;
        printf("Writer %d: Wrote value %d\n", writer_id, shared_data);

        // Simulate writing time
        usleep(rand() % 150000);

        // Release write lock
        pthread_rwlock_unlock(&rwlock);

        usleep(rand() % 300000);  // Wait before next write
    }

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize read-write lock
    if (pthread_rwlock_init(&rwlock, NULL) != 0) {
        perror("pthread_rwlock_init");
        exit(EXIT_FAILURE);
    }

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        if (pthread_create(&readers[i], NULL, reader_function, &reader_ids[i]) != 0) {
            perror("pthread_create reader");
            exit(EXIT_FAILURE);
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        if (pthread_create(&writers[i], NULL, writer_function, &writer_ids[i]) != 0) {
            perror("pthread_create writer");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    printf("Final shared data value: %d\n", shared_data);

    // Destroy read-write lock
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
```

### **3. Condition Variables**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0, out = 0;

pthread_mutex_t buffer_mutex;
pthread_cond_t buffer_not_full;
pthread_cond_t buffer_not_empty;

// Producer thread
void* producer(void* arg) {
    int producer_id = *(int*)arg;

    for (int i = 0; i < 20; i++) {
        int item = producer_id * 100 + i;

        pthread_mutex_lock(&buffer_mutex);

        // Wait if buffer is full
        while (count == BUFFER_SIZE) {
            printf("Producer %d: Buffer full, waiting...\n", producer_id);
            pthread_cond_wait(&buffer_not_full, &buffer_mutex);
        }

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Producer %d: Produced %d (count: %d)\n", producer_id, item, count);

        // Signal consumer
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&buffer_mutex);

        usleep(rand() % 100000);  // Random delay
    }

    return NULL;
}

// Consumer thread
void* consumer(void* arg) {
    int consumer_id = *(int*)arg;

    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&buffer_mutex);

        // Wait if buffer is empty
        while (count == 0) {
            printf("Consumer %d: Buffer empty, waiting...\n", consumer_id);
            pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
        }

        // Remove item from buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumer %d: Consumed %d (count: %d)\n", consumer_id, item, count);

        // Signal producer
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&buffer_mutex);

        usleep(rand() % 150000);  // Random delay
    }

    return NULL;
}

int main() {
    pthread_t producers[2], consumers[2];
    int producer_ids[2] = {1, 2};
    int consumer_ids[2] = {1, 2};

    // Initialize synchronization primitives
    pthread_mutex_init(&buffer_mutex, NULL);
    pthread_cond_init(&buffer_not_full, NULL);
    pthread_cond_init(&buffer_not_empty, NULL);

    // Create producer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&buffer_not_full);
    pthread_cond_destroy(&buffer_not_empty);

    return 0;
}
```

---

## 🏗️ Thread Pools and Work Queues

### **1. Simple Thread Pool**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 4
#define WORK_QUEUE_SIZE 256

typedef struct {
    void (*function)(void* arg);
    void* arg;
} WorkItem;

typedef struct {
    pthread_t threads[THREAD_POOL_SIZE];
    WorkItem work_queue[WORK_QUEUE_SIZE];
    int work_count;
    int work_front;
    int work_rear;
    pthread_mutex_t queue_mutex;
    pthread_cond_t queue_not_empty;
    pthread_cond_t queue_not_full;
    int shutdown;
} ThreadPool;

// Function to execute work
void execute_work(WorkItem* work) {
    if (work->function) {
        work->function(work->arg);
    }
}

// Worker thread function
void* worker_thread(void* arg) {
    ThreadPool* pool = (ThreadPool*)arg;

    while (1) {
        pthread_mutex_lock(&pool->queue_mutex);

        // Wait for work or shutdown signal
        while (pool->work_count == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->queue_not_empty, &pool->queue_mutex);
        }

        if (pool->shutdown && pool->work_count == 0) {
            pthread_mutex_unlock(&pool->queue_mutex);
            break;
        }

        // Get work from queue
        WorkItem work = pool->work_queue[pool->work_front];
        pool->work_front = (pool->work_front + 1) % WORK_QUEUE_SIZE;
        pool->work_count--;

        // Signal that queue is not full
        pthread_cond_signal(&pool->queue_not_full);
        pthread_mutex_unlock(&pool->queue_mutex);

        // Execute work
        execute_work(&work);
    }

    return NULL;
}

// Initialize thread pool
ThreadPool* create_thread_pool() {
    ThreadPool* pool = calloc(1, sizeof(ThreadPool));
    if (!pool) return NULL;

    pool->work_count = 0;
    pool->work_front = 0;
    pool->work_rear = 0;
    pool->shutdown = 0;

    pthread_mutex_init(&pool->queue_mutex, NULL);
    pthread_cond_init(&pool->queue_not_empty, NULL);
    pthread_cond_init(&pool->queue_not_full, NULL);

    // Create worker threads
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&pool->threads[i], NULL, worker_thread, pool);
    }

    return pool;
}

// Add work to thread pool
int add_work(ThreadPool* pool, void (*function)(void*), void* arg) {
    pthread_mutex_lock(&pool->queue_mutex);

    // Wait if queue is full
    while (pool->work_count == WORK_QUEUE_SIZE && !pool->shutdown) {
        pthread_cond_wait(&pool->queue_not_full, &pool->queue_mutex);
    }

    if (pool->shutdown) {
        pthread_mutex_unlock(&pool->queue_mutex);
        return -1;
    }

    // Add work to queue
    pool->work_queue[pool->work_rear].function = function;
    pool->work_queue[pool->work_rear].arg = arg;
    pool->work_rear = (pool->work_rear + 1) % WORK_QUEUE_SIZE;
    pool->work_count++;

    // Signal worker threads
    pthread_cond_signal(&pool->queue_not_empty);
    pthread_mutex_unlock(&pool->queue_mutex);

    return 0;
}

// Shutdown thread pool
void destroy_thread_pool(ThreadPool* pool) {
    pthread_mutex_lock(&pool->queue_mutex);
    pool->shutdown = 1;
    pthread_cond_broadcast(&pool->queue_not_empty);
    pthread_mutex_unlock(&pool->queue_mutex);

    // Wait for all threads to finish
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_join(pool->threads[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&pool->queue_mutex);
    pthread_cond_destroy(&pool->queue_not_empty);
    pthread_cond_destroy(&pool->queue_not_full);
    free(pool);
}

// Example work function
void example_work(void* arg) {
    int work_id = *(int*)arg;
    printf("Processing work item %d\n", work_id);
    sleep(1);  // Simulate work
    printf("Completed work item %d\n", work_id);
}

int main() {
    ThreadPool* pool = create_thread_pool();
    if (!pool) {
        perror("create_thread_pool");
        exit(EXIT_FAILURE);
    }

    // Add work to pool
    for (int i = 0; i < 10; i++) {
        int* work_id = malloc(sizeof(int));
        *work_id = i;
        add_work(pool, example_work, work_id);
    }

    // Wait for all work to complete
    sleep(5);

    // Shutdown pool
    destroy_thread_pool(pool);

    printf("Thread pool shutdown complete\n");
    return 0;
}
```

---

## 🔄 Concurrent Data Structures

### **1. Thread-Safe Queue**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    int max_size;
} ConcurrentQueue;

// Initialize queue
ConcurrentQueue* queue_create(int max_size) {
    ConcurrentQueue* queue = calloc(1, sizeof(ConcurrentQueue));
    if (!queue) return NULL;

    queue->max_size = max_size;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    pthread_cond_init(&queue->not_full, NULL);

    return queue;
}

// Enqueue item
int queue_enqueue(ConcurrentQueue* queue, void* data) {
    pthread_mutex_lock(&queue->mutex);

    // Wait if queue is full
    while (queue->size == queue->max_size) {
        pthread_cond_wait(&queue->not_full, &queue->mutex);
    }

    // Create new node
    Node* node = malloc(sizeof(Node));
    if (!node) {
        pthread_mutex_unlock(&queue->mutex);
        return -1;
    }

    node->data = data;
    node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }

    queue->size++;

    // Signal waiting threads
    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->mutex);

    return 0;
}

// Dequeue item
void* queue_dequeue(ConcurrentQueue* queue) {
    pthread_mutex_lock(&queue->mutex);

    // Wait if queue is empty
    while (queue->size == 0) {
        pthread_cond_wait(&queue->not_empty, &queue->mutex);
    }

    // Remove front node
    Node* temp = queue->front;
    void* data = temp->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;

    // Signal waiting threads
    pthread_cond_signal(&queue->not_full);
    pthread_mutex_unlock(&queue->mutex);

    return data;
}

// Get queue size
int queue_size(ConcurrentQueue* queue) {
    pthread_mutex_lock(&queue->mutex);
    int size = queue->size;
    pthread_mutex_unlock(&queue->mutex);
    return size;
}

// Destroy queue
void queue_destroy(ConcurrentQueue* queue) {
    pthread_mutex_lock(&queue->mutex);

    Node* current = queue->front;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    pthread_mutex_unlock(&queue->mutex);
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->not_empty);
    pthread_cond_destroy(&queue->not_full);
    free(queue);
}
```

### **2. Thread-Safe Hash Map**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define HASH_TABLE_SIZE 256

typedef struct HashEntry {
    char* key;
    void* value;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    HashEntry* table[HASH_TABLE_SIZE];
    pthread_mutex_t mutex;
} ConcurrentHashMap;

// Hash function
unsigned int hash_function(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % HASH_TABLE_SIZE;
}

// Create hash map
ConcurrentHashMap* hashmap_create() {
    ConcurrentHashMap* map = calloc(1, sizeof(ConcurrentHashMap));
    if (!map) return NULL;

    pthread_mutex_init(&map->mutex, NULL);
    return map;
}

// Put key-value pair
void hashmap_put(ConcurrentHashMap* map, const char* key, void* value) {
    unsigned int index = hash_function(key);

    pthread_mutex_lock(&map->mutex);

    // Check if key already exists
    HashEntry* current = map->table[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            pthread_mutex_unlock(&map->mutex);
            return;
        }
        current = current->next;
    }

    // Create new entry
    HashEntry* entry = malloc(sizeof(HashEntry));
    if (!entry) {
        pthread_mutex_unlock(&map->mutex);
        return;
    }

    entry->key = strdup(key);
    entry->value = value;
    entry->next = map->table[index];
    map->table[index] = entry;

    pthread_mutex_unlock(&map->mutex);
}

// Get value by key
void* hashmap_get(ConcurrentHashMap* map, const char* key) {
    unsigned int index = hash_function(key);

    pthread_mutex_lock(&map->mutex);

    HashEntry* current = map->table[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            void* value = current->value;
            pthread_mutex_unlock(&map->mutex);
            return value;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&map->mutex);
    return NULL;
}

// Remove key-value pair
void hashmap_remove(ConcurrentHashMap* map, const char* key) {
    unsigned int index = hash_function(key);

    pthread_mutex_lock(&map->mutex);

    HashEntry* current = map->table[index];
    HashEntry* prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->table[index] = current->next;
            }

            free(current->key);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    pthread_mutex_unlock(&map->mutex);
}

// Destroy hash map
void hashmap_destroy(ConcurrentHashMap* map) {
    pthread_mutex_lock(&map->mutex);

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashEntry* current = map->table[i];
        while (current) {
            HashEntry* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }

    pthread_mutex_unlock(&map->mutex);
    pthread_mutex_destroy(&map->mutex);
    free(map);
}
```

---

## ⚠️ Race Conditions and Deadlocks

### **1. Race Condition Example**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_variable = 0;

// Thread function with race condition
void* increment_function(void* arg) {
    for (int i = 0; i < 100000; i++) {
        // Race condition: read-modify-write is not atomic
        int temp = shared_variable;
        temp = temp + 1;
        shared_variable = temp;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads that increment the same variable
    pthread_create(&thread1, NULL, increment_function, NULL);
    pthread_create(&thread2, NULL, increment_function, NULL);

    // Wait for threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value: %d (expected: 200000)\n", shared_variable);
    printf("Race condition caused loss of %d updates\n", 200000 - shared_variable);

    return 0;
}
```

### **2. Deadlock Prevention**

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

// Thread 1: Locks mutex1 then mutex2
void* thread1_function(void* arg) {
    printf("Thread 1: Trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: Locked mutex1\n");

    sleep(1);  // Allow thread 2 to lock mutex2

    printf("Thread 1: Trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1: Locked mutex2\n");

    // Critical section
    printf("Thread 1: In critical section\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

// Thread 2: Locks mutex2 then mutex1
void* thread2_function(void* arg) {
    printf("Thread 2: Trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: Locked mutex2\n");

    sleep(1);  // Allow thread 1 to lock mutex1

    printf("Thread 2: Trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 2: Locked mutex1\n");

    // Critical section
    printf("Thread 2: In critical section\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

// Solution: Always acquire locks in the same order
void* thread1_safe(void* arg) {
    printf("Thread 1: Trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: Locked mutex1\n");

    printf("Thread 1: Trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1: Locked mutex2\n");

    printf("Thread 1: In critical section\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void* thread2_safe(void* arg) {
    printf("Thread 2: Trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);  // Same order as thread 1
    printf("Thread 2: Locked mutex1\n");

    printf("Thread 2: Trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: Locked mutex2\n");

    printf("Thread 2: In critical section\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    printf("=== Demonstrating Deadlock ===\n");
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\n=== Safe Version (Same Lock Order) ===\n");
    pthread_create(&thread1, NULL, thread1_safe, NULL);
    pthread_create(&thread2, NULL, thread2_safe, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
```

---

## 🎯 Best Practices for Multi-threading

### **1. Thread Safety**
```c
// Thread-safe singleton pattern
static pthread_mutex_t singleton_mutex = PTHREAD_MUTEX_INITIALIZER;
static MyObject* singleton_instance = NULL;

MyObject* get_singleton_instance() {
    if (singleton_instance == NULL) {
        pthread_mutex_lock(&singleton_mutex);
        if (singleton_instance == NULL) {  // Double-checked locking
            singleton_instance = create_my_object();
        }
        pthread_mutex_unlock(&singleton_mutex);
    }
    return singleton_instance;
}
```

### **2. Resource Management**
```c
// RAII-like resource management for threads
typedef struct {
    pthread_t thread;
    int active;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} ManagedThread;

ManagedThread* create_managed_thread(void* (*start_routine)(void*), void* arg) {
    ManagedThread* mt = calloc(1, sizeof(ManagedThread));
    if (!mt) return NULL;

    mt->active = 1;
    pthread_mutex_init(&mt->mutex, NULL);
    pthread_cond_init(&mt->cond, NULL);

    if (pthread_create(&mt->thread, NULL, start_routine, arg) != 0) {
        free(mt);
        return NULL;
    }

    return mt;
}

void destroy_managed_thread(ManagedThread* mt) {
    if (!mt) return;

    pthread_mutex_lock(&mt->mutex);
    mt->active = 0;
    pthread_cond_signal(&mt->cond);
    pthread_mutex_unlock(&mt->mutex);

    pthread_join(mt->thread, NULL);

    pthread_mutex_destroy(&mt->mutex);
    pthread_cond_destroy(&mt->cond);
    free(mt);
}
```

### **3. Performance Optimization**
```c
// Lock-free data structures using atomic operations
#include <stdatomic.h>

typedef struct {
    atomic_int counter;
    atomic_flag lock;
} LockFreeCounter;

void increment_counter(LockFreeCounter* counter) {
    // Atomic increment
    atomic_fetch_add(&counter->counter, 1);
}

int get_counter_value(LockFreeCounter* counter) {
    return atomic_load(&counter->counter);
}

// Spin lock implementation
void spin_lock(atomic_flag* lock) {
    while (atomic_flag_test_and_set(lock)) {
        // Spin until lock is acquired
    }
}

void spin_unlock(atomic_flag* lock) {
    atomic_flag_clear(lock);
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Basic Multi-threading**
- Create a parallel sum calculator using multiple threads
- Implement matrix multiplication with thread parallelism
- Build a concurrent file downloader

### **Exercise 2: Synchronization**
- Implement a thread-safe LRU cache
- Create a producer-consumer problem solution
- Build a readers-writers problem implementation

### **Exercise 3: Thread Pools**
- Design a web server with thread pool
- Implement work stealing in thread pools
- Create a thread pool with priority queues

### **Exercise 4: Concurrent Data Structures**
- Implement a lock-free queue
- Create a concurrent hash map with fine-grained locking
- Build a thread-safe priority queue

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is a race condition?
a) When threads compete for resources
b) When multiple threads access shared data without synchronization
c) When a thread runs too fast
d) When threads deadlock

### **Question 2:**
Which synchronization primitive allows multiple readers but only one writer?
a) Mutex
b) Semaphore
c) Read-write lock
d) Condition variable

### **Question 3:**
What is the purpose of `pthread_join()`?
a) Create a new thread
b) Wait for a thread to complete
c) Lock a mutex
d) Send a signal

### **Question 4:**
What is deadlock?
a) When a thread crashes
b) When threads wait for each other indefinitely
c) When a thread uses too much memory
d) When threads compete for CPU time

### **Question 5:**
Which is NOT a valid thread state?
a) Running
b) Ready
c) Blocked
d) Terminated
e) All are valid

---

## 🔗 Additional Resources

### **Multi-threading**
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [C Concurrency in Action](https://www.amazon.com/C-Concurrency-Action-Anthony-Williams/dp/1933988770)
- [Pthreads Tutorial](https://randu.org/tutorials/threads/)

### **Further Reading**
- [The Art of Multiprocessor Programming](https://www.amazon.com/Art-Multiprocessor-Programming-Revised-Reprint/dp/0123973376)
- [Concurrency in C](https://www.amazon.com/Concurrency-C%E2%84%A2-Practical-Programming/dp/1491906759)
- [Linux Kernel Development](https://www.amazon.com/Linux-Kernel-Development-Robert-Love/dp/0672329468)

---

## 🎯 Next Steps

**Congratulations!** You've mastered:
- ✅ POSIX threads programming
- ✅ Synchronization primitives
- ✅ Thread pools and work queues
- ✅ Concurrent data structures
- ✅ Race condition prevention
- ✅ Deadlock avoidance

**Next Lesson Preview:**
- Database integration with SQLite
- Web API development
- Containerization with Docker
- Cloud deployment
- Performance profiling and optimization

---

**🚀 Ready to integrate databases?**

[⬅️ Previous: Network Programming](02_Network_Programming.md) | [Next: Database Integration](04_Database_Integration.md)