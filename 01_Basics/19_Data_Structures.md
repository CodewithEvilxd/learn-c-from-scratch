# 🏗️ Lesson 19: Data Structures in C
## Building Efficient Data Organization

---

## 🎯 Learning Objectives

- Implement linked lists (singly, doubly, circular)
- Master stack and queue operations
- Understand tree structures and algorithms
- Learn hash table basics
- Apply data structures to real-world problems

---

## 📖 Data Structures Kya Hain?

**Data structures** data ko organize, store, aur efficiently access karne ke specialized formats hain. Ye applications ke specific requirements ke based data ko structure karne ke different ways provide karte hain.

### **Data Structures Ki Classification**
1. **Linear**: Arrays, Linked Lists, Stacks, Queues
2. **Non-linear**: Trees, Graphs, Hash Tables
3. **Static**: Fixed size (Arrays)
4. **Dynamic**: Variable size (Linked Lists, Trees)
5. **Abstract**: Interfaces without implementation details
6. **Concrete**: Specific implementation with details

### **Advanced Data Structure Concepts**
- **Time Complexity Analysis**: Big O, Big Ω, Big θ
- **Space Complexity**: Memory usage patterns
- **Cache Efficiency**: Memory access patterns
- **Concurrency**: Thread-safe data structures
- **Persistence**: Disk-based data structures

---

## 🔗 Linked Lists

### **1. Singly Linked List**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

// Create a new node
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Initialize linked list
LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// Insert at beginning
void insert_beginning(LinkedList* list, int data) {
    Node* new_node = create_node(data);
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

// Insert at end
void insert_end(LinkedList* list, int data) {
    Node* new_node = create_node(data);

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

// Delete node by value
void delete_node(LinkedList* list, int data) {
    if (list->head == NULL) return;

    // If head node contains the data
    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
        return;
    }

    // Search for the node
    Node* current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }

    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
        list->size--;
    }
}

// Display list
void display_list(LinkedList* list) {
    Node* current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    printf("Size: %d\n", list->size);
}

// Free list memory
void free_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList* list = create_list();

    insert_beginning(list, 10);
    insert_beginning(list, 20);
    insert_end(list, 30);
    insert_end(list, 40);

    display_list(list);

    delete_node(list, 20);
    display_list(list);

    free_list(list);
    return 0;
}
```

### **2. Doubly Linked List**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

// Create node
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// Initialize list
DoublyLinkedList* create_list() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Insert at end
void insert_end(DoublyLinkedList* list, int data) {
    Node* new_node = create_node(data);

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    list->size++;
}

// Delete node by value
void delete_node(DoublyLinkedList* list, int data) {
    if (list->head == NULL) return;

    Node* current = list->head;

    // Find the node
    while (current != NULL && current->data != data) {
        current = current->next;
    }

    if (current == NULL) return;  // Node not found

    // Update pointers
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;  // Deleting head
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;  // Deleting tail
    }

    free(current);
    list->size--;
}

// Display list forward
void display_forward(DoublyLinkedList* list) {
    Node* current = list->head;
    printf("Forward: ");
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Display list backward
void display_backward(DoublyLinkedList* list) {
    Node* current = list->tail;
    printf("Backward: ");
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

int main() {
    DoublyLinkedList* list = create_list();

    insert_end(list, 10);
    insert_end(list, 20);
    insert_end(list, 30);
    insert_end(list, 40);

    display_forward(list);
    display_backward(list);

    delete_node(list, 20);
    display_forward(list);

    // Free memory
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);

    return 0;
}
```

### **3. Circular Linked List**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} CircularList;

