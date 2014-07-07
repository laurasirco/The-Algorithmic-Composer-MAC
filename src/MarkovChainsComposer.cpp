//
//  MarkovChainsComposer.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 07/07/14.
//
//

#include "MarkovChainsComposer.h"
#include "Note.h"
#include "Silence.h"
#include "Scales.h"
#include "UniformDistribution.h"
#include "Randomize.h"

MarkovChainsComposer::MarkovChainsComposer(){
	
	matrix = new float*[12];
	for(int i = 0; i < 12; ++i){
		matrix[i] = new float[12];
		
		for (int j = 0; j < 12; j++) {
			matrix[i][j] = 0.0;
		}
	}
	
	
}

MarkovChainsComposer::~MarkovChainsComposer(){
	
	
}

vector<Figure *> MarkovChainsComposer::compose(bool infinite){
	
	int scale = 0;
	cout<<"Compose "<<stems<<", "<<meter<<"/"<<pattern<<", Scale "<<NamesOfScales[0]<<endl;
	std::vector<Figure *> fragment;
	float counter = 0.0;
	float total = calculeTimePerStem();
	bool f;
	Type t;
	float duration;
	UniformDistribution * distribution = new UniformDistribution();
	int prevPitch = -1;
	
	for(int i = 0; i < stems; i++){
		
		while(counter < total){
			
			
			f = true;
			t = Quarter;
			
			duration = Figure::typeToDuration(t);
			//cout<<"duration: "<<duration<<endl;
			int tests = 0;
			
			while(counter + duration > total){
				
				float difference = total - counter;
				
				if(tests == 20){
					t = Figure::durationToType(difference);
				}
				
				duration = Figure::typeToDuration(t);
				//cout<<"duration: "<<duration<<" counter: "<<counter<<" +: "<<counter+duration<<" total: "<<total<<endl;
				
				tests++;
			}
			counter += duration;
			
			
			int max = 7;
			if (scale == 0)
				max = 12;
			else if (scale == 1)
				max = 5;
			
			int tone = 0;
			
			//Calcule tone
			float value = distribution->getValue();
			float sum = 0.0;
			
			if(prevPitch != -1){
				
				sum += matrix[0][prevPitch];
				if (value >= sum && value < sum + matrix[1][prevPitch]) {
					tone = 0;
				}
				
				sum += matrix[1][prevPitch];
				if (value >= sum && value < sum + matrix[2][prevPitch]) {
					tone = 1;
				}
				
				sum += matrix[2][prevPitch];
				if (value >= sum && value < sum + matrix[3][prevPitch]) {
					tone = 2;
				}
				
				sum += matrix[3][prevPitch];
				if (value >= sum && value < sum + matrix[4][prevPitch]) {
					tone = 3;
				}
				
				sum += matrix[4][prevPitch];
				if (value >= sum && value < sum + matrix[5][prevPitch]) {
					tone = 4;
				}
				
				sum += matrix[5][prevPitch];
				if (value >= sum && value < sum + matrix[6][prevPitch]) {
					tone = 5;
				}
				
				sum += matrix[6][prevPitch];
				if (value >= sum && value < sum + matrix[7][prevPitch]) {
					tone = 6;
				}
				
				sum += matrix[7][prevPitch];
				if (value >= sum && value < sum + matrix[8][prevPitch]) {
					tone = 7;
				}
				
				sum += matrix[8][prevPitch];
				if (value >= sum && value < sum + matrix[9][prevPitch]) {
					tone = 8;
				}
				
				sum += matrix[9][prevPitch];
				if (value >= sum && value < sum + matrix[10][prevPitch]) {
					tone = 9;
				}
				
				sum += matrix[10][prevPitch];
				if (value >= sum && value < sum + matrix[11][prevPitch]) {
					tone = 10;
				}
				
				sum += matrix[11][prevPitch];
				if (value >= sum && value < 1.0) {
					tone = 11;
				}
				
			}
			
			prevPitch = tone;
			
			
			int octave = 4;
			
			int pitch = 10*(octave + 2) + ListOfScales[scale][tone];
			//pitch = mapValue(distribution->getValue(), 0, 127);
			
			
			int velocity = 50;
			Note * note = new Note(t, pitch, velocity);
			fragment.push_back(note);
			
		}
		counter = 0.0;
	}
	
	return fragment;
	
	
}

void MarkovChainsComposer::addMidiToChain(string filename){
	
	vector<Figure *> input = Midi::readMidiFile(filename);
	int prev = -1;
	int rPitch = -1;
	
	for (int i = 0; i < input.size(); i++) {
		
		if (input[i]->getKind() == KNote) {
			
			Note * n = (Note *) input[i];
			
			prev = rPitch;
			rPitch = n->getPitch() % 11;
			
			if(prev != -1)
				matrix[prev][rPitch]++;
			
		}
	}
	
	for (int i = 0; i < 12; i++) {
		
		float sum = 0;
		
		for (int j = 0; j < 12; j++) {
			sum += matrix[j][i];
		}
		for (int j = 0; j < 12; j++) {
			matrix[j][i] /= sum;
		}
	}
	
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	
}
