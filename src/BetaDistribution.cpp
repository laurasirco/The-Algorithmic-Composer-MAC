//
//  BetaDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 18/06/14.
//
//

#include "BetaDistribution.h"
#include <math.h>

BetaDistribution::BetaDistribution(){
	a = 0.5;
	b = 0.5;
	mean = a/(a+b);
}

BetaDistribution::~BetaDistribution(){
	
	
}

float BetaDistribution::getValue(){
	
	float u1, u2, y1, y2, sum, ainv, binv;
	ainv = 1/a;
	binv = 1/b;
	
	do{
		do{
			u1 = rand() % 100;
			u1 /= 100;
		}while(u1 == 0.0);
		
		do{
			u2 = rand() % 100;
			u2 /= 100;
		}while(u2 == 0.0);
		
		y1 = powf(u1, ainv);
		y2 = powf(u2, binv);
		sum = y1 + y2;
		
	}while(sum > 1);
	
	//cout<<"value: "<<y1/sum<<endl;
	return y1/sum;
	
}