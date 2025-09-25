# 08. Data Structures - Comprehensive Guide to Data Organization

## Introduction

Data structures are fundamental building blocks of efficient software systems. They provide systematic ways to organize, store, and manipulate data to optimize operations like searching, sorting, insertion, and deletion. Understanding data structures is essential for writing high-performance programs and solving complex computational problems. This comprehensive guide explores both basic and advanced data structures with detailed implementations, analysis, and real-world applications.

## What are Data Structures? - Deep Analysis

Data structures are specialized formats for organizing and storing data in computer memory. They define the relationships between data elements and specify the operations that can be performed on them. The choice of data structure significantly impacts program efficiency, memory usage, and algorithmic complexity.

### Fundamental Characteristics

1. **Organization**: How data elements are arranged and related
2. **Operations**: Supported operations (insert, delete, search, traverse)
3. **Performance**: Time and space complexity of operations
4. **Memory Layout**: How data is stored in memory
5. **Access Patterns**: How data can be accessed and modified

### Classification System

#### By Structure Type
- **Linear Data Structures**: Elements in sequential order (arrays, linked lists, stacks, queues)
- **Non-Linear Data Structures**: Elements in hierarchical/complex relationships (trees, graphs, hash tables)
- **Homogeneous Data Structures**: All elements same type (arrays, matrices)
- **Heterogeneous Data Structures**: Elements can be different types (structs, objects)

#### By Memory Allocation
- **Contiguous Memory**: Elements stored in adjacent memory locations (arrays)
- **Linked Memory**: Elements connected via pointers/references (linked lists, trees)
- **Dynamic Memory**: Memory allocated/deallocated at runtime (all advanced structures)

#### By Access Pattern
- **Sequential Access**: Elements accessed in order (linked lists)
- **Random Access**: Any element accessible directly (arrays)
- **Indexed Access**: Elements accessed via keys (hash tables, dictionaries)
- **Hierarchical Access**: Elements accessed via tree/graph traversal

## Arrays - Fixed-Size Contiguous Storage

Arrays are fundamental data structures that store elements of the same type in contiguous memory locations. They provide constant-time access to elements and are the basis for many other data structures.

### Array Characteristics and Properties

#### Memory Layout
- **Contiguous Allocation**: Elements stored in adjacent memory locations
- **Fixed Size**: Size determined at creation time
- **Homogeneous Elements**: All elements must be same type
- **Random Access**: Direct access to any element via index
- **Zero-Based Indexing**: First element at index 0

#### Performance Characteristics
- **Access Time**: O(1) - constant time
- **Search Time**: O(n) - linear search
- **Insertion/Deletion**: O(n) - may require shifting elements
- **Memory Usage**: Predictable, no overhead per element

### Multi-Language Array Implementations

#### Python Lists (Dynamic Arrays)
```python
# Creating arrays with different methods
numbers = [1, 2, 3, 4, 5]                    # List literal
names = ["Alice", "Bob", "Charlie"]           # String array
empty_array = []                              # Empty array
zeros = [0] * 10                             # Initialize with zeros

# Multi-dimensional arrays
matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

# Array operations
print(len(numbers))          # Length: 5
print(numbers[0])           # First element: 1
print(numbers[-1])          # Last element: 5

# Slicing operations
print(numbers[1:4])         # [2, 3, 4]
print(numbers[::2])         # [1, 3, 5] (every other element)
print(numbers[::-1])        # [5, 4, 3, 2, 1] (reversed)

# Modifying elements
numbers[1] = 10
print(numbers)              # [1, 10, 3, 4, 5]

# Adding elements
numbers.append(6)           # [1, 10, 3, 4, 5, 6]
numbers.insert(2, 99)       # [1, 10, 99, 3, 4, 5, 6]
numbers.extend([7, 8])      # [1, 10, 99, 3, 4, 5, 6, 7, 8]

# Removing elements
numbers.remove(99)          # Remove first occurrence of 99
last_element = numbers.pop()  # Remove and return last element
del numbers[1]              # Remove element at index 1

# Searching and sorting
print(3 in numbers)         # Check if element exists: True
print(numbers.index(3))     # Find index of element: 2
numbers.sort()              # Sort in place
numbers.reverse()           # Reverse in place

# List comprehensions (powerful array operations)
squares = [x**2 for x in range(10)]                    # [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
even_squares = [x**2 for x in range(10) if x % 2 == 0] # [0, 4, 16, 36, 64]
matrix_sum = [sum(row) for row in matrix]              # [6, 15, 24]
```

#### Java Arrays (Fixed-Size)
```java
public class ArrayExamples {
    public static void main(String[] args) {
        // Declaration and initialization
        int[] numbers = {1, 2, 3, 4, 5};
        String[] names = {"Alice", "Bob", "Charlie"};
        
        // Alternative declaration
        int[] emptyArray = new int[10];  // All elements initialized to 0
        double[] decimals = new double[5]; // All elements initialized to 0.0
        
        // Multi-dimensional arrays
        int[][] matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        
        // Array operations
        System.out.println("Length: " + numbers.length);  // 5
        System.out.println("First element: " + numbers[0]); // 1
        System.out.println("Last element: " + numbers[numbers.length - 1]); // 5
        
        // Modifying elements
        numbers[1] = 10;
        
        // Iterating through arrays
        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }
        System.out.println();
        
        // Enhanced for loop (foreach)
        for (int number : numbers) {
            System.out.print(number + " ");
        }
        System.out.println();
        
        // Array utilities
        java.util.Arrays.sort(numbers);  // Sort array
        int index = java.util.Arrays.binarySearch(numbers, 3); // Binary search
        System.out.println("Index of 3: " + index);
        
        // Copying arrays
        int[] copy = java.util.Arrays.copyOf(numbers, numbers.length);
        int[] range = java.util.Arrays.copyOfRange(numbers, 1, 4);
        
        // Comparing arrays
        boolean equal = java.util.Arrays.equals(numbers, copy);
        System.out.println("Arrays equal: " + equal);
        
        // Filling arrays
        java.util.Arrays.fill(emptyArray, 42); // Fill with 42
        
        // Converting to string
        System.out.println("Array as string: " + java.util.Arrays.toString(numbers));
    }
}
```

#### JavaScript Arrays (Dynamic and Flexible)
```javascript
// Creating arrays
let numbers = [1, 2, 3, 4, 5];
let names = ["Alice", "Bob", "Charlie"];
let mixed = [1, "hello", true, null, undefined]; // Mixed types allowed

// Array constructor
let emptyArray = new Array();
let sizedArray = new Array(10); // Creates array with 10 undefined elements
let filledArray = new Array(3).fill(0); // [0, 0, 0]

// Multi-dimensional arrays
let matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];

// Array properties and methods
console.log("Length:", numbers.length); // 5
console.log("First element:", numbers[0]); // 1
console.log("Last element:", numbers[numbers.length - 1]); // 5

// Modifying arrays
numbers[1] = 10; // [1, 10, 3, 4, 5]
numbers.push(6); // Add to end: [1, 10, 3, 4, 5, 6]
numbers.unshift(0); // Add to beginning: [0, 1, 10, 3, 4, 5, 6]
numbers.pop(); // Remove from end: [0, 1, 10, 3, 4, 5]
numbers.shift(); // Remove from beginning: [1, 10, 3, 4, 5]

// Splicing (add/remove elements)
numbers.splice(2, 1, 99, 100); // Remove 1 element at index 2, add 99, 100
console.log(numbers); // [1, 10, 99, 100, 4, 5]

// Searching and sorting
console.log("Index of 4:", numbers.indexOf(4)); // 4
console.log("Includes 10:", numbers.includes(10)); // true

numbers.sort((a, b) => a - b); // Sort numerically
numbers.reverse(); // Reverse order

// Iteration methods
numbers.forEach(num => console.log("Number:", num));

let doubled = numbers.map(num => num * 2); // [10, 8, 6, 4, 2]
let evenNumbers = numbers.filter(num => num % 2 === 0); // [10, 8, 6, 4, 2]
let sum = numbers.reduce((acc, num) => acc + num, 0); // Sum all elements

// Array manipulation
let sliced = numbers.slice(1, 4); // Extract portion
let concatenated = numbers.concat([6, 7, 8]); // Join arrays
let joined = names.join(", "); // "Alice, Bob, Charlie"

// Advanced methods
let found = numbers.find(num => num > 5); // First element > 5
let foundIndex = numbers.findIndex(num => num > 5); // Index of first element > 5
let someEven = numbers.some(num => num % 2 === 0); // At least one even
let allEven = numbers.every(num => num % 2 === 0); // All even

console.log("Array operations result:", {
    doubled,
    evenNumbers,
    sum,
    sliced,
    found,
    foundIndex,
    someEven,
    allEven
});
```

#### C Arrays (Low-Level Memory Management)
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Fixed-size arrays
    int numbers[5] = {1, 2, 3, 4, 5};
    char name[20] = "Hello World";
    
    // Multi-dimensional arrays
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    // Array operations
    printf("Array length: %lu\n", sizeof(numbers) / sizeof(numbers[0]));
    printf("First element: %d\n", numbers[0]);
    printf("Last element: %d\n", numbers[4]);
    
    // Modifying elements
    numbers[1] = 10;
    
    // Iterating with traditional loop
    printf("Array elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // Iterating with pointers
    printf("Using pointers: ");
    for (int *ptr = numbers; ptr < numbers + 5; ptr++) {
        printf("%d ", *ptr);
    }
    printf("\n");
    
    // String operations (character arrays)
    printf("String length: %lu\n", strlen(name));
    printf("String: %s\n", name);
    
    // String manipulation
    strcpy(name, "New String");  // Copy string
    printf("Modified string: %s\n", name);
    
    strcat(name, " Appended");  // Concatenate
    printf("Appended string: %s\n", name);
    
    // Dynamic arrays (using pointers)
    int *dynamic_array = (int *)malloc(5 * sizeof(int));
    if (dynamic_array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    // Initialize dynamic array
    for (int i = 0; i < 5; i++) {
        dynamic_array[i] = i * 10;
    }
    
    printf("Dynamic array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dynamic_array[i]);
    }
    printf("\n");
    
    // Resize dynamic array
    dynamic_array = (int *)realloc(dynamic_array, 10 * sizeof(int));
    for (int i = 5; i < 10; i++) {
        dynamic_array[i] = i * 10;
    }
    
    printf("Resized array: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", dynamic_array[i]);
    }
    printf("\n");
    
    // Free memory
    free(dynamic_array);
    
    return 0;
}
```

### Advanced Array Operations and Algorithms

#### Array Traversal Patterns
```python
def traverse_array(arr):
    """Demonstrate different traversal patterns."""
    print("Forward traversal:")
    for i in range(len(arr)):
        print(f"Index {i}: {arr[i]}")
    
    print("\nBackward traversal:")
    for i in range(len(arr) - 1, -1, -1):
        print(f"Index {i}: {arr[i]}")
    
    print("\nEvery other element:")
    for i in range(0, len(arr), 2):
        print(f"Index {i}: {arr[i]}")

def find_max_min(arr):
    """Find maximum and minimum values with single pass."""
    if not arr:
        return None, None
    
    max_val = min_val = arr[0]
    
    for num in arr[1:]:
        if num > max_val:
            max_val = num
        if num < min_val:
            min_val = num
    
    return max_val, min_val

def rotate_array(arr, k):
    """Rotate array k positions to the right."""
    if not arr:
        return arr
    
    k = k % len(arr)  # Handle k > len(arr)
    return arr[-k:] + arr[:-k]

def remove_duplicates(arr):
    """Remove duplicates while preserving order."""
    seen = set()
    result = []
    
    for item in arr:
        if item not in seen:
            seen.add(item)
            result.append(item)
    
    return result

# Usage examples
numbers = [3, 1, 4, 1, 5, 9, 2, 6]
traverse_array(numbers)

max_val, min_val = find_max_min(numbers)
print(f"Max: {max_val}, Min: {min_val}")

rotated = rotate_array(numbers, 3)
print(f"Original: {numbers}")
print(f"Rotated by 3: {rotated}")

with_duplicates = [1, 2, 2, 3, 4, 4, 5]
without_duplicates = remove_duplicates(with_duplicates)
print(f"With duplicates: {with_duplicates}")
print(f"Without duplicates: {without_duplicates}")
```

#### Array Searching Algorithms
```python
def linear_search(arr, target):
    """Linear search - O(n) time complexity."""
    for i, element in enumerate(arr):
        if element == target:
            return i
    return -1

def binary_search(arr, target):
    """Binary search - O(log n) time complexity. Array must be sorted."""
    left, right = 0, len(arr) - 1
    
    while left <= right:
        mid = (left + right) // 2
        
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return -1

def interpolation_search(arr, target):
    """Interpolation search - O(log log n) average case for uniformly distributed data."""
    if not arr:
        return -1
    
    low, high = 0, len(arr) - 1
    
    while low <= high and arr[low] <= target <= arr[high]:
        if low == high:
            if arr[low] == target:
                return low
            return -1
        
        # Interpolation formula
        pos = low + ((target - arr[low]) * (high - low)) // (arr[high] - arr[low])
        
        if arr[pos] == target:
            return pos
        elif arr[pos] < target:
            low = pos + 1
        else:
            high = pos - 1
    
    return -1

# Usage
sorted_array = [1, 3, 5, 7, 9, 11, 13, 15]
target = 7

linear_result = linear_search(sorted_array, target)
binary_result = binary_search(sorted_array, target)
interp_result = interpolation_search(sorted_array, target)

print(f"Linear search for {target}: index {linear_result}")
print(f"Binary search for {target}: index {binary_result}")
print(f"Interpolation search for {target}: index {interp_result}")
```

#### Array Sorting Algorithms
```python
def bubble_sort(arr):
    """Bubble sort - O(n²) time complexity."""
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break  # Array already sorted
    return arr

def selection_sort(arr):
    """Selection sort - O(n²) time complexity."""
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def insertion_sort(arr):
    """Insertion sort - O(n²) worst case, O(n) best case."""
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        
        arr[j + 1] = key
    return arr

def merge_sort(arr):
    """Merge sort - O(n log n) time complexity."""
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    return merge(left, right)

def merge(left, right):
    """Helper function for merge sort."""
    result = []
    i = j = 0
    
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    result.extend(left[i:])
    result.extend(right[j:])
    return result

# Usage
unsorted = [64, 34, 25, 12, 22, 11, 90, 5, 77, 30]

print("Original:", unsorted)

bubble_sorted = bubble_sort(unsorted.copy())
print("Bubble sort:", bubble_sorted)

selection_sorted = selection_sort(unsorted.copy())
print("Selection sort:", selection_sorted)

insertion_sorted = insertion_sort(unsorted.copy())
print("Insertion sort:", insertion_sorted)

merge_sorted = merge_sort(unsorted.copy())
print("Merge sort:", merge_sorted)
```

### Array Memory Management and Optimization

#### Memory Layout Understanding
```python
import sys
import array

