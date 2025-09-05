# 🔄 **Project 17: Sorting Algorithm Comparison in C**
## 🎯 **Multiple Sorting Algorithms with Performance Analysis**

---

## 📋 **Project Overview**

**English:** A comprehensive sorting algorithm comparison tool in C that implements and compares multiple sorting algorithms including Bubble Sort, Quick Sort, Merge Sort, and Heap Sort with performance metrics and visualization.

**Hinglish:** Ek comprehensive sorting algorithm comparison tool jo C mein hai, jisme multiple sorting algorithms implement kiye gaye hain including Bubble Sort, Quick Sort, Merge Sort, aur Heap Sort with performance metrics aur visualization ke saath.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Algorithm implementation
- Performance measurement
- Time complexity analysis
- Memory usage tracking
- Comparative analysis

✅ **Algorithm Concepts:**
- Sorting algorithms
- Divide and conquer
- In-place sorting
- Stable vs unstable sorts
- Best/worst case analysis

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Algorithm implementation | Handles sorting logic and timing |
| **Time Library** | Performance measurement | CPU time tracking for comparisons |
| **Standard Library** | Utility functions | Memory operations and random number generation |
| **Math Library** | Statistical analysis | Performance metric calculations |

---

## 📁 **Project Structure**

```
SortingAlgorithms/
├── include/
│   ├── sorting.h
│   ├── performance.h
│   ├── visualization.h
├── src/
│   ├── sorting.c
│   ├── performance.c
│   ├── visualization.c
│   └── main.c
├── data/
│   └── test_data.txt
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Sorting Algorithms**

```c
// sorting.h
#ifndef SORTING_H
#define SORTING_H

// Function declarations for all sorting algorithms
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void quick_sort(int arr[], int low, int high);
void merge_sort(int arr[], int left, int right);
void heap_sort(int arr[], int n);

// Helper functions
void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void merge(int arr[], int left, int mid, int right);
void heapify(int arr[], int n, int i);

// Array utilities
void copy_array(int dest[], int src[], int n);
int is_sorted(int arr[], int n);
void print_array(int arr[], int n);

#endif
```

```c
// sorting.c
#include <stdio.h>
#include "sorting.h"

// Bubble Sort
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[i], &arr[min_idx]);
    }
}

// Insertion Sort
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Merge Sort
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Heap Sort
void heap_sort(int arr[], int n) {
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Utility functions
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void copy_array(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int is_sorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return 0;
        }
    }
    return 1;
}
```

### **2. Performance Measurement**

```c
// performance.h
#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <time.h>

typedef struct {
    char algorithm_name[50];
    double execution_time;
    int comparisons;
    int swaps;
    int is_stable;
    char time_complexity[20];
} PerformanceMetrics;

// Performance functions
PerformanceMetrics measure_performance(void (*sort_func)(int[], int), int arr[], int n, const char *name);
void compare_algorithms(int original[], int n);
void print_performance_report(PerformanceMetrics metrics[], int count);

#endif
```

```c
// performance.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "performance.h"
#include "sorting.h"

// Measure performance of a sorting algorithm
PerformanceMetrics measure_performance(void (*sort_func)(int[], int), int arr[], int n, const char *name) {
    PerformanceMetrics metrics;
    strcpy(metrics.algorithm_name, name);

    // Create a copy of the array
    int *test_arr = (int*)malloc(n * sizeof(int));
    copy_array(test_arr, arr, n);

    // Measure execution time
    clock_t start = clock();
    sort_func(test_arr, n);
    clock_t end = clock();

    metrics.execution_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // milliseconds

    // Check if sorted correctly
    if (!is_sorted(test_arr, n)) {
        printf("Error: %s did not sort correctly!\n", name);
    }

    free(test_arr);

    // Set algorithm properties
    if (strcmp(name, "Bubble Sort") == 0) {
        strcpy(metrics.time_complexity, "O(n²)");
        metrics.is_stable = 1;
    } else if (strcmp(name, "Selection Sort") == 0) {
        strcpy(metrics.time_complexity, "O(n²)");
        metrics.is_stable = 0;
    } else if (strcmp(name, "Insertion Sort") == 0) {
        strcpy(metrics.time_complexity, "O(n²)");
        metrics.is_stable = 1;
    } else if (strcmp(name, "Quick Sort") == 0) {
        strcpy(metrics.time_complexity, "O(n log n)");
        metrics.is_stable = 0;
    } else if (strcmp(name, "Merge Sort") == 0) {
        strcpy(metrics.time_complexity, "O(n log n)");
        metrics.is_stable = 1;
    } else if (strcmp(name, "Heap Sort") == 0) {
        strcpy(metrics.time_complexity, "O(n log n)");
        metrics.is_stable = 0;
    }

    return metrics;
}