// Create node
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Initialize list
CircularList* create_list() {
    CircularList* list = (CircularList*)malloc(sizeof(CircularList));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// Insert at end
void insert_end(CircularList* list, int data) {
    Node* new_node = create_node(data);

    if (list->head == NULL) {
        list->head = new_node;
        new_node->next = new_node;  // Point to itself
    } else {
        Node* current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = new_node;
        new_node->next = list->head;
    }
    list->size++;
}

// Display list
void display_list(CircularList* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* current = list->head;
    printf("List: ");
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("(back to start)\n");
    printf("Size: %d\n", list->size);
}

// Delete node by value
void delete_node(CircularList* list, int data) {
    if (list->head == NULL) return;

    Node* current = list->head;
    Node* prev = NULL;

    // Find the node
    do {
        if (current->data == data) {
            break;
        }
        prev = current;
        current = current->next;
    } while (current != list->head);

    if (current == list->head && prev == NULL) {
        // Only one node
        free(current);
        list->head = NULL;
    } else if (current == list->head) {
        // Deleting head
        prev->next = current->next;
        list->head = current->next;
        free(current);
    } else {
        // Deleting middle or last node
        prev->next = current->next;
        free(current);
    }
    list->size--;
}

int main() {
    CircularList* list = create_list();

    insert_end(list, 10);
    insert_end(list, 20);
    insert_end(list, 30);
    insert_end(list, 40);

    display_list(list);

    delete_node(list, 20);
    display_list(list);

    // Free memory
    if (list->head != NULL) {
        Node* current = list->head;
        Node* next;
        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != list->head);
    }
    free(list);

    return 0;
}
```

### **4. Skip List (Advanced Linked List)**
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_LEVEL 16
#define P 0.5  // Probability for level generation

typedef struct Node {
    int data;
    struct Node** forward;  // Array of forward pointers
} Node;

typedef struct {
    Node* header;
    int level;
    int size;
} SkipList;

// Create node with given level
Node* create_node(int level, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    node->data = data;
    node->forward = (Node**)malloc(sizeof(Node*) * (level + 1));
    if (node->forward == NULL) {
        free(node);
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i <= level; i++) {
        node->forward[i] = NULL;
    }

    return node;
}

// Generate random level
int random_level() {
    int level = 0;
    while ((double)rand() / RAND_MAX < P && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// Initialize skip list
SkipList* create_skip_list() {
    SkipList* list = (SkipList*)malloc(sizeof(SkipList));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    list->level = 0;
    list->header = create_node(MAX_LEVEL, INT_MIN);
    list->size = 0;

    return list;
}

// Search for a value
Node* search(SkipList* list, int data) {
    Node* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];
    if (current != NULL && current->data == data) {
        return current;
    }

    return NULL;
}

// Insert a value
void insert(SkipList* list, int data) {
    Node* current = list->header;
    Node* update[MAX_LEVEL + 1];

    // Find position to insert
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    // If data already exists, don't insert
    if (current != NULL && current->data == data) {
        return;
    }

    // Generate random level
    int new_level = random_level();

    // Update list level if necessary
    if (new_level > list->level) {
        for (int i = list->level + 1; i <= new_level; i++) {
            update[i] = list->header;
        }
        list->level = new_level;
    }

    // Create new node
    Node* new_node = create_node(new_level, data);

    // Update forward pointers
    for (int i = 0; i <= new_level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }

    list->size++;
}

// Delete a value
void delete_node(SkipList* list, int data) {
    Node* current = list->header;
    Node* update[MAX_LEVEL + 1];

    // Find node to delete
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != NULL && current->data == data) {
        // Update forward pointers
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }

        // Reduce level if necessary
        while (list->level > 0 && list->header->forward[list->level] == NULL) {
            list->level--;
        }

        free(current->forward);
        free(current);
        list->size--;
    }
}

// Display skip list
void display_skip_list(SkipList* list) {
    printf("Skip List (Level %d, Size %d):\n", list->level, list->size);

    for (int i = 0; i <= list->level; i++) {
        Node* current = list->header->forward[i];
        printf("Level %d: ", i);
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->forward[i];
        }
        printf("NULL\n");
    }
}

// Free skip list
void free_skip_list(SkipList* list) {
    Node* current = list->header->forward[0];
    while (current != NULL) {
        Node* temp = current;
        current = current->forward[0];
        free(temp->forward);
        free(temp);
    }
    free(list->header->forward);
    free(list->header);
    free(list);
}

int main() {
    srand(time(NULL));

    SkipList* list = create_skip_list();

    insert(list, 10);
    insert(list, 20);
    insert(list, 30);
    insert(list, 40);
    insert(list, 50);

    display_skip_list(list);

    printf("Search for 30: %s\n", search(list, 30) != NULL ? "Found" : "Not found");
    printf("Search for 25: %s\n", search(list, 25) != NULL ? "Found" : "Not found");

    delete_node(list, 30);
    printf("After deleting 30:\n");
    display_skip_list(list);

    free_skip_list(list);
    return 0;
}
```

