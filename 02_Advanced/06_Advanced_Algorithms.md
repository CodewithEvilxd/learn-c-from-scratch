# 🧮 Advanced C: Algorithms & Data Structures

## Mastering Complex Algorithms and Efficient Data Structures

---

## 🎯 Learning Objectives

- Master advanced sorting and searching algorithms
- Understand graph algorithms and implementations
- Learn dynamic programming techniques
- Implement advanced tree structures
- Master string algorithms and pattern matching
- Understand algorithm complexity analysis

---

## 📖 Algorithm Analysis Fundamentals

**Algorithm analysis** involves understanding time and space complexity to choose optimal solutions for problems.

### **Key Concepts:**
- Big O notation and complexity classes
- Amortized analysis
- Best, worst, and average case analysis
- Space-time tradeoffs
- Algorithm design paradigms

---

## 🔍 Advanced Sorting Algorithms

### **1. Quick Sort with Optimizations**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Partition function with median-of-three pivot selection
int median_of_three(int* arr, int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid]) {
        int temp = arr[low];
        arr[low] = arr[mid];
        arr[mid] = temp;
    }
    if (arr[low] > arr[high]) {
        int temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
    if (arr[mid] > arr[high]) {
        int temp = arr[mid];
        arr[mid] = arr[high];
        arr[high] = temp;
    }

    return mid;
}

