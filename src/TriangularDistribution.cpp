//
//  TriangularDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "TriangularDistribution.h"

TriangularDistribution::TriangularDistribution(){
	mean = 0.5;
}

TriangularDistribution::~TriangularDistribution(){
	
}

float TriangularDistribution::getValue(){
	
	float v1 = rand() % 100;
	float v2 = rand() % 100;
	v1 /= 100;
	v2 /= 100;
	
	float value = (v1 + v2) * mean;
	
	return value;
}

