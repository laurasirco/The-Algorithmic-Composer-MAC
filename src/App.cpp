#include "App.h"
#include "IndependentStochasticComposer.h"
#include "Figure.h"
#include "Scales.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;

//--------------------------------------------------------------
ofxTonicSynth App::synth = ofxTonicSynth();
ofxUITextArea * App::currentFigureLabel = NULL;
ofxUIScrollableCanvas * App::resultsGui = NULL;

void App::setup(){
    
	initGUI();
	initSynth();
    
	uniform = new UniformDistribution();
	
	linear = new LinearDistribution();
	linear->setDirection(Down);
	
	triangular = new TriangularDistribution();
	//triangular->setMean(0.9);
	triangular->setTriangleBase(1.0);
	
	exponential = new ExponentialDistribution();
	//exponential->setLambda(1.0);
	
	gauss = new GaussianDistribution();
	gauss->setMu(0.5);
	gauss->setSpread(10);
	
	cauchy = new CauchyDistribution();
	cauchy->setAlpha(10);
	
	beta = new BetaDistribution();
	beta->setB(1);
	beta->setA(50);
	
	weibull = new WeibullDistribution();
	weibull->setT(0.5);
	weibull->setS(0.1);
	
	poisson = new PoissonDistribution();
	
	composer = new IndependentStochasticComposer(uniform);
	//std::vector<Figure *> result = composer->compose(false, 2, 4, 10);
	
	player = new Player(60);
	
	//player->play(result);
	

}

//--------------------------------------------------------------
void App::update(){

	if(!player->isAllPlayed())
		player->update();
	else
		synth.setParameter("volume", 0);
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
	synth.fillBufferOfFloats(output, bufferSize, nChannels);
}

void App::exit(){
    
}

void App::guiEvent(ofxUIEventArgs &e){
	
	string name = e.getName();
	int kind = e.getKind();
	IndependentStochasticComposer * c = dynamic_cast<IndependentStochasticComposer *>(composer);
	
	
	if(name == "Uniform"){
		c->setDistribution(uniform);
		mg->setBuffer(uniform->getValuesForGraphic(1000));
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
	}
	
	
	else if(name == "Linear"){
		c->setDistribution(linear);
		mg->setBuffer(linear->getValuesForGraphic(1000));
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(true);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);

	}
	else if(name == "Up"){
		linear->setDirection(Up);
		mg->setBuffer(linear->getValuesForGraphic(1000));
	}
	else if(name == "Down"){
		linear->setDirection(Down);
		mg->setBuffer(linear->getValuesForGraphic(1000));
	}
	
	
	else if(name == "Triangular"){
		c->setDistribution(triangular);
		mg->setBuffer(triangular->getValuesForGraphic(1000));
		triangularDistGUI->setVisible(true);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
	}
	else if(name == "Triangle Base"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		triangular->setTriangleBase(slider->getValue());
		mg->setBuffer(triangular->getValuesForGraphic(1000));
	}
	
	
	
	else if(name == "Exponential"){
		c->setDistribution(exponential);
		mg->setBuffer(exponential->getValuesForGraphic(1000));
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(true);
		gaussDistGUI->setVisible(false);
	}
	else if (name == "Lambda"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		exponential->setLambda(slider->getValue());
		mg->setBuffer(exponential->getValuesForGraphic(1000));
	}
	
	
	else if(name == "Gauss"){
		c->setDistribution(gauss);
		mg->setBuffer(gauss->getValuesForGraphic(1000));
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(true);
	}
	else if (name == "Sigma"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		gauss->setSigma(slider->getValue());
		mg->setBuffer(gauss->getValuesForGraphic(1000));
	}
	else if (name == "Mu"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		gauss->setMu(slider->getValue());
		mg->setBuffer(gauss->getValuesForGraphic(1000));
	}
	
	
	else if(name == "Cauchy"){
		c->setDistribution(cauchy);
		mg->setBuffer(cauchy->getValuesForGraphic(1000));
	}
	else if(name == "Beta"){
		c->setDistribution(beta);
	}
	else if(name == "Weibull"){
		c->setDistribution(weibull);
		mg->setBuffer(weibull->getValuesForGraphic(1000));
	}
	else if(name == "Poisson"){
		c->setDistribution(poisson);
		mg->setBuffer(poisson->getValuesForGraphic(1000));
	}
	
	else if(name == "COMPOSE"){
		composition.clear();
		composition = c->compose(false, 2, 4);
		resultsGui->removeWidgets();
	}
	else if(name == "PLAY" && composition.size() > 0){
		player->play(composition);
	}
	
	else if(name == "TEMPO"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		player->setTempo((int)slider->getValue());
	}
	
	else if(name == "theme"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();

		gui1->setTheme((int)slider->getValue());
		gui2->setTheme((int)slider->getValue());
		generalGUI->setTheme((int)slider->getValue());
	}
	
	else if(name == "Octaves"){
		ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget;
		c->setOctaves((int)slider->getValueLow(), (int)slider->getValueHigh());
	}
	
	else if(name == "Stems"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		c->setStems((int)slider->getValue());
	}
	
	//SCALE FINDER
	
	else{
		
		bool found = false;
		int count = 0;
		while(!found && count < 38){
			if (name == NamesOfScales[count]) {
				found = true;
			}
			else count++;
		}
		
		cout<<count<<endl;
	}

}

