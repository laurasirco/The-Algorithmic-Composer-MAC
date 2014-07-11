//
//  Randomize.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 11/06/14.
//
//

#include "Randomize.h"

bool Randomize::getRandomFigure(){
	
	int value = rand() % 2;
	if(value == 0)
		return false;
	else if(value == 1)
		return true;
}

bool Randomize::getRandomDirection(){
	int value = rand() % 2;
	if(value == 0)
		return false;
	else if(value == 1)
		return true;
}

Type Randomize::getRandomDuration(){
	
	//Type value = (Type)rand() % 7;
	//return value;
}

int Randomize::getRandomPitch(){
	
	int value = 21 + (rand() % 108);
	return value;
}

float Randomize::getRandomValue(){
	
	float value = rand() % 100;
	return value/100;
}