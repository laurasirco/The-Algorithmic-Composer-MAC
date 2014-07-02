//
//  Utils.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 02/07/14.
//
//

#include <stdio.h>
#include <cmath>

float getFrequency(float midiNote){
	return  (440 * pow(2.0f, ((midiNote - 69)/12)));
}