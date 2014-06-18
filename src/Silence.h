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
#include <string>
using namespace std;

class Silence : public Figure{
    public:
	Silence(Type t) : Figure(t){
		kind = KSilence;
	}
	~Silence();
	void printMyself();
	string getDescription();
    private:
};

#endif /* defined(__The_Algorithmic_Composer__Silence__) */