# Different array types and memory usage
numbers_list = [1, 2, 3, 4, 5]
numbers_array = array.array('i', [1, 2, 3, 4, 5])  # 'i' for signed int

print(f"List size: {sys.getsizeof(numbers_list)} bytes")
print(f"Array size: {sys.getsizeof(numbers_array)} bytes")

# Memory efficiency comparison
large_list = list(range(1000))
large_array = array.array('i', range(1000))

print(f"Large list: {sys.getsizeof(large_list)} bytes")
print(f"Large array: {sys.getsizeof(large_array)} bytes")
```

#### Array Resizing Strategies
```python
class DynamicArray:
    """Simple dynamic array implementation."""
    
    def __init__(self, capacity=10):
        self.capacity = capacity
        self.size = 0
        self.array = [None] * capacity
    
    def resize(self, new_capacity):
        """Resize the array to new capacity."""
        new_array = [None] * new_capacity
        
        # Copy existing elements
        for i in range(self.size):
            new_array[i] = self.array[i]
        
        self.array = new_array
        self.capacity = new_capacity
    
    def append(self, element):
        """Add element to end of array."""
        if self.size == self.capacity:
            # Double the capacity when full
            self.resize(self.capacity * 2)
        
        self.array[self.size] = element
        self.size += 1
    
    def get(self, index):
        """Get element at index."""
        if index < 0 or index >= self.size:
            raise IndexError("Index out of bounds")
        return self.array[index]
    
    def __len__(self):
        return self.size
    
    def __str__(self):
        return str(self.array[:self.size])

# Usage
dyn_array = DynamicArray(2)
print("Initial:", dyn_array)

for i in range(10):
    dyn_array.append(i)
    print(f"After adding {i}: {dyn_array} (capacity: {dyn_array.capacity})")
```

### Common Array Problems and Solutions

#### 1. Array Bounds Checking
```python
def safe_array_access(arr, index):
    """Safe array access with bounds checking."""
    try:
        return arr[index]
    except IndexError:
        print(f"Index {index} is out of bounds for array of length {len(arr)}")
        return None

# Usage
numbers = [1, 2, 3, 4, 5]
print(safe_array_access(numbers, 2))    # 3
print(safe_array_access(numbers, 10))   # None (with error message)
```

#### 2. Array Rotation
```python
def rotate_left(arr, k):
    """Rotate array k positions to the left."""
    if not arr:
        return arr
    
    k = k % len(arr)
    return arr[k:] + arr[:k]

def rotate_right(arr, k):
    """Rotate array k positions to the right."""
    if not arr:
        return arr
    
    k = k % len(arr)
    return arr[-k:] + arr[:-k]

# Usage
original = [1, 2, 3, 4, 5, 6]
print("Original:", original)
print("Rotate left by 2:", rotate_left(original, 2))
print("Rotate right by 2:", rotate_right(original, 2))
```

#### 3. Array Chunking
```python
def chunk_array(arr, chunk_size):
    """Split array into chunks of specified size."""
    return [arr[i:i + chunk_size] for i in range(0, len(arr), chunk_size)]

def flatten_array(nested_arr):
    """Flatten a nested array."""
    flattened = []
    for sublist in nested_arr:
        if isinstance(sublist, list):
            flattened.extend(flatten_array(sublist))
        else:
            flattened.append(sublist)
    return flattened

# Usage
numbers = list(range(1, 13))  # [1, 2, 3, ..., 12]
chunks = chunk_array(numbers, 4)
print("Chunks:", chunks)

nested = [[1, 2], [3, [4, 5]], 6]
flattened = flatten_array(nested)
print("Flattened:", flattened)
```

### Array Performance Analysis

#### Time Complexity Summary
| Operation | Python List | Java Array | C Array | Notes |
|-----------|-------------|------------|---------|-------|
| Access by index | O(1) | O(1) | O(1) | Direct memory access |
| Search (unsorted) | O(n) | O(n) | O(n) | Linear search |
| Search (sorted) | O(log n) | O(log n) | O(log n) | Binary search |
| Insert at end | O(1) amortized | O(1) | O(1) | May require resize |
| Insert at beginning | O(n) | O(n) | O(n) | Shift elements |
| Delete at end | O(1) | O(1) | O(1) | Simple removal |
| Delete at beginning | O(n) | O(n) | O(n) | Shift elements |

#### Space Complexity
- **Fixed Arrays**: O(n) - exactly what's needed
- **Dynamic Arrays**: O(n) amortized - extra space for growth
- **Sparse Arrays**: O(k) where k is number of non-zero elements
- **Memory Overhead**: Varies by language and implementation

### Real-World Array Applications

#### 1. Image Processing
```python
def apply_filter(image_matrix, filter_matrix):
    """Apply a filter to an image represented as a matrix."""
    # Simplified convolution operation
    result = []
    for i in range(len(image_matrix)):
        row = []
        for j in range(len(image_matrix[0])):
            # Apply filter to pixel (i,j)
            pixel_sum = 0
            for fi in range(len(filter_matrix)):
                for fj in range(len(filter_matrix[0])):
                    if 0 <= i + fi - 1 < len(image_matrix) and 0 <= j + fj - 1 < len(image_matrix[0]):
                        pixel_sum += image_matrix[i + fi - 1][j + fj - 1] * filter_matrix[fi][fj]
            row.append(pixel_sum)
        result.append(row)
    return result
```

#### 2. Database Records
```python
class SimpleDatabase:
    """Simple in-memory database using arrays."""
    
    def __init__(self):
        self.records = []
        self.next_id = 1
    
    def insert(self, record):
        """Insert a new record."""
        record['id'] = self.next_id
        self.next_id += 1
        self.records.append(record)
        return record['id']
    
    def find_by_id(self, record_id):
        """Find record by ID."""
        for record in self.records:
            if record.get('id') == record_id:
                return record
        return None
    
    def find_all(self, condition_func=None):
        """Find all records, optionally filtered by condition."""
        if condition_func is None:
            return self.records[:]
        return [record for record in self.records if condition_func(record)]
    
    def update(self, record_id, updates):
        """Update a record."""
        record = self.find_by_id(record_id)
        if record:
            record.update(updates)
            return True
        return False
    
    def delete(self, record_id):
        """Delete a record."""
        for i, record in enumerate(self.records):
            if record.get('id') == record_id:
                del self.records[i]
                return True
        return False

# Usage
db = SimpleDatabase()

# Insert records
user1_id = db.insert({"name": "Alice", "age": 25, "city": "New York"})
user2_id = db.insert({"name": "Bob", "age": 30, "city": "San Francisco"})
user3_id = db.insert({"name": "Charlie", "age": 35, "city": "New York"})

# Query records
alice = db.find_by_id(user1_id)
print("Alice's record:", alice)

# Find all users from New York
ny_users = db.find_all(lambda r: r.get('city') == 'New York')
print("New York users:", ny_users)

# Update a record
db.update(user2_id, {"age": 31, "city": "Los Angeles"})

# Delete a record
db.delete(user3_id)

print("All remaining records:", db.records)
```

This comprehensive coverage of arrays demonstrates their fundamental role in programming and their applications across different domains. Arrays serve as the building blocks for more complex data structures and are essential for efficient data manipulation and storage.

## Linked Lists - Dynamic Node-Based Structures

Linked lists are dynamic data structures where elements (nodes) are connected via pointers/references. Unlike arrays, linked lists can grow and shrink dynamically without requiring contiguous memory allocation.

### Node Structure and Memory Layout

#### Basic Node Implementation
```python
class Node:
    """Basic node structure for linked lists."""
    def __init__(self, data):
        self.data = data      # The actual data
        self.next = None      # Reference to next node
    
    def __repr__(self):
        return f"Node({self.data})"
```

#### Memory Characteristics
- **Dynamic Allocation**: Nodes allocated individually in heap memory
- **No Contiguous Requirement**: Nodes can be scattered in memory
- **Pointer Overhead**: Each node stores a reference/pointer
- **Variable Size**: Can grow/shrink without copying elements

### Singly Linked List - One-Way Navigation

#### Complete Implementation
```python
class SinglyLinkedList:
    """Singly linked list implementation."""
    
    def __init__(self):
        self.head = None
        self.size = 0
    
    def is_empty(self):
        """Check if list is empty."""
        return self.head is None
    
    def append(self, data):
        """Add element to end of list."""
        new_node = Node(data)
        if self.is_empty():
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        self.size += 1
    
    def prepend(self, data):
        """Add element to beginning of list."""
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node
        self.size += 1
    
    def insert_at(self, index, data):
        """Insert element at specific index."""
        if index < 0 or index > self.size:
            raise IndexError("Index out of bounds")
        
        if index == 0:
            self.prepend(data)
            return
        
        new_node = Node(data)
        current = self.head
        for _ in range(index - 1):
            current = current.next
        
        new_node.next = current.next
        current.next = new_node
        self.size += 1
    
    def remove_first(self):
        """Remove and return first element."""
        if self.is_empty():
            raise IndexError("List is empty")
        
        removed_data = self.head.data
        self.head = self.head.next
        self.size -= 1
        return removed_data
    
    def remove_last(self):
        """Remove and return last element."""
        if self.is_empty():
            raise IndexError("List is empty")
        
        if self.head.next is None:
            removed_data = self.head.data
            self.head = None
            self.size -= 1
            return removed_data
        
        current = self.head
        while current.next.next:
            current = current.next
        
        removed_data = current.next.data
        current.next = None
        self.size -= 1
        return removed_data
    
    def remove_at(self, index):
        """Remove element at specific index."""
        if index < 0 or index >= self.size:
            raise IndexError("Index out of bounds")
        
        if index == 0:
            return self.remove_first()
        
        current = self.head
        for _ in range(index - 1):
            current = current.next
        
        removed_data = current.next.data
        current.next = current.next.next
        self.size -= 1
        return removed_data
    
    def get(self, index):
        """Get element at index."""
        if index < 0 or index >= self.size:
            raise IndexError("Index out of bounds")
        
        current = self.head
        for _ in range(index):
            current = current.next
        return current.data
    
    def index_of(self, data):
        """Find index of element."""
        current = self.head
        index = 0
        
        while current:
            if current.data == data:
                return index
            current = current.next
            index += 1
        
        return -1
    
    def contains(self, data):
        """Check if element exists."""
        return self.index_of(data) != -1
    
    def reverse(self):
        """Reverse the linked list in place."""
        prev = None
        current = self.head
        
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        
        self.head = prev
    
    def display(self):
        """Display the linked list."""
        if self.is_empty():
            print("List is empty")
            return
        
        current = self.head
        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("None")
    
    def __len__(self):
        """Return size of list."""
        return self.size
    
    def __str__(self):
        """String representation of list."""
        if self.is_empty():
            return "[]"
        
        elements = []
        current = self.head
        while current:
            elements.append(str(current.data))
            current = current.next
        
        return "[" + " -> ".join(elements) + "]"

# Usage example
sll = SinglyLinkedList()
sll.append(10)
sll.append(20)
sll.append(30)
sll.prepend(5)

print("List:", sll)           # [5 -> 10 -> 20 -> 30]
print("Length:", len(sll))    # 4
print("Get index 2:", sll.get(2))  # 20
print("Contains 15:", sll.contains(15))  # False

sll.insert_at(2, 15)
print("After insert:", sll)   # [5 -> 10 -> 15 -> 20 -> 30]

sll.remove_at(1)
print("After remove:", sll)   # [5 -> 15 -> 20 -> 30]

sll.reverse()
print("After reverse:", sll)  # [30 -> 20 -> 15 -> 5]
```

### Doubly Linked List - Bidirectional Navigation

#### Enhanced Node Structure
```python
class DoublyNode:
    """Node for doubly linked list."""
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None
    
    def __repr__(self):
        return f"DoublyNode({self.data})"
```

#### Complete Doubly Linked List Implementation
```python
class DoublyLinkedList:
    """Doubly linked list with bidirectional traversal."""
    
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0
    
    def is_empty(self):
        return self.head is None
    
    def append(self, data):
        """Add element to end."""
        new_node = DoublyNode(data)
        
        if self.is_empty():
            self.head = self.tail = new_node
        else:
            new_node.prev = self.tail
            self.tail.next = new_node
            self.tail = new_node
        
        self.size += 1
    
    def prepend(self, data):
        """Add element to beginning."""
        new_node = DoublyNode(data)
        
        if self.is_empty():
            self.head = self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node
        
        self.size += 1
    
    def insert_at(self, index, data):
        """Insert at specific index."""
        if index < 0 or index > self.size:
            raise IndexError("Index out of bounds")
        
        if index == 0:
            self.prepend(data)
        elif index == self.size:
            self.append(data)
        else:
            new_node = DoublyNode(data)
            current = self.head
            
            for _ in range(index):
                current = current.next
            
            new_node.prev = current.prev
            new_node.next = current
            current.prev.next = new_node
            current.prev = new_node
            
            self.size += 1
    
    def remove_first(self):
        """Remove and return first element."""
        if self.is_empty():
            raise IndexError("List is empty")
        
        removed_data = self.head.data
        
        if self.head == self.tail:
            self.head = self.tail = None
        else:
            self.head = self.head.next
            self.head.prev = None
        
        self.size -= 1
        return removed_data
    
    def remove_last(self):
        """Remove and return last element."""
        if self.is_empty():
            raise IndexError("List is empty")
        
        removed_data = self.tail.data
        
        if self.head == self.tail:
            self.head = self.tail = None
        else:
            self.tail = self.tail.prev
            self.tail.next = None
        
        self.size -= 1
        return removed_data
    
    def remove_at(self, index):
        """Remove element at index."""
        if index < 0 or index >= self.size:
            raise IndexError("Index out of bounds")
        
        if index == 0:
            return self.remove_first()
        elif index == self.size - 1:
            return self.remove_last()
        else:
            current = self.head
            for _ in range(index):
                current = current.next
            
            current.prev.next = current.next
            current.next.prev = current.prev
            
            self.size -= 1
            return current.data
    
    def get(self, index):
        """Get element at index (optimized for doubly linked list)."""
        if index < 0 or index >= self.size:
            raise IndexError("Index out of bounds")
        
        # Start from closer end
        if index < self.size // 2:
            current = self.head
            for _ in range(index):
                current = current.next
        else:
            current = self.tail
            for _ in range(self.size - 1 - index):
                current = current.prev
        
        return current.data
    
    def reverse(self):
        """Reverse the list in place."""
        current = self.head
        temp = None
        
        # Swap next and prev for all nodes
        while current:
            temp = current.prev
            current.prev = current.next
            current.next = temp
            current = current.prev  # Move to next (which is now prev)
        
        # Swap head and tail
        temp = self.head
        self.head = self.tail
        self.tail = temp
    
    def display_forward(self):
        """Display list from head to tail."""
        current = self.head
        while current:
            print(current.data, end=" <-> ")
            current = current.next
        print("None")
    
    def display_backward(self):
        """Display list from tail to head."""
        current = self.tail
        while current:
            print(current.data, end=" <-> ")
            current = current.prev
        print("None")
    
    def __len__(self):
        return self.size