int partition(int* arr, int low, int high) {
    // Use median-of-three for better pivot selection
    int pivot_index = median_of_three(arr, low, high);
    int pivot = arr[pivot_index];

    // Move pivot to end
    int temp = arr[pivot_index];
    arr[pivot_index] = arr[high];
    arr[high] = temp;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Optimized quicksort with insertion sort for small arrays
#define INSERTION_SORT_THRESHOLD 10

void insertion_sort(int* arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void quicksort(int* arr, int low, int high) {
    while (low < high) {
        // Use insertion sort for small arrays
        if (high - low < INSERTION_SORT_THRESHOLD) {
            insertion_sort(arr, low, high);
            return;
        }

        int pivot = partition(arr, low, high);

        // Recurse on smaller partition first (optimization)
        if (pivot - low < high - pivot) {
            quicksort(arr, low, pivot - 1);
            low = pivot + 1;
        } else {
            quicksort(arr, pivot + 1, high);
            high = pivot - 1;
        }
    }
}

// Public interface
void quick_sort(int* arr, int size) {
    if (size <= 1) return;
    quicksort(arr, 0, size - 1);
}
```

### **2. Merge Sort with Optimizations**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bottom-up merge sort (iterative, better cache performance)
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = malloc(n1 * sizeof(int));
    int* R = malloc(n2 * sizeof(int));

    if (!L || !R) {
        free(L);
        free(R);
        return;
    }

    memcpy(L, &arr[left], n1 * sizeof(int));
    memcpy(R, &arr[mid + 1], n2 * sizeof(int));

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void merge_sort(int* arr, int size) {
    for (int curr_size = 1; curr_size < size; curr_size *= 2) {
        for (int left = 0; left < size - 1; left += 2 * curr_size) {
            int mid = left + curr_size - 1;
            int right = (left + 2 * curr_size - 1 < size - 1) ?
                       (left + 2 * curr_size - 1) : (size - 1);

            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}
```

### **3. Timsort (Hybrid Sorting Algorithm)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_RUN 32

// Insertion sort for small arrays
void insertion_sort(int* arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Calculate minimum run size
int calc_min_run(int n) {
    int r = 0;
    while (n >= MIN_RUN) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

// Merge function for timsort
void timsort_merge(int* arr, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;

    int* left = malloc(len1 * sizeof(int));
    int* right = malloc(len2 * sizeof(int));

    if (!left || !right) {
        free(left);
        free(right);
        return;
    }

    memcpy(left, &arr[l], len1 * sizeof(int));
    memcpy(right, &arr[m + 1], len2 * sizeof(int));

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < len1) {
        arr[k++] = left[i++];
    }

    while (j < len2) {
        arr[k++] = right[j++];
    }

    free(left);
    free(right);
}

void timsort(int* arr, int n) {
    int min_run = calc_min_run(n);

    // Sort individual subarrays of size min_run
    for (int i = 0; i < n; i += min_run) {
        insertion_sort(arr, i, (i + min_run - 1 < n - 1) ?
                      (i + min_run - 1) : (n - 1));
    }

    // Merge sorted subarrays
    for (int size = min_run; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ?
                       (left + 2 * size - 1) : (n - 1);

            if (mid < right) {
                timsort_merge(arr, left, mid, right);
            }
        }
    }
}
```

---

## 🌳 Advanced Tree Structures

### **1. Red-Black Tree Implementation**

```c
#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int data;
    Color color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

typedef struct {
    RBNode* root;
    RBNode* nil;  // Sentinel node
} RBTree;

// Create a new node
RBNode* create_node(RBTree* tree, int data) {
    RBNode* node = malloc(sizeof(RBNode));
    if (!node) return NULL;

    node->data = data;
    node->color = RED;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = tree->nil;

    return node;
}

// Left rotate
void left_rotate(RBTree* tree, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Right rotate
void right_rotate(RBTree* tree, RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;

    if (y->right != tree->nil) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

// Fix red-black tree properties after insertion
void rb_insert_fixup(RBTree* tree, RBNode* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        } else {
            // Symmetric case for right side
            RBNode* y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }

    tree->root->color = BLACK;
}

// Insert a node
void rb_insert(RBTree* tree, int data) {
    RBNode* z = create_node(tree, data);
    if (!z) return;

    RBNode* y = tree->nil;
    RBNode* x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == tree->nil) {
        tree->root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    rb_insert_fixup(tree, z);
}

// Initialize red-black tree
RBTree* rb_tree_create() {
    RBTree* tree = malloc(sizeof(RBTree));
    if (!tree) return NULL;

    tree->nil = malloc(sizeof(RBNode));
    if (!tree->nil) {
        free(tree);
        return NULL;
    }

    tree->nil->color = BLACK;
    tree->nil->left = tree->nil->right = tree->nil->parent = tree->nil;
    tree->root = tree->nil;

    return tree;
}
```

### **2. B-Tree Implementation**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3  // Minimum degree

typedef struct BTreeNode {
    int* keys;
    struct BTreeNode** children;
    int n;          // Current number of keys
    bool leaf;      // True if leaf node
} BTreeNode;

typedef struct {
    BTreeNode* root;
    int t;  // Minimum degree
} BTree;

// Create a new B-tree node
BTreeNode* btree_create_node(int t, bool leaf) {
    BTreeNode* node = malloc(sizeof(BTreeNode));
    if (!node) return NULL;

    node->keys = malloc((2 * t - 1) * sizeof(int));
    node->children = malloc(2 * t * sizeof(BTreeNode*));
    node->n = 0;
    node->leaf = leaf;

    if (!node->keys || !node->children) {
        free(node->keys);
        free(node->children);
        free(node);
        return NULL;
    }

    return node;
}

// Split child node
void btree_split_child(BTree* tree, BTreeNode* x, int i) {
    BTreeNode* y = x->children[i];
    BTreeNode* z = btree_create_node(tree->t, y->leaf);

    if (!z) return;

    // Move keys from y to z
    for (int j = 0; j < tree->t - 1; j++) {
        z->keys[j] = y->keys[j + tree->t];
    }

    // Move children if not leaf
    if (!y->leaf) {
        for (int j = 0; j < tree->t; j++) {
            z->children[j] = y->children[j + tree->t];
        }
    }

    y->n = tree->t - 1;
    z->n = tree->t - 1;

    // Insert z as child of x
    for (int j = x->n; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
    }
    x->children[i + 1] = z;

    // Move middle key from y to x
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }
    x->keys[i] = y->keys[tree->t - 1];
    x->n++;
}

// Insert non-full node
void btree_insert_nonfull(BTree* tree, BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        // Find position to insert
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        // Find child to descend
        while (i >= 0 && x->keys[i] > k) {
            i--;
        }
        i++;

        // Split child if full
        if (x->children[i]->n == 2 * tree->t - 1) {
            btree_split_child(tree, x, i);
            if (k > x->keys[i]) {
                i++;
            }
        }

        btree_insert_nonfull(tree, x->children[i], k);
    }
}

// Insert key into B-tree
void btree_insert(BTree* tree, int k) {
    BTreeNode* r = tree->root;

    // If root is full, create new root
    if (r->n == 2 * tree->t - 1) {
        BTreeNode* s = btree_create_node(tree->t, false);
        if (!s) return;

        tree->root = s;
        s->children[0] = r;
        btree_split_child(tree, s, 0);
        btree_insert_nonfull(tree, s, k);
    } else {
        btree_insert_nonfull(tree, r, k);
    }
}

// Search for a key in B-tree
BTreeNode* btree_search(BTreeNode* x, int k) {
    int i = 0;

    while (i < x->n && k > x->keys[i]) {
        i++;
    }

    if (i < x->n && k == x->keys[i]) {
        return x;
    }

    if (x->leaf) {
        return NULL;
    }

    return btree_search(x->children[i], k);
}

// Create B-tree
BTree* btree_create(int t) {
    BTree* tree = malloc(sizeof(BTree));
    if (!tree) return NULL;

    tree->t = t;
    tree->root = btree_create_node(t, true);

    if (!tree->root) {
        free(tree);
        return NULL;
    }

    return tree;
}
```

---

## 🔗 Graph Algorithms

### **1. Dijkstra's Shortest Path Algorithm**

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define V 9  // Number of vertices

// Find vertex with minimum distance
int min_distance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Print solution
void print_solution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Dijkstra's algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool visited[V];

    // Initialize distances and visited array
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = min_distance(dist, visited);
        visited[u] = true;

        // Update distance of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    print_solution(dist);
}

// Optimized Dijkstra with binary heap
typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode* nodes;
    int size;
    int capacity;
    int* positions;
} MinHeap;

// Create min heap
MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = malloc(sizeof(MinHeap));
    heap->nodes = malloc(capacity * sizeof(HeapNode));
    heap->positions = malloc(V * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

// Swap heap nodes
void swap_heap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify
void min_heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size &&
        heap->nodes[left].distance < heap->nodes[smallest].distance) {
        smallest = left;
    }

    if (right < heap->size &&
        heap->nodes[right].distance < heap->nodes[smallest].distance) {
        smallest = right;
    }

    if (smallest != idx) {
        // Update positions
        heap->positions[heap->nodes[smallest].vertex] = idx;
        heap->positions[heap->nodes[idx].vertex] = smallest;

        swap_heap_nodes(&heap->nodes[smallest], &heap->nodes[idx]);
        min_heapify(heap, smallest);
    }
}

