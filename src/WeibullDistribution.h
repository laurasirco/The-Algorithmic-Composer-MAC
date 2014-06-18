//
//  WeibullDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 18/06/14.
//
//

#ifndef __The_Algorithmic_Composer__WeibullDistribution__
#define __The_Algorithmic_Composer__WeibullDistribution__

#include <iostream>
using namespace std;
#include "Distribution.h"

class WeibullDistribution : public Distribution {
	
public:
	WeibullDistribution();
	~WeibullDistribution();
	float getValue();
	
	float getT(){ return t; }
	float getS(){ return s; }
	
	void setT(float x){ t = x; }
	void setS(float x){ s = x; }
private:
	float t;
	float s;
};

#endif /* defined(__The_Algorithmic_Composer__WeibullDistribution__) */
