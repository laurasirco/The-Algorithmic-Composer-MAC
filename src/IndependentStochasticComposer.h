//
//  IndependentStochasticComposer.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__IndependentStochasticComposer__
#define __The_Algorithmic_Composer__IndependentStochasticComposer__

#include <iostream>
#include <vector>
#include "Composer.h"
#include "Distribution.h"
#include "Figure.h"
using namespace std;

class IndependentStochasticComposer: public Composer{
public:
    IndependentStochasticComposer(Distribution * d);
	std::vector<Figure *> compose(bool infinite = false);
	void setPitchesDistribution(Distribution * d){ pitchesDistribution = d; }
	void setDurationsDistribution(Distribution * d){ durationsDistribution = d; }
	void setNotesAndSilencesDistribution(Distribution * d){ notesAndSilencesDistribution = d; fixedKind = KBoth; }
	void setScale(int s){ scale = s; }
	void setOctaves(int min, int max){ minOct = min; maxOct = max; }
	void setUniqueDuration(Type t){ uniqueDuration = t; }
	void setNumberOfFigures(int n){ nFigures = n; }
	
	Distribution * getPitchesDistribution(){ return pitchesDistribution; }
	Distribution * getDurationsDistribution(){ return durationsDistribution; }
	Distribution * getNotesAndSilencesDistribution(){ return notesAndSilencesDistribution; }
	
	void setFixedPitch(int p){ fixedPitch = p; cout << "fixedPitch = " << fixedPitch << endl; }
	void setFixedDuration(Type t){ uniqueDuration = t; cout << "fixedDuration = " << uniqueDuration << endl; }
	void setFixedKind(Kind k){ fixedKind = k; }
	
private:
    Distribution * pitchesDistribution;
	Distribution * durationsDistribution;
	Distribution * notesAndSilencesDistribution;
	int mapValue(float value, int min, int max);
	int scale;
	int minOct;
	int maxOct;
	Type uniqueDuration;
	int nFigures;
	
	int fixedPitch;
	Kind fixedKind;
};


#endif /* defined(__The_Algorithmic_Composer__IndependentStochasticComposer__) */
