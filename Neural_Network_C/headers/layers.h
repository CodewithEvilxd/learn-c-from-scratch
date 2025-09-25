/*
 * Neural Network System - Layer Implementations Header
 * Defines various neural network layer types and their operations
 */

#ifndef NEURAL_NETWORK_LAYERS_H
#define NEURAL_NETWORK_LAYERS_H

#include <stdio.h>
#include "neural_net.h"

// ============================================================================
// Dense (Fully Connected) Layer
// ============================================================================

/**
 * @brief Dense layer parameters
 */
typedef struct {
    int input_size;             // Input feature size
    int output_size;            // Output feature size
    void (*activation)(float*, int); // Activation function
    void (*activation_derivative)(float*, int); // Activation derivative
    float dropout_rate;         // Dropout rate (0.0 = no dropout)
} DenseParams;

/**
 * @brief Dense layer data
 */
typedef struct {
    DenseParams params;         // Layer parameters
    Tensor* weights;            // Weight matrix (output_size x input_size)
    Tensor* biases;             // Bias vector (output_size)
    Tensor* weight_gradients;   // Weight gradients for backprop
    Tensor* bias_gradients;     // Bias gradients for backprop
    float* dropout_mask;        // Dropout mask for training
} DenseData;

/**
 * @brief Create a dense layer
 * @param input_size Number of input features
 * @param output_size Number of output features
 * @param activation Activation function
 * @return Pointer to created layer or NULL on failure
 */
Layer* layer_dense_create(int input_size, int output_size,
                         void (*activation)(float*, int));

/**
 * @brief Initialize dense layer weights
 * @param layer Dense layer to initialize
 * @param method Initialization method ("random", "xavier", "he")
 */
void layer_dense_init_weights(Layer* layer, const char* method);

// ============================================================================
// Convolutional 2D Layer
// ============================================================================

/**
 * @brief Convolutional layer parameters
 */
typedef struct {
    int input_channels;         // Number of input channels
    int output_channels;        // Number of output channels
    int kernel_size;            // Convolution kernel size (square)
    int stride;                 // Convolution stride
    int padding;                // Padding size
    void (*activation)(float*, int); // Activation function
} Conv2DParams;

/**
 * @brief Convolutional layer data
 */
typedef struct {
    Conv2DParams params;        // Layer parameters
    Tensor* kernels;            // Convolution kernels
    Tensor* biases;             // Bias terms
    Tensor* kernel_gradients;   // Kernel gradients
    Tensor* bias_gradients;     // Bias gradients
    int input_height;           // Input feature map height
    int input_width;            // Input feature map width
    int output_height;          // Output feature map height
    int output_width;           // Output feature map width
} Conv2DData;

/**
 * @brief Create a 2D convolutional layer
 * @param input_channels Number of input channels
 * @param output_channels Number of output channels
 * @param kernel_size Size of convolution kernel
 * @param stride Convolution stride
 * @param padding Padding size
 * @param activation Activation function
 * @return Pointer to created layer or NULL on failure
 */
Layer* layer_conv2d_create(int input_channels, int output_channels,
                          int kernel_size, int stride, int padding,
                          void (*activation)(float*, int));

// ============================================================================
// Pooling Layers
// ============================================================================

/**
 * @brief Pooling layer parameters
 */
typedef struct {
    int pool_size;              // Pooling window size (square)
    int stride;                 // Pooling stride
    int padding;                // Padding size
} PoolParams;

/**
 * @brief Max pooling layer data
 */
typedef struct {
    PoolParams params;          // Pooling parameters
    int* max_indices;           // Indices of maximum values for backprop
    int input_height;           // Input height
    int input_width;            // Input width
    int output_height;          // Output height
    int output_width;           // Output width
} MaxPoolData;

/**
 * @brief Create a 2D max pooling layer
 * @param pool_size Pooling window size
 * @param stride Pooling stride
 * @return Pointer to created layer or NULL on failure
 */
Layer* layer_maxpool2d_create(int pool_size, int stride);

/**
 * @brief Create a 2D average pooling layer
 * @param pool_size Pooling window size
 * @param stride Pooling stride
 * @return Pointer to created layer or NULL on failure
 */
Layer* layer_avgpool2d_create(int pool_size, int stride);

// ============================================================================
// Utility Layers
// ============================================================================

/**
 * @brief Flatten layer data
 */
