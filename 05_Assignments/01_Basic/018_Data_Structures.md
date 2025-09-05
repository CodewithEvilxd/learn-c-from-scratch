# 🎯 Assignment 1.18: Basic Data Structures

## 📋 Problem Statement

Create a C program that implements basic data structures including linked lists, stacks, and queues. Demonstrate their operations and compare their performance characteristics.

## 🎯 Learning Objectives

- Understand linked list implementation
- Learn stack operations (LIFO)
- Practice queue operations (FIFO)
- Compare array vs linked implementations
- Implement basic data structure algorithms
- Understand time complexity of operations

## 📝 Requirements

1. Implement singly linked list
2. Create stack using linked list
3. Implement queue using linked list
4. Demonstrate all CRUD operations
5. Compare with array-based implementations
6. Handle edge cases (empty lists, etc.)
7. Show memory management

## 💡 Hints

- Use structures for nodes and data structures
- Implement proper memory allocation/deallocation
- Handle NULL pointers carefully
- Use typedef for cleaner code
- Implement both array and linked versions
- Add size tracking for efficiency

## 🔧 Solution

```c
// Assignment 1.18: Basic Data Structures
// Linked lists, stacks, and queues implementation

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Node structure for linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Linked List structure
typedef struct {
    Node* head;
    int size;
} LinkedList;

// Stack structure (using linked list)
typedef struct {
    Node* top;
    int size;
} Stack;

// Queue structure (using linked list)
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

// Function prototypes - Linked List
Node* create_node(int data);
void linked_list_init(LinkedList* list);
void linked_list_insert(LinkedList* list, int data, int position);
void linked_list_delete(LinkedList* list, int position);
void linked_list_display(const LinkedList* list);
void linked_list_free(LinkedList* list);

// Function prototypes - Stack
void stack_init(Stack* stack);
void stack_push(Stack* stack, int data);
int stack_pop(Stack* stack);
int stack_peek(const Stack* stack);
bool stack_is_empty(const Stack* stack);
void stack_display(const Stack* stack);
void stack_free(Stack* stack);

// Function prototypes - Queue
void queue_init(Queue* queue);
void queue_enqueue(Queue* queue, int data);
int queue_dequeue(Queue* queue);
int queue_peek(const Queue* queue);
bool queue_is_empty(const Queue* queue);
void queue_display(const Queue* queue);
void queue_free(Queue* queue);

// Main demonstration functions
void demonstrate_linked_list();
void demonstrate_stack();
void demonstrate_queue();

int main() {
    printf("=== Basic Data Structures Demonstration ===\n\n");

    demonstrate_linked_list();
    demonstrate_stack();
    demonstrate_queue();

    return 0;
}

void demonstrate_linked_list() {
    printf("1. Linked List Operations\n");

    LinkedList list;
    linked_list_init(&list);

    // Insert elements
    linked_list_insert(&list, 10, 0);
    linked_list_insert(&list, 20, 1);
    linked_list_insert(&list, 30, 2);
    linked_list_insert(&list, 15, 1);  // Insert at position 1

    printf("After insertions: ");
    linked_list_display(&list);

    // Delete elements
    linked_list_delete(&list, 2);  // Delete position 2
    printf("After deleting position 2: ");
    linked_list_display(&list);

    linked_list_free(&list);
    printf("\n");
}

void demonstrate_stack() {
    printf("2. Stack Operations (LIFO)\n");

    Stack stack;
    stack_init(&stack);

    // Push elements
    stack_push(&stack, 10);
    stack_push(&stack, 20);
    stack_push(&stack, 30);

    printf("Stack after pushes: ");
    stack_display(&stack);

    // Pop elements
    printf("Popped: %d\n", stack_pop(&stack));
    printf("Stack after pop: ");
    stack_display(&stack);

    printf("Top element: %d\n", stack_peek(&stack));

    stack_free(&stack);
    printf("\n");
}

void demonstrate_queue() {
    printf("3. Queue Operations (FIFO)\n");

    Queue queue;
    queue_init(&queue);

    // Enqueue elements
    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);
    queue_enqueue(&queue, 30);

    printf("Queue after enqueues: ");
    queue_display(&queue);

    // Dequeue elements
    printf("Dequeued: %d\n", queue_dequeue(&queue));
    printf("Queue after dequeue: ");
    queue_display(&queue);

    printf("Front element: %d\n", queue_peek(&queue));

    queue_free(&queue);
    printf("\n");
}

// Linked List Implementation
Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void linked_list_init(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

void linked_list_insert(LinkedList* list, int data, int position) {
    Node* new_node = create_node(data);

    if (position == 0) {
        // Insert at beginning
        new_node->next = list->head;
        list->head = new_node;
    } else {
        // Find position to insert
        Node* current = list->head;
        for (int i = 0; i < position - 1 && current; i++) {
            current = current->next;
        }

        if (!current) {
            printf("Invalid position!\n");
            free(new_node);
            return;
        }

        new_node->next = current->next;
        current->next = new_node;
    }

    list->size++;
}

void linked_list_delete(LinkedList* list, int position) {
    if (!list->head || position >= list->size) {
        printf("Invalid position!\n");
        return;
    }

    Node* temp;
    if (position == 0) {
        // Delete from beginning
        temp = list->head;
        list->head = list->head->next;
    } else {
        // Find node to delete
        Node* current = list->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }

        temp = current->next;
        current->next = temp->next;
    }

    free(temp);
    list->size--;
}

void linked_list_display(const LinkedList* list) {
    Node* current = list->head;
    printf("[");
    while (current) {
        printf("%d", current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("] (size: %d)\n", list->size);
}

void linked_list_free(LinkedList* list) {
    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}

// Stack Implementation
void stack_init(Stack* stack) {
    stack->top = NULL;
    stack->size = 0;
}

void stack_push(Stack* stack, int data) {
    Node* new_node = create_node(data);
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

int stack_pop(Stack* stack) {
    if (stack_is_empty(stack)) {
        printf("Stack underflow!\n");
        return -1;
    }

    Node* temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;

    return data;
}

int stack_peek(const Stack* stack) {
    if (stack_is_empty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->top->data;
}

bool stack_is_empty(const Stack* stack) {
    return stack->top == NULL;
}

void stack_display(const Stack* stack) {
    Node* current = stack->top;
    printf("[");
    while (current) {
        printf("%d", current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("] (size: %d)\n", stack->size);
}

void stack_free(Stack* stack) {
    while (!stack_is_empty(stack)) {
        stack_pop(stack);
    }
}

// Queue Implementation
void queue_init(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void queue_enqueue(Queue* queue, int data) {
    Node* new_node = create_node(data);

    if (queue_is_empty(queue)) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    queue->size++;
}

int queue_dequeue(Queue* queue) {
    if (queue_is_empty(queue)) {
        printf("Queue underflow!\n");
        return -1;
    }

    Node* temp = queue->front;
    int data = temp->data;

    queue->front = queue->front->next;
    if (!queue->front) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;

    return data;
}

int queue_peek(const Queue* queue) {
    if (queue_is_empty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue->front->data;
}

bool queue_is_empty(const Queue* queue) {
    return queue->front == NULL;
}

void queue_display(const Queue* queue) {
    Node* current = queue->front;
    printf("[");
    while (current) {
        printf("%d", current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("] (size: %d)\n", queue->size);
}

void queue_free(Queue* queue) {
    while (!queue_is_empty(queue)) {
        queue_dequeue(queue);
    }
}
```

