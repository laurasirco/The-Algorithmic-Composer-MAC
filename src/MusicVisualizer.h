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

enum IMetric{
	IM21, IM31, IM41, IM22, IM32, IM42, IM24, IM34, IM44, IM28, IM38, IM48, IM216, IM316, IM416
};

enum INote{
	INDWhole, INWhole, INDDHalf, INUDHalf, INDHalf, INUHalf, INDDQuarter, INUDQuarter, INDQuarter, INUQuarter, INDDEighth, INUDEighth, INDEighth, INUEighth, INDDSixteenth, INUDSixteenth, INDSixteenth, INUSixteenth, INDDThirtySecond, INUDThirtySecond, INDThirtySecond, INUThirtySecond, INDSixtyFourth, INUSixtyFourth, ISDWhole, ISWhole, ISDHalf, ISHalf, ISDQuarter, ISQuarter, ISDEighth, ISEighth, ISDSixteenth, ISSixteenth, ISDThirtySecond, ISThirtySecond, ISSixtyFourth
};

class MusicVisualizer {
  
public:
	MusicVisualizer();
	~MusicVisualizer();
	void draw();
	void drawFigures(vector<Figure *> f);
	void update();
	void pause(){ paused = true; }
	void unpause(){ paused = false; }
	void stop();
	
private:
	
	ofImage claveSol;
	ofImage claveFa;
	
	vector<ofImage> metricImages;
	vector<ofImage> figureImages;
	
	float velocity;
	int currentFigure;
	
	vector<Figure *> figures;
	vector<int> positions;
	vector<bool> appeared;
	vector<INote> images;
	
	float map(float x, float in_min, float in_max, float out_min, float out_max);
	float getFactorOfType(Type t);
	INote getImageNoteOfFigure(Figure * f);
	
	bool paused;
	bool playing;
	bool allPlayed;
	
};

#endif /* defined(__The_Algorithmic_Composer__MusicVisualizer__) */
