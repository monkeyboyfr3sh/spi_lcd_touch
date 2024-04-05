#include <string.h>
#include "dsp.h"
#include "filter10c_float.h"
#include "mag_hpf.h"

// 10O float:      20052 us/8000 samples, 132988 samples x3/s
// 10O 8x8x16:     23436 us/8000 samples, 113785 samples x3/s
// 10O 16x16x40:   20523 us/8000 samples, 129936 samples x3/s
// 10O 16x16x64:   20521 us/8000 samples, 129948 samples x3/s
// 10O 32x32x64:   34929 us/8000 samples, 76345  samples x3/s
// 10O 32x32x64:   34929 us/8000 samples, 76345  samples x3/s
// 4O float:       9053  us/8000 samples, 294562 samples x3/s
// 4O 32x32x64:    15019 us/8000 samples, 177553 samples x3/s
// 10Oc float:

void dart_dsp_init(dart_iir_filter_t *filter)
{
    filter10c_float_init((filter10c_floatType *)filter);
}

// void dart_dsp_set_coeff(float *arr)
// {
//     // memcpy(filter10c_float_coefficients, arr, sizeof(filter10c_float_coefficients));
// }

void dart_dsp_batch_filter(dart_iir_filter_t *filter, float *input, float *output, int length)
{
    filter10c_float_filterBlock((filter10c_floatType*)filter, input, output, length);
}

void dart_dsp_single_filter(dart_iir_filter_t *filter, float val)
{
    filter10c_float_writeInput((filter10c_floatType*)filter, val);
}


// MAGNETOMETER helper functions
void dart_mag_dsp_init(dart_iir_filter_t *filter) {
    mag_hpf_init((mag_hpfType*)filter);
}

void dart_mag_dsp_reset(dart_iir_filter_t *filter) {
    mag_hpf_reset((mag_hpfType*)filter);
}

void dart_mag_dsp_batch_filter(dart_iir_filter_t *filter, float *input, float *output, int length) {
    mag_hpf_filterBlock((mag_hpfType*)filter, input, output, length);
}

void dart_mag_dsp_single_filter(dart_iir_filter_t *filter, float val) {
    mag_hpf_writeInput((mag_hpfType*)filter, val);
}
