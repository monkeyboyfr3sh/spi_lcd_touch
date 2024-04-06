#ifndef DART_DSP_H
#define DART_DSP_H

typedef struct
{
    float state[20];
    float output;
} iir_filter_t;

void dart_dsp_init(iir_filter_t *filter);
void dart_dsp_batch_filter(iir_filter_t *filter, float *input, float *output, int length);
void dart_dsp_single_filter(iir_filter_t *filter, float val);

#endif