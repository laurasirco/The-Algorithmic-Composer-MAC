#include "App.h"
#include "IndependentStochasticComposer.h"
#include "MarkovChainsComposer.h"
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
	
	initGUI();
	initSynth();
	
	//player->play(result);
	
	/*MarkovChainsComposer * mc = new MarkovChainsComposer();
	 mc->addMidiToChain("../../../data/mozart_eine_kleine.mid");
	 mc->setStems(10);
	 vector<Figure *> notes = mc->compose();
	 player->play(notes);*/
	
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
	
	backgroundColor = ofColor(red, green, blue);
    ofBackground(backgroundColor);
	
	musicNotesFont.drawString("`ACDGF", 400, 600);
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
	if(button == 2)
    {
        styleGUI->setPosition(x, y);
        styleGUI->setVisible(true);
        return;
    }
    
    if(!styleGUI->isHit(x, y))
    {
        styleGUI->setVisible(false);
    }
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
		setValuesForGraph(uniform);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	
	
	else if(name == "Linear"){
		c->setDistribution(linear);
		setValuesForGraph(linear);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(true);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if(name == "Up"){
		linear->setDirection(Up);
		setValuesForGraph(linear);
	}
	else if(name == "Down"){
		linear->setDirection(Down);
		setValuesForGraph(linear);
	}
	
	
	else if(name == "Triangular"){
		c->setDistribution(triangular);
		setValuesForGraph(triangular);
		triangularDistGUI->setVisible(true);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if(name == "Triangle Base"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		triangular->setTriangleBase(slider->getValue());
		setValuesForGraph(triangular);
	}
	
	
	
	else if(name == "Exponential"){
		c->setDistribution(exponential);
		setValuesForGraph(exponential);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(true);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "Lambda"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		exponential->setLambda(slider->getValue());
		setValuesForGraph(exponential);
	}
	
	
	else if(name == "Gaussian"){
		c->setDistribution(gauss);
		setValuesForGraph(gauss);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(true);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "Sigma"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		gauss->setSigma(slider->getValue());
		setValuesForGraph(gauss);
	}
	else if (name == "Mu"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		gauss->setMu(slider->getValue());
		setValuesForGraph(gauss);
	}
	
	
	else if(name == "Cauchy"){
		c->setDistribution(cauchy);
		setValuesForGraph(cauchy);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(true);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "Alpha"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		cauchy->setAlpha(slider->getValue());
		setValuesForGraph(cauchy);
	}
	
	
	else if(name == "Beta"){
		c->setDistribution(beta);
		setValuesForGraph(beta);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(true);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "a"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		beta->setA(slider->getValue());
		setValuesForGraph(beta);
	}
	else if (name == "b"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		beta->setB(slider->getValue());
		setValuesForGraph(beta);
	}
	
	else if(name == "Weibull"){
		c->setDistribution(weibull);
		setValuesForGraph(weibull);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(true);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "T"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		weibull->setT(slider->getValue());
		setValuesForGraph(weibull);
	}
	else if (name == "S"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		weibull->setS(slider->getValue());
		setValuesForGraph(weibull);
	}
	
	else if(name == "Poisson"){
		c->setDistribution(poisson);
		setValuesForGraph(poisson);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(true);
	}
	else if (name == "lambda"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		poisson->setv(slider->getValue());
		setValuesForGraph(poisson);
	}
	
	else if(name == "COMPOSE"  && e.getButton()->getValue() == true){
		composition.clear();
		composition = composer->compose();
		resultsGui->removeWidgets();
	}
	else if(name == "PLAY" && composition.size() > 0 && !player->isPlaying()  && e.getButton()->getValue() == true){
		player->play(composition);
	}
	
	else if(name == "TEMPO"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		player->setTempo((int)slider->getValue());
	}
	
	else if(name == "THEME"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		setGUITheme((int)slider->getValue());
		
	}
	
	else if(name == "Octaves"){
		ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget;
		c->setOctaves((int)slider->getValueLow(), (int)slider->getValueHigh());
	}
	
	else if(name == "Stems"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		composer->setStems((int)slider->getValue());
	}
	else if(name == "Notes"){
		ofxUIToggle * toggle = e.getToggle();
		if(toggle->getValue())
			composer->setWantSilences(false);
	}
	else if(name == "Notes + Silences"){
		ofxUIToggle * toggle = e.getToggle();
		if(toggle->getValue())
			composer->setWantSilences(true);
	}
	else if (name == "Independent Stochastic"){
		showIndependentStochasticGUI(true);
		showMarkovChainsGUI(false);
		composer = new IndependentStochasticComposer(uniform);
	}
	else if (name == "Markov Chains"){
		showMarkovChainsGUI(true);
		showIndependentStochasticGUI(false);
		composer = new MarkovChainsComposer();
		
		MarkovChainsComposer * mc = dynamic_cast<MarkovChainsComposer *>(composer);
		mc->addMidiToChain("../../../data/mozart_eine_kleine.mid");
		fileLabel->setLabel("mozart_eine_kleine.mid");
	}
	else if(name == "Select .mid file" && e.getButton()->getValue() == true){
		ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a .mid file");
		
		//Check if the user opened a file
		if (openFileResult.bSuccess){
			
			
			std::size_t found = openFileResult.getName().find(".mid");
			if (found!=std::string::npos){
				ofLogVerbose("User selected a file");
				MarkovChainsComposer * mc = dynamic_cast<MarkovChainsComposer *>(composer);
				mc->addMidiToChain(openFileResult.getPath());
				fileLabel->setLabel(openFileResult.getName());
			}
			
			
		}else {
			ofLogVerbose("User hit cancel");
		}
	}
	
	else if(kind == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		
		if(toggle->getParent()->getName() == "Scale"){
			
			bool found = false;
			int count = 0;
			while(!found && count < 38){
				if (name == NamesOfScales[count]) {
					found = true;
				}
				else count++;
			}
		}
		else if (toggle->getParent()->getName() == "Meter"){
			int meter = atoi(name.c_str());
			composer->setMeter(meter);
		}
		else if(toggle->getParent()->getName() == "Pattern"){
			int meter = atoi(name.c_str());
			composer->setPattern(meter);
		}
		else if(toggle->getParent()->getName() == "Starting Note"){
			
			MarkovChainsComposer * mc = dynamic_cast<MarkovChainsComposer *>(composer);
			
			if (toggle->getName() == "C")
				mc->setStartingNote(0);
			else if (toggle->getName() == "C#")
				mc->setStartingNote(1);
			else if (toggle->getName() == "D")
				mc->setStartingNote(2);
			else if (toggle->getName() == "D#")
				mc->setStartingNote(3);
			else if (toggle->getName() == "E")
				mc->setStartingNote(4);
			else if (toggle->getName() == "F")
				mc->setStartingNote(5);
			else if (toggle->getName() == "F#")
				mc->setStartingNote(6);
			else if (toggle->getName() == "G")
				mc->setStartingNote(7);
			else if (toggle->getName() == "G#")
				mc->setStartingNote(8);
			else if (toggle->getName() == "A")
				mc->setStartingNote(9);
			else if (toggle->getName() == "A#")
				mc->setStartingNote(10);
			else if (toggle->getName() == "B")
				mc->setStartingNote(11);
		}
		
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
	synth.setOutputGen( (tone + firstPartial + secondPartial) * ADSR(0.3f, 0.0f, 0.1f, 0.1f).trigger(volume).legato(0));
}

void App::initGUI(){
	
	red = 236;
	green = 250;
	blue = 244;
	
	backgroundColor = ofColor(red, green, blue);
	
	musicNotesFont.loadFont("GUI/LASSUS.TTF", 100, false);
	
    ofBackground(backgroundColor);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	
	ofSetColor(0,0,0);
	
	
	methodGUI = new ofxUICanvas();
	methodGUI->setFont("GUI/Lekton-Regular.ttf");
	methodGUI->addLabel("METHOD", OFX_UI_FONT_LARGE);
	methodGUI->addSpacer();
	methodGUI->setPosition(0, 0);
	
	vector<string> methods;
	methods.push_back("Independent Stochastic");
	methods.push_back("Markov Chains");
	methods.push_back("Random Walk");
	
	ofxUIRadio * m = methodGUI->addRadio("Method", methods, OFX_UI_ORIENTATION_HORIZONTAL);
	m->getToggles()[0]->setValue(true);
	methodGUI->addSpacer();
	methodGUI->autoSizeToFitWidgets();
	methodGUI->setWidth(421);
	ofAddListener(methodGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(methodGUI);
	
	//////////
	
	styleGUI = new ofxUICanvas();
	styleGUI->setFont("GUI/Lekton-Regular.ttf");
	styleGUI->addLabel("CONTEXTUAL MENU");
    styleGUI->addSpacer();
    styleGUI->addFPSSlider("FPS");
    styleGUI->addSpacer();
	styleGUI->addSlider("THEME", 0.0, 42.0, 3.0);
	styleGUI->addSpacer();
    styleGUI->addSlider("RED", 0.0, 255.0, &red);
    styleGUI->addSlider("GREEN", 0.0, 255.0, &green);
    styleGUI->addSlider("BLUE", 0.0, 255.0, &blue);
	styleGUI->setVisible(false);
	ofAddListener(styleGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(styleGUI);
	
	
	//
	
	generalGUI = new ofxUICanvas();
	generalGUI->setFont("GUI/Lekton-Regular.ttf");
	
	generalGUI->setPosition(724, 0);
	generalGUI->setWidth(300);
	generalGUI->setHeight(120);
	
	generalGUI->addLabelButton("COMPOSE", false);
	generalGUI->addLabelButton("PLAY", false);
	generalGUI->addSlider("TEMPO", 1, 200, 60);
	generalGUI->addSpacer(300, 10);
	generalGUI->addLabel("RESULTS", OFX_UI_FONT_LARGE);
	generalGUI->addSpacer();
	ofAddListener(generalGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(generalGUI);
	
	
	/////////////
	
	
	vector<float> distribution;
	for (int i = 0; i < 10; i++) {
		distribution.push_back(0.0);
	}
	distributionGUI = new ofxUICanvas();
	distributionGUI->setFont("GUI/Lekton-Regular.ttf");
	distributionGUI->setPosition(210, 58);
	distributionGUI->addLabel("DISTRIBUTION", OFX_UI_FONT_LARGE);
	distributionGUI->addLabel("Based on 1000 samples", OFX_UI_FONT_SMALL);
	mg = distributionGUI->addMovingGraph("distribution", distribution, 10, 0.0, 25.0, 50);
	distributionGUI->addSpacer();
	distributionGUI->autoSizeToFitWidgets();
	guis.push_back(distributionGUI);
	
	
	///////////
	
	isGUI1 = new ofxUICanvas();
	isGUI1->setFont("GUI/Lekton-Regular.ttf");
	isGUI1->setHeight(360);
	isGUI1->setPosition(0, 58);
	
	
	isGUI1->addLabel("PURE STOCHASTIC", OFX_UI_FONT_LARGE);
	isGUI1->addSpacer();
	
	
	isGUI1->addLabel("DISTRIBUTION");
	
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
	
	ofxUIRadio * dis = isGUI1->addRadio("Distribution", distributions);
	dis->getToggles()[0]->setValue(true);
	setValuesForGraph(uniform);
	
	isGUI1->addSpacer();
	
	isGUI1->addLabel("MUSICAL PARAMETERS");
	isGUI1->addRangeSlider("Octaves", 0, 10, 2, 4);
	isGUI1->addSlider("Stems", 1, 20, 1);
	isGUI1->addSpacer(210, 3);
	
	vector<string> meter;
	meter.push_back("2"); meter.push_back("3"); meter.push_back("4");
	
	isGUI1->addLabel("Meter", OFX_UI_FONT_SMALL);
	ofxUIRadio * mR = isGUI1->addRadio("Meter", meter, OFX_UI_ORIENTATION_HORIZONTAL);
	mR->getToggles()[0]->setValue(true);
	
	vector<string> pattern;
	pattern.push_back("1"); pattern.push_back("2"); pattern.push_back("4"); pattern.push_back("8"); pattern.push_back("16");
	
	isGUI1->addLabel("Pattern", OFX_UI_FONT_SMALL);
	ofxUIRadio * pR = isGUI1->addRadio("Pattern", pattern, OFX_UI_ORIENTATION_HORIZONTAL);
	pR->getToggles()[2]->setValue(true);
	
	isGUI1->addSpacer(210, 3);
	vector<string> figures;
	figures.push_back("Notes");
	figures.push_back("Notes + Silences");
	ofxUIRadio * figuresRadio = isGUI1->addRadio("Figures", figures);
	figuresRadio->getToggles()[1]->setValue(true);
	
	isGUI1->addSpacer(210, 3);
	isGUI1->addLabel("Scale", OFX_UI_FONT_SMALL);
	isGUI1->autoSizeToFitWidgets();
	isGUI1->setWidth(210);
	
	ofAddListener(isGUI1->newGUIEvent, this, &App::guiEvent);
	guis.push_back(isGUI1);
	
	
	//////////////////
	
	
	isGUI2 = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	
	isGUI2->setScrollAreaToScreen();
    isGUI2->setScrollableDirections(false, true);
	isGUI2->setFont("GUI/Lekton-Regular.ttf");
	isGUI2->setPosition(0, 529);
	
	
	vector<string> scales(NamesOfScales, NamesOfScales + sizeof(NamesOfScales) / sizeof(string));
	scaleRadioButtons = isGUI2->addRadio("Scale", scales);
	scaleRadioButtons->getToggles()[0]->setValue(true);
	
	isGUI2->autoSizeToFitWidgets();
	isGUI2->setWidth(210);
	isGUI2->getRect()->setWidth(ofGetWidth());
	ofAddListener(isGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(isGUI2);
	
	
	///////////////
	
	
	string textString = "1. Select distribution \n\n3. Select Scale \n\n2. Press COMPOSE \n\n3. Press PLAY";
	
	resultsGui = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	resultsGui->setFont("GUI/Lekton-Regular.ttf");
	resultsGui->setScrollAreaToScreen();
    resultsGui->setScrollableDirections(false, true);
	
	resultsGui->setPosition(724, 120);
	resultsGui->setHeight(648);
	resultsGui->setWidth(300);
	ofAddListener(resultsGui->newGUIEvent, this, &App::guiEvent);
	//currentFigureLabel = resultsGui->addTextArea("textarea", textString, OFX_UI_FONT_MEDIUM);
	guis.push_back(resultsGui);
	
	
	/////////////
	
	
	linearDistGUI = new ofxUICanvas();
	linearDistGUI->setFont("GUI/Lekton-Regular.ttf");
	linearDistGUI->setPosition(210, 171);
	linearDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	vector<string> op1;
	op1.push_back("Up");
	op1.push_back("Down");
	linearDistGUI->addRadio("Direction", op1);
	linearDistGUI->autoSizeToFitWidgets();
	linearDistGUI->setWidth(211);
	linearDistGUI->setVisible(false);
	ofAddListener(linearDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(linearDistGUI);
	
	
	triangularDistGUI = new ofxUICanvas();
	triangularDistGUI->setFont("GUI/Lekton-Regular.ttf");
	triangularDistGUI->setPosition(210, 171);
	triangularDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	triangularDistGUI->addSlider("Triangle Base", 0.01, 1.0, 1.0);
	triangularDistGUI->autoSizeToFitWidgets();
	triangularDistGUI->setWidth(211);
	triangularDistGUI->setVisible(false);
	ofAddListener(triangularDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(triangularDistGUI);
	
	
	
	exponentialDistGUI = new ofxUICanvas();
	exponentialDistGUI->setFont("GUI/Lekton-Regular.ttf");
	exponentialDistGUI->setPosition(210, 171);
	exponentialDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	exponentialDistGUI->addSlider("Lambda", 0.5, 10.0, 1.0);
	exponentialDistGUI->autoSizeToFitWidgets();
	exponentialDistGUI->setWidth(211);
	exponentialDistGUI->setVisible(false);
	ofAddListener(exponentialDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(exponentialDistGUI);
	
	
	gaussDistGUI = new ofxUICanvas();
	gaussDistGUI->setFont("GUI/Lekton-Regular.ttf");
	gaussDistGUI->setPosition(210, 171);
	gaussDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	gaussDistGUI->addSlider("Sigma", 0.1, 10.0, 0.15);
	gaussDistGUI->addSlider("Mu", -1.5, 1.5, 0.5);
	gaussDistGUI->autoSizeToFitWidgets();
	gaussDistGUI->setWidth(211);
	gaussDistGUI->setVisible(false);
	ofAddListener(gaussDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(gaussDistGUI);
	
	cauchyDistGUI = new ofxUICanvas();
	cauchyDistGUI->setFont("GUI/Lekton-Regular.ttf");
	cauchyDistGUI->setPosition(210, 171);
	cauchyDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	cauchyDistGUI->addSlider("Alpha", 0.1, 2.5, 1.0);
	cauchyDistGUI->autoSizeToFitWidgets();
	cauchyDistGUI->setWidth(211);
	cauchyDistGUI->setVisible(false);
	ofAddListener(cauchyDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(cauchyDistGUI);
	
	
	betaDistGUI = new ofxUICanvas();
	betaDistGUI->setFont("GUI/Lekton-Regular.ttf");
	betaDistGUI->setPosition(210, 171);
	betaDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	betaDistGUI->addSlider("a", 0.1, 4.0, 0.5);
	betaDistGUI->addSlider("b", 0.1, 4.0, 0.5);
	betaDistGUI->autoSizeToFitWidgets();
	betaDistGUI->setWidth(211);
	betaDistGUI->setVisible(false);
	ofAddListener(betaDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(betaDistGUI);
	
	
	weibullDistGUI = new ofxUICanvas();
	weibullDistGUI->setFont("GUI/Lekton-Regular.ttf");
	weibullDistGUI->setPosition(210, 171);
	weibullDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	weibullDistGUI->addSlider("T", 0.1, 10.0, 1.0);
	weibullDistGUI->addSlider("S", 0.1, 3.0, 1.0);
	weibullDistGUI->autoSizeToFitWidgets();
	weibullDistGUI->setWidth(211);
	weibullDistGUI->setVisible(false);
	ofAddListener(weibullDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(weibullDistGUI);
	
	
	
	poissonDistGUI = new ofxUICanvas();
	poissonDistGUI->setFont("GUI/Lekton-Regular.ttf");
	poissonDistGUI->setPosition(210, 171);
	poissonDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	poissonDistGUI->addSlider("lambda", 0.1, 100.0, 100.0);
	poissonDistGUI->autoSizeToFitWidgets();
	poissonDistGUI->setWidth(211);
	poissonDistGUI->setVisible(false);
	ofAddListener(poissonDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(poissonDistGUI);
	
	
	/* MARKOV CHAINS */
	
	mcGUI1 = new ofxUICanvas();
	mcGUI1->setFont("GUI/Lekton-Regular.ttf");
	mcGUI1->setPosition(0, 58);
	mcGUI1->addLabel("MARKOV CHAINS", OFX_UI_FONT_LARGE);
	mcGUI1->addSpacer();
	mcGUI1->addLabelButton("Select .mid file", false);
	fileLabel = mcGUI1->addLabel("No file", OFX_UI_FONT_SMALL);
	mcGUI1->addSpacer();
	mcGUI1->addLabel("MUSICAL PARAMETERS", OFX_UI_FONT_MEDIUM);
	mcGUI1->addSlider("Stems", 1, 20, 1);
	
	mcGUI1->addLabel("Meter", OFX_UI_FONT_SMALL);
	mR = mcGUI1->addRadio("Meter", meter, OFX_UI_ORIENTATION_HORIZONTAL);
	mR->getToggles()[0]->setValue(true);
	
	mcGUI1->addLabel("Pattern", OFX_UI_FONT_SMALL);
	pR = mcGUI1->addRadio("Pattern", pattern, OFX_UI_ORIENTATION_HORIZONTAL);
	pR->getToggles()[2]->setValue(true);
	
	mcGUI1->addLabel("Starting Note", OFX_UI_FONT_SMALL);
	vector<string> start;
	start.push_back("C"); start.push_back("C#"); start.push_back("D"); start.push_back("D#"); start.push_back("E"); start.push_back("F"); start.push_back("F#");
	start.push_back("G"); start.push_back("G#"); start.push_back("A"); start.push_back("A#"); start.push_back("B");
	ofxUIRadio * sR = mcGUI1->addRadio("Starting Note", start, OFX_UI_ORIENTATION_HORIZONTAL);
	
	mcGUI1->autoSizeToFitWidgets();
	guis.push_back(mcGUI1);
	ofAddListener(mcGUI1->newGUIEvent, this, &App::guiEvent);
	
	showMarkovChainsGUI(false);
	
	
	setGUITheme(3);
	
}


void App::setValuesForGraph(Distribution * d){
	
	vector<float> values = d->getValuesForGraphic(1000);
	
	float max = 0.0;
	for(int i = 0; i < values.size(); i++){
		if(values[i] > max)
			max = values[i];
	}
	
	mg->setBuffer(values);
	mg->setMax(max + 5);
	
}


void App::showIndependentStochasticGUI(bool show){
	
	isGUI1->setVisible(show);
	isGUI2->setVisible(show);
	distributionGUI->setVisible(show);
	if(show == false){
		linearDistGUI->setVisible(show);
		triangularDistGUI->setVisible(show);
		exponentialDistGUI->setVisible(show);
		gaussDistGUI->setVisible(show);
		cauchyDistGUI->setVisible(show);
		betaDistGUI->setVisible(show);
		weibullDistGUI->setVisible(show);
		poissonDistGUI->setVisible(show);
	}
}

void App::showMarkovChainsGUI(bool show){
	mcGUI1->setVisible(show);
}

void App::setGUITheme(int i){
	
	for (int j = 0; j < guis.size(); j++) {
		guis[j]->setTheme(i);
	}
}