// Extract minimum
HeapNode extract_min(MinHeap* heap) {
    if (heap->size == 0) {
        HeapNode null_node = {-1, INT_MAX};
        return null_node;
    }

    HeapNode root = heap->nodes[0];
    HeapNode last = heap->nodes[heap->size - 1];
    heap->nodes[0] = last;

    heap->positions[root.vertex] = heap->size - 1;
    heap->positions[last.vertex] = 0;

    heap->size--;
    min_heapify(heap, 0);

    return root;
}

// Decrease key
void decrease_key(MinHeap* heap, int vertex, int distance) {
    int i = heap->positions[vertex];
    heap->nodes[i].distance = distance;

    while (i > 0 && heap->nodes[i].distance <
           heap->nodes[(i - 1) / 2].distance) {
        heap->positions[heap->nodes[i].vertex] = (i - 1) / 2;
        heap->positions[heap->nodes[(i - 1) / 2].vertex] = i;

        swap_heap_nodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Check if heap contains vertex
bool is_in_heap(MinHeap* heap, int vertex) {
    return heap->positions[vertex] < heap->size;
}

// Optimized Dijkstra
void dijkstra_optimized(int graph[V][V], int src) {
    int dist[V];
    MinHeap* heap = create_min_heap(V);

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        heap->nodes[i].vertex = i;
        heap->nodes[i].distance = INT_MAX;
        heap->positions[i] = i;
    }

    heap->nodes[src].distance = 0;
    dist[src] = 0;
    heap->size = V;

    while (heap->size > 0) {
        HeapNode min_node = extract_min(heap);
        int u = min_node.vertex;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];

                if (is_in_heap(heap, v)) {
                    decrease_key(heap, v, dist[v]);
                }
            }
        }
    }

    print_solution(dist);

    free(heap->nodes);
    free(heap->positions);
    free(heap);
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    printf("Dijkstra's Algorithm (Standard):\n");
    dijkstra(graph, 0);

    printf("\nDijkstra's Algorithm (Optimized with Heap):\n");
    dijkstra_optimized(graph, 0);

    return 0;
}
```

### **2. A* Pathfinding Algorithm**

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#define GRID_SIZE 10
#define START_X 0
#define START_Y 0
#define GOAL_X 9
#define GOAL_Y 9

typedef struct {
    int x, y;
    int f, g, h;
    struct Node* parent;
} Node;

typedef struct {
    Node* nodes[GRID_SIZE][GRID_SIZE];
    bool closed[GRID_SIZE][GRID_SIZE];
    Node* open_list[GRID_SIZE * GRID_SIZE];
    int open_count;
} AStar;

// Manhattan distance heuristic
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check if position is valid
bool is_valid(int x, int y) {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
}

// Check if position is blocked (simple obstacle avoidance)
bool is_blocked(int x, int y) {
    // Add some obstacles
    return (x == 3 && y == 3) || (x == 5 && y == 5) || (x == 7 && y == 2);
}

// Get node with lowest f score
Node* get_lowest_f(AStar* astar) {
    if (astar->open_count == 0) return NULL;

    Node* lowest = astar->open_list[0];
    int lowest_idx = 0;

    for (int i = 1; i < astar->open_count; i++) {
        if (astar->open_list[i]->f < lowest->f) {
            lowest = astar->open_list[i];
            lowest_idx = i;
        }
    }

    // Remove from open list
    astar->open_list[lowest_idx] = astar->open_list[astar->open_count - 1];
    astar->open_count--;

    return lowest;
}

// Add to open list
void add_to_open(AStar* astar, Node* node) {
    astar->open_list[astar->open_count++] = node;
}

// A* algorithm
Node* a_star() {
    AStar astar = {0};

    // Initialize start node
    Node* start = malloc(sizeof(Node));
    start->x = START_X;
    start->y = START_Y;
    start->g = 0;
    start->h = heuristic(START_X, START_Y, GOAL_X, GOAL_Y);
    start->f = start->g + start->h;
    start->parent = NULL;

    astar.nodes[START_X][START_Y] = start;
    add_to_open(&astar, start);

    while (astar.open_count > 0) {
        Node* current = get_lowest_f(&astar);

        if (current->x == GOAL_X && current->y == GOAL_Y) {
            return current;  // Found path
        }

        astar.closed[current->x][current->y] = true;

        // Check neighbors
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!is_valid(nx, ny) || is_blocked(nx, ny) ||
                astar.closed[nx][ny]) {
                continue;
            }

            int tentative_g = current->g + 1;

            if (astar.nodes[nx][ny] == NULL) {
                Node* neighbor = malloc(sizeof(Node));
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(nx, ny, GOAL_X, GOAL_Y);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;

                astar.nodes[nx][ny] = neighbor;
                add_to_open(&astar, neighbor);
            } else if (tentative_g < astar.nodes[nx][ny]->g) {
                astar.nodes[nx][ny]->g = tentative_g;
                astar.nodes[nx][ny]->f = tentative_g + astar.nodes[nx][ny]->h;
                astar.nodes[nx][ny]->parent = current;
            }
        }
    }

    return NULL;  // No path found
}

// Print path
void print_path(Node* goal) {
    if (goal == NULL) {
        printf("No path found!\n");
        return;
    }

    printf("Path found:\n");
    Node* current = goal;

    while (current != NULL) {
        printf("(%d, %d)", current->x, current->y);
        if (current->parent != NULL) {
            printf(" <- ");
        }
        current = current->parent;
    }
    printf("\n");
}

int main() {
    Node* goal = a_star();
    print_path(goal);

    // Cleanup (simplified)
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            free(astar.nodes[i][j]);
        }
    }

    return 0;
}
```

