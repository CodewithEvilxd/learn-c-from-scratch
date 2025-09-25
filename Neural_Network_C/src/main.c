/*
 * Neural Network System - Main Application
 * Entry point for the neural network training and inference system
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../headers/neural_net.h"
#include "../headers/layers.h"
#include "../headers/activations.h"
#include "../headers/losses.h"
#include "../headers/optimizers.h"

// ============================================================================
// Demo Data Generation
// ============================================================================

/**
 * @brief Generate XOR dataset for demonstration
 * @param x Output input array
 * @param y Output target array
 * @param samples Number of samples to generate
 */
void generate_xor_data(float* x, float* y, int samples) {
    for (int i = 0; i < samples; i++) {
        // Generate random inputs (0 or 1)
        float input1 = (rand() % 2);
        float input2 = (rand() % 2);

        // XOR logic: 1 if inputs are different, 0 if same
        float target = (input1 != input2) ? 1.0f : 0.0f;

        x[i * 2] = input1;
        x[i * 2 + 1] = input2;
        y[i] = target;
    }
}

/**
 * @brief Generate simple classification dataset
 * @param x Output input array
 * @param y Output target array
 * @param samples Number of samples
 * @param features Number of features
 * @param classes Number of classes
 */
void generate_classification_data(float* x, float* y, int samples, int features, int classes) {
    for (int i = 0; i < samples; i++) {
        // Generate random features
        for (int f = 0; f < features; f++) {
            x[i * features + f] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // [-1, 1]
        }

        // Assign class based on first feature
        int class_idx = (x[i * features] > 0) ? 0 : 1;
        if (classes > 2) {
            class_idx = (int)((x[i * features] + 1.0f) * (classes - 1) / 2.0f);
            class_idx = class_idx < 0 ? 0 : (class_idx >= classes ? classes - 1 : class_idx);
        }

        // One-hot encoding for targets
        for (int c = 0; c < classes; c++) {
            y[i * classes + c] = (c == class_idx) ? 1.0f : 0.0f;
        }
    }
}

// ============================================================================
// Demo Functions
// ============================================================================

/**
 * @brief Demonstrate XOR problem solving
 */
void demo_xor_network() {
    printf("🧠 XOR Neural Network Demo\n");
    printf("==========================\n\n");

    // Create neural network
    NeuralNetwork* net = neural_network_create("XOR_Network");

    // Add layers
    neural_network_add_layer(net, layer_dense_create(2, 4, activation_tanh));
    neural_network_add_layer(net, layer_dense_create(4, 1, activation_sigmoid));

    // Create loss and optimizer
    Loss* loss = loss_create(LOSS_BINARY_CROSS_ENTROPY);
    Optimizer* optimizer = optimizer_create(OPTIMIZER_ADAM, 0.01f);

    // Compile network
    if (!neural_network_compile(net, loss, optimizer)) {
        printf("❌ Failed to compile network\n");
        return;
    }

    printf("✅ Network compiled successfully\n");
    printf("   - Input size: 2\n");
    printf("   - Hidden layer: 4 neurons (tanh)\n");
    printf("   - Output size: 1 (sigmoid)\n");
    printf("   - Loss: Binary Cross-Entropy\n");
    printf("   - Optimizer: Adam (lr=0.01)\n\n");

    // Generate training data
    const int samples = 1000;
    float* x_data = (float*)malloc(samples * 2 * sizeof(float));
    float* y_data = (float*)malloc(samples * sizeof(float));

    if (!x_data || !y_data) {
        printf("❌ Memory allocation failed\n");
        return;
    }

    generate_xor_data(x_data, y_data, samples);

    // Create tensors
    Tensor* x_tensor = tensor_create(x_data, (int[]){samples, 2}, 2);
    Tensor* y_tensor = tensor_create(y_data, (int[]){samples, 1}, 2);

    if (!x_tensor || !y_tensor) {
        printf("❌ Tensor creation failed\n");
        free(x_data);
        free(y_data);
        return;
    }

    // Training configuration
    TrainingConfig config = training_config_create(100, 32, 0.01f);
    config.verbose = 1;

    printf("🚀 Starting training...\n\n");

    // Train network
    if (neural_network_fit(net, x_tensor, y_tensor, config)) {
        printf("\n✅ Training completed!\n\n");

        // Test on XOR truth table
        printf("🧪 Testing on XOR truth table:\n");
        printf("Input → Output (Expected → Predicted)\n");

        float test_inputs[4][2] = {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
        };
        float expected_outputs[4] = {0, 1, 1, 0};

        for (int i = 0; i < 4; i++) {
            Tensor* test_input = tensor_create(test_inputs[i], (int[]){1, 2}, 2);
            Tensor* prediction = neural_network_predict(net, test_input);

            if (prediction && prediction->data) {
                printf("(%.0f, %.0f) → %.3f (%.0f)\n",
                       test_inputs[i][0], test_inputs[i][1],
                       prediction->data[0], expected_outputs[i]);
            }

            tensor_destroy(test_input);
            tensor_destroy(prediction);
        }
    } else {
        printf("❌ Training failed\n");
    }

    // Cleanup
    tensor_destroy(x_tensor);
    tensor_destroy(y_tensor);
    free(x_data);
    free(y_data);
    neural_network_destroy(net);
    loss_destroy(loss);
    optimizer_destroy(optimizer);
}

