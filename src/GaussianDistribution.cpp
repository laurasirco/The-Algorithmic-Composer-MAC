//
//  GaussianDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "GaussianDistribution.h"

GaussianDistribution::GaussianDistribution(){
	mu = 5;
	mean = mu;
	sigma = 0.5;
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
	cout<<"value: "<<value<<endl;
	
	if(value < 0)
		return 0.0;
	if(value > 1.0)
		return 1.0;
	
	return value;
	
}