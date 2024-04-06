#pragma once

#include <stdio.h>

/**
 * @brief A circular buffer structure for accumulating and maintaining N samples.
 */
typedef struct {
    int* data;       /**< Array to store the samples */
    int size;        /**< Size of the circular buffer */
    int head;        /**< Index of the newest sample */
    int tail;        /**< Index of the oldest sample */
    int count;       /**< Number of samples currently in the buffer */
    int sum;         /**< Accumulated sum of samples */
} CircularBuffer;

/**
 * @brief Initializes the circular buffer.
 *
 * @param buffer Pointer to the CircularBuffer structure to be initialized.
 * @param size   The size of the circular buffer.
 */
void initializeCircularBuffer(CircularBuffer* buffer, int size);

/**
 * @brief Adds a sample to the circular buffer.
 *
 * If the buffer is full, the oldest sample is removed to maintain a rolling accumulation.
 *
 * @param buffer Pointer to the CircularBuffer structure.
 * @param sample The sample to be added.
 */
void addSample(CircularBuffer* buffer, int sample);

/**
 * @brief Gets the accumulated sum of samples in the circular buffer.
 *
 * @param buffer Pointer to the CircularBuffer structure.
 * @return The accumulated sum of samples.
 */
int getAccumulatedSum(const CircularBuffer* buffer);

/**
 * @brief Accumulates data in the circular buffer and generates an accumulation array.
 *
 * This function accumulates data in the circular buffer and generates an accumulation
 * array `acc` of the same size as the input `data`. Each element in `acc` represents
 * the accumulated sum of data up to that point in the circular buffer.
 *
 * @param buffer Pointer to the CircularBuffer structure.
 * @param data   Array of input data to be accumulated.
 * @param acc    Output accumulation array.
 * @param dataSize The number of elements in the input data and output accumulation array.
 */
void accumulateDataInCircularBuffer(CircularBuffer *buffer, int data[], int acc[], int dataSize);
