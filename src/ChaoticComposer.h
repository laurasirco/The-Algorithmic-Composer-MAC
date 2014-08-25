//
//  ChaoticComposer.h
//  the_algorithmic_composer
//
//  Created by Laura Sirvent Collado on 06/08/14.
//
//

#ifndef __the_algorithmic_composer__ChaoticComposer__
#define __the_algorithmic_composer__ChaoticComposer__

#include <iostream>
#include "Composer.h"
#include "Figure.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum DynamicalSystem {
	LogisticMap, HenonMap, MandelbrotSet, TentMap
};

enum Variables {
	Pitches, Durations, Velocities
};

class ChaoticComposer : public Composer{
	
public:
	ChaoticComposer();
	~ChaoticComposer();
	vector<Figure *> compose(bool infinite = false);
	
	void setDynamicalSystem(DynamicalSystem s){ system = s; }
	DynamicalSystem getDynamicalSystem(){ return system; }
	
	void setScale(int s){ scale = s; setPitchesBasedOnScaleAndOctaves(); };
	void setMinAndMaxOctave(int min, int max){ minOctave = min; maxOctave = max; setPitchesBasedOnScaleAndOctaves(); }
	
	void setIterations(int i){ iterations = i; }
	
	void setA(float a){ A = a; }
	void setB(float b){ B = b; }
	void setX0(float x){ x0 = x; }
	void setY0(float y){ y0 = y; }
	
	void setFixedDuration(Type t){ fixedDuration = t; }
	
private:
	DynamicalSystem system;
	Type fixedDuration;
	
	float x0;
	float y0;
	float A;
	float B;
	
	int scale;
	int minOctave;
	int maxOctave;
	int iterations;
	
	vector<int> pitches;
	
	vector<float> pitchesSequence;
	vector<float> durationsSequence;
	vector<float> velocitiesSequence;
	
	void setPitchesBasedOnScaleAndOctaves();
	
	void getSequenceByLogisticMap(float x0, float alpha, int size, vector<float> * seq1);
	void getSequencesByHenonMap(float x0, float y0, float a, float b, int size, vector<float> * seq1, vector<float> * seq2);
	void getSequenceByMandelbrotSet(float x0, float c, int size, vector<float> * seq1);
	void getSequenceByTentMap(float x0, float mu, int size, vector<float> * seq1);
	
	int mapValue(float value, int min, int max);
	float map(float x, float in_min, float in_max, float out_min, float out_max);
	vector<float> mapVector(vector<float> input);
	
};

#endif /* defined(__the_algorithmic_composer__ChaoticComposer__) */
