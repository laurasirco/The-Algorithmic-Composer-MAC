//
//  MusicVisualizer.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 15/07/14.
//
//

#include "MusicVisualizer.h"
#include "App.h"
#include "Note.h"


#define WIDTH 1024
#define HEIGHT 768

MusicVisualizer::MusicVisualizer(){
	
	claveSol.loadImage("GUI/Notes/ClaveSol.png");
	claveFa.loadImage("GUI/Notes/ClaveFa.png");
	
	
	ofImage image0;
	image0.loadImage("GUI/Notes/21.png");
	metricImages.push_back(image0);
	
	ofImage image1;
	image1.loadImage("GUI/Notes/31.png");
	metricImages.push_back(image1);
	
	ofImage image2;
	image2.loadImage("GUI/Notes/41.png");
	metricImages.push_back(image2);
	
	ofImage image3;
	image3.loadImage("GUI/Notes/22.png");
	metricImages.push_back(image3);
	
	ofImage image4;
	image4.loadImage("GUI/Notes/32.png");
	metricImages.push_back(image4);
	
	ofImage image5;
	image5.loadImage("GUI/Notes/42.png");
	metricImages.push_back(image5);
	
	ofImage image6;
	image6.loadImage("GUI/Notes/24.png");
	metricImages.push_back(image6);
	
	ofImage image7;
	image7.loadImage("GUI/Notes/34.png");
	metricImages.push_back(image7);
	
	ofImage image8;
	image8.loadImage("GUI/Notes/44.png");
	metricImages.push_back(image8);
	
	ofImage image9;
	image9.loadImage("GUI/Notes/28.png");
	metricImages.push_back(image9);
	
	ofImage image10;
	image10.loadImage("GUI/Notes/38.png");
	metricImages.push_back(image10);
	
	ofImage image11;
	image11.loadImage("GUI/Notes/48.png");
	metricImages.push_back(image11);
	
	ofImage image12;
	image12.loadImage("GUI/Notes/216.png");
	metricImages.push_back(image12);
	
	ofImage image13;
	image13.loadImage("GUI/Notes/316.png");
	metricImages.push_back(image13);
	
	ofImage image14;
	image14.loadImage("GUI/Notes/416.png");
	metricImages.push_back(image14);
	
	
	ofImage image15;
	image15.loadImage("GUI/Notes/dwhole.png");
	figureImages.push_back(image15);
	
	ofImage image16;
	image16.loadImage("GUI/Notes/whole.png");
	figureImages.push_back(image16);
	
	ofImage image17;
	image17.loadImage("GUI/Notes/ddhalf.png");
	figureImages.push_back(image17);
	
	ofImage image18;
	image18.loadImage("GUI/Notes/udhalf.png");
	figureImages.push_back(image18);
	
	ofImage image19;
	image19.loadImage("GUI/Notes/dhalf.png");
	figureImages.push_back(image19);
	
	ofImage image20;
	image20.loadImage("GUI/Notes/uhalf.png");
	figureImages.push_back(image20);
	
	ofImage image21;
	image21.loadImage("GUI/Notes/ddquarter.png");
	figureImages.push_back(image21);
	
	ofImage image22;
	image22.loadImage("GUI/Notes/udquarter.png");
	figureImages.push_back(image22);
	
	ofImage image23;
	image23.loadImage("GUI/Notes/dquarter.png");
	figureImages.push_back(image23);
	
	ofImage image24;
	image24.loadImage("GUI/Notes/uquarter.png");
	figureImages.push_back(image24);
	
	ofImage image25;
	image25.loadImage("GUI/Notes/ddeighth.png");
	figureImages.push_back(image25);
	
	ofImage image26;
	image26.loadImage("GUI/Notes/udeighth.png");
	figureImages.push_back(image26);
	
	ofImage image27;
	image27.loadImage("GUI/Notes/deighth.png");
	figureImages.push_back(image27);
	
	ofImage image28;
	image28.loadImage("GUI/Notes/ueighth.png");
	figureImages.push_back(image28);
	
	ofImage image29;
	image29.loadImage("GUI/Notes/ddsixteenth.png");
	figureImages.push_back(image29);
	
	ofImage image30;
	image30.loadImage("GUI/Notes/udsixteenth.png");
	figureImages.push_back(image30);
	
	ofImage image31;
	image31.loadImage("GUI/Notes/dsixteenth.png");
	figureImages.push_back(image31);
	
	ofImage image32;
	image32.loadImage("GUI/Notes/usixteenth.png");
	figureImages.push_back(image32);
	
	ofImage image33;
	image33.loadImage("GUI/Notes/ddthirtysecond.png");
	figureImages.push_back(image33);
	
	ofImage image34;
	image34.loadImage("GUI/Notes/udthirtysecond.png");
	figureImages.push_back(image34);
	
	ofImage image35;
	image35.loadImage("GUI/Notes/dthirtysecond.png");
	figureImages.push_back(image35);
	
	ofImage image36;
	image36.loadImage("GUI/Notes/uthirtysecond.png");
	figureImages.push_back(image36);
	
	ofImage image37;
	image37.loadImage("GUI/Notes/dsixtyfourth.png");
	figureImages.push_back(image37);
	
	ofImage image38;
	image38.loadImage("GUI/Notes/usixtyfourth.png");
	figureImages.push_back(image38);
	
	ofImage image39;
	image39.loadImage("GUI/Notes/sdwhole.png");
	figureImages.push_back(image39);
	
	ofImage image40;
	image40.loadImage("GUI/Notes/swhole.png");
	figureImages.push_back(image40);
	
	ofImage image41;
	image41.loadImage("GUI/Notes/sdhalf.png");
	figureImages.push_back(image41);
	
	ofImage image42;
	image42.loadImage("GUI/Notes/shalf.png");
	figureImages.push_back(image42);
	
	ofImage image43;
	image43.loadImage("GUI/Notes/sdquarter.png");
	figureImages.push_back(image43);
	
	ofImage image44;
	image44.loadImage("GUI/Notes/squarter.png");
	figureImages.push_back(image44);
	
	ofImage image45;
	image45.loadImage("GUI/Notes/sdeighth.png");
	figureImages.push_back(image45);
	
	ofImage image46;
	image46.loadImage("GUI/Notes/seighth.png");
	figureImages.push_back(image46);
	
	ofImage image47;
	image47.loadImage("GUI/Notes/sdsixteenth.png");
	figureImages.push_back(image47);
	
	ofImage image48;
	image48.loadImage("GUI/Notes/ssixteenth.png");
	figureImages.push_back(image48);
	
	ofImage image49;
	image49.loadImage("GUI/Notes/sdthirtysecond.png");
	figureImages.push_back(image49);
	
	ofImage image50;
	image50.loadImage("GUI/Notes/sthirtysecond.png");
	figureImages.push_back(image50);
	
	ofImage image51;
	image51.loadImage("GUI/Notes/ssixtyfourth.png");
	figureImages.push_back(image51);
	
	
	figures.clear();
	positions.clear();
	appeared.clear();
}

