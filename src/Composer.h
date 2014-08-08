//
//  Composer.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#ifndef __The_Algorithmic_Composer__Composer__
#define __The_Algorithmic_Composer__Composer__

#include <iostream>
#include "Figure.h"
#include <vector>

enum CType {
	IndependentStochastic, MarkovChains, RandomWalk, MotivicDevelopment, Serialist, FractionalNoise, Chaotic
};

class Composer{
public:
	Composer();
	~Composer();
	virtual std::vector<Figure *> compose(bool infinite = false) = 0;
	void setStems(int s){ stems = s; }
	void setMeter(int m){ meter = m; }
	void setPattern(int p){ pattern = p; if (pattern == 1)
		patternType = Whole;
	else if (pattern == 2)
		patternType = Half;
	else if (pattern == 4)
		patternType = Quarter;
	else if(pattern == 8)
		patternType = Eighth;
	else if (pattern == 16)
		patternType = Sixteenth; }
	void setWantSilences(bool s){ wantSilences = s; }
	
	CType getType(){ return type; }
	
	int getMeter(){ return meter; }
	int getPattern(){ return pattern; }
	float calculeTimePerStem();
	
protected:
	int stems;
	int meter;
	int pattern;
	bool wantSilences;
	CType type;
	Type patternType;
	
};

#endif /* defined(__The_Algorithmic_Composer__Composer__) */
