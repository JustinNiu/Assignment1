//
//  Fir.cpp
//  MUSI8903
//
//  Created by Siyuan Niu on 1/27/16.
//
//

#include <stdio.h>
#include <iostream>
#include <cmath>

#include "Fir.h"

FirComb::FirComb() {}

FirComb::~FirComb() {}

Error_t FirComb::process(float **inputBuffer, float **outputBuffer, int numSamples) {
    //Implement filter
    for (int channelId = 0; channelId < filterNumChannels; channelId++) {
        for (int dataId = 0; dataId < numSamples; dataId++) {
            outputBuffer[channelId][dataId] = inputBuffer[channelId][dataId] + gain*delayBuffer[channelId][delayLineInSamples-1];
            
            for (int i = delayLineInSamples-1; i > 0 ; i--) {
                delayBuffer[channelId][i] = delayBuffer[channelId][i-1];
            }
            
            delayBuffer[channelId][0] = inputBuffer[channelId][dataId];
            
        }
    }
    
    return kNoError;
}


void FirComb::setDelayLineInSamples(long int paramVal)
{
    delayLineInSamples = paramVal;
}

void FirComb::setGain(float paramVal)
{
    gain = paramVal;
}

