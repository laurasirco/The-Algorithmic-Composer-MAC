//
//  Scales.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 16/06/14.
//
//

#ifndef The_Algorithmic_Composer_Scales_h
#define The_Algorithmic_Composer_Scales_h

class Scales {
  
public:
	static const int Chromatic[];
	static const int Pentatonic[];
	
	static const int* getScale(int i){
		if(i == 0)
			return Chromatic;
		else
			return Pentatonic;
	}
};

const int Scales::Chromatic[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int Scales::Pentatonic[5] = {0, 2, 4, 7, 9};


#endif
