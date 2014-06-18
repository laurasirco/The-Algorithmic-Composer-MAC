//
//  PoissonDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 18/06/14.
//
//

#ifndef __The_Algorithmic_Composer__PoissonDistribution__
#define __The_Algorithmic_Composer__PoissonDistribution__

#include <iostream>
using namespace std;
#include "Distribution.h"

class PoissonDistribution : public Distribution {
	
public:
	PoissonDistribution();
	~PoissonDistribution();
	float getValue();
	
	float getlambda(){ return lambda; }
	
	void setv(float x){ lambda = x; }
private:
	float lambda;
};

#endif /* defined(__The_Algorithmic_Composer__PoissonDistribution__) */
