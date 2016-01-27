//
//  Assign1.h
//  MUSI8903
//
//  Created by Siyuan Niu on 1/26/16.
//
//

#ifndef Assign1_h
#define Assign1_h

#include "ErrorDef.h"
#include "AudioFileIf.h"

class Assign1{
    
public:
    Assign1 ();
    virtual ~Assign1 ();
    
    static Error_t create(Assign1*& pCKortIf, int type, float delayTimeInSecs, float gain, long int sampleRate, int numChannels);
    static Error_t destroy (Assign1*& pCKortIf);
    
    Error_t init (float delayTimeInSecs, float gain, long int sampleRate, int numChannels);
    Error_t reset ();
    
    float getDelayLineInSamples();
    float getGain();
    
    long int delayLineInSamples;
    float gain;
    float** delayBuffer;
    long int filterSampleRate;
    int filterNumChannels;
    
    long int getDelayLineInSamples(long int fs, float delayLineInSecs);
    virtual void setDelayLineInSamples(long int paramVal);
    virtual void setGain(float paramVal);
};

#endif /* Assign1_h */
