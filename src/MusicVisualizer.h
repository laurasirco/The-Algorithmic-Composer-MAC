//
//  MusicVisualizer.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 15/07/14.
//
//

#ifndef __The_Algorithmic_Composer__MusicVisualizer__
#define __The_Algorithmic_Composer__MusicVisualizer__

#include <iostream>
#include "Figure.h"
#include "ofMain.h"

#include <vector>
#include <string>
using namespace std;



class MusicVisualizer {
  
public:
	MusicVisualizer();
	~MusicVisualizer();
	void draw();
	void drawFigures(vector<Figure *> f);
	void update();
	
private:
	
	ofImage claveSol;
	ofImage claveFa;
	ofImage metric;
	
	ofImage dWhole;
	
	float velocity;
	int frameCount;
	int currentFigure;
	
	vector<Figure *> figures;
	vector<int> positions;
	vector<bool> appeared;
	
	float map(float x, float in_min, float in_max, float out_min, float out_max);
	float getFactorOfType(Type t);
	
};

#endif /* defined(__The_Algorithmic_Composer__MusicVisualizer__) */
