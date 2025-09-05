# 📊 Lesson 8: Arrays in C
## Working with Collections of Data

---

## 🎯 Learning Objectives

- Understand array declaration and initialization
- Master multi-dimensional arrays
- Learn array operations and manipulation
- Understand passing arrays to functions
- Avoid common array pitfalls

---

## 📖 Arrays Kya Hain?

**Arrays** basically same type ke data items ka collection hota hai jo contiguous memory locations mein store hota hai. Ye ek single variable name ke under multiple values store karne deta hai.

### **Array ki Characteristics**
- **Fixed Size**: Size compile time pe decide hota hai
- **Homogeneous**: Saare elements same data type ke
- **Contiguous Memory**: Elements sequentially store hote hain
- **Zero-based Indexing**: First element index 0 pe hota hai

### **Array ki Types**
- **Static Arrays**: Fixed size, compile time allocation
- **Dynamic Arrays**: Runtime pe size change kar sakte hain
- **Multi-dimensional Arrays**: 2D, 3D arrays for complex data
- **Variable Length Arrays (VLA)**: C99 feature, runtime size

---

## 🔢 One-Dimensional Arrays

### **Array Declaration**
```c
// Syntax: data_type array_name[size];

// Examples
int numbers[5];           // Array of 5 integers
float prices[10];         // Array of 10 floats
char name[20];            // Array of 20 characters
double values[100];       // Array of 100 doubles
```

### **Array Initialization**
```c
#include <stdio.h>

int main() {
    // Method 1: Initialize with values
    int arr1[5] = {1, 2, 3, 4, 5};

    // Method 2: Partial initialization (remaining elements 0)
    int arr2[5] = {1, 2};  // arr2[2], arr2[3], arr2[4] = 0

    // Method 3: Initialize all elements to 0
    int arr3[5] = {0};

    // Method 4: Size determined by initializer
    int arr4[] = {10, 20, 30, 40, 50};  // Size = 5

    // Character array (string)
    char greeting[] = "Hello";  // Size = 6 (including '\0')

    return 0;
}
```

### **Array Access and Modification**
```c
#include <stdio.h>

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};

    // Access elements
    printf("First element: %d\n", numbers[0]);
    printf("Third element: %d\n", numbers[2]);

    // Modify elements
    numbers[1] = 25;
    numbers[4] = 55;

    // Display all elements
    printf("Array elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
```

---

## 📐 Multi-Dimensional Arrays

### **Two-Dimensional Arrays**
```c
#include <stdio.h>

int main() {
    // Declaration: data_type array_name[rows][columns]
    int matrix[3][4];

    // Initialization
    int matrix2[2][3] = {
        {1, 2, 3},      // Row 0
        {4, 5, 6}       // Row 1
    };

    // Partial initialization
    int matrix3[3][3] = {
        {1, 2},
        {4}
    };  // Remaining elements = 0

    // Access elements
    printf("Element at [1][2]: %d\n", matrix2[1][2]);  // 6

    // Modify elements
    matrix2[0][1] = 10;

    return 0;
}
```

### **Three-Dimensional Arrays**
```c
#include <stdio.h>

int main() {
    // Declaration: data_type array_name[x][y][z]
    int cube[2][3][4];

    // Initialization
    int cube2[2][2][2] = {
        {   // Layer 0
            {1, 2},     // Row 0
            {3, 4}      // Row 1
        },
        {   // Layer 1
            {5, 6},     // Row 0
            {7, 8}      // Row 1
        }
    };

    // Access elements
    printf("Element at [1][0][1]: %d\n", cube2[1][0][1]);  // 6

    return 0;
}
```

---

## 🔄 Array Operations

### **1. Traversing Arrays**
```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Method 1: for loop
    printf("Using for loop: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Method 2: while loop
    printf("Using while loop: ");
    int i = 0;
    while (i < size) {
        printf("%d ", arr[i]);
        i++;
    }
    printf("\n");

    return 0;
}
```

### **2. Finding Maximum/Minimum**
```c
#include <stdio.h>

int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int find_min(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    int numbers[] = {12, 45, 23, 67, 34, 89, 15};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Maximum: %d\n", find_max(numbers, size));
    printf("Minimum: %d\n", find_min(numbers, size));

    return 0;
}
```

### **3. Linear Search**
```c
#include <stdio.h>

int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 30;

    int result = linear_search(arr, size, target);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
```

### **4. Array Reversal**
```c
#include <stdio.h>

void reverse_array(int arr[], int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        // Swap elements
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    print_array(arr, size);

    reverse_array(arr, size);

    printf("Reversed array: ");
    print_array(arr, size);

    return 0;
}
```

