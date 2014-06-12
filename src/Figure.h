//
//  Figure.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#ifndef __The_Algorithmic_Composer__Figure__
#define __The_Algorithmic_Composer__Figure__

#include <iostream>

enum Type{
	Whole, Half, Quarter, Eighth, Sixteenth, ThirtySecond, SixtyFourth
};

enum Kind{
	KNote, KSilence
};

class Figure{
public:
    Figure(Type t);
    ~Figure();
	static float typeToDuration(Type t);
	virtual void printMyself() = 0;
	float getDuration(){ return duration; }
	Kind getKind(){ return kind; }
protected:
    float duration;
    //int attackPoint;
	Type t;
	Kind kind;
};

#endif /* defined(__The_Algorithmic_Composer__Figure__) */
