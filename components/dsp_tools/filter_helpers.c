#include <string.h>
#include "filter_helpers.h"
#include "filter10c_float.h"

void filters_init(iir_filter_t *filter)
{
    filter10c_float_init((filter10c_floatType *)filter);
}

void batch_filter(iir_filter_t *filter, float *input, float *output, int length)
{
    filter10c_float_filterBlock((filter10c_floatType*)filter, input, output, length);
}

void single_filter(iir_filter_t *filter, float val)
{
    filter10c_float_writeInput((filter10c_floatType*)filter, val);
}
