/*
 * Neural Network System - Main Neural Network Header
 * Defines the core neural network structures, training, and inference
 */

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdint.h>
#include <stdbool.h>

// Forward declarations
typedef struct Tensor Tensor;
typedef struct Layer Layer;
typedef struct Loss Loss;
typedef struct Optimizer Optimizer;
typedef struct NeuralNetwork NeuralNetwork;
typedef struct TrainingConfig TrainingConfig;

// ============================================================================
// Tensor Data Structure
// ============================================================================

/**
 * @brief Multi-dimensional tensor for neural network computations
 */
struct Tensor {
    float* data;                // Contiguous data array
    int* shape;                 // Dimension sizes
    int ndim;                   // Number of dimensions
    int size;                   // Total number of elements
    bool requires_grad;         // Whether gradients are needed
    float* grad;                // Gradient data (if requires_grad)
};

// ============================================================================
// Tensor Functions
// ============================================================================

/**
 * @brief Create a tensor
 * @param data Data array (can be NULL for zero initialization)
 * @param shape Shape array
 * @param ndim Number of dimensions
 * @return Created tensor or NULL on failure
 */
Tensor* tensor_create(float* data, int* shape, int ndim);

/**
 * @brief Destroy a tensor
 * @param tensor Tensor to destroy
 */
void tensor_destroy(Tensor* tensor);

// ============================================================================
// Layer System
// ============================================================================

/**
 * @brief Layer types supported by the network
 */
typedef enum {
    LAYER_DENSE,                // Fully connected layer
    LAYER_CONV2D,               // 2D convolutional layer
    LAYER_MAXPOOL2D,            // 2D max pooling layer
    LAYER_AVGPOOL2D,            // 2D average pooling layer
    LAYER_FLATTEN,              // Flatten layer
    LAYER_DROPOUT,              // Dropout regularization
    LAYER_BATCH_NORM,           // Batch normalization
    LAYER_LSTM,                 // Long short-term memory
    LAYER_GRU,                  // Gated recurrent unit
    LAYER_EMBEDDING             // Embedding layer
} LayerType;

/**
 * @brief Base layer structure
 */
struct Layer {
    char name[64];              // Layer name
    LayerType type;             // Layer type

    // Input/output shapes
    int* input_shape;           // Input tensor shape
    int* output_shape;          // Output tensor shape
    int input_ndim;             // Input dimensions
    int output_ndim;            // Output dimensions

    // Parameters
    Tensor** weights;           // Weight tensors
    Tensor** biases;            // Bias tensors
    Tensor** weight_gradients;  // Weight gradients for backprop
    Tensor** bias_gradients;    // Bias gradients for backprop
    int num_weights;            // Number of weight tensors
    int num_biases;             // Number of bias tensors

    // Forward/backward functions
    Tensor* (*forward)(struct Layer*, Tensor*);  // Forward pass
    Tensor* (*backward)(struct Layer*, Tensor*); // Backward pass

    // Layer-specific data
    void* layer_data;           // Layer-specific parameters
    bool trainable;             // Whether layer is trainable

    // State
    Tensor* input_cache;        // Cached input for backprop
    Tensor* output_cache;       // Cached output for backprop
};

// ============================================================================
// Loss Functions
// ============================================================================

/**
 * @brief Loss function types
 */
typedef enum {
    LOSS_MSE,                   // Mean squared error
    LOSS_CROSS_ENTROPY,         // Cross entropy
    LOSS_BINARY_CROSS_ENTROPY,  // Binary cross entropy
    LOSS_CATEGORICAL_CROSS_ENTROPY, // Categorical cross entropy
    LOSS_HUBER                  // Huber loss
} LossType;

/**
 * @brief Loss function structure
 */
struct Loss {
    char name[64];              // Loss function name
    LossType type;              // Loss function type

    // Loss computation
    float (*compute)(Tensor*, Tensor*);  // Compute loss
    Tensor* (*gradient)(Tensor*, Tensor*); // Compute gradient

    // User data
    void* user_data;            // User-defined data
};

// ============================================================================
// Optimizers
// ============================================================================

/**
 * @brief Optimizer types
 */
