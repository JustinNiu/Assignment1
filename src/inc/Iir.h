//
//  Iir.h
//  MUSI8903
//
//  Created by Siyuan Niu on 1/27/16.
//
//

#ifndef Iir_h
#define Iir_h

#include "MyProject.h"

class IirComb : public CMyProject
{
public:
    IirComb();
    
    ~IirComb();
    
    Error_t filtering (float **inputBuffer, float **outputBuffer, int numSamples) override;
    
    void setDelayLineInSamples(long int leng) override;
    void setGain(float g) override;
    
private:
    
};


#endif /* Iir_h */
