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
#include "Distribution.h"

class TriangularDistribution: public Distribution {

public:
	TriangularDistribution();
	~TriangularDistribution();
	float getValue();
};

#endif /* defined(__The_Algorithmic_Composer__TriangularDistribution__) */
