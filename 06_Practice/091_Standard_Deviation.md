# 🎯 Practical 91: Standard Deviation

## 📋 Problem Statement

Write a C program to calculate standard deviation.

## 🎯 Learning Objectives

- Understand statistical calculations
- Practice variance and standard deviation
- Learn population vs sample formulas
- Understand data analysis
- Practice mathematical computations

## 📝 Requirements

1. Accept array of numbers
2. Calculate mean
3. Calculate variance
4. Calculate standard deviation
5. Display all results

## 💡 Hints

- Population SD: sqrt(sum((x-mean)^2)/n)
- Sample SD: sqrt(sum((x-mean)^2)/(n-1))
- Use arrays for data storage
- Calculate mean first
- Use pow() for squaring

## 🔧 Solution

```c
// Practical 91: Standard Deviation
// Calculates standard deviation of data set

#include <stdio.h>
#include <math.h>

int main() {
    int n;
    
    printf("Standard Deviation Calculator\n");
    printf("=============================\n");
    
    printf("Enter the number of data points: ");
    scanf("%d", &n);
    
    if (n <= 1) {
        printf("At least 2 data points required for standard deviation!\n");
        return 1;
    }
    
    double data[n];
    double sum = 0, mean, variance_pop = 0, variance_samp = 0;
    double std_dev_pop, std_dev_samp;
    
    // Input data
    printf("Enter %d data points:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &data[i]);
        sum += data[i];
    }
    
    // Calculate mean
    mean = sum / n;
    
    // Calculate variance
    for (int i = 0; i < n; i++) {
        double diff = data[i] - mean;
        variance_pop += diff * diff;
        variance_samp += diff * diff;
    }
    
    variance_pop /= n;           // Population variance
    variance_samp /= (n - 1);    // Sample variance
    
    // Calculate standard deviation
    std_dev_pop = sqrt(variance_pop);
    std_dev_samp = sqrt(variance_samp);
    
    // Display results
    printf("\nData points: ");
    for (int i = 0; i < n; i++) {
        printf("%.2f", data[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    
    printf("\n\nMean: %.4f\n", mean);
    printf("Population Variance: %.4f\n", variance_pop);
    printf("Sample Variance: %.4f\n", variance_samp);
    printf("Population Standard Deviation: %.4f\n", std_dev_pop);
    printf("Sample Standard Deviation: %.4f\n", std_dev_samp);
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Data
```
Input: n=5, data=[10, 12, 14, 16, 18]
Expected Output:
Mean: 14.0000
Population Standard Deviation: 2.8284
Sample Standard Deviation: 3.1623
```

### Test Case 2: Same Values
```
Input: n=4, data=[5, 5, 5, 5]
Expected Output:
Mean: 5.0000
Population Standard Deviation: 0.0000
Sample Standard Deviation: 0.0000
```

### Test Case 3: Mixed Values
```
Input: n=3, data=[1, 3, 7]
Expected Output:
Mean: 3.6667
Population Standard Deviation: 2.4944
Sample Standard Deviation: 3.2146
```

## 🔍 Explanation

1. **Mean Calculation**: sum / n
2. **Variance**: Average of squared differences from mean
3. **Population SD**: Uses n in denominator
4. **Sample SD**: Uses n-1 in denominator
5. **Standard Deviation**: Square root of variance

## 🎯 Key Concepts Covered

- Statistical calculations
- Population vs sample statistics
- Variance and standard deviation
- Data analysis
- Mathematical precision

## 🚀 Extensions

1. Calculate confidence intervals
2. Handle large datasets
3. Add data visualization
4. Calculate other statistical measures