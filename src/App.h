#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "Composer.h"
#include "Player.h"

#include "UniformDistribution.h"
#include "LinearDistribution.h"
#include "TriangularDistribution.h"
#include "ExponentialDistribution.h"
#include "GaussianDistribution.h"
#include "CauchyDistribution.h"
#include "BetaDistribution.h"
#include "WeibullDistribution.h"
#include "PoissonDistribution.h"

#include <iostream>
using namespace std;
#include "ofxTonic.h"

using namespace Tonic;

class App : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
	void audioRequested (float * output, int bufferSize, int nChannels);

	static float getFramerate(){ return ofGetFrameRate(); }
	
	static void setMidiNote(int note);
	static void setIsSilence(bool t);
	static void setVolume(float volume);
	static void setCurrentFigure(Figure * f);
private:
    
	Composer * composer;
	Player * player;
	static ofxTonicSynth synth;
	
	void initSynth();
	void initGUI();
	void setValuesForGraph(Distribution * d);
	void showIndependentStochasticGUI(bool show);
	void showMarkovChainsGUI(bool show);
	void setGUITheme(int i);
	
	std::vector<Figure *> composition;
	
	UniformDistribution * uniform;
	LinearDistribution * linear;
	TriangularDistribution * triangular;
	ExponentialDistribution * exponential;
	GaussianDistribution * gauss;
	CauchyDistribution * cauchy;
	BetaDistribution * beta;
	WeibullDistribution * weibull;
	PoissonDistribution * poisson;
	
	void guiEvent(ofxUIEventArgs &e);

	vector<ofxUICanvas *> guis;
	ofxUICanvas * methodGUI;
	static ofxUIScrollableCanvas * resultsGui;
	ofxUICanvas * generalGUI;
	ofxUICanvas * styleGUI;
	ofColor backgroundColor; 
	float red, green, blue;
	ofTrueTypeFont musicNotesFont;
	
	static ofxUITextArea *currentFigureLabel;
	ofxUIRadio *scaleRadioButtons;
	ofxUIImageToggle * pauseToggle;
	
	
	/* INDEPENDENT STOCHASTIC GUI */
	
	ofxUICanvas *isGUI1;
	ofxUIScrollableCanvas *isGUI2;
	ofxUICanvas *distributionGUI;
	ofxUIMovingGraph * mg;
	
	ofxUICanvas * linearDistGUI;
	ofxUICanvas * triangularDistGUI;
	ofxUICanvas * exponentialDistGUI;
	ofxUICanvas * gaussDistGUI;
	ofxUICanvas * cauchyDistGUI;
	ofxUICanvas * betaDistGUI;
	ofxUICanvas * weibullDistGUI;
	ofxUICanvas * poissonDistGUI;
	
	
	/* MARKOV CHAINS GUI */
	
	ofxUICanvas *mcGUI1;
	ofxUILabel *fileLabel;
	
};
