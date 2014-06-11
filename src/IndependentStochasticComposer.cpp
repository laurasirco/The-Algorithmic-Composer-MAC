//
//  IndependentStochasticComposer.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "IndependentStochasticComposer.h"
#include "Randomize.h"
#include "Note.h"
#include "Silence.h"

IndependentStochasticComposer::IndependentStochasticComposer(Distribution *d){
	
	distribution = d;
}

std::vector<Figure *> IndependentStochasticComposer::compose(bool infinite, int meter, int pattern, int stems){
	
	std::vector<Figure *> fragment;
	float counter = 0.0;
	float total = (float)meter / (float)pattern;
	bool f;
	Type t;
	float duration;
	
	for(int i = 0; i < stems; i++){
		
		while(counter < total){
			
			f = Randomize::getRandomFigure();

			t = (Type)mapValue(distribution->getValue(), 0, 6);
			
			duration = Figure::typeToDuration(t);
			
			while(counter + duration > total){
				t = (Type)mapValue(distribution->getValue(), 0, 6);
				duration = Figure::typeToDuration(t);
			}
			counter += duration;
			
			if(f){ //Note
				int pitch = mapValue(distribution->getValue(), 21, 108);
				int velocity = mapValue(distribution->getValue(), 0, 100);
				Note * note = new Note(t, pitch, velocity);
				fragment.push_back(note);
			}
			else{ //Silence
				Silence * silence = new Silence(t);
				fragment.push_back(silence);
			}
		}
		counter = 0.0;
	}
	
	return fragment;
}

int IndependentStochasticComposer::mapValue(float value, int min, int max){
	
	int returnValue = (value * (max - min)) + min;
	return returnValue;
}