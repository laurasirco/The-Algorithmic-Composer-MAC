//
//  ExponentialDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "ExponentialDistribution.h"
#include <math.h>

ExponentialDistribution::ExponentialDistribution(){
	lambda = 1.0;
	mean = 0.69315 / lambda;
}

ExponentialDistribution::~ExponentialDistribution(){
	
}

float ExponentialDistribution::getValue(){
	
	float value = rand() % 100;
	value /= 100;
	
	while (value == 0.0) {
		value = rand() % 100;
		value /= 100;
	}
	if(-log10(value)/lambda > 1.0)
		return 1.0;
	
	//std::cout<<"value: "<<value<<", log: "<<-log10(value)/lambda<<std::endl;
	return -log10(value)/lambda;
	
}

