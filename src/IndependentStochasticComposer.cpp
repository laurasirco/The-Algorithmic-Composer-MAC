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
	
	pitchesDistribution = d;
	durationsDistribution = d;
	notesAndSilencesDistribution = d;
	scale = 0;
	minOct = 2;
	maxOct = 4;
	type = IndependentStochastic;
	
	uniqueDuration = NotAFigure;
	fixedPitch = -1;
	nFigures = 0;
}

std::vector<Figure *> IndependentStochasticComposer::compose(bool infinite){
	
	cout<<"Compose "<<stems<<", "<<meter<<"/"<<pattern<<", Scale "<<NamesOfScales[scale]<<endl;
	std::vector<Figure *> fragment;
	float counter = 0.0;
	float total = calculeTimePerStem();
	bool f;
	Type t;
	float duration;
	
	if (nFigures == 0) {
		
		for(int i = 0; i < stems; i++){
			
			while(counter < total){
				
				float fig = notesAndSilencesDistribution->getValue();
				
				if(fig <= 0.5)
					f = true;
				else
					f = false;
				
				if(uniqueDuration == NotAFigure){
					
					t = (Type)mapValue(durationsDistribution->getValue(), 0, 12);
					
					duration = Figure::typeToDuration(t);
					//cout<<"duration: "<<duration<<endl;
					int tests = 0;
					
					while(counter + duration > total){
						
						float difference = total - counter;
						
						if(tests == 20){
							t = Figure::durationToType(difference);
						}
						else
							t = (Type)mapValue(durationsDistribution->getValue(), 0, 12);
						
						duration = Figure::typeToDuration(t);
						//cout<<"duration: "<<duration<<" counter: "<<counter<<" +: "<<counter+duration<<" total: "<<total<<endl;
						
						tests++;
					}
					
				}
				else{
					float fixed = Figure::typeToDuration(uniqueDuration);
					float patternD = Figure::typeToDuration(patternType) * meter;
					cout << fixed << ", " << patternD << endl;
					
					if (fixed > 0.0 && fixed <= patternD)
						duration = Figure::typeToDuration(uniqueDuration);
					else
						duration = Figure::typeToDuration(Figure::durationToType(patternD));
					
					cout << "duration: " << duration << endl;
					t = Figure::durationToType(duration);
				}
				
				counter += duration;
				
				if(f){ //Note
					
					int max = 7;
					if (scale == 0)
						max = 12;
					else if (scale == 1)
						max = 5;
					

					int tone = mapValue(pitchesDistribution->getValue(), 0, 7);
					int octave = mapValue(pitchesDistribution->getValue(), minOct, maxOct);
					
					int pitch = 10*(octave + 2) + ListOfScales[scale][tone] + (2*octave + 4);
					
					if (fixedPitch != -1) {
						pitch = fixedPitch;
					}
					//pitch = mapValue(distribution->getValue(), 0, 127);
					
					
					int velocity = mapValue(pitchesDistribution->getValue(), 0, 100);
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
	}
	
	else{
	
		for (int i = 0; i < nFigures; i++) {
			float fig = notesAndSilencesDistribution->getValue();
			
			if(fig <= 0.5)
				f = true;
			else
				f = false;
			
			if(uniqueDuration == NotAFigure){
				
				t = (Type)mapValue(durationsDistribution->getValue(), 0, 12);
				
				duration = Figure::typeToDuration(t);
				//cout<<"duration: "<<duration<<endl;
				int tests = 0;
				
				while(counter + duration > total){
					
					float difference = total - counter;
					
					if(tests == 20){
						t = Figure::durationToType(difference);
					}
					else
						t = (Type)mapValue(durationsDistribution->getValue(), 0, 12);
					
					duration = Figure::typeToDuration(t);
					//cout<<"duration: "<<duration<<" counter: "<<counter<<" +: "<<counter+duration<<" total: "<<total<<endl;
					
					tests++;
				}
				
			}
			else{
				
				if (uniqueDuration > patternType)
					duration = Figure::typeToDuration(patternType);
				
				else
					duration = Figure::typeToDuration(uniqueDuration);
			}
			if(f){ //Note
				
				int max = 7;
				if (scale == 0)
					max = 12;
				else if (scale == 1)
					max = 5;
				
				int tone = mapValue(pitchesDistribution->getValue(), 0, 7);
				int octave = mapValue(pitchesDistribution->getValue(), minOct, maxOct);
				
				int pitch = 10*(octave + 2) + ListOfScales[scale][tone] + (2*octave + 4);
				//pitch = mapValue(distribution->getValue(), 0, 127);
				
				
				int velocity = mapValue(pitchesDistribution->getValue(), 0, 100);
				Note * note = new Note(t, pitch, velocity);
				fragment.push_back(note);
			}
			else{ //Silence
				Silence * silence = new Silence(t);
				fragment.push_back(silence);
			}
			
			
		}
	}
	
	return fragment;
}

int IndependentStochasticComposer::mapValue(float value, int min, int max){
	
	int returnValue = (value * (max - min)) + min;
	return returnValue;
}