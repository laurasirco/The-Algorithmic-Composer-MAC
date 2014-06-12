#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "Composer.h"
#include "Player.h"

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
    
	ofxUITabBar *guiTabBar;
	vector<ofxUICanvas *> guis;
	void guiEvent(ofxUIEventArgs &e);
	
	static float getFramerate(){ return ofGetFrameRate(); }
	
	static void setMidiNote(int note);
private:
    
	Composer * composer;
	Player * player;
	static ofxTonicSynth synth;

};
