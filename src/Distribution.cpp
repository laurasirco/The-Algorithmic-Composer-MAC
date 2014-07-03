//
//  Distribution.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "Distribution.h"

Distribution::Distribution(){
	srand(time(NULL));
}

Distribution::~Distribution(){
	
	
}

vector<float> Distribution::getValuesForGraphic(int samples){
	
	vector<float> values;
	
	for (int i = 0; i < 10; i++) {
		values.push_back(0.0);
	}
	
	for (int i = 0; i < samples; i++) {
		float v = getValue();
		
		
		if(v >= 0.0 && v < 0.1)
			values[0] += 0.1;
		else if(v >= 0.1 && v < 0.2)
			values[1] += 0.1;
		else if(v >= 0.2 && v < 0.3)
			values[2] += 0.1;
		else if(v >= 0.3 && v < 0.4)
			values[3] += 0.1;
		else if(v >= 0.4 && v < 0.5)
			values[4] += 0.1;
		else if(v >= 0.5 && v < 0.6)
			values[5] += 0.1;
		else if(v >= 0.6 && v < 0.7)
			values[6] += 0.1;
		else if(v >= 0.7 && v < 0.8)
			values[7] += 0.1;
		else if(v >= 0.8 && v < 0.9)
			values[8] += 0.1;
		else if(v >= 0.9 && v < 1.0)
			values[9] += 0.1;
	}
	
	return values;
	
}