---

## 📚 Stacks and Queues

### **1. Stack Implementation**
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// Initialize stack
void init_stack(Stack* stack) {
    stack->top = -1;
}

// Check if stack is empty
bool is_empty(Stack* stack) {
    return stack->top == -1;
}

// Check if stack is full
bool is_full(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Push element
void push(Stack* stack, int value) {
    if (is_full(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// Pop element
int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// Peek top element
int peek(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->data[stack->top];
}

// Display stack
void display_stack(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int main() {
    Stack stack;
    init_stack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    display_stack(&stack);

    printf("Popped: %d\n", pop(&stack));
    printf("Top element: %d\n", peek(&stack));

    display_stack(&stack);

    return 0;
}
```

### **2. Queue Implementation**
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// Initialize queue
void init_queue(Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

// Check if queue is empty
bool is_empty(Queue* queue) {
    return queue->size == 0;
}

// Check if queue is full
bool is_full(Queue* queue) {
    return queue->size == MAX_SIZE;
}

// Enqueue element
void enqueue(Queue* queue, int value) {
    if (is_full(queue)) {
        printf("Queue overflow\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->data[queue->rear] = value;
    queue->size++;
}

// Dequeue element
int dequeue(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->size--;
    return value;
}

// Peek front element
int peek(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->data[queue->front];
}

// Display queue
void display_queue(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");
    int i = queue->front;
    for (int count = 0; count < queue->size; count++) {
        printf("%d ", queue->data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    Queue queue;
    init_queue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    display_queue(&queue);

    printf("Dequeued: %d\n", dequeue(&queue));
    printf("Front element: %d\n", peek(&queue));

    display_queue(&queue);

    return 0;
}
```

---

## 🌳 Trees

### **1. Binary Tree Implementation**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create new node
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insert node
Node* insert_node(Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }

    if (data < root->data) {
        root->left = insert_node(root->left, data);
    } else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }

    return root;
}

// Inorder traversal
void inorder_traversal(Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

// Preorder traversal
void preorder_traversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

// Postorder traversal
void postorder_traversal(Node* root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

// Search for a value
Node* search_node(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search_node(root->left, data);
    } else {
        return search_node(root->right, data);
    }
}

// Find minimum value node
Node* find_min(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Delete node
Node* delete_node(Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // Node with one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        Node* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }

    return root;
}

// Free tree memory
void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;

    // Insert nodes
    root = insert_node(root, 50);
    root = insert_node(root, 30);
    root = insert_node(root, 70);
    root = insert_node(root, 20);
    root = insert_node(root, 40);
    root = insert_node(root, 60);
    root = insert_node(root, 80);

    printf("Inorder traversal: ");
    inorder_traversal(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder_traversal(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder_traversal(root);
    printf("\n");

    // Search
    Node* found = search_node(root, 40);
    if (found != NULL) {
        printf("Found node with value: %d\n", found->data);
    }

    // Delete
    root = delete_node(root, 30);
    printf("After deleting 30, inorder: ");
    inorder_traversal(root);
    printf("\n");

    free_tree(root);
    return 0;
}
```

### **2. AVL Tree (Self-Balancing Binary Search Tree)**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Get height of node
int height(Node* node) {
    return node ? node->height : 0;
}

// Get balance factor
int get_balance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Create new node
Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate
Node* right_rotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// Left rotate
Node* left_rotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// Insert node with balancing
Node* insert_avl(Node* node, int data) {
    // Standard BST insertion
    if (node == NULL) {
        return create_node(data);
    }

    if (data < node->data) {
        node->left = insert_avl(node->left, data);
    } else if (data > node->data) {
        node->right = insert_avl(node->right, data);
    } else {
        return node; // Duplicate data not allowed
    }

    // Update height
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Get balance factor
    int balance = get_balance(node);

    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        return right_rotate(node);
    }

    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        return left_rotate(node);
    }

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

// Preorder traversal
void preorder_traversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

// Inorder traversal
void inorder_traversal(Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

int main() {
    Node* root = NULL;

    // Insert nodes
    root = insert_avl(root, 10);
    root = insert_avl(root, 20);
    root = insert_avl(root, 30);
    root = insert_avl(root, 40);
    root = insert_avl(root, 50);
    root = insert_avl(root, 25);

    printf("Preorder traversal: ");
    preorder_traversal(root);
    printf("\n");

    printf("Inorder traversal: ");
    inorder_traversal(root);
    printf("\n");

    printf("Tree height: %d\n", height(root));

    // Free memory
    // (Implementation left as exercise)

    return 0;
}
```

### **3. Heap (Priority Queue)**
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int data[MAX_HEAP_SIZE];
    int size;
} MaxHeap;

// Initialize heap
void init_heap(MaxHeap* heap) {
    heap->size = 0;
}

// Get parent index
int parent(int i) {
    return (i - 1) / 2;
}

// Get left child index
int left_child(int i) {
    return 2 * i + 1;
}

// Get right child index
int right_child(int i) {
    return 2 * i + 2;
}

// Swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up (for insertion)
void heapify_up(MaxHeap* heap, int index) {
    while (index > 0 && heap->data[parent(index)] < heap->data[index]) {
        swap(&heap->data[parent(index)], &heap->data[index]);
        index = parent(index);
    }
}

// Heapify down (for deletion)
void heapify_down(MaxHeap* heap, int index) {
    int largest = index;
    int left = left_child(index);
    int right = right_child(index);

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

// Insert element
void insert(MaxHeap* heap, int value) {
    if (heap->size >= MAX_HEAP_SIZE) {
        printf("Heap overflow\n");
        return;
    }

    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
}

// Extract maximum element
int extract_max(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap underflow\n");
        return -1;
    }

    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);

    return max;
}

// Get maximum element without removing
int get_max(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return -1;
    }
    return heap->data[0];
}

// Display heap
void display_heap(MaxHeap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main() {
    MaxHeap heap;
    init_heap(&heap);

    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 15);
    insert(&heap, 30);
    insert(&heap, 25);

    display_heap(&heap);

    printf("Maximum element: %d\n", get_max(&heap));

    printf("Extracted max: %d\n", extract_max(&heap));
    display_heap(&heap);

    printf("Extracted max: %d\n", extract_max(&heap));
    display_heap(&heap);

    return 0;
}
```

### **4. Trie (Prefix Tree)**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool is_end_of_word;
    int count;  // Number of words passing through this node
} TrieNode;

// Create new trie node
TrieNode* create_node() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    node->is_end_of_word = false;
    node->count = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

// Insert word into trie
void insert(TrieNode* root, const char* word) {
    TrieNode* current = root;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';

        if (current->children[index] == NULL) {
            current->children[index] = create_node();
        }

        current = current->children[index];
        current->count++;
    }

    current->is_end_of_word = true;
}

// Search for word in trie
bool search(TrieNode* root, const char* word) {
    TrieNode* current = root;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';

        if (current->children[index] == NULL) {
            return false;
        }

        current = current->children[index];
    }

    return current != NULL && current->is_end_of_word;
}

// Check if prefix exists
bool starts_with(TrieNode* root, const char* prefix) {
    TrieNode* current = root;
    int length = strlen(prefix);

    for (int i = 0; i < length; i++) {
        int index = prefix[i] - 'a';

        if (current->children[index] == NULL) {
            return false;
        }

        current = current->children[index];
    }

    return true;
}

// Get count of words with given prefix
int count_prefix(TrieNode* root, const char* prefix) {
    TrieNode* current = root;
    int length = strlen(prefix);

    for (int i = 0; i < length; i++) {
        int index = prefix[i] - 'a';

        if (current->children[index] == NULL) {
            return 0;
        }

        current = current->children[index];
    }

    return current->count;
}

// Delete word from trie
bool delete_word(TrieNode* root, const char* word) {
    TrieNode* current = root;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';

        if (current->children[index] == NULL) {
            return false;
        }

        current = current->children[index];
    }

    if (current->is_end_of_word) {
        current->is_end_of_word = false;
        return true;
    }

    return false;
}

// Free trie memory
void free_trie(TrieNode* node) {
    if (node == NULL) return;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            free_trie(node->children[i]);
        }
    }

    free(node);
}

int main() {
    TrieNode* root = create_node();

    insert(root, "hello");
    insert(root, "world");
    insert(root, "hello");
    insert(root, "hell");
    insert(root, "heaven");

    printf("Search 'hello': %s\n", search(root, "hello") ? "Found" : "Not found");
    printf("Search 'world': %s\n", search(root, "world") ? "Found" : "Not found");
    printf("Search 'hell': %s\n", search(root, "hell") ? "Found" : "Not found");
    printf("Search 'heaven': %s\n", search(root, "heaven") ? "Found" : "Not found");
    printf("Search 'helloo': %s\n", search(root, "helloo") ? "Found" : "Not found");

    printf("Starts with 'he': %s\n", starts_with(root, "he") ? "Yes" : "No");
    printf("Starts with 'hi': %s\n", starts_with(root, "hi") ? "Yes" : "No");

    printf("Words with prefix 'he': %d\n", count_prefix(root, "he"));
    printf("Words with prefix 'hel': %d\n", count_prefix(root, "hel"));

    delete_word(root, "hello");
    printf("After deleting 'hello', search 'hello': %s\n",
           search(root, "hello") ? "Found" : "Not found");

    free_trie(root);
    return 0;
}
```

---

## 🔍 Hash Tables (Basics)

### **1. Simple Hash Table Implementation**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Entry {
    char* key;
    int value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry* table[TABLE_SIZE];
} HashTable;

// Hash function
unsigned int hash(const char* key) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value * 31) + *key;
        key++;
    }
    return hash_value % TABLE_SIZE;
}

