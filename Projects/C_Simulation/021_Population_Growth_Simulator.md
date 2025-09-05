# 📈 **Project 21: Population Growth Simulator in C**
## 🎯 **Mathematical Modeling with Data Visualization**

---

## 📋 **Project Overview**

**English:** A population growth simulator in C that implements various growth models (exponential, logistic) with data visualization, statistical analysis, and predictive modeling capabilities.

**Hinglish:** Ek population growth simulator jo C mein hai, jisme various growth models (exponential, logistic) implement kiye gaye hain with data visualization, statistical analysis, aur predictive modeling capabilities ke saath.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Mathematical modeling implementation
- Data visualization techniques
- Statistical analysis
- File I/O for data persistence
- Algorithm optimization

✅ **Mathematical Concepts:**
- Exponential growth modeling
- Logistic growth curves
- Population dynamics
- Statistical analysis
- Predictive modeling

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Mathematical computations | Handles growth calculations and modeling |
| **Math Library** | Advanced mathematics | Exponential and logarithmic functions |
| **File System** | Data persistence | Save/load simulation results |
| **Time Library** | Performance timing | Simulation timing and analysis |

---

## 📁 **Project Structure**

```
PopulationSimulator/
├── include/
│   ├── growth.h
│   ├── simulation.h
│   ├── statistics.h
├── src/
│   ├── growth.c
│   ├── simulation.c
│   ├── statistics.c
│   └── main.c
├── data/
│   └── results.csv
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Growth Models**

```c
// growth.h
#ifndef GROWTH_H
#define GROWTH_H

typedef enum {
    EXPONENTIAL_GROWTH,
    LOGISTIC_GROWTH,
    LINEAR_GROWTH
} GrowthModel;

typedef struct {
    GrowthModel model;
    double initial_population;
    double growth_rate;
    double carrying_capacity; // For logistic growth
    int max_time_steps;
} GrowthParameters;

// Growth calculation functions
double calculate_exponential_growth(double population, double rate, int time);
double calculate_logistic_growth(double population, double rate, double capacity, int time);
double* simulate_population_growth(GrowthParameters params, int *steps);

#endif
```

```c
// growth.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "growth.h"

// Calculate exponential growth
double calculate_exponential_growth(double population, double rate, int time) {
    return population * exp(rate * time);
}

// Calculate logistic growth
double calculate_logistic_growth(double population, double rate, double capacity, int time) {
    double exponent = -rate * time;
    return capacity / (1 + (capacity / population - 1) * exp(exponent));
}

// Simulate population growth over time
double* simulate_population_growth(GrowthParameters params, int *steps) {
    *steps = params.max_time_steps;
    double *population_data = (double*)malloc(params.max_time_steps * sizeof(double));

    if (!population_data) return NULL;

    population_data[0] = params.initial_population;

    for (int t = 1; t < params.max_time_steps; t++) {
        switch (params.model) {
            case EXPONENTIAL_GROWTH:
                population_data[t] = calculate_exponential_growth(
                    params.initial_population, params.growth_rate, t);
                break;

            case LOGISTIC_GROWTH:
                population_data[t] = calculate_logistic_growth(
                    params.initial_population, params.growth_rate,
                    params.carrying_capacity, t);
                break;

            case LINEAR_GROWTH:
                population_data[t] = params.initial_population +
                                   params.growth_rate * t;
                break;
        }
    }

    return population_data;
}
```

### **2. Simulation Engine**

```c
// simulation.h
#ifndef SIMULATION_H
#define SIMULATION_H

#include "growth.h"

typedef struct {
    GrowthParameters params;
    double *population_data;
    int time_steps;
    double final_population;
    double growth_rate_calculated;
} SimulationResult;

// Simulation functions
SimulationResult run_simulation(GrowthParameters params);
void display_simulation_results(SimulationResult result);
void save_simulation_data(SimulationResult result, const char *filename);
void plot_population_growth(SimulationResult result);

#endif
```

```c
// simulation.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulation.h"
#include "growth.h"

