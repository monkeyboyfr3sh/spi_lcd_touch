#include <string.h>
#include "dsp.h"
#include "filter10c_float.h"

void dart_dsp_init(dart_iir_filter_t *filter)
{
    filter10c_float_init((filter10c_floatType *)filter);
}

void dart_dsp_batch_filter(dart_iir_filter_t *filter, float *input, float *output, int length)
{
    filter10c_float_filterBlock((filter10c_floatType*)filter, input, output, length);
}

void dart_dsp_single_filter(dart_iir_filter_t *filter, float val)
{
    filter10c_float_writeInput((filter10c_floatType*)filter, val);
}
