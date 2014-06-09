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

class Composer{
public:
	Composer();
	~Composer();
	virtual float compose() = 0;
private:
};

#endif /* defined(__The_Algorithmic_Composer__Composer__) */