// Run complete simulation
SimulationResult run_simulation(GrowthParameters params) {
    SimulationResult result;
    result.params = params;
    result.population_data = simulate_population_growth(params, &result.time_steps);

    if (result.population_data) {
        result.final_population = result.population_data[result.time_steps - 1];

        // Calculate actual growth rate
        if (result.time_steps > 1) {
            result.growth_rate_calculated = log(result.final_population /
                                               result.params.initial_population) /
                                           (result.time_steps - 1);
        } else {
            result.growth_rate_calculated = 0.0;
        }
    } else {
        result.final_population = 0.0;
        result.growth_rate_calculated = 0.0;
    }

    return result;
}

// Display simulation results
void display_simulation_results(SimulationResult result) {
    printf("\n=== Population Growth Simulation Results ===\n");
    printf("Model: ");
    switch (result.params.model) {
        case EXPONENTIAL_GROWTH: printf("Exponential Growth\n"); break;
        case LOGISTIC_GROWTH: printf("Logistic Growth\n"); break;
        case LINEAR_GROWTH: printf("Linear Growth\n"); break;
    }

    printf("Initial Population: %.0f\n", result.params.initial_population);
    printf("Growth Rate: %.4f\n", result.params.growth_rate);
    if (result.params.model == LOGISTIC_GROWTH) {
        printf("Carrying Capacity: %.0f\n", result.params.carrying_capacity);
    }
    printf("Time Steps: %d\n", result.time_steps);
    printf("Final Population: %.0f\n", result.final_population);
    printf("Calculated Growth Rate: %.4f\n", result.growth_rate_calculated);

    // Show some data points
    printf("\nPopulation Data (first 10 steps):\n");
    for (int i = 0; i < result.time_steps && i < 10; i++) {
        printf("Time %d: %.0f\n", i, result.population_data[i]);
    }

    if (result.time_steps > 10) {
        printf("... (%d more steps)\n", result.time_steps - 10);
    }
}

// Save simulation data to file
void save_simulation_data(SimulationResult result, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error saving data to file!\n");
        return;
    }

    fprintf(file, "Time,Population\n");
    for (int i = 0; i < result.time_steps; i++) {
        fprintf(file, "%d,%.2f\n", i, result.population_data[i]);
    }

    fclose(file);
    printf("Simulation data saved to %s\n", filename);
}

// Simple text-based plot
void plot_population_growth(SimulationResult result) {
    printf("\n=== Population Growth Plot ===\n");

    // Find max population for scaling
    double max_pop = 0;
    for (int i = 0; i < result.time_steps; i++) {
        if (result.population_data[i] > max_pop) {
            max_pop = result.population_data[i];
        }
    }

    // Plot each time step
    for (int i = 0; i < result.time_steps && i < 20; i++) { // Show first 20 steps
        int bar_length = (int)(result.population_data[i] / max_pop * 50);
        printf("Time %2d: ", i);
        for (int j = 0; j < bar_length; j++) {
            printf("█");
        }
        printf(" %.0f\n", result.population_data[i]);
    }

    if (result.time_steps > 20) {
        printf("... (%d more time steps)\n", result.time_steps - 20);
    }
}
```

### **3. Statistical Analysis**

```c
// statistics.h
#ifndef STATISTICS_H
#define STATISTICS_H

#include "simulation.h"

// Statistical functions
double calculate_mean(double *data, int n);
double calculate_median(double *data, int n);
double calculate_standard_deviation(double *data, int n);
double calculate_growth_rate(double *data, int n);
void analyze_population_trends(SimulationResult result);

#endif
```

```c
// statistics.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "statistics.h"

