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


//constructor
FirComb::FirComb() {}

FirComb::~FirComb() {}

Error_t FirComb::filtering(float **inputBuffer, float **outputBuffer, int numSamples) {
    
    //for each channel
    for (int channel = 0; channel < filterNumChannels; channel++) {
        
        //for each frame
        for (int dataFrame = 0; dataFrame < numSamples; dataFrame++) {
            
            //feedforward
            outputBuffer[channel][dataFrame] = inputBuffer[channel][dataFrame] + gain*delayBuffer[channel][delayLineInSamples-1];
            
            //iterate the delayline
            for (int i = delayLineInSamples-1; i > 0 ; i--) {
                delayBuffer[channel][i] = delayBuffer[channel][i-1];
            }
            
            delayBuffer[channel][0] = inputBuffer[channel][dataFrame];
            
        }
    }
    
    return kNoError;
}

//set the length of the delayline
void FirComb::setDelayLineInSamples(long int leng)
{
    delayLineInSamples = leng;
}

//set the gain
void FirComb::setGain(float g)
{
    gain = g;
}