---

## 🎯 Dynamic Programming

### **1. Longest Common Subsequence**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LCS using dynamic programming
int lcs_length(const char* X, const char* Y) {
    int m = strlen(X);
    int n = strlen(Y);

    int** dp = malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = calloc(n + 1, sizeof(int));
    }

    // Fill dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ?
                          dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int result = dp[m][n];

    // Free memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

// Space-optimized LCS
int lcs_optimized(const char* X, const char* Y) {
    int m = strlen(X);
    int n = strlen(Y);

    if (m > n) {
        // Ensure X is shorter
        const char* temp = X;
        X = Y;
        Y = temp;
        int temp_len = m;
        m = n;
        n = temp_len;
    }

    int* prev = calloc(m + 1, sizeof(int));
    int* curr = calloc(m + 1, sizeof(int));

    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            if (X[i - 1] == Y[j - 1]) {
                curr[i] = prev[i - 1] + 1;
            } else {
                curr[i] = (prev[i] > curr[i - 1]) ? prev[i] : curr[i - 1];
            }
        }

        // Swap arrays
        int* temp = prev;
        prev = curr;
        curr = temp;
        memset(curr, 0, (m + 1) * sizeof(int));
    }

    int result = prev[m];
    free(prev);
    free(curr);

    return result;
}
```

### **2. Knapsack Problem**

```c
#include <stdio.h>
#include <stdlib.h>

