//
//  Figure.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#include "Figure.h"

Figure::Figure(Type t){
	
	switch (t) {
		case Whole:
			duration = 1.0;
			break;
		case Half:
			duration = 0.5;
			break;
		case Quarter:
			duration = 0.25;
			break;
		case Eighth:
			duration = 0.125;
			break;
		case Sixteenth:
			duration = 0.0625;
			break;
		case ThirtySecond:
			duration = 0.03125;
			break;
		case SixtyFourth:
			duration = 0.015625;
		default:
			break;
	}
	
}

float Figure::typeToDuration(Type t){
	
	float d = 0;
	
	if(t == Whole)
		d = 1.0;
	else if(t == Half)
		d = 0.5;
	else if(t == Quarter)
		d = 0.25;
	else if (t == Eighth)
		d = 0.125;
	else if(t == Sixteenth)
		d = 0.0625;
	else if (t == ThirtySecond)
		d = 0.03125;
	else if(t == SixtyFourth)
		d = 0.015625;
	
	return d;
}