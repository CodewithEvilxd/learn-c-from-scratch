# 🎯 Practical 129: Singly Linked List Operations

## 📋 Problem Statement

Write a C program to implement basic operations on a singly linked list (create, insert, delete, display, search).

## 🎯 Learning Objectives

- Understand linked list data structure
- Practice dynamic memory allocation
- Learn pointer manipulation
- Implement basic list operations
- Understand memory management

## 📝 Requirements

1. Implement singly linked list with following operations:
   - Create empty list
   - Insert at beginning
   - Insert at end
   - Insert at specific position
   - Delete from beginning
   - Delete from end
   - Delete specific node
   - Search for element
   - Display list
   - Count nodes

2. Handle edge cases (empty list, single node, invalid positions)
3. Proper memory management (free allocated memory)
4. User-friendly menu interface

## 💡 Hints

- Define Node structure with data and next pointer
- Use typedef for cleaner code
- Implement separate functions for each operation
- Handle NULL pointers carefully
- Free memory when deleting nodes

## 🔧 Solution

```c
// Practical 129: Singly Linked List Operations
// Implements basic operations on singly linked list

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function prototypes
Node* createNode(int data);
void insertAtBeginning(Node** head, int data);
void insertAtEnd(Node** head, int data);
void insertAtPosition(Node** head, int data, int position);
void deleteFromBeginning(Node** head);
void deleteFromEnd(Node** head);
void deleteAtPosition(Node** head, int position);
int searchElement(Node* head, int key);
void displayList(Node* head);
int countNodes(Node* head);
void freeList(Node** head);

int main() {
    Node* head = NULL;
    int choice, data, position;

    printf("Singly Linked List Operations\n");
    printf("=============================\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete at Position\n");
        printf("7. Search Element\n");
        printf("8. Display List\n");
        printf("9. Count Nodes\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;

            case 2:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;

            case 3:
                printf("Enter data and position: ");
                scanf("%d %d", &data, &position);
                insertAtPosition(&head, data, position);
                break;

            case 4:
                deleteFromBeginning(&head);
                break;

            case 5:
                deleteFromEnd(&head);
                break;

            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;

            case 7:
                printf("Enter element to search: ");
                scanf("%d", &data);
                position = searchElement(head, data);
                if (position != -1) {
                    printf("Element found at position %d\n", position);
                } else {
                    printf("Element not found\n");
                }
                break;

            case 8:
                displayList(head);
                break;

            case 9:
                printf("Total nodes: %d\n", countNodes(head));
                break;

            case 0:
                freeList(&head);
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d at beginning\n", data);
}

// Insert at end
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        printf("Inserted %d at end\n", data);
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Inserted %d at end\n", data);
}

// Insert at specific position
void insertAtPosition(Node** head, int data, int position) {
    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }

    if (position == 1) {
        insertAtBeginning(head, data);
        return;
    }

    Node* newNode = createNode(data);
    Node* temp = *head;

    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d\n", data, position);
}

// Delete from beginning
void deleteFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Node* temp = *head;
    *head = (*head)->next;
    printf("Deleted %d from beginning\n", temp->data);
    free(temp);
}

// Delete from end
void deleteFromEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    if ((*head)->next == NULL) {
        printf("Deleted %d from end\n", (*head)->data);
        free(*head);
        *head = NULL;
        return;
    }

    Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    printf("Deleted %d from end\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

// Delete at specific position
void deleteAtPosition(Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }

    if (position == 1) {
        deleteFromBeginning(head);
        return;
    }

    Node* temp = *head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position out of range!\n");
        return;
    }

    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("Deleted %d from position %d\n", nodeToDelete->data, position);
    free(nodeToDelete);
}

// Search element
int searchElement(Node* head, int key) {
    Node* temp = head;
    int position = 1;

    while (temp != NULL) {
        if (temp->data == key) {
            return position;
        }
        temp = temp->next;
        position++;
    }

    return -1;
}

// Display list
void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("Linked List: ");
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Count nodes
int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

// Free entire list
void freeList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}
```

## 📊 Test Cases

### Test Case 1: Basic Operations
```
Operations:
1. Insert at end: 10
2. Insert at end: 20
3. Insert at beginning: 5
4. Display: 5 -> 10 -> 20 -> NULL
5. Search 10: Found at position 2
```

### Test Case 2: Position-based Operations
```
Operations:
1. Insert at end: 1,2,3,4,5
2. Insert at position 3: 99
3. Display: 1 -> 2 -> 99 -> 3 -> 4 -> 5 -> NULL
4. Delete at position 3
5. Display: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
```

## 🔍 Explanation

1. **Node Structure**: Contains data and next pointer
2. **Operations**:
   - Insert: Create new node and link appropriately
   - Delete: Unlink node and free memory
   - Search: Traverse and compare values
   - Display: Traverse and print all elements

3. **Edge Cases**:
   - Empty list operations
   - Single node operations
   - Invalid positions
   - Memory allocation failures

## 🎯 Key Concepts Covered

- Dynamic memory allocation
- Pointer manipulation
- Linked list traversal
- Memory deallocation
- Error handling

## 🚀 Extensions

1. Implement doubly linked list
2. Add sorting functionality
3. Implement circular linked list
4. Add reverse operation
5. Implement stack/queue using linked list