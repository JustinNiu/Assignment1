//
//  Iir.cpp
//  MUSI8903
//
//  Created by Siyuan Niu on 1/27/16.
//
//

#include <stdio.h>
#include <iostream>
#include <cmath>

#include "Iir.h"

IirComb::IirComb() {}

IirComb::~IirComb() {}

Error_t IirComb::filtering(float **inputBuffer, float **outputBuffer, int numSamples) {
    //Implement filter
    for (int channelId = 0; channelId < filterNumChannels; channelId++) {
        for (int dataId = 0; dataId < numSamples; dataId++) {
            outputBuffer[channelId][dataId] = inputBuffer[channelId][dataId] + gain*delayBuffer[channelId][delayLineInSamples-1];
            
            for (int i = delayLineInSamples-1; i > 0 ; i--) {
                delayBuffer[channelId][i] = delayBuffer[channelId][i-1];
            }
            
            delayBuffer[channelId][0] = outputBuffer[channelId][dataId];
            
        }
    }
    
    return kNoError;
}

void IirComb::setDelayLineInSamples(long int paramVal)
{
    delayLineInSamples = paramVal;
}

void IirComb::setGain(float paramVal) {
    if (fabs(paramVal) > 1)
    {
        std::cout << "Incorrect parameter value for filter gain. Magnitude should be <= 1" << std::endl;
        exit(0);
    }
    gain = paramVal;
}


