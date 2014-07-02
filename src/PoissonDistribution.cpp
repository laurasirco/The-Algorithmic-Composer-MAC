//
//  PoissonDistribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 18/06/14.
//
//

#include "PoissonDistribution.h"
#include <math.h>

PoissonDistribution::PoissonDistribution(){
	lambda = 100;
	mean = lambda;
}

PoissonDistribution::~PoissonDistribution(){
	
}

float PoissonDistribution::getValue(){
	
	float u, v;
	float n = 0;
	v = expf(-lambda);
	u = rand() % 100;
	u /= 100;
	
	while (u >= v) {
		float r = rand() % 100;
		r /= 100;
		
		u *= r;
		n += 0.01;
	}
	
	//cout<<"value: "<<n<<endl;
	
	if(n > 1.0)
		return 1.0;
	
	return n;
}