// 0/1 Knapsack using dynamic programming
int knapsack(int weights[], int values[], int n, int capacity) {
    int** dp = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = calloc(capacity + 1, sizeof(int));
    }

    // Fill dp table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w]) ?
                          values[i - 1] + dp[i - 1][w - weights[i - 1]] : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][capacity];

    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

// Space-optimized knapsack
int knapsack_optimized(int weights[], int values[], int n, int capacity) {
    int* dp = calloc(capacity + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            if (values[i] + dp[w - weights[i]] > dp[w]) {
                dp[w] = values[i] + dp[w - weights[i]];
            }
        }
    }

    int result = dp[capacity];
    free(dp);

    return result;
}
```

---

## 🔤 Advanced String Algorithms

### **1. KMP Pattern Matching**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compute prefix function for KMP
void compute_prefix_function(const char* pattern, int* prefix, int m) {
    int len = 0;
    prefix[0] = 0;

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            prefix[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = prefix[len - 1];
            } else {
                prefix[i] = 0;
                i++;
            }
        }
    }
}

// KMP search algorithm
int kmp_search(const char* text, const char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    if (m == 0) return 0;

    int* prefix = malloc(m * sizeof(int));
    compute_prefix_function(pattern, prefix, m);

    int i = 0;  // index for text
    int j = 0;  // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            free(prefix);
            return i - j;  // Pattern found at position i - j
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                i++;
            }
        }
    }

    free(prefix);
    return -1;  // Pattern not found
}

// Multiple pattern search
typedef struct {
    char* pattern;
    int* prefix;
    int length;
} Pattern;

int* kmp_multi_search(const char* text, Pattern* patterns, int num_patterns) {
    int* results = calloc(num_patterns, sizeof(int));
    for (int i = 0; i < num_patterns; i++) {
        results[i] = kmp_search(text, patterns[i].pattern);
    }
    return results;
}
```

### **2. Rabin-Karp Algorithm**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PRIME 101
#define BASE 256

// Rolling hash function
uint64_t compute_hash(const char* str, int length) {
    uint64_t hash = 0;
    uint64_t power = 1;

    for (int i = length - 1; i >= 0; i--) {
        hash = (hash + (uint64_t)str[i] * power) % PRIME;
        power = (power * BASE) % PRIME;
    }

    return hash;
}

// Rabin-Karp search
int rabin_karp_search(const char* text, const char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    if (m == 0) return 0;
    if (m > n) return -1;

    uint64_t pattern_hash = compute_hash(pattern, m);
    uint64_t text_hash = compute_hash(text, m);

    uint64_t power = 1;
    for (int i = 0; i < m - 1; i++) {
        power = (power * BASE) % PRIME;
    }

    for (int i = 0; i <= n - m; i++) {
        if (pattern_hash == text_hash) {
            // Verify match (handle hash collisions)
            if (strncmp(text + i, pattern, m) == 0) {
                return i;
            }
        }

        if (i < n - m) {
            // Update rolling hash
            text_hash = (text_hash - (uint64_t)text[i] * power % PRIME + PRIME) % PRIME;
            text_hash = (text_hash * BASE + (uint64_t)text[i + m]) % PRIME;
        }
    }

    return -1;
}

// Multiple pattern search with Rabin-Karp
typedef struct {
    char* pattern;
    uint64_t hash;
    int length;
} RKPattern;

int* rabin_karp_multi_search(const char* text, RKPattern* patterns, int num_patterns) {
    int* results = malloc(num_patterns * sizeof(int));
    for (int i = 0; i < num_patterns; i++) {
        results[i] = rabin_karp_search(text, patterns[i].pattern);
    }
    return results;
}
```

---

## 🎯 Best Practices for Algorithm Implementation

### **1. Algorithm Selection**
```c
// Choose algorithm based on constraints
void sort_array(int* arr, int size, int constraints) {
    if (constraints & MEMORY_LIMITED) {
        // Use in-place sort
        quick_sort(arr, size);
    } else if (constraints & STABLE_REQUIRED) {
        // Use stable sort
        merge_sort(arr, size);
    } else if (constraints & NEARLY_SORTED) {
        // Use adaptive sort
        timsort(arr, size);
    } else {
        // Use general-purpose sort
        std::sort(arr, arr + size);
    }
}
```

### **2. Complexity Analysis**
```c
// Time complexity analysis
typedef enum {
    O_1, O_LOG_N, O_N, O_N_LOG_N, O_N2, O_2N
} Complexity;

