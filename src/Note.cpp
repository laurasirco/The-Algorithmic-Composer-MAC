//
//  Note.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#include "Note.h"
#include <sstream>

Note::~Note(){
    
    
}

void Note::printMyself(){
	std::cout<<"Im a note, type "<<typeNames[type]<<", duration "<<duration<<", pitch "<<pitch<<", velocity "<<velocity<<std::endl;
}

string Note::getDescription(){
	
	stringstream st;
	st << "Note " << typeNames[type];
	st << " Pitch " << pitch;
	st << " Velocity " << velocity << endl;
	
	return st.str();
}