// Create hash table
HashTable* create_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        table->table[i] = NULL;
    }

    return table;
}

// Insert key-value pair
void insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash(key);

    // Check if key already exists
    Entry* current = table->table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    // Create new entry
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    if (new_entry == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = table->table[index];
    table->table[index] = new_entry;
}

// Get value by key
int get(HashTable* table, const char* key) {
    unsigned int index = hash(key);

    Entry* current = table->table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return -1;  // Key not found
}

// Delete key-value pair
void delete_key(HashTable* table, const char* key) {
    unsigned int index = hash(key);

    Entry* current = table->table[index];
    Entry* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                table->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Display hash table
void display_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        Entry* current = table->table[i];
        while (current != NULL) {
            printf("(%s, %d) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

// Free hash table
void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* current = table->table[i];
        while (current != NULL) {
            Entry* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table);
}

int main() {
    HashTable* table = create_table();

    insert(table, "apple", 10);
    insert(table, "banana", 20);
    insert(table, "orange", 30);

    printf("apple: %d\n", get(table, "apple"));
    printf("banana: %d\n", get(table, "banana"));
    printf("grape: %d\n", get(table, "grape"));  // Not found

    display_table(table);

    delete_key(table, "banana");
    printf("After deleting banana:\n");
    display_table(table);

    free_table(table);
    return 0;
}
```

---

## 🎯 Best Practices

### **1. Choose Appropriate Data Structure**
```c
// ✅ Use array for fixed-size, indexed access
int fixed_array[100];

// ✅ Use linked list for dynamic size, frequent insertions/deletions
// LinkedList implementation

// ✅ Use stack for LIFO operations
// Stack implementation

// ✅ Use queue for FIFO operations
// Queue implementation

// ✅ Use tree for hierarchical data
// Tree implementation
```

### **2. Handle Memory Management**
```c
// ✅ Always free allocated memory
Node* node = create_node(10);
// Use node
free(node);

// ✅ Check for NULL after allocation
Node* node = (Node*)malloc(sizeof(Node));
if (node == NULL) {
    // Handle error
}
```

### **3. Implement Error Checking**
```c
// ✅ Check bounds and conditions
void insert_at_position(LinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf("Invalid position\n");
        return;
    }
    // Insert logic
}
```

### **4. Use Consistent Naming**
```c
// ✅ Descriptive function names
void insert_at_beginning(LinkedList* list, int data);
void delete_from_end(LinkedList* list);
int search_element(LinkedList* list, int data);

// ❌ Generic names
void insert(LinkedList* list, int data);
void delete(LinkedList* list);
int search(LinkedList* list, int data);
```

---

## 🐛 Common Mistakes

### **1. Memory Leaks in Linked Lists**
```c
// Wrong - losing reference
void bad_function() {
    Node* node = create_node(10);
    node = create_node(20);  // Lost reference to first node
}

// Correct
void good_function() {
    Node* node1 = create_node(10);
    Node* node2 = create_node(20);
    // Use both nodes
    free(node1);
    free(node2);
}
```

### **2. Stack Overflow**
```c
// Wrong - recursive function without base case
void infinite_recursion() {
    infinite_recursion();  // Stack overflow
}

// Correct
void proper_recursion(int n) {
    if (n <= 0) return;  // Base case
    proper_recursion(n - 1);
}
```

### **3. Incorrect Pointer Updates**
```c
// Wrong - not updating head pointer
void bad_insert(LinkedList* list, int data) {
    Node* new_node = create_node(data);
    new_node->next = list->head;
    // Forgot: list->head = new_node;
}

// Correct
void good_insert(LinkedList* list, int data) {
    Node* new_node = create_node(data);
    new_node->next = list->head;
    list->head = new_node;
}
```

### **4. Off-by-One Errors**
```c
// Wrong - off by one
for (int i = 0; i <= list->size; i++) {  // May access invalid index
    // Process
}

// Correct
for (int i = 0; i < list->size; i++) {
    // Process
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Linked Lists**
- Implement a polynomial addition using linked lists
- Create a student database with search and sort functionality
- Build a music playlist manager

### **Exercise 2: Stacks and Queues**
- Implement stack using linked list
- Create a queue for job scheduling
- Build a browser history using stacks

### **Exercise 3: Trees**
- Implement tree traversal algorithms
- Create a binary search tree with balance checking
- Build an expression tree evaluator

### **Exercise 4: Hash Tables**
- Implement collision resolution strategies
- Create a dictionary using hash tables
- Build a cache with LRU eviction

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
Which data structure follows LIFO principle?
a) Queue
b) Stack
c) Linked List
d) Tree

