#include "App.h"
#include "IndependentStochasticComposer.h"
#include "Figure.h"
#include "Scales.h"

#include <vector>
#include <string>
using namespace std;

//--------------------------------------------------------------
ofxTonicSynth App::synth = ofxTonicSynth();
ofxUITextArea * App::currentFigureLabel = NULL;

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
	
	if(name == "Uniform")
		c->setDistribution(uniform);
	else if(name == "Linear")
		c->setDistribution(linear);
	else if(name == "Triangular")
		c->setDistribution(triangular);
	else if(name == "Exponential")
		c->setDistribution(exponential);
	else if(name == "Gauss")
		c->setDistribution(gauss);
	else if(name == "Cauchy")
		c->setDistribution(cauchy);
	else if(name == "Beta")
		c->setDistribution(beta);
	else if(name == "Weibull")
		c->setDistribution(weibull);
	else if(name == "Poisson")
		c->setDistribution(poisson);
	
	else if(name == "COMPOSE"){
		composition.clear();
		composition = c->compose(false, 2, 4, 3);
	}
	else if(name == "PLAY" && composition.size() > 0){
		player->play(composition);
	}
	
	else if(name == "TEMPO"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		player->setTempo((int)slider->getValue());
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
		
	currentFigureLabel->setTextString(f->getDescription());

}

void App::initSynth(){
	
	//SYNTH SETTINGS
	
	ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
	
	ControlGenerator midiNote = synth.addParameter("midiNumber");
	
	ControlGenerator volume = synth.addParameter("volume");
	synth.setParameter("volume", 1);
	
	ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
	
	// create a new oscillator which we'll use for the actual audio signal
	SquareWave tone = SquareWave();
	// create a sine wave we'll use for some vibrato
	SineWave vibratoOsc = SineWave();
	vibratoOsc.freq(10);
	
	// you can use the regular arithmatic operators on Generators and their subclasses (SineWave extends Generator)
	Generator frequency = noteFreq + (vibratoOsc * noteFreq * 0.01);
	
	// plug that frequency generator into the frequency slot of the main audio-producing sine wave
	tone.freq(noteFreq);
	
	// Partials
	SquareWave firstPartial = SquareWave().freq(noteFreq * 2);
	SquareWave secondPartial = SquareWave().freq(noteFreq * 3);
	
	// set the synth's final output generator
	synth.setOutputGen( (tone + firstPartial + secondPartial) * ADSR(0.3f, 0.0f, 0.1f, 0.6f).trigger(volume).legato(1));
}