# Usage
dll = DoublyLinkedList()
for i in range(1, 6):
    dll.append(i)

print("Forward:", end=" ")
dll.display_forward()    # 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> None

print("Backward:", end=" ")
dll.display_backward()   # 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> None

dll.reverse()
print("After reverse - Forward:", end=" ")
dll.display_forward()    # 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> None
```

### Circular Linked List - Ring Structure

#### Circular Singly Linked List
```python
class CircularLinkedList:
    """Circular singly linked list."""
    
    def __init__(self):
        self.head = None
        self.size = 0
    
    def is_empty(self):
        return self.head is None
    
    def append(self, data):
        """Add element to end."""
        new_node = Node(data)
        
        if self.is_empty():
            self.head = new_node
            new_node.next = self.head  # Point to itself
        else:
            current = self.head
            while current.next != self.head:
                current = current.next
            
            current.next = new_node
            new_node.next = self.head
        
        self.size += 1
    
    def prepend(self, data):
        """Add element to beginning."""
        new_node = Node(data)
        
        if self.is_empty():
            self.head = new_node
            new_node.next = self.head
        else:
            new_node.next = self.head
            # Find last node and update its next
            current = self.head
            while current.next != self.head:
                current = current.next
            current.next = new_node
            self.head = new_node
        
        self.size += 1
    
    def display(self):
        """Display the circular list."""
        if self.is_empty():
            print("List is empty")
            return
        
        current = self.head
        count = 0
        
        print("Circular List:", end=" ")
        while count < self.size:
            print(current.data, end=" -> ")
            current = current.next
            count += 1
        print("(back to head)")
    
    def __len__(self):
        return self.size

# Usage
cll = CircularLinkedList()
for i in range(1, 4):
    cll.append(i)

cll.display()  # Circular List: 1 -> 2 -> 3 -> (back to head)
```

### Linked List Operations and Algorithms

#### Finding Middle Element
```python
def find_middle_singly(head):
    """Find middle element using slow-fast pointer technique."""
    if not head:
        return None
    
    slow = fast = head
    
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    
    return slow.data

def find_middle_doubly(dll):
    """Find middle using doubly linked list properties."""
    if dll.is_empty():
        return None
    
    left = dll.head
    right = dll.tail
    
    while left != right and left.next != right:
        left = left.next
        right = right.prev
    
    return left.data
```

#### Detecting Cycles
```python
def has_cycle(head):
    """Detect cycle in linked list using Floyd's algorithm."""
    if not head:
        return False
    
    slow = fast = head
    
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        
        if slow == fast:
            return True
    
    return False

def find_cycle_start(head):
    """Find start of cycle if one exists."""
    if not head:
        return None
    
    # First detect cycle
    slow = fast = head
    has_cycle_flag = False
    
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        
        if slow == fast:
            has_cycle_flag = True
            break
    
    if not has_cycle_flag:
        return None
    
    # Find cycle start
    slow = head
    while slow != fast:
        slow = slow.next
        fast = fast.next
    
    return slow.data
```

#### Merging Sorted Lists
```python
def merge_sorted_lists(list1, list2):
    """Merge two sorted singly linked lists."""
    if not list1:
        return list2
    if not list2:
        return list1
    
    # Determine head of merged list
    if list1.data <= list2.data:
        head = list1
        list1 = list1.next
    else:
        head = list2
        list2 = list2.next
    
    current = head
    
    # Merge remaining elements
    while list1 and list2:
        if list1.data <= list2.data:
            current.next = list1
            list1 = list1.next
        else:
            current.next = list2
            list2 = list2.next
        current = current.next
    
    # Attach remaining elements
    if list1:
        current.next = list1
    if list2:
        current.next = list2
    
    return head
```

#### Linked List Performance Analysis

| Operation | Singly Linked List | Doubly Linked List | Time Complexity |
|-----------|-------------------|-------------------|-----------------|
| Access by index | O(n) | O(min(k, n-k)) | Linear |
| Insert at beginning | O(1) | O(1) | Constant |
| Insert at end | O(n) | O(1) | Varies |
| Insert at middle | O(n) | O(n) | Linear |
| Delete at beginning | O(1) | O(1) | Constant |
| Delete at end | O(n) | O(1) | Varies |
| Delete at middle | O(n) | O(n) | Linear |
| Search | O(n) | O(n) | Linear |

### Real-World Applications of Linked Lists

#### 1. Undo Functionality
```python
class TextEditor:
    """Text editor with undo functionality using linked list."""
    
    def __init__(self):
        self.text = ""
        self.history = SinglyLinkedList()  # Store previous states
    
    def type_text(self, new_text):
        # Save current state before change
        self.history.append(self.text)
        self.text += new_text
    
    def undo(self):
        """Undo last operation."""
        if not self.history.is_empty():
            self.text = self.history.remove_last()
            return True
        return False
    
    def get_text(self):
        return self.text

# Usage
editor = TextEditor()
editor.type_text("Hello ")
editor.type_text("World!")
print("Current text:", editor.get_text())  # "Hello World!"

editor.undo()
print("After undo:", editor.get_text())    # "Hello "

editor.undo()
print("After second undo:", editor.get_text())  # ""
```

#### 2. Music Playlist
```python
class Song:
    def __init__(self, title, artist, duration):
        self.title = title
        self.artist = artist
        self.duration = duration
    
    def __str__(self):
        return f"{self.title} by {self.artist} ({self.duration})"

class MusicPlaylist:
    """Music playlist using doubly linked list for navigation."""
    
    def __init__(self):
        self.songs = DoublyLinkedList()
        self.current = None
    
    def add_song(self, song):
        """Add song to playlist."""
        self.songs.append(song)
        if self.current is None:
            self.current = self.songs.head
    
    def play_next(self):
        """Play next song."""
        if self.current and self.current.next:
            self.current = self.current.next
            return self.current.data
        return None
    
    def play_previous(self):
        """Play previous song."""
        if self.current and self.current.prev:
            self.current = self.current.prev
            return self.current.data
        return None
    
    def get_current_song(self):
        """Get currently playing song."""
        return self.current.data if self.current else None
    
    def shuffle(self):
        """Simple shuffle implementation."""
        # Convert to list, shuffle, rebuild
        song_list = []
        current = self.songs.head
        while current:
            song_list.append(current.data)
            current = current.next
        
        import random
        random.shuffle(song_list)
        
        # Rebuild playlist
        self.songs = DoublyLinkedList()
        for song in song_list:
            self.songs.append(song)
        
        self.current = self.songs.head

# Usage
playlist = MusicPlaylist()
playlist.add_song(Song("Bohemian Rhapsody", "Queen", "5:55"))
playlist.add_song(Song("Stairway to Heaven", "Led Zeppelin", "8:02"))
playlist.add_song(Song("Hotel California", "Eagles", "6:30"))

print("Current song:", playlist.get_current_song())
print("Next song:", playlist.play_next())
print("Next song:", playlist.play_next())
print("Previous song:", playlist.play_previous())
```

#### 3. Browser History
```python
class BrowserHistory:
    """Browser history using doubly linked list."""
    
    def __init__(self):
        self.history = DoublyLinkedList()
        self.current = None
    
    def visit_page(self, url):
        """Visit a new page."""
        # Remove forward history when visiting new page
        if self.current:
            # In a real implementation, we'd remove all nodes after current
            pass
        
        self.history.append(url)
        self.current = self.history.tail  # Move to last added
    
    def go_back(self):
        """Go back to previous page."""
        if self.current and self.current.prev:
            self.current = self.current.prev
            return self.current.data
        return None
    
    def go_forward(self):
        """Go forward to next page."""
        if self.current and self.current.next:
            self.current = self.current.next
            return self.current.data
        return None
    
    def get_current_page(self):
        """Get current page URL."""
        return self.current.data if self.current else None
    
    def display_history(self):
        """Display browsing history."""
        print("Browser History:")
        current = self.history.head
        while current:
            marker = " <-- CURRENT" if current == self.current else ""
            print(f"  {current.data}{marker}")
            current = current.next

# Usage
browser = BrowserHistory()
browser.visit_page("https://google.com")
browser.visit_page("https://github.com")
browser.visit_page("https://stackoverflow.com")

print("Current page:", browser.get_current_page())
browser.display_history()

browser.go_back()
print("After going back:", browser.get_current_page())

browser.go_back()
print("After going back again:", browser.get_current_page())

browser.visit_page("https://reddit.com")  # This should clear forward history
browser.display_history()
```

Linked lists provide flexibility and dynamic sizing that arrays cannot match. They excel in scenarios requiring frequent insertions and deletions, and their implementations demonstrate fundamental computer science concepts like pointers, memory management, and algorithmic efficiency.

## Stacks - LIFO (Last-In-First-Out) Data Structure

Stacks are linear data structures that follow the Last-In-First-Out principle, where the last element added is the first one to be removed. They are fundamental to computer science and have numerous applications in programming.

### Stack Operations and Interface

#### Core Operations
- **push(item)**: Add item to top of stack
- **pop()**: Remove and return item from top
- **peek()/top()**: Return top item without removing it
- **is_empty()**: Check if stack contains no elements
- **size()**: Return number of elements in stack

#### Advanced Operations
- **clear()**: Remove all elements
- **contains(item)**: Check if item exists in stack
- **to_array()**: Convert stack to array/list

### Stack Implementations

#### Array-Based Stack (Python)
```python
class ArrayStack:
    """Stack implementation using dynamic array (list)."""
    
    def __init__(self, capacity=None):
        self.items = []
        self.capacity = capacity
    
    def push(self, item):
        """Add item to top of stack."""
        if self.capacity and len(self.items) >= self.capacity:
            raise OverflowError("Stack is full")
        self.items.append(item)
    
    def pop(self):
        """Remove and return top item."""
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.items.pop()
    
    def peek(self):
        """Return top item without removing it."""
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.items[-1]
    
    def is_empty(self):
        """Check if stack is empty."""
        return len(self.items) == 0
    
    def size(self):
        """Return number of items in stack."""
        return len(self.items)
    
    def clear(self):
        """Remove all items from stack."""
        self.items.clear()
    
    def __str__(self):
        """String representation of stack."""
        return f"Stack({self.items})"

# Usage
stack = ArrayStack()
stack.push(10)
stack.push(20)
stack.push(30)
print("Stack:", stack)        # Stack([10, 20, 30])
print("Size:", stack.size())  # 3
print("Top:", stack.peek())   # 30
print("Pop:", stack.pop())    # 30
print("Size after pop:", stack.size())  # 2
```

#### Linked List-Based Stack
```python
class LinkedStack:
    """Stack implementation using linked list."""
    
    class Node:
        def __init__(self, data):
            self.data = data
            self.next = None
    
    def __init__(self):
        self.top = None
        self._size = 0
    
    def push(self, item):
        """Add item to top of stack."""
        new_node = self.Node(item)
        new_node.next = self.top
        self.top = new_node
        self._size += 1
    
    def pop(self):
        """Remove and return top item."""
        if self.is_empty():
            raise IndexError("Stack is empty")
        
        popped_item = self.top.data
        self.top = self.top.next
        self._size -= 1
        return popped_item
    
    def peek(self):
        """Return top item without removing it."""
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.top.data
    
    def is_empty(self):
        """Check if stack is empty."""
        return self.top is None
    
    def size(self):
        """Return number of items in stack."""
        return self._size
    
    def clear(self):
        """Remove all items from stack."""
        self.top = None
        self._size = 0
    
    def __str__(self):
        """String representation of stack."""
        items = []
        current = self.top
        while current:
            items.append(str(current.data))
            current = current.next
        return f"Stack([{', '.join(reversed(items))}])"

# Usage
stack = LinkedStack()
for i in range(1, 4):
    stack.push(i)

print("Linked Stack:", stack)  # Stack([1, 2, 3])
print("Size:", stack.size())   # 3
print("Pop:", stack.pop())     # 3
print("After pop:", stack)     # Stack([1, 2])
```

### Stack Applications and Algorithms

#### 1. Expression Evaluation and Parsing

##### Infix to Postfix Conversion
```python
def infix_to_postfix(expression):
    """Convert infix expression to postfix using stack."""
    precedence = {'+': 1, '-': 1, '*': 2, '/': 2, '^': 3}
    stack = ArrayStack()
    postfix = []
    
    for char in expression:
        if char.isalnum():  # Operand
            postfix.append(char)
        elif char == '(':
            stack.push(char)
        elif char == ')':
            while not stack.is_empty() and stack.peek() != '(':
                postfix.append(stack.pop())
            if not stack.is_empty():
                stack.pop()  # Remove '('
        else:  # Operator
            while (not stack.is_empty() and
                   stack.peek() != '(' and
                   precedence.get(stack.peek(), 0) >= precedence.get(char, 0)):
                postfix.append(stack.pop())
            stack.push(char)
    
    while not stack.is_empty():
        postfix.append(stack.pop())
    
    return ''.join(postfix)

# Usage
infix = "A+B*C"
postfix = infix_to_postfix(infix)
print(f"Infix: {infix}")     # A+B*C
print(f"Postfix: {postfix}") # ABC*+
```

##### Postfix Expression Evaluation
```python
def evaluate_postfix(expression):
    """Evaluate postfix expression using stack."""
    stack = ArrayStack()
    
    for char in expression:
        if char.isdigit():
            stack.push(int(char))
        else:
            # Operator
            operand2 = stack.pop()
            operand1 = stack.pop()
            
            if char == '+':
                result = operand1 + operand2
            elif char == '-':
                result = operand1 - operand2
            elif char == '*':
                result = operand1 * operand2
            elif char == '/':
                result = operand1 / operand2
            
            stack.push(result)
    
    return stack.pop()

# Usage
postfix_expr = "23*5+"
result = evaluate_postfix(postfix_expr)
print(f"{postfix_expr} = {result}")  # 23*5+ = 11
```

#### 2. Function Call Stack Simulation

```python
class CallStack:
    """Simulate function call stack."""
    
    def __init__(self):
        self.stack = ArrayStack()
    
    def push_frame(self, function_name, local_vars=None):
        """Push function frame onto stack."""
        frame = {
            'function': function_name,
            'locals': local_vars or {},
            'return_address': None
        }
        self.stack.push(frame)
        print(f"Called: {function_name}")
    
    def pop_frame(self):
        """Pop function frame from stack."""
        if self.stack.is_empty():
            raise RuntimeError("Stack underflow")
        
        frame = self.stack.pop()
        print(f"Returned from: {frame['function']}")
        return frame
    
    def peek_frame(self):
        """Get current function frame."""
        return self.stack.peek() if not self.stack.is_empty() else None
    
    def display_stack(self):
        """Display current call stack."""
        if self.stack.is_empty():
            print("Call stack is empty")
            return
        
        print("Call Stack (top to bottom):")
        # Convert stack to list for display
        frames = []
        temp_stack = ArrayStack()
        
        while not self.stack.is_empty():
            frame = self.stack.pop()
            frames.append(frame)
            temp_stack.push(frame)
        
        # Restore stack
        while not temp_stack.is_empty():
            self.stack.push(temp_stack.pop())
        
        # Display in reverse order (top first)
        for frame in reversed(frames):
            print(f"  {frame['function']}")