/**
 * @brief Demonstrate multi-class classification
 */
void demo_classification_network() {
    printf("🎯 Multi-Class Classification Demo\n");
    printf("=================================\n\n");

    const int features = 4;
    const int classes = 3;
    const int samples = 1000;

    // Create neural network
    NeuralNetwork* net = neural_network_create("Classification_Network");

    // Add layers
    neural_network_add_layer(net, layer_dense_create(features, 8, activation_relu));
    neural_network_add_layer(net, layer_dense_create(8, classes, activation_softmax));

    // Create loss and optimizer
    Loss* loss = loss_create(LOSS_CATEGORICAL_CROSS_ENTROPY);
    Optimizer* optimizer = optimizer_create(OPTIMIZER_ADAM, 0.001f);

    // Compile network
    if (!neural_network_compile(net, loss, optimizer)) {
        printf("❌ Failed to compile network\n");
        return;
    }

    printf("✅ Network compiled successfully\n");
    printf("   - Input features: %d\n", features);
    printf("   - Hidden layer: 8 neurons (ReLU)\n");
    printf("   - Output classes: %d (Softmax)\n", classes);
    printf("   - Loss: Categorical Cross-Entropy\n");
    printf("   - Optimizer: Adam (lr=0.001)\n\n");

    // Generate training data
    float* x_data = (float*)malloc(samples * features * sizeof(float));
    float* y_data = (float*)malloc(samples * classes * sizeof(float));

    if (!x_data || !y_data) {
        printf("❌ Memory allocation failed\n");
        return;
    }

    generate_classification_data(x_data, y_data, samples, features, classes);

    // Create tensors
    Tensor* x_tensor = tensor_create(x_data, (int[]){samples, features}, 2);
    Tensor* y_tensor = tensor_create(y_data, (int[]){samples, classes}, 2);

    if (!x_tensor || !y_tensor) {
        printf("❌ Tensor creation failed\n");
        free(x_data);
        free(y_data);
        return;
    }

    // Training configuration
    TrainingConfig config = training_config_create(50, 64, 0.001f);
    config.verbose = 1;

    printf("🚀 Starting training...\n\n");

    // Train network
    if (neural_network_fit(net, x_tensor, y_tensor, config)) {
        printf("\n✅ Training completed!\n\n");

        // Test on a few samples
        printf("🧪 Testing on sample data:\n");
        printf("Input → Predicted Class\n");

        for (int i = 0; i < 5; i++) {
            // Get a random sample
            int sample_idx = rand() % samples;
            float* sample_input = &x_data[sample_idx * features];

            Tensor* test_input = tensor_create(sample_input, (int[]){1, features}, 2);
            Tensor* prediction = neural_network_predict(net, test_input);

            if (prediction && prediction->data) {
                // Find predicted class
                int predicted_class = 0;
                float max_prob = prediction->data[0];
                for (int c = 1; c < classes; c++) {
                    if (prediction->data[c] > max_prob) {
                        max_prob = prediction->data[c];
                        predicted_class = c;
                    }
                }

                printf("[%.2f, %.2f, %.2f, %.2f] → Class %d (%.3f)\n",
                       sample_input[0], sample_input[1], sample_input[2], sample_input[3],
                       predicted_class, max_prob);
            }

            tensor_destroy(test_input);
            tensor_destroy(prediction);
        }
    } else {
        printf("❌ Training failed\n");
    }

    // Cleanup
    tensor_destroy(x_tensor);
    tensor_destroy(y_tensor);
    free(x_data);
    free(y_data);
    neural_network_destroy(net);
    loss_destroy(loss);
    optimizer_destroy(optimizer);
}

/**
 * @brief Display system information
 */
void display_system_info() {
    printf("🧠 NEURAL NETWORK SYSTEM\n");
    printf("========================\n");
    printf("A comprehensive artificial neural network implementation in pure C\n\n");

    printf("🎯 Key Features:\n");
    printf("• Multiple network architectures (MLP, CNN, RNN)\n");
    printf("• Various activation functions (ReLU, Sigmoid, Tanh, Softmax)\n");
    printf("• Multiple optimizers (SGD, Adam, RMSProp)\n");
    printf("• Loss functions (MSE, Cross-Entropy, Huber)\n");
    printf("• Regularization techniques (Dropout, L2)\n");
    printf("• Batch processing and mini-batch training\n");
    printf("• Model serialization and loading\n\n");

    printf("📊 Technical Specifications:\n");
    printf("• Pure C implementation (C99)\n");
    printf("• Cross-platform compatibility\n");
    printf("• Dynamic memory management\n");
    printf("• Custom tensor operations\n");
    printf("• No external dependencies\n\n");

    printf("🚀 Available Demos:\n");
    printf("1. XOR Problem - Classic neural network example\n");
    printf("2. Multi-Class Classification - General classification task\n");
    printf("3. System Information - This display\n\n");
}

/**
 * @brief Display menu and get user choice
 * @return Selected option
 */
int display_menu() {
    printf("🎮 Select a Demo:\n");
    printf("================\n");
    printf("1. XOR Neural Network\n");
    printf("2. Multi-Class Classification\n");
    printf("3. System Information\n");
    printf("0. Exit\n\n");

    printf("Enter your choice (0-3): ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

// ============================================================================
// Main Application
// ============================================================================

int main(int argc, char* argv[]) {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Check command line arguments
    if (argc > 1) {
        if (strcmp(argv[1], "--xor") == 0) {
            demo_xor_network();
            return 0;
        } else if (strcmp(argv[1], "--classification") == 0) {
            demo_classification_network();
            return 0;
        } else if (strcmp(argv[1], "--info") == 0) {
            display_system_info();
            return 0;
        }
    }

    // Interactive mode
    display_system_info();

    bool running = true;
    while (running) {
        int choice = display_menu();

        switch (choice) {
            case 1:
                demo_xor_network();
                break;
            case 2:
                demo_classification_network();
                break;
            case 3:
                display_system_info();
                break;
            case 0:
                running = false;
                break;
            default:
                printf("❌ Invalid choice. Please try again.\n\n");
                break;
        }

        if (running) {
            printf("\nPress Enter to continue...");
            getchar(); // Consume newline from scanf
            getchar(); // Wait for user input
            printf("\n");
        }
    }

    printf("👋 Thank you for using Neural Network System!\n");
    return 0;
}