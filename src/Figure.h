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
#include <vector>
#include <string>
using namespace std;

enum Type{
	DWhole, Whole, DHalf, Half, DQuarter, Quarter, DEighth, Eighth, DSixteenth, Sixteenth, DThirtySecond, ThirtySecond, SixtyFourth, NotAFigure
};

enum Kind{
	KNote, KSilence
};

class Figure{
public:
    Figure(Type t);
    ~Figure();
	static float typeToDuration(Type t);
	static Type durationToType(float d);
	static Type MIDIDurationToType(int ppq, int duration);
	virtual void printMyself() = 0;
	float getDuration(){ return duration; }
	Kind getKind(){ return kind; }
	Type getType(){ return type; }
	virtual string getDescription() = 0;
protected:
    float duration;
    //int attackPoint;
	Type type;
	Kind kind;
	std::vector<std::string> typeNames;
};

#endif /* defined(__The_Algorithmic_Composer__Figure__) */
