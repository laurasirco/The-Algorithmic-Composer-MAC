//
//  UniformDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "UniformDistribution.h"

UniformDistribution::UniformDistribution(){
	mean = 0.5;
	spread = 0.0;
}

UniformDistribution::~UniformDistribution(){
	
}

float UniformDistribution::getValue(){
	float value = rand() % 100;
	return value/100;
}