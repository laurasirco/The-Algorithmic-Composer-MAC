//
//  MotivicDevelopmentMethods.h
//  the_algorithmic_composer
//
//  Created by Raúl Ibarra Díez on 22/07/14.
//
//

#ifndef __the_algorithmic_composer__MotivicDevelopmentMethods__
#define __the_algorithmic_composer__MotivicDevelopmentMethods__

#include <iostream>
#include <vector>
#include "Figure.h"
using namespace std;

class Method {
protected:
    int findPreviousPitchFrom(int position, vector<Figure *> v);
public:
    Method();
    ~Method();
    virtual vector<Figure *> performTransformation(vector<Figure *> motive) = 0;
};


class TransposeMethod : public Method {
    
public:
    TransposeMethod(int s);
    ~TransposeMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
private:
    int steps;
};


class RegisterDisplacement : public Method {
    
public:
    RegisterDisplacement(vector<int> r);
    ~RegisterDisplacement();
    vector<Figure *> performTransformation(vector<Figure *> motive);
private:
    vector<int> regSteps;
};


class InvertMethod : public Method {
    
public:
    InvertMethod();
    ~InvertMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
};

class RetrogradeMethod : public Method {
    
public:
    RetrogradeMethod();
    ~RetrogradeMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
};

class ExpandMethod : public Method {
    
public:
    ExpandMethod(int s);
    ~ExpandMethod();
    vector<Figure *> performTransformation(vector<Figure *> motive);
private:
    int steps;
};


class RepetitionMethod : public Method {
	
public:
	RepetitionMethod();
	~RepetitionMethod();
	vector<Figure *> performTransformation(vector<Figure *> motive);
};


class RhythmExpand : public Method {
	
public:
	RhythmExpand(int f);
	~RhythmExpand();
	vector<Figure *> performTransformation(vector<Figure *> motive);
private:
	int factor;
};

#endif /* defined(__the_algorithmic_composer__MotivicDevelopmentMethods__) */
