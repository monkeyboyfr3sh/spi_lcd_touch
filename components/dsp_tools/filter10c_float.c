/******************************* SOURCE LICENSE *********************************
Copyright (c) 2021 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to 
the Licensee to use the following Information for both Commercial and Non-Commercial purposes.

This source code is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/
#include "filter10c_float.h"

#include <stdlib.h> // For malloc/free
#include <string.h> // For memset

float filter10c_float_coefficients[25] = 
{
// Scaled for floating point

    0.04228604406929655, -0.0845720881385931, 0.04228604406929655, -1.6414240821129888, -0.6842305502825513,// b0, b1, b2, a1, a2
    0.0625, -0.125, 0.0625, -1.5856092647014346, -0.7171052088590032,// b0, b1, b2, a1, a2
    0.0625, -0.125, 0.0625, -1.5033945293323485, -0.7770099736683609,// b0, b1, b2, a1, a2
    0.0625, -0.125, 0.0625, -1.4378705629762318, -0.8562336849654508,// b0, b1, b2, a1, a2
    0.03125, -0.0625, 0.03125, -1.4291159188179028, -0.9491951567663961// b0, b1, b2, a1, a2

};

// // The coefficients of the filter before adjustment
// float filter10c_float_coefficients[25] = 
// {
// // Scaled for floating point

//     0.04872575557485175, -0.0974515111497035, 0.04872575557485175, -1.705771287197217, -0.7403021790231266,// b0, b1, b2, a1, a2
//     0.0625, -0.125, 0.0625, -1.6290441896127317, -0.768989155820976,// b0, b1, b2, a1, a2
//     0.0625, -0.125, 0.0625, -1.5146018774763819, -0.8200863614681231,// b0, b1, b2, a1, a2
//     0.0625, -0.125, 0.0625, -1.4165939581783298, -0.8856134506464572,// b0, b1, b2, a1, a2
//     0.03125, -0.0625, 0.03125, -1.3813823995066863, -0.9601161054600078// b0, b1, b2, a1, a2
// };

filter10c_floatType *filter10c_float_create( void )
{
    filter10c_floatType *result = (filter10c_floatType *)malloc( sizeof( filter10c_floatType ) ); // Allocate memory for the object
    filter10c_float_init( result );                                               // Initialize it
    return result;                                                        // Return the result
}

void filter10c_float_destroy( filter10c_floatType *pObject )
{
    free( pObject );
}

void filter10c_float_init( filter10c_floatType * pThis )
{
    filter10c_float_reset( pThis );
}

void filter10c_float_reset( filter10c_floatType * pThis )
{
    memset( &pThis->state, 0, sizeof( pThis->state ) ); // Reset state to 0
    pThis->output = 0;                                    // Reset output
}

int filter10c_float_filterBlock( filter10c_floatType * pThis, float * pInput, float * pOutput, unsigned int count )
{
    filter10c_float_executionState executionState;          // The executionState structure holds call data, minimizing stack reads and writes 
    if( ! count ) return 0;                         // If there are no input samples, return immediately
    executionState.pInput = pInput;                 // Pointers to the input and output buffers that each call to filterBiquad() will use
    executionState.pOutput = pOutput;               // - pInput and pOutput can be equal, allowing reuse of the same memory.
    executionState.count = count;                   // The number of samples to be processed
    executionState.pState = pThis->state;                   // Pointer to the biquad's internal state and coefficients. 
    executionState.pCoefficients = filter10c_float_coefficients;    // Each call to filterBiquad() will advance pState and pCoefficients to the next biquad

    // The 1st call to filter1_filterBiquad() reads from the caller supplied input buffer and writes to the output buffer.
    // The remaining calls to filterBiquad() recycle the same output buffer, so that multiple intermediate buffers are not required.

    filter10c_float_filterBiquad( &executionState );		// Run biquad #0
    executionState.pInput = executionState.pOutput;         // The remaining biquads will now re-use the same output buffer.

    filter10c_float_filterBiquad( &executionState );		// Run biquad #1

    filter10c_float_filterBiquad( &executionState );		// Run biquad #2

    filter10c_float_filterBiquad( &executionState );		// Run biquad #3

    filter10c_float_filterBiquad( &executionState );		// Run biquad #4

    // At this point, the caller-supplied output buffer will contain the filtered samples and the input buffer will contain the unmodified input samples.  
    return count;		// Return the number of samples processed, the same as the number of input samples
}

void filter10c_float_filterBiquad( filter10c_float_executionState * pExecState )
{

    // Read state variables
    float x0;
    float x1 = pExecState->pState[0];
    float x2 = pExecState->pState[1];
    float y1 = pExecState->pState[2];
    float y2 = pExecState->pState[3];

    // Read coefficients into work registers
    float b0 = *(pExecState->pCoefficients++);
    float b1 = *(pExecState->pCoefficients++);
    float b2 = *(pExecState->pCoefficients++);
    float a1 = *(pExecState->pCoefficients++);
    float a2 = *(pExecState->pCoefficients++);

    // Read source and target pointers
    float *pInput  = pExecState->pInput;
    float *pOutput = pExecState->pOutput;
    short count = pExecState->count;
    float accumulator;

    while( count-- )
    {
        x0 = *(pInput++);

        accumulator  = x2 * b2;
        accumulator += x1 * b1;
        accumulator += x0 * b0;

        x2 = x1;        // Shuffle left history buffer
        x1 = x0;

        accumulator += y2 * a2;
        accumulator += y1 * a1;

        y2 = y1;        // Shuffle right history buffer
        y1 = accumulator ;

        *(pOutput++) = accumulator ;
    }

    *(pExecState->pState++) = x1;
    *(pExecState->pState++) = x2;
    *(pExecState->pState++) = y1;
    *(pExecState->pState++) = y2;
   
}


