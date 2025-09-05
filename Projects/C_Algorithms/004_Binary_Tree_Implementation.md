# 🌳 Binary Tree Implementation
## Complete binary tree data structure with operations

---

## 📋 Project Overview

This project implements a complete binary tree data structure in C with all essential operations including insertion, deletion, traversal, and searching. Binary trees are fundamental data structures used in computer science for efficient data organization and retrieval.

## 🎯 Learning Objectives

- Understand binary tree data structure
- Practice recursive algorithms
- Learn tree traversal techniques
- Implement dynamic memory management
- Practice pointer manipulation

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Libraries**: Standard C libraries (stdlib.h, stdio.h)
- **Platform**: Cross-platform
- **Compiler**: GCC, MinGW, or MSVC

## 📁 Project Structure

```
binary_tree/
├── src/
│   ├── main.c           # Main program with menu
│   ├── tree.c           # Core tree operations
│   ├── traversal.c      # Tree traversal functions
│   ├── utils.c          # Utility functions
│   └── queue.c          # Queue for level-order traversal
├── include/
│   ├── tree.h
│   ├── traversal.h
│   ├── utils.h
│   └── queue.h
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Tree Structure and Basic Operations**

```c
// tree.h
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
    int size;
} BinaryTree;

// Function prototypes
BinaryTree* create_tree(void);
TreeNode* create_node(int data);
void insert_node(BinaryTree* tree, int data);
TreeNode* search_node(BinaryTree* tree, int data);
void delete_node(BinaryTree* tree, int data);
void free_tree(BinaryTree* tree);
int get_height(TreeNode* node);
int get_size(TreeNode* node);
bool is_empty(BinaryTree* tree);

#endif
```

```c
// tree.c
#include "tree.h"

