//
//  Player.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 12/06/14.
//
//

#include "Player.h"
#include "App.h"
#include "Note.h"
#include <sstream>

Player::Player(int b){
	count = 0;
	BPM = b;
	i = 0;
	allPlayed = true;
	playing = false;
	prevPitch = -1;
	
}

Player::~Player(){
	
}

void Player::stop(){
	
	playing = false;
	allPlayed = true;
	i = fragment.size() - 1;
	fragment.clear();
	prevPitch = -1;
	App::setIsSilence(true);
}

void Player::play(std::vector<Figure*> f){
	
	float FPS = App::getFramerate();
	fragment = f;
	i = 0;
	count = 0;
	allPlayed = false;
	playing = true;
	paused = false;
	prevPitch = -1;
	
	float framesQuarter = (60.0/(float)BPM)/(1.0/(float)FPS);
	cout << "frames per quarter: " << framesQuarter << endl;
	
	Type type = fragment[i]->getType();
	
	switch (type) {
		case DWhole:
			x = framesQuarter * 6;
			break;
		case Whole:
			x = framesQuarter * 4;
			break;
		case DHalf:
			x = framesQuarter * 3;
			break;
		case Half:
			x = framesQuarter * 2;
			break;
		case DQuarter:
			x = framesQuarter * 1.5;
			break;
		case Quarter:
			x = framesQuarter * 1;
			break;
		case DEighth:
			x = framesQuarter * 0.75;
			break;
		case Eighth:
			x = framesQuarter * 0.5;
			break;
		case DSixteenth:
			x = framesQuarter * 0.375;
			break;
		case Sixteenth:
			x = framesQuarter * 0.25;
			break;
		case DThirtySecond:
			x = framesQuarter * 0.1875;
			break;
		case ThirtySecond:
			x = framesQuarter * 0.125;
			break;
		case SixtyFourth:
			x = framesQuarter * 0.0625;
			break;
		default:
			break;
	}
		
	//play note here
	cout<<"Total notes: "<<fragment.size()<<endl;
	cout<<"playing note: "<<i; fragment[i]->printMyself();
	
	App::setCurrentFigure(fragment[i]);
	if(fragment[i]->getKind() == KNote){
		if(prevPitch != -1)
			piano[prevPitch].stop();
		Note * n = (Note *)fragment[i];
		App::setIsSilence(false);
		//App::setMidiNote(n->getPitch());
		//App::setVolume((float)n->getVelocity());
		piano[n->getPitch() - 36].play();
		prevPitch = n->getPitch() - 36;
		
	}
	else{
		if(prevPitch != -1)
			piano[prevPitch].stop();
		prevPitch = -1;
		App::setIsSilence(true);
	}
	
	
}

void Player::update(){
	
	if((count == x) && (i+1 < fragment.size()) && !paused){ //next note
		
		i++;
		count = 0;
		
		float FPS = App::getFramerate();
		float framesQuarter = (60.0/(float)BPM)/(1.0/(float)FPS);
		cout << "frames per quarter: " << framesQuarter << endl;
		
		Type type = fragment[i]->getType();
		
		switch (type) {
			case DWhole:
				x = framesQuarter * 6;
				break;
			case Whole:
				x = framesQuarter * 4;
				break;
			case DHalf:
				x = framesQuarter * 3;
				break;
			case Half:
				x = framesQuarter * 2;
				break;
			case DQuarter:
				x = framesQuarter * 1.5;
				break;
			case Quarter:
				x = framesQuarter * 1;
				break;
			case DEighth:
				x = framesQuarter * 0.75;
				break;
			case Eighth:
				x = framesQuarter * 0.5;
				break;
			case DSixteenth:
				x = framesQuarter * 0.375;
				break;
			case Sixteenth:
				x = framesQuarter * 0.25;
				break;
			case DThirtySecond:
				x = framesQuarter * 0.1875;
				break;
			case ThirtySecond:
				x = framesQuarter * 0.125;
				break;
			case SixtyFourth:
				x = framesQuarter * 0.0625;
				break;
			default:
				break;
		}
		
		//play note here
		cout<<"playing note: "<<i<<" "; fragment[i]->printMyself();
		
		App::setCurrentFigure(fragment[i]);
		if(fragment[i]->getKind() == KNote){
			if(prevPitch != -1)
				piano[prevPitch].stop();
			Note * n = (Note *)fragment[i];
			App::setIsSilence(false);
			//App::setMidiNote(n->getPitch());
			//App::setVolume((float)n->getVelocity());
			piano[n->getPitch() - 36].play();
			prevPitch = n->getPitch() - 36;
			
		}
		else{
			if(prevPitch != -1)
				piano[prevPitch].stop();
			prevPitch = -1;
			App::setIsSilence(true);
		}
		
	}
	
	if (i == fragment.size() - 1 && (count == x)) {
		allPlayed = true;
		playing = false;
		if(prevPitch != -1)
			piano[prevPitch].stop();
		prevPitch = -1;
	}
	else{
		//cout<<"Count "<<count<<" to x "<<x<<endl;
		if(!paused)
			count++;
		else{
			if(prevPitch != -1)
				piano[prevPitch].stop();
			App::setIsSilence(true);
		}
	}
	
}