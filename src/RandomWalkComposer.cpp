//
//  RandomWalkComposer.cpp
//  the_algorithmic_composer
//
//  Created by Raúl Ibarra Díez on 09/07/14.
//
//

#include "RandomWalkComposer.h"
#include "Randomize.h"
#include "Scales.h"
#include "Note.h"

RandomWalkComposer::RandomWalkComposer(){

    type = RandomWalk;
    boundary = Reflecting;
	startingPitch = 64;
	minPitch = 0;
	maxPitch = 127;
	scale = 0;
	
}

RandomWalkComposer::~RandomWalkComposer(){
    
    
}

vector<Figure *> RandomWalkComposer::compose(bool infinite){
    
    cout<<"Compose "<<stems<<", "<<meter<<"/"<<pattern<<endl;
	
	std::vector<Figure *> fragment;
	float counter = 0.0;
	float total = calculeTimePerStem();
	bool f;
	Type t;
	float duration;
	
	int prevPitch;
	int currentPitch = startingPitch;
    
	for(int i = 0; i < stems; i++){
		
		while(counter < total){
			
			prevPitch = currentPitch;
			direction = Randomize::getRandomDirection();
			
			if (direction) {
				currentPitch = prevPitch + 1;
				
				if (currentPitch == maxPitch) {
					currentPitch = currentPitch - 2;
				}
			}
			else if (!direction){
				currentPitch = prevPitch - 1;
				
				if (currentPitch == minPitch) {
					currentPitch = currentPitch + 2;
				}
			}
			
			t = patternType;
			counter += Figure::typeToDuration(t);
			
			Note * note = new Note(t, currentPitch, 50);
			fragment.push_back(note);
			
		}
		
		counter = 0.0;
	}
	
	return fragment;
    
}