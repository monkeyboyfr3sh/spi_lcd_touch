#ifndef DART_DSP_H
#define DART_DSP_H

typedef struct
{
    float state[20];
    float output;
} dart_iir_filter_t;

void dart_dsp_init(dart_iir_filter_t *filter);
void dart_dsp_batch_filter(dart_iir_filter_t *filter, float *input, float *output, int length);
void dart_dsp_single_filter(dart_iir_filter_t *filter, float val);

#endif