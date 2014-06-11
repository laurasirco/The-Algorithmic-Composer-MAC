#include "App.h"
#include "IndependentStochasticComposer.h"
#include "UniformDistribution.h"
#include "LinearDistribution.h"
#include "TriangularDistribution.h"
#include "ExponentialDistribution.h"
#include "GaussianDistribution.h"
#include "CauchyDistribution.h"
#include "Figure.h"

//--------------------------------------------------------------
void App::setup(){
    
    
    ofBackground(ofxUIColor::crimson);

    
    guiTabBar = new ofxUITabBar();
    
    //SETTING GUI
    guiTabBar->setFont("GUI/Lekton-Regular.ttf");
    guiTabBar->setFontSize(OFX_UI_FONT_LARGE, 16);
    guiTabBar->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    guiTabBar->setFontSize(OFX_UI_FONT_SMALL, 8);
    guiTabBar->setName("Metodo");
    guiTabBar->addLabel("Metodo");
    guiTabBar->addSpacer();
    guiTabBar->autoSizeToFitWidgets();
    guiTabBar->setPadding(10.0);
    guiTabBar->setPosition(10,10);
    ofxUIColor color = ofxUIColor();
    color.set(0,0,0,60);
    guiTabBar->setColorBack(color);
    
    
    ofxUITabBar* gui1 = new ofxUITabBar();
    gui1->setFont("GUI/Lekton-Regular.ttf");
    gui1->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui1->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui1->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui1->setName("Estocastico");
    gui1->addLabel("Metodo (II)");
    gui1->addSpacer();
    gui1->autoSizeToFitWidgets();
    ofAddListener(gui1->newGUIEvent,this,&App::guiEvent);
    guiTabBar->addCanvas(gui1);
    guis.push_back(gui1);
    
    ofxUITabBar* gui11 = new ofxUITabBar();
    gui11->setFont("GUI/Lekton-Regular.ttf");
    gui11->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui11->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui11->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui11->setName("Sucesos independientes");
    gui11->addLabel("Opciones");
    gui11->addSpacer();
    gui11->autoSizeToFitWidgets();
    ofAddListener(gui11->newGUIEvent,this,&App::guiEvent);
    gui1->addCanvas(gui11);
    
    ofxUITabBar* gui12 = new ofxUITabBar();
    gui12->setFont("GUI/Lekton-Regular.ttf");
    gui12->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui12->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui12->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui12->setName("Sucesos dependientes");
    gui12->addLabel("Metodo (III)");
    gui12->addSpacer();
    gui12->autoSizeToFitWidgets();
    ofAddListener(gui12->newGUIEvent,this,&App::guiEvent);
    gui1->addCanvas(gui12);
    

    ofxUICanvas* gui2 = new ofxUICanvas();
    gui2->setFont("GUI/Lekton-Regular.ttf");
    gui2->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui2->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui2->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui2->setName("Determinista");
    gui2->addLabel("Metodo (II)");
    gui2->addSpacer();
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent,this,&App::guiEvent);
    guiTabBar->addCanvas(gui2);
    guis.push_back(gui2);

    ofxUICanvas* gui3 = new ofxUICanvas();
    gui3->setFont("GUI/Lekton-Regular.ttf");
    gui3->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui3->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui3->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui3->setName("Gramatical");
    gui3->addLabel("Metodo (II)");
    gui3->addSpacer();
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent,this,&App::guiEvent);
    guiTabBar->addCanvas(gui3);
    guis.push_back(gui3);
    
    ofxUICanvas* gui4 = new ofxUICanvas();
    gui4->setFont("GUI/Lekton-Regular.ttf");
    gui4->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui4->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui4->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui4->setName("Evolutivo");
    gui4->addLabel("Metodo (II)");
    gui4->addSpacer();
    gui4->autoSizeToFitWidgets();
    ofAddListener(gui4->newGUIEvent,this,&App::guiEvent);
    guiTabBar->addCanvas(gui4);
    guis.push_back(gui4);
    
    /*ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    // create a new oscillator which we'll use for the actual audio signal
    SineWave tone = SineWave();
    
    // create a sine wave we'll use for some vibrato
    SineWave vibratoOsc = SineWave();
    vibratoOsc.freq(10);
    
    // you can use the regular arithmatic operators on Generators and their subclasses (SineWave extends Generator)
    float basePitch = 400;
    Generator frequency = basePitch + (vibratoOsc * basePitch * 0.01);
    
    // plug that frequency generator into the frequency slot of the main audio-producing sine wave
    tone.freq(frequency);
    
    // let's also create a tremelo effect
    SineWave tremeloSine = SineWave().freq(1);
    
    // set the synth's final output generator
    synth.setOutputGen( tone * tremeloSine );*/
	
	UniformDistribution * uniform = new UniformDistribution();
	
	LinearDistribution * linear = new LinearDistribution();
	linear->setDirection(Up);
	
	TriangularDistribution * triangular = new TriangularDistribution();
	triangular->setMean(0.9);
	
	ExponentialDistribution * exponential = new ExponentialDistribution();
	exponential->setLambda(1.0);
	
	GaussianDistribution * gauss = new GaussianDistribution();
	//gauss->setMu(10);
	
	CauchyDistribution * cauchy = new CauchyDistribution();
	cauchy->setAlpha(10);
	
	
	composer = new IndependentStochasticComposer(triangular);
	
	ofSetFrameRate(30);
}

//--------------------------------------------------------------
void App::update(){
	//cout<<"FPS: "<<ofGetFrameRate()<<endl;
	cout<<"----------------------------------"<<endl;
	std::vector<Figure *> result = composer->compose(false, 2, 4, 1);
	float sum = 0.0;
	for(int i = 0; i < result.size(); i++){
		result[i]->printMyself();
		sum += result[i]->getDuration();
	}
	cout<<"TOTAL duration: "<<sum<<endl;
}

//--------------------------------------------------------------
void App::draw(){

}

//--------------------------------------------------------------
void App::keyPressed(int key){

}

//--------------------------------------------------------------
void App::keyReleased(int key){

}

//--------------------------------------------------------------
void App::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void App::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void App::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void App::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void App::windowResized(int w, int h){

}

//--------------------------------------------------------------
void App::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void App::dragEvent(ofDragInfo dragInfo){

}

void App::audioRequested (float * output, int bufferSize, int nChannels){
    //synth.fillBufferOfFloats(output, bufferSize, nChannels);
}


void App::exit(){
    
}

void App::guiEvent(ofxUIEventArgs &e){
    
}
