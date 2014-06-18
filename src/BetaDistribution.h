//
//  BetaDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 18/06/14.
//
//

#ifndef __The_Algorithmic_Composer__BetaDistribution__
#define __The_Algorithmic_Composer__BetaDistribution__

#include <iostream>
using namespace std;
#include "Distribution.h"

class BetaDistribution : public Distribution {
	
public:
	BetaDistribution();
	~BetaDistribution();
	float getValue();
	
	float getA(){ return a; }
	float getB(){ return b; }
	
	void setA(float x){ a = x; }
	void setB(float x){ b = x; }
private:
	float a;
	float b;
};


#endif /* defined(__The_Algorithmic_Composer__BetaDistribution__) */
