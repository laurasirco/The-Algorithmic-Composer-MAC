//
//  IndependentStochasticComposer.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__IndependentStochasticComposer__
#define __The_Algorithmic_Composer__IndependentStochasticComposer__

#include <iostream>
#include "Composer.h"
#include "Distribution.h"

class IndependentStochasticComposer: public Composer{
public:
    IndependentStochasticComposer(Distribution * d);
    void setMean(float m){ distribution->setMean(m); }
    void setSpread(float s){ distribution->setSpread(s); }
	float compose(){ return distribution->getValue(); }
private:
    Distribution * distribution;
};

#endif /* defined(__The_Algorithmic_Composer__IndependentStochasticComposer__) */
