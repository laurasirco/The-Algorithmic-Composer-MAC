//
//  Player.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 12/06/14.
//
//

#ifndef __The_Algorithmic_Composer__Player__
#define __The_Algorithmic_Composer__Player__

#include <iostream>
#include <vector>
#include "Figure.h"
#include "ofxTonic.h"

using namespace Tonic;
using namespace std;

class Player {

public:
	Player(int b = 60);
	~Player();
	void play(std::vector<Figure *> f);
	void update();
	void setBPM(int b){ BPM = b; }
	bool isAllPlayed(){ return allPlayed; }
	ofxTonicSynth getSynth(){ return synth; }
private:
	int BPM;
	int count;
	int x;
	std::vector<Figure *> fragment;
	int i;
	bool allPlayed;
	
	ofxTonicSynth synth;
};

#endif /* defined(__The_Algorithmic_Composer__Player__) */