### **5. Binary Search (Sorted Array)**
```c
#include <stdio.h>

// Iterative binary search
int binary_search_iterative(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;  // Found
        } else if (arr[mid] < target) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }

    return -1;  // Not found
}

// Recursive binary search
int binary_search_recursive(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;  // Base case: not found
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;  // Found
    } else if (arr[mid] < target) {
        return binary_search_recursive(arr, mid + 1, right, target);
    } else {
        return binary_search_recursive(arr, left, mid - 1, target);
    }
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 23;

    // Iterative search
    int result1 = binary_search_iterative(arr, size, target);
    printf("Iterative: Element found at index %d\n", result1);

    // Recursive search
    int result2 = binary_search_recursive(arr, 0, size - 1, target);
    printf("Recursive: Element found at index %d\n", result2);

    return 0;
}
```

### **6. Bubble Sort**
```c
#include <stdio.h>

void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int swapped = 0;  // Optimization flag

        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        // If no swaps occurred, array is already sorted
        if (swapped == 0) {
            break;
        }
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    print_array(arr, size);

    bubble_sort(arr, size);

    printf("Sorted array: ");
    print_array(arr, size);

    return 0;
}
```

### **7. Selection Sort**
```c
#include <stdio.h>

void selection_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;

        // Find minimum element in unsorted part
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        // Swap minimum element with first element of unsorted part
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    print_array(arr, size);

    selection_sort(arr, size);

    printf("Sorted array: ");
    print_array(arr, size);

    return 0;
}
```

### **8. Array Rotation**
```c
#include <stdio.h>

// Rotate array to the left by k positions
void rotate_left(int arr[], int size, int k) {
    k = k % size;  // Handle k > size

    // Reverse entire array
    reverse_array(arr, 0, size - 1);

    // Reverse first k elements
    reverse_array(arr, 0, k - 1);

    // Reverse remaining elements
    reverse_array(arr, k, size - 1);
}

// Rotate array to the right by k positions
void rotate_right(int arr[], int size, int k) {
    k = k % size;

    // Reverse entire array
    reverse_array(arr, 0, size - 1);

    // Reverse first (size - k) elements
    reverse_array(arr, 0, size - k - 1);

    // Reverse remaining k elements
    reverse_array(arr, size - k, size - 1);
}

// Helper function to reverse subarray
void reverse_array(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    printf("Original array: ");
    print_array(arr, size);

    rotate_left(arr, size, k);
    printf("After left rotation by %d: ", k);
    print_array(arr, size);

    rotate_right(arr, size, k);
    printf("After right rotation by %d: ", k);
    print_array(arr, size);

    return 0;
}
```

### **9. Remove Duplicates from Sorted Array**
```c
#include <stdio.h>

// Function to remove duplicates from sorted array
int remove_duplicates(int arr[], int size) {
    if (size == 0 || size == 1) {
        return size;
    }

    int j = 0;  // Index for unique elements

    for (int i = 0; i < size - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }

    arr[j++] = arr[size - 1];  // Last element
    return j;
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    print_array(arr, size);

    int new_size = remove_duplicates(arr, size);

    printf("After removing duplicates: ");
    print_array(arr, new_size);

    printf("New size: %d\n", new_size);

    return 0;
}
```

### **10. Find Missing Number**
```c
#include <stdio.h>

// Method 1: Using sum formula
int find_missing_sum(int arr[], int size) {
    int expected_sum = (size + 1) * (size + 2) / 2;
    int actual_sum = 0;

    for (int i = 0; i < size; i++) {
        actual_sum += arr[i];
    }

    return expected_sum - actual_sum;
}

// Method 2: Using XOR
int find_missing_xor(int arr[], int size) {
    int xor_all = 0;
    int xor_array = 0;

    // XOR all numbers from 1 to n+1
    for (int i = 1; i <= size + 1; i++) {
        xor_all ^= i;
    }

    // XOR all elements in array
    for (int i = 0; i < size; i++) {
        xor_array ^= arr[i];
    }

    return xor_all ^ xor_array;
}

int main() {
    int arr[] = {1, 2, 4, 5, 6};  // Missing: 3
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Missing number (sum method): %d\n", find_missing_sum(arr, size));
    printf("Missing number (XOR method): %d\n", find_missing_xor(arr, size));

    return 0;
}
```

---

## 📈 Matrix Operations

