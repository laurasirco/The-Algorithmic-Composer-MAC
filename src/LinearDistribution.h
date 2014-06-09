//
//  LinearDistribution.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#ifndef __The_Algorithmic_Composer__LinearDistribution__
#define __The_Algorithmic_Composer__LinearDistribution__

#include <iostream>
#include "Distribution.h"

enum Direction{
	Up, Down
};

class LinearDistribution : public Distribution{

public:
	LinearDistribution();
	~LinearDistribution();
	float getValue();
	void setDirection(Direction d){ direction = d; }
private:
	Direction direction;
};


#endif /* defined(__The_Algorithmic_Composer__LinearDistribution__) */
