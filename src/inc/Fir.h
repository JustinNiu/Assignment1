//
//  Fir.h
//  MUSI8903
//
//  Created by Siyuan Niu on 1/27/16.
//
//

#ifndef Fir_h
#define Fir_h

#include "MyProject.h"

class FirComb : public CMyProject
{
public:
    FirComb();
    ~FirComb();
    
    Error_t filtering (float **inputBuffer, float **outputBuffer, int numSamples) override;
    
    void setDelayLineInSamples(long int paramVal) override;
    void setGain(float paramVal) override;
    
private:
    
};

#endif /* Fir_h */
