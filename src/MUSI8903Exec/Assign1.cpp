//
//  Assign1.cpp
//  MUSI8903
//
//  Created by Siyuan Niu on 1/26/16.
//
//
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "ErrorDef.h"
#include "Assign1.h"

Assign1::Assign1 () {}
Assign1::~Assign1 () {
    this->reset();
}

Error_t Assign1::create(Assign1*& pAssign1, int type, float delayTimeInSecs, float gain, long int sampleRate, int numChannels)
{
    if (type == 0)
        pAssign1 = new FIRCombFilter();
    else
        pAssign1 = new IIRCombFilter();
    
    if (!pAssign1)
        return kUnknownError;
    
    pAssign1->init(delayTimeInSecs, gain, sampleRate, numChannels);
    
    return kNoError;
}

Error_t Assign1::destroy (Assign1*& pAssign1)
{
    if (!pAssign1)
        return kUnknownError;
    
    delete pAssign1;
    pAssign1 = 0;
    
    return kNoError;
}

Error_t Assign1::init(float delayTimeInSecs, float gainValue, long int sampleRate, int numChannels)
{
    gain = gainValue;
    filterSampleRate = sampleRate;
    filterNumChannels = numChannels;
    delayLineInSamples = getDelayLineInSamples(sampleRate, delayTimeInSecs);
    
    std::cout << delayLineInSamples << std::endl;
    
    delayBuffer = new float*[filterNumChannels];
    
    for(int i = 0; i < filterNumChannels; i++)
    {
        delayBuffer[i] = new float[delayLineInSamples];
    }
    
    for(int i = 0; i < filterNumChannels; i++) {
        for (int k = 0; k < delayLineInSamples; k++) {
            delayBuffer[i][k] = 0.0F;
        }
    }
    
    return kNoError;
}


Error_t Assign1::reset () {
    
    std::cout << delayBuffer[0][0] << std::endl;
    std::cout << filterNumChannels << std::endl;
    for (int i = 0; i < filterNumChannels; i++)
    {
        delete[] delayBuffer[i];
    }
    delete[] delayBuffer;
    delayLineInSamples = 0;
    gain = 0.0;
    filterNumChannels = 0;
    filterSampleRate = 0;
    return kNoError;
}

float Assign1::getDelayLineInSamples()
{
    return delayLineInSamples;
}

float Assign1::getGain()
{
    return gain;
}

void Assign1::setDelayLineInSamples(long int paramVal)
{
    delayLineInSamples = paramVal;
}

void Assign1::setGain(float paramVal)
{
    gain = paramVal;
}

long int Assign1::getDelayLineInSamples(long int fs, float delayLineInSecs)
{
    return roundf(fs*delayLineInSecs);
}

