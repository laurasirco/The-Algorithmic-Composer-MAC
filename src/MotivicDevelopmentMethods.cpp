//
//  MotivicDevelopmentMethods.cpp
//  the_algorithmic_composer
//
//  Created by Raúl Ibarra Díez on 22/07/14.
//
//

#include "MotivicDevelopmentMethods.h"
#include "Note.h"
#include <cmath>

#define MAX_PITCH 107
#define MIN_PITCH 36

/* METHOD */

Method::Method(){
    
}

Method::~Method(){
    
}

int Method::findPreviousPitchFrom(int position, vector<Figure *> v){
	
	bool found = false;
	int c = position - 1;
	
	while (!found && c > -1 && c < v.size()) {
		if (v[c]->getKind() == KNote) {
			Note * n = dynamic_cast<Note *>(v[c]);
			return n->getPitch();
            found = true;
		}
		else
			c--;
	}
	
	return -1;
	
	
}

/* TRANSPOSE METHOD */

TransposeMethod::TransposeMethod(int s){
    steps = s;
}

TransposeMethod::~TransposeMethod(){
    
}

vector<Figure *> TransposeMethod::performTransformation(vector<Figure *> motive){
    
    vector<Figure *> transposed;
	cout << "TRANSPOSITION, " << steps << " steps. ";
	
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

/* REGDISP METHOD */

RegisterDisplacement::RegisterDisplacement(vector<int> r){
    regSteps = r;
}

RegisterDisplacement::~RegisterDisplacement(){
    
}

vector<Figure *> RegisterDisplacement::performTransformation(vector<Figure *> motive){
    
    int counter = 0;
	vector<Figure *> regDisplaced;
	cout << "REGISTER DISPLACEMENT, ";
	
	for (int i = 0; i < motive.size(); i++) {
		if (motive[i]->getKind() == KNote) {
			Note * n = dynamic_cast<Note *>(motive[i]);
			cout << regSteps[counter] << " ";
			int pitch = n->getPitch();
			pitch += 12 * regSteps[counter];
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
	cout << " steps. ";
	
	return regDisplaced;
}

/* INVERT METHOD */

InvertMethod::InvertMethod(){

}

InvertMethod::~InvertMethod(){
    
}

vector<Figure *> InvertMethod::performTransformation(vector<Figure *> motive){
    
    vector<Figure *> inverted;
	cout << "INVERT. ";
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
    
    return inverted;
}

/* RETRO METHOD */

RetrogradeMethod::RetrogradeMethod(){
    
}

RetrogradeMethod::~RetrogradeMethod(){
    
}

vector<Figure *> RetrogradeMethod::performTransformation(vector<Figure *> motive){
    
    int j;
	cout << "RETROGRADE. ";
	vector<Figure *> retrograded;
	
	for(int i = 0; i < motive.size(); i++){
		j = motive.size() - 1 - i;
		
		retrograded.push_back(motive[j]);
	}
	
	return retrograded;
}

/* EXPAND METHOD */


ExpandMethod::ExpandMethod(int s){
    steps = s;
}

ExpandMethod::~ExpandMethod(){
    
}

vector<Figure *> ExpandMethod::performTransformation(vector<Figure *> motive){
    
    vector<Figure *> expanded;
	cout << "EXPAND " << steps << " steps. ";
	expanded.push_back(motive[0]);
	
	for (int i = 1; i < motive.size(); i++) {
		if (motive[i]->getKind() == KNote) {
			
			Note * n = dynamic_cast<Note *>(motive[i]);
			int pitch = n->getPitch();
			
			int prevInPitch = findPreviousPitchFrom(i, motive);
			int prevOutPitch = findPreviousPitchFrom(i, expanded);
			
			if (prevInPitch != -1 && prevOutPitch != -1) {
				int interval = abs(n->getPitch() - prevInPitch) + steps;
				
				if (interval < 1) {
					interval = 1;
				}
				if (pitch > prevInPitch) {
					pitch = prevOutPitch + interval;
				}
				else{
					pitch = prevOutPitch - interval;
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

RepetitionMethod::RepetitionMethod(){
	
}

RepetitionMethod::~RepetitionMethod(){
	
	
}

vector<Figure *> RepetitionMethod::performTransformation(vector<Figure *> motive){
	
	cout << "REPETITION. ";
	return motive;
}