void App::initGUI(){
	
	
    ofBackground(ofxUIColor::crimson);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	//ofEnableSmoothing();

	
	gui1 = new ofxUICanvas();
	gui1->setFont("GUI/Lekton-Regular.ttf");
	gui1->setHeight(720);
	gui1->setWidth(300);
	gui1->setPosition(0, 0);
	
	gui1->addLabel("STOCHASTIC COMPOSER", OFX_UI_FONT_LARGE);
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
	gui1->addLabelButton("COMPOSE", false);
	gui1->addLabelButton("PLAY", false);
	gui1->addSlider("TEMPO", 1, 200, 60);
	
	string textString = "1. Select distribution \n3. Select Scale \n2. Press COMPOSE \n3. Press PLAY";
    gui1->addSpacer();
    currentFigureLabel = gui1->addTextArea("textarea", textString, OFX_UI_FONT_MEDIUM);
	
	//gui1->autoSizeToFitWidgets();
	ofAddListener(gui1->newGUIEvent, this, &App::guiEvent);
	
	
	gui2 = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	gui2->setScrollAreaToScreen();
    gui2->setScrollableDirections(false, true);
	gui2->setFont("GUI/Lekton-Regular.ttf");
	gui2->addLabel("SCALE", OFX_UI_FONT_LARGE);
	gui2->setWidth(200);
	gui2->setPosition(300, 0);
	
	
	vector<string> scales(NamesOfScales, NamesOfScales + sizeof(NamesOfScales) / sizeof(string));
	gui2->addRadio("Scale", scales);
	
	
	gui2->autoSizeToFitWidgets();
	gui2->getRect()->setWidth(ofGetWidth());
	ofAddListener(gui2->newGUIEvent, this, &App::guiEvent);
	
    /*gui1TabBar = new ofxUITabBar();
	
    //SETTING gui1
    gui1TabBar->setFont("gui1/Lekton-Regular.ttf");
    gui1TabBar->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui1TabBar->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui1TabBar->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui1TabBar->setName("Metodo");
    gui1TabBar->addLabel("Metodo");
    gui1TabBar->addSpacer();
    gui1TabBar->autoSizeToFitWidgets();
    gui1TabBar->setPadding(10.0);
    gui1TabBar->setPosition(10,10);
    ofxUIColor color = ofxUIColor();
    color.set(0,0,0,60);
    gui1TabBar->setColorBack(color);
    
    
    ofxUITabBar* gui11 = new ofxUITabBar();
    gui11->setFont("gui1/Lekton-Regular.ttf");
    gui11->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui11->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui11->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui11->setName("Estocastico");
    gui11->addLabel("Metodo (II)");
    gui11->addSpacer();
    gui11->autoSizeToFitWidgets();
    ofAddListener(gui11->newgui1Event,this,&App::gui1Event);
    gui1TabBar->addCanvas(gui11);
    gui1s.push_back(gui11);
    
    ofxUITabBar* gui111 = new ofxUITabBar();
    gui111->setFont("gui1/Lekton-Regular.ttf");
    gui111->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui111->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui111->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui111->setName("Sucesos independientes");
    gui111->addLabel("Opciones");
    gui111->addSpacer();
    gui111->autoSizeToFitWidgets();
    ofAddListener(gui111->newgui1Event,this,&App::gui1Event);
    gui11->addCanvas(gui111);
    
    ofxUITabBar* gui112 = new ofxUITabBar();
    gui112->setFont("gui1/Lekton-Regular.ttf");
    gui112->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui112->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui112->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui112->setName("Sucesos dependientes");
    gui112->addLabel("Metodo (III)");
    gui112->addSpacer();
    gui112->autoSizeToFitWidgets();
    ofAddListener(gui112->newgui1Event,this,&App::gui1Event);
    gui11->addCanvas(gui112);
    
	
    ofxUICanvas* gui12 = new ofxUICanvas();
    gui12->setFont("gui1/Lekton-Regular.ttf");
    gui12->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui12->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui12->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui12->setName("Determinista");
    gui12->addLabel("Metodo (II)");
    gui12->addSpacer();
    gui12->autoSizeToFitWidgets();
    ofAddListener(gui12->newgui1Event,this,&App::gui1Event);
    gui1TabBar->addCanvas(gui12);
    gui1s.push_back(gui12);
	
    ofxUICanvas* gui13 = new ofxUICanvas();
    gui13->setFont("gui1/Lekton-Regular.ttf");
    gui13->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui13->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui13->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui13->setName("Gramatical");
    gui13->addLabel("Metodo (II)");
    gui13->addSpacer();
    gui13->autoSizeToFitWidgets();
    ofAddListener(gui13->newgui1Event,this,&App::gui1Event);
    gui1TabBar->addCanvas(gui13);
    gui1s.push_back(gui13);
    
    ofxUICanvas* gui14 = new ofxUICanvas();
    gui14->setFont("gui1/Lekton-Regular.ttf");
    gui14->setFontSize(OFX_UI_FONT_LARGE, 16);
    gui14->setFontSize(OFX_UI_FONT_MEDIUM, 10);
    gui14->setFontSize(OFX_UI_FONT_SMALL, 8);
    gui14->setName("Evolutivo");
    gui14->addLabel("Metodo (II)");
    gui14->addSpacer();
    gui14->autoSizeToFitWidgets();
    ofAddListener(gui14->newgui1Event,this,&App::gui1Event);
    gui1TabBar->addCanvas(gui14);
    gui1s.push_back(gui14);
	*/

}
