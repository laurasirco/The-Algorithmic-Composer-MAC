//
//  Distribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__Distribution__
#define __The_Algorithmic_Composer__Distribution__

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

class Distribution{
public:
    Distribution();
	~Distribution();
    float getMean(){ return mean; }
    float getSpread(){ return spread; }
    virtual float getValue() = 0;
    
    void setSpread(float s){ spread = s; }
    void setMean(float m){ mean = m; }
	
	vector<float> getValuesForGraphic(int samples);
protected:
    float mean;
    float spread;
};

#endif /* defined(__The_Algorithmic_Composer__Distribution__) */
