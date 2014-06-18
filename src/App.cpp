#include "App.h"
#include "IndependentStochasticComposer.h"
#include "Figure.h"

#include <vector>
#include <string>
using namespace std;

//--------------------------------------------------------------
ofxTonicSynth App::synth = ofxTonicSynth();
ofxUILabel * App::currentFigureLabel = NULL;

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
	cout << "got event from: " << name << endl;
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
	
	string label = "lala";
	currentFigureLabel->setLabel(label);
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
	synth.setOutputGen( (tone + firstPartial + secondPartial)  * ADSR(0.3f, 0.0f, 0.5f, 0.6f).trigger(volume).legato(1));
}

void App::initGUI(){
	
	
    ofBackground(ofxUIColor::crimson);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	
	gui = new ofxUICanvas();
	gui->setFont("GUI/Lekton-Regular.ttf");
	gui->addLabel("STOCHASTIC COMPOSER");
	gui->addSpacer();
	gui->addLabel("Distribution");
	
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
	
	gui->addRadio("Distribution", distributions);
	
	gui->addSpacer();
	gui->addLabelButton("COMPOSE", false);
	gui->addLabelButton("PLAY", false);
	
	gui->addSpacer();
	currentFigureLabel = gui->addLabel("figure");
	gui->autoSizeToFitWidgets();
	
	ofAddListener(gui->newGUIEvent, this, &App::guiEvent);
	
    /*guiTabBar = new ofxUITabBar();
	
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
	*/

}
