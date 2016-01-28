//
//  Fir.h
//  MUSI8903
//
//  Created by Siyuan Niu on 1/27/16.
//
//

#ifndef Fir_h
#define Fir_h

#include "Assign1.h"

class FirComb : public Assign1
{
public:
    FirComb();
    ~FirComb();
    
    Error_t process (float **inputBuffer, float **outputBuffer, int numSamples) ;
    
    void setDelayLineInSamples(long int paramVal) ;
    void setGain(float paramVal) ;
    
private:
    
};

#endif /* Fir_h */