typedef struct {
    int input_size;             // Total input size
    int* input_shape;           // Original input shape
    int input_ndim;             // Number of input dimensions
} FlattenData;

/**
 * @brief Create a flatten layer
 * @return Pointer to created layer or NULL on failure
 */
Layer* layer_flatten_create();

/**
 * @brief Dropout layer data
 */
typedef struct {
    float dropout_rate;         // Dropout probability
    float* dropout_mask;        // Dropout mask
    bool training;              // Whether in training mode
} DropoutData;

/**
 * @brief Create a dropout layer
 * @param dropout_rate Dropout probability (0.0 to 1.0)
 * @return Pointer to created layer or NULL on failure
 */
Layer* layer_dropout_create(float dropout_rate);

// ============================================================================
// Recurrent Layers
// ============================================================================

/**
 * @brief LSTM layer parameters
 */
typedef struct {
    int input_size;             // Input feature size
    int hidden_size;            // Hidden state size
    bool return_sequences;      // Whether to return all sequences
} LSTMParams;

/**
 * @brief LSTM layer data
 */
typedef struct {
    LSTMParams params;          // Layer parameters
    Tensor* input_weights;      // Input-to-hidden weights
    Tensor* hidden_weights;     // Hidden-to-hidden weights
    Tensor* biases;             // Bias terms
    Tensor* cell_state;         // Cell state
    Tensor* hidden_state;       // Hidden state
    Tensor* input_gradients;    // Input weight gradients
    Tensor* hidden_gradients;   // Hidden weight gradients
    Tensor* bias_gradients;     // Bias gradients
} LSTMData;

/**
 * @brief Create an LSTM layer
 * @param input_size Input feature size
 * @param hidden_size Hidden state size
 * @param return_sequences Whether to return all sequences
 * @return Pointer to created layer or NULL on failure
 */
Layer* layer_lstm_create(int input_size, int hidden_size, bool return_sequences);

/**
 * @brief GRU layer parameters
 */
typedef struct {
    int input_size;             // Input feature size
    int hidden_size;            // Hidden state size
    bool return_sequences;      // Whether to return all sequences
} GRUParams;

/**
 * @brief Create a GRU layer
 * @param input_size Input feature size
 * @param hidden_size Hidden state size
 * @param return_sequences Whether to return all sequences
 * @return Pointer to created layer or NULL on failure
 */
Layer* layer_gru_create(int input_size, int hidden_size, bool return_sequences);

// ============================================================================
// Layer Management Functions
// ============================================================================

/**
 * @brief Destroy a layer
 * @param layer Layer to destroy
 */
void layer_destroy(Layer* layer);

/**
 * @brief Get layer parameter count
 * @param layer Target layer
 * @return Number of parameters in the layer
 */
int layer_get_parameter_count(Layer* layer);

/**
 * @brief Set layer training mode
 * @param layer Target layer
 * @param training Whether in training mode
 */
void layer_set_training_mode(Layer* layer, bool training);

/**
 * @brief Reset layer state (for recurrent layers)
 * @param layer Target layer
 */
void layer_reset_state(Layer* layer);

/**
 * @brief Clone a layer
 * @param source Source layer
 * @return Cloned layer or NULL on failure
 */
Layer* layer_clone(Layer* source);

/**
 * @brief Save layer to file
 * @param layer Layer to save
 * @param file File pointer
 * @return Success status
 */
bool layer_save_to_file(Layer* layer, FILE* file);

/**
 * @brief Load layer from file
 * @param file File pointer
 * @return Loaded layer or NULL on failure
 */
Layer* layer_load_from_file(FILE* file);

// ============================================================================
// Layer Forward Pass Functions
// ============================================================================

/**
 * @brief Dense layer forward pass
 * @param layer Dense layer
 * @param input Input tensor
 * @return Output tensor or NULL on failure
 */
Tensor* layer_dense_forward(Layer* layer, Tensor* input);

/**
 * @brief Dense layer backward pass
 * @param layer Dense layer
 * @param gradient_output Output gradient
 * @return Input gradient or NULL on failure
 */
Tensor* layer_dense_backward(Layer* layer, Tensor* gradient_output);

/**
 * @brief Convolutional layer forward pass
 * @param layer Convolutional layer
 * @param input Input tensor
 * @return Output tensor or NULL on failure
 */