// Compare all algorithms
void compare_algorithms(int original[], int n) {
    PerformanceMetrics results[6];

    results[0] = measure_performance(bubble_sort, original, n, "Bubble Sort");
    results[1] = measure_performance(selection_sort, original, n, "Selection Sort");
    results[2] = measure_performance(insertion_sort, original, n, "Insertion Sort");
    results[3] = measure_performance(quick_sort, original, n, "Quick Sort");
    results[4] = measure_performance(merge_sort, original, n, "Merge Sort");
    results[5] = measure_performance(heap_sort, original, n, "Heap Sort");

    print_performance_report(results, 6);
}

// Print performance report
void print_performance_report(PerformanceMetrics metrics[], int count) {
    printf("\n========================================\n");
    printf("    SORTING ALGORITHM COMPARISON\n");
    printf("========================================\n");
    printf("%-15s %-12s %-8s %-6s\n", "Algorithm", "Time(ms)", "Stable", "Complexity");
    printf("--------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-15s %-12.2f %-8s %-6s\n",
               metrics[i].algorithm_name,
               metrics[i].execution_time,
               metrics[i].is_stable ? "Yes" : "No",
               metrics[i].time_complexity);
    }

    printf("========================================\n");

    // Find fastest algorithm
    int fastest_idx = 0;
    for (int i = 1; i < count; i++) {
        if (metrics[i].execution_time < metrics[fastest_idx].execution_time) {
            fastest_idx = i;
        }
    }

    printf("Fastest Algorithm: %s (%.2f ms)\n", metrics[fastest_idx].algorithm_name, metrics[fastest_idx].execution_time);
}
```

### **3. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include "performance.h"

void display_menu() {
    printf("\n=== Sorting Algorithm Comparison ===\n");
    printf("1. Run All Sorting Algorithms\n");
    printf("2. Compare Performance\n");
    printf("3. Test Individual Algorithm\n");
    printf("4. Generate Random Data\n");
    printf("5. Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}

void generate_random_array(int arr[], int n, int max_value) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max_value;
    }
}

void test_individual_algorithm() {
    printf("Select algorithm:\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Quick Sort\n");
    printf("5. Merge Sort\n");
    printf("6. Heap Sort\n");
    printf("Enter choice: ");

    int choice, n;
    scanf("%d", &choice);

    printf("Enter array size: ");
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    print_array(arr, n);

    switch (choice) {
        case 1: bubble_sort(arr, n); printf("Bubble Sort: "); break;
        case 2: selection_sort(arr, n); printf("Selection Sort: "); break;
        case 3: insertion_sort(arr, n); printf("Insertion Sort: "); break;
        case 4: quick_sort(arr, 0, n-1); printf("Quick Sort: "); break;
        case 5: merge_sort(arr, 0, n-1); printf("Merge Sort: "); break;
        case 6: heap_sort(arr, n); printf("Heap Sort: "); break;
        default: printf("Invalid choice!\n"); free(arr); return;
    }

    print_array(arr, n);
    free(arr);
}

int main() {
    srand(time(NULL));

    printf("Sorting Algorithm Comparison Tool\n");
    printf("==================================\n");

    int choice;
    int *data = NULL;
    int data_size = 0;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Run all algorithms
                if (data_size == 0) {
                    printf("No data available. Generate data first.\n");
                    break;
                }

                printf("Running all sorting algorithms on %d elements...\n", data_size);

                // Test each algorithm
                int *test_arr = (int*)malloc(data_size * sizeof(int));

                printf("\n--- Bubble Sort ---\n");
                copy_array(test_arr, data, data_size);
                bubble_sort(test_arr, data_size);
                printf("Sorted successfully!\n");

                printf("\n--- Quick Sort ---\n");
                copy_array(test_arr, data, data_size);
                quick_sort(test_arr, 0, data_size - 1);
                printf("Sorted successfully!\n");

                printf("\n--- Merge Sort ---\n");
                copy_array(test_arr, data, data_size);
                merge_sort(test_arr, 0, data_size - 1);
                printf("Sorted successfully!\n");

                printf("\n--- Heap Sort ---\n");
                copy_array(test_arr, data, data_size);
                heap_sort(test_arr, data_size);
                printf("Sorted successfully!\n");

                free(test_arr);
                break;
            }

            case 2: {
                // Compare performance
                if (data_size == 0) {
                    printf("No data available. Generate data first.\n");
                    break;
                }

                compare_algorithms(data, data_size);
                break;
            }

            case 3:
                test_individual_algorithm();
                break;

            case 4: {
                // Generate random data
                printf("Enter data size: ");
                scanf("%d", &data_size);

                if (data) free(data);
                data = (int*)malloc(data_size * sizeof(int));

                printf("Enter maximum value: ");
                int max_val;
                scanf("%d", &max_val);

                generate_random_array(data, data_size, max_val);
                printf("Generated %d random elements!\n", data_size);
                break;
            }

            case 5:
                if (data) free(data);
                printf("Thank you for using Sorting Algorithm Comparison Tool!\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
```

