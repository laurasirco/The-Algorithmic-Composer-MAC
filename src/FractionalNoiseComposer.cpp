//
//  FractionalNoiseComposer.cpp
//  the_algorithmic_composer
//
//  Created by Laura Sirvent Collado on 05/08/14.
//
//

#include "FractionalNoiseComposer.h"
#include "Scales.h"
#include "Note.h"
#include <stdlib.h>
#include <time.h>
#include "App.h"
#include <sstream>

#define MAX_PITCH 107
#define MIN_PITCH 36

FractionalNoiseComposer::FractionalNoiseComposer(){
	
	type = FractionalNoise;
	
	fixedDuration = NotAFigure;
	fixedPitch = -1;
	scale = 0;
	
	minOctave = 1;
	maxOctave = 6;
	
	alpha = 1.0;
	
	setPitchesBasedOnScaleAndOctaves();
	
}

FractionalNoiseComposer::~FractionalNoiseComposer(){
	
}

vector<Figure *> FractionalNoiseComposer::compose(bool infinite){
	
	int minPitch = 10*(minOctave + 2) + ListOfScales[scale][0] + (2*minOctave + 4);
	int maxPitch = 10*(maxOctave + 2) + ListOfScales[scale][0] + (2*maxOctave + 4);
	cout << minPitch << ", " << maxPitch << endl;
	
	std::vector<Figure *> fragment;
	vector<float> pitchesNoiseSequence, durationsNoiseSequence;
	float counter = 0.0;
	float total = calculeTimePerStem();
	bool f;
	Type t;
	float duration;
	int c = 0;
	int c2 = 0;
	
	//GET NOISE VALUES
	if (fixedDuration == NotAFigure) {
		durationsNoiseSequence = getFractionalNoiseSequence(500);
	}
	if (fixedPitch == -1) {
		pitchesNoiseSequence = getFractionalNoiseSequence(400);
	}
	
	for (int i = 0; i < stems; i++) {
		
		while (counter < total) {
			f = true; // Only Notes btw
			
			if (fixedDuration == NotAFigure) {
				t = (Type) mapValue(durationsNoiseSequence[c2], 0, 12);
				
				duration = Figure::typeToDuration(t);
				c2++;
				
				int tests = 0;
				
				while(counter + duration > total){
					
					
					float difference = total - counter;
					
					if(tests == 20){
						t = Figure::durationToType(difference);
					}
					else
						t = (Type) mapValue(durationsNoiseSequence[c2], 0, 12);
					
					duration = Figure::typeToDuration(t);
					//cout<<"duration: "<<duration<<" counter: "<<counter<<" +: "<<counter+duration<<" total: "<<total<<endl;
					
					tests++;
					c2++;
				}
			}
			
			else{
				float fixed = Figure::typeToDuration(fixedDuration);
				float patternD = Figure::typeToDuration(patternType) * meter;
				cout << fixed << ", " << patternD << endl;
				
				if (fixed > 0.0 && fixed <= patternD)
					duration = Figure::typeToDuration(fixedDuration);
				else
					duration = Figure::typeToDuration(Figure::durationToType(patternD));
				
				t = Figure::durationToType(duration);
			}
			counter += duration;
			
			if(f){
				
				//int pitch = 10*(octave + 2) + ListOfScales[scale][tone] + (2*octave + 4);
				int pitch;
				
				if (fixedPitch == -1) {
					
					int position = mapValue(pitchesNoiseSequence[c], 0, pitches.size() - 1);
					pitch = pitches[position];
					
					if (pitch < minPitch)
						pitch = minPitch;
					
					if (pitch > maxPitch)
						pitch = maxPitch;
					
					cout << "Value = " << pitchesNoiseSequence[c] << ", pitch  = " << pitch << endl;
				}
				else
					pitch = fixedPitch;
				
				Note * n = new Note(t, pitch, 50);
				c++;
				fragment.push_back(n);
			}
			
		}
		counter = 0.0;
	}
	
	stringstream sst;
	sst << "Got " << fragment.size() << " figures ";
	App::addLogMessage(sst.str());
	
	return fragment;
}


vector<float> FractionalNoiseComposer::getFractionalNoiseSequence(int size){
	
	vector<float> output;
	int seed_init = (int) time(NULL);
	cout << "Seed: " << seed_init << endl;
	double * x = f_alpha(size, 1.0, alpha, &seed_init);
	
	//Get the min and max value
	float min = 0.0;
	float max = 0.0;
	for (int i = 0; i < size; i++) {
		if (x[i] < min)
			min = x[i];
		
		if (x[i] > max)
			max = x[i];
	}
	
	//Map values
	for (int i = 0; i < size; i++) {
		output.push_back(map(x[i], min, max, 0.0f, 1.0f));
	}
	
    return output;
}


float FractionalNoiseComposer::map(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int FractionalNoiseComposer::mapValue(float value, int min, int max){
	
	int returnValue = (value * (max - min)) + min;
	return returnValue;
}


void FractionalNoiseComposer::setPitchesBasedOnScaleAndOctaves(){
	
	int max = 7;
	if (scale == 0)
		max = 12;
	else if (scale == 1)
		max = 5;
	
	pitches.clear();
	
	for (int octave = minOctave; octave <= maxOctave; octave++) {
		
		for (int tone = 0; tone < max; tone++) {
			int pitch = 10*(octave + 2) + ListOfScales[scale][tone] + (2*octave + 4);
			pitches.push_back(pitch);
		}
		
	}
	
}







