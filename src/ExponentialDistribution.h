//
//  ExponentialDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__ExponentialDistribution__
#define __The_Algorithmic_Composer__ExponentialDistribution__

#include <iostream>
#include "Distribution.h"
using namespace std;

class ExponentialDistribution: public Distribution {
  
public:
	ExponentialDistribution();
	~ExponentialDistribution();
	float getValue();
	
	float getLambda(){ return lambda; }
	void setLambda(float l){ lambda = l; }
	
private:
	float lambda;
};

#endif /* defined(__The_Algorithmic_Composer__ExponentialDistribution__) */
