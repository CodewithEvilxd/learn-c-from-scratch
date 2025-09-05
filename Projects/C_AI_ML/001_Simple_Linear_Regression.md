# 🤖 Simple Linear Regression in C
## Implement machine learning algorithms from scratch

---

## 📋 Project Overview

This project implements a simple linear regression algorithm in pure C without any external libraries. Linear regression is a fundamental machine learning algorithm used for predicting continuous values based on input features.

## 🎯 Learning Objectives

- Understand linear regression mathematics
- Implement gradient descent algorithm
- Practice numerical computing in C
- Learn data preprocessing techniques
- Understand model evaluation metrics

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Libraries**: Standard C libraries only (math.h, stdio.h, stdlib.h)
- **Platform**: Cross-platform (Windows/Linux/macOS)
- **Compiler**: GCC, Clang, or MSVC

## 📁 Project Structure

```
linear_regression/
├── src/
│   ├── main.c              # Main program and data loading
│   ├── linear_regression.c # Core algorithm implementation
│   ├── data_processing.c   # Data preprocessing utilities
│   ├── metrics.c          # Model evaluation functions
│   └── utils.c            # Helper functions
├── include/
│   ├── linear_regression.h
│   ├── data_processing.h
│   ├── metrics.h
│   └── utils.h
├── data/
│   ├── train.csv          # Training data
│   └── test.csv           # Test data
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Data Structures**

```c
// linear_regression.h
#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SAMPLES 10000
#define MAX_FEATURES 100

typedef struct {
    double** X;        // Feature matrix [n_samples][n_features]
    double* y;         // Target values [n_samples]
    int n_samples;     // Number of training samples
    int n_features;    // Number of features
} Dataset;

typedef struct {
    double* weights;   // Model weights [n_features + 1]
    double bias;       // Bias term
    int n_features;    // Number of features
} LinearRegression;

typedef struct {
    double mse;        // Mean Squared Error
    double rmse;       // Root Mean Squared Error
    double mae;        // Mean Absolute Error
    double r2_score;   // R-squared score
} ModelMetrics;

// Function prototypes
LinearRegression* create_model(int n_features);
void free_model(LinearRegression* model);
Dataset* load_dataset(const char* filename);
void free_dataset(Dataset* dataset);
void fit(LinearRegression* model, Dataset* dataset, double learning_rate, int n_iterations);
double predict(LinearRegression* model, double* features);
ModelMetrics evaluate(LinearRegression* model, Dataset* dataset);

#endif
```

### **Step 2: Core Algorithm Implementation**

```c
// linear_regression.c
#include "linear_regression.h"

LinearRegression* create_model(int n_features) {
    LinearRegression* model = (LinearRegression*)malloc(sizeof(LinearRegression));
    if (!model) return NULL;

    model->n_features = n_features;
    model->weights = (double*)calloc(n_features + 1, sizeof(double));
    if (!model->weights) {
        free(model);
        return NULL;
    }

    model->bias = 0.0;
    return model;
}

void free_model(LinearRegression* model) {
    if (model) {
        free(model->weights);
        free(model);
    }
}

void fit(LinearRegression* model, Dataset* dataset, double learning_rate, int n_iterations) {
    int n_samples = dataset->n_samples;
    int n_features = dataset->n_features;

    // Initialize weights randomly or with zeros
    for (int i = 0; i <= n_features; i++) {
        model->weights[i] = 0.0;
    }

    // Gradient descent
    for (int iter = 0; iter < n_iterations; iter++) {
        double* gradients = (double*)calloc(n_features + 1, sizeof(double));

        // Calculate gradients for all samples
        for (int i = 0; i < n_samples; i++) {
            // Calculate prediction
            double prediction = model->bias;
            for (int j = 0; j < n_features; j++) {
                prediction += model->weights[j] * dataset->X[i][j];
            }

            // Calculate error
            double error = prediction - dataset->y[i];

            // Update gradients
            gradients[0] += error;  // Bias gradient
            for (int j = 0; j < n_features; j++) {
                gradients[j + 1] += error * dataset->X[i][j];
            }
        }

        // Update weights
        model->bias -= learning_rate * gradients[0] / n_samples;
        for (int j = 0; j < n_features; j++) {
            model->weights[j] -= learning_rate * gradients[j + 1] / n_samples;
        }

        free(gradients);

        // Optional: Print progress
        if ((iter + 1) % 100 == 0) {
            printf("Iteration %d completed\n", iter + 1);
        }
    }
}

