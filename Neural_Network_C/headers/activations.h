/*
 * Neural Network System - Activation Functions Header
 * Defines various activation functions and their derivatives
 */

#ifndef NEURAL_NETWORK_ACTIVATIONS_H
#define NEURAL_NETWORK_ACTIVATIONS_H

#include <math.h>

// ============================================================================
// Activation Function Types
// ============================================================================

/**
 * @brief Activation function pointer type
 */
typedef void (*ActivationFunction)(float*, int);

/**
 * @brief Activation derivative function pointer type
 */
typedef void (*ActivationDerivative)(float*, int);

// ============================================================================
// Sigmoid Activation
// ============================================================================

/**
 * @brief Sigmoid activation function: σ(x) = 1 / (1 + e^(-x))
 * @param x Input/output array
 * @param size Array size
 */
void activation_sigmoid(float* x, int size);

/**
 * @brief Sigmoid derivative: σ'(x) = σ(x) * (1 - σ(x))
 * @param x Input array (sigmoid outputs)
 * @param size Array size
 */
void activation_sigmoid_derivative(float* x, int size);

// ============================================================================
// Tanh (Hyperbolic Tangent) Activation
// ============================================================================

/**
 * @brief Tanh activation function: tanh(x) = (e^x - e^(-x)) / (e^x + e^(-x))
 * @param x Input/output array
 * @param size Array size
 */
void activation_tanh(float* x, int size);

/**
 * @brief Tanh derivative: tanh'(x) = 1 - tanh²(x)
 * @param x Input array (tanh outputs)
 * @param size Array size
 */
void activation_tanh_derivative(float* x, int size);

// ============================================================================
// ReLU (Rectified Linear Unit) Activation
// ============================================================================

/**
 * @brief ReLU activation function: relu(x) = max(0, x)
 * @param x Input/output array
 * @param size Array size
 */
void activation_relu(float* x, int size);

/**
 * @brief ReLU derivative: relu'(x) = 1 if x > 0, 0 otherwise
 * @param x Input array (original inputs, not ReLU outputs)
 * @param size Array size
 */
void activation_relu_derivative(float* x, int size);

// ============================================================================
// Leaky ReLU Activation
// ============================================================================

/**
 * @brief Leaky ReLU activation function: leaky_relu(x) = x if x > 0, 0.01x otherwise
 * @param x Input/output array
 * @param size Array size
 */
void activation_leaky_relu(float* x, int size);

/**
 * @brief Leaky ReLU derivative: leaky_relu'(x) = 1 if x > 0, 0.01 otherwise
 * @param x Input array (original inputs, not Leaky ReLU outputs)
 * @param size Array size
 */
void activation_leaky_relu_derivative(float* x, int size);

// ============================================================================
// ELU (Exponential Linear Unit) Activation
// ============================================================================

/**
 * @brief ELU activation function: elu(x) = x if x > 0, α(e^x - 1) otherwise
 * @param x Input/output array
 * @param size Array size
 */
void activation_elu(float* x, int size);

/**
 * @brief ELU derivative: elu'(x) = 1 if x > 0, αe^x otherwise
 * @param x Input array (original inputs, not ELU outputs)
 * @param size Array size
 */
void activation_elu_derivative(float* x, int size);

// ============================================================================
// Swish Activation
// ============================================================================

/**
 * @brief Swish activation function: swish(x) = x * sigmoid(x)
 * @param x Input/output array
 * @param size Array size
 */
void activation_swish(float* x, int size);

/**
 * @brief Swish derivative: swish'(x) = swish(x) + sigmoid(x) * (1 - swish(x))
 * @param x Input array (original inputs)
 * @param size Array size
 */
void activation_swish_derivative(float* x, int size);

// ============================================================================
// Softmax Activation
// ============================================================================

/**
 * @brief Softmax activation function for multi-class classification
 * @param x Input/output array (will be modified in-place)
 * @param size Array size
 */
void activation_softmax(float* x, int size);

/**
 * @brief Softmax derivative (used in cross-entropy loss)
 * @param x Input array (softmax outputs)
 * @param size Array size
 * @note For cross-entropy loss, this is handled in the loss function
 */
