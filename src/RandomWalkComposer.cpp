//
//  RandomWalkComposer.cpp
//  the_algorithmic_composer
//
//  Created by Raúl Ibarra Díez on 09/07/14.
//
//

#include "RandomWalkComposer.h"
#include "Randomize.h"
#include "Note.h"
#include "Utils.h"
#include "Scales.h"


RandomWalkComposer::RandomWalkComposer(){

    type = RandomWalk;
    boundary = Reflecting;
	startingGrade = 0;
	
	maxOctave = 4;
	minOctave = 2;
	
	scale = 0;
	figureType = patternType;
	
	minPitch = 10*(minOctave + 2) + ListOfScales[scale][0] + (2*minOctave + 4);
	maxPitch = 10*(maxOctave + 2) + ListOfScales[scale][0] + (2*maxOctave + 4);
	
}

void RandomWalkComposer::setMaxOctave(int m){
	maxOctave = m;
	maxPitch = 10*(maxOctave + 2) + ListOfScales[scale][0] + (2*maxOctave + 4);
}

void RandomWalkComposer::setMinOctave(int m){
	minOctave = m;
	minPitch = 10*(minOctave + 2) + ListOfScales[scale][0] + (2*minOctave + 4);
}

RandomWalkComposer::~RandomWalkComposer(){
    
    
}

vector<Figure *> RandomWalkComposer::compose(bool infinite){
    
    cout<<"Compose "<<stems<<", "<<meter<<"/"<<pattern<<endl;
	
	std::vector<Figure *> fragment;
	float counter = 0.0;
	float total = calculeTimePerStem();
	bool f;
	float duration;
	
	int currentPitch;
	
	int prevRelativePitch;
	int octave = Utils::map(Randomize::getRandomValue(), 0, 1, minOctave, maxOctave);
	int octaveChangeDown = OctaveDown[scale];
	int octaveChangeUp = OctaveUp[scale];
	
	if(Figure::typeToDuration(figureType) > Figure::typeToDuration(patternType))
		figureType = patternType;
	
	int scaleLimit = 7;
	if (scale == 0) {
		scaleLimit = 12;
	}
	else if (scale == 1){
		scaleLimit = 5;
	}
	
	//int currentRelativePitch = Utils::map(Randomize::getRandomValue(), 0, 1, 0, scaleLimit);
	int currentRelativePitch = startingGrade;
	
	for(int i = 0; i < stems; i++){
		
		while(counter < total){
			
			prevRelativePitch = currentRelativePitch;
			direction = Randomize::getRandomDirection();
			
			if (direction) {
				cout << "arriba" << endl;
				
				currentRelativePitch++;
				
				cout<<currentRelativePitch<<endl;
				
				if (currentRelativePitch == scaleLimit){
					cout<<"vuelta +"<<endl;
					currentRelativePitch = 0;
					cout<<currentRelativePitch<<endl;
				}
				if (currentRelativePitch == octaveChangeUp) {
					cout<<"cambio octava"<<endl;
					octave++;
					cout<<currentRelativePitch<<", octava: "<<octave<<endl;
					
				}
				
				currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
				
				if (currentPitch > maxPitch) {
					cout << "Se pasa por arriba" << endl;
					
					currentRelativePitch -= 2;
					cout << currentRelativePitch << endl;
					
					if (currentRelativePitch == -1) {
						cout<<"vuelta -"<<endl;
						currentRelativePitch = scaleLimit - 1;
						cout<<currentRelativePitch<<endl;
					}
					if (currentRelativePitch == octaveChangeDown) {
						cout<<"cambio octava"<<endl;
						octave--;
						cout<<currentRelativePitch<<", octava: "<<octave<<endl;
					}
					
					currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
				}
				
				cout << currentPitch << endl;
			}
			else if (!direction){
				cout << "abajo" << endl;
				
				currentRelativePitch--;
				
				cout << currentRelativePitch << endl;
				
				if (currentRelativePitch == -1) {
					cout<<"vuelta -"<<endl;
					currentRelativePitch = scaleLimit - 1;
					cout<<currentRelativePitch<<endl;
				}
				if (currentRelativePitch == octaveChangeDown) {
					cout<<"cambio octava"<<endl;
					octave--;
					cout<<currentRelativePitch<<", octava: "<<octave<<endl;
				}
				
				currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
				
				if (currentPitch < minPitch) {
					cout << "se pasa por abajo" << endl;
					
					currentRelativePitch += 2;
					cout << currentRelativePitch << endl;
					
					if (currentRelativePitch == scaleLimit){
						cout<<"vuelta +"<<endl;
						currentRelativePitch = 0;
						cout<<currentRelativePitch<<endl;
					}
					if (currentRelativePitch == octaveChangeUp) {
						cout<<"cambio octava"<<endl;
						octave++;
						cout<<currentRelativePitch<<", octava: "<<octave<<endl;
						
					}
					
					currentPitch = 10*(octave + 2) + ListOfScales[scale][currentRelativePitch] + (2*octave + 4);
				}
				
				cout << currentPitch << endl;
			}
			
			counter += Figure::typeToDuration(figureType);
			
			Note * note = new Note(figureType, currentPitch, 50);
			fragment.push_back(note);
			cout << "---" << endl;
			
		}
		
		counter = 0.0;
	}
	
	return fragment;
    
}