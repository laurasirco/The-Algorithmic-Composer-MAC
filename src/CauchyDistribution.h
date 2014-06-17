//
//  CauchyDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__CauchyDistribution__
#define __The_Algorithmic_Composer__CauchyDistribution__

#include <iostream>
using namespace std;
#include "Distribution.h"

class CauchyDistribution : public Distribution {

public:
	CauchyDistribution();
	~CauchyDistribution();
	float getValue();
	float getAlpha(){ return alpha; }
	void setAlpha(float a){ alpha = a;}

private:
	float alpha;
};

#endif /* defined(__The_Algorithmic_Composer__CauchyDistribution__) */