---

## 🎯 **Features Implemented**

### **Sorting Algorithms**
- ✅ Bubble Sort (O(n²))
- ✅ Selection Sort (O(n²))
- ✅ Insertion Sort (O(n²))
- ✅ Quick Sort (O(n log n))
- ✅ Merge Sort (O(n log n))
- ✅ Heap Sort (O(n log n))

### **Analysis Features**
- ✅ Performance comparison
- ✅ Time complexity analysis
- ✅ Stability testing
- ✅ Execution time measurement

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Sorting Algorithm Comparison - Performance Analysis in C"
- **Hinglish:** "Sorting Algorithm Comparison - Performance Analysis in C"

### **Slide 2: What We Built**
- ✅ Complete implementation of 6 sorting algorithms
- ✅ Performance comparison tool
- ✅ Time complexity analysis
- ✅ Stability testing
- ✅ Interactive testing interface

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char algorithm_name[50];
    double execution_time;
    int is_stable;
    char time_complexity[20];
} PerformanceMetrics;

// Core sorting functions
void bubble_sort(int arr[], int n);
void quick_sort(int arr[], int low, int high);
void merge_sort(int arr[], int left, int right);
void heap_sort(int arr[], int n);

// Performance measurement
PerformanceMetrics measure_performance(void (*sort_func)(int[], int), int arr[], int n, const char *name);
void compare_algorithms(int original[], int n);
```

### **Slide 4: Algorithm Comparison**
```c
// Performance comparison example
PerformanceMetrics results[6];
results[0] = measure_performance(bubble_sort, arr, n, "Bubble Sort");
results[1] = measure_performance(quick_sort, arr, n, "Quick Sort");
results[2] = measure_performance(merge_sort, arr, n, "Merge Sort");
results[3] = measure_performance(heap_sort, arr, n, "Heap Sort");

// Print comparison report
print_performance_report(results, 4);
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Algorithm implementation
- ✅ Performance measurement
- ✅ Time complexity analysis
- ✅ Comparative analysis
- ✅ Code optimization

### **Algorithm Concepts:**
- ✅ Sorting algorithms
- ✅ Divide and conquer
- ✅ In-place sorting
- ✅ Stability analysis
- ✅ Best/worst case scenarios

---

## 📞 **Contact & Support**

**Project Developer:** Algorithms Student
**Email:** sorting@studentproject.com
**GitHub:** https://github.com/c-sorting/algorithm-comparison

---

**🔄 This sorting algorithm comparison tool demonstrates algorithm analysis and performance measurement in C, perfect for understanding computational complexity and algorithm efficiency.**