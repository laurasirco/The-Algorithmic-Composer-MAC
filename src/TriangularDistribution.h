//
//  TriangularDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__TriangularDistribution__
#define __The_Algorithmic_Composer__TriangularDistribution__

#include <iostream>
#include <cmath>
#include "Distribution.h"
using namespace std;

class TriangularDistribution: public Distribution {

public:
	TriangularDistribution();
	~TriangularDistribution();
	float getValue();
	void setTriangleBase(float b){ triangleBase = b; min = abs(triangleBase/2 - mean); max = triangleBase/2 + mean; }
private:
	float triangleBase;
	float min, max;
};

#endif /* defined(__The_Algorithmic_Composer__TriangularDistribution__) */
