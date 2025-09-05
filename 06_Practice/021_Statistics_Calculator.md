# 🎯 Practical 21: Statistics Calculator

## 📋 Problem Statement

Write a C program to find mean, variance and standard deviation.

## 🎯 Learning Objectives

- Understand statistical calculations
- Practice array operations
- Learn mathematical functions
- Understand data processing
- Practice precision handling

## 📝 Requirements

1. Accept array of numbers
2. Calculate mean
3. Calculate variance
4. Calculate standard deviation
5. Display results

## 💡 Hints

- Use arrays for data storage
- Calculate sum for mean
- Use variance formula
- Use sqrt() for standard deviation
- Handle floating point precision

## 🔧 Solution

```c
// Practical 21: Statistics Calculator
// Calculates mean, variance, and standard deviation

#include <stdio.h>
#include <math.h>

int main() {
    int n;
    float sum = 0, mean, variance = 0, std_dev;

    printf("Statistics Calculator\n");
    printf("====================\n");

    printf("Enter the number of data points: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of data points must be positive!\n");
        return 1;
    }

    float data[n];

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &data[i]);
        sum += data[i];
    }

    // Calculate mean
    mean = sum / n;

    // Calculate variance
    for (int i = 0; i < n; i++) {
        variance += pow(data[i] - mean, 2);
    }
    variance /= n;

    // Calculate standard deviation
    std_dev = sqrt(variance);

    printf("\nResults:\n");
    printf("--------\n");
    printf("Mean: %.2f\n", mean);
    printf("Variance: %.2f\n", variance);
    printf("Standard Deviation: %.2f\n", std_dev);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Data
```
Input: 5, [1, 2, 3, 4, 5]
Expected Output:
Mean: 3.00
Variance: 2.00
Standard Deviation: 1.41
```

### Test Case 2: Same Values
```
Input: 3, [5, 5, 5]
Expected Output:
Mean: 5.00
Variance: 0.00
Standard Deviation: 0.00
```

### Test Case 3: Two Values
```
Input: 2, [10, 20]
Expected Output:
Mean: 15.00
Variance: 25.00
Standard Deviation: 5.00
```

## 🔍 Explanation

1. **Input**: Number of data points and values
2. **Mean**: Average of all values
3. **Variance**: Average of squared differences from mean
4. **Std Dev**: Square root of variance
5. **Precision**: Uses float for accuracy

## 🎯 Key Concepts Covered

- Statistical calculations
- Array manipulation
- Mathematical functions
- Data processing
- Precision handling

## 🚀 Extensions

1. Calculate median and mode
2. Handle large datasets
3. Add data visualization
4. Support file input