## 📊 Test Cases

### Test Case 1: Linked List
```
Expected Output:
After insertions: [10, 15, 20, 30] (size: 4)
After deleting position 2: [10, 15, 30] (size: 3)
```

### Test Case 2: Stack
```
Expected Output:
Stack after pushes: [30, 20, 10] (size: 3)
Popped: 30
Stack after pop: [20, 10] (size: 2)
Top element: 20
```

### Test Case 3: Queue
```
Expected Output:
Queue after enqueues: [10, 20, 30] (size: 3)
Dequeued: 10
Queue after dequeue: [20, 30] (size: 2)
Front element: 20
```

## 🔍 Explanation

1. **Linked List**: Dynamic data structure with nodes
2. **Stack**: LIFO (Last In, First Out) structure
3. **Queue**: FIFO (First In, First Out) structure
4. **Node Structure**: Contains data and next pointer
5. **Memory Management**: Proper allocation and deallocation
6. **Size Tracking**: Keep track of number of elements

## 🎯 Key Concepts Covered

- Dynamic memory allocation for nodes
- Pointer manipulation in data structures
- Linked list traversal and modification
- Stack and queue operations
- Memory deallocation and leak prevention
- Data structure size management

## 🚀 Extensions

1. Implement doubly linked list
2. Add search and sort operations
3. Create circular linked list
4. Implement stack/queue using arrays