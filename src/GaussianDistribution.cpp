//
//  GaussianDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "GaussianDistribution.h"

GaussianDistribution::GaussianDistribution(){
	mu = 0;
	mean = mu;
	sigma = 1;
	spread = sigma;
}

GaussianDistribution::~GaussianDistribution(){
	
}

float GaussianDistribution::getValue(){
	
	int N = 12;
	float halfN = 6;
	float scale = 1;
	float sum = 0;
	
	for(int k = 1; k < N; k++){
		float value = rand() % 100;
		value /= 100;
		
		sum += value;
	}
	
	float value = sigma * scale * (sum - halfN) + mu;
	
	return value;
	
}