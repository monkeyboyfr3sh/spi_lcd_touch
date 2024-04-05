#pragma once

/**
 * @brief Compute the absolute values of elements in an array.
 *
 * This function computes the absolute values of each element in the input array
 * `data` and stores the result in the output array `absoluteValues`.
 *
 * @param data The input array containing the data for which absolute values are computed.
 * @param absoluteValues The output array where the absolute values will be stored.
 * @param dataSize The number of elements in the input array and output array.
 */
void batch_absolute(int data[], int absoluteValues[], int dataSize);
