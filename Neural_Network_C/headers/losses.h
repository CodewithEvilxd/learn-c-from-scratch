/*
 * Neural Network System - Loss Functions Header
 * Defines various loss functions and their gradients
 */

#ifndef NEURAL_NETWORK_LOSSES_H
#define NEURAL_NETWORK_LOSSES_H

#include "neural_net.h"

// ============================================================================
// Loss Function Structures
// ============================================================================

/**
 * @brief Loss function structure
 */
typedef struct {
    char name[64];              // Loss function name
    LossType type;              // Loss function type

    // Loss computation
    float (*compute)(Tensor*, Tensor*);  // Compute loss
    Tensor* (*gradient)(Tensor*, Tensor*); // Compute gradient
} LossFunction;

// ============================================================================
// Loss Function Implementations
// ============================================================================

/**
 * @brief Create loss function
 * @param type Loss function type
 * @return Loss function pointer or NULL on failure
 */
Loss* loss_create(LossType type);

/**
 * @brief Destroy loss function
 * @param loss Loss function to destroy
 */
void loss_destroy(Loss* loss);

/**
 * @brief Compute loss value
 * @param loss Loss function
 * @param predictions Network predictions
 * @param targets Target values
 * @return Loss value
 */
float loss_compute(Loss* loss, Tensor* predictions, Tensor* targets);

/**
 * @brief Compute loss gradient
 * @param loss Loss function
 * @param predictions Network predictions
 * @param targets Target values
 * @return Loss gradient tensor
 */
Tensor* loss_gradient(Loss* loss, Tensor* predictions, Tensor* targets);

// ============================================================================
// Mean Squared Error (MSE) Loss
// ============================================================================

/**
 * @brief MSE loss: (1/n) * Σ(y_true - y_pred)²
 * @param predictions Predicted values
 * @param targets Target values
 * @return MSE loss value
 */
float loss_mse_compute(Tensor* predictions, Tensor* targets);

/**
 * @brief MSE gradient: (2/n) * (y_pred - y_true)
 * @param predictions Predicted values
 * @param targets Target values
 * @return MSE gradient tensor
 */
Tensor* loss_mse_gradient(Tensor* predictions, Tensor* targets);

// ============================================================================
// Cross-Entropy Loss
// ============================================================================

/**
 * @brief Cross-entropy loss for binary classification
 * @param predictions Predicted probabilities (sigmoid outputs)
 * @param targets Target values (0 or 1)
 * @return Binary cross-entropy loss
 */
float loss_binary_crossentropy_compute(Tensor* predictions, Tensor* targets);

/**
 * @brief Binary cross-entropy gradient
 * @param predictions Predicted probabilities
 * @param targets Target values
 * @return Gradient tensor
 */
Tensor* loss_binary_crossentropy_gradient(Tensor* predictions, Tensor* targets);

/**
 * @brief Categorical cross-entropy loss for multi-class classification
 * @param predictions Predicted probabilities (softmax outputs)
 * @param targets One-hot encoded targets
 * @return Categorical cross-entropy loss
 */
float loss_categorical_crossentropy_compute(Tensor* predictions, Tensor* targets);

/**
 * @brief Categorical cross-entropy gradient
 * @param predictions Predicted probabilities
 * @param targets One-hot encoded targets
 * @return Gradient tensor
 */
Tensor* loss_categorical_crossentropy_gradient(Tensor* predictions, Tensor* targets);

// ============================================================================
// Huber Loss
// ============================================================================

/**
 * @brief Huber loss (combination of MSE and MAE)
 * @param predictions Predicted values
 * @param targets Target values
 * @param delta Threshold parameter
 * @return Huber loss value
 */
float loss_huber_compute(Tensor* predictions, Tensor* targets, float delta);

/**
 * @brief Huber loss gradient
 * @param predictions Predicted values
 * @param targets Target values
 * @param delta Threshold parameter
 * @return Gradient tensor
 */
Tensor* loss_huber_gradient(Tensor* predictions, Tensor* targets, float delta);

// ============================================================================
// Loss Function Utilities
// ============================================================================

/**
 * @brief Get loss function name
 * @param type Loss function type
 * @return Loss function name string
 */
const char* loss_get_name(LossType type);

/**
 * @brief Check if loss function is for classification
 * @param type Loss function type
 * @return True if classification loss
 */
bool loss_is_classification(LossType type);

/**
 * @brief Check if loss function is for regression
 * @param type Loss function type
 * @return True if regression loss
 */
bool loss_is_regression(LossType type);

/**
 * @brief Get recommended loss function for task
 * @param num_classes Number of classes (0 for regression)
 * @return Recommended loss function type
 */
LossType loss_recommend(int num_classes);

/**
 * @brief Validate loss function for given outputs
 * @param loss Loss function
 * @param predictions Predictions tensor
 * @param targets Targets tensor
 * @return True if valid
 */
bool loss_validate(Loss* loss, Tensor* predictions, Tensor* targets);

// ============================================================================
// Custom Loss Functions
// ============================================================================

/**
 * @brief Create custom loss function
 * @param compute_func Custom loss computation function
 * @param gradient_func Custom gradient computation function
 * @param name Custom loss name
 * @return Custom loss function or NULL on failure
 */
Loss* loss_create_custom(float (*compute_func)(Tensor*, Tensor*),
                        Tensor* (*gradient_func)(Tensor*, Tensor*),
                        const char* name);

/**
 * @brief Set loss function user data
 * @param loss Loss function
 * @param user_data User data pointer
 */
void loss_set_user_data(Loss* loss, void* user_data);

/**
 * @brief Get loss function user data
 * @param loss Loss function
 * @return User data pointer
 */
void* loss_get_user_data(Loss* loss);

#endif // NEURAL_NETWORK_LOSSES_H