//
//  ChaoticComposer.cpp
//  the_algorithmic_composer
//
//  Created by Laura Sirvent Collado on 06/08/14.
//
//

#include "ChaoticComposer.h"
#include "Note.h"
#include "Scales.h"
#include "App.h"
#include <sstream>

ChaoticComposer::ChaoticComposer(){
	
	system = LogisticMap;
	
	type = Chaotic;
	scale = 0;
	
	minOctave = 1;
	maxOctave = 6;
	
	stems = 10;
	
	iterations = 10;
	x0 = 0.1;
	y0 = 0.1;
	A = 1.0;
	B = 0.3;

	setPitchesBasedOnScaleAndOctaves();
	
	fixedDuration = patternType;
	
}

ChaoticComposer::~ChaoticComposer(){
	
}


vector<Figure *> ChaoticComposer::compose(bool infinite){
	
	int minPitch = 10*(minOctave + 2) + ListOfScales[scale][0] + (2*minOctave + 4);
	int maxPitch = 10*(maxOctave + 2) + ListOfScales[scale][0] + (2*maxOctave + 4);
	vector<Figure *> fragment;
	float counter = 0.0;
	float total = calculeTimePerStem();
	bool f;
	Type t;
	float duration;
	
	//Clear sequences
	pitchesSequence.clear();
	durationsSequence.clear();
	velocitiesSequence.clear();
	
	int c1 = 0;
	int c2 = 0;
	int c3 = 0;
	
	//Get the sequence
	if (system == LogisticMap) {
		getSequenceByLogisticMap(x0, A, iterations, &pitchesSequence);
	}
	else if (system == HenonMap){
		getSequencesByHenonMap(x0, y0, A, B, iterations, &pitchesSequence, &durationsSequence);
	}
	else if (system == MandelbrotSet){
		getSequenceByMandelbrotSet(x0, A, iterations, &pitchesSequence);
	}
	else if (system == TentMap){
		getSequenceByTentMap(x0, A, iterations, &pitchesSequence);
	}
	
	for (int i = 0; i < iterations; i++) {
		
		f = true; // Only notes btw
		
		if (durationsSequence.size() == 0) {
			
			t = fixedDuration;
		}
		else{
			t = (Type) mapValue(durationsSequence[c2], 0, 12);
			c2++;
		}
		
		if (f) {
			
			int pitch;
			
			if (pitchesSequence.size() == 0) {
				
			}
			else{
				
				int position = mapValue(pitchesSequence[c1], 0, pitches.size() - 1);
				pitch = pitches[position];
				
				if (pitch < minPitch)
					pitch = minPitch;
				
				if (pitch > maxPitch)
					pitch = maxPitch;
								
				c1++;
				
			}
			
			Note * n = new Note(t, pitch, 50);
			fragment.push_back(n);
		}
	}
	
	/*
	for (int i = 0; i < stems; i++) {
		while (counter < total) {
			
			f = true; // Only notes btw
			
			if (durationsSequence.size() == 0) {
				duration = Figure::typeToDuration(patternType);
				
				cout << "duration: " << duration << endl;
				t = Figure::durationToType(duration);
			}
			
			else{
				
				t = (Type) mapValue(durationsSequence[c2], 0, 12);
				duration = Figure::typeToDuration(t);
				c2++;
				
				int tests = 0;
				
				while (counter + duration > total) {
					float difference = total - counter;
					
					if(tests == 20){
						t = Figure::durationToType(difference);
					}
					else
						t = (Type) mapValue(durationsSequence[c2], 0, 12);
					
					duration = Figure::typeToDuration(t);					
					tests++;
					c2++;
				}
			}
			counter += duration;
			
			if (f) {
				
				int pitch;
				
				if (pitchesSequence.size() == 0) {
					
				}
				else{
					
					int position = mapValue(pitchesSequence[c1], 0, pitches.size() - 1);
					pitch = pitches[position];
					
					if (pitch < minPitch)
						pitch = minPitch;
					
					if (pitch > maxPitch)
						pitch = maxPitch;
					
					cout << "Value = " << pitchesSequence[c1] << ", pitch  = " << pitch << endl;
					
					c1++;

				}
				
				Note * n = new Note(t, pitch, 50);
				fragment.push_back(n);
			}
		}
		counter = 0.0;
	}*/
	
	stringstream sst;
	sst << "Got " << fragment.size() << " figures ";
	App::addLogMessage(sst.str());
	
	return fragment;
}


/* SYSTEMS */


void ChaoticComposer::getSequenceByLogisticMap(float x0, float alpha, int size, vector<float> * seq1){
	
	vector<float> sequence;
	
	sequence.push_back(x0);
	
	int i = 0;
	while (i < size - 1) {
		
		float x = alpha * x0 * (1 - x0);
		sequence.push_back(x);
		x0 = x;
		i++;
		cout << " i :" << i <<", x : " << x0 << endl;
		
	}
	cout << "-------------------------" << endl << endl;
	*seq1 = mapVector(sequence);
}

void ChaoticComposer::getSequencesByHenonMap(float x0, float y0, float a, float b, int size, vector<float> *seq1, vector<float> *seq2){
	
	vector<float> s1;
	vector<float> s2;
	
	s1.push_back(x0);
	s2.push_back(y0);
	
	int i = 0;
	while (i < size - 1) {
		float x = - a*x0*x0 + y0 + 1;
		float y = b * x0;
		x0 = x;
		y0 = y;
		
		i++;
		
		s1.push_back(x0);
		s2.push_back(y0);
		cout << " i :" << i <<", x : " << x0 << ", y : " << y0 << endl;
	}
	cout << "-------------------------" << endl << endl;
	
	*seq1 = mapVector(s1);
	*seq2 = mapVector(s2);
}

void ChaoticComposer::getSequenceByMandelbrotSet(float x0, float c, int size, vector<float> *seq1){
	
	vector<float> s1;
	
	s1.push_back(x0);
	
	int i = 0;
	while(i < size - 1){
		
		float x = x0*x0 + c;
		x0 = x;
		i++;
		s1.push_back(x0);
		cout << " i :" << i <<", x : " << x0 << endl;
	}
	cout << "-------------------------" << endl << endl;
	*seq1 = mapVector(s1);
}

void ChaoticComposer::getSequenceByTentMap(float x0, float mu, int size, vector<float> *seq1){
	
	vector<float> s1;
	
	s1.push_back(x0);
	
	int i = 0;
	while (i < size - 1) {
		
		float x;
		
		if (x0 < 0.5)
			x = mu * x0;
		else
			x = mu * (1 - x0);
		
		x0 = x;
		i++;
		s1.push_back(x0);
		cout << " i :" << i <<", x : " << x0 << endl;
	}
	
	cout << "-------------------------" << endl << endl;
	*seq1 = mapVector(s1);
}

/* UTILS */

float ChaoticComposer::map(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int ChaoticComposer::mapValue(float value, int min, int max){
	
	int returnValue = (value * (max - min)) + min;
	return returnValue;
}

vector<float> ChaoticComposer::mapVector(vector<float> input){
	
	vector<float> output;
	float min = 0.0;
	float max = 0.0;
	
	for (int i = 0; i < input.size(); i++) {
		if (input[i] < min) {
			min = input[i];
		}
		
		if (input[i] > max) {
			max = input[i];
		}
	}
	
	for (int i = 0; i < input.size(); i++) {
		float mappedValue = map(input[i], min, max, 0.0, 1.0);
		output.push_back(mappedValue);
	}
	
	return output;
}


void ChaoticComposer::setPitchesBasedOnScaleAndOctaves(){
	
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
