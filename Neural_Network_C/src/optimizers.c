/*
 * Neural Network System - Optimizers Implementation
 * Implementation of various optimization algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../headers/optimizers.h"

// ============================================================================
// Optimizer Creation and Management
// ============================================================================

Optimizer* optimizer_create(OptimizerType type, float learning_rate) {
    Optimizer* optimizer = (Optimizer*)malloc(sizeof(Optimizer));
    if (!optimizer) return NULL;

    optimizer->type = type;
    optimizer->learning_rate = learning_rate;
    optimizer->user_data = NULL;

    // Set default hyperparameters
    optimizer->beta1 = 0.9f;      // Adam beta1
    optimizer->beta2 = 0.999f;    // Adam beta2
    optimizer->epsilon = 1e-8f;   // Small constant
    optimizer->weight_decay = 0.0f; // L2 regularization
    optimizer->momentum = 0.0f;   // Momentum factor

    // Initialize state
    optimizer->m = NULL;  // First moment (Adam)
    optimizer->v = NULL;  // Second moment (Adam)
    optimizer->t = 0;     // Time step

    // Set function pointers based on type
    switch (type) {
        case OPTIMIZER_SGD:
            strcpy(optimizer->name, "Stochastic Gradient Descent");
            optimizer->update = optimizer_update_layer;
            break;

        case OPTIMIZER_SGD_MOMENTUM:
            strcpy(optimizer->name, "SGD with Momentum");
            optimizer->momentum = 0.9f;
            optimizer->update = optimizer_update_layer;
            break;

        case OPTIMIZER_ADAGRAD:
            strcpy(optimizer->name, "AdaGrad");
            optimizer->update = optimizer_update_layer;
            break;

        case OPTIMIZER_RMSPROP:
            strcpy(optimizer->name, "RMSProp");
            optimizer->update = optimizer_update_layer;
            break;

        case OPTIMIZER_ADAM:
            strcpy(optimizer->name, "Adam");
            optimizer->update = optimizer_update_layer;
            break;

        case OPTIMIZER_ADAMAX:
            strcpy(optimizer->name, "Adamax");
            optimizer->update = optimizer_update_layer;
            break;

        case OPTIMIZER_NADAM:
            strcpy(optimizer->name, "NAdam");
            optimizer->update = optimizer_update_layer;
            break;

        default:
            free(optimizer);
            return NULL;
    }

    return optimizer;
}

void optimizer_destroy(Optimizer* optimizer) {
    if (!optimizer) return;

    // Free moment estimates if they exist
    if (optimizer->m) {
        // Would need to free each tensor in the array
        free(optimizer->m);
    }
    if (optimizer->v) {
        free(optimizer->v);
    }

    free(optimizer);
}

void optimizer_update_layer(Optimizer* optimizer, Layer* layer, int layer_index) {
    if (!optimizer || !layer || !optimizer->update) return;

    // Update weights if they exist
    if (layer->weights && layer->num_weights > 0) {
        for (int i = 0; i < layer->num_weights; i++) {
            if (layer->weights[i] && layer->weight_gradients && layer->weight_gradients[i]) {
                // Use appropriate update function based on optimizer type
                switch (optimizer->type) {
                    case OPTIMIZER_SGD:
                        optimizer_sgd_update(layer->weights[i], layer->weight_gradients[i],
                                           optimizer->learning_rate, NULL);
                        break;
                    case OPTIMIZER_SGD_MOMENTUM:
                        optimizer_sgd_momentum_update(layer->weights[i], layer->weight_gradients[i],
                                                    optimizer->learning_rate, NULL);
                        break;
                    case OPTIMIZER_ADAGRAD:
                        optimizer_adagrad_update(layer->weights[i], layer->weight_gradients[i],
                                               optimizer->learning_rate, NULL);
                        break;
                    case OPTIMIZER_RMSPROP:
                        optimizer_rmsprop_update(layer->weights[i], layer->weight_gradients[i],
                                               optimizer->learning_rate, NULL);
                        break;
                    case OPTIMIZER_ADAM:
                        optimizer_adam_update(layer->weights[i], layer->weight_gradients[i],
                                            optimizer->learning_rate, NULL);
                        break;
                    default:
                        optimizer_sgd_update(layer->weights[i], layer->weight_gradients[i],
                                           optimizer->learning_rate, NULL);
                        break;
                }
            }
        }
    }

    // Update biases if they exist
    if (layer->biases && layer->num_biases > 0) {
        for (int i = 0; i < layer->num_biases; i++) {
            if (layer->biases[i] && layer->bias_gradients && layer->bias_gradients[i]) {
                // Use appropriate update function based on optimizer type
                switch (optimizer->type) {
                    case OPTIMIZER_SGD:
                        optimizer_sgd_update(layer->biases[i], layer->bias_gradients[i],
                                           optimizer->learning_rate, NULL);
                        break;
                    case OPTIMIZER_SGD_MOMENTUM:
                        optimizer_sgd_momentum_update(layer->biases[i], layer->bias_gradients[i],
                                                    optimizer->learning_rate, NULL);
                        break;
                    case OPTIMIZER_ADAGRAD:
                        optimizer_adagrad_update(layer->biases[i], layer->bias_gradients[i],
                                               optimizer->learning_rate, NULL);
                        break;
                    case OPTIMIZER_RMSPROP:
                        optimizer_rmsprop_update(layer->biases[i], layer->bias_gradients[i],
                                               optimizer->learning_rate, NULL);
                        break;
                    case OPTIMIZER_ADAM:
                        optimizer_adam_update(layer->biases[i], layer->bias_gradients[i],
                                            optimizer->learning_rate, NULL);
                        break;
                    default:
                        optimizer_sgd_update(layer->biases[i], layer->bias_gradients[i],
                                           optimizer->learning_rate, NULL);
                        break;
                }
            }
        }
    }
}

void optimizer_reset(Optimizer* optimizer) {
    if (!optimizer) return;

    optimizer->t = 0;

    // Reset moment estimates (would need to zero out tensors)
    // This is a simplified version
}

// ============================================================================
// SGD Implementation
// ============================================================================

void optimizer_sgd_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data) {
    if (!weights || !gradients || weights->size != gradients->size) return;

    for (int i = 0; i < weights->size; i++) {
        weights->data[i] -= learning_rate * gradients->data[i];
    }
}

// ============================================================================
// SGD with Momentum Implementation
// ============================================================================

void optimizer_sgd_momentum_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data) {
    // Simplified momentum implementation
    // In a full implementation, this would store velocity per parameter
    static float* velocity = NULL;
    static int velocity_size = 0;

    if (!weights || !gradients || weights->size != gradients->size) return;

    // Allocate velocity if needed
    if (velocity_size != weights->size) {
        free(velocity);
        velocity = (float*)malloc(weights->size * sizeof(float));
        if (velocity) {
            memset(velocity, 0, weights->size * sizeof(float));
            velocity_size = weights->size;
        }
    }

    if (velocity) {
        float momentum = 0.9f; // Default momentum
        for (int i = 0; i < weights->size; i++) {
            velocity[i] = momentum * velocity[i] - learning_rate * gradients->data[i];
            weights->data[i] += velocity[i];
        }
    } else {
        // Fallback to regular SGD
        optimizer_sgd_update(weights, gradients, learning_rate, user_data);
    }
}

// ============================================================================
// AdaGrad Implementation
// ============================================================================

void optimizer_adagrad_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data) {
    // Simplified AdaGrad implementation
    // In a full implementation, this would accumulate squared gradients
    static float* accumulated = NULL;
    static int accumulated_size = 0;

    if (!weights || !gradients || weights->size != gradients->size) return;

    // Allocate accumulated if needed
    if (accumulated_size != weights->size) {
        free(accumulated);
        accumulated = (float*)malloc(weights->size * sizeof(float));
        if (accumulated) {
            memset(accumulated, 0, weights->size * sizeof(float));
            accumulated_size = weights->size;
        }
    }

    if (accumulated) {
        float epsilon = 1e-8f;
        for (int i = 0; i < weights->size; i++) {
            accumulated[i] += gradients->data[i] * gradients->data[i];
            float adaptive_lr = learning_rate / (sqrtf(accumulated[i]) + epsilon);
            weights->data[i] -= adaptive_lr * gradients->data[i];
        }
    } else {
        optimizer_sgd_update(weights, gradients, learning_rate, user_data);
    }
}

// ============================================================================
// RMSProp Implementation
// ============================================================================

void optimizer_rmsprop_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data) {
    // Simplified RMSProp implementation
    static float* v = NULL;
    static int v_size = 0;

    if (!weights || !gradients || weights->size != gradients->size) return;

    // Allocate v if needed
    if (v_size != weights->size) {
        free(v);
        v = (float*)malloc(weights->size * sizeof(float));
        if (v) {
            memset(v, 0, weights->size * sizeof(float));
            v_size = weights->size;
        }
    }

    if (v) {
        float beta2 = 0.999f;
        float epsilon = 1e-8f;

        for (int i = 0; i < weights->size; i++) {
            v[i] = beta2 * v[i] + (1.0f - beta2) * gradients->data[i] * gradients->data[i];
            float adaptive_lr = learning_rate / (sqrtf(v[i]) + epsilon);
            weights->data[i] -= adaptive_lr * gradients->data[i];
        }
    } else {
        optimizer_sgd_update(weights, gradients, learning_rate, user_data);
    }
}

// ============================================================================
// Adam Implementation
// ============================================================================

void optimizer_adam_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data) {
    // Simplified Adam implementation
    static float* m = NULL;
    static float* v = NULL;
    static int state_size = 0;
    static int t = 0;

    if (!weights || !gradients || weights->size != gradients->size) return;

    // Allocate state if needed
    if (state_size != weights->size) {
        free(m);
        free(v);
        m = (float*)malloc(weights->size * sizeof(float));
        v = (float*)malloc(weights->size * sizeof(float));
        if (m && v) {
            memset(m, 0, weights->size * sizeof(float));
            memset(v, 0, weights->size * sizeof(float));
            state_size = weights->size;
            t = 0;
        }
    }

    if (m && v) {
        t++;
        float beta1 = 0.9f;
        float beta2 = 0.999f;
        float epsilon = 1e-8f;

        for (int i = 0; i < weights->size; i++) {
            // Update biased first moment estimate
            m[i] = beta1 * m[i] + (1.0f - beta1) * gradients->data[i];

            // Update biased second moment estimate
            v[i] = beta2 * v[i] + (1.0f - beta2) * gradients->data[i] * gradients->data[i];

            // Compute bias-corrected estimates
            float m_hat = m[i] / (1.0f - powf(beta1, t));
            float v_hat = v[i] / (1.0f - powf(beta2, t));

            // Update parameters
            weights->data[i] -= learning_rate * m_hat / (sqrtf(v_hat) + epsilon);
        }
    } else {
        optimizer_sgd_update(weights, gradients, learning_rate, user_data);
    }
}

// ============================================================================
// Adamax and NAdam (Stub Implementations)
// ============================================================================

void optimizer_adamax_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data) {
    // Placeholder: would implement Adamax
    optimizer_adam_update(weights, gradients, learning_rate, user_data);
}

void optimizer_nadam_update(Tensor* weights, Tensor* gradients, float learning_rate, void* user_data) {
    // Placeholder: would implement NAdam
    optimizer_adam_update(weights, gradients, learning_rate, user_data);
}

// ============================================================================
// Utility Functions
// ============================================================================

const char* optimizer_get_name(OptimizerType type) {
    switch (type) {
        case OPTIMIZER_SGD: return "Stochastic Gradient Descent";
        case OPTIMIZER_SGD_MOMENTUM: return "SGD with Momentum";
        case OPTIMIZER_ADAGRAD: return "AdaGrad";
        case OPTIMIZER_RMSPROP: return "RMSProp";
        case OPTIMIZER_ADAM: return "Adam";
        case OPTIMIZER_ADAMAX: return "Adamax";
        case OPTIMIZER_NADAM: return "NAdam";
        default: return "Unknown";
    }
}

bool optimizer_uses_momentum(OptimizerType type) {
    return type == OPTIMIZER_SGD_MOMENTUM || type == OPTIMIZER_ADAM ||
           type == OPTIMIZER_ADAMAX || type == OPTIMIZER_NADAM;
}

bool optimizer_is_adaptive(OptimizerType type) {
    return type == OPTIMIZER_ADAGRAD || type == OPTIMIZER_RMSPROP ||
           type == OPTIMIZER_ADAM || type == OPTIMIZER_ADAMAX || type == OPTIMIZER_NADAM;
}

OptimizerType optimizer_recommend(const char* network_type) {
    if (strcmp(network_type, "cnn") == 0 || strcmp(network_type, "rnn") == 0) {
        return OPTIMIZER_ADAM; // Adam works well for deep networks
    } else {
        return OPTIMIZER_ADAM; // Default to Adam
    }
}

bool optimizer_set_param(Optimizer* optimizer, const char* param, float value) {
    if (!optimizer || !param) return false;

    if (strcmp(param, "learning_rate") == 0) {
        optimizer->learning_rate = value;
        return true;
    } else if (strcmp(param, "beta1") == 0) {
        optimizer->beta1 = value;
        return true;
    } else if (strcmp(param, "beta2") == 0) {
        optimizer->beta2 = value;
        return true;
    } else if (strcmp(param, "epsilon") == 0) {
        optimizer->epsilon = value;
        return true;
    } else if (strcmp(param, "weight_decay") == 0) {
        optimizer->weight_decay = value;
        return true;
    } else if (strcmp(param, "momentum") == 0) {
        optimizer->momentum = value;
        return true;
    }

    return false;
}

float optimizer_get_param(Optimizer* optimizer, const char* param) {
    if (!optimizer || !param) return 0.0f;

    if (strcmp(param, "learning_rate") == 0) {
        return optimizer->learning_rate;
    } else if (strcmp(param, "beta1") == 0) {
        return optimizer->beta1;
    } else if (strcmp(param, "beta2") == 0) {
        return optimizer->beta2;
    } else if (strcmp(param, "epsilon") == 0) {
        return optimizer->epsilon;
    } else if (strcmp(param, "weight_decay") == 0) {
        return optimizer->weight_decay;
    } else if (strcmp(param, "momentum") == 0) {
        return optimizer->momentum;
    }

    return 0.0f;
}

// ============================================================================
// Learning Rate Scheduling (Stub)
// ============================================================================

LRScheduler* lr_scheduler_create(LRSchedulerType type, float initial_lr,
                                float final_lr, int decay_steps) {
    // Placeholder implementation
    (void)type; (void)initial_lr; (void)final_lr; (void)decay_steps;
    return NULL;
}

void lr_scheduler_destroy(LRScheduler* scheduler) {
    // Placeholder
    (void)scheduler;
}

float lr_scheduler_get_lr(LRScheduler* scheduler) {
    // Placeholder
    (void)scheduler;
    return 0.001f;
}

void lr_scheduler_step(LRScheduler* scheduler) {
    // Placeholder
    (void)scheduler;
}

void optimizer_attach_scheduler(Optimizer* optimizer, LRScheduler* scheduler) {
    // Placeholder
    (void)optimizer; (void)scheduler;
}

// ============================================================================
// Custom Optimizers (Stub)
// ============================================================================

Optimizer* optimizer_create_custom(void (*update_func)(Tensor*, Tensor*, float, void*),
                                  const char* name, float learning_rate) {
    // Placeholder implementation
    (void)update_func; (void)name; (void)learning_rate;
    return NULL;
}

void optimizer_set_user_data(Optimizer* optimizer, void* user_data) {
    if (optimizer) {
        optimizer->user_data = user_data;
    }
}

void* optimizer_get_user_data(Optimizer* optimizer) {
    return optimizer ? optimizer->user_data : NULL;
}