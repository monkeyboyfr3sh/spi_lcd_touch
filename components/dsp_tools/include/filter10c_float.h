/******************************* SOURCE LICENSE *********************************
Copyright (c) 2021 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to 
the Licensee to use the following Information for both Commercial and Non-Commercial purposes.

This source code is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/
// Begin header file, filter10c_float.h

#ifndef FILTER10C_FLOAT_H_ // Include guards
#define FILTER10C_FLOAT_H_

/*
Generated code is based on the following filter design:
<micro.DSP.FilterDocument sampleFrequency="#4000" arithmetic="float" biquads="Direct1" classname="filter10c_float" inputMax="#1" inputShift="#15" >
  <micro.DSP.IirChebyshevFilter N="#10" bandType="h" w1="#0.3829787234042553" w2="#0.4999" stopbandRipple="#undefined" passbandRipple="#0.01418439717283688" transitionRatio="#undefined" >
    <micro.DSP.FilterStructure coefficientBits="#0" variableBits="#0" accumulatorBits="#0" biquads="Direct1" >
      <micro.DSP.FilterSection form="Direct1" historyType="Double" accumulatorBits="#0" variableBits="#0" coefficientBits="#0" />
      <micro.DSP.FilterSection form="Direct1" historyType="Double" accumulatorBits="#0" variableBits="#0" coefficientBits="#0" />
      <micro.DSP.FilterSection form="Direct1" historyType="Double" accumulatorBits="#0" variableBits="#0" coefficientBits="#0" />
      <micro.DSP.FilterSection form="Direct1" historyType="Double" accumulatorBits="#0" variableBits="#0" coefficientBits="#0" />
      <micro.DSP.FilterSection form="Direct1" historyType="Double" accumulatorBits="#0" variableBits="#0" coefficientBits="#0" />
    </micro.DSP.FilterStructure>
    <micro.DSP.PoleOrZeroContainer >
      <micro.DSP.PoleOrZero i="#0.662270397505212" r="#-0.7145579594089514" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#4" />
      <micro.DSP.PoleOrZero i="#0.5825510672868555" r="#-0.7189352814881159" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#3" />
      <micro.DSP.PoleOrZero i="#0.4603924369076369" r="#-0.7516972646661743" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#2" />
      <micro.DSP.PoleOrZero i="#0.2976004431822091" r="#-0.7928046323507173" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#1" />
      <micro.DSP.PoleOrZero i="#0.10325839407735456" r="#-0.8207120410564944" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#0" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#2" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#2" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#3" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#3" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#1" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#1" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#0" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#0" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#4" />
      <micro.DSP.PoleOrZero i="#0" r="#1" isPoint="#true" isPole="#false" isZero="#true" symmetry="r" N="#1" cascade="#4" />
    </micro.DSP.PoleOrZeroContainer>
    <micro.DSP.GenericC.CodeGenerator generateTestCases="#false" />
    <micro.DSP.GainControl magnitude="#1" frequency="#0.48046875" peak="#true" />
  </micro.DSP.IirChebyshevFilter>
</micro.DSP.FilterDocument>

*/

static const int filter10c_float_numStages = 5;
static const int filter10c_float_coefficientLength = 25;
extern float filter10c_float_coefficients[25];

typedef struct
{
	float state[20];
	float output;
} filter10c_floatType;

typedef struct
{
    float *pInput;
    float *pOutput;
    float *pState;
    float *pCoefficients;
    short count;
} filter10c_float_executionState;


filter10c_floatType *filter10c_float_create( void );
void filter10c_float_destroy( filter10c_floatType *pObject );
void filter10c_float_init( filter10c_floatType * pThis );
void filter10c_float_reset( filter10c_floatType * pThis );
#define filter10c_float_writeInput( pThis, input )  \
    filter10c_float_filterBlock( pThis, &(input), &(pThis)->output, 1 );

#define filter10c_float_readOutput( pThis )  \
    (pThis)->output

int filter10c_float_filterBlock( filter10c_floatType * pThis, float * pInput, float * pOutput, unsigned int count );
#define filter10c_float_outputToFloat( output )  \
    (output)

#define filter10c_float_inputFromFloat( input )  \
    (input)

void filter10c_float_filterBiquad( filter10c_float_executionState * pExecState );
#endif // FILTER10C_FLOAT_H_
	
