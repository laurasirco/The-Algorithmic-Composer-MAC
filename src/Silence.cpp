//
//  Silence.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#include "Silence.h"
#include <sstream>

void Silence::printMyself(){
	
	std::cout<<"Im a silence, type "<<typeNames[type]<<" duration "<<duration<<std::endl;
}

string Silence::getDescription(){
	
	stringstream st;
	st << "Silence " << typeNames[type];
	
	return st.str();
}