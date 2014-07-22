//
//  MotivicDevelopmentComposer.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 21/07/14.
//
//

#include "MotivicDevelopmentComposer.h"
#include "Note.h"
#include <cmath>

#define MAX_PITCH 107
#define MIN_PITCH 36

MotivicDevelopmentComposer::MotivicDevelopmentComposer(){
	
	sequence.push_back(Transpose);

}

MotivicDevelopmentComposer::~MotivicDevelopmentComposer(){
	
}

vector<Figure *> MotivicDevelopmentComposer::compose(bool infinite){
	
	
}

vector<Figure *> MotivicDevelopmentComposer::transpose(int steps){
	
	

	vector<Figure *> transposed;
	
	for (int i = 0; i < motive.size(); i++) {
		if (motive[i]->getKind() == KNote) {
			Note * n = dynamic_cast<Note *>(motive[i]);
			int pitch = n->getPitch();
			pitch += steps;
			
			if (pitch < MIN_PITCH)
				pitch = MIN_PITCH;
		
			if (pitch > MAX_PITCH)
				pitch = MAX_PITCH;
			
			Note * t = new Note(n->getType(), pitch, n->getVelocity());
			transposed.push_back(t);
			
		}
		else
			transposed.push_back(motive[i]);
	}
	
	return transposed;
	
}


vector<Figure *> MotivicDevelopmentComposer::regDisplacement(vector<int> reg){
	
	int counter = 0;
	vector<Figure *> regDisplaced;
	
	for (int i = 0; i < motive.size(); i++) {
		if (motive[i]->getKind() == KNote) {
			Note * n = dynamic_cast<Note *>(motive[i]);
			
			int pitch = n->getPitch();
			pitch += 12 * reg[counter];
			counter++;
			
			if (pitch < MIN_PITCH)
				pitch = MIN_PITCH;
			
			if (pitch > MAX_PITCH)
				pitch = MAX_PITCH;
			
			Note * rd = new Note(n->getType(), pitch, n->getVelocity());
			regDisplaced.push_back(rd);
		}
		else{
			regDisplaced.push_back(motive[i]);
		}
	}
	
	return regDisplaced;
}


vector<Figure *> MotivicDevelopmentComposer::invert(){
	
	vector<Figure *> inverted;
	inverted.push_back(motive[0]);
	
	for (int i = 1; i < motive.size(); i++) {
		
		if(motive[i]->getKind() == KNote){
			
			int prevInPitch = findPreviousPitchFrom(i, motive);
			int prevOutPitch = findPreviousPitchFrom(i, inverted);
			
			if(prevInPitch != -1 && prevOutPitch != -1){
				Note *n = dynamic_cast<Note *>(motive[i]);
				
				int pitch = prevOutPitch - (n->getPitch() - prevInPitch);
				
				if (pitch < MIN_PITCH)
					pitch = MIN_PITCH;
				
				if (pitch > MAX_PITCH)
					pitch = MAX_PITCH;
				
				Note *i = new Note(n->getType(), pitch, n->getVelocity());
				inverted.push_back(i);
			}
			
		}
		else{
			inverted.push_back(motive[i]);
		}
		
	}
	
}


int MotivicDevelopmentComposer::findPreviousPitchFrom(int position, vector<Figure *> v){
	
	bool found = false;
	int c = position;
	
	while (!found && c > -1) {
		if (v[c]->getKind() == KNote) {
			Note * n = dynamic_cast<Note *>(v[c]);
			return n->getPitch();
		}
		else
			c--;
	}
	
	return -1;
	
	
}


vector<Figure *> MotivicDevelopmentComposer::retrograde(){
	
	int j;
	vector<Figure *> retrograded;
	
	for(int i = 0; i < motive.size(); i++){
		j = motive.size() - 1 - i;
		
		retrograded.push_back(motive[j]);
	}
	
	return retrograded;
}



vector<Figure *> MotivicDevelopmentComposer::expand(int steps){
	
	vector<Figure *> expanded;
	
	expanded.push_back(motive[0]);
	
	for (int i = 1; i < motive.size(); i++) {
		if (motive[i]->getKind() == KNote) {
			
			Note * n = dynamic_cast<Note *>(motive[i]);
			int pitch = n->getPitch();
			
			int prevPitch = findPreviousPitchFrom(i, motive);
			
			if (prevPitch != -1) {
				int interval = abs(n->getPitch() - prevPitch) + steps;
				
				if (interval < 1) {
					interval = 1;
				}
				if (n->getPitch() > prevPitch) {
					pitch = prevPitch + interval;
				}
				else{
					pitch = prevPitch - interval;
				}
			}
			
			if (pitch < MIN_PITCH)
				pitch = MIN_PITCH;
			
			if (pitch > MAX_PITCH)
				pitch = MAX_PITCH;
			
			Note * e = new Note(n->getType(), pitch, n->getVelocity());
			expanded.push_back(e);
		}
	}
	
	return expanded;
	
}




