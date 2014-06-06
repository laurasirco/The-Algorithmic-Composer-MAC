//
//  Note.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 05/06/14.
//
//

#ifndef __The_Algorithmic_Composer__Note__
#define __The_Algorithmic_Composer__Note__

#include <iostream>
#include "Figure.h"

class Note : public Figure{
public:
    Note();
    ~Note();
private:
    int pitch;
    int velocity;
};

#endif /* defined(__The_Algorithmic_Composer__Note__) */
