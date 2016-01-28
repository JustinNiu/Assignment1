//
//  CMyProject.cpp
//  MUSI8903
//
//  Created by Siyuan Niu on 1/26/16.
//
//
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "ErrorDef.h"
#include "MyProject.h"
#include "Fir.h"
#include "Iir.h"

CMyProject::CMyProject () {}
CMyProject::~CMyProject () {
    this->reset();
}

Error_t CMyProject::create(CMyProject*& pCMyProject, int type, float delayTimeInSecs, float gain, long int sampleRate, int numChannels)
{
    if (type == 0)
        pCMyProject = new FirComb();
    else
        pCMyProject = new IirComb();
    
    if (!pCMyProject)
        return kUnknownError;
    
    pCMyProject->init(delayTimeInSecs, gain, sampleRate, numChannels);
    
    return kNoError;
}

Error_t CMyProject::destroy (CMyProject*& pCMyProject)
{
    if (!pCMyProject)
        return kUnknownError;
    
    delete pCMyProject;
    pCMyProject = 0;
    
    return kNoError;
}

Error_t CMyProject::init(float delayTimeInSecs, float gainValue, long int sampleRate, int numChannels)
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


Error_t CMyProject::reset () {
    
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


