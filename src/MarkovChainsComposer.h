//
//  MarkovChainsComposer.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 07/07/14.
//
//

#ifndef __The_Algorithmic_Composer__MarkovChainsComposer__
#define __The_Algorithmic_Composer__MarkovChainsComposer__

#include <iostream>
#include "Composer.h"
#include "Figure.h"
#include "Midi.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MarkovChainsComposer : public Composer {
public:
	MarkovChainsComposer();
	~MarkovChainsComposer();
    std::vector<Figure *> compose(bool infinite = false);
	
	void addMidiToChain(string filename);
	void cleanMatrices();
	void setStartingNote(int i){ startingNote = i; }
	
private:
	float ** pitchesMatrix;
	float ** durationsMatrix;
	int startingNote;
};

#endif /* defined(__The_Algorithmic_Composer__MarkovChainsComposer__) */
