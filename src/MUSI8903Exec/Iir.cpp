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


//constructor
IirComb::IirComb() {}

IirComb::~IirComb() {}

Error_t IirComb::filtering(float **inputBuffer, float **outputBuffer, int numSamples) {
    //for each channel
    for (int channel = 0; channel < filterNumChannels; channel++) {
        
        //for each frame
        for (int dataFrame = 0; dataFrame < numSamples; dataFrame++) {

            //feedbackward
            outputBuffer[channel][dataFrame] = inputBuffer[channel][dataFrame] + gain*delayBuffer[channel][delayLineInSamples-1];
            
            //iterate the delayline
            for (int i = delayLineInSamples-1; i > 0 ; i--) {
                delayBuffer[channel][i] = delayBuffer[channel][i-1];
            }
            
            delayBuffer[channel][0] = outputBuffer[channel][dataFrame];
            
        }
    }
    
    return kNoError;
}

void IirComb::setDelayLineInSamples(long int leng)
{
    delayLineInSamples = leng;
}

void IirComb::setGain(float g) {
    if (fabs(g) > 1)
    {
        std::cout << "Incorrect parameter value for filter gain. Magnitude should be <= 1" << std::endl;
        exit(0);
    }
    gain = g;
}