MusicVisualizer::~MusicVisualizer(){
	
}


void MusicVisualizer::stop(){
	
	
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
	
	
	metricImages[IM21].draw(50, HEIGHT - 165, metricImages[IM21].getWidth() * 0.2, metricImages[IM21].getHeight() * 0.2);
	
	
	for (int i = 0; i < figures.size(); i++) {
		
		if(appeared[i]){
			positions[i] -= velocity;
			
			ofColor color = App::getUIColor();
			
			float opacity0 = map(positions[i], 40, 80, 0, 255); //final fade
			float opacity1 = map(positions[i], WIDTH - 340, (WIDTH - 340) - (figureImages[images[i]].getWidth() * 0.2), 0, 255); //initial fade
			
			if (opacity0 == 255 && opacity1 == 255)
				ofSetColor(color.r, color.g, color.b, 255);
			else if (opacity1 < 255)
				ofSetColor(color.r, color.g, color.b, opacity1);
			else if (opacity0 < 255)
				ofSetColor(color.r, color.g, color.b, opacity0);
			
			figureImages[images[i]].draw(positions[i], HEIGHT - 180, figureImages[images[i]].getWidth() * 0.2, figureImages[images[i]].getHeight() * 0.2);
		}
		
	}
	
}

void MusicVisualizer::drawFigures(vector<Figure *> f){
	
	paused = false;
	figures = f;
	allPlayed = false;
	playing = true;
	
	//Add initial positions for each figure
	for(int i = 0; i < f.size(); i++){
		positions.push_back(WIDTH - 340);
		appeared.push_back(false);
	}
	
	
	currentFigure = 0;
	appeared[0] = true;
	images.push_back(getImageNoteOfFigure(figures[0]));
	
	cout << velocity << endl;
	
}


