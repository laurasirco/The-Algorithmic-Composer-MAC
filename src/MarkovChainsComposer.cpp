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
	
	pitchesMatrix = new float*[12];
	for(int i = 0; i < 12; ++i){
		pitchesMatrix[i] = new float[12];
		
		for (int j = 0; j < 12; j++) {
			pitchesMatrix[i][j] = 1.0; //All starts with one, to avoid dead ends
		}
	}
	
	durationsMatrix = new float*[13];
	for (int i = 0; i < 13; ++i) {
		durationsMatrix[i] = new float[13];
		
		for (int j = 0; j < 13; j++) {
			durationsMatrix[i][j] = 1.0;
		}
	}
	
	type = MarkovChains;
	startingNote = 0;
	
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
	float duration;
	UniformDistribution * distribution = new UniformDistribution();
	int prevPitch = -1;
	Type prevDur = NotAFigure;
	
	for(int i = 0; i < stems; i++){
		
		while(counter < total){
			
			
			f = true;
			float value = distribution->getValue();
			float sum = 0.0;
			Type dur = Quarter;
			
			if (prevDur != NotAFigure) {
				int c = 0;
				bool found = false;
				while (c < 12 && !found) {
					sum += durationsMatrix[c][prevDur];
					if (value >= sum && value < sum + durationsMatrix[c + 1][prevDur]) {
						dur = (Type)c;
						cout<<"Found: "<<dur<<endl;
						found = true;
					}
					c++;
				}
				
				sum += durationsMatrix[12][prevDur];
				if (value >= sum && value < 1.0 && !found) {
					dur = (Type)12;
				}
			}
						
			duration = Figure::typeToDuration(dur);
			cout<<"duration: "<<duration<<endl;
			
			if(counter + duration > total){
				
				float difference = total - counter;

				dur = Figure::durationToType(difference);
				
				cout<<"duration: "<<difference<<" counter: "<<counter<<" +: "<<counter+duration<<" total: "<<total<<endl;

			}
			
			prevDur = dur;
			counter += duration;
			
			
			int max = 7;
			if (scale == 0)
				max = 12;
			else if (scale == 1)
				max = 5;
			
			int tone = startingNote;
			
			//Calcule tone
			value = distribution->getValue();
			sum = 0.0;
			
			if(prevPitch != -1){
				
				int c = 0;
				bool found = false;
				while (c < 11 && !found) {
					sum += pitchesMatrix[c][prevPitch];
					if (value >= sum && value < sum + pitchesMatrix[c + 1][prevPitch]) {
						tone = c;
						found = true;
					}
					c++;
				}
				
				sum += pitchesMatrix[11][prevPitch];
				if (value >= sum && value < 1.0 && !found) {
					tone = 11;
				}
				
			}
			
			prevPitch = tone;
			
			
			int octave = 4;
			
			int pitch = 10*(octave + 2) + ListOfScales[scale][tone];
			//pitch = mapValue(distribution->getValue(), 0, 127);
			
			
			int velocity = 50;
			Note * note = new Note(dur, pitch, velocity);
			fragment.push_back(note);
			
		}
		counter = 0.0;
	}
	
	return fragment;
	
	
}

void MarkovChainsComposer::addMidiToChain(string filename){
	
	vector<Figure *> input = Midi::readMidiFile(filename);
	int prevPitch = -1;
	int rPitch = -1;
	Type prevDur = NotAFigure;
	Type dur = NotAFigure;
	
	for (int i = 0; i < input.size(); i++) {
		
		prevDur = dur;
		dur = input[i]->getType();
		if(prevDur != NotAFigure && dur != NotAFigure)
			durationsMatrix[prevDur][dur]++;
		
		if (input[i]->getKind() == KNote) {
			
			Note * n = (Note *) input[i];
			
			prevPitch = rPitch;
			rPitch = n->getPitch() % 11;
			
			if(prevPitch != -1)
				pitchesMatrix[prevPitch][rPitch]++;
			
		}
	}
	
	
	//Pitches Matrix normalization
	for (int i = 0; i < 12; i++) {
		
		float sum = 0;
		
		for (int j = 0; j < 12; j++) {
			sum += pitchesMatrix[j][i];
		}
		for (int j = 0; j < 12; j++) {
			pitchesMatrix[j][i] /= sum;
		}
	}
	
	//Durations Matrix normalization
	for (int i = 0; i < 13; i++) {
		
		float sum = 0;
		
		for (int j = 0; j < 13; j++) {
			sum += durationsMatrix[j][i];
		}
		for (int j = 0; j < 13; j++) {
			durationsMatrix[j][i] /= sum;
		}
	}
	
	
	/*cout<<"PITCHES MATRIX"<<endl;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			cout << pitchesMatrix[i][j] << " ";
		}
		cout << endl;
	}
	
	
	cout<<"DURATIONS MATRIX"<<endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			cout << durationsMatrix[i][j] << " ";
		}
		cout << endl;
	}*/
	
}

void MarkovChainsComposer::cleanMatrices(){
	
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			pitchesMatrix[i][j] = 0.0;
		}
	}
	
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			durationsMatrix[i][j] = 0.0;
		}
	}
	
}
