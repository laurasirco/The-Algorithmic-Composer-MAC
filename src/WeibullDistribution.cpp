//
//  WeibullDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 18/06/14.
//
//

#include "WeibullDistribution.h"
#include <math.h>

WeibullDistribution::WeibullDistribution(){
	t = 1;
	s = 1;
}

WeibullDistribution::~WeibullDistribution(){
	
	
}

float WeibullDistribution::getValue(){
	
	float u, a, tinv;
	tinv = 1/t;
	
	do{
		u = rand() % 100;
		u /= 100;
	}while(u == 0 || u == 1);
	
	a = 1/(1-u);
	
	float value = s*powf(logf(a), tinv);
	//cout<<"value: "<<value<<endl;
	
	if(value > 1.0){
		//cout<<"return 1.0"<<endl;
		return 1;
	}
	else
		return value;
}