// Calculate mean
double calculate_mean(double *data, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// Calculate median
double calculate_median(double *data, int n) {
    // Simple bubble sort for median calculation
    double *sorted = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) sorted[i] = data[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                double temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    double median;
    if (n % 2 == 0) {
        median = (sorted[n/2 - 1] + sorted[n/2]) / 2.0;
    } else {
        median = sorted[n/2];
    }

    free(sorted);
    return median;
}

// Calculate standard deviation
double calculate_standard_deviation(double *data, int n) {
    double mean = calculate_mean(data, n);
    double sum_sq = 0.0;

    for (int i = 0; i < n; i++) {
        sum_sq += pow(data[i] - mean, 2);
    }

    return sqrt(sum_sq / n);
}

// Calculate growth rate
double calculate_growth_rate(double *data, int n) {
    if (n < 2) return 0.0;

    double initial = data[0];
    double final = data[n - 1];

    if (initial == 0) return 0.0;

    return (final - initial) / initial / (n - 1);
}

// Analyze population trends
void analyze_population_trends(SimulationResult result) {
    printf("\n=== Population Trend Analysis ===\n");

    double mean_pop = calculate_mean(result.population_data, result.time_steps);
    double median_pop = calculate_median(result.population_data, result.time_steps);
    double std_dev = calculate_standard_deviation(result.population_data, result.time_steps);
    double growth_rate = calculate_growth_rate(result.population_data, result.time_steps);

    printf("Mean Population: %.2f\n", mean_pop);
    printf("Median Population: %.2f\n", median_pop);
    printf("Standard Deviation: %.2f\n", std_dev);
    printf("Average Growth Rate: %.4f\n", growth_rate);

    // Trend analysis
    if (growth_rate > 0.1) {
        printf("Trend: Rapid growth\n");
    } else if (growth_rate > 0.01) {
        printf("Trend: Moderate growth\n");
    } else if (growth_rate > 0) {
        printf("Trend: Slow growth\n");
    } else {
        printf("Trend: Population decline\n");
    }
}
```

### **4. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "growth.h"
#include "simulation.h"
#include "statistics.h"

void display_menu() {
    printf("\n=== Population Growth Simulator ===\n");
    printf("1. Run Exponential Growth Simulation\n");
    printf("2. Run Logistic Growth Simulation\n");
    printf("3. Run Linear Growth Simulation\n");
    printf("4. Compare Growth Models\n");
    printf("5. Analyze Population Trends\n");
    printf("6. Save Simulation Data\n");
    printf("7. Plot Population Growth\n");
    printf("8. Exit\n");
    printf("===================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    GrowthParameters params;
    SimulationResult result;

    printf("Population Growth Simulator\n");
    printf("===========================\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Exponential Growth
                printf("Enter initial population: ");
                scanf("%lf", &params.initial_population);
                printf("Enter growth rate: ");
                scanf("%lf", &params.growth_rate);
                printf("Enter time steps: ");
                scanf("%d", &params.max_time_steps);

                params.model = EXPONENTIAL_GROWTH;
                result = run_simulation(params);
                display_simulation_results(result);
                break;
            }

            case 2: {
                // Logistic Growth
                printf("Enter initial population: ");
                scanf("%lf", &params.initial_population);
                printf("Enter growth rate: ");
                scanf("%lf", &params.growth_rate);
                printf("Enter carrying capacity: ");
                scanf("%lf", &params.carrying_capacity);
                printf("Enter time steps: ");
                scanf("%d", &params.max_time_steps);

                params.model = LOGISTIC_GROWTH;
                result = run_simulation(params);
                display_simulation_results(result);
                break;
            }

            case 3: {
                // Linear Growth
                printf("Enter initial population: ");
                scanf("%lf", &params.initial_population);
                printf("Enter growth rate: ");
                scanf("%lf", &params.growth_rate);
                printf("Enter time steps: ");
                scanf("%d", &params.max_time_steps);

                params.model = LINEAR_GROWTH;
                result = run_simulation(params);
                display_simulation_results(result);
                break;
            }

            case 4: {
                // Compare models
                printf("Enter initial population: ");
                scanf("%lf", &params.initial_population);
                printf("Enter growth rate: ");
                scanf("%lf", &params.growth_rate);
                printf("Enter carrying capacity (for logistic): ");
                scanf("%lf", &params.carrying_capacity);
                printf("Enter time steps: ");
                scanf("%d", &params.max_time_steps);

                printf("\n=== Model Comparison ===\n");

                // Exponential
                params.model = EXPONENTIAL_GROWTH;
                SimulationResult exp_result = run_simulation(params);
                printf("Exponential - Final: %.0f\n", exp_result.final_population);

                // Logistic
                params.model = LOGISTIC_GROWTH;
                SimulationResult log_result = run_simulation(params);
                printf("Logistic - Final: %.0f\n", log_result.final_population);

                // Linear
                params.model = LINEAR_GROWTH;
                SimulationResult lin_result = run_simulation(params);
                printf("Linear - Final: %.0f\n", lin_result.final_population);

                // Cleanup
                free(exp_result.population_data);
                free(log_result.population_data);
                free(lin_result.population_data);
                break;
            }

            case 5: {
                // Analyze trends (requires previous simulation)
                if (result.population_data) {
                    analyze_population_trends(result);
                } else {
                    printf("Run a simulation first!\n");
                }
                break;
            }

            case 6: {
                // Save data
                if (result.population_data) {
                    save_simulation_data(result, "data/population_data.csv");
                } else {
                    printf("Run a simulation first!\n");
                }
                break;
            }

            case 7: {
                // Plot data
                if (result.population_data) {
                    plot_population_growth(result);
                } else {
                    printf("Run a simulation first!\n");
                }
                break;
            }

            case 8:
                if (result.population_data) {
                    free(result.population_data);
                }
                printf("Thank you for using Population Growth Simulator!\n");
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

### **Growth Models**
- ✅ Exponential growth simulation
- ✅ Logistic growth with carrying capacity
- ✅ Linear growth modeling
- ✅ Model comparison capabilities
- ✅ Statistical analysis

### **Visualization & Analysis**
- ✅ Text-based plotting
- ✅ Statistical trend analysis
- ✅ Data export to CSV
- ✅ Performance metrics
- ✅ Growth rate calculations

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Population Growth Simulator - Mathematical Modeling in C"
- **Hinglish:** "Population Growth Simulator - Mathematical Modeling in C"

### **Slide 2: What We Built**
- ✅ Complete population growth simulator
- ✅ Multiple mathematical models (exponential, logistic, linear)
- ✅ Statistical analysis and trend detection
- ✅ Data visualization and export
- ✅ Model comparison capabilities

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
    EXPONENTIAL_GROWTH,
    LOGISTIC_GROWTH,
    LINEAR_GROWTH
} GrowthModel;

typedef struct {
    GrowthModel model;
    double initial_population;
    double growth_rate;
    double carrying_capacity;
} GrowthParameters;

// Core functions
double calculate_exponential_growth(double population, double rate, int time);
double calculate_logistic_growth(double population, double rate, double capacity, int time);
double* simulate_population_growth(GrowthParameters params, int *steps);
SimulationResult run_simulation(GrowthParameters params);
```

### **Slide 4: Mathematical Models**
```c
// Exponential growth formula
double calculate_exponential_growth(double population, double rate, int time) {
    return population * exp(rate * time);
}

// Logistic growth formula
double calculate_logistic_growth(double population, double rate, double capacity, int time) {
    double exponent = -rate * time;
    return capacity / (1 + (capacity / population - 1) * exp(exponent));
}
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Mathematical modeling
- ✅ Algorithm implementation
- ✅ Data visualization
- ✅ Statistical analysis
- ✅ File I/O operations

### **Mathematical Concepts:**
- ✅ Population dynamics
- ✅ Growth modeling
- ✅ Statistical analysis
- ✅ Predictive modeling
- ✅ Data interpretation

---

## 📞 **Contact & Support**

**Project Developer:** Mathematical Modeling Student
**Email:** simulation@studentproject.com
**GitHub:** https://github.com/c-simulation/population-growth

---

**📈 This population growth simulator demonstrates mathematical modeling and simulation techniques in C, perfect for understanding population dynamics and predictive modeling.**