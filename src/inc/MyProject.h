//
//  CMyProject.h
//  MUSI8903
//
//  Created by Siyuan Niu on 1/26/16.
//
//

#ifndef CMyProject_h
#define CMyProject_h

#include "ErrorDef.h"
#include "AudioFileIf.h"

class CMyProject{
    
public:
    
    enum Version_t
    {
        kMajor,                         //!< major version number
        kMinor,                         //!< minor version number
        kPatch,                         //!< patch version number
        
        kNumVersionInts
    };
    
    static const int  getVersion (const Version_t eVersionIdx);
    static const char* getBuildDate ();
    
    static Error_t create(CMyProject*& pCKortIf, int type, float delayTimeInSecs, float gain, long int sampleRate, int numChannels);
    static Error_t destroy (CMyProject*& pCKortIf);
    
    Error_t init (float delayTimeInSecs, float gain, long int sampleRate, int numChannels);
    Error_t reset ();

    // get the delayline in sample and gain
    float getDelayLineInSamples();
    float getGain();
    
    virtual Error_t process (float **inputBuffer, float **outputBuffer, int numSamples) = 0;
    
    long int delayLineInSamples;
    
    float gain;
    
    float** delayBuffer;
    
    long int filterSampleRate;
    
    int filterNumChannels;
    
    // get the delayline in sample(overload)
    long int getDelayLineInSamples(long int fs, float delayLineInSecs);
    
    // set the delayline in sample
    virtual void setDelayLineInSamples(long int paramVal);
    
    // set the gain
    virtual void setGain(float paramVal);
    
protected:
    
    CMyProject ();
    virtual ~CMyProject ();
};

#endif /* CMyProject_h */
