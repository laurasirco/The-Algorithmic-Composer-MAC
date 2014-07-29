//
//  SerialismMethods.h
//  the_algorithmic_composer
//
//  Created by Laura Sirvent Collado on 26/07/14.
//
//

#ifndef __the_algorithmic_composer__SerialismMethods__
#define __the_algorithmic_composer__SerialismMethods__

#include <iostream>
#include <vector>
#include "Figure.h"
using namespace std;

enum SeriesType{
	TPitch, TRhythm, TDynamic, TPitchAndRhythm
};

class SMethod {
	
public:
	SMethod(SeriesType t);
    ~SMethod();
    virtual vector<Figure *> performTransformation(vector<Figure *> motive) = 0;
protected:
	SeriesType type;
};



class RetrogradeSMethod : public SMethod{
	
public:
	RetrogradeSMethod(SeriesType t);
    ~RetrogradeSMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
};



class InvertSMethod : public SMethod{
	
public:
	InvertSMethod(SeriesType t);
    ~InvertSMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
};



class RetrogradeInversionSMethod : public SMethod{
	
public:
	RetrogradeInversionSMethod(SeriesType t);
    ~RetrogradeInversionSMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
};



class TransposeSMethod : public SMethod{
	
public:
	TransposeSMethod(SeriesType t, int s);
    ~TransposeSMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
private:
	int steps;
};



class RepetitionSMethod : public SMethod{
	
public:
	RepetitionSMethod(SeriesType t);
    ~RepetitionSMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
};




#endif /* defined(__the_algorithmic_composer__SerialismMethods__) */
