//
//  Iir.h
//  MUSI8903
//
//  Created by Siyuan Niu on 1/27/16.
//
//

#ifndef Iir_h
#define Iir_h

#include "Assign1.h"

class IirComb : public Assign1
{
public:
    IirComb();
    
    ~IirComb();
    
    //void processFilter(float **inputAudioData, float **outputAudioData, CAudioFileIf::FileSpec_t spec, long long iInFileLength) override;
    Error_t process (float **inputBuffer, float **outputBuffer, int numSamples) ;
    
    void setDelayLineInSamples(long int paramVal) override;
    void setGain(float paramVal) override;
    
private:
    
};


#endif /* Iir_h */
