#pragma once

#include <stdlib.h>
#include <stdint.h>

/**
 * @file dart_convert.h
 * @brief Functions for converting arrays between int32_t and float types.
 */

/**
 * @brief Convert an array of int32_t to an array of float.
 *
 * This function takes an array of int32_t values and converts them to an
 * array of float values of the same size.
 *
 * @param iarr Pointer to the input int32_t array.
 * @param farr Pointer to the output float array.
 * @param size The number of elements in the arrays.
 */
void dart_convert_array_float(int32_t *iarr, float *farr, size_t size);

/**
 * @brief Convert an array of float to an array of int32_t.
 *
 * This function takes an array of float values and converts them to an
 * array of int32_t values of the same size.
 *
 * @param farr Pointer to the input float array.
 * @param iarr Pointer to the output int32_t array.
 * @param size The number of elements in the arrays.
 */
void dart_convert_array_int32(float *farr, int32_t *iarr, size_t size);
