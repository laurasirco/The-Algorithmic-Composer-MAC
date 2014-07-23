//
//  MotivicDevelopmentComposer.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 21/07/14.
//
//

#include "MotivicDevelopmentComposer.h"
#include "Note.h"


MotivicDevelopmentComposer::MotivicDevelopmentComposer(){
	
    InvertMethod * m1 = new InvertMethod();
    TransposeMethod * m2 = new TransposeMethod(1);
    RetrogradeMethod * m3 = new RetrogradeMethod();
    
    sequence.push_back(m1);
    sequence.push_back(m2);
    sequence.push_back(m3);
    
    Note * n1 = new Note(Eighth, 60, 50);
    Note * n2 = new Note(Eighth, 64, 50);
    Note * n3 = new Note(Eighth, 67, 50);
    Note * n4 = new Note(Eighth, 72, 50);
    
    motive.push_back(n1);
    motive.push_back(n2);
    motive.push_back(n3);
    motive.push_back(n4);
}

MotivicDevelopmentComposer::~MotivicDevelopmentComposer(){
	
}

vector<Figure *> MotivicDevelopmentComposer::compose(bool infinite){
	
    cout << "Compose" << endl;
    std::vector<Figure *> fragment;
    fragment.insert(fragment.end(), motive.begin(), motive.end());
    
    for (int i = 0; i < sequence.size(); i++) {
        vector<Figure *> transformation = sequence[i]->performTransformation(motive);
        fragment.insert(fragment.end(), transformation.begin(), transformation.end());
    }
    
    return fragment;
}