void MusicVisualizer::update(){
	
	if(figures.size() > 0 && !paused && playing){
		if (positions[currentFigure] <= (WIDTH - 340) - (figureImages[INDWhole].getWidth() * 0.2) - 10 && currentFigure < figures.size() - 1) {
			
			currentFigure++;
			
			//get duration of the next figure
			appeared[currentFigure] = true;
			images.push_back(getImageNoteOfFigure(figures[currentFigure]));
			
			cout << velocity << endl;
		}
		
		float duration = Figure::typeToDuration(figures[currentFigure]->getType());
		float FPS = App::getFramerate();
		float BPM = App::getTempo();
		float framesQuarter = (60.0/(float)BPM)/(1.0/(float)FPS);
		
		//calcule global velocity as current figure velocity
		velocity = (float)(figureImages[images[currentFigure]].getWidth() * 0.2) / (float)(framesQuarter * getFactorOfType(figures[currentFigure]->getType()));
		
		if (currentFigure == figures.size() - 1) {
			allPlayed = true;
			playing = false;
		}
		
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


INote MusicVisualizer::getImageNoteOfFigure(Figure * f){
	
	INote note;
	
	if (f->getKind() == KNote) { // NOTE
		
		Note * n = dynamic_cast<Note *>(f);
		
		if((n->getPitch() >= 36 && n->getPitch() <= 48) || (n->getPitch() >= 60 && n->getPitch() <= 69)){
			if (f->getType() == DWhole) {
				note = INDWhole;
			}
			else if (f->getType() == Whole){
				note = INWhole;
			}
			else if (f->getType() == DHalf){
				note = INUDHalf;
			}
			else if (f->getType() == Half){
				note = INUHalf;
			}
			else if (f->getType() == DQuarter) {
				note = INUDQuarter;
			}
			else if (f->getType() == Quarter ) {
				note = INUQuarter;
			}
			else if (f->getType() == DEighth){
				note = INUDEighth;
			}
			else if (f->getType() == Eighth){
				note = INUEighth;
			}
			else if (f->getType() == DSixteenth){
				note = INUDSixteenth;
			}
			else if (f->getType() == Sixteenth){
				note = INUSixteenth;
			}
			else if (f->getType() == DThirtySecond){
				note = INUDThirtySecond;
			}
			else if (f->getType() == ThirtySecond){
				note = INUThirtySecond;
			}
			else if (f->getType() == SixtyFourth){
				note = INUSixtyFourth;
			}
			
		}
		else{
			
			if (f->getType() == DWhole) {
				note = INDWhole;
			}
			else if (f->getType() == Whole){
				note = INWhole;
			}
			else if (f->getType() == DHalf){
				note = INDDHalf;
			}
			else if (f->getType() == Half){
				note = INDHalf;
			}
			else if (f->getType() == DQuarter) {
				note = INDDQuarter;
			}
			else if (f->getType() == Quarter ) {
				note = INDQuarter;
			}
			else if (f->getType() == DEighth){
				note = INDDEighth;
			}
			else if (f->getType() == Eighth){
				note = INDEighth;
			}
			else if (f->getType() == DSixteenth){
				note = INDDSixteenth;
			}
			else if (f->getType() == Sixteenth){
				note = INDSixteenth;
			}
			else if (f->getType() == DThirtySecond){
				note = INDDThirtySecond;
			}
			else if (f->getType() == ThirtySecond){
				note = INDThirtySecond;
			}
			else if (f->getType() == SixtyFourth){
				note = INDSixtyFourth;
			}
			
		}
		
	}
	else{ // SILENCE
		if (f->getType() == DWhole) {
			note = ISDWhole;
		}
		else if (f->getType() == Whole){
			note = ISWhole;
		}
		else if (f->getType() == DHalf){
			note = ISDHalf;
		}
		else if (f->getType() == Half){
			note = ISHalf;
		}
		else if (f->getType() == DQuarter) {
			note = ISDQuarter;
		}
		else if (f->getType() == Quarter ) {
			note = ISQuarter;
		}
		else if (f->getType() == DEighth){
			note = ISDEighth;
		}
		else if (f->getType() == Eighth){
			note = ISEighth;
		}
		else if (f->getType() == DSixteenth){
			note = ISDSixteenth;
		}
		else if (f->getType() == Sixteenth){
			note = ISSixteenth;
		}
		else if (f->getType() == DThirtySecond){
			note = ISDThirtySecond;
		}
		else if (f->getType() == ThirtySecond){
			note = ISThirtySecond;
		}
		else if (f->getType() == SixtyFourth){
			note = ISSixtyFourth;
		}
	}
	
	return note;
	
}