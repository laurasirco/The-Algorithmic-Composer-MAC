//
//  Silence.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#ifndef __The_Algorithmic_Composer__Silence__
#define __The_Algorithmic_Composer__Silence__

#include <iostream>
#include "Figure.h"

class Silence : public Figure{
    public:
	Silence(Type t) : Figure(t){}
	~Silence();
	void printMyself(){ std::cout<<"Im a silence, type "<<t<<" duration "<<duration<<std::endl; }
    private:
};

#endif /* defined(__The_Algorithmic_Composer__Silence__) */
