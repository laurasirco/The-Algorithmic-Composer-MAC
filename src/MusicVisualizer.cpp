//
//  MusicVisualizer.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 15/07/14.
//
//

#include "MusicVisualizer.h"
#include "App.h"


#define WIDTH 1024
#define HEIGHT 768

MusicVisualizer::MusicVisualizer(){
	
	claveSol.loadImage("GUI/Notes/ClaveSol.png");
	claveFa.loadImage("GUI/Notes/ClaveFa.png");
	metric.loadImage("GUI/Notes/42.png");
	dWhole.loadImage("GUI/Notes/whole.png");
	
	frameCount = 0;
	figures.clear();
	positions.clear();
	appeared.clear();
}

MusicVisualizer::~MusicVisualizer(){
	
}

void MusicVisualizer::draw(){
	
	ofLine(20, HEIGHT - 160, WIDTH - 320, HEIGHT - 160);
	ofLine(20, HEIGHT - 150, WIDTH - 320, HEIGHT - 150);
	ofLine(20, HEIGHT - 140, WIDTH - 320, HEIGHT - 140);
	ofLine(20, HEIGHT - 130, WIDTH - 320, HEIGHT - 130);
	ofLine(20, HEIGHT - 120, WIDTH - 320, HEIGHT - 120);
	
	ofLine(20, HEIGHT - 80, WIDTH - 320, HEIGHT - 80);
	ofLine(20, HEIGHT - 70, WIDTH - 320, HEIGHT - 70);
	ofLine(20, HEIGHT - 60, WIDTH - 320, HEIGHT - 60);
	ofLine(20, HEIGHT - 50, WIDTH - 320, HEIGHT - 50);
	ofLine(20, HEIGHT - 40, WIDTH - 320, HEIGHT - 40);
	
	claveSol.draw(20, HEIGHT - 170, claveSol.getWidth() * 0.2, claveSol.getHeight() * 0.2);
	claveFa.draw(20, HEIGHT - 80, claveFa.getWidth() * 0.2, claveFa.getHeight() * 0.2);
	metric.draw(50, HEIGHT - 165, metric.getWidth() * 0.2, metric.getHeight() * 0.2);
	
	
	for (int i = 0; i < figures.size(); i++) {
		
		if(appeared[i])
			positions[i] -= velocity;
		
		ofColor color = App::getUIColor();
		
		float opacity0 = map(positions[i], 40, 80, 0, 255);
		float opacity1 = map(positions[i], WIDTH - 340, (WIDTH - 340) - (dWhole.getWidth() * 0.2), 0, 255);
		
		ofSetColor(color.r, color.g, color.b, opacity1);
		dWhole.draw(positions[i], HEIGHT - 180, dWhole.getWidth() * 0.2, dWhole.getHeight() * 0.2);
		
	}
	
}

void MusicVisualizer::drawFigures(vector<Figure *> f){
	
	figures = f;
	
	//Add initial positions for each figure
	for(int i = 0; i < f.size(); i++){
		positions.push_back(WIDTH - 340);
		appeared.push_back(false);
	}
	
	
	currentFigure = 0;
	appeared[0] = true;
	
	cout << velocity << endl;
	
}


void MusicVisualizer::update(){
	
	if(figures.size() > 0){
		if (positions[currentFigure] <= (WIDTH - 340) - (dWhole.getWidth() * 0.2) - 10 && currentFigure < figures.size() - 1) {
			
			currentFigure++;
			
			//get duration of the next figure
			appeared[currentFigure] = true;
			
			cout << velocity << endl;
		}
		
		float duration = Figure::typeToDuration(figures[currentFigure]->getType());
		float FPS = App::getFramerate();
		float BPM = App::getTempo();
		float framesQuarter = (60.0/(float)BPM)/(1.0/(float)FPS);
		
		
		//calcule global velocity as current figure velocity
		velocity = (float)(dWhole.getWidth() * 0.2) / (float)(framesQuarter * getFactorOfType(figures[currentFigure]->getType()));
		
	}
}


float MusicVisualizer::map(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float MusicVisualizer::getFactorOfType(Type t){
	
	float division;
	
	if (t == DWhole) {
		division = 6.0;
	}
	else if (t == Whole){
		division = 4.0;
	}
	else if (t == DHalf){
		division = 3.0;
	}
	else if (t == Half){
		division = 2.0;
	}
	else if (t == DQuarter) {
		division = 1.5;
	}
	else if (t == Quarter ) {
		division = 1.0;
	}
	else if (t == DEighth){
		division = 0.75;
	}
	else if (t == Eighth){
		division = 0.5;
	}
	else if (t == DSixteenth){
		division = 0.25 + 0.25/2;
	}
	else if (t == Sixteenth){
		division = 0.25;
	}
	else if (t == DThirtySecond){
		division = 0.125 + 0.125/2;
	}
	else if (t == ThirtySecond){
		division = 0.125;
	}
	else if (t == SixtyFourth){
		division = 0.125/2;
	}
	
	return division;
}