void activation_softmax_derivative(float* x, int size);

// ============================================================================
// Linear Activation (Identity)
// ============================================================================

/**
 * @brief Linear activation function: linear(x) = x
 * @param x Input/output array (unchanged)
 * @param size Array size
 */
void activation_linear(float* x, int size);

/**
 * @brief Linear derivative: linear'(x) = 1
 * @param x Input array
 * @param size Array size
 */
void activation_linear_derivative(float* x, int size);

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @brief Apply activation function to array
 * @param x Input/output array
 * @param size Array size
 * @param activation Activation function to apply
 */
void activation_apply(float* x, int size, ActivationFunction activation);

/**
 * @brief Compute activation derivative
 * @param input Original input to activation function
 * @param output Activation function output
 * @param gradient Output gradient array
 * @param size Array size
 * @param activation_derivative Derivative function
 */
void activation_compute_derivative(float* input, float* output, float* gradient,
                                 int size, ActivationDerivative activation_derivative);

/**
 * @brief Get activation function by name
 * @param name Activation function name
 * @return Activation function pointer or NULL if not found
 */
ActivationFunction activation_get_function(const char* name);

/**
 * @brief Get activation derivative by name
 * @param name Activation function name
 * @return Activation derivative pointer or NULL if not found
 */
ActivationDerivative activation_get_derivative(const char* name);

/**
 * @brief List all available activation functions
 * @param names Output array for function names
 * @param max_names Maximum number of names to return
 * @return Number of activation functions
 */
int activation_list_functions(char** names, int max_names);

// ============================================================================
// Activation Function Properties
// ============================================================================

/**
 * @brief Check if activation function is bounded
 * @param activation Activation function
 * @return True if output is bounded (e.g., sigmoid, tanh)
 */
bool activation_is_bounded(ActivationFunction activation);

/**
 * @brief Check if activation function has zero mean
 * @param activation Activation function
 * @return True if output has approximately zero mean
 */
bool activation_has_zero_mean(ActivationFunction activation);

/**
 * @brief Get activation function range
 * @param activation Activation function
 * @param min_output Minimum output value
 * @param max_output Maximum output value
 */
void activation_get_range(ActivationFunction activation, float* min_output, float* max_output);

/**
 * @brief Check if activation function is monotonic
 * @param activation Activation function
 * @return True if function is monotonically increasing
 */
bool activation_is_monotonic(ActivationFunction activation);

// ============================================================================
// Advanced Activation Functions
// ============================================================================

/**
 * @brief GELU (Gaussian Error Linear Unit) activation
 * @param x Input/output array
 * @param size Array size
 */
void activation_gelu(float* x, int size);

/**
 * @brief SELU (Scaled Exponential Linear Unit) activation
 * @param x Input/output array
 * @param size Array size
 */
void activation_selu(float* x, int size);

/**
 * @brief Mish activation function
 * @param x Input/output array
 * @param size Array size
 */
void activation_mish(float* x, int size);

// ============================================================================
// Batch Normalization Compatible Activations
// ============================================================================

/**
 * @brief Check if activation works well with batch normalization
 * @param activation Activation function
 * @return True if compatible with batch norm
 */
bool activation_batch_norm_compatible(ActivationFunction activation);

/**
 * @brief Get recommended activation for batch normalization
 * @param use_batch_norm Whether batch normalization is used
 * @return Recommended activation function
 */
ActivationFunction activation_recommend_for_batch_norm(bool use_batch_norm);

// ============================================================================
// Performance Considerations
// ============================================================================

/**
 * @brief Check if activation function is computationally expensive
 * @param activation Activation function
 * @return True if expensive (e.g., exp, log operations)
 */
bool activation_is_expensive(ActivationFunction activation);

/**
 * @brief Get activation function memory requirements
 * @param activation Activation function
 * @param input_size Input size
 * @return Additional memory required in bytes
 */
size_t activation_memory_requirement(ActivationFunction activation, int input_size);

#endif // NEURAL_NETWORK_ACTIVATIONS_H