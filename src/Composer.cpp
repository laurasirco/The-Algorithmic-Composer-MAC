//
//  Composer.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#include "Composer.h"

Composer::Composer(){
    
	stems = 1;
	meter = 2;
	pattern = 4;
	wantSilences = true;
	
	if (pattern == 1)
		patternType = Whole;
	else if (pattern == 2)
		patternType = Half;
	else if (pattern == 4)
		patternType = Quarter;
	else if(pattern == 8)
		patternType = Eighth;
	else if (pattern == 16)
		patternType = Sixteenth;
}

Composer::~Composer(){
	
	
}

float Composer::calculeTimePerStem(){

	float time = 0.0;
	
	if (pattern == 1)
		time = Figure::typeToDuration(Whole);
	else if (pattern == 2)
		time = Figure::typeToDuration(Half);
	else if (pattern == 4)
		time = Figure::typeToDuration(Quarter);
	else if(pattern == 8)
		time = Figure::typeToDuration(Eighth);
	else if (pattern == 16)
		time = Figure::typeToDuration(Sixteenth);
	
	time = time * meter;
	
	return time;
		
	
}