void App::setMidiNote(int note){
	synth.setParameter("midiNumber", note);
}

void App::setIsSilence(bool t){
	if(t == false)
		synth.setParameter("volume", 1);
	else
		synth.setParameter("volume", 0);
}

void App::setVolume(float volume){
	//synth.setParameter("volume", volume);
}

void App::setCurrentFigure(Figure *f){
		
	
	resultsGui->addTextArea("text", "\n", OFX_UI_FONT_SMALL);
	resultsGui->addTextArea("text", f->getDescription(), OFX_UI_FONT_SMALL);
	
	
}

void App::initSynth(){
	
	//SYNTH SETTINGS
	
	ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
	
	ControlGenerator midiNote = synth.addParameter("midiNumber");
	
	ControlGenerator volume = synth.addParameter("volume");
	synth.setParameter("volume", 1);
	
	ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
	
	// create a new oscillator which we'll use for the actual audio signal
	SineWave tone = SineWave();
	// create a sine wave we'll use for some vibrato
	SineWave vibratoOsc = SineWave();
	vibratoOsc.freq(10);
	
	// you can use the regular arithmatic operators on Generators and their subclasses (SineWave extends Generator)
	Generator frequency = noteFreq + (vibratoOsc * noteFreq * 0.01);
	
	// plug that frequency generator into the frequency slot of the main audio-producing sine wave
	tone.freq(noteFreq);
	
	// Partials
	SineWave firstPartial = SineWave().freq(noteFreq * 2);
	SineWave secondPartial = SineWave().freq(noteFreq * 3);
	
	// set the synth's final output generator
	synth.setOutputGen( (tone + firstPartial + secondPartial) * ADSR(0.3f, 0.0f, 0.1f, 0.6f).trigger(volume).legato(1));
}