// Analyze algorithm complexity
Complexity analyze_complexity(int n, long long operations) {
    if (operations <= 100) return O_1;
    if (operations <= 100 * log2(n)) return O_LOG_N;
    if (operations <= 100 * n) return O_N;
    if (operations <= 100 * n * log2(n)) return O_N_LOG_N;
    if (operations <= 100 * n * n) return O_N2;
    return O_2N;
}
```

### **3. Memory Management**
```c
// Efficient memory usage
typedef struct {
    void* buffer;
    size_t size;
    size_t used;
} MemoryPool;

void* pool_allocate(MemoryPool* pool, size_t size) {
    if (pool->used + size > pool->size) {
        return NULL;  // Out of memory
    }

    void* ptr = (char*)pool->buffer + pool->used;
    pool->used += size;

    return ptr;
}

// Cache-aligned allocations
void* aligned_allocate(size_t size, size_t alignment) {
    void* ptr;
    if (posix_memalign(&ptr, alignment, size) != 0) {
        return NULL;
    }
    return ptr;
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Sorting Algorithms**
- Implement counting sort for integer arrays
- Create a hybrid sort combining quicksort and heapsort
- Implement external sorting for large datasets

### **Exercise 2: Graph Algorithms**
- Implement Floyd-Warshall algorithm for all-pairs shortest paths
- Create a minimum spanning tree using Kruskal's algorithm
- Build a topological sort for dependency resolution

### **Exercise 3: Dynamic Programming**
- Solve the traveling salesman problem using DP
- Implement the longest increasing subsequence
- Create a solution for the knapsack problem with multiple constraints

### **Exercise 4: String Algorithms**
- Implement the Z-algorithm for pattern matching
- Create a suffix array for efficient string searching
- Build a compression algorithm using LZ77

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the time complexity of quicksort in the worst case?
a) O(n)
b) O(n log n)
c) O(n²)
d) O(log n)

### **Question 2:**
Which data structure is typically used to implement Dijkstra's algorithm efficiently?
a) Array
b) Linked List
c) Binary Heap
d) Hash Table

### **Question 3:**
What is the space complexity of the standard LCS dynamic programming solution?
a) O(1)
b) O(n)
c) O(n + m)
d) O(n * m)

### **Question 4:**
Which string matching algorithm uses a prefix table?
a) Naive search
b) Rabin-Karp
c) KMP
d) Boyer-Moore

### **Question 5:**
What property must a red-black tree maintain?
a) All leaves are black
b) No two adjacent red nodes
c) Both A and B
d) Perfect balance

---

## 🔗 Additional Resources

### **Algorithm References**
- [Introduction to Algorithms (CLRS)](https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/0262033844)
- [Algorithm Design Manual](https://www.amazon.com/Algorithm-Design-Manual-Steven-Skiena/dp/0387948600)
- [Competitive Programming](https://cp-algorithms.com/)

### **Further Reading**
- [The Art of Computer Programming](https://www.amazon.com/Computer-Programming-Volumes-1-4A-Boxed/dp/0321751043)
- [Algorithms](https://www.amazon.com/Algorithms-4th-Robert-Sedgewick/dp/032157351X)
- [Hacker's Delight](https://www.amazon.com/Hackers-Delight-2nd-Henry-Warren/dp/0321842685)

---

## 🎯 Next Steps

**Congratulations!** You've mastered:
- ✅ Advanced sorting algorithms (quicksort, mergesort, timsort)
- ✅ Complex tree structures (red-black trees, B-trees)
- ✅ Graph algorithms (Dijkstra, A*)
- ✅ Dynamic programming techniques
- ✅ Advanced string algorithms (KMP, Rabin-Karp)
- ✅ Algorithm complexity analysis

**Next Lesson Preview:**
- Competitive programming techniques
- Advanced data structures (tries, segment trees)
- Mathematical algorithms and number theory
- Optimization problems and metaheuristics
- Real-world algorithm applications

---

**🚀 Ready to become a competitive programmer?**

[⬅️ Previous: