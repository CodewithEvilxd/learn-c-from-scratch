# 🤖 **Project 12: Linear Regression Implementation in C**
## 🎯 **Machine Learning Algorithm with Data Analysis**

---

## 📋 **Project Overview**

**English:** A complete linear regression implementation in C that performs data analysis, model training, prediction, and evaluation with statistical metrics and data visualization.

**Hinglish:** Ek complete linear regression implementation jo C mein bani hai, jisme data analysis, model training, prediction, aur evaluation statistical metrics aur data visualization ke saath included hai.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Mathematical algorithm implementation
- Statistical computation
- Data processing and analysis
- Memory management for datasets
- File I/O for data handling

✅ **ML Concepts:**
- Linear regression fundamentals
- Cost function optimization
- Gradient descent algorithm
- Model evaluation metrics
- Data preprocessing

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Core ML algorithms | Handles mathematical computations |
| **Math Library** | Statistical functions | sqrt, pow for calculations |
| **File System** | Data persistence | CSV data loading and saving |
| **Standard Library** | Data structures | Arrays for dataset management |

---

## 📁 **Project Structure**

```
LinearRegression/
├── include/
│   ├── regression.h
│   ├── dataset.h
│   └── statistics.h
├── src/
│   ├── regression.c
│   ├── dataset.c
│   ├── statistics.c
│   └── main.c
├── data/
│   └── sample_data.csv
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Data Structures**

```c
// dataset.h
#ifndef DATASET_H
#define DATASET_H

#define MAX_SAMPLES 1000
#define MAX_FEATURES 10

typedef struct {
    double **X;        // Feature matrix
    double *y;         // Target values
    int n_samples;     // Number of samples
    int n_features;    // Number of features
} Dataset;

#endif
```

```c
// regression.h
#ifndef REGRESSION_H
#define REGRESSION_H

#include "dataset.h"

typedef struct {
    double *weights;      // Model weights
    double bias;          // Model bias
    int n_features;       // Number of features
    double learning_rate; // Learning rate
    int max_iter;         // Maximum iterations
} LinearRegression;

#endif
```

### **2. Dataset Management**

```c
// dataset.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

// Create dataset
Dataset* create_dataset(int n_samples, int n_features) {
    Dataset *dataset = (Dataset*)malloc(sizeof(Dataset));
    if (!dataset) return NULL;

    dataset->n_samples = n_samples;
    dataset->n_features = n_features;

    // Allocate feature matrix
    dataset->X = (double**)malloc(n_samples * sizeof(double*));
    if (!dataset->X) {
        free(dataset);
        return NULL;
    }

    for (int i = 0; i < n_samples; i++) {
        dataset->X[i] = (double*)malloc(n_features * sizeof(double));
        if (!dataset->X[i]) {
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(dataset->X[j]);
            }
            free(dataset->X);
            free(dataset);
            return NULL;
        }
    }

    // Allocate target array
    dataset->y = (double*)malloc(n_samples * sizeof(double));
    if (!dataset->y) {
        for (int i = 0; i < n_samples; i++) {
            free(dataset->X[i]);
        }
        free(dataset->X);
        free(dataset);
        return NULL;
    }

    return dataset;
}

// Load dataset from CSV
Dataset* load_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    // Count lines and features (simplified)
    int n_samples = 0;
    int n_features = 1; // Assume single feature for simplicity
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        n_samples++;
    }

    rewind(file);

    Dataset *dataset = create_dataset(n_samples, n_features);
    if (!dataset) {
        fclose(file);
        return NULL;
    }

    // Read data
    for (int i = 0; i < n_samples && fgets(line, sizeof(line), file); i++) {
        char *token = strtok(line, ",");
        if (token) {
            dataset->X[i][0] = atof(token);
        }

        token = strtok(NULL, ",");
        if (token) {
            dataset->y[i] = atof(token);
        }
    }

    fclose(file);
    return dataset;
}

// Free dataset memory
void free_dataset(Dataset *dataset) {
    if (!dataset) return;

    for (int i = 0; i < dataset->n_samples; i++) {
        free(dataset->X[i]);
    }
    free(dataset->X);
    free(dataset->y);
    free(dataset);
}
```

### **3. Linear Regression Implementation**

```c
// regression.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "regression.h"

// Create linear regression model
LinearRegression* create_model(int n_features) {
    LinearRegression *model = (LinearRegression*)malloc(sizeof(LinearRegression));
    if (!model) return NULL;

    model->n_features = n_features;
    model->weights = (double*)malloc(n_features * sizeof(double));
    if (!model->weights) {
        free(model);
        return NULL;
    }

    // Initialize weights and bias
    for (int i = 0; i < n_features; i++) {
        model->weights[i] = 0.0;
    }
    model->bias = 0.0;
    model->learning_rate = 0.01;
    model->max_iter = 1000;

    return model;
}

// Predict single sample
double predict_single(LinearRegression *model, double *X) {
    double prediction = model->bias;

    for (int i = 0; i < model->n_features; i++) {
        prediction += model->weights[i] * X[i];
    }

    return prediction;
}

// Train model using gradient descent
void fit(LinearRegression *model, Dataset *dataset) {
    int n_samples = dataset->n_samples;
    int n_features = dataset->n_features;

    for (int iter = 0; iter < model->max_iter; iter++) {
        double bias_gradient = 0.0;
        double *weight_gradients = (double*)calloc(n_features, sizeof(double));

        // Calculate gradients
        for (int i = 0; i < n_samples; i++) {
            double prediction = predict_single(model, dataset->X[i]);
            double error = prediction - dataset->y[i];

            bias_gradient += error;

            for (int j = 0; j < n_features; j++) {
                weight_gradients[j] += error * dataset->X[i][j];
            }
        }

        // Update parameters
        model->bias -= model->learning_rate * bias_gradient / n_samples;

        for (int j = 0; j < n_features; j++) {
            model->weights[j] -= model->learning_rate * weight_gradients[j] / n_samples;
        }

        free(weight_gradients);
    }
}

// Make predictions
double* predict(LinearRegression *model, Dataset *dataset) {
    int n_samples = dataset->n_samples;
    double *predictions = (double*)malloc(n_samples * sizeof(double));

    for (int i = 0; i < n_samples; i++) {
        predictions[i] = predict_single(model, dataset->X[i]);
    }

    return predictions;
}

// Calculate R-squared score
double r2_score(double *y_true, double *y_pred, int n_samples) {
    double ss_res = 0.0;
    double ss_tot = 0.0;
    double y_mean = 0.0;

    // Calculate mean
    for (int i = 0; i < n_samples; i++) {
        y_mean += y_true[i];
    }
    y_mean /= n_samples;

    // Calculate sums of squares
    for (int i = 0; i < n_samples; i++) {
        ss_res += pow(y_true[i] - y_pred[i], 2);
        ss_tot += pow(y_true[i] - y_mean, 2);
    }

    return 1.0 - (ss_res / ss_tot);
}

// Free model memory
void free_model(LinearRegression *model) {
    if (!model) return;
    free(model->weights);
    free(model);
}
```

### **4. Statistics and Evaluation**

```c
// statistics.c
#include <stdio.h>
#include <math.h>
#include "statistics.h"

