//
//  SerialistComposer.h
//  the_algorithmic_composer
//
//  Created by Laura Sirvent Collado on 26/07/14.
//
//

#ifndef __the_algorithmic_composer__SerialistComposer__
#define __the_algorithmic_composer__SerialistComposer__

#include <iostream>
#include "Composer.h"
#include "Figure.h"
#include "Midi.h"
#include "SerialismMethods.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SerialistComposer : public Composer {
public:
	SerialistComposer();
	~SerialistComposer();
	vector<Figure *> compose(bool infinite = false);
	
	void setSequence(vector<SMethod *> s){ sequence = s; }
	void setMelodicClasses(vector<int> mC){ if(mC.size() == 12){ melodicClasses.clear(); melodicClasses = mC;} }
	void setRhythmicClasses(vector<Type> rC){ if(rC.size() == 12){ rhythmicClasses.clear(); rhythmicClasses = rC;} }
	
	void setOriginalSeries(vector<int> o){ if(o.size() == 12){ original.clear(); original = o;} }
	int getOctave(){ return octave; }
	void setOctave(int o){ octave = o; }
	void addMethodToSequence(SMethod *m){ sequence.push_back(m); }
	void resetSequence(){ sequence.clear(); }
	void setFixedPitches(bool s){ fixedPitch = s; }
	void setFixedRhythm(bool s){ fixedRhythm = s; }
	
private:
	
	vector<int> melodicClasses;
	vector<Type> rhythmicClasses;
	vector<SMethod *> sequence;
	
	vector<int> original;
	
	int octave;
	bool fixedPitch;
	bool fixedRhythm;
	
};


#endif /* defined(__the_algorithmic_composer__SerialistComposer__) */
