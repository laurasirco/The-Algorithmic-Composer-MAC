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
#include "Scales.h"

using namespace std;

IndependentStochasticComposer::IndependentStochasticComposer(Distribution *d){
	
	distribution = d;
	scale = 0;
	minOct = 2;
	maxOct = 4;
	type = IndependentStochastic;
}

std::vector<Figure *> IndependentStochasticComposer::compose(bool infinite){
	
	cout<<"Compose "<<stems<<", "<<meter<<"/"<<pattern<<", Scale "<<NamesOfScales[scale]<<endl;
	std::vector<Figure *> fragment;
	float counter = 0.0;
	float total = calculeTimePerStem();
	bool f;
	Type t;
	float duration;
	
	
	for(int i = 0; i < stems; i++){
		
		while(counter < total){
			
			if(wantSilences)
				f = Randomize::getRandomFigure();
			else
				f = true;
			
			t = (Type)mapValue(distribution->getValue(), 0, 12);
			
			duration = Figure::typeToDuration(t);
			//cout<<"duration: "<<duration<<endl;
			int tests = 0;
			
			while(counter + duration > total){
				
				float difference = total - counter;
				
				if(tests == 20){
					t = Figure::durationToType(difference);
				}
				else
					t = (Type)mapValue(distribution->getValue(), 0, 12);
				
				duration = Figure::typeToDuration(t);
				//cout<<"duration: "<<duration<<" counter: "<<counter<<" +: "<<counter+duration<<" total: "<<total<<endl;
				
				tests++;
			}
			counter += duration;
			
			if(f){ //Note
				
				int max = 7;
				if (scale == 0)
					max = 12;
				else if (scale == 1)
					max = 5;
				
				int tone = mapValue(distribution->getValue(), 0, 7);
				int octave = mapValue(distribution->getValue(), minOct, maxOct);
				
				int pitch = 10*(octave + 2) + ListOfScales[scale][tone];
				//pitch = mapValue(distribution->getValue(), 0, 127);
				
				
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