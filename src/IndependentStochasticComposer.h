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
#include <vector>
#include "Composer.h"
#include "Distribution.h"
#include "Figure.h"

class IndependentStochasticComposer: public Composer{
public:
    IndependentStochasticComposer(Distribution * d);
    void setMean(float m){ distribution->setMean(m); }
    void setSpread(float s){ distribution->setSpread(s); }
	std::vector<Figure *> compose(bool infinite, int meter, int pattern);
	void setDistribution(Distribution * d){ distribution = d; }
	void setScale(int s){ scale = s; }
	void setOctaves(int min, int max){ minOct = min; maxOct = max; }
private:
    Distribution * distribution;
	int mapValue(float value, int min, int max);
	int scale;
	int minOct;
	int maxOct;
};


#endif /* defined(__The_Algorithmic_Composer__IndependentStochasticComposer__) */