BinaryTree* create_tree(void) {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (tree == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

TreeNode* create_node(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert_node(BinaryTree* tree, int data) {
    TreeNode* new_node = create_node(data);

    if (tree->root == NULL) {
        tree->root = new_node;
        tree->size++;
        return;
    }

    TreeNode* current = tree->root;
    TreeNode* parent = NULL;

    // Find insertion point
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // Duplicate value, free node and return
            free(new_node);
            return;
        }
    }

    // Insert new node
    if (data < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    tree->size++;
}

TreeNode* search_node(BinaryTree* tree, int data) {
    TreeNode* current = tree->root;

    while (current != NULL) {
        if (data == current->data) {
            return current;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

TreeNode* find_min(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void delete_node(BinaryTree* tree, int data) {
    TreeNode* current = tree->root;
    TreeNode* parent = NULL;

    // Find node to delete
    while (current != NULL && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Node with value %d not found\n", data);
        return;
    }

    // Case 1: Node has no children
    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            tree->root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
    // Case 2: Node has one child
    else if (current->left == NULL || current->right == NULL) {
        TreeNode* child = (current->left != NULL) ? current->left : current->right;

        if (parent == NULL) {
            tree->root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(current);
    }
    // Case 3: Node has two children
    else {
        TreeNode* successor = find_min(current->right);
        int successor_data = successor->data;
        delete_node(tree, successor_data); // Recursively delete successor
        current->data = successor_data;
    }

    tree->size--;
}

void free_tree_helper(TreeNode* node) {
    if (node != NULL) {
        free_tree_helper(node->left);
        free_tree_helper(node->right);
        free(node);
    }
}

void free_tree(BinaryTree* tree) {
    if (tree != NULL) {
        free_tree_helper(tree->root);
        free(tree);
    }
}

int get_height(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }

    int left_height = get_height(node->left);
    int right_height = get_height(node->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

int get_size(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }

    return 1 + get_size(node->left) + get_size(node->right);
}

bool is_empty(BinaryTree* tree) {
    return tree->root == NULL;
}
```

### **Step 2: Tree Traversal Algorithms**

```c
// traversal.h
#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "tree.h"

void inorder_traversal(TreeNode* node);
void preorder_traversal(TreeNode* node);
void postorder_traversal(TreeNode* node);
void levelorder_traversal(TreeNode* root);

#endif
```

```c
// traversal.c
#include "traversal.h"
#include "queue.h"

void inorder_traversal(TreeNode* node) {
    if (node != NULL) {
        inorder_traversal(node->left);
        printf("%d ", node->data);
        inorder_traversal(node->right);
    }
}

void preorder_traversal(TreeNode* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preorder_traversal(node->left);
        preorder_traversal(node->right);
    }
}

void postorder_traversal(TreeNode* node) {
    if (node != NULL) {
        postorder_traversal(node->left);
        postorder_traversal(node->right);
        printf("%d ", node->data);
    }
}

void levelorder_traversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    Queue* queue = create_queue();
    enqueue(queue, root);

    while (!is_queue_empty(queue)) {
        TreeNode* current = dequeue(queue);
        printf("%d ", current->data);

        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }

    free_queue(queue);
}
```

### **Step 3: Queue Implementation for Level-Order Traversal**

```c
// queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"

typedef struct QueueNode {
    TreeNode* data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

Queue* create_queue(void);
void enqueue(Queue* queue, TreeNode* data);
TreeNode* dequeue(Queue* queue);
bool is_queue_empty(Queue* queue);
void free_queue(Queue* queue);

#endif
```

```c
// queue.c
#include "queue.h"

Queue* create_queue(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void enqueue(Queue* queue, TreeNode* data) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    new_node->data = data;
    new_node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    queue->size++;
}

TreeNode* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    QueueNode* temp = queue->front;
    TreeNode* data = temp->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;

    return data;
}

bool is_queue_empty(Queue* queue) {
    return queue->front == NULL;
}

void free_queue(Queue* queue) {
    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}
```

### **Step 4: Main Program with User Interface**

```c
// main.c
#include "tree.h"
#include "traversal.h"
#include <string.h>

void display_menu(void) {
    printf("\n=== Binary Tree Operations ===\n");
    printf("1. Insert Node\n");
    printf("2. Delete Node\n");
    printf("3. Search Node\n");
    printf("4. Inorder Traversal\n");
    printf("5. Preorder Traversal\n");
    printf("6. Postorder Traversal\n");
    printf("7. Level-order Traversal\n");
    printf("8. Get Tree Height\n");
    printf("9. Get Tree Size\n");
    printf("10. Check if Empty\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    BinaryTree* tree = create_tree();
    int choice, data;

    printf("Binary Tree Implementation in C\n");
    printf("===============================\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Insert
                printf("Enter value to insert: ");
                scanf("%d", &data);
                insert_node(tree, data);
                printf("Node inserted successfully\n");
                break;

            case 2: // Delete
                printf("Enter value to delete: ");
                scanf("%d", &data);
                delete_node(tree, data);
                break;

            case 3: // Search
                printf("Enter value to search: ");
                scanf("%d", &data);
                if (search_node(tree, data) != NULL) {
                    printf("Node found in the tree\n");
                } else {
                    printf("Node not found in the tree\n");
                }
                break;

            case 4: // Inorder
                printf("Inorder Traversal: ");
                inorder_traversal(tree->root);
                printf("\n");
                break;

            case 5: // Preorder
                printf("Preorder Traversal: ");
                preorder_traversal(tree->root);
                printf("\n");
                break;

            case 6: // Postorder
                printf("Postorder Traversal: ");
                postorder_traversal(tree->root);
                printf("\n");
                break;

            case 7: // Level-order
                printf("Level-order Traversal: ");
                levelorder_traversal(tree->root);
                printf("\n");
                break;

            case 8: // Height
                printf("Tree Height: %d\n", get_height(tree->root));
                break;

            case 9: // Size
                printf("Tree Size: %d\n", tree->size);
                break;

            case 10: // Is Empty
                if (is_empty(tree)) {
                    printf("Tree is empty\n");
                } else {
                    printf("Tree is not empty\n");
                }
                break;

            case 0: // Exit
                printf("Exiting program...\n");
                free_tree(tree);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Tree Operations**
- [x] Node insertion (BST property)
- [x] Node deletion (all cases)
- [x] Node searching
- [x] Tree traversal (4 types)
- [x] Height calculation
- [x] Size calculation

### **✅ Advanced Features**
- [x] Memory management
- [x] Error handling
- [x] Duplicate prevention
- [x] Tree statistics
- [x] User-friendly interface

### **🚀 Extensions**
- [ ] Tree balancing (AVL/Red-Black)
- [ ] Tree visualization
- [ ] File I/O for persistence
- [ ] Threaded binary trees
- [ ] Expression tree evaluation
- [ ] Huffman coding tree

## 🧪 Testing and Usage

### **Sample Operations**
```c
// Create and populate tree
BinaryTree* tree = create_tree();
insert_node(tree, 50);
insert_node(tree, 30);
insert_node(tree, 70);
insert_node(tree, 20);
insert_node(tree, 40);

// Traversals
printf("Inorder: ");
inorder_traversal(tree->root);    // 20 30 40 50 70

printf("Preorder: ");
preorder_traversal(tree->root);   // 50 30 20 40 70

printf("Level-order: ");
levelorder_traversal(tree->root); // 50 30 70 20 40
```

### **Test Cases**
- Insert nodes in different orders
- Delete leaf, single-child, and two-child nodes
- Search for existing and non-existing values
- Test all traversal methods
- Verify tree height and size calculations

## 📊 Technical Learning Outcomes

### **Data Structure Concepts**
- Binary tree properties
- BST invariants
- Tree balancing concepts
- Traversal algorithms
- Recursive vs iterative approaches

### **C Programming Skills**
- Dynamic memory allocation
- Pointer manipulation
- Recursive function implementation
- Struct usage for complex data
- Memory deallocation and leak prevention

## 🚀 Advanced Extensions

### **AVL Tree Implementation**
```c
typedef struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

int get_balance_factor(AVLNode* node) {
    if (node == NULL) return 0;
    return get_height(node->left) - get_height(node->right);
}

AVLNode* rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    return x;
}
```

### **Tree Visualization**
```c
void print_tree(TreeNode* root, int space) {
    if (root == NULL) return;

    space += 5;

    print_tree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    print_tree(root->left, space);
}
```

## 📖 References

- **Introduction to Algorithms** by Cormen et al.
- **Data Structures and Algorithm Analysis** by Weiss
- **Binary Tree Traversals** - GeeksforGeeks
- **Tree Data Structures** - Stanford CS Library

## 🎯 Real-World Applications

- **Database Indexing**: B-trees, B+-trees
- **File Systems**: Directory structures
- **Compiler Design**: Expression trees, syntax trees
- **Artificial Intelligence**: Decision trees, game trees
- **Network Routing**: Routing tables, spanning trees

---

**🌳 This project provides a complete understanding of binary tree data structures and algorithms in C!**