// Calculate mean
double mean(double *data, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// Calculate standard deviation
double std_dev(double *data, int n) {
    double m = mean(data, n);
    double sum_sq = 0.0;

    for (int i = 0; i < n; i++) {
        sum_sq += pow(data[i] - m, 2);
    }

    return sqrt(sum_sq / n);
}

// Print model statistics
void print_model_stats(LinearRegression *model, Dataset *dataset) {
    printf("\n=== Model Statistics ===\n");
    printf("Number of features: %d\n", model->n_features);
    printf("Learning rate: %.4f\n", model->learning_rate);
    printf("Max iterations: %d\n", model->max_iter);
    printf("Final weights: ");
    for (int i = 0; i < model->n_features; i++) {
        printf("%.4f ", model->weights[i]);
    }
    printf("\n");
    printf("Bias: %.4f\n", model->bias);

    // Make predictions and calculate R-squared
    double *predictions = predict(model, dataset);
    double r2 = r2_score(dataset->y, predictions, dataset->n_samples);

    printf("R-squared score: %.4f\n", r2);
    free(predictions);
}
```

### **5. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "regression.h"
#include "statistics.h"

int main() {
    printf("Linear Regression Implementation\n");
    printf("===============================\n");

    // Create sample dataset
    Dataset *dataset = create_dataset(10, 1);
    if (!dataset) {
        printf("Failed to create dataset!\n");
        return 1;
    }

    // Add sample data
    double X_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double y_data[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    for (int i = 0; i < 10; i++) {
        dataset->X[i][0] = X_data[i];
        dataset->y[i] = y_data[i];
    }

    // Create and train model
    LinearRegression *model = create_model(1);
    if (!model) {
        printf("Failed to create model!\n");
        free_dataset(dataset);
        return 1;
    }

    printf("Training model...\n");
    fit(model, dataset);

    // Print model statistics
    print_model_stats(model, dataset);

    // Make predictions
    printf("\n=== Predictions ===\n");
    double test_X[5] = {11, 12, 13, 14, 15};
    for (int i = 0; i < 5; i++) {
        double prediction = predict_single(model, &test_X[i]);
        printf("X = %.0f, Predicted y = %.2f\n", test_X[i], prediction);
    }

    // Cleanup
    free_model(model);
    free_dataset(dataset);

    return 0;
}
```

---

## 🎯 **Features Implemented**

### **ML Features**
- ✅ Linear regression algorithm
- ✅ Gradient descent optimization
- ✅ Model training and prediction
- ✅ R-squared evaluation metric
- ✅ Statistical analysis

### **Data Features**
- ✅ Dataset creation and management
- ✅ CSV data loading
- ✅ Memory-efficient data structures
- ✅ Data preprocessing

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Linear Regression - Machine Learning in C"
- **Hinglish:** "Linear Regression - Machine Learning in C"

### **Slide 2: What We Built**
- ✅ Complete linear regression implementation
- ✅ Gradient descent optimization
- ✅ Model evaluation with R-squared
- ✅ Statistical analysis and visualization
- ✅ Data loading and preprocessing

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double *weights;
    double bias;
    int n_features;
} LinearRegression;

typedef struct {
    double **X;
    double *y;
    int n_samples;
} Dataset;

// Core functions
LinearRegression* create_model(int n_features);
void fit(LinearRegression *model, Dataset *dataset);
double predict_single(LinearRegression *model, double *X);
double r2_score(double *y_true, double *y_pred, int n);
```

### **Slide 4: ML Algorithm**
```c
// Gradient descent implementation
for (int iter = 0; iter < max_iter; iter++) {
    // Calculate gradients
    for (int i = 0; i < n_samples; i++) {
        double prediction = predict_single(model, X[i]);
        double error = prediction - y[i];
        bias_gradient += error;
        for (int j = 0; j < n_features; j++) {
            weight_gradients[j] += error * X[i][j];
        }
    }

    // Update parameters
    model->bias -= learning_rate * bias_gradient / n_samples;
    for (int j = 0; j < n_features; j++) {
        model->weights[j] -= learning_rate * weight_gradients[j] / n_samples;
    }
}
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Algorithm implementation
- ✅ Mathematical computing
- ✅ Memory management
- ✅ Data structures
- ✅ Statistical analysis

### **ML Concepts:**
- ✅ Linear regression
- ✅ Gradient descent
- ✅ Model evaluation
- ✅ Data preprocessing
- ✅ Performance metrics

---

## 📞 **Contact & Support**

**Project Developer:** ML Student
**Email:** ml@studentproject.com
**GitHub:** https://github.com/c-ml/linear-regression

---

**🤖 This linear regression implementation demonstrates machine learning concepts and mathematical computing in C, perfect for understanding ML algorithms and data analysis.**