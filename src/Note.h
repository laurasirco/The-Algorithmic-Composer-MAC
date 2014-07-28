//
//  Note.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#ifndef __The_Algorithmic_Composer__Note__
#define __The_Algorithmic_Composer__Note__

#include <iostream>
#include <string>
using namespace std;
#include "Figure.h"

class Note : public Figure{
public:
    Note(Type t, int p, int v) : Figure(t){
		pitch = p;
		velocity = v;
		kind = KNote;
	}
    ~Note();
	void printMyself();
	int getPitch(){ return pitch; }
	int getVelocity(){ return velocity; }
	
	void setPitch(int p){ pitch = p; }
	
	string getDescription();
private:
    int pitch;
    int velocity;
};

#endif /* defined(__The_Algorithmic_Composer__Note__) */
