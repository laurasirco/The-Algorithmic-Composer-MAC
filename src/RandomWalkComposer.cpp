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
	startingPitch = 50;
	minPitch = 0;
	maxPitch = 127;
	scale = 2;
	
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
	
	int prevRelativePitch;
	int currentRelativePitch = startingPitch % 11;
	int octave = (startingPitch / 11) - 2;
	
	int scaleLimit = 8;
	if (scale == 0) {
		scaleLimit = 12;
	}
	else if (scale == 1){
		scaleLimit = 5;
	}
    
	for(int i = 0; i < stems; i++){
		
		while(counter < total){
			
			prevRelativePitch = currentRelativePitch;
			prevPitch = currentPitch;
			direction = Randomize::getRandomDirection();
			
			if (direction) {
				cout << "arriba" << endl;
				currentPitch = prevPitch + 1;
				
				currentRelativePitch++;
				
				cout<<currentRelativePitch<<endl;
				
				if (currentRelativePitch >= scaleLimit) {
					cout<<"aumento"<<endl;
					currentRelativePitch = 0;
					octave++;
					cout<<currentRelativePitch<<", octava: "<<octave<<endl;
					
				}
				currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch];
				cout << currentPitch << endl;
				
				if (currentPitch == maxPitch) {
					currentRelativePitch--;
					currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch];
				}
			}
			else if (!direction){
				cout << "abajo" << endl;
				currentPitch = prevPitch - 1;
				
				currentRelativePitch--;
				
				cout<<currentRelativePitch<<endl;
				
				if (currentRelativePitch <= -1) {
					cout<<"disminuyo"<<endl;
					currentRelativePitch = scaleLimit;
					octave--;
					cout<<currentRelativePitch<<", octava: "<<octave<<endl;
				}
				currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch];
				cout << currentPitch << endl;
				
				if (currentPitch == minPitch) {
					currentRelativePitch++;
					currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch];
				}
			}
			
			t = patternType;
			counter += Figure::typeToDuration(t);
			
			Note * note = new Note(t, currentPitch, 50);
			fragment.push_back(note);
			cout << "---" << endl;
			
		}
		
		counter = 0.0;
	}
	
	return fragment;
    
}