### **Question 2:**
What is the time complexity of inserting at the beginning of a linked list?
a) O(1)
b) O(n)
c) O(log n)
d) O(n²)

### **Question 3:**
Which traversal visits root first?
a) Inorder
b) Preorder
c) Postorder
d) Level order

### **Question 4:**
What happens in hash table collision?
a) Program crashes
b) Data is lost
c) Multiple keys map to same index
d) Table size increases

### **Question 5:**
Which data structure is best for implementing recursion?
a) Stack
b) Queue
c) Linked List
d) Tree

---

## 🔗 Additional Resources

### **Data Structures**
- [Linked Lists](https://en.wikipedia.org/wiki/Linked_list)
- [Stacks and Queues](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))
- [Binary Trees](https://en.wikipedia.org/wiki/Binary_tree)
- [Hash Tables](https://en.wikipedia.org/wiki/Hash_table)

### **Further Reading**
- [Data Structures in C](https://www.programiz.com/dsa)
- [Algorithms and Data Structures](https://algs4.cs.princeton.edu/home/)
- [Big O Notation](https://www.bigocheatsheet.com/)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ Linked list implementations (singly, doubly, circular)
- ✅ Stack and queue data structures
- ✅ Binary tree operations and algorithms
- ✅ Hash table basics with collision handling
- ✅ Practical applications of data structures

**Next Lesson Preview:**
- Advanced C features
- Function pointers and callbacks
- Variable arguments
- Advanced preprocessor techniques

---

**🚀 Ready to explore advanced C concepts?**

[⬅️ Previous: Error Handling](18_Error_Handling.md) | [Next: Advanced C Features ➡️](20_Advanced_C_Features.md)