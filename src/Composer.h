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

class Composer{
public:
	Composer();
	~Composer();
	virtual std::vector<Figure *> compose(bool infinite, int meter, int pattern, int stems = 2) = 0;
private:
};

#endif /* defined(__The_Algorithmic_Composer__Composer__) */
