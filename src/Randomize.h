//
//  Randomize.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 11/06/14.
//
//

#ifndef __The_Algorithmic_Composer__Randomize__
#define __The_Algorithmic_Composer__Randomize__

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Figure.h"

class Randomize {

public:
	static bool getRandomFigure();
	static Type getRandomDuration();
	static int getRandomPitch();
	static bool getRandomDirection();
	static float getRandomValue();
};

#endif /* defined(__The_Algorithmic_Composer__Randomize__) */
