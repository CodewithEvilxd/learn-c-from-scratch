/*
 * Neural Network System - Loss Functions Implementation
 * Implementation of various loss functions and their gradients
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../headers/losses.h"

// ============================================================================
// Loss Function Creation and Management
// ============================================================================

Loss* loss_create(LossType type) {
    Loss* loss = (Loss*)malloc(sizeof(Loss));
    if (!loss) return NULL;

    loss->type = type;
    loss->user_data = NULL;

    // Set function pointers based on type
    switch (type) {
        case LOSS_MSE:
            strcpy(loss->name, "Mean Squared Error");
            loss->compute = loss_mse_compute;
            loss->gradient = loss_mse_gradient;
            break;

        case LOSS_BINARY_CROSS_ENTROPY:
            strcpy(loss->name, "Binary Cross-Entropy");
            loss->compute = loss_binary_crossentropy_compute;
            loss->gradient = loss_binary_crossentropy_gradient;
            break;

        case LOSS_CATEGORICAL_CROSS_ENTROPY:
            strcpy(loss->name, "Categorical Cross-Entropy");
            loss->compute = loss_categorical_crossentropy_compute;
            loss->gradient = loss_categorical_crossentropy_gradient;
            break;

        case LOSS_HUBER:
            strcpy(loss->name, "Huber Loss");
            // Note: Huber loss would need additional parameters
            loss->compute = NULL; // Placeholder
            loss->gradient = NULL; // Placeholder
            break;

        default:
            free(loss);
            return NULL;
    }

    return loss;
}

void loss_destroy(Loss* loss) {
    if (!loss) return;
    free(loss);
}

float loss_compute(Loss* loss, Tensor* predictions, Tensor* targets) {
    if (!loss || !loss->compute || !predictions || !targets) {
        return 0.0f;
    }

    return loss->compute(predictions, targets);
}

Tensor* loss_gradient(Loss* loss, Tensor* predictions, Tensor* targets) {
    if (!loss || !loss->gradient || !predictions || !targets) {
        return NULL;
    }

    return loss->gradient(predictions, targets);
}

// ============================================================================
// Mean Squared Error Implementation
// ============================================================================

float loss_mse_compute(Tensor* predictions, Tensor* targets) {
    if (!predictions || !targets || predictions->size != targets->size) {
        return 0.0f;
    }

    float sum = 0.0f;
    for (int i = 0; i < predictions->size; i++) {
        float diff = predictions->data[i] - targets->data[i];
        sum += diff * diff;
    }

    return sum / predictions->size;
}

Tensor* loss_mse_gradient(Tensor* predictions, Tensor* targets) {
    if (!predictions || !targets || predictions->size != targets->size) {
        return NULL;
    }

    Tensor* gradient = tensor_create(NULL, predictions->shape, predictions->ndim);
    if (!gradient) return NULL;

    float scale = 2.0f / predictions->size;
    for (int i = 0; i < predictions->size; i++) {
        gradient->data[i] = scale * (predictions->data[i] - targets->data[i]);
    }

    return gradient;
}

// ============================================================================
// Binary Cross-Entropy Implementation
// ============================================================================

float loss_binary_crossentropy_compute(Tensor* predictions, Tensor* targets) {
    if (!predictions || !targets || predictions->size != targets->size) {
        return 0.0f;
    }

    float sum = 0.0f;
    const float epsilon = 1e-7f; // Prevent log(0)

    for (int i = 0; i < predictions->size; i++) {
        float pred = predictions->data[i];
        float target = targets->data[i];

        // Clamp predictions to prevent log(0)
        pred = fmaxf(epsilon, fminf(1.0f - epsilon, pred));

        sum += -target * logf(pred) - (1.0f - target) * logf(1.0f - pred);
    }

    return sum / predictions->size;
}

Tensor* loss_binary_crossentropy_gradient(Tensor* predictions, Tensor* targets) {
    if (!predictions || !targets || predictions->size != targets->size) {
        return NULL;
    }

    Tensor* gradient = tensor_create(NULL, predictions->shape, predictions->ndim);
    if (!gradient) return NULL;

    const float epsilon = 1e-7f;

    for (int i = 0; i < predictions->size; i++) {
        float pred = predictions->data[i];
        float target = targets->data[i];

        // Clamp predictions
        pred = fmaxf(epsilon, fminf(1.0f - epsilon, pred));

        gradient->data[i] = (pred - target) / (pred * (1.0f - pred) + epsilon);
    }

    // Scale by batch size
    for (int i = 0; i < gradient->size; i++) {
        gradient->data[i] /= predictions->size;
    }

    return gradient;
}

// ============================================================================
// Categorical Cross-Entropy Implementation
// ============================================================================

float loss_categorical_crossentropy_compute(Tensor* predictions, Tensor* targets) {
    if (!predictions || !targets || predictions->size != targets->size) {
        return 0.0f;
    }

    float sum = 0.0f;
    const float epsilon = 1e-7f;

    for (int i = 0; i < predictions->size; i++) {
        float pred = predictions->data[i];
        float target = targets->data[i];

        // Clamp predictions
        pred = fmaxf(epsilon, pred);

        sum += -target * logf(pred);
    }

    return sum / predictions->size;
}

Tensor* loss_categorical_crossentropy_gradient(Tensor* predictions, Tensor* targets) {
    if (!predictions || !targets || predictions->size != targets->size) {
        return NULL;
    }

    Tensor* gradient = tensor_create(NULL, predictions->shape, predictions->ndim);
    if (!gradient) return NULL;

    for (int i = 0; i < predictions->size; i++) {
        gradient->data[i] = (predictions->data[i] - targets->data[i]) / predictions->size;
    }

    return gradient;
}

// ============================================================================
// Utility Functions
// ============================================================================

const char* loss_get_name(LossType type) {
    switch (type) {
        case LOSS_MSE: return "Mean Squared Error";
        case LOSS_BINARY_CROSS_ENTROPY: return "Binary Cross-Entropy";
        case LOSS_CATEGORICAL_CROSS_ENTROPY: return "Categorical Cross-Entropy";
        case LOSS_HUBER: return "Huber Loss";
        default: return "Unknown";
    }
}

bool loss_is_classification(LossType type) {
    return type == LOSS_BINARY_CROSS_ENTROPY || type == LOSS_CATEGORICAL_CROSS_ENTROPY;
}

bool loss_is_regression(LossType type) {
    return type == LOSS_MSE || type == LOSS_HUBER;
}

LossType loss_recommend(int num_classes) {
    if (num_classes == 0) {
        return LOSS_MSE; // Regression
    } else if (num_classes == 2) {
        return LOSS_BINARY_CROSS_ENTROPY;
    } else {
        return LOSS_CATEGORICAL_CROSS_ENTROPY;
    }
}

bool loss_validate(Loss* loss, Tensor* predictions, Tensor* targets) {
    if (!loss || !predictions || !targets) return false;

    // Check tensor sizes match
    if (predictions->size != targets->size) return false;

    // Additional validation based on loss type
    if (loss_is_classification(loss->type)) {
        // For classification, predictions should be probabilities (0-1)
        for (int i = 0; i < predictions->size; i++) {
            if (predictions->data[i] < 0.0f || predictions->data[i] > 1.0f) {
                return false;
            }
        }
    }

    return true;
}

// ============================================================================
// Custom Loss Functions (Stub)
// ============================================================================

Loss* loss_create_custom(float (*compute_func)(Tensor*, Tensor*),
                        Tensor* (*gradient_func)(Tensor*, Tensor*),
                        const char* name) {
    // Placeholder implementation
    (void)compute_func;
    (void)gradient_func;
    (void)name;
    return NULL;
}

void loss_set_user_data(Loss* loss, void* user_data) {
    if (loss) {
        loss->user_data = user_data;
    }
}

void* loss_get_user_data(Loss* loss) {
    return loss ? loss->user_data : NULL;
}