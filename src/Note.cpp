//
//  Note.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#include "Note.h"


Note::~Note(){
    
    
}

void Note::printMyself(){
	std::cout<<"Im a note, type "<<typeNames[type]<<", duration "<<duration<<", pitch "<<pitch<<", velocity "<<velocity<<std::endl;
}