### **Matrix Addition**
```c
#include <stdio.h>

#define ROWS 3
#define COLS 3

void add_matrices(int mat1[][COLS], int mat2[][COLS], int result[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void print_matrix(int mat[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int mat1[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int mat2[ROWS][COLS] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int result[ROWS][COLS];

    add_matrices(mat1, mat2, result);

    printf("Matrix 1:\n");
    print_matrix(mat1);

    printf("\nMatrix 2:\n");
    print_matrix(mat2);

    printf("\nSum:\n");
    print_matrix(result);

    return 0;
}
```

### **Advanced Matrix Operations**

#### **Matrix Determinant (2x2)**
```c
#include <stdio.h>

int determinant_2x2(int mat[2][2]) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

int main() {
    int mat[2][2] = {
        {4, 3},
        {2, 1}
    };

    printf("Matrix:\n");
    printf("%d %d\n", mat[0][0], mat[0][1]);
    printf("%d %d\n", mat[1][0], mat[1][1]);

    printf("Determinant: %d\n", determinant_2x2(mat));

    return 0;
}
```

#### **Matrix Scalar Operations**
```c
#include <stdio.h>
#define ROWS 3
#define COLS 3

// Scalar multiplication
void scalar_multiply(int mat[][COLS], int scalar) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mat[i][j] *= scalar;
        }
    }
}

void print_matrix(int mat[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int mat[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("Original matrix:\n");
    print_matrix(mat);

    scalar_multiply(mat, 2);
    printf("\nAfter scalar multiplication by 2:\n");
    print_matrix(mat);

    return 0;
}
```

### **Matrix Transpose**
```c
#include <stdio.h>

#define ROWS 3
#define COLS 2

void transpose_matrix(int mat[][COLS], int result[][ROWS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[j][i] = mat[i][j];
        }
    }
}

void print_matrix_2x3(int mat[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void print_matrix_3x2(int mat[][ROWS]) {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int mat[ROWS][COLS] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    int transpose[COLS][ROWS];

    transpose_matrix(mat, transpose);

    printf("Original Matrix:\n");
    print_matrix_2x3(mat);

    printf("\nTransposed Matrix:\n");
    print_matrix_3x2(transpose);

    return 0;
}
```

### **Matrix Multiplication**
```c
#include <stdio.h>

#define ROWS1 2
#define COLS1 3
#define ROWS2 3
#define COLS2 2

void multiply_matrices(int mat1[][COLS1], int mat2[][COLS2], int result[][COLS2]) {
    for (int i = 0; i < ROWS1; i++) {
        for (int j = 0; j < COLS2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COLS1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void print_matrix_2x2(int mat[][COLS2]) {
    for (int i = 0; i < ROWS1; i++) {
        for (int j = 0; j < COLS2; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int mat1[ROWS1][COLS1] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int mat2[ROWS2][COLS2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    int result[ROWS1][COLS2];

    multiply_matrices(mat1, mat2, result);

    printf("Result of multiplication:\n");
    print_matrix_2x2(result);

    return 0;
}
```

---

## 🔗 Passing Arrays to Functions

### **1. Passing 1D Arrays**
```c
#include <stdio.h>

// Method 1: Using array notation
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Method 2: Using pointer notation
void print_array_ptr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    print_array(numbers, size);
    print_array_ptr(numbers, size);

    return 0;
}
```

### **2. Passing 2D Arrays**
```c
#include <stdio.h>

#define ROWS 3
#define COLS 3

// Method 1: Fixed size
void print_matrix_fixed(int mat[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

// Method 2: Variable columns
void print_matrix_var(int mat[][COLS], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    print_matrix_fixed(matrix);
    printf("\n");
    print_matrix_var(matrix, ROWS);

    return 0;
}
```

### **3. Returning Arrays from Functions**
```c
#include <stdio.h>

// Method 1: Return pointer to static array
int* get_static_array() {
    static int arr[5] = {1, 2, 3, 4, 5};
    return arr;
}

// Method 2: Pass array as parameter and modify
void fill_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * i;
    }
}

int main() {
    // Method 1
    int *static_arr = get_static_array();
    printf("Static array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", static_arr[i]);
    }
    printf("\n");

    // Method 2
    int dynamic_arr[5];
    fill_array(dynamic_arr, 5);
    printf("Dynamic array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dynamic_arr[i]);
    }
    printf("\n");

    return 0;
}
```

---

## ⚠️ Common Array Mistakes

### **1. Array Index Out of Bounds**
```c
#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    // Error: Accessing beyond array bounds
    printf("%d\n", arr[5]);    // Undefined behavior
    printf("%d\n", arr[-1]);   // Undefined behavior

    // Correct: Check bounds
    int index = 3;
    if (index >= 0 && index < 5) {
        printf("%d\n", arr[index]);
    }

    return 0;
}
```

