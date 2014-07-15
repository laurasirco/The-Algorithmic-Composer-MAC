//
//  Utils.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 02/07/14.
//
//

#include <stdio.h>
#include <cmath>
#pragma once

namespace Utils {
	
	float getFrequency(float midiNote){
		return  (440 * pow(2.0f, ((midiNote - 69)/12)));
	}
	
	float map(float x, float in_min, float in_max, float out_min, float out_max){
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
	
}