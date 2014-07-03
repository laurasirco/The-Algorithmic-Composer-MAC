//
//  LinearDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "LinearDistribution.h"

LinearDistribution::LinearDistribution(){
	direction = Down;
}

LinearDistribution::~LinearDistribution(){
	
}

float LinearDistribution::getValue(){
	
	float v1 = rand() % 100;
	float v2 = rand() % 100;
	v1 /= 100;
	v2 /= 100;
	
	if(direction == Down){
		if(v2 < v1)
			v1 = v2;
	}
	else{
		if (v2 > v1) {
			v1 = v2;
		}
	}
	
	return v1;
}