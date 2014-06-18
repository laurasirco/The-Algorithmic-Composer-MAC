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

Player::Player(int b){
	count = 0;
	BPM = b;
	i = 0;
	allPlayed = true;
}

Player::~Player(){
	
}

void Player::play(std::vector<Figure*> f){
	
	float FPS = App::getFramerate();
	fragment = f;
	i = 0;
	count = 0;
	allPlayed = false;
	
	float framesQuarter = (60/BPM)/(1/FPS);
	
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
		Note * n = (Note *)fragment[i];
		App::setIsSilence(false);
		App::setMidiNote(n->getPitch());
		
	}
	else
		App::setIsSilence(true);
	
}

void Player::update(){
	
	if((count == x) && (i+1 < fragment.size())){ //next note
		
		i++;
		count = 0;
		
		float FPS = App::getFramerate();
		float framesQuarter = (60/BPM)/(1/FPS);
		
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
			Note * n = (Note *)fragment[i];
			App::setIsSilence(false);
			App::setVolume(n->getVelocity());
			App::setMidiNote(n->getPitch());
		}
		else
			App::setIsSilence(true);
		
	}
	
	if (i == fragment.size() - 1 && (count == x)) {
		allPlayed = true;
	}
	else{
		//cout<<"Count "<<count<<" to x "<<x<<endl;
		count++;
	}
	
}