/*
 * Neural Network System - Tensor Implementation
 * Multi-dimensional tensor operations for neural networks
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../headers/neural_net.h"

// ============================================================================
// Tensor Creation and Destruction
// ============================================================================

Tensor* tensor_create(float* data, int* shape, int ndim) {
    if (!shape || ndim <= 0) return NULL;

    Tensor* tensor = (Tensor*)malloc(sizeof(Tensor));
    if (!tensor) return NULL;

    // Calculate total size
    tensor->size = 1;
    for (int i = 0; i < ndim; i++) {
        tensor->size *= shape[i];
    }

    // Allocate data
    if (data) {
        tensor->data = (float*)malloc(tensor->size * sizeof(float));
        if (!tensor->data) {
            free(tensor);
            return NULL;
        }
        memcpy(tensor->data, data, tensor->size * sizeof(float));
    } else {
        tensor->data = (float*)calloc(tensor->size, sizeof(float));
        if (!tensor->data) {
            free(tensor);
            return NULL;
        }
    }

    // Copy shape
    tensor->shape = (int*)malloc(ndim * sizeof(int));
    if (!tensor->shape) {
        free(tensor->data);
        free(tensor);
        return NULL;
    }
    memcpy(tensor->shape, shape, ndim * sizeof(int));

    tensor->ndim = ndim;
    tensor->requires_grad = false;
    tensor->grad = NULL;

    return tensor;
}

void tensor_destroy(Tensor* tensor) {
    if (!tensor) return;

    free(tensor->data);
    free(tensor->shape);
    if (tensor->grad) {
        free(tensor->grad);
    }
    free(tensor);
}

// ============================================================================
// Tensor Operations
// ============================================================================

Tensor* tensor_add(Tensor* a, Tensor* b) {
    if (!a || !b || a->size != b->size) return NULL;

    Tensor* result = tensor_create(NULL, a->shape, a->ndim);
    if (!result) return NULL;

    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] + b->data[i];
    }

    return result;
}

Tensor* tensor_multiply(Tensor* a, Tensor* b) {
    if (!a || !b || a->size != b->size) return NULL;

    Tensor* result = tensor_create(NULL, a->shape, a->ndim);
    if (!result) return NULL;

    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] * b->data[i];
    }

    return result;
}

Tensor* tensor_scalar_multiply(Tensor* tensor, float scalar) {
    if (!tensor) return NULL;

    Tensor* result = tensor_create(NULL, tensor->shape, tensor->ndim);
    if (!result) return NULL;

    for (int i = 0; i < tensor->size; i++) {
        result->data[i] = tensor->data[i] * scalar;
    }

    return result;
}

float tensor_sum(Tensor* tensor) {
    if (!tensor) return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < tensor->size; i++) {
        sum += tensor->data[i];
    }

    return sum;
}

void tensor_fill(Tensor* tensor, float value) {
    if (!tensor) return;

    for (int i = 0; i < tensor->size; i++) {
        tensor->data[i] = value;
    }
}

void tensor_zero(Tensor* tensor) {
    tensor_fill(tensor, 0.0f);
}

Tensor* tensor_copy(Tensor* tensor) {
    if (!tensor) return NULL;
    return tensor_create(tensor->data, tensor->shape, tensor->ndim);
}

void tensor_print(Tensor* tensor, const char* name) {
    if (!tensor) {
        printf("%s: NULL tensor\n", name ? name : "Tensor");
        return;
    }

    printf("%s: shape=[", name ? name : "Tensor");
    for (int i = 0; i < tensor->ndim; i++) {
        printf("%d", tensor->shape[i]);
        if (i < tensor->ndim - 1) printf(",");
    }
    printf("], size=%d\n", tensor->size);

    // Print first few elements
    int max_print = tensor->size < 10 ? tensor->size : 10;
    printf("  [");
    for (int i = 0; i < max_print; i++) {
        printf("%.3f", tensor->data[i]);
        if (i < max_print - 1) printf(", ");
    }
    if (tensor->size > 10) printf(", ...");
    printf("]\n");
}

// ============================================================================
// Matrix Operations (for dense layers)
// ============================================================================

Tensor* matrix_multiply(Tensor* a, Tensor* b) {
    if (!a || !b || a->ndim != 2 || b->ndim != 2 || a->shape[1] != b->shape[0]) {
        return NULL;
    }

    int m = a->shape[0]; // rows of a
    int n = b->shape[1]; // cols of b
    int p = a->shape[1]; // cols of a / rows of b

    int result_shape[2] = {m, n};
    Tensor* result = tensor_create(NULL, result_shape, 2);
    if (!result) return NULL;

    // Matrix multiplication
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            float sum = 0.0f;
            for (int k = 0; k < p; k++) {
                sum += a->data[i * p + k] * b->data[k * n + j];
            }
            result->data[i * n + j] = sum;
        }
    }

    return result;
}

Tensor* matrix_transpose(Tensor* matrix) {
    if (!matrix || matrix->ndim != 2) return NULL;

    int rows = matrix->shape[0];
    int cols = matrix->shape[1];
    int transpose_shape[2] = {cols, rows};

    Tensor* transpose = tensor_create(NULL, transpose_shape, 2);
    if (!transpose) return NULL;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose->data[j * rows + i] = matrix->data[i * cols + j];
        }
    }

    return transpose;
}

// ============================================================================
// Utility Functions
// ============================================================================

bool tensor_shapes_equal(Tensor* a, Tensor* b) {
    if (!a || !b || a->ndim != b->ndim) return false;

    for (int i = 0; i < a->ndim; i++) {
        if (a->shape[i] != b->shape[i]) return false;
    }

    return true;
}

int tensor_get_index(Tensor* tensor, int* indices) {
    if (!tensor || !indices) return -1;

    int index = 0;
    int stride = 1;

    for (int i = tensor->ndim - 1; i >= 0; i--) {
        if (indices[i] < 0 || indices[i] >= tensor->shape[i]) return -1;
        index += indices[i] * stride;
        stride *= tensor->shape[i];
    }

    return index;
}

bool tensor_set_value(Tensor* tensor, int* indices, float value) {
    int index = tensor_get_index(tensor, indices);
    if (index < 0) return false;

    tensor->data[index] = value;
    return true;
}

float tensor_get_value(Tensor* tensor, int* indices) {
    int index = tensor_get_index(tensor, indices);
    if (index < 0) return 0.0f;

    return tensor->data[index];
}