# Simulate recursive function calls
call_stack = CallStack()

def simulate_recursion(n):
    call_stack.push_frame(f"factorial({n})")
    
    if n <= 1:
        call_stack.pop_frame()
        return 1
    
    result = n * simulate_recursion(n - 1)
    call_stack.pop_frame()
    return result

print("Simulating factorial(3):")
result = simulate_recursion(3)
print(f"Result: {result}")
call_stack.display_stack()
```

#### 3. Undo/Redo Functionality

```python
class TextEditor:
    """Text editor with undo/redo using two stacks."""
    
    def __init__(self):
        self.text = ""
        self.undo_stack = ArrayStack()
        self.redo_stack = ArrayStack()
    
    def type_text(self, new_text):
        """Add text and save state for undo."""
        self.undo_stack.push(self.text)
        self.text += new_text
        # Clear redo stack when new action is performed
        self.redo_stack.clear()
    
    def undo(self):
        """Undo last action."""
        if self.undo_stack.is_empty():
            return False
        
        # Save current state to redo stack
        self.redo_stack.push(self.text)
        # Restore previous state
        self.text = self.undo_stack.pop()
        return True
    
    def redo(self):
        """Redo last undone action."""
        if self.redo_stack.is_empty():
            return False
        
        # Save current state to undo stack
        self.undo_stack.push(self.text)
        # Restore next state
        self.text = self.redo_stack.pop()
        return True
    
    def get_text(self):
        """Get current text."""
        return self.text
    
    def display_state(self):
        """Display current editor state."""
        print(f"Text: '{self.text}'")
        print(f"Undo stack size: {self.undo_stack.size()}")
        print(f"Redo stack size: {self.redo_stack.size()}")

# Usage
editor = TextEditor()
editor.type_text("Hello ")
editor.display_state()

editor.type_text("World!")
editor.display_state()

editor.undo()
editor.display_state()

editor.undo()
editor.display_state()

editor.redo()
editor.display_state()
```

#### 4. Browser Back/Forward Navigation

```python
class BrowserHistory:
    """Browser navigation using two stacks."""
    
    def __init__(self):
        self.back_stack = ArrayStack()
        self.forward_stack = ArrayStack()
        self.current_page = None
    
    def visit_page(self, url):
        """Visit a new page."""
        if self.current_page:
            self.back_stack.push(self.current_page)
        
        self.current_page = url
        # Clear forward stack when visiting new page
        self.forward_stack.clear()
        print(f"Visited: {url}")
    
    def go_back(self):
        """Go back to previous page."""
        if self.back_stack.is_empty():
            print("Cannot go back - no history")
            return False
        
        self.forward_stack.push(self.current_page)
        self.current_page = self.back_stack.pop()
        print(f"Went back to: {self.current_page}")
        return True
    
    def go_forward(self):
        """Go forward to next page."""
        if self.forward_stack.is_empty():
            print("Cannot go forward - no forward history")
            return False
        
        self.back_stack.push(self.current_page)
        self.current_page = self.forward_stack.pop()
        print(f"Went forward to: {self.current_page}")
        return True
    
    def get_current_page(self):
        """Get current page URL."""
        return self.current_page
    
    def display_history(self):
        """Display navigation history."""
        print(f"Current: {self.current_page}")
        print(f"Back stack: {self.back_stack}")
        print(f"Forward stack: {self.forward_stack}")

# Usage
browser = BrowserHistory()
browser.visit_page("https://google.com")
browser.visit_page("https://github.com")
browser.visit_page("https://stackoverflow.com")

browser.go_back()
browser.go_back()

browser.visit_page("https://reddit.com")  # Clears forward history

browser.display_history()
```

#### 5. Balanced Parentheses Checker

```python
def is_balanced(expression):
    """Check if parentheses are balanced using stack."""
    stack = ArrayStack()
    opening = "({["
    closing = ")}]"
    matches = {')': '(', '}': '{', ']': '['}
    
    for char in expression:
        if char in opening:
            stack.push(char)
        elif char in closing:
            if stack.is_empty():
                return False
            if stack.pop() != matches[char]:
                return False
    
    return stack.is_empty()

# Test cases
test_cases = [
    "(a + b)",           # True
    "[{()}]",            # True
    "(a + b",            # False - missing closing
    "a + b)",            # False - extra closing
    "[(])",              # False - mismatched
    "{a + [b * (c + d)] - e}",  # True
]

for expr in test_cases:
    result = is_balanced(expr)
    print(f"'{expr}' is balanced: {result}")
```

### Stack Performance and Analysis

#### Time Complexity
| Operation | Array Stack | Linked Stack | Notes |
|-----------|-------------|--------------|-------|
| push() | O(1) amortized | O(1) | Linked stack always O(1) |
| pop() | O(1) | O(1) | Both constant time |
| peek() | O(1) | O(1) | Direct access to top |
| is_empty() | O(1) | O(1) | Simple check |
| size() | O(1) | O(1) | Maintained counter |

#### Space Complexity
- **Array Stack**: O(n) - may have unused capacity
- **Linked Stack**: O(n) - exact size, extra pointer overhead

#### When to Use Stacks
- **Function call management**: Recursion, call stack
- **Expression evaluation**: Shunting-yard algorithm
- **Undo/redo functionality**: Text editors, games
- **Browser navigation**: Back/forward buttons
- **Syntax checking**: Balanced parentheses, XML validation
- **Depth-first search**: Graph algorithms

### Advanced Stack Concepts

#### Bounded Stacks
```python
class BoundedStack:
    """Stack with maximum capacity."""
    
    def __init__(self, capacity):
        self.stack = ArrayStack()
        self.capacity = capacity
    
    def push(self, item):
        if self.stack.size() >= self.capacity:
            raise OverflowError(f"Stack capacity {self.capacity} exceeded")
        self.stack.push(item)
    
    def pop(self):
        return self.stack.pop()
    
    def peek(self):
        return self.stack.peek()
    
    def is_empty(self):
        return self.stack.is_empty()
    
    def is_full(self):
        return self.stack.size() >= self.capacity
    
    def size(self):
        return self.stack.size()
```

#### Stack with Minimum Element Tracking
```python
class MinStack:
    """Stack that can return minimum element in O(1) time."""
    
    def __init__(self):
        self.stack = ArrayStack()
        self.min_stack = ArrayStack()  # Parallel stack for minimums
    
    def push(self, item):
        self.stack.push(item)
        
        # Update minimum stack
        if self.min_stack.is_empty() or item <= self.min_stack.peek():
            self.min_stack.push(item)
    
    def pop(self):
        if self.stack.is_empty():
            raise IndexError("Stack is empty")
        
        popped_item = self.stack.pop()
        
        # Update minimum stack
        if popped_item == self.min_stack.peek():
            self.min_stack.pop()
        
        return popped_item
    
    def peek(self):
        return self.stack.peek()
    
    def get_min(self):
        """Get minimum element in O(1) time."""
        if self.min_stack.is_empty():
            raise IndexError("Stack is empty")
        return self.min_stack.peek()
    
    def is_empty(self):
        return self.stack.is_empty()

# Usage
min_stack = MinStack()
min_stack.push(5)
min_stack.push(2)
min_stack.push(8)
min_stack.push(1)

print("Min:", min_stack.get_min())  # 1
min_stack.pop()
print("Min after pop:", min_stack.get_min())  # 2
```

Stacks are fundamental data structures with wide-ranging applications in computer science. Their LIFO nature makes them perfect for scenarios involving nested structures, undo operations, and recursive algorithms. Understanding stack implementations and their applications is crucial for efficient programming and algorithm design.

## Queues - FIFO (First-In-First-Out) Data Structure

Queues are linear data structures that follow the First-In-First-Out principle, where the first element added is the first one to be removed. They are essential for managing ordered sequences and are widely used in computer systems.

### Queue Operations and Interface

#### Core Operations
- **enqueue(item)**: Add item to rear of queue
- **dequeue()**: Remove and return item from front
- **front()/peek()**: Return front item without removing it
- **rear()**: Return rear item without removing it
- **is_empty()**: Check if queue contains no elements
- **size()**: Return number of elements in queue

#### Advanced Operations
- **clear()**: Remove all elements
- **contains(item)**: Check if item exists in queue
- **to_array()**: Convert queue to array/list

### Queue Implementations

#### Array-Based Queue (Python)
```python
class ArrayQueue:
    """Queue implementation using dynamic array (list)."""
    
    def __init__(self, capacity=None):
        self.items = []
        self.capacity = capacity
        self.front_index = 0
    
    def enqueue(self, item):
        """Add item to rear of queue."""
        if self.capacity and len(self.items) >= self.capacity:
            raise OverflowError("Queue is full")
        self.items.append(item)
    
    def dequeue(self):
        """Remove and return front item."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        
        front_item = self.items[self.front_index]
        self.front_index += 1
        
        # Reset indices when front reaches middle to save space
        if self.front_index > len(self.items) // 2:
            self.items = self.items[self.front_index:]
            self.front_index = 0
        
        return front_item
    
    def front(self):
        """Return front item without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.items[self.front_index]
    
    def rear(self):
        """Return rear item without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.items[-1]
    
    def is_empty(self):
        """Check if queue is empty."""
        return self.front_index >= len(self.items)
    
    def size(self):
        """Return number of items in queue."""
        return len(self.items) - self.front_index
    
    def clear(self):
        """Remove all items from queue."""
        self.items.clear()
        self.front_index = 0
    
    def __str__(self):
        """String representation of queue."""
        visible_items = self.items[self.front_index:]
        return f"Queue({visible_items})"

# Usage
queue = ArrayQueue()
for i in range(1, 6):
    queue.enqueue(i)

print("Queue:", queue)         # Queue([1, 2, 3, 4, 5])
print("Size:", queue.size())   # 5
print("Front:", queue.front()) # 1
print("Rear:", queue.rear())   # 5
print("Dequeue:", queue.dequeue())  # 1
print("After dequeue:", queue) # Queue([2, 3, 4, 5])
```

#### Linked List-Based Queue
```python
class LinkedQueue:
    """Queue implementation using linked list."""
    
    class Node:
        def __init__(self, data):
            self.data = data
            self.next = None
    
    def __init__(self):
        self.front = None
        self.rear = None
        self._size = 0
    
    def enqueue(self, item):
        """Add item to rear of queue."""
        new_node = self.Node(item)
        
        if self.is_empty():
            self.front = self.rear = new_node
        else:
            self.rear.next = new_node
            self.rear = new_node
        
        self._size += 1
    
    def dequeue(self):
        """Remove and return front item."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        
        dequeued_item = self.front.data
        
        if self.front == self.rear:
            self.front = self.rear = None
        else:
            self.front = self.front.next
        
        self._size -= 1
        return dequeued_item
    
    def front(self):
        """Return front item without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.front.data
    
    def rear(self):
        """Return rear item without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.rear.data
    
    def is_empty(self):
        """Check if queue is empty."""
        return self.front is None
    
    def size(self):
        """Return number of items in queue."""
        return self._size
    
    def clear(self):
        """Remove all items from queue."""
        self.front = self.rear = None
        self._size = 0
    
    def __str__(self):
        """String representation of queue."""
        items = []
        current = self.front
        while current:
            items.append(str(current.data))
            current = current.next
        return f"Queue([{', '.join(items)}])"

# Usage
queue = LinkedQueue()
for i in range(1, 4):
    queue.enqueue(i)

