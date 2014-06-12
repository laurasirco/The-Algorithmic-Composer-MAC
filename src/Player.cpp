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
	
	float duration = fragment[i]->getDuration();
	
	if (duration == 1)
		x = framesQuarter * 4;
	else if (duration == 0.5)
		x = framesQuarter * 2;
	else if(duration == 0.25)
		x = framesQuarter;
	else if(duration == 0.125)
		x = framesQuarter / 2;
	else if(duration == 0.0625)
		x = framesQuarter / 4;
	else if(duration == 0.03125)
		x = framesQuarter / 8;
	else if(duration == 0.015625)
		x = framesQuarter / 16;
	
	//play note here
	cout<<"Total notes: "<<fragment.size()<<endl;
	cout<<"playing note: "<<i; fragment[i]->printMyself();
	
	if(fragment[i]->getKind() == KNote){
		Note * n = (Note *)fragment[i];
		App::setMidiNote(n->getPitch());
	}
		
}

void Player::update(){
	
	if((count == x) && (i+1 < fragment.size())){ //next note
		
		i++;
		count = 0;
		
		float FPS = App::getFramerate();
		float framesQuarter = (60/BPM)/(1/FPS);
		
		float duration = fragment[i]->getDuration();
		
		if (duration == 1)
			x = framesQuarter * 4;
		else if (duration == 0.5)
			x = framesQuarter * 2;
		else if(duration == 0.25)
			x = framesQuarter;
		else if(duration == 0.125)
			x = framesQuarter / 2;
		else if(duration == 0.0625)
			x = framesQuarter / 4;
		else if(duration == 0.03125)
			x = framesQuarter / 8;
		else if(duration == 0.015625)
			x = framesQuarter / 16;
		
		//play note here
		cout<<"playing note: "<<i<<" "; fragment[i]->printMyself();
		
		if(fragment[i]->getKind() == KNote){
			Note * n = (Note *)fragment[i];
			App::setMidiNote(n->getPitch());
		}
		
	}
	
	if (i == fragment.size() - 1 && (count == x)) {
		allPlayed = true;
	}
	else{
		//cout<<"Count "<<count<<" to x "<<x<<endl;
		count++;
	}

}