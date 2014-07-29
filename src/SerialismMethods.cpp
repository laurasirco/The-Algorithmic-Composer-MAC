//
//  SerialismMethods.cpp
//  the_algorithmic_composer
//
//  Created by Laura Sirvent Collado on 26/07/14.
//
//

#include "SerialismMethods.h"
#include "Note.h"


SMethod::SMethod(SeriesType t){
	
	type = t;
}


SMethod::~SMethod(){
	
	
}



RetrogradeSMethod::RetrogradeSMethod(SeriesType t) : SMethod(t){
	
}

RetrogradeSMethod::~RetrogradeSMethod(){
	
}


vector<Figure *> RetrogradeSMethod::performTransformation(vector<Figure *> motive){
	
	vector<Figure *> retrograded;
	
	for (int i = 11; i >= 0; i--) {
		
		if (type == TPitch) {
			
			if (motive[i]->getKind() == KNote) {
				Note * n = dynamic_cast<Note *>(motive[i]);
				Note * n2 = dynamic_cast<Note *>(motive[11 - i]);
				
				Note * n3 = new Note(n2->getType(), n->getPitch(), n2->getVelocity());
				retrograded.push_back(n3);
			}
			
		}
		else if (type == TRhythm){
			if (motive[i]->getKind() == KNote) {
				Note * n = dynamic_cast<Note *>(motive[i]);
				Note * n2 = dynamic_cast<Note *>(motive[11 - i]);
				
				Note * n3 = new Note(n->getType(), n2->getPitch(), n2->getVelocity());
				retrograded.push_back(n3);
			}
		}
		else if (type == TPitchAndRhythm){
			if (motive[i]->getKind() == KNote) {
				Note * n = dynamic_cast<Note *>(motive[i]);
				Note * n2 = dynamic_cast<Note *>(motive[11 - i]);
				
				Note * n3 = new Note(n->getType(), n->getPitch(), n2->getVelocity());
				retrograded.push_back(n3);
			}
		}
		
	}
	
	return retrograded;
}




InvertSMethod::InvertSMethod(SeriesType t) : SMethod(t){
	
}

InvertSMethod::~InvertSMethod(){
	
}

vector<Figure *> InvertSMethod::performTransformation(vector<Figure *> motive){
	
	vector<Figure *> inverted;
	
	for (int i = 0; i < 12; i++) {
		
		if (type == TPitch) {
			
			if (motive[i]->getKind() == KNote) {
				Note * n = dynamic_cast<Note *>(motive[i]);
				Note * n2 = new Note(n->getType(), (12 - n->getPitch())%12, n->getVelocity());
				inverted.push_back(n2);
			}
			else
				inverted.push_back(motive[i]);
		}
		else if(type == TRhythm){
			
			Type t = (Type)((12 - motive[i]->getType())%12);
			
			if (motive[i]->getKind() == KNote) {
				Note * n = dynamic_cast<Note *>(motive[i]);
				Note * n2 = new Note(t, n->getPitch(), n->getVelocity());
				inverted.push_back(n2);
			}
		}
		else if (type == TPitchAndRhythm){
			
			Type t = (Type)((12 - motive[i]->getType())%12);
			
			if (motive[i]->getKind() == KNote) {
				Note * n = dynamic_cast<Note *>(motive[i]);
				Note * n2 = new Note(t, (12 - n->getPitch())%12, n->getVelocity());
				inverted.push_back(n2);
			}
			
		}
	}
	
	return inverted;
	
}


RetrogradeInversionSMethod::RetrogradeInversionSMethod(SeriesType t) : SMethod(t){
	
}

RetrogradeInversionSMethod::~RetrogradeInversionSMethod(){
	
}

vector<Figure *> RetrogradeInversionSMethod::performTransformation(vector<Figure *> motive){
	
	vector<Figure *> r1;
	vector<Figure *> r2;
	RetrogradeSMethod * m1 = new RetrogradeSMethod(type);
	InvertSMethod * m2 = new InvertSMethod(type);
	
	r1 = m1->performTransformation(motive);
	r2 = m2->performTransformation(r1);
	
	return r2;
	
}


TransposeSMethod::TransposeSMethod(SeriesType t, int s) : SMethod(t){
	steps = s;
}

TransposeSMethod::~TransposeSMethod(){
	
}

vector<Figure *> TransposeSMethod::performTransformation(vector<Figure *> motive){
	
	vector<Figure *> transposed;
	
	for (int i = 0; i < 12; i++) {
		
		if (type == TPitch) {
			
			if (motive[i]->getKind() == KNote) {
				
				Note * n = dynamic_cast<Note *>(motive[i]);
				
				int pitch = (n->getPitch() + steps) % 12;
				
				Note * n2 = new Note(n->getType(), pitch, n->getVelocity());
				
				transposed.push_back(n2);
			}
			else
				transposed.push_back(motive[i]);
		}
		
		else if (type == TRhythm){
			
			Type t = (Type)((motive[i]->getType() + steps) % 12);
			if (motive[i]->getKind() == KNote) {
				Note * n = dynamic_cast<Note *>(motive[i]);
				Note * n2 = new Note(t, n->getPitch(), n->getVelocity());
				transposed.push_back(n2);
			}
			
		}
		else if (type == TPitchAndRhythm){
			
			Type t = (Type)((motive[i]->getType() + steps) % 12);
			if (motive[i]->getKind() == KNote) {
				Note * n = dynamic_cast<Note *>(motive[i]);
				int pitch = (n->getPitch() + steps) % 12;
				Note * n2 = new Note(t, pitch, n->getVelocity());
				transposed.push_back(n2);
			}
		}
	}
	
	return transposed;
}




RepetitionSMethod::RepetitionSMethod(SeriesType t) : SMethod(t){
	
}


RepetitionSMethod::~RepetitionSMethod(){
	
}

vector<Figure *> RepetitionSMethod::performTransformation(vector<Figure *> motive){
	
	return motive;
}



