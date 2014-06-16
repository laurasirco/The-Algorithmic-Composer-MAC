//
//  GaussianDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__GaussianDistribution__
#define __The_Algorithmic_Composer__GaussianDistribution__

#include <iostream>
#include "Distribution.h"
using namespace std;

class GaussianDistribution : public Distribution {
  
public:
	GaussianDistribution();
	~GaussianDistribution();
	float getValue();
	
	void setSigma(float s){ sigma = s; }
	void setMu(float m){ mu = m; }
	float getSigma(){ return sigma; }
	float getMu(){ return mu; }
private:
	float sigma;
	float mu;
};

#endif /* defined(__The_Algorithmic_Composer__GaussianDistribution__) */