typedef enum {
    OPTIMIZER_SGD,              // Stochastic gradient descent
    OPTIMIZER_SGD_MOMENTUM,     // SGD with momentum
    OPTIMIZER_ADAGRAD,          // Adaptive gradient
    OPTIMIZER_RMSPROP,          // RMS propagation
    OPTIMIZER_ADAM,             // Adam optimizer
    OPTIMIZER_ADAMAX,           // Adamax optimizer
    OPTIMIZER_NADAM             // NAdam optimizer
} OptimizerType;

/**
 * @brief Optimizer structure
 */
struct Optimizer {
    char name[64];              // Optimizer name
    OptimizerType type;         // Optimizer type

    // Hyperparameters
    float learning_rate;        // Learning rate
    float beta1;                // Beta1 for Adam (first moment)
    float beta2;                // Beta2 for Adam (second moment)
    float epsilon;              // Small constant for numerical stability
    float weight_decay;         // Weight decay (L2 regularization)
    float momentum;             // Momentum factor

    // State
    Tensor** m;                 // First moment estimates (Adam)
    Tensor** v;                 // Second moment estimates (Adam)
    int t;                      // Time step (for bias correction)

    // Update function
    void (*update)(Layer*, int);  // Update layer parameters

    // User data
    void* user_data;            // User-defined data
};

// ============================================================================
// Neural Network
// ============================================================================

/**
 * @brief Training configuration
 */
struct TrainingConfig {
    int epochs;                 // Number of training epochs
    int batch_size;             // Batch size for mini-batch training
    float validation_split;     // Fraction of data for validation
    bool shuffle;               // Whether to shuffle data each epoch
    int verbose;                // Verbosity level (0-2)
    bool early_stopping;        // Whether to use early stopping
    int patience;               // Early stopping patience
    float min_delta;            // Minimum change for early stopping
};

/**
 * @brief Main neural network structure
 */
struct NeuralNetwork {
    char name[256];             // Network name
    Layer** layers;             // Array of layers
    int num_layers;             // Number of layers
    int max_layers;             // Maximum layers capacity

    // Training components
    Loss* loss_function;        // Loss function
    Optimizer* optimizer;       // Optimizer
    TrainingConfig config;      // Training configuration

    // Network state
    bool compiled;              // Whether network is compiled
    bool trained;               // Whether network has been trained

    // Input/output information
    int* input_shape;           // Input tensor shape
    int* output_shape;          // Output tensor shape
    int input_size;             // Input tensor size
    int output_size;            // Output tensor size

    // Training metrics
    float* training_loss;       // Training loss history
    float* validation_loss;     // Validation loss history
    float* training_accuracy;   // Training accuracy history
    float* validation_accuracy; // Validation accuracy history
    int history_size;           // Size of training history
    int current_epoch;          // Current training epoch

    // Performance metrics
    double training_time;       // Total training time
    int parameters_count;       // Total number of parameters
    float memory_usage;         // Memory usage in MB
};

// ============================================================================
// Neural Network Management Functions
// ============================================================================

/**
 * @brief Create a new neural network
 * @param name Network name
 * @return Pointer to created network or NULL on failure
 */
NeuralNetwork* neural_network_create(const char* name);

/**
 * @brief Destroy a neural network
 * @param net Network to destroy
 */
void neural_network_destroy(NeuralNetwork* net);

/**
 * @brief Add a layer to the network
 * @param net Target network
 * @param layer Layer to add
 * @return Success status
 */
bool neural_network_add_layer(NeuralNetwork* net, Layer* layer);

/**
 * @brief Remove a layer from the network
 * @param net Target network
 * @param index Layer index to remove
 * @return Success status
 */
bool neural_network_remove_layer(NeuralNetwork* net, int index);

/**
 * @brief Compile the neural network
 * @param net Network to compile
 * @param loss Loss function
 * @param optimizer Optimizer
 * @return Success status
 */
bool neural_network_compile(NeuralNetwork* net, Loss* loss, Optimizer* optimizer);

/**
 * @brief Build the network with input shape
 * @param net Network to build
 * @param input_shape Input tensor shape
 * @param input_ndim Number of input dimensions
 * @return Success status
 */