print("Linked Queue:", queue)  # Queue([1, 2, 3])
print("Dequeue:", queue.dequeue())  # 1
print("After dequeue:", queue)  # Queue([2, 3])
```

### Specialized Queue Types

#### 1. Circular Queue
```python
class CircularQueue:
    """Circular queue implementation."""
    
    def __init__(self, capacity):
        self.capacity = capacity
        self.queue = [None] * capacity
        self.front = self.rear = -1
        self.size = 0
    
    def enqueue(self, item):
        """Add item to rear of queue."""
        if self.is_full():
            raise OverflowError("Queue is full")
        
        if self.front == -1:  # First element
            self.front = 0
        
        self.rear = (self.rear + 1) % self.capacity
        self.queue[self.rear] = item
        self.size += 1
    
    def dequeue(self):
        """Remove and return front item."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        
        dequeued_item = self.queue[self.front]
        
        if self.front == self.rear:  # Last element
            self.front = self.rear = -1
        else:
            self.front = (self.front + 1) % self.capacity
        
        self.size -= 1
        return dequeued_item
    
    def front(self):
        """Return front item without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.queue[self.front]
    
    def rear(self):
        """Return rear item without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.queue[self.rear]
    
    def is_empty(self):
        """Check if queue is empty."""
        return self.front == -1
    
    def is_full(self):
        """Check if queue is full."""
        return (self.rear + 1) % self.capacity == self.front
    
    def size(self):
        """Return number of items in queue."""
        return self.size
    
    def __str__(self):
        """String representation of circular queue."""
        if self.is_empty():
            return "CircularQueue([])"
        
        items = []
        i = self.front
        for _ in range(self.size):
            items.append(str(self.queue[i]))
            i = (i + 1) % self.capacity
        
        return f"CircularQueue([{', '.join(items)}])"

# Usage
cq = CircularQueue(5)
for i in range(1, 4):
    cq.enqueue(i)

print("Circular Queue:", cq)  # CircularQueue([1, 2, 3])
cq.dequeue()
cq.enqueue(4)
cq.enqueue(5)
print("After operations:", cq)  # CircularQueue([2, 3, 4, 5])
```

#### 2. Priority Queue
```python
import heapq

class PriorityQueue:
    """Priority queue implementation using heap."""
    
    def __init__(self):
        self.queue = []
        self.index = 0  # For handling equal priorities
    
    def enqueue(self, item, priority=0):
        """Add item with priority."""
        heapq.heappush(self.queue, (priority, self.index, item))
        self.index += 1
    
    def dequeue(self):
        """Remove and return highest priority item."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return heapq.heappop(self.queue)[2]
    
    def peek(self):
        """Return highest priority item without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.queue[0][2]
    
    def is_empty(self):
        """Check if queue is empty."""
        return len(self.queue) == 0
    
    def size(self):
        """Return number of items in queue."""
        return len(self.queue)
    
    def __str__(self):
        """String representation of priority queue."""
        items = [str(item) for _, _, item in self.queue]
        return f"PriorityQueue([{', '.join(items)}])"

# Usage
pq = PriorityQueue()
pq.enqueue("low priority task", priority=3)
pq.enqueue("high priority task", priority=1)
pq.enqueue("medium priority task", priority=2)

print("Priority Queue:", pq)
print("Highest priority:", pq.peek())  # "high priority task"
print("Dequeue:", pq.dequeue())        # "high priority task"
print("Next highest:", pq.peek())      # "medium priority task"
```

#### 3. Deque (Double-Ended Queue)
```python
class Deque:
    """Double-ended queue implementation."""
    
    def __init__(self):
        self.items = []
    
    def add_front(self, item):
        """Add item to front of deque."""
        self.items.insert(0, item)
    
    def add_rear(self, item):
        """Add item to rear of deque."""
        self.items.append(item)
    
    def remove_front(self):
        """Remove and return front item."""
        if self.is_empty():
            raise IndexError("Deque is empty")
        return self.items.pop(0)
    
    def remove_rear(self):
        """Remove and return rear item."""
        if self.is_empty():
            raise IndexError("Deque is empty")
        return self.items.pop()
    
    def peek_front(self):
        """Return front item without removing it."""
        if self.is_empty():
            raise IndexError("Deque is empty")
        return self.items[0]
    
    def peek_rear(self):
        """Return rear item without removing it."""
        if self.is_empty():
            raise IndexError("Deque is empty")
        return self.items[-1]
    
    def is_empty(self):
        """Check if deque is empty."""
        return len(self.items) == 0
    
    def size(self):
        """Return number of items in deque."""
        return len(self.items)
    
    def clear(self):
        """Remove all items from deque."""
        self.items.clear()
    
    def __str__(self):
        """String representation of deque."""
        return f"Deque({self.items})"

# Usage
deque = Deque()
deque.add_rear(1)
deque.add_rear(2)
deque.add_front(0)

print("Deque:", deque)              # Deque([0, 1, 2])
print("Remove front:", deque.remove_front())  # 0
print("Remove rear:", deque.remove_rear())    # 2
print("After operations:", deque)   # Deque([1])
```

### Queue Applications and Algorithms

#### 1. Breadth-First Search (BFS)
```python
from collections import deque

def bfs(graph, start_node):
    """Breadth-first search using queue."""
    visited = set()
    queue = deque([start_node])
    visited.add(start_node)
    traversal_order = []
    
    while queue:
        current_node = queue.popleft()
        traversal_order.append(current_node)
        
        # Visit all unvisited neighbors
        for neighbor in graph.get(current_node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    
    return traversal_order

# Example graph
graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

print("BFS traversal:", bfs(graph, 'A'))  # ['A', 'B', 'C', 'D', 'E', 'F']
```

#### 2. Task Scheduling and Job Queue
```python
import time
from datetime import datetime

class JobQueue:
    """Job queue for task scheduling."""
    
    def __init__(self):
        self.queue = LinkedQueue()
        self.processing = False
    
    def add_job(self, job_name, priority=1):
        """Add job to queue with priority."""
        job = {
            'name': job_name,
            'priority': priority,
            'submitted_at': datetime.now(),
            'status': 'queued'
        }
        self.queue.enqueue(job)
        print(f"Job '{job_name}' added to queue")
    
    def process_jobs(self):
        """Process jobs in FIFO order."""
        if self.processing:
            print("Already processing jobs")
            return
        
        self.processing = True
        
        while not self.queue.is_empty():
            job = self.queue.dequeue()
            job['status'] = 'processing'
            job['started_at'] = datetime.now()
            
            print(f"Processing job: {job['name']}")
            
            # Simulate job processing time
            time.sleep(1)
            
            job['status'] = 'completed'
            job['completed_at'] = datetime.now()
            
            print(f"Completed job: {job['name']}")
        
        self.processing = False
        print("All jobs processed")

# Usage
job_queue = JobQueue()
job_queue.add_job("Data backup")
job_queue.add_job("Email sending")
job_queue.add_job("Report generation")

job_queue.process_jobs()
```

#### 3. Print Queue Simulation
```python
class PrintQueue:
    """Print queue simulation."""
    
    def __init__(self):
        self.queue = ArrayQueue()
        self.completed_jobs = []
    
    def add_print_job(self, document_name, pages, user):
        """Add document to print queue."""
        job = {
            'document': document_name,
            'pages': pages,
            'user': user,
            'submitted_at': datetime.now(),
            'status': 'queued'
        }
        self.queue.enqueue(job)
        print(f"Print job added: {document_name} ({pages} pages) for {user}")
    
    def process_print_jobs(self):
        """Process print jobs."""
        while not self.queue.is_empty():
            job = self.queue.dequeue()
            job['status'] = 'printing'
            job['started_at'] = datetime.now()
            
            print(f"Printing: {job['document']} for {job['user']}")
            
            # Simulate printing time (10 pages per minute)
            printing_time = job['pages'] / 10.0
            time.sleep(printing_time)
            
            job['status'] = 'completed'
            job['completed_at'] = datetime.now()
            self.completed_jobs.append(job)
            
            print(f"Completed: {job['document']} ({job['pages']} pages)")
    
    def show_queue_status(self):
        """Display current queue status."""
        if self.queue.is_empty():
            print("Print queue is empty")
        else:
            print(f"Jobs in queue: {self.queue.size()}")
            # In a real implementation, we'd iterate through queue
    
    def get_completed_jobs(self):
        """Get list of completed jobs."""
        return self.completed_jobs.copy()

# Usage
printer = PrintQueue()
printer.add_print_job("Report.pdf", 5, "Alice")
printer.add_print_job("Presentation.pptx", 20, "Bob")
printer.add_print_job("Letter.docx", 2, "Charlie")

printer.show_queue_status()
printer.process_print_jobs()

completed = printer.get_completed_jobs()
print(f"Total jobs completed: {len(completed)}")
```

#### 4. Message Queue System
```python
class MessageQueue:
    """Simple message queue for inter-process communication."""
    
    def __init__(self):
        self.queue = LinkedQueue()
        self.max_size = 100
    
    def send_message(self, message, sender, priority=1):
        """Send message to queue."""
        if self.queue.size() >= self.max_size:
            raise OverflowError("Message queue is full")
        
        msg = {
            'content': message,
            'sender': sender,
            'priority': priority,
            'timestamp': datetime.now(),
            'id': f"msg_{int(time.time() * 1000)}"
        }
        
        self.queue.enqueue(msg)
        print(f"Message sent by {sender}: {message[:50]}...")
    
    def receive_message(self):
        """Receive next message from queue."""
        if self.queue.is_empty():
            return None
        
        message = self.queue.dequeue()
        message['received_at'] = datetime.now()
        print(f"Message received from {message['sender']}: {message['content'][:50]}...")
        return message
    
    def peek_message(self):
        """Peek at next message without removing it."""
        return self.queue.front() if not self.queue.is_empty() else None
    
    def get_queue_size(self):
        """Get current queue size."""
        return self.queue.size()
    
    def clear_queue(self):
        """Clear all messages from queue."""
        self.queue.clear()
        print("Message queue cleared")

# Usage
mq = MessageQueue()
mq.send_message("Hello, how are you?", "Alice")
mq.send_message("Meeting at 3 PM", "Bob", priority=2)
mq.send_message("Project deadline extended", "Charlie")

print(f"Messages in queue: {mq.get_queue_size()}")

while mq.get_queue_size() > 0:
    mq.receive_message()
```

### Queue Performance Analysis

#### Time Complexity
| Operation | Array Queue | Linked Queue | Circular Queue | Notes |
|-----------|-------------|--------------|----------------|-------|
| enqueue() | O(1) | O(1) | O(1) | All constant time |
| dequeue() | O(1) amortized | O(1) | O(1) | Linked may have cleanup |
| front() | O(1) | O(1) | O(1) | Direct access |
| is_empty() | O(1) | O(1) | O(1) | Simple check |
| size() | O(1) | O(1) | O(1) | Maintained counter |

#### Space Complexity
- **Array Queue**: O(n) - may have unused space due to front index
- **Linked Queue**: O(n) - exact size, extra node overhead
- **Circular Queue**: O(n) - fixed size, optimal space usage

#### When to Use Queues
- **Task scheduling**: Print queues, job queues
- **Breadth-first search**: Graph traversal algorithms
- **Message passing**: Inter-process communication
- **Resource management**: Managing shared resources
- **Event handling**: Processing events in order
- **Cache implementation**: LRU cache with queues

### Advanced Queue Concepts

#### Thread-Safe Queue
```python
import threading

class ThreadSafeQueue:
    """Thread-safe queue implementation."""
    
    def __init__(self, max_size=None):
        self.queue = LinkedQueue()
        self.max_size = max_size
        self.lock = threading.Lock()
        self.not_empty = threading.Condition(self.lock)
        self.not_full = threading.Condition(self.lock)
    
    def enqueue(self, item, timeout=None):
        """Thread-safe enqueue with optional timeout."""
        with self.not_full:
            if self.max_size and self.queue.size() >= self.max_size:
                if not self.not_full.wait(timeout=timeout):
                    raise TimeoutError("Queue is full")
            
            self.queue.enqueue(item)
            self.not_empty.notify()
    
    def dequeue(self, timeout=None):
        """Thread-safe dequeue with optional timeout."""
        with self.not_empty:
            if self.queue.is_empty():
                if not self.not_empty.wait(timeout=timeout):
                    raise TimeoutError("Queue is empty")
            
            item = self.queue.dequeue()
            self.not_full.notify()
            return item
    
    def is_empty(self):
        """Check if queue is empty."""
        with self.lock:
            return self.queue.is_empty()
    
    def size(self):
        """Get queue size."""
        with self.lock:
            return self.queue.size()

# Usage example (would need threading)
# queue = ThreadSafeQueue(max_size=10)
# Threading code would go here...
```

Queues are fundamental data structures that manage ordered sequences efficiently. Their FIFO nature makes them perfect for scenarios involving processing in arrival order, task scheduling, and breadth-first algorithms. Understanding queue implementations and their applications is essential for building robust, concurrent systems.

## Trees - Hierarchical Data Structures

Trees are hierarchical data structures that organize data in a parent-child relationship. Each node (except the root) has exactly one parent, and each node can have zero or more children. Trees are fundamental for representing hierarchical relationships and are essential for many algorithms.

### Tree Terminology and Properties

#### Basic Tree Concepts
- **Root**: Topmost node with no parent
- **Node**: Element containing data and references to children
- **Edge**: Connection between parent and child nodes
- **Leaf**: Node with no children
- **Internal Node**: Node with at least one child
- **Height**: Longest path from root to leaf
- **Depth**: Distance from root to node
- **Level**: Nodes at same depth
- **Subtree**: Tree formed by node and its descendants

#### Tree Properties
- **Acyclic**: No cycles in the structure
- **Connected**: All nodes reachable from root
- **Directed**: Edges have direction (parent to child)
- **Recursive**: Subtrees are also trees

### Binary Trees - Two Children Maximum

#### Binary Tree Node Structure
```python
class TreeNode:
    """Binary tree node with data and two children."""
    
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
    
    def __repr__(self):
        return f"TreeNode({self.data})"
    
    def is_leaf(self):
        """Check if node is a leaf."""
        return self.left is None and self.right is None
    
    def has_left_child(self):
        """Check if node has left child."""
        return self.left is not None
    
    def has_right_child(self):
        """Check if node has right child."""
        return self.right is not None
    
    def get_height(self):
        """Calculate height of subtree rooted at this node."""
        if self.is_leaf():
            return 0
        
        left_height = self.left.get_height() if self.left else -1
        right_height = self.right.get_height() if self.right else -1
        
        return 1 + max(left_height, right_height)
```

#### Binary Tree Implementation
```python
class BinaryTree:
    """Binary tree implementation."""
    
    def __init__(self, root=None):
        self.root = root
    
    def is_empty(self):
        """Check if tree is empty."""
        return self.root is None
    
    def insert(self, data):
        """Insert data into binary tree (not BST - just adds to first available spot)."""
        if self.is_empty():
            self.root = TreeNode(data)
            return
        
        queue = [self.root]
        
        while queue:
            current = queue.pop(0)
            
            if not current.has_left_child():
                current.left = TreeNode(data)
                return
            elif not current.has_right_child():
                current.right = TreeNode(data)
                return
            else:
                queue.append(current.left)
                queue.append(current.right)
    
    def search(self, data):
        """Search for data in tree."""
        if self.is_empty():
            return None
        
        queue = [self.root]
        
        while queue:
            current = queue.pop(0)
            
            if current.data == data:
                return current
            
            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)
        
        return None
    
    def get_height(self):
        """Get height of tree."""
        return self.root.get_height() if self.root else -1
    
    def count_nodes(self):
        """Count total number of nodes."""
        if self.is_empty():
            return 0
        
        count = 0
        queue = [self.root]
        
        while queue:
            current = queue.pop(0)
            count += 1
            
            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)
        
        return count
    
    def count_leaves(self):
        """Count number of leaf nodes."""
        if self.is_empty():
            return 0
        
        count = 0
        queue = [self.root]
        
        while queue:
            current = queue.pop(0)
            
            if current.is_leaf():
                count += 1
            else:
                if current.left:
                    queue.append(current.left)
                if current.right:
                    queue.append(current.right)
        
        return count

# Usage
bt = BinaryTree()
for i in range(1, 8):
    bt.insert(i)

print(f"Tree height: {bt.get_height()}")      # 2
print(f"Total nodes: {bt.count_nodes()}")     # 7
print(f"Leaf nodes: {bt.count_leaves()}")     # 4

found_node = bt.search(5)
print(f"Found node: {found_node}")            # TreeNode(5)
```

### Tree Traversal Algorithms

#### Depth-First Traversals

##### Preorder Traversal (Root, Left, Right)
```python
def preorder_traversal(node):
    """Preorder: Root -> Left -> Right."""
    if node:
        print(node.data, end=" ")
        preorder_traversal(node.left)
        preorder_traversal(node.right)

# Iterative preorder
def preorder_iterative(root):
    """Iterative preorder using stack."""
    if not root:
        return
    
    stack = [root]
    
    while stack:
        current = stack.pop()
        print(current.data, end=" ")
        
        # Push right first, then left (so left is processed first)
        if current.right:
            stack.append(current.right)
        if current.left:
            stack.append(current.left)
```

##### Inorder Traversal (Left, Root, Right)
```python
def inorder_traversal(node):
    """Inorder: Left -> Root -> Right."""
    if node:
        inorder_traversal(node.left)
        print(node.data, end=" ")
        inorder_traversal(node.right)

# Iterative inorder
def inorder_iterative(root):
    """Iterative inorder using stack."""
    stack = []
    current = root
    
    while current or stack:
        # Reach the leftmost node
        while current:
            stack.append(current)
            current = current.left
        
        # Process the node
        current = stack.pop()
        print(current.data, end=" ")
        
        # Move to right subtree
        current = current.right
```

##### Postorder Traversal (Left, Right, Root)
```python
def postorder_traversal(node):
    """Postorder: Left -> Right -> Root."""
    if node:
        postorder_traversal(node.left)
        postorder_traversal(node.right)
        print(node.data, end=" ")

# Iterative postorder (more complex)
def postorder_iterative(root):
    """Iterative postorder using two stacks."""
    if not root:
        return
    
    stack1 = [root]
    stack2 = []
    
    while stack1:
        current = stack1.pop()
        stack2.append(current)
        
        if current.left:
            stack1.append(current.left)
        if current.right:
            stack1.append(current.right)
    
    # Print from stack2
    while stack2:
        print(stack2.pop().data, end=" ")
```

#### Breadth-First Traversal (Level Order)
```python
def level_order_traversal(root):
    """Level order traversal using queue."""
    if not root:
        return
    
    from collections import deque
    queue = deque([root])
    
    while queue:
        current = queue.popleft()
        print(current.data, end=" ")
        
        if current.left:
            queue.append(current.left)
        if current.right:
            queue.append(current.right)

# Create sample tree
root = TreeNode(1)
root.left = TreeNode(2)
root.right = TreeNode(3)
root.left.left = TreeNode(4)
root.left.right = TreeNode(5)
root.right.left = TreeNode(6)
root.right.right = TreeNode(7)

print("Preorder:", end=" ")
preorder_traversal(root)
print()

print("Inorder:", end=" ")
inorder_traversal(root)
print()

print("Postorder:", end=" ")
postorder_traversal(root)
print()

print("Level order:", end=" ")
level_order_traversal(root)
print()
```

### Binary Search Trees (BST)

#### BST Properties
- Left subtree contains only nodes with values less than root
- Right subtree contains only nodes with values greater than root
- Both subtrees are also BSTs
- No duplicate values (typically)

#### BST Implementation
```python
class BSTNode:
    """Binary Search Tree Node."""
    
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.parent = None  # For advanced operations
    
    def __repr__(self):
        return f"BSTNode({self.data})"

class BinarySearchTree:
    """Binary Search Tree implementation."""
    
    def __init__(self):
        self.root = None
        self.size = 0
    
    def is_empty(self):
        return self.root is None
    
    def insert(self, data):
        """Insert data into BST."""
        if self.is_empty():
            self.root = BSTNode(data)
        else:
            self._insert_recursive(self.root, data)
        self.size += 1
    
    def _insert_recursive(self, node, data):
        """Recursive insert helper."""
        if data < node.data:
            if node.left is None:
                node.left = BSTNode(data)
                node.left.parent = node
            else:
                self._insert_recursive(node.left, data)
        elif data > node.data:
            if node.right is None:
                node.right = BSTNode(data)
                node.right.parent = node
            else:
                self._insert_recursive(node.right, data)
        # Ignore duplicates for simplicity
    
    def search(self, data):
        """Search for data in BST."""
        return self._search_recursive(self.root, data)
    
    def _search_recursive(self, node, data):
        """Recursive search helper."""
        if node is None or node.data == data:
            return node
        
        if data < node.data:
            return self._search_recursive(node.left, data)
        else:
            return self._search_recursive(node.right, data)
    
    def find_min(self):
        """Find minimum value in BST."""
        if self.is_empty():
            return None
        
        current = self.root
        while current.left:
            current = current.left
        return current.data
    
    def find_max(self):
        """Find maximum value in BST."""
        if self.is_empty():
            return None
        
        current = self.root
        while current.right:
            current = current.right
        return current.data
    
    def inorder_traversal(self):
        """Inorder traversal (sorted order for BST)."""
        result = []
        self._inorder_helper(self.root, result)
        return result
    
    def _inorder_helper(self, node, result):
        """Inorder traversal helper."""
        if node:
            self._inorder_helper(node.left, result)
            result.append(node.data)
            self._inorder_helper(node.right, result)
    
    def delete(self, data):
        """Delete node with given data."""
        self.root = self._delete_recursive(self.root, data)
    
    def _delete_recursive(self, node, data):
        """Recursive delete helper."""
        if node is None:
            return node
        
        if data < node.data:
            node.left = self._delete_recursive(node.left, data)
        elif data > node.data:
            node.right = self._delete_recursive(node.right, data)
        else:
            # Node with one or no child
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            
            # Node with two children
            # Get inorder successor (smallest in right subtree)
            successor = self._find_min(node.right)
            node.data = successor.data
            node.right = self._delete_recursive(node.right, successor.data)
        
        return node
    
    def _find_min(self, node):
        """Find minimum node in subtree."""
        current = node
        while current.left:
            current = current.left
        return current

# Usage
bst = BinarySearchTree()
data = [50, 30, 70, 20, 40, 60, 80]

for item in data:
    bst.insert(item)

print("Inorder traversal:", bst.inorder_traversal())  # [20, 30, 40, 50, 60, 70, 80]
print("Search 40:", bst.search(40) is not None)       # True
print("Search 90:", bst.search(90) is not None)       # False
print("Min:", bst.find_min())                         # 20
print("Max:", bst.find_max())                         # 80

bst.delete(30)
print("After deleting 30:", bst.inorder_traversal())  # [20, 40, 50, 60, 70, 80]
```

### Advanced Tree Structures

#### AVL Trees (Self-Balancing BST)
```python
class AVLNode:
    """AVL Tree Node with height."""
    
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1
    
    def get_balance(self):
        """Get balance factor."""
        left_height = self.left.height if self.left else 0
        right_height = self.right.height if self.right else 0
        return left_height - right_height
    
    def update_height(self):
        """Update height based on children."""
        left_height = self.left.height if self.left else 0
        right_height = self.right.height if self.right else 0
        self.height = 1 + max(left_height, right_height)

class AVLTree:
    """Self-balancing AVL Tree."""
    
    def insert(self, root, data):
        """Insert with balancing."""
        if not root:
            return AVLNode(data)
        
        if data < root.data:
            root.left = self.insert(root.left, data)
        elif data > root.data:
            root.right = self.insert(root.right, data)
        else:
            return root  # Duplicate
        
        root.update_height()
        
        balance = root.get_balance()
        
        # Left Left Case
        if balance > 1 and data < root.left.data:
            return self.right_rotate(root)
        
        # Right Right Case
        if balance < -1 and data > root.right.data:
            return self.left_rotate(root)
        
        # Left Right Case
        if balance > 1 and data > root.left.data:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)
        
        # Right Left Case
        if balance < -1 and data < root.right.data:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)
        
        return root
    
    def left_rotate(self, z):
        """Left rotation."""
        y = z.right
        T2 = y.left
        
        y.left = z
        z.right = T2
        
        z.update_height()
        y.update_height()
        
        return y
    
    def right_rotate(self, z):
        """Right rotation."""
        y = z.left
        T3 = y.right
        
        y.right = z
        z.left = T3
        
        z.update_height()
        y.update_height()
        
        return y

# AVL Tree maintains O(log n) height
```

#### Trie (Prefix Tree)
```python
class TrieNode:
    """Trie node with children dictionary."""
    
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie:
    """Prefix tree for efficient string operations."""
    
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word):
        """Insert word into trie."""
        current = self.root
        
        for char in word:
            if char not in current.children:
                current.children[char] = TrieNode()
            current = current.children[char]
        
        current.is_end_of_word = True
    
    def search(self, word):
        """Check if word exists in trie."""
        current = self.root
        
        for char in word:
            if char not in current.children:
                return False
            current = current.children[char]
        
        return current.is_end_of_word
    
    def starts_with(self, prefix):
        """Check if any word starts with given prefix."""
        current = self.root
        
        for char in prefix:
            if char not in current.children:
                return False
            current = current.children[char]
        
        return True
    
    def get_words_with_prefix(self, prefix):
        """Get all words with given prefix."""
        def dfs(node, current_word, result):
            if node.is_end_of_word:
                result.append(current_word)
            
            for char, child_node in node.children.items():
                dfs(child_node, current_word + char, result)
        
        current = self.root
        for char in prefix:
            if char not in current.children:
                return []
            current = current.children[char]
        
        result = []
        dfs(current, prefix, result)
        return result

# Usage
trie = Trie()
words = ["apple", "app", "application", "bat", "ball", "batman"]

for word in words:
    trie.insert(word)

print("Search 'app':", trie.search("app"))                    # True
print("Search 'apple':", trie.search("apple"))                # True
print("Search 'appl':", trie.search("appl"))                  # False
print("Starts with 'app':", trie.starts_with("app"))          # True
print("Words with 'app' prefix:", trie.get_words_with_prefix("app"))  # ['apple', 'app', 'application']
```

### Tree Performance Analysis

#### Time Complexity
| Operation | Binary Tree | BST | AVL Tree | Notes |
|-----------|-------------|-----|----------|-------|
| Search | O(n) | O(h) | O(log n) | h = height |
| Insert | O(n) | O(h) | O(log n) | Worst case varies |
| Delete | O(n) | O(h) | O(log n) | BST may degenerate |
| Traversal | O(n) | O(n) | O(n) | All nodes visited |

#### Space Complexity
- **Binary Tree**: O(n) - nodes and pointers
- **BST**: O(n) - same as binary tree
- **AVL Tree**: O(n) - additional height information
- **Trie**: O(m) - m = total characters in all words

#### When to Use Trees
- **Hierarchical data**: File systems, organization charts
- **Sorted data**: BST for ordered operations
- **Fast search**: Balanced trees for O(log n) operations
- **Prefix matching**: Tries for autocomplete
- **Expression parsing**: Expression trees
- **Decision making**: Decision trees

Trees provide powerful ways to organize hierarchical data and enable efficient operations on structured information. Understanding tree traversals, balancing algorithms, and specialized tree types is crucial for advanced programming and algorithm design.

## Hash Tables - Fast Key-Value Storage

Hash tables (also called hash maps or dictionaries) are data structures that store key-value pairs and provide average O(1) time complexity for insertions, deletions, and lookups. They use hash functions to map keys to array indices.

### Hash Function and Collision Resolution

#### Hash Function Properties
- **Deterministic**: Same key always produces same hash
- **Uniform Distribution**: Evenly distributes keys across table
- **Fast Computation**: Quick to calculate
- **Avalanche Effect**: Small input changes cause large output changes

#### Collision Resolution Strategies
1. **Separate Chaining**: Each bucket contains linked list of entries
2. **Open Addressing**: Find alternative location when collision occurs
   - Linear Probing: Check next consecutive slots
   - Quadratic Probing: Check slots with quadratic function
   - Double Hashing: Use second hash function

### Hash Table Implementation

#### Simple Hash Table with Separate Chaining
```python
class HashTableEntry:
    """Entry for hash table with key-value pairs."""
    
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None
    
    def __repr__(self):
        return f"Entry({self.key}: {self.value})"

class HashTable:
    """Hash table implementation with separate chaining."""
    
    def __init__(self, capacity=16):
        self.capacity = capacity
        self.size = 0
        self.buckets = [None] * capacity
        self.load_factor_threshold = 0.75
    
    def _hash(self, key):
        """Simple hash function."""
        return hash(key) % self.capacity
    
    def _resize(self):
        """Resize hash table when load factor exceeded."""
        old_buckets = self.buckets
        self.capacity *= 2
        self.buckets = [None] * self.capacity
        self.size = 0
        
        # Rehash all entries
        for bucket in old_buckets:
            current = bucket
            while current:
                self.put(current.key, current.value)
                current = current.next
    
    def put(self, key, value):
        """Insert or update key-value pair."""
        index = self._hash(key)
        
        # Check if key already exists
        current = self.buckets[index]
        while current:
            if current.key == key:
                current.value = value
                return
            current = current.next
        
        # Key doesn't exist, add new entry
        new_entry = HashTableEntry(key, value)
        new_entry.next = self.buckets[index]
        self.buckets[index] = new_entry
        self.size += 1
        
        # Check load factor
        if self.size / self.capacity > self.load_factor_threshold:
            self._resize()
    
    def get(self, key):
        """Get value for key."""
        index = self._hash(key)
        current = self.buckets[index]
        
        while current:
            if current.key == key:
                return current.value
            current = current.next
        
        raise KeyError(f"Key '{key}' not found")
    
    def remove(self, key):
        """Remove key-value pair."""
        index = self._hash(key)
        current = self.buckets[index]
        prev = None
        
        while current:
            if current.key == key:
                if prev:
                    prev.next = current.next
                else:
                    self.buckets[index] = current.next
                self.size -= 1
                return current.value
            prev = current
            current = current.next
        
        raise KeyError(f"Key '{key}' not found")
    
    def contains(self, key):
        """Check if key exists."""
        try:
            self.get(key)
            return True
        except KeyError:
            return False
    
    def keys(self):
        """Get all keys."""
        keys = []
        for bucket in self.buckets:
            current = bucket
            while current:
                keys.append(current.key)
                current = current.next
        return keys
    
    def values(self):
        """Get all values."""
        values = []
        for bucket in self.buckets:
            current = bucket
            while current:
                values.append(current.value)
                current = current.next
        return values
    
    def items(self):
        """Get all key-value pairs."""
        items = []
        for bucket in self.buckets:
            current = bucket
            while current:
                items.append((current.key, current.value))
                current = current.next
        return items
    
    def __len__(self):
        """Return number of entries."""
        return self.size
    
    def __str__(self):
        """String representation."""
        items = []
        for bucket in self.buckets:
            current = bucket
            while current:
                items.append(f"{current.key}: {current.value}")
                current = current.next
        return "{" + ", ".join(items) + "}"

# Usage
ht = HashTable()
ht.put("Alice", 95)
ht.put("Bob", 87)
ht.put("Charlie", 92)

print("Hash table:", ht)                    # {Alice: 95, Bob: 87, Charlie: 92}
print("Get Alice:", ht.get("Alice"))        # 95
print("Contains Bob:", ht.contains("Bob"))  # True
print("Size:", len(ht))                     # 3

ht.put("Alice", 97)  # Update
print("After update:", ht)                  # {Alice: 97, Bob: 87, Charlie: 92}

ht.remove("Bob")
print("After remove:", ht)                  # {Alice: 97, Charlie: 92}
```

### Python Dictionary Implementation Details

```python
# Python's built-in dict uses open addressing with probing
# Here's how it works internally

class PythonDictSimulation:
    """Simplified simulation of Python dict behavior."""
    
    def __init__(self):
        self.keys = []
        self.values = []
        self.size = 0
        self.capacity = 8
    
    def _find_index(self, key):
        """Find index for key using linear probing."""
        hash_value = hash(key)
        index = hash_value % self.capacity
        
        # Linear probing for collision resolution
        original_index = index
        while self.keys[index] is not None and self.keys[index] != key:
            index = (index + 1) % self.capacity
            if index == original_index:  # Full cycle
                return -1
        
        return index
    
    def __setitem__(self, key, value):
        """Set item (simplified)."""
        if self.size / self.capacity > 0.75:
            self._resize()
        
        index = self._find_index(key)
        if index == -1:
            raise RuntimeError("Hash table is full")
        
        if self.keys[index] is None:
            self.size += 1
        
        self.keys[index] = key
        self.values[index] = value
    
    def __getitem__(self, key):
        """Get item."""
        index = self._find_index(key)
        if index == -1 or self.keys[index] is None:
            raise KeyError(key)
        return self.values[index]
    
    def _resize(self):
        """Resize hash table."""
        old_keys = self.keys
        old_values = self.values
        
        self.capacity *= 2
        self.keys = [None] * self.capacity
        self.values = [None] * self.capacity
        self.size = 0
        
        # Rehash all entries
        for key, value in zip(old_keys, old_values):
            if key is not None:
                self[key] = value

# Real Python dict usage
student_grades = {
    "Alice": 95,
    "Bob": 87,
    "Charlie": 92
}

# Accessing values
print(student_grades["Alice"])     # 95
print(student_grades.get("Bob"))   # 87
print(student_grades.get("David", "Not found"))  # Not found

# Adding/modifying entries
student_grades["David"] = 88
student_grades["Alice"] = 97

# Iterating
for name, grade in student_grades.items():
    print(f"{name}: {grade}")

# Dictionary methods
print("Keys:", list(student_grades.keys()))
print("Values:", list(student_grades.values()))
print("Items:", list(student_grades.items()))

# Dictionary comprehensions
squared_grades = {name: grade**2 for name, grade in student_grades.items()}
print("Squared grades:", squared_grades)

# Merging dictionaries
more_grades = {"Eve": 89, "Frank": 91}
all_grades = {**student_grades, **more_grades}
print("All grades:", all_grades)
```

### Advanced Hash Table Applications

#### 1. Caching with TTL (Time To Live)
```python
import time

class TTLCache:
    """Cache with time-to-live functionality."""
    
    def __init__(self, capacity=100, default_ttl=300):
        self.cache = {}
        self.ttl = {}  # Time-to-live for each key
        self.capacity = capacity
        self.default_ttl = default_ttl
    
    def set(self, key, value, ttl=None):
        """Set value with optional TTL."""
        if ttl is None:
            ttl = self.default_ttl
        
        current_time = time.time()
        self.cache[key] = value
        self.ttl[key] = current_time + ttl
        
        # Simple LRU-like eviction if over capacity
        if len(self.cache) > self.capacity:
            self._evict_oldest()
    
    def get(self, key):
        """Get value if not expired."""
        if key not in self.cache:
            return None
        
        if time.time() > self.ttl[key]:
            # Expired
            del self.cache[key]
            del self.ttl[key]
            return None
        
        return self.cache[key]
    
    def delete(self, key):
        """Delete key from cache."""
        if key in self.cache:
            del self.cache[key]
            del self.ttl[key]
    
    def clear_expired(self):
        """Clear all expired entries."""
        current_time = time.time()
        expired_keys = [
            key for key, expiry in self.ttl.items()
            if current_time > expiry
        ]
        
        for key in expired_keys:
            del self.cache[key]
            del self.ttl[key]
    
    def _evict_oldest(self):
        """Evict oldest entry (simplified LRU)."""
        if not self.cache:
            return
        
        # Find key with earliest expiry
        oldest_key = min(self.ttl.keys(), key=lambda k: self.ttl[k])
        self.delete(oldest_key)

# Usage
cache = TTLCache(capacity=3, default_ttl=10)  # 10 seconds TTL

cache.set("user_data", {"name": "Alice", "age": 25})
cache.set("config", {"theme": "dark"}, ttl=5)  # 5 seconds TTL

print("Get user_data:", cache.get("user_data"))  # Works
print("Get config:", cache.get("config"))       # Works

time.sleep(6)  # Wait for config to expire
print("Get config after expiry:", cache.get("config"))  # None
```

#### 2. Frequency Counter
```python
def character_frequency(text):
    """Count frequency of each character using hash table."""
    frequency = {}
    
    for char in text:
        if char in frequency:
            frequency[char] += 1
        else:
            frequency[char] = 1
    
    return frequency

def word_frequency(text):
    """Count frequency of each word."""
    words = text.lower().split()
    frequency = {}
    
    for word in words:
        # Remove punctuation
        clean_word = ''.join(c for c in word if c.isalnum())
        if clean_word:
            frequency[clean_word] = frequency.get(clean_word, 0) + 1
    
    return frequency

# Usage
text = "Hello world! Hello Python. Python is great."
print("Character frequency:", character_frequency(text))
print("Word frequency:", word_frequency(text))

# Find most common elements
def most_common(items, n=1):
    """Find n most common items."""
    frequency = {}
    for item in items:
        frequency[item] = frequency.get(item, 0) + 1
    
    # Sort by frequency (descending)
    sorted_items = sorted(frequency.items(), key=lambda x: x[1], reverse=True)
    return sorted_items[:n]

numbers = [1, 2, 2, 3, 3, 3, 4, 4, 4, 4]
print("Most common numbers:", most_common(numbers, 2))
```

#### 3. Two Sum Problem
```python
def two_sum(nums, target):
    """Find two numbers that add up to target."""
    seen = {}  # number -> index
    
    for i, num in enumerate(nums):
        complement = target - num
        
        if complement in seen:
            return [seen[complement], i]
        
        seen[num] = i
    
    return None

# Usage
nums = [2, 7, 11, 15]
target = 9
result = two_sum(nums, target)
print(f"Indices that sum to {target}: {result}")  # [0, 1] (2 + 7 = 9)

# Group Anagrams
def group_anagrams(words):
    """Group words that are anagrams."""
    anagram_groups = {}
    
    for word in words:
        # Sort characters to create key
        sorted_word = ''.join(sorted(word.lower()))
        
        if sorted_word not in anagram_groups:
            anagram_groups[sorted_word] = []
        
        anagram_groups[sorted_word].append(word)
    
    return list(anagram_groups.values())

words = ["eat", "tea", "tan", "ate", "nat", "bat"]
print("Anagram groups:", group_anagrams(words))
# [['eat', 'tea', 'ate'], ['tan', 'nat'], ['bat']]
```

### Hash Table Performance Analysis

#### Time Complexity
| Operation | Average Case | Worst Case | Notes |
|-----------|--------------|------------|-------|
| Insert | O(1) | O(n) | Depends on collision resolution |
| Search | O(1) | O(n) | Worst case with many collisions |
| Delete | O(1) | O(n) | Same as search |
| Contains | O(1) | O(n) | Same as search |

#### Space Complexity
- **Hash Table**: O(n) - for entries plus overhead
- **Load Factor**: n/m where n=entries, m=buckets
- **Rehashing**: Temporary O(n) space during resize

#### Load Factor and Rehashing
- **Load Factor**: ratio of entries to buckets
- **Threshold**: when to resize (typically 0.75)
- **Rehashing**: create new table, rehash all entries
- **Growth**: typically double the size

### Hash Function Design

#### Good Hash Function Properties
```python
def simple_hash(key, table_size):
    """Simple hash function for demonstration."""
    if isinstance(key, str):
        # String hash
        hash_value = 0
        for char in key:
            hash_value = (hash_value * 31 + ord(char)) % table_size
        return hash_value
    elif isinstance(key, int):
        return key % table_size
    else:
        return hash(key) % table_size

def djb2_hash(key, table_size):
    """DJB2 hash function."""
    hash_value = 5381
    
    for char in str(key):
        hash_value = ((hash_value << 5) + hash_value) + ord(char)  # hash * 33 + char
    
    return hash_value % table_size

# Test hash functions
keys = ["apple", "banana", "cherry", "date", "elderberry"]
table_size = 16

print("Hash distribution:")
for key in keys:
    simple = simple_hash(key, table_size)
    djb2 = djb2_hash(key, table_size)
    print(f"{key}: simple={simple}, djb2={djb2}")
```

### Hash Table vs Other Data Structures

| Data Structure | Search | Insert | Delete | Ordered | Notes |
|----------------|--------|--------|--------|---------|-------|
| Hash Table | O(1) | O(1) | O(1) | No | Fast, unordered |
| Binary Search Tree | O(log n) | O(log n) | O(log n) | Yes | Ordered, balanced |
| Array | O(n) | O(1)* | O(n) | Yes | Fast insert end |
| Linked List | O(n) | O(1) | O(1)* | No | Fast insert/delete |

* = amortized or with pointer

### Real-World Applications

#### 1. Database Indexing
```python
class SimpleDatabaseIndex:
    """Simple database index using hash table."""
    
    def __init__(self):
        self.primary_index = {}  # id -> record
        self.secondary_indexes = {}  # field -> {value -> [ids]}
    
    def insert(self, record):
        """Insert record with automatic indexing."""
        record_id = record['id']
        self.primary_index[record_id] = record
        
        # Create secondary indexes
        for field, value in record.items():
            if field != 'id':
                if field not in self.secondary_indexes:
                    self.secondary_indexes[field] = {}
                
                if value not in self.secondary_indexes[field]:
                    self.secondary_indexes[field][value] = []
                
                self.secondary_indexes[field][value].append(record_id)
    
    def find_by_id(self, record_id):
        """Find record by primary key."""
        return self.primary_index.get(record_id)
    
    def find_by_field(self, field, value):
        """Find records by field value."""
        if field not in self.secondary_indexes:
            return []
        
        ids = self.secondary_indexes[field].get(value, [])
        return [self.primary_index[id] for id in ids]

# Usage
db = SimpleDatabaseIndex()

records = [
    {"id": 1, "name": "Alice", "department": "Engineering"},
    {"id": 2, "name": "Bob", "department": "Sales"},
    {"id": 3, "name": "Charlie", "department": "Engineering"},
]

for record in records:
    db.insert(record)

print("Find by ID:", db.find_by_id(2))
print("Find by department:", db.find_by_field("department", "Engineering"))
```

#### 2. Symbol Table in Compilers
```python
class SymbolTable:
    """Symbol table for compiler - tracks variables, functions, etc."""
    
    def __init__(self):
        self.symbols = {}
        self.scope_stack = []  # For nested scopes
    
    def enter_scope(self):
        """Enter new scope."""
        self.scope_stack.append({})
    
    def exit_scope(self):
        """Exit current scope."""
        if self.scope_stack:
            self.scope_stack.pop()
    
    def declare_symbol(self, name, symbol_type, attributes=None):
        """Declare symbol in current scope."""
        if not self.scope_stack:
            raise RuntimeError("No active scope")
        
        current_scope = self.scope_stack[-1]
        if name in current_scope:
            raise ValueError(f"Symbol '{name}' already declared in current scope")
        
        current_scope[name] = {
            'type': symbol_type,
            'attributes': attributes or {},
            'scope_level': len(self.scope_stack)
        }
    
    def lookup_symbol(self, name):
        """Lookup symbol starting from current scope outward."""
        # Search from innermost to outermost scope
        for scope in reversed(self.scope_stack):
            if name in scope:
                return scope[name]
        return None
    
    def get_all_symbols(self):
        """Get all symbols in all scopes."""
        all_symbols = {}
        for scope in self.scope_stack:
            all_symbols.update(scope)
        return all_symbols

# Usage in compiler
symbol_table = SymbolTable()

# Global scope
symbol_table.enter_scope()
symbol_table.declare_symbol("global_var", "integer", {"value": 42})

# Function scope
symbol_table.enter_scope()
symbol_table.declare_symbol("local_var", "string", {"value": "hello"})
symbol_table.declare_symbol("param", "boolean", {"default": True})

print("Lookup local_var:", symbol_table.lookup_symbol("local_var"))
print("Lookup global_var:", symbol_table.lookup_symbol("global_var"))

symbol_table.exit_scope()  # Exit function scope
print("Lookup local_var after exit:", symbol_table.lookup_symbol("local_var"))  # None
print("Lookup global_var after exit:", symbol_table.lookup_symbol("global_var"))  # Still works
```

Hash tables are fundamental to efficient data access and are used extensively in databases, caches, compilers, and many other applications. Understanding hash functions, collision resolution, and performance characteristics is essential for building high-performance systems.

## Advanced Data Structures and Specialized Collections

### Graphs - Complex Relationship Modeling

#### Graph Terminology
- **Vertex/Node**: Fundamental unit (data point)
- **Edge**: Connection between vertices
- **Directed Graph**: Edges have direction
- **Undirected Graph**: Edges are bidirectional
- **Weighted Graph**: Edges have weights/costs
- **Degree**: Number of edges connected to vertex
- **Path**: Sequence of vertices connected by edges
- **Cycle**: Path that starts and ends at same vertex

#### Graph Representations

##### Adjacency Matrix
```python
class GraphMatrix:
    """Graph representation using adjacency matrix."""
    
    def __init__(self, vertices):
        self.vertices = vertices
        self.matrix = [[0 for _ in range(vertices)] for _ in range(vertices)]
    
    def add_edge(self, u, v, weight=1):
        """Add edge between vertices u and v."""
        self.matrix[u][v] = weight
        # For undirected graph, add reverse edge
        # self.matrix[v][u] = weight
    
    def remove_edge(self, u, v):
        """Remove edge between vertices u and v."""
        self.matrix[u][v] = 0
        # self.matrix[v][u] = 0  # For undirected
    
    def has_edge(self, u, v):
        """Check if edge exists."""
        return self.matrix[u][v] != 0
    
    def get_neighbors(self, u):
        """Get all neighbors of vertex u."""
        return [v for v in range(self.vertices) if self.matrix[u][v] != 0]
    
    def display(self):
        """Display adjacency matrix."""
        for row in self.matrix:
            print(row)

# Usage
graph = GraphMatrix(4)
graph.add_edge(0, 1)
graph.add_edge(0, 2)
graph.add_edge(1, 2)
graph.add_edge(2, 3)

print("Adjacency Matrix:")
graph.display()
print("Neighbors of 0:", graph.get_neighbors(0))
```

##### Adjacency List
```python
class GraphList:
    """Graph representation using adjacency list."""
    
    def __init__(self):
        self.adj_list = {}
    
    def add_vertex(self, vertex):
        """Add vertex to graph."""
        if vertex not in self.adj_list:
            self.adj_list[vertex] = []
    
    def add_edge(self, u, v, weight=1):
        """Add edge between vertices u and v."""
        if u not in self.adj_list:
            self.add_vertex(u)
        if v not in self.adj_list:
            self.add_vertex(v)
        
        self.adj_list[u].append((v, weight))
        # For undirected graph: self.adj_list[v].append((u, weight))
    
    def remove_edge(self, u, v):
        """Remove edge between u and v."""
        if u in self.adj_list:
            self.adj_list[u] = [(vertex, w) for vertex, w in self.adj_list[u] if vertex != v]
        # For undirected: also remove from v's list
    
    def get_neighbors(self, u):
        """Get neighbors of vertex u."""
        return [vertex for vertex, _ in self.adj_list.get(u, [])]
    
    def get_weight(self, u, v):
        """Get weight of edge between u and v."""
        for vertex, weight in self.adj_list.get(u, []):
            if vertex == v:
                return weight
        return None
    
    def display(self):
        """Display adjacency list."""
        for vertex, neighbors in self.adj_list.items():
            print(f"{vertex}: {neighbors}")

# Usage
graph = GraphList()
graph.add_edge('A', 'B', 4)
graph.add_edge('A', 'C', 2)
graph.add_edge('B', 'C', 5)
graph.add_edge('B', 'D', 10)
graph.add_edge('C', 'D', 3)

print("Adjacency List:")
graph.display()
print("Neighbors of A:", graph.get_neighbors('A'))
print("Weight A->B:", graph.get_weight('A', 'B'))
```

#### Graph Traversal Algorithms

##### Depth-First Search (DFS)
```python
def dfs_recursive(graph, start, visited=None):
    """DFS using recursion."""
    if visited is None:
        visited = set()
    
    visited.add(start)
    print(start, end=" ")
    
    for neighbor in graph.get(start, []):
        vertex = neighbor[0] if isinstance(neighbor, tuple) else neighbor
        if vertex not in visited:
            dfs_recursive(graph, vertex, visited)

def dfs_iterative(graph, start):
    """DFS using stack."""
    visited = set()
    stack = [start]
    
    while stack:
        vertex = stack.pop()
        
        if vertex not in visited:
            visited.add(vertex)
            print(vertex, end=" ")
            
            # Add neighbors to stack (reverse order for correct traversal)
            for neighbor in reversed(graph.get(vertex, [])):
                neighbor_vertex = neighbor[0] if isinstance(neighbor, tuple) else neighbor
                if neighbor_vertex not in visited:
                    stack.append(neighbor_vertex)

# Usage
graph = {
    'A': [('B', 4), ('C', 2)],
    'B': [('A', 4), ('C', 5), ('D', 10)],
    'C': [('A', 2), ('B', 5), ('D', 3)],
    'D': [('B', 10), ('C', 3)]
}

print("DFS Recursive:", end=" ")
dfs_recursive(graph, 'A')
print()

print("DFS Iterative:", end=" ")
dfs_iterative(graph, 'A')
print()
```

##### Breadth-First Search (BFS)
```python
from collections import deque

def bfs(graph, start):
    """BFS using queue."""
    visited = set()
    queue = deque([start])
    visited.add(start)
    
    while queue:
        vertex = queue.popleft()
        print(vertex, end=" ")
        
        for neighbor in graph.get(vertex, []):
            neighbor_vertex = neighbor[0] if isinstance(neighbor, tuple) else neighbor
            if neighbor_vertex not in visited:
                visited.add(neighbor_vertex)
                queue.append(neighbor_vertex)

# Usage
print("BFS:", end=" ")
bfs(graph, 'A')
print()
```

#### Shortest Path Algorithms

##### Dijkstra's Algorithm
```python
import heapq

def dijkstra(graph, start):
    """Find shortest paths from start to all vertices."""
    # Priority queue: (distance, vertex)
    pq = [(0, start)]
    distances = {vertex: float('inf') for vertex in graph}
    distances[start] = 0
    previous = {vertex: None for vertex in graph}
    
    while pq:
        current_distance, current_vertex = heapq.heappop(pq)
        
        # Skip if we found a better path already
        if current_distance > distances[current_vertex]:
            continue
        
        for neighbor, weight in graph.get(current_vertex, []):
            distance = current_distance + weight
            
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous[neighbor] = current_vertex
                heapq.heappush(pq, (distance, neighbor))
    
    return distances, previous

def get_shortest_path(previous, target):
    """Reconstruct path from start to target."""
    path = []
    current = target
    
    while current is not None:
        path.append(current)
        current = previous[current]
    
    path.reverse()
    return path

# Usage
distances, previous = dijkstra(graph, 'A')
print("Shortest distances from A:", distances)
print("Shortest path to D:", get_shortest_path(previous, 'D'))
```

### Heaps - Priority Queue Implementation

#### Binary Heap Implementation
```python
class MinHeap:
    """Min-heap implementation."""
    
    def __init__(self):
        self.heap = []
    
    def parent(self, i):
        return (i - 1) // 2
    
    def left_child(self, i):
        return 2 * i + 1
    
    def right_child(self, i):
        return 2 * i + 2
    
    def swap(self, i, j):
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]
    
    def heapify_up(self, i):
        """Maintain heap property by moving element up."""
        while i > 0 and self.heap[i] < self.heap[self.parent(i)]:
            self.swap(i, self.parent(i))
            i = self.parent(i)
    
    def heapify_down(self, i):
        """Maintain heap property by moving element down."""
        smallest = i
        left = self.left_child(i)
        right = self.right_child(i)
        
        if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
            smallest = left
        
        if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
            smallest = right
        
        if smallest != i:
            self.swap(i, smallest)
            self.heapify_down(smallest)
    
    def insert(self, value):
        """Insert value into heap."""
        self.heap.append(value)
        self.heapify_up(len(self.heap) - 1)
    
    def extract_min(self):
        """Remove and return minimum element."""
        if not self.heap:
            raise IndexError("Heap is empty")
        
        if len(self.heap) == 1:
            return self.heap.pop()
        
        min_value = self.heap[0]
        self.heap[0] = self.heap.pop()
        self.heapify_down(0)
        
        return min_value
    
    def peek(self):
        """Return minimum element without removing."""
        if not self.heap:
            raise IndexError("Heap is empty")
        return self.heap[0]
    
    def is_empty(self):
        return len(self.heap) == 0
    
    def size(self):
        return len(self.heap)

# Usage
heap = MinHeap()
heap.insert(10)
heap.insert(5)
heap.insert(15)
heap.insert(3)

print("Heap size:", heap.size())
print("Min element:", heap.peek())
print("Extract min:", heap.extract_min())
print("New min:", heap.peek())
```

### Disjoint Sets (Union-Find) - Cycle Detection

```python
class DisjointSet:
    """Disjoint set data structure for cycle detection."""
    
    def __init__(self, vertices):
        self.parent = {v: v for v in vertices}
        self.rank = {v: 0 for v in vertices}
    
    def find(self, vertex):
        """Find root parent with path compression."""
        if self.parent[vertex] != vertex:
            self.parent[vertex] = self.find(self.parent[vertex])
        return self.parent[vertex]
    
    def union(self, x, y):
        """Union two sets by rank."""
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x != root_y:
            # Attach smaller rank tree under root of higher rank tree
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1
    
    def connected(self, x, y):
        """Check if two vertices are in same set."""
        return self.find(x) == self.find(y)

# Cycle detection in undirected graph
def has_cycle(graph):
    """Detect cycle using disjoint sets."""
    vertices = list(graph.keys())
    ds = DisjointSet(vertices)
    
    for u in graph:
        for v, _ in graph[u]:
            if u < v:  # Process each edge once
                if ds.connected(u, v):
                    return True
                ds.union(u, v)
    
    return False

# Usage
cycle_graph = {
    'A': [('B', 1), ('C', 1)],
    'B': [('A', 1), ('C', 1)],
    'C': [('A', 1), ('B', 1)]
}

no_cycle_graph = {
    'A': [('B', 1)],
    'B': [('A', 1), ('C', 1)],
    'C': [('B', 1)]
}

print("Cycle graph has cycle:", has_cycle(cycle_graph))
print("No cycle graph has cycle:", has_cycle(no_cycle_graph))
```

## Data Structure Selection Guide

### Choosing the Right Data Structure

#### Problem Characteristics to Consider
1. **Data Access Patterns**: Random vs sequential access
2. **Insertion/Deletion Frequency**: How often data changes
3. **Search Requirements**: Exact match, range queries, pattern matching
4. **Order Requirements**: Sorted vs unsorted data
5. **Memory Constraints**: Available memory vs data size
6. **Performance Requirements**: Time vs space trade-offs

#### Decision Tree for Data Structure Selection

```
Need fast search/lookup?
├── Yes → Need ordered data?
│   ├── Yes → BST, AVL Tree, or Skip List
│   └── No → Hash Table (Dictionary)
└── No → Need FIFO access?
    ├── Yes → Queue
    └── No → Need LIFO access?
        ├── Yes → Stack
        └── No → Need fast insertion/deletion?
            ├── Yes → Linked List
            └── No → Array/List
```

#### Common Use Cases and Recommendations

| Use Case | Recommended Structure | Reasoning |
|----------|----------------------|-----------|
| Phone book (name lookup) | Hash Table | Fast lookup by key |
| Task scheduler | Priority Queue | Ordered by priority |
| Undo/redo functionality | Stack | LIFO operations |
| Print job management | Queue | FIFO processing |
| File system navigation | Tree | Hierarchical structure |
| Social network | Graph | Complex relationships |
| Dictionary/spell checker | Trie | Prefix-based operations |
| Database indexes | B-Tree | Balanced, disk-efficient |
| Cache with expiration | Hash Table + TTL | Fast access with time management |
| Real-time analytics | Circular Buffer | Fixed-size, FIFO |

### Performance Comparison Matrix

| Operation | Array | Linked List | Stack | Queue | Hash Table | BST | Heap |
|-----------|-------|-------------|-------|-------|------------|-----|------|
| Access by index | O(1) | O(n) | - | - | - | - | - |
| Access by key | - | - | - | - | O(1) | O(log n) | - |
| Search | O(n) | O(n) | - | - | O(1) | O(log n) | - |
| Insert end | O(1) | O(1) | O(1) | O(1) | O(1) | O(log n) | O(log n) |
| Insert beginning | O(n) | O(1) | - | - | O(1) | O(log n) | - |
| Delete end | O(1) | O(1) | O(1) | O(1) | O(1) | O(log n) | O(log n) |
| Delete beginning | O(n) | O(1) | - | - | O(1) | O(log n) | - |
| Memory overhead | None | High | Low | Low | Medium | Medium | Low |

### Advanced Optimization Techniques

#### 1. Memory Pool Allocation
```python
class MemoryPool:
    """Memory pool for efficient object allocation."""
    
    def __init__(self, object_class, pool_size=100):
        self.object_class = object_class
        self.pool = [object_class() for _ in range(pool_size)]
        self.available = list(range(pool_size))
    
    def allocate(self):
        """Get object from pool."""
        if not self.available:
            # Pool exhausted, create new object
            return self.object_class()
        
        index = self.available.pop()
        return self.pool[index]
    
    def deallocate(self, obj):
        """Return object to pool."""
        # Find object in pool
        for i, pool_obj in enumerate(self.pool):
            if pool_obj is obj:
                self.available.append(i)
                # Reset object state if needed
                break

# Usage for frequent node allocation
node_pool = MemoryPool(TreeNode, 1000)
node = node_pool.allocate()
# Use node...
node_pool.deallocate(node)
```

#### 2. Cache-Oblivious Algorithms
- Design algorithms that work well with any cache size
- Use space-filling curves for memory access
- Optimize for sequential memory access patterns

#### 3. Concurrent Data Structures
```python
import threading

class ThreadSafeQueue:
    """Thread-safe queue implementation."""
    
    def __init__(self, max_size=None):
        self.queue = LinkedQueue()
        self.max_size = max_size
        self.lock = threading.Lock()
        self.not_empty = threading.Condition(self.lock)
        self.not_full = threading.Condition(self.lock)
    
    def enqueue(self, item, timeout=None):
        """Thread-safe enqueue."""
        with self.not_full:
            if self.max_size and self.queue.size() >= self.max_size:
                if not self.not_full.wait(timeout=timeout):
                    raise TimeoutError("Queue full")
            
            self.queue.enqueue(item)
            self.not_empty.notify()
    
    def dequeue(self, timeout=None):
        """Thread-safe dequeue."""
        with self.not_empty:
            if self.queue.is_empty():
                if not self.not_empty.wait(timeout=timeout):
                    raise TimeoutError("Queue empty")
            
            item = self.queue.dequeue()
            self.not_full.notify()
            return item

# Usage in multi-threaded environment
# Producer-consumer pattern implementation would go here
```

## Summary

Data structures are the foundation of efficient programming. From basic arrays and linked lists to complex trees, graphs, and hash tables, each structure serves specific purposes and offers different performance characteristics. Understanding when and how to use each data structure is crucial for writing efficient, scalable software.

Key concepts covered:
- **Arrays**: Contiguous memory, O(1) access, fixed size
- **Linked Lists**: Dynamic size, efficient insertions/deletions
- **Stacks**: LIFO operations, function call management
- **Queues**: FIFO operations, task scheduling
- **Trees**: Hierarchical data, fast search (BST), balanced trees (AVL)
- **Hash Tables**: Fast lookups, key-value storage
- **Graphs**: Complex relationships, traversal algorithms
- **Heaps**: Priority queues, efficient min/max operations

The choice of data structure significantly impacts program performance, memory usage, and code complexity. Always analyze your requirements and choose the most appropriate structure for your use case.

## Comprehensive Exercises

### Basic Data Structure Mastery
1. **Array Operations**: Implement dynamic array with resize operations
2. **Linked List Algorithms**: Reverse, detect cycle, find middle element
3. **Stack Applications**: Expression evaluation, bracket matching
4. **Queue Implementations**: Circular queue, deque operations

### Intermediate Challenges
5. **Tree Traversals**: Implement all four traversal methods iteratively
6. **BST Operations**: Insert, delete, find kth smallest element
7. **Hash Table Collisions**: Implement different collision resolution strategies
8. **Graph Algorithms**: DFS, BFS, shortest path, topological sort

### Advanced Problems
9. **Memory Management**: Implement garbage collection simulation
10. **Concurrent Structures**: Thread-safe data structures with locks
11. **Cache Implementation**: LRU cache with hash table and linked list
12. **Database Index**: B-tree implementation for disk-based storage

### Real-World Applications
13. **File System**: Tree structure for directory navigation
14. **Social Network**: Graph for friend connections and recommendations
15. **Web Crawler**: Queue for URL processing, set for visited URLs
16. **Compiler Symbol Table**: Hash table with scope management
17. **Text Editor**: Gap buffer or rope data structure
18. **Game Engine**: Spatial partitioning with quadtrees/octrees

### Performance Optimization
19. **Benchmarking**: Compare performance of different implementations
20. **Memory Profiling**: Analyze memory usage patterns
21. **Algorithm Tuning**: Optimize for specific use cases
22. **Cache-Friendly Code**: Improve data locality and access patterns

## Further Reading and Resources

### Classic Texts
- **"Introduction to Algorithms"** by Cormen, Leiserson, Rivest, Stein
- **"Data Structures and Algorithm Analysis"** by Mark Allen Weiss
- **"Algorithms"** by Robert Sedgewick and Kevin Wayne

### Specialized Books
- **"Purely Functional Data Structures"** by Chris Okasaki
- **"The Art of Computer Programming"** by Donald Knuth
- **"Handbook of Data Structures and Applications"** by Dinesh P. Mehta

### Online Resources
- **GeeksforGeeks**: Comprehensive tutorials and practice problems
- **LeetCode**: Algorithm and data structure problems
- **HackerRank**: Coding challenges with data structures
- **Visualgo**: Interactive algorithm visualizations

### Research Papers
- **"A Discipline of Programming"** by Edsger Dijkstra
- **"On the Entropy of Trees"** by Donald Knuth
- **"The Ubiquitous B-Tree"** by Douglas Comer

### Communities
- **Stack Overflow**: Data structure implementation questions
- **Reddit r/algorithms**: Algorithm and data structure discussions
- **GitHub**: Open source implementations and libraries

Remember: Data structures are tools in your programming toolbox. The more you understand about their strengths, weaknesses, and implementation details, the better equipped you'll be to solve complex problems efficiently. Practice implementing these structures from scratch, analyze their performance characteristics, and always consider the trade-offs when making design decisions.