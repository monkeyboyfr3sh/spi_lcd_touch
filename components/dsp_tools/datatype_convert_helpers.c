#include "datatype_convert_helpers.h"

#include <stdlib.h>
#include <stdint.h>

void convert_int32_to_float(int32_t *iarr, float *farr, size_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        farr[i] = (float)iarr[i];
    }
    return;
}

void convert_float_to_int32(float *farr, int32_t *iarr, size_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        iarr[i] = (int32_t)farr[i];
    }
    return;
}