Tensor* layer_conv2d_forward(Layer* layer, Tensor* input);

/**
 * @brief Convolutional layer backward pass
 * @param layer Convolutional layer
 * @param gradient_output Output gradient
 * @return Input gradient or NULL on failure
 */
Tensor* layer_conv2d_backward(Layer* layer, Tensor* gradient_output);

/**
 * @brief Max pooling forward pass
 * @param layer Max pooling layer
 * @param input Input tensor
 * @return Output tensor or NULL on failure
 */
Tensor* layer_maxpool_forward(Layer* layer, Tensor* input);

/**
 * @brief Max pooling backward pass
 * @param layer Max pooling layer
 * @param gradient_output Output gradient
 * @return Input gradient or NULL on failure
 */
Tensor* layer_maxpool_backward(Layer* layer, Tensor* gradient_output);

/**
 * @brief Average pooling forward pass
 * @param layer Average pooling layer
 * @param input Input tensor
 * @return Output tensor or NULL on failure
 */
Tensor* layer_avgpool_forward(Layer* layer, Tensor* input);

/**
 * @brief Average pooling backward pass
 * @param layer Average pooling layer
 * @param gradient_output Output gradient
 * @return Input gradient or NULL on failure
 */
Tensor* layer_avgpool_backward(Layer* layer, Tensor* gradient_output);

/**
 * @brief Flatten layer forward pass
 * @param layer Flatten layer
 * @param input Input tensor
 * @return Output tensor or NULL on failure
 */
Tensor* layer_flatten_forward(Layer* layer, Tensor* input);

/**
 * @brief Flatten layer backward pass
 * @param layer Flatten layer
 * @param gradient_output Output gradient
 * @return Input gradient or NULL on failure
 */
Tensor* layer_flatten_backward(Layer* layer, Tensor* gradient_output);

/**
 * @brief Dropout layer forward pass
 * @param layer Dropout layer
 * @param input Input tensor
 * @return Output tensor or NULL on failure
 */
Tensor* layer_dropout_forward(Layer* layer, Tensor* input);

/**
 * @brief Dropout layer backward pass
 * @param layer Dropout layer
 * @param gradient_output Output gradient
 * @return Input gradient or NULL on failure
 */
Tensor* layer_dropout_backward(Layer* layer, Tensor* gradient_output);

/**
 * @brief LSTM layer forward pass
 * @param layer LSTM layer
 * @param input Input tensor
 * @return Output tensor or NULL on failure
 */
Tensor* layer_lstm_forward(Layer* layer, Tensor* input);

/**
 * @brief LSTM layer backward pass
 * @param layer LSTM layer
 * @param gradient_output Output gradient
 * @return Input gradient or NULL on failure
 */
Tensor* layer_lstm_backward(Layer* layer, Tensor* gradient_output);

// ============================================================================
// Layer Utility Functions
// ============================================================================

/**
 * @brief Initialize layer weights using Xavier initialization
 * @param weights Weight tensor
 * @param fan_in Number of input units
 * @param fan_out Number of output units
 */
void layer_init_weights_xavier(Tensor* weights, int fan_in, int fan_out);

/**
 * @brief Initialize layer weights using He initialization
 * @param weights Weight tensor
 * @param fan_in Number of input units
 */
void layer_init_weights_he(Tensor* weights, int fan_in);

/**
 * @brief Initialize layer weights randomly
 * @param weights Weight tensor
 * @param scale Initialization scale
 */
void layer_init_weights_random(Tensor* weights, float scale);

/**
 * @brief Apply activation function to tensor
 * @param tensor Target tensor
 * @param activation Activation function
 */
void layer_apply_activation(Tensor* tensor, void (*activation)(float*, int));

/**
 * @brief Compute activation derivative
 * @param tensor Input tensor
 * @param output_tensor Output tensor
 * @param activation_derivative Activation derivative function
 */
void layer_compute_activation_derivative(Tensor* tensor, Tensor* output_tensor,
                                       void (*activation_derivative)(float*, int));

/**
 * @brief Zero out layer gradients
 * @param layer Target layer
 */
void layer_zero_gradients(Layer* layer);

/**
 * @brief Clip layer gradients
 * @param layer Target layer
 * @param max_norm Maximum gradient norm
 */
void layer_clip_gradients(Layer* layer, float max_norm);

#endif // NEURAL_NETWORK_LAYERS_H