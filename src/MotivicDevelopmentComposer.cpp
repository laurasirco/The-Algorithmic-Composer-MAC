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
	
	//TEST MOTIVE
    Note * n1 = new Note(Eighth, 60, 50);
    Note * n2 = new Note(Eighth, 64, 50);
    Note * n3 = new Note(Eighth, 68, 50);
    Note * n4 = new Note(Eighth, 69, 50);
	Note * n5 = new Note(Eighth, 66, 50);
    
    motive.push_back(n1);
    motive.push_back(n2);
    motive.push_back(n3);
    motive.push_back(n4);
	motive.push_back(n5);
	
	type = MotivicDevelopment;
}

MotivicDevelopmentComposer::~MotivicDevelopmentComposer(){
	
}

vector<Figure *> MotivicDevelopmentComposer::compose(bool infinite){
	
    cout << "Compose with " << sequence.size() << " methods: "<< endl;
    std::vector<Figure *> fragment;
    fragment.insert(fragment.end(), motive.begin(), motive.end());
    
    for (int i = 0; i < sequence.size(); i++) {
		cout << "Method " << i << ": ";
        vector<Figure *> transformation = sequence[i]->performTransformation(motive);
        fragment.insert(fragment.end(), transformation.begin(), transformation.end());
		cout << endl;
    }
    
	//sequence.clear();
    return fragment;
}