### **2. Incorrect Array Size Calculation**
```c
#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    // Wrong: Using sizeof(arr) in function
    // This will give size of pointer, not array

    // Correct: Calculate size in same scope
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Array size: %d\n", size);

    return 0;
}
```

### **3. String Array Issues**
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[10];

    // Error: No bounds checking
    strcpy(str, "This is a very long string that will overflow");

    // Correct: Use strncpy with bounds checking
    strncpy(str, "This is safe", sizeof(str) - 1);
    str[sizeof(str) - 1] = '\0';  // Ensure null termination

    printf("%s\n", str);

    return 0;
}
```

### **4. Multi-dimensional Array Confusion**
```c
#include <stdio.h>

int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};

    // Correct access
    printf("%d\n", arr[1][2]);  // 6

    // Wrong: arr[1, 2] is not valid in C
    // printf("%d\n", arr[1, 2]);  // Error!

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Always Check Bounds**
```c
// ✅ Safe array access
int safe_get(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        printf("Index out of bounds\n");
        return -1;
    }
    return arr[index];
}
```

### **2. Use const for Read-only Arrays**
```c
// ✅ Prevent accidental modification
void print_array(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        // arr[i] = 10;  // Error: cannot modify const array
    }
}
```

### **3. Initialize Arrays Properly**
```c
// ✅ Complete initialization
int arr1[5] = {1, 2, 3, 4, 5};
int arr2[5] = {0};  // All elements 0
int arr3[] = {1, 2, 3};  // Size automatically determined

// ❌ Partial initialization without care
int arr4[5] = {1, 2};  // arr4[2], arr4[3], arr4[4] are garbage
```

### **4. Use Meaningful Names**
```c
// ✅ Descriptive names
int student_marks[50];
float product_prices[100];
char employee_names[50][30];

// ❌ Generic names
int a[10];
float b[20];
char c[5][10];
```

---

## 📝 Practice Exercises

### **Exercise 1: Array Operations**
Create functions for:
- Find second largest element
- Remove duplicates from array
- Rotate array by k positions
- Find intersection of two arrays

### **Exercise 2: Matrix Operations**
Implement:
- Matrix scalar multiplication
- Check if matrix is identity
- Find transpose without extra space
- Matrix-vector multiplication

### **Exercise 3: String Arrays**
Create programs for:
- Sort array of strings
- Find longest common prefix
- Group anagrams together
- Implement simple spell checker

### **Exercise 4: Advanced Arrays**
Build:
- Dynamic array implementation
- Sparse matrix representation
- Array-based stack and queue
- Binary search on rotated array

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the index of the first element in a C array?
a) 1
b) -1
c) 0
d) Random

### **Question 2:**
Which of these correctly declares a 2D array?
a) `int arr[2,3];`
b) `int arr[2][3];`
c) `int arr(2)(3);`
d) `int arr{2}{3};`

### **Question 3:**
What happens when you access an array out of bounds?
a) Compilation error
b) Runtime error
c) Undefined behavior
d) Program terminates safely

### **Question 4:**
How do you find the number of elements in an array?
a) `sizeof(arr)`
b) `sizeof(arr) / sizeof(arr[0])`
c) `length(arr)`
d) `arr.size()`

### **Question 5:**
Which is the correct way to pass an array to a function?
a) `void func(int arr[])`
b) `void func(int arr[10])`
c) `void func(int *arr)`
d) All of the above

---

## 🔗 Additional Resources

### **Array Algorithms**
- [Array Sorting Algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm)
- [Array Searching Algorithms](https://en.wikipedia.org/wiki/Search_algorithm)
- [Matrix Operations](https://en.wikipedia.org/wiki/Matrix_(mathematics))

### **Further Reading**
- [Arrays in C](https://en.cppreference.com/w/c/language/array)
- [Multidimensional Arrays](https://www.programiz.com/c-programming/c-multi-dimensional-arrays)
- [Array Best Practices](https://www.geeksforgeeks.org/c-arrays/)

---

## 🎯 Next Steps

**Great job!** You've mastered:
- ✅ Array declaration and initialization
- ✅ Multi-dimensional arrays
- ✅ Array operations and algorithms
- ✅ Matrix operations
- ✅ Passing arrays to functions
- ✅ Common array pitfalls

**Next Lesson Preview:**
- Strings and string manipulation
- Standard string functions
- String algorithms
- Character array operations

---

**🚀 Ready to work with strings?**

[⬅️ Previous: Functions](07_Functions.md) | [Next: Strings ➡️](09_Strings.md)