void App::initGUI(){
	
	
    ofBackground(ofxUIColor::lightSlateGray);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofEnableSmoothing();

	ofSetColor(0,0,0);
	
	
	generalGUI = new ofxUICanvas();
	generalGUI->setFont("GUI/Lekton-Regular.ttf");
	
	generalGUI->setPosition(980, 0);
	generalGUI->setWidth(300);
	generalGUI->setHeight(120);
	
	generalGUI->addLabelButton("COMPOSE", false);
	generalGUI->addLabelButton("PLAY", false);
	generalGUI->addSlider("TEMPO", 1, 200, 60);
	generalGUI->addSpacer(300, 10);
	generalGUI->addLabel("RESULTS", OFX_UI_FONT_LARGE);
	generalGUI->addSpacer();
	ofAddListener(generalGUI->newGUIEvent, this, &App::guiEvent);
	
	
	/////////////
	
	
	gui1 = new ofxUICanvas();
	gui1->setFont("GUI/Lekton-Regular.ttf");
	gui1->setHeight(360);
	gui1->setWidth(300);
	gui1->setPosition(0, 0);
	
	
	gui1->addLabel("STOCHASTIC COMPOSER", OFX_UI_FONT_LARGE);
	gui1->addSpacer();
	
	gui1->addSlider("theme", 0, 42, 1);
	gui1->addSpacer();
	
	gui1->addLabel("DISTRIBUTION");
	
	vector<string> distributions;
	distributions.push_back("Uniform");
	distributions.push_back("Linear");
	distributions.push_back("Triangular");
	distributions.push_back("Exponential");
	distributions.push_back("Gaussian");
	distributions.push_back("Cauchy");
	distributions.push_back("Beta");
	distributions.push_back("Weibull");
	distributions.push_back("Poisson");
	
	gui1->addRadio("Distribution", distributions);
		
	gui1->addSpacer();
	
	gui1->addLabel("MUSICAL PARAMETERS");
	gui1->addRangeSlider("Octaves", 0, 10, 2, 4);
	gui1->addSlider("Stems", 1, 20, 1);
	ofAddListener(gui1->newGUIEvent, this, &App::guiEvent);

	
	//////////////////
	
	
	gui2 = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	
	gui2->setScrollAreaToScreen();
    gui2->setScrollableDirections(false, true);
	gui2->setFont("GUI/Lekton-Regular.ttf");
	gui2->addLabel("SCALE", OFX_UI_FONT_MEDIUM);
	gui2->setPosition(0, 360);
	
	
	vector<string> scales(NamesOfScales, NamesOfScales + sizeof(NamesOfScales) / sizeof(string));
	scaleRadioButtons = gui2->addRadio("Scale", scales);
	
	gui2->autoSizeToFitWidgets();
	gui2->setWidth(300);
	gui2->getRect()->setWidth(ofGetWidth());
	ofAddListener(gui2->newGUIEvent, this, &App::guiEvent);

	
	///////////////
	
	
	string textString = "1. Select distribution \n\n3. Select Scale \n\n2. Press COMPOSE \n\n3. Press PLAY";
		
	resultsGui = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	resultsGui->setFont("GUI/Lekton-Regular.ttf");
	resultsGui->setScrollAreaToScreen();
    resultsGui->setScrollableDirections(false, true);
	
	resultsGui->setPosition(980, 120);
	resultsGui->setHeight(640);
	resultsGui->setWidth(300);
	ofAddListener(resultsGui->newGUIEvent, this, &App::guiEvent);
	//currentFigureLabel = resultsGui->addTextArea("textarea", textString, OFX_UI_FONT_MEDIUM);
	
		
	/////////////
	
	vector<float> distribution;
	for (int i = 0; i < 10; i++) {
		distribution.push_back(0.0);
	}
	distributionGUI = new ofxUICanvas();
	distributionGUI->setFont("GUI/Lekton-Regular.ttf");
	distributionGUI->setPosition(300, 0);
	distributionGUI->addLabel("DISTRIBUTION", OFX_UI_FONT_LARGE);
	distributionGUI->addLabel("Based on 1000 samples", OFX_UI_FONT_SMALL);
	mg = distributionGUI->addMovingGraph("distribution", distribution, 10, 0.0, 25.0, 50);
	distributionGUI->addSpacer();
	distributionGUI->autoSizeToFitWidgets();
	//distributionGUI->setVisible(false);
	
	linearDistGUI = new ofxUICanvas();
	linearDistGUI->setFont("GUI/Lekton-Regular.ttf");
	linearDistGUI->setPosition(300, 113);
	linearDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	
	vector<string> op1;
	op1.push_back("Up");
	op1.push_back("Down");
	linearDistGUI->addRadio("Direction", op1);
	
	linearDistGUI->autoSizeToFitWidgets();
	linearDistGUI->setWidth(211);
	linearDistGUI->setVisible(false);
	ofAddListener(linearDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	triangularDistGUI = new ofxUICanvas();
	triangularDistGUI->setFont("GUI/Lekton-Regular.ttf");
	triangularDistGUI->setPosition(300, 113);
	triangularDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	triangularDistGUI->addSlider("Triangle Base", 0.01, 1.0, 1.0);
	triangularDistGUI->autoSizeToFitWidgets();
	triangularDistGUI->setWidth(211);
	triangularDistGUI->setVisible(false);
	ofAddListener(triangularDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	
	exponentialDistGUI = new ofxUICanvas();
	exponentialDistGUI->setFont("GUI/Lekton-Regular.ttf");
	exponentialDistGUI->setPosition(300, 113);
	exponentialDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	exponentialDistGUI->addSlider("Lambda", 0.5, 10.0, 1.0);
	exponentialDistGUI->autoSizeToFitWidgets();
	exponentialDistGUI->setWidth(211);
	exponentialDistGUI->setVisible(false);
	ofAddListener(exponentialDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	gaussDistGUI = new ofxUICanvas();
	gaussDistGUI->setFont("GUI/Lekton-Regular.ttf");
	gaussDistGUI->setPosition(300, 113);
	gaussDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	gaussDistGUI->addSlider("Sigma", 0.5, 10.0, 0.5);
	gaussDistGUI->addSlider("Mu", 0.5, 10.0, 5.0);
	gaussDistGUI->autoSizeToFitWidgets();
	gaussDistGUI->setWidth(211);
	gaussDistGUI->setVisible(false);
	ofAddListener(gaussDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	gui1->setTheme(OFX_UI_THEME_DEFAULT);
	gui2->setTheme(OFX_UI_THEME_DEFAULT);
	generalGUI->setTheme(OFX_UI_THEME_DEFAULT);
	resultsGui->setTheme(OFX_UI_THEME_DEFAULT);
	distributionGUI->setTheme(OFX_UI_THEME_DEFAULT);



}
