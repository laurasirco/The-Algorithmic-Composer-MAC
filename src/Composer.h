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
	IndependentStochastic, MarkovChains
};

class Composer{
public:
	Composer();
	~Composer();
	virtual std::vector<Figure *> compose(bool infinite = false) = 0;
	void setStems(int s){ stems = s; }
	void setMeter(int m){ meter = m; }
	void setPattern(int p){ pattern = p; }
	void setWantSilences(bool s){ wantSilences = s; }
	
	CType getType(){ return type; }
protected:
	int stems;
	int meter;
	int pattern;
	bool wantSilences;
	CType type;
	
	float calculeTimePerStem();
};

#endif /* defined(__The_Algorithmic_Composer__Composer__) */
