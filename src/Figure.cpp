//
//  Figure.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#include "Figure.h"
#include <cmath>

Figure::Figure(Type t){
	
	switch (t) {
		case DWhole:
			duration = 1.0 + 1.0/2.0;
			break;
		case Whole:
			duration = 1.0;
			break;
		case DHalf:
			duration = 0.5 + 0.5/2.0;
			break;
		case Half:
			duration = 0.5;
			break;
		case DQuarter:
			duration = 0.25 + 0.25/2.0;
			break;
		case Quarter:
			duration = 0.25;
			break;
		case DEighth:
			duration = 0.125 + 0.125/2.0;
			break;
		case Eighth:
			duration = 0.125;
			break;
		case DSixteenth:
			duration = 0.0625 + 0.0625/2.0;
			break;
		case Sixteenth:
			duration = 0.0625;
			break;
		case DThirtySecond:
			duration = 0.03125 + 0.03125/2.0;
			break;
		case ThirtySecond:
			duration = 0.03125;
			break;
		case SixtyFourth:
			duration = 0.015625;
			break;
		case NotAFigure:
			duration = 0.0;
		default:
			break;
	}
	type = t;
	
	typeNames.push_back("DWhole");
	typeNames.push_back("Whole");
	typeNames.push_back("DHalf");
	typeNames.push_back("Half");
	typeNames.push_back("DQuarter");
	typeNames.push_back("Quarter");
	typeNames.push_back("DEighth");
	typeNames.push_back("Eighth");
	typeNames.push_back("DSixteenth");
	typeNames.push_back("Sixteenth");
	typeNames.push_back("DThirtySecond");
	typeNames.push_back("ThirtySecond");
	typeNames.push_back("SixtyFourth");
	typeNames.push_back("Not a figure");
	
}

float Figure::typeToDuration(Type t){
	
	float d = 0;
	
	if(t == DWhole)
		d = 1.0 + 0.5;
	else if(t == Whole)
		d = 1.0;
	else if(t == DHalf)
		d = 0.5 + 0.5/2;
	else if(t == Half)
		d = 0.5;
	else if(t == DQuarter)
		d = 0.25 + 0.25/2;
	else if(t == Quarter)
		d = 0.25;
	else if (t == DEighth)
		d = 0.125 + 0.125/2;
	else if (t == Eighth)
		d = 0.125;
	else if(t == DSixteenth)
		d = 0.0625 + 0.0625/2;
	else if(t == Sixteenth)
		d = 0.0625;
	else if (t == DThirtySecond)
		d = 0.03125 + 0.03125/2;
	else if (t == ThirtySecond)
		d = 0.03125;
	else if(t == SixtyFourth)
		d = 0.015625;
	
	return d;
}

Type Figure::durationToType(float d){
	
	Type t;
	
	if(d ==  1.0 + 0.5)
		t = DWhole;
	else if(d == 1.0)
		t = Whole;
	else if(d == 0.5 + 0.5/2)
		t = DHalf;
	else if(d == 0.5)
		t = Half;
	else if(d == 0.25 + 0.25/2)
		t = DQuarter;
	else if(d == 0.25)
		t = Quarter;
	else if (d == 0.125 + 0.125/2)
		t = DEighth;
	else if (d == 0.125)
		t = Eighth;
	else if(d == 0.0625 + 0.0625/2)
		t = DSixteenth;
	else if(d == 0.0625)
		t = Sixteenth;
	else if (d == 0.03125 + 0.03125/2)
		t = DThirtySecond;
	else if (d == 0.03125)
		t = ThirtySecond;
	else if(d == 0.015625)
		t = SixtyFourth;
	else
		t = NotAFigure;
	
	return t;
}


Type Figure::MIDIDurationToType(int ppq, int duration){
	
	float division = (float)duration/(float)ppq;
	Type t;
	
	if (division == 6.0) {
		t = DWhole;
	}
	else if (division == 4.0){
		t = Whole;
	}
	else if (division == 3.0){
		t = DHalf;
	}
	else if (division == 2.0){
		t = Half;
	}
	else if (division == 1.5) {
		t = DQuarter;
	}
	else if (division == 1.0) {
		t = Quarter;
	}
	else if (division == 0.75){
		t = DEighth;
	}
	else if (division == 0.5){
		t = Eighth;
	}
	else if (division == 0.25 + 0.25/2){
		t = DSixteenth;
	}
	else if (division == 0.25){
		t = Sixteenth;
	}
	else if (division == 0.125 + 0.125/2){
		t = DThirtySecond;
	}
	else if (division == 0.125){
		t = ThirtySecond;
	}
	else if (division == 0.125/2){
		t = SixtyFourth;
	}
	else{
		
		if (abs(division - (6.0)) < 0.5)
			t = DWhole;
		else if (abs(division - 4.0) < 0.5)
			t = Whole;
		else if (abs(division - (3.0)) < 0.3)
			t = DHalf;
		else if (abs(division - 2.0) < 0.25)
			t = Half;
		else if (abs(division - (1.5)) < 0.2)
			t = DQuarter;
		else if (abs(division - 1.0) < 0.15)
			t = Quarter;
		else if(abs(division - (0.75)) < 0.1)
			t = DEighth;
		else if (abs(division - 0.5) < 0.1)
			t = Eighth;
		else if (abs(division - (0.375)) < 0.02)
			t = DSixteenth;
		else if (abs(division - 0.25) < 0.05)
			t = Sixteenth;
		else if (abs(division - (0.1875)) < 0.012)
			t = DThirtySecond;
		else if (abs(division - 0.125) < 0.01)
			t = ThirtySecond;
		else if (abs(division - 0.0625) < 0.005)
			t = SixtyFourth;
		
	}
	
	return t;
	
	
}