//
//  FractionalNoiseComposer.h
//  the_algorithmic_composer
//
//  Created by Laura Sirvent Collado on 05/08/14.
//
//

#ifndef __the_algorithmic_composer__FractionalNoiseComposer__
#define __the_algorithmic_composer__FractionalNoiseComposer__

#include <iostream>
#include "Composer.h"
#include "Figure.h"
#include <iostream>
#include <vector>
#include <string>
#include "colorednoise.h"


class FractionalNoiseComposer : public Composer {
	
public:
	FractionalNoiseComposer();
	~FractionalNoiseComposer();
	vector<Figure *> compose(bool infinite = false);
	
	void setFixedPitch(int p){ fixedPitch = p; }
	void setFixedDuration(Type t){ fixedDuration = t; }
	void setScale(int s){ scale = s; setPitchesBasedOnScaleAndOctaves(); };
	void setMinAndMaxOctave(int min, int max){ minOctave = min; maxOctave = max; setPitchesBasedOnScaleAndOctaves(); }
	void setNoiseAlpha(float a){ if (a >= 0.0 && a <= 2.0) alpha = a; }
	
	vector<float> getFractionalNoiseSequence(int size);
	
private:
	
	int mapValue(float value, int min, int max);
	float map(float x, float in_min, float in_max, float out_min, float out_max);
	void setPitchesBasedOnScaleAndOctaves();
	
	int fixedPitch;
	Type fixedDuration;
	int scale;
	int minOctave;
	int maxOctave;
	float alpha;
	vector<int> pitches;
	
};

#endif /* defined(__the_algorithmic_composer__FractionalNoiseComposer__) */
