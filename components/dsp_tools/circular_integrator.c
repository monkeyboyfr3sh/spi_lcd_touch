#include "circular_integrator.h"
#include <stdio.h>

void initializeCircularBuffer(CircularBuffer* buffer, int size)
{
    // Allocate memory for the circular buffer data
    buffer->data = (int*)malloc(sizeof(int) * size);
    
    // Initialize buffer properties
    buffer->size = size;
    buffer->head = 0;
    buffer->tail = 0;
    buffer->count = 0;
    buffer->sum = 0;
}

void addSample(CircularBuffer* buffer, int sample)
{
    // Check if the buffer is full and implement circular behavior
    if (buffer->count == buffer->size) {
        // Subtract the oldest sample from the sum
        buffer->sum -= buffer->data[buffer->tail];
        
        // Move the tail index to the next oldest sample (circular)
        buffer->tail = (buffer->tail + 1) % buffer->size;
        
        // Decrease the sample count
        buffer->count--;
    }

    // Store the new sample at the head of the buffer
    buffer->data[buffer->head] = sample;
    
    // Move the head index to the next position (circular)
    buffer->head = (buffer->head + 1) % buffer->size;
    
    // Increase the sample count
    buffer->count++;
    
    // Add the new sample to the sum
    buffer->sum += sample;
}

int getAccumulatedSum(const CircularBuffer* buffer)
{
    return buffer->sum;
}

// Function to accumulate data into a circular buffer and print the accumulated sum
void accumulateDataInCircularBuffer(CircularBuffer *buffer, int data[], int acc[], int dataSize)
{
    for (int i = 0; i < dataSize; i++) {
        // Add a sample
        addSample(buffer, data[i]);
        // Generate an accumulate
        acc[i] = getAccumulatedSum(buffer);
    }
}
