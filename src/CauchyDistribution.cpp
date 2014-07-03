//
//  CauchyDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "CauchyDistribution.h"
#include <math.h>

CauchyDistribution::CauchyDistribution(){
	alpha = 1;
}

CauchyDistribution::~CauchyDistribution(){
	
	
}

float CauchyDistribution::getValue(){

	float value = rand() % 100;
	value /= 100;
	
	while(value == 0.5){
		value = rand() % 100;
		value /= 100;
	}
	
	
	//cout<<"Value: "<<alpha * tan(value * M_PI)<<endl;
	
	return alpha * tan(value);
}