double predict(LinearRegression* model, double* features) {
    double prediction = model->bias;
    for (int i = 0; i < model->n_features; i++) {
        prediction += model->weights[i] * features[i];
    }
    return prediction;
}
```

### **Step 3: Model Evaluation**

```c
// metrics.c
#include "linear_regression.h"

ModelMetrics evaluate(LinearRegression* model, Dataset* dataset) {
    ModelMetrics metrics = {0.0, 0.0, 0.0, 0.0};

    int n_samples = dataset->n_samples;
    double sum_squared_errors = 0.0;
    double sum_absolute_errors = 0.0;
    double sum_y = 0.0;
    double sum_y_squared = 0.0;

    // Calculate mean of actual values
    for (int i = 0; i < n_samples; i++) {
        sum_y += dataset->y[i];
    }
    double mean_y = sum_y / n_samples;

    // Calculate predictions and errors
    for (int i = 0; i < n_samples; i++) {
        double prediction = predict(model, dataset->X[i]);
        double error = prediction - dataset->y[i];

        sum_squared_errors += error * error;
        sum_absolute_errors += fabs(error);
        sum_y_squared += (dataset->y[i] - mean_y) * (dataset->y[i] - mean_y);
    }

    // Calculate metrics
    metrics.mse = sum_squared_errors / n_samples;
    metrics.rmse = sqrt(metrics.mse);
    metrics.mae = sum_absolute_errors / n_samples;
    metrics.r2_score = 1.0 - (sum_squared_errors / sum_y_squared);

    return metrics;
}
```

### **Step 4: Data Processing**

```c
// data_processing.c
#include "linear_regression.h"
#include <string.h>

Dataset* load_dataset(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    Dataset* dataset = (Dataset*)malloc(sizeof(Dataset));
    if (!dataset) return NULL;

    // Count lines and features (simplified CSV parsing)
    char line[1024];
    int line_count = 0;
    int feature_count = 0;

    // Read header to determine number of features
    if (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        while (token) {
            feature_count++;
            token = strtok(NULL, ",");
        }
        feature_count--; // Last column is target
    }

    // Count data lines
    while (fgets(line, sizeof(line), file)) {
        line_count++;
    }

    // Reset file pointer
    rewind(file);
    fgets(line, sizeof(line), file); // Skip header

    // Allocate memory
    dataset->n_samples = line_count;
    dataset->n_features = feature_count;
    dataset->X = (double**)malloc(line_count * sizeof(double*));
    dataset->y = (double*)malloc(line_count * sizeof(double));

    if (!dataset->X || !dataset->y) {
        free_dataset(dataset);
        fclose(file);
        return NULL;
    }

    // Read data
    for (int i = 0; i < line_count; i++) {
        dataset->X[i] = (double*)malloc(feature_count * sizeof(double));
        if (!dataset->X[i]) {
            free_dataset(dataset);
            fclose(file);
            return NULL;
        }

        if (fgets(line, sizeof(line), file)) {
            char* token = strtok(line, ",");
            for (int j = 0; j < feature_count; j++) {
                if (token) {
                    dataset->X[i][j] = atof(token);
                    token = strtok(NULL, ",");
                }
            }
            if (token) {
                dataset->y[i] = atof(token);
            }
        }
    }

    fclose(file);
    return dataset;
}

void free_dataset(Dataset* dataset) {
    if (dataset) {
        if (dataset->X) {
            for (int i = 0; i < dataset->n_samples; i++) {
                free(dataset->X[i]);
            }
            free(dataset->X);
        }
        free(dataset->y);
        free(dataset);
    }
}
```

### **Step 5: Main Program**

```c
// main.c
#include "linear_regression.h"

int main() {
    printf("Simple Linear Regression in C\n");
    printf("=============================\n\n");

    // Load training data
    Dataset* train_data = load_dataset("data/train.csv");
    if (!train_data) {
        printf("Failed to load training data\n");
        return 1;
    }

    printf("Loaded %d training samples with %d features\n",
           train_data->n_samples, train_data->n_features);

    // Create and train model
    LinearRegression* model = create_model(train_data->n_features);
    if (!model) {
        printf("Failed to create model\n");
        free_dataset(train_data);
        return 1;
    }

    printf("Training model...\n");
    fit(model, train_data, 0.01, 1000);

    // Evaluate on training data
    ModelMetrics metrics = evaluate(model, train_data);
    printf("\nTraining Metrics:\n");
    printf("MSE: %.4f\n", metrics.mse);
    printf("RMSE: %.4f\n", metrics.rmse);
    printf("MAE: %.4f\n", metrics.mae);
    printf("R² Score: %.4f\n", metrics.r2_score);

    // Load test data
    Dataset* test_data = load_dataset("data/test.csv");
    if (test_data) {
        ModelMetrics test_metrics = evaluate(model, test_data);
        printf("\nTest Metrics:\n");
        printf("MSE: %.4f\n", test_metrics.mse);
        printf("RMSE: %.4f\n", test_metrics.rmse);
        printf("MAE: %.4f\n", test_metrics.mae);
        printf("R² Score: %.4f\n", test_metrics.r2_score);

        free_dataset(test_data);
    }

    // Make a prediction
    printf("\nModel Weights:\n");
    printf("Bias: %.4f\n", model->bias);
    for (int i = 0; i < model->n_features; i++) {
        printf("Weight[%d]: %.4f\n", i, model->weights[i]);
    }

    // Example prediction
    double sample_features[] = {1.0, 2.0}; // Adjust based on your data
    double prediction = predict(model, sample_features);
    printf("\nSample Prediction: %.4f\n", prediction);

    // Cleanup
    free_model(model);
    free_dataset(train_data);

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Algorithm**
- [x] Linear regression implementation
- [x] Gradient descent optimization
- [x] Model training and prediction
- [x] Multiple evaluation metrics

### **✅ Data Handling**
- [x] CSV data loading
- [x] Memory-efficient data structures
- [x] Data preprocessing utilities
- [x] Error handling for file operations

### **🚀 Extensions**
- [ ] Multiple linear regression
- [ ] Polynomial regression
- [ ] Regularization (L1/L2)
- [ ] Cross-validation
- [ ] Feature scaling
- [ ] Model serialization

## 📊 Sample Data Format

### **train.csv**
```csv
feature1,feature2,target
1.0,2.0,5.0
2.0,3.0,8.0
3.0,4.0,11.0
4.0,5.0,14.0
```

### **test.csv**
```csv
feature1,feature2,target
1.5,2.5,6.5
2.5,3.5,9.5
```

## 🧪 Testing and Validation

### **Unit Testing**
```c
// Simple test for prediction
void test_prediction() {
    LinearRegression* model = create_model(2);
    model->bias = 1.0;
    model->weights[0] = 2.0;
    model->weights[1] = 3.0;

    double features[] = {1.0, 1.0};
    double prediction = predict(model, features);

    // Expected: 1.0 + 2.0*1.0 + 3.0*1.0 = 6.0
    assert(fabs(prediction - 6.0) < 0.001);

    free_model(model);
    printf("Prediction test passed!\n");
}
```

### **Performance Benchmarking**
```c
// Benchmark training time
void benchmark_training() {
    Dataset* data = load_dataset("data/large_dataset.csv");
    LinearRegression* model = create_model(data->n_features);

    clock_t start = clock();
    fit(model, data, 0.01, 1000);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Training time: %.2f seconds\n", time_taken);

    free_model(model);
    free_dataset(data);
}
```

## 📈 Learning Outcomes

### **Mathematical Understanding**
- Linear algebra fundamentals
- Calculus (partial derivatives)
- Optimization algorithms
- Statistical concepts

### **Programming Skills**
- Numerical computing in C
- Memory management for large datasets
- Algorithm implementation
- Performance optimization

## 🚀 Advanced Extensions

### **Regularization**
```c
// Add L2 regularization to gradient descent
void fit_with_regularization(LinearRegression* model, Dataset* dataset,
                           double learning_rate, double lambda, int n_iterations) {
    // Implementation with L2 penalty
}
```

### **Polynomial Features**
```c
// Generate polynomial features
double** generate_polynomial_features(double** X, int n_samples, int n_features, int degree) {
    // Implementation for polynomial regression
}
```

## 📖 References

- **"Pattern Recognition and Machine Learning"** by Christopher Bishop
- **"Elements of Statistical Learning"** by Hastie et al.
- **"Machine Learning: A Probabilistic Perspective"** by Kevin Murphy

## 🎯 Real-World Applications

- **House Price Prediction**: Predict property values based on features
- **Stock Price Forecasting**: Financial time series prediction
- **Sales Forecasting**: Business revenue prediction
- **Medical Diagnosis**: Disease risk assessment
- **Quality Control**: Manufacturing defect prediction

---

**🌟 This project demonstrates implementing complex algorithms in pure C, showcasing the language's power for numerical computing!**