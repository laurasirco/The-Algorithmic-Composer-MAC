//
//  MotivicDevelopmentComposer.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 21/07/14.
//
//

#ifndef __The_Algorithmic_Composer__MotivicDevelopmentComposer__
#define __The_Algorithmic_Composer__MotivicDevelopmentComposer__

#include <iostream>
#include "Composer.h"
#include "Figure.h"
#include "Midi.h"
#include "MotivicDevelopmentMethods.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Operation{
	Transpose, RegDisplacement, Invert, Retrograde, Expand
};

class MotivicDevelopmentComposer : public Composer {
public:
	MotivicDevelopmentComposer();
	~MotivicDevelopmentComposer();
	vector<Figure *> compose(bool infinite = false);
	void setMotive(vector<Figure *> m){ motive = m; }
	void setSequence(vector<Method *> s){ sequence = s; }
private:
	vector<Method *> sequence;
	vector<Figure *> motive;
	
};

#endif /* defined(__The_Algorithmic_Composer__MotivicDevelopmentComposer__) */
