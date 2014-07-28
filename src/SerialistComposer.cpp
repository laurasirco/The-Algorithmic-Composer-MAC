//
//  SerialistComposer.cpp
//  the_algorithmic_composer
//
//  Created by Laura Sirvent Collado on 26/07/14.
//
//

#include "SerialistComposer.h"
#include "Note.h"


SerialistComposer::SerialistComposer(){
	
	RetrogradeSMethod *rgm = new RetrogradeSMethod(TPitch);
	InvertSMethod *im = new InvertSMethod(TPitch);
	RetrogradeInversionSMethod *rgim = new RetrogradeInversionSMethod(TPitch);
	
	for(int i = 0; i < 12; i++){
		
		melodicClasses.push_back(60 + i);
		rhythmicClasses.push_back((Type) i);
				
		TransposeSMethod *tm = new TransposeSMethod(TRhythm, i);
		
		/*sequence.push_back(tm);
		sequence.push_back(rgm);
		sequence.push_back(im);
		sequence.push_back(rgim);*/
	}
	
	TransposeSMethod *tm = new TransposeSMethod(TRhythm, 0);
	sequence.push_back(tm);
	sequence.push_back(rgm);
	sequence.push_back(im);
	sequence.push_back(rgim);
	
	original.push_back(0);
	original.push_back(11);
	original.push_back(5);
	original.push_back(2);
	original.push_back(10);
	original.push_back(1);
	original.push_back(4);
	original.push_back(7);
	original.push_back(3);
	original.push_back(6);
	original.push_back(9);
	original.push_back(8);
	
}

SerialistComposer::~SerialistComposer(){
	
}


vector<Figure *> SerialistComposer::compose(bool infinite){
	
	vector<Figure *> originalMotive;
	std::vector<Figure *> fragment;
	
	for (int i = 0; i < 12; i++) {
		Note * n = new Note((Type)original[i], 60, 50);
		originalMotive.push_back(n);
	}
	
	for (int i = 0; i < sequence.size(); i++) {
		vector<Figure *> transformation = sequence[i]->performTransformation(originalMotive);
		
		fragment.insert(fragment.end(), transformation.begin(), transformation.end());
	}
	
	for (int i = 0; i < fragment.size(); i++) {
		
		Note * n = dynamic_cast<Note *>(fragment[i]);
		if (n->getPitch() >= 0 && n->getPitch() <= 11) {
			n->setPitch(melodicClasses[n->getPitch()]);
		}
	}
	
	return fragment;
	
}