//
//  UniformDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__UniformDistribution__
#define __The_Algorithmic_Composer__UniformDistribution__

#include <iostream>
#include "Distribution.h"
using namespace std;

class UniformDistribution : public Distribution {
  
public:
	UniformDistribution();
	~UniformDistribution();
	float getValue();
private:
	
};

#endif /* defined(__The_Algorithmic_Composer__UniformDistribution__) */
