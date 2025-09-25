/*
 * Neural Network System - Optimizers Header
 * Defines various optimization algorithms for training neural networks
 */

#ifndef NEURAL_NETWORK_OPTIMIZERS_H
#define NEURAL_NETWORK_OPTIMIZERS_H

#include "neural_net.h"

// ============================================================================
// Optimizer Structures
// ============================================================================

/**
 * @brief Optimizer function structure
 */
typedef struct {
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
    void (*update)(Tensor*, Tensor*, float, void*); // Parameter update function
} OptimizerFunction;

// ============================================================================
// Optimizer Creation and Management
// ============================================================================

/**
 * @brief Create optimizer
 * @param type Optimizer type
 * @param learning_rate Learning rate
 * @return Optimizer pointer or NULL on failure
 */
Optimizer* optimizer_create(OptimizerType type, float learning_rate);

/**
 * @brief Destroy optimizer
 * @param optimizer Optimizer to destroy
 */
void optimizer_destroy(Optimizer* optimizer);

/**
 * @brief Update layer parameters using optimizer
 * @param optimizer Optimizer
 * @param layer Layer to update
 * @param layer_index Layer index in network
 */
void optimizer_update_layer(Optimizer* optimizer, Layer* layer, int layer_index);

/**
 * @brief Reset optimizer state
 * @param optimizer Optimizer to reset
 */
void optimizer_reset(Optimizer* optimizer);

// ============================================================================
// Stochastic Gradient Descent (SGD)
// ============================================================================

/**
 * @brief SGD update: w = w - lr * grad
 * @param weights Weight tensor
 * @param gradients Gradient tensor
 * @param learning_rate Learning rate
 * @param user_data Optimizer state (unused for SGD)
 */
void optimizer_sgd_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data);

/**
 * @brief SGD with momentum update
 * @param weights Weight tensor
 * @param gradients Gradient tensor
 * @param learning_rate Learning rate
 * @param user_data Momentum state
 */
void optimizer_sgd_momentum_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data);

// ============================================================================
// Adaptive Gradient (AdaGrad)
// ============================================================================

/**
 * @brief AdaGrad update: accumulates squared gradients
 * @param weights Weight tensor
 * @param gradients Gradient tensor
 * @param learning_rate Learning rate
 * @param user_data AdaGrad state (accumulated squares)
 */
void optimizer_adagrad_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data);

// ============================================================================
// RMSProp Optimizer
// ============================================================================

/**
 * @brief RMSProp update: exponentially weighted moving average of squared gradients
 * @param weights Weight tensor
 * @param gradients Gradient tensor
 * @param learning_rate Learning rate
 * @param user_data RMSProp state
 */
void optimizer_rmsprop_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data);

// ============================================================================
// Adam Optimizer
// ============================================================================

/**
 * @brief Adam update: adaptive moment estimation
 * @param weights Weight tensor
 * @param gradients Gradient tensor
 * @param learning_rate Learning rate
 * @param user_data Adam state (m, v, t)
 */
void optimizer_adam_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data);

/**
 * @brief Adamax update: Adam with infinity norm
 * @param weights Weight tensor
 * @param gradients Gradient tensor
 * @param learning_rate Learning rate
 * @param user_data Adamax state
 */
void optimizer_adamax_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data);

/**
 * @brief NAdam update: Adam with Nesterov momentum
 * @param weights Weight tensor
 * @param gradients Gradient tensor
 * @param learning_rate Learning rate
 * @param user_data NAdam state
 */
void optimizer_nadam_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data);

// ============================================================================
// Optimizer Utilities
// ============================================================================

/**
 * @brief Get optimizer name
 * @param type Optimizer type
 * @return Optimizer name string
 */
const char* optimizer_get_name(OptimizerType type);

/**
 * @brief Check if optimizer uses momentum
 * @param type Optimizer type
 * @return True if momentum-based
 */
bool optimizer_uses_momentum(OptimizerType type);

/**
 * @brief Check if optimizer is adaptive
 * @param type Optimizer type
 * @return True if adaptive (adjusts learning rate per parameter)
 */
bool optimizer_is_adaptive(OptimizerType type);

/**
 * @brief Get recommended optimizer for network type
 * @param network_type Network architecture type
 * @return Recommended optimizer type
 */
OptimizerType optimizer_recommend(const char* network_type);

/**
 * @brief Set optimizer hyperparameters
 * @param optimizer Optimizer to configure
 * @param param Parameter name
 * @param value Parameter value
 * @return Success status
 */
bool optimizer_set_param(Optimizer* optimizer, const char* param, float value);

/**
 * @brief Get optimizer hyperparameters
 * @param optimizer Optimizer
 * @param param Parameter name
 * @return Parameter value or 0.0 if not found
 */
float optimizer_get_param(Optimizer* optimizer, const char* param);

// ============================================================================
// Learning Rate Scheduling
// ============================================================================

/**
 * @brief Learning rate scheduler types
 */
typedef enum {
    LR_SCHEDULER_CONSTANT,      // Constant learning rate
    LR_SCHEDULER_STEP,          // Step decay
    LR_SCHEDULER_EXPONENTIAL,   // Exponential decay
    LR_SCHEDULER_COSINE,        // Cosine annealing
    LR_SCHEDULER_LINEAR         // Linear decay
} LRSchedulerType;

/**
 * @brief Learning rate scheduler
 */
typedef struct {
    LRSchedulerType type;       // Scheduler type
    float initial_lr;            // Initial learning rate
    float final_lr;              // Final learning rate
    int decay_steps;             // Steps for decay
    float decay_rate;            // Decay rate
    int current_step;            // Current step
} LRScheduler;

/**
 * @brief Create learning rate scheduler
 * @param type Scheduler type
 * @param initial_lr Initial learning rate
 * @param final_lr Final learning rate
 * @param decay_steps Steps for decay
 * @return Learning rate scheduler
 */
LRScheduler* lr_scheduler_create(LRSchedulerType type, float initial_lr,
                                float final_lr, int decay_steps);

/**
 * @brief Destroy learning rate scheduler
 * @param scheduler Scheduler to destroy
 */
void lr_scheduler_destroy(LRScheduler* scheduler);

/**
 * @brief Get learning rate for current step
 * @param scheduler Learning rate scheduler
 * @return Current learning rate
 */
float lr_scheduler_get_lr(LRScheduler* scheduler);

/**
 * @brief Step the learning rate scheduler
 * @param scheduler Scheduler to step
 */
void lr_scheduler_step(LRScheduler* scheduler);

/**
 * @brief Attach scheduler to optimizer
 * @param optimizer Optimizer
 * @param scheduler Learning rate scheduler
 */
void optimizer_attach_scheduler(Optimizer* optimizer, LRScheduler* scheduler);

// ============================================================================
// Custom Optimizers
// ============================================================================

/**
 * @brief Create custom optimizer
 * @param update_func Custom update function
 * @param name Custom optimizer name
 * @param learning_rate Learning rate
 * @return Custom optimizer or NULL on failure
 */
Optimizer* optimizer_create_custom(void (*update_func)(Tensor*, Tensor*, float, void*),
                                  const char* name, float learning_rate);

/**
 * @brief Set optimizer user data
 * @param optimizer Optimizer
 * @param user_data User data pointer
 */
void optimizer_set_user_data(Optimizer* optimizer, void* user_data);

/**
 * @brief Get optimizer user data
 * @param optimizer Optimizer
 * @return User data pointer
 */
void* optimizer_get_user_data(Optimizer* optimizer);

#endif // NEURAL_NETWORK_OPTIMIZERS_H