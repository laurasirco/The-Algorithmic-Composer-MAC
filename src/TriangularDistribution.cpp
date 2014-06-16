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
	triangleBase = 1.0;
	min = abs(triangleBase/2 - mean);
	max = triangleBase/2 + mean;
}

TriangularDistribution::~TriangularDistribution(){
	
}

float TriangularDistribution::getValue(){
	
	int min100 = min * 100;
	int max100 = max * 100;
	float v1 = rand() % (max100 - min100) + min100;
	float v2 = rand() % (max100 - min100) + min100;
	v1 /= 100;
	v2 /= 100;
	
	float value = (v1 + v2) * mean;
	//cout<<"value: "<<value<<", min: "<<min<<", max:"<<max<<endl;
	
	return value;
}