bool neural_network_build(NeuralNetwork* net, int* input_shape, int input_ndim);

/**
 * @brief Forward pass through the network
 * @param net Network
 * @param input Input tensor
 * @return Output tensor or NULL on failure
 */
Tensor* neural_network_forward(NeuralNetwork* net, Tensor* input);

/**
 * @brief Backward pass through the network
 * @param net Network
 * @param output Network output
 * @param target Target values
 * @return Success status
 */
bool neural_network_backward(NeuralNetwork* net, Tensor* output, Tensor* target);

/**
 * @brief Update network parameters
 * @param net Network to update
 */
void neural_network_update(NeuralNetwork* net);

/**
 * @brief Train the neural network
 * @param net Network to train
 * @param x Training input data
 * @param y Training target data
 * @param config Training configuration
 * @return Success status
 */
bool neural_network_fit(NeuralNetwork* net, Tensor* x, Tensor* y, TrainingConfig config);

/**
 * @brief Make predictions with the network
 * @param net Trained network
 * @param x Input data
 * @return Predictions tensor or NULL on failure
 */
Tensor* neural_network_predict(NeuralNetwork* net, Tensor* x);

/**
 * @brief Evaluate network performance
 * @param net Network to evaluate
 * @param x Test input data
 * @param y Test target data
 * @param metrics Output metrics (loss, accuracy, etc.)
 * @return Success status
 */
bool neural_network_evaluate(NeuralNetwork* net, Tensor* x, Tensor* y, float* metrics);

/**
 * @brief Save network to file
 * @param net Network to save
 * @param filename Output filename
 * @return Success status
 */
bool neural_network_save(NeuralNetwork* net, const char* filename);

/**
 * @brief Load network from file
 * @param filename Input filename
 * @return Loaded network or NULL on failure
 */
NeuralNetwork* neural_network_load(const char* filename);

// ============================================================================
// Training Functions
// ============================================================================

/**
 * @brief Train network for one epoch
 * @param net Network to train
 * @param x_batch Input batch
 * @param y_batch Target batch
 * @param batch_size Batch size
 * @return Average loss for the batch
 */
float neural_network_train_step(NeuralNetwork* net, Tensor* x_batch, Tensor* y_batch, int batch_size);

/**
 * @brief Validate network on validation data
 * @param net Network to validate
 * @param x_val Validation input
 * @param y_val Validation target
 * @param metrics Output validation metrics
 */
void neural_network_validate(NeuralNetwork* net, Tensor* x_val, Tensor* y_val, float* metrics);

/**
 * @brief Check early stopping condition
 * @param net Network
 * @param current_loss Current validation loss
 * @return True if training should stop
 */
bool neural_network_check_early_stopping(NeuralNetwork* net, float current_loss);

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @brief Get network summary
 * @param net Network
 * @param summary Output summary string
 * @param max_length Maximum summary length
 */
void neural_network_summary(NeuralNetwork* net, char* summary, int max_length);

/**
 * @brief Get network statistics
 * @param net Network
 * @param stats Output statistics structure
 */
void neural_network_get_stats(NeuralNetwork* net, void* stats);

/**
 * @brief Reset network state
 * @param net Network to reset
 */
void neural_network_reset(NeuralNetwork* net);

/**
 * @brief Copy network architecture
 * @param source Source network
 * @return Copied network or NULL on failure
 */
NeuralNetwork* neural_network_copy(NeuralNetwork* source);

/**
 * @brief Create training configuration
 * @param epochs Number of epochs
 * @param batch_size Batch size
 * @param learning_rate Learning rate
 * @return Training configuration
 */
TrainingConfig training_config_create(int epochs, int batch_size, float learning_rate);

/**
 * @brief Print training progress
 * @param epoch Current epoch
 * @param total_epochs Total epochs
 * @param loss Current loss
 * @param accuracy Current accuracy
 * @param val_loss Validation loss (0 if not available)
 * @param val_accuracy Validation accuracy (0 if not available)
 */
void print_training_progress(int epoch, int total_epochs, float loss, float accuracy,
                           float val_loss, float val_accuracy);

#endif // NEURAL_NETWORK_H