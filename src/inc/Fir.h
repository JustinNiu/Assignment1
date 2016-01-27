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

class FIRCombFilter : public CMyProject
{
public:
    FIRCombFilter();    
    ~FIRCombFilter();
    
    Error_t process (float **inputBuffer, float **outputBuffer, int numSamples) override;
    
    void setDelayLineInSamples(long int paramVal) override;
    void setGain(float paramVal) override;
    
private:
    
};

#endif /* Fir_h */
