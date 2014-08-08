#include "App.h"
#include "IndependentStochasticComposer.h"
#include "MarkovChainsComposer.h"
#include "RandomWalkComposer.h"
#include "MotivicDevelopmentComposer.h"
#include "MotivicDevelopmentMethods.h"
#include "SerialistComposer.h"
#include "FractionalNoiseComposer.h"
#include "ChaoticComposer.h"
#include "Figure.h"
#include "Silence.h"
#include "Note.h"
#include "Scales.h"
#include "Midi.h"

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#define WIDTH 1024
#define HEIGHT 768

using namespace std;

//--------------------------------------------------------------
ofxTonicSynth App::synth = ofxTonicSynth();
ofxUITextArea * App::currentFigureLabel = NULL;
ofxUIScrollableCanvas * App::resultsGui = NULL;
ofxUIScrollableCanvas * App::logGUI = NULL;
Player * App::player = new Player(120);
Composer * App::composer = new RandomWalkComposer();
MusicVisualizer * App::mv = new MusicVisualizer();

void App::setup(){
	
	cout << "load" << endl;
	
	for(int i = 0; i < 72; i++){
		
		ofSoundPlayer p;
		stringstream sst;
		sst << "Samples/Piano/" << i + 24 << ".wav";
		p.loadSound(sst.str());
		p.setMultiPlay(true);
		player->pushPianoSound(p);
		
	}
	
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
	
	initGUI();
	initSynth();
	selectedDistribution = 1;
	mv->init();
}

//--------------------------------------------------------------
void App::update(){
	
	if(!player->isAllPlayed())
		player->update();
	else
		synth.setParameter("volume", 0);
	//mv->update();
}

//--------------------------------------------------------------
void App::draw(){
	
	ofxUIColor c = generalGUI->getColorFill();
	
	backgroundColor = ofColor(red, green, blue);
    ofBackground(backgroundColor);
	ofSetColor(0, 0, 0, 10);
	drawGrid(8,8);
	
	ofEnableAlphaBlending();
	ofSetColor(c.r, c.g, c.b);
	
	mv->draw();
	
	ofDisableAlphaBlending();
	
}

ofColor App::getUIColor(){
	
	ofxUIColor c = resultsGui->getColorFill();
	ofColor color(c.r, c.g, c.b, 255);
	return color;
}

//--------------------------------------------------------------
void App::keyPressed(int key){
	if(key == 's'){
		styleGUI->setPosition(0,400);
		styleGUI->setVisible(true);
	}
	
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
		if (composer->getType() == IndependentStochastic) {
			isHelpGUI->setPosition(x, y);
			isHelpGUI->setVisible(true);
			return;
		}
		else if (composer->getType() == MarkovChains) {
			mcHelpGUI->setPosition(x, y);
			mcHelpGUI->setVisible(true);
			return;
		}
		else if (composer->getType() == RandomWalk) {
			rwHelpGUI->setPosition(x, y);
			rwHelpGUI->setVisible(true);
			return;
		}
		else if (composer->getType() == FractionalNoise) {
			fsHelpGUI->setPosition(x, y);
			fsHelpGUI->setVisible(true);
			return;
		}
		else if (composer->getType() == Chaotic) {
			crHelpGUI->setPosition(x, y);
			crHelpGUI->setVisible(true);
			return;
		}
		/*else if (composer->getType() == MotivicDevelopment) {
			mdHelpGUI->setPosition(x, y);
			mdHelpGUI->setVisible(true);
			return;
		}
		else if (composer->getType() == Serialist) {
			sHelpGUI->setPosition(x, y);
			sHelpGUI->setVisible(true);
			return;
		}*/
    }
    
    if(!isHelpGUI->isHit(x, y) && isHelpGUI->isVisible()){
        isHelpGUI->setVisible(false);
    }
	else if(!mcHelpGUI->isHit(x, y) && mcHelpGUI->isVisible()){
        mcHelpGUI->setVisible(false);
    }
	else if(!rwHelpGUI->isHit(x, y) && rwHelpGUI->isVisible()){
        rwHelpGUI->setVisible(false);
    }
	else if(!fsHelpGUI->isHit(x, y) && fsHelpGUI->isVisible()){
        fsHelpGUI->setVisible(false);
    }
	else if(!crHelpGUI->isHit(x, y) && crHelpGUI->isVisible()){
        crHelpGUI->setVisible(false);
    }
	/*else if(!mdHelpGUI->isHit(x, y) && mdHelpGUI->isVisible()){
        mdHelpGUI->setVisible(false);
    }
	else if(!sHelpGUI->isHit(x, y) && sHelpGUI->isVisible()){
        sHelpGUI->setVisible(false);
    }*/
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
	
	if (name == "Fixed") {
		if (selectedDistribution == 1) {
			c->setFixedPitch(60);
			fixedGUI->setVisible(true);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(false);
		}
		else if (selectedDistribution == 2){
			c->setFixedDuration((Type)5);
			fixedGUI2->setVisible(true);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(false);
		}
	}
	if (name == "Pitch" && composer->getType() == IndependentStochastic) {
		c->setFixedPitch((int)e.getSlider()->getValue());
	}
	if (name == "Duration"  && composer->getType() == IndependentStochastic) {
		c->setFixedDuration((Type)e.getSlider()->getValue());
	}

	
	if(name == "Uniform"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(uniform);
			setValuesForGraph(uniform);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(false);
			fixedGUI->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(uniform);
			setValuesForGraph(uniform);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(false);
			fixedGUI2->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(uniform);
			setValuesForGraph(uniform);
			triangularDistGUI3->setVisible(false);
			linearDistGUI3->setVisible(false);
			exponentialDistGUI3->setVisible(false);
			gaussDistGUI3->setVisible(false);
			cauchyDistGUI3->setVisible(false);
			betaDistGUI3->setVisible(false);
			weibullDistGUI3->setVisible(false);
			poissonDistGUI3->setVisible(false);
		}
		
	}
	
	
	else if(name == "Linear"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(linear);
			setValuesForGraph(linear);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(true);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(false);
			fixedGUI->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(linear);
			setValuesForGraph(linear);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(true);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(false);
			fixedGUI2->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(linear);
			setValuesForGraph(linear);
			triangularDistGUI3->setVisible(false);
			linearDistGUI3->setVisible(true);
			exponentialDistGUI3->setVisible(false);
			gaussDistGUI3->setVisible(false);
			cauchyDistGUI3->setVisible(false);
			betaDistGUI3->setVisible(false);
			weibullDistGUI3->setVisible(false);
			poissonDistGUI3->setVisible(false);
		}
	}
	else if(name == "Up"){
		if (selectedDistribution == 1) {
			LinearDistribution * d = dynamic_cast<LinearDistribution *>(c->getPitchesDistribution());
			d->setDirection(Up);
		}
		else if (selectedDistribution == 2) {
			LinearDistribution * d = dynamic_cast<LinearDistribution *>(c->getDurationsDistribution());
			d->setDirection(Up);
		}
		else if (selectedDistribution == 3) {
			LinearDistribution * d = dynamic_cast<LinearDistribution *>(c->getNotesAndSilencesDistribution());
			d->setDirection(Up);
		}
		
		setValuesForGraph(linear);
	}
	else if(name == "Down"){
		if (selectedDistribution == 1) {
			LinearDistribution * d = dynamic_cast<LinearDistribution *>(c->getPitchesDistribution());
			d->setDirection(Down);
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 2) {
			LinearDistribution * d = dynamic_cast<LinearDistribution *>(c->getDurationsDistribution());
			d->setDirection(Down);
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3) {
			LinearDistribution * d = dynamic_cast<LinearDistribution *>(c->getNotesAndSilencesDistribution());
			d->setDirection(Down);
			setValuesForGraph(d);
		}
		
	}
	
	
	else if(name == "Triangular"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(triangular);
			setValuesForGraph(triangular);
			triangularDistGUI->setVisible(true);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(false);
			fixedGUI->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(triangular);
			setValuesForGraph(triangular);
			triangularDistGUI2->setVisible(true);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(false);
			fixedGUI2->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(triangular);
			setValuesForGraph(triangular);
			triangularDistGUI3->setVisible(true);
			linearDistGUI3->setVisible(false);
			exponentialDistGUI3->setVisible(false);
			gaussDistGUI3->setVisible(false);
			cauchyDistGUI3->setVisible(false);
			betaDistGUI3->setVisible(false);
			weibullDistGUI3->setVisible(false);
			poissonDistGUI3->setVisible(false);
		}
	}
	else if(name == "Triangle Base"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			TriangularDistribution * d = dynamic_cast<TriangularDistribution *>(c->getPitchesDistribution());
			d->setTriangleBase(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			TriangularDistribution * d = dynamic_cast<TriangularDistribution *>(c->getDurationsDistribution());
			d->setTriangleBase(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			TriangularDistribution * d = dynamic_cast<TriangularDistribution *>(c->getNotesAndSilencesDistribution());
			d->setTriangleBase(slider->getValue());
			setValuesForGraph(d);
		}
	}
	
	
	
	else if(name == "Exponential"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(exponential);
			setValuesForGraph(exponential);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(true);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(false);
			fixedGUI->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(exponential);
			setValuesForGraph(exponential);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(true);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(false);
			fixedGUI2->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(exponential);
			setValuesForGraph(exponential);
			triangularDistGUI3->setVisible(false);
			linearDistGUI3->setVisible(false);
			exponentialDistGUI3->setVisible(true);
			gaussDistGUI3->setVisible(false);
			cauchyDistGUI3->setVisible(false);
			betaDistGUI3->setVisible(false);
			weibullDistGUI3->setVisible(false);
			poissonDistGUI3->setVisible(false);
		}
	}
	else if (name == "Lambda"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			ExponentialDistribution * d = dynamic_cast<ExponentialDistribution *>(c->getPitchesDistribution());
			d->setLambda(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			ExponentialDistribution * d = dynamic_cast<ExponentialDistribution *>(c->getDurationsDistribution());
			d->setLambda(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			ExponentialDistribution * d = dynamic_cast<ExponentialDistribution *>(c->getNotesAndSilencesDistribution());
			d->setLambda(slider->getValue());
			setValuesForGraph(d);
		}
	}
	
	
	else if(name == "Gaussian"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(gauss);
			setValuesForGraph(gauss);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(true);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(false);
			fixedGUI->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(gauss);
			setValuesForGraph(gauss);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(true);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(false);
			fixedGUI2->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(gauss);
			setValuesForGraph(gauss);
			triangularDistGUI3->setVisible(false);
			linearDistGUI3->setVisible(false);
			exponentialDistGUI3->setVisible(false);
			gaussDistGUI3->setVisible(true);
			cauchyDistGUI3->setVisible(false);
			betaDistGUI3->setVisible(false);
			weibullDistGUI3->setVisible(false);
			poissonDistGUI3->setVisible(false);
		}
	}
	else if (name == "Sigma"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			GaussianDistribution * d = dynamic_cast<GaussianDistribution *>(c->getPitchesDistribution());
			d->setSigma(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			GaussianDistribution * d = dynamic_cast<GaussianDistribution *>(c->getDurationsDistribution());
			d->setSigma(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			GaussianDistribution * d = dynamic_cast<GaussianDistribution *>(c->getNotesAndSilencesDistribution());
			d->setSigma(slider->getValue());
			setValuesForGraph(d);
		}
	}
	else if (name == "Mu"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			GaussianDistribution * d = dynamic_cast<GaussianDistribution *>(c->getPitchesDistribution());
			d->setMu(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			GaussianDistribution * d = dynamic_cast<GaussianDistribution *>(c->getDurationsDistribution());
			d->setMu(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			GaussianDistribution * d = dynamic_cast<GaussianDistribution *>(c->getNotesAndSilencesDistribution());
			d->setMu(slider->getValue());
			setValuesForGraph(d);
		}
	}
	
	
	else if(name == "Cauchy"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(cauchy);
			setValuesForGraph(cauchy);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(true);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(false);
			fixedGUI->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(cauchy);
			setValuesForGraph(cauchy);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(true);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(false);
			fixedGUI2->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(cauchy);
			setValuesForGraph(cauchy);
			triangularDistGUI3->setVisible(false);
			linearDistGUI3->setVisible(false);
			exponentialDistGUI3->setVisible(false);
			gaussDistGUI3->setVisible(false);
			cauchyDistGUI3->setVisible(true);
			betaDistGUI3->setVisible(false);
			weibullDistGUI3->setVisible(false);
			poissonDistGUI3->setVisible(false);
		}
	}
	else if (name == "Alpha"){
		
		if (composer->getType() == IndependentStochastic) {
			
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			CauchyDistribution * d = dynamic_cast<CauchyDistribution *>(c->getPitchesDistribution());
			d->setAlpha(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			CauchyDistribution * d = dynamic_cast<CauchyDistribution *>(c->getDurationsDistribution());
			d->setAlpha(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			CauchyDistribution * d = dynamic_cast<CauchyDistribution *>(c->getNotesAndSilencesDistribution());
			d->setAlpha(slider->getValue());
			setValuesForGraph(d);
		}
			
		}
		else if (composer->getType() == FractionalNoise){
			
			FractionalNoiseComposer * c = dynamic_cast<FractionalNoiseComposer *>(composer);
			c->setNoiseAlpha((int)e.getSlider()->getValue());
		}
	}
	
	
	else if(name == "Beta"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(beta);
			setValuesForGraph(beta);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(true);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(false);
			fixedGUI->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(beta);
			setValuesForGraph(beta);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(true);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(false);
			fixedGUI2->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(beta);
			setValuesForGraph(beta);
			triangularDistGUI3->setVisible(false);
			linearDistGUI3->setVisible(false);
			exponentialDistGUI3->setVisible(false);
			gaussDistGUI3->setVisible(false);
			cauchyDistGUI3->setVisible(false);
			betaDistGUI3->setVisible(true);
			weibullDistGUI3->setVisible(false);
			poissonDistGUI3->setVisible(false);
		}
	}
	else if (name == "a"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			BetaDistribution * d = dynamic_cast<BetaDistribution *>(c->getPitchesDistribution());
			d->setA(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			BetaDistribution * d = dynamic_cast<BetaDistribution *>(c->getDurationsDistribution());
			d->setA(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			BetaDistribution * d = dynamic_cast<BetaDistribution *>(c->getNotesAndSilencesDistribution());
			d->setA(slider->getValue());
			setValuesForGraph(d);
		}
	}
	else if (name == "b"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			BetaDistribution * d = dynamic_cast<BetaDistribution *>(c->getPitchesDistribution());
			d->setB(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			BetaDistribution * d = dynamic_cast<BetaDistribution *>(c->getDurationsDistribution());
			d->setB(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			BetaDistribution * d = dynamic_cast<BetaDistribution *>(c->getNotesAndSilencesDistribution());
			d->setB(slider->getValue());
			setValuesForGraph(d);
		}
	}
	
	else if(name == "Weibull"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(weibull);
			setValuesForGraph(weibull);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(true);
			poissonDistGUI->setVisible(false);
			fixedGUI->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(weibull);
			setValuesForGraph(weibull);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(true);
			poissonDistGUI2->setVisible(false);
			fixedGUI2->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(weibull);
			setValuesForGraph(weibull);
			triangularDistGUI3->setVisible(false);
			linearDistGUI3->setVisible(false);
			exponentialDistGUI3->setVisible(false);
			gaussDistGUI3->setVisible(false);
			cauchyDistGUI3->setVisible(false);
			betaDistGUI3->setVisible(false);
			weibullDistGUI3->setVisible(true);
			poissonDistGUI3->setVisible(false);
		}
	}
	else if (name == "T"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			WeibullDistribution * d = dynamic_cast<WeibullDistribution *>(c->getPitchesDistribution());
			d->setT(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			WeibullDistribution * d = dynamic_cast<WeibullDistribution *>(c->getDurationsDistribution());
			d->setT(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			WeibullDistribution * d = dynamic_cast<WeibullDistribution *>(c->getNotesAndSilencesDistribution());
			d->setT(slider->getValue());
			setValuesForGraph(d);
		}
	}
	else if (name == "S"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			WeibullDistribution * d = dynamic_cast<WeibullDistribution *>(c->getPitchesDistribution());
			d->setS(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			WeibullDistribution * d = dynamic_cast<WeibullDistribution *>(c->getDurationsDistribution());
			d->setS(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			WeibullDistribution * d = dynamic_cast<WeibullDistribution *>(c->getNotesAndSilencesDistribution());
			d->setS(slider->getValue());
			setValuesForGraph(d);
		}
	}
	
	else if(name == "Poisson"){
		if (selectedDistribution == 1) {
			c->setFixedPitch(-1);
			c->setPitchesDistribution(poisson);
			setValuesForGraph(poisson);
			triangularDistGUI->setVisible(false);
			linearDistGUI->setVisible(false);
			exponentialDistGUI->setVisible(false);
			gaussDistGUI->setVisible(false);
			cauchyDistGUI->setVisible(false);
			betaDistGUI->setVisible(false);
			weibullDistGUI->setVisible(false);
			poissonDistGUI->setVisible(true);
			fixedGUI2->setVisible(false);
		}
		else if (selectedDistribution == 2) {
			c->setFixedDuration(NotAFigure);
			c->setDurationsDistribution(weibull);
			setValuesForGraph(weibull);
			triangularDistGUI2->setVisible(false);
			linearDistGUI2->setVisible(false);
			exponentialDistGUI2->setVisible(false);
			gaussDistGUI2->setVisible(false);
			cauchyDistGUI2->setVisible(false);
			betaDistGUI2->setVisible(false);
			weibullDistGUI2->setVisible(false);
			poissonDistGUI2->setVisible(true);
			fixedGUI->setVisible(false);
		}
		if (selectedDistribution == 3) {
			c->setNotesAndSilencesDistribution(weibull);
			setValuesForGraph(weibull);
			triangularDistGUI3->setVisible(false);
			linearDistGUI3->setVisible(false);
			exponentialDistGUI3->setVisible(false);
			gaussDistGUI3->setVisible(false);
			cauchyDistGUI3->setVisible(false);
			betaDistGUI3->setVisible(false);
			weibullDistGUI3->setVisible(false);
			poissonDistGUI3->setVisible(true);
		}
	}
	else if (name == "lambda"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		
		if (selectedDistribution == 1) {
			PoissonDistribution * d = dynamic_cast<PoissonDistribution *>(c->getPitchesDistribution());
			d->setv(slider->getValue());
			setValuesForGraph(d);
		}
		else if(selectedDistribution == 2){
			PoissonDistribution * d = dynamic_cast<PoissonDistribution *>(c->getDurationsDistribution());
			d->setv(slider->getValue());
			setValuesForGraph(d);
		}
		else if (selectedDistribution == 3){
			PoissonDistribution * d = dynamic_cast<PoissonDistribution *>(c->getNotesAndSilencesDistribution());
			d->setv(slider->getValue());
			setValuesForGraph(d);
		}
	}
	
	else if(name == "COMPOSE"  && e.getButton()->getValue() == true){
		addLogMessage("Composing...");
		composition.clear();
		composition = composer->compose();
		resultsGui->removeWidgets();
	}
	else if(name == "PLAY" && composition.size() > 0 && !player->isPlaying()  && e.getButton()->getValue() == true){
		
		if(!player->isPaused()){
			addLogMessage("Playing...");
			player->play(composition);
			//mv->drawFigures(composition);
		}
		else{
			addLogMessage("Unpaused");
			player->unpause();
			mv->unpause();
			pauseToggle->setValue(false);
		}
		
	}
	else if (name == "PAUSE"){
		if(e.getToggle()->getValue() == true){
			addLogMessage("Paused");
			player->pause();
			mv->pause();
		}
		else{
			addLogMessage("Unpaused");
			mv->unpause();
			player->unpause();
		}
	}
	else if (name == "STOP" && e.getButton()->getValue() == true){
		addLogMessage("Stoped");
		player->stop();
		mv->stop();
		resultsGui->removeWidgets();
		
	}
	else if (name == "SAVE" && e.getButton()->getValue() == true){
		
		if(composition.size() > 0){
			ofFileDialogResult saveFileResult = ofSystemSaveDialog("Composition - " + ofGetTimestampString() + ".mid", "Save your file");
			if (saveFileResult.bSuccess){
				Midi::writeMidiFile(saveFileResult.getPath(), composition);
				stringstream sst;
				addLogMessage("Saved midi file");
			}
		}
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
		if(composer->getType() == IndependentStochastic)
			c->setOctaves((int)slider->getValueLow(), (int)slider->getValueHigh());
		else if(composer->getType() == RandomWalk){
			RandomWalkComposer * rw = dynamic_cast<RandomWalkComposer *>(composer);
			rw->setMinOctave((int)slider->getValueLow());
			rw->setMaxOctave((int)slider->getValueHigh());
		}
		else if(composer->getType() == FractionalNoise){
			FractionalNoiseComposer * c = dynamic_cast<FractionalNoiseComposer *>(composer);
			c->setMinAndMaxOctave((int)slider->getValueLow(), (int)slider->getValueHigh());
		}
		else if (composer->getType() == Chaotic){
			ChaoticComposer * c = dynamic_cast<ChaoticComposer *>(composer);
			c->setMinAndMaxOctave((int)slider->getValueLow(), (int)slider->getValueHigh());
		}
	}
	else if (name == "Octave"){
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		if (composer->getType() == MarkovChains) {
			MarkovChainsComposer * c = dynamic_cast<MarkovChainsComposer *>(composer);
			c->setOctave((int)slider->getValue());
		}
		else if (composer->getType() == Serialist){
			SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
			c->setOctave((int)slider->getValue());
		}
		
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
		showMarkovChainsGUI(false);
		showRandomWalkGUI(false);
		showIndependentStochasticGUI(true);
		showMotivicDevelopmentGUI(false);
		showSerialGUI(false);
		showFractionalNoiseGUI(false);
		showChaoticResponseGUI(false);
		
		composer = new IndependentStochasticComposer(uniform);
	}
	else if (name == "Markov Chains"){
		showIndependentStochasticGUI(false);
		showRandomWalkGUI(false);
		showMarkovChainsGUI(true);
		showMotivicDevelopmentGUI(false);
		showSerialGUI(false);
		showFractionalNoiseGUI(false);
		showChaoticResponseGUI(false);
		
		composer = new MarkovChainsComposer();
		
		MarkovChainsComposer * mc = dynamic_cast<MarkovChainsComposer *>(composer);
		mc->addMidiToChain("../../../data/mozart_eine_kleine.mid");
		fileLabel->setLabel("mozart_eine_kleine.mid");
		composition = Midi::readMidiFile("../../../data/mozart_eine_kleine.mid");
		addLogMessage("Read file mozart_eine_kleine.mid");
	}
	else if(name == "Random Walk"){
		showMarkovChainsGUI(false);
		showIndependentStochasticGUI(false);
		showRandomWalkGUI(true);
		showMotivicDevelopmentGUI(false);
		showSerialGUI(false);
		showFractionalNoiseGUI(false);
		showChaoticResponseGUI(false);
		
		composer = new RandomWalkComposer();
	}
	else if(name == "Motivic Development"){
		showMarkovChainsGUI(false);
		showIndependentStochasticGUI(false);
		showRandomWalkGUI(false);
		showMotivicDevelopmentGUI(true);
		showSerialGUI(false);
		showFractionalNoiseGUI(false);
		showChaoticResponseGUI(false);
		
		composer = new MotivicDevelopmentComposer();
	}
	else if(name == "Serialism"){
		showMarkovChainsGUI(false);
		showIndependentStochasticGUI(false);
		showRandomWalkGUI(false);
		showMotivicDevelopmentGUI(false);
		showSerialGUI(true);
		showFractionalNoiseGUI(false);
		showChaoticResponseGUI(false);
		
		composer = new SerialistComposer();
	}
	else if (name == "Fractional Noise"){
		showMarkovChainsGUI(false);
		showIndependentStochasticGUI(false);
		showRandomWalkGUI(false);
		showMotivicDevelopmentGUI(false);
		showSerialGUI(false);
		showFractionalNoiseGUI(true);
		showChaoticResponseGUI(false);
		
		composer = new FractionalNoiseComposer();
	}
	else if(name == "Chaotic Response"){
		showMarkovChainsGUI(false);
		showIndependentStochasticGUI(false);
		showRandomWalkGUI(false);
		showMotivicDevelopmentGUI(false);
		showSerialGUI(false);
		showFractionalNoiseGUI(false);
		showChaoticResponseGUI(true);
		
		composer = new ChaoticComposer();
	}
	if(name == "Iterations"){
		ofxUISlider * s = e.getSlider();
		ChaoticComposer * c = dynamic_cast<ChaoticComposer *>(composer);
		c->setIterations((int) s->getValue());
	}
	
	if(name == "X_0"){
		
		ChaoticComposer * c = dynamic_cast<ChaoticComposer *>(composer);
		c->setX0(e.getSlider()->getValue());
	}
	if(name == "Y_0"){
		
		ChaoticComposer * c = dynamic_cast<ChaoticComposer *>(composer);
		c->setY0(e.getSlider()->getValue());
	}
	if(name == "A" && composer->getType() == Chaotic){
		
		ChaoticComposer * c = dynamic_cast<ChaoticComposer *>(composer);
		c->setA(e.getSlider()->getValue());
	}
	if(name == "B" &&  composer->getType() == Chaotic){
		
		ChaoticComposer * c = dynamic_cast<ChaoticComposer *>(composer);
		c->setB(e.getSlider()->getValue());
	}
	
	if (name == "Pitch" && composer->getType() == FractionalNoise) {
		FractionalNoiseComposer * c = dynamic_cast<FractionalNoiseComposer *>(composer);
		
		c->setFixedPitch((int)e.getSlider()->getValue());
	}
	
	else if (name == "Add figure" && e.getButton()->getValue() == true){
		
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		
		ofxUIRadio * type = dynamic_cast<ofxUIRadio *>(mdGUI0->getWidget("Type"));
		ofxUIRadio * duration = dynamic_cast<ofxUIRadio *>(mdGUI0->getWidget("Duration"));
		ofxUISlider * pitch = dynamic_cast<ofxUISlider *>(mdGUI0->getWidget("Pitch"));
		ofxUISlider * velocity = dynamic_cast<ofxUISlider *>(mdGUI0->getWidget("Velocity"));
		
		bool f = false;
		int i = 0;
		while(!f && i < duration->getToggles().size()){
			if (duration->getToggles()[i]->getValue() == true) {
				f = true;
			}
			else i++;
		}
		Type t = (Type) i;
		
		if(i == duration->getToggles().size())
			t = Quarter;
		
		//NOTE
		if (type->getToggles()[0]->getValue() == true) {
			Note *n = new Note(t, (int)pitch->getValue(), (int)velocity->getValue());
			c->addFigureToMotive(n);
			n->printMyself();
			
		}
		
		//SILENCE
		else if(type->getToggles()[1]->getValue() == true){
			Silence *s = new Silence(t);
			c->addFigureToMotive(s);
			s->printMyself();
		}
	}
	else if (name == "Reset Motive" && e.getButton()->getValue() == true){
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->resetMotive();
		addLogMessage("Deleted motive");
	}
	
	else if(name == "Add repetition" && e.getButton()->getValue() == true){
		
		RepetitionMethod * rm = new RepetitionMethod();
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->addMethodToSequence(rm);
		stringstream sst;
		sst << labels.size() + 1 << " REPETITION ";
		labels.push_back(mdGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL));
	}
	else if(name == "Add transpose" && e.getButton()->getValue() == true){
		ofxUISlider *t = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("Transpose steps (st)"));
		TransposeMethod * tm = new TransposeMethod((int) t->getValue());
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->addMethodToSequence(tm);
		
		stringstream sst;
		sst << labels.size() + 1 << " TRANSPOSE " << (int)t->getValue() << " steps";
		labels.push_back(mdGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL));
	}
	
	else if(name == "Add expand" && e.getButton()->getValue() == true){
		ofxUISlider *e = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("Expand steps (st)"));
		ExpandMethod * em = new ExpandMethod((int) e->getValue());
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->addMethodToSequence(em);
		
		stringstream sst;
		sst << labels.size() + 1 << " EXPAND " << (int)e->getValue() << " steps";
		labels.push_back(mdGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL));
	}
    
	else if (name == "Add invert" && e.getButton()->getValue() == true){
        
        /*ofxUISortableList * list = dynamic_cast<ofxUISortableList *>(mdGUI3->getWidget("Sequence"));
		 
		 cout << "before: " << list->getListItems().size() << endl;
		 list->addItem("Invert");
		 cout << "after: " << list->getListItems().size() << endl;*/
		
		InvertMethod * im = new InvertMethod();
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->addMethodToSequence(im);
		
		stringstream sst;
		sst << labels.size() + 1 << " INVERT ";
		labels.push_back(mdGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL));
    }
	
	else if(name == "Add retrograde" && e.getButton()->getValue() == true){
		
		RetrogradeMethod * rm = new RetrogradeMethod();
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->addMethodToSequence(rm);
		stringstream sst;
		sst << labels.size() + 1 << " RETROGRADE ";
		labels.push_back(mdGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL));
	}
	
	else if(name == "Add register displacement" && e.getButton()->getValue() == true){
		
		vector<int> regDisp;
		
		ofxUISlider *e1 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("1"));
		regDisp.push_back((int) e1->getValue());
		ofxUISlider *e2 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("2"));
		regDisp.push_back((int) e2->getValue());
		ofxUISlider *e3 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("3"));
		regDisp.push_back((int) e3->getValue());
		ofxUISlider *e4 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("4"));
		regDisp.push_back((int) e4->getValue());
		ofxUISlider *e5 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("5"));
		regDisp.push_back((int) e5->getValue());
		ofxUISlider *e6 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("6"));
		regDisp.push_back((int) e6->getValue());
		ofxUISlider *e7 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("7"));
		regDisp.push_back((int) e7->getValue());
		ofxUISlider *e8 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("8"));
		regDisp.push_back((int) e8->getValue());
		ofxUISlider *e9 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("9"));
		regDisp.push_back((int) e9->getValue());
		
		RegisterDisplacement * rdm = new RegisterDisplacement(regDisp);
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->addMethodToSequence(rdm);
		
		stringstream sst;
		sst << labels.size() + 1 << " REGISTER DISPLACEMENT ";
		labels.push_back(mdGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL));
	}
	
	
	else if(name == "Add rhythm expand" && e.getButton()->getValue() == true){
		
		ofxUISlider *e1 = dynamic_cast<ofxUISlider *>(mdGUI1->getWidget("Factor"));
		RhythmExpand * re = new RhythmExpand((int)e1->getValue());
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->addMethodToSequence(re);
		
		stringstream sst;
		sst << labels.size() + 1 << " RHYTHM EXPAND f " << (int)e1->getValue();
		labels.push_back(mdGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL));
	}
	
	else if(name == "Generate" && e.getButton()->getValue() == true){
		
		ofxUISlider * e1 = dynamic_cast<ofxUISlider *>(mdGUI0->getWidget("Figures"));
		ofxUIRangeSlider * e2 = dynamic_cast<ofxUIRangeSlider *>(mdGUI0->getWidget("Octaves"));
		int figures = (int)e1->getValue();
		int minOctave = (int)e2->getValueLow();
		int maxOctave = (int)e2->getValueHigh();
		
		IndependentStochasticComposer * ic = new IndependentStochasticComposer(new UniformDistribution());
		ic->setOctaves(minOctave, maxOctave);
		ic->setNumberOfFigures(figures);
		
		vector<Figure *> motive = ic->compose();
		
		MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
		c->setMotive(motive);
		delete(ic);
		ic = NULL;
		
		
		
	}
	else if (name == "Reset" && e.getButton()->getValue() == true){
		
		if(composer->getType() == MotivicDevelopment){
			MotivicDevelopmentComposer * c = dynamic_cast<MotivicDevelopmentComposer *>(composer);
			c->resetSequence();
			
			for (int i = 0; i < labels.size(); i++) {
				mdGUI3->removeWidget(labels[i]);
			}
			labels.clear();
		}
		
		else if (composer->getType() == Serialist){
			SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
			c->resetSequence();
			
			for (int i = 0; i < sequenceListLabels.size(); i++) {
				sGUI3->removeWidget(sequenceListLabels[i]);
			}
			sequenceListLabels.clear();
		}
		
	}
	
	else if(name == "Select .mid file" && e.getButton()->getValue() == true){
		ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a .mid file");
		
		//Check if the user opened a file
		if (openFileResult.bSuccess){
			
			
			std::size_t found = openFileResult.getName().find(".mid");
			if (found!=std::string::npos){
				ofLogVerbose("User selected a file");
				
				if(composer->getType() == MarkovChains){
					MarkovChainsComposer * mc = dynamic_cast<MarkovChainsComposer *>(composer);
					mc->addMidiToChain(openFileResult.getPath());
					fileLabel->setLabel(openFileResult.getName());
					composition = Midi::readMidiFile(openFileResult.getPath());
				}
				else if(composer->getType() == MotivicDevelopment){
					MotivicDevelopmentComposer * md = dynamic_cast<MotivicDevelopmentComposer *>(composer);
					vector<Figure *> motive = Midi::readMidiFile(openFileResult.getPath());
					motive.erase(motive.begin() + 9, motive.end());
					md->setMotive(motive);
					
				}
				stringstream sst;
				App::addLogMessage("Opened midi file");
			}
			
			
		}else {
			ofLogVerbose("User hit cancel");
		}
	}
	
	
	else if(name == "PITCHES" && e.getButton()->getValue() == true){
		selectedDistribution = 1;
		setValuesForGraph(c->getPitchesDistribution());
		toggleDistribution();
	}
	else if(name == "DURATIONS" && e.getButton()->getValue() == true){
		selectedDistribution = 2;
		setValuesForGraph(c->getDurationsDistribution());
		toggleDistribution();
	}
	else if(name == "NOTES-SILENCES" && e.getButton()->getValue() == true){
		selectedDistribution = 3;
		setValuesForGraph(c->getNotesAndSilencesDistribution());
		toggleDistribution();
	}
    
	else if(name == "Reset Melodic Classes" && e.getButton()->getValue() == true){
		melodicList.clear();
		melodicListLabel->setTextString("Classes: ");
	}
	else if(name == "Set Melodic Classes" && e.getButton()->getValue() == true){
		
		if (melodicList.size() == 12) {
			vector<int> mC;
			SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
			int octave = c->getOctave();
			
			for (int i = 0; i < 12; i++) {
				int pitch;
				if (melodicList[i] == "C") {
					pitch = 10*(octave + 2) + 0 + (2*octave + 4);
				}
				else if (melodicList[i] == "C#") {
					pitch = 10*(octave + 2) + 1 + (2*octave + 4);
				}
				else if (melodicList[i] == "D") {
					pitch = 10*(octave + 2) + 2 + (2*octave + 4);
				}
				else if (melodicList[i] == "D#") {
					pitch = 10*(octave + 2) + 3 + (2*octave + 4);
				}
				else if (melodicList[i] == "E") {
					pitch = 10*(octave + 2) + 4 + (2*octave + 4);
				}
				else if (melodicList[i] == "F") {
					pitch = 10*(octave + 2) + 5 + (2*octave + 4);
				}
				else if (melodicList[i] == "F#") {
					pitch = 10*(octave + 2) + 6 + (2*octave + 4);
				}
				else if (melodicList[i] == "G") {
					pitch = 10*(octave + 2) + 7 + (2*octave + 4);
				}
				else if (melodicList[i] == "G#") {
					pitch = 10*(octave + 2) + 8 + (2*octave + 4);
				}
				else if (melodicList[i] == "A") {
					pitch = 10*(octave + 2) + 9 + (2*octave + 4);
				}
				else if (melodicList[i] == "A#") {
					pitch = 10*(octave + 2) + 10 + (2*octave + 4);
				}
				else if (melodicList[i] == "B") {
					pitch = 10*(octave + 2) + 11 + (2*octave + 4);
				}
				
				mC.push_back(pitch);
			}
			
			c->setMelodicClasses(mC);
		}
	}
	else if(name == "Reset Rhythmic Classes" && e.getButton()->getValue() == true){
		rhythmicList.clear();
		rhythmicListLabel->setTextString("Classes: ");
	}
	else if(name == "Set Rhythmic Classes" && e.getButton()->getValue() == true){
		
		if(rhythmicList.size() == 12){
			vector<Type> rC;
			SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
			
			for (int i = 0; i < 12; i++) {
				Type t;
				if (rhythmicList[i] == "DWhole") {
					t = DWhole;
				}
				else if (rhythmicList[i] == "Whole") {
					t = Whole;
				}
				else if (rhythmicList[i] == "DHalf") {
					t = DHalf;
				}
				else if (rhythmicList[i] == "Half") {
					t = Half;
				}
				else if (rhythmicList[i] == "DQuarter") {
					t = DQuarter;
				}
				else if (rhythmicList[i] == "Quarter") {
					t = Quarter;
				}
				else if (rhythmicList[i] == "DEighth") {
					t = DEighth;
				}
				else if (rhythmicList[i] == "Eighth") {
					t = Eighth;
				}
				else if (rhythmicList[i] == "DSixteenth") {
					t = DSixteenth;
				}
				else if (rhythmicList[i] == "Sixteenth") {
					t = Sixteenth;
				}
				else if (rhythmicList[i] == "DThirtySecond") {
					t = DThirtySecond;
				}
				else if (rhythmicList[i] == "ThirtySecond") {
					t = ThirtySecond;
				}
				rC.push_back(t);
			}
			c->setRhythmicClasses(rC);
		}
	}
	else if(name == "Reset Series" && e.getButton()->getValue() == true){
		seriesList.clear();
		seriesListLabel->setTextString("Classes: ");
	}
	else if (name == "Set Series" && e.getButton()->getValue() == true){
		
		if (seriesList.size() == 12) {
			vector<int> sL;
			SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
			
			for (int i = 0; i < seriesList.size(); i++) {
				sL.push_back(atoi(seriesList[i].c_str()));
			}
			
			c->setOriginalSeries(sL);
		}
	}
	else if (name == "Add Transpose" && e.getButton()->getValue() == true){
		
		ofxUISlider * s = (ofxUISlider *)sGUI2->getWidget("Steps");
		ofxUIRadio * r = (ofxUIRadio *)sGUI2->getWidget("Transpose Affects");
		bool pitch = r->getToggles()[0]->getValue();
		bool dur = r->getToggles()[1]->getValue();
		
		SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
		if((int)s->getValue() > 0){
			TransposeSMethod * sm;
			if (pitch && !dur) {
				sm = new TransposeSMethod(TPitch, (int)s->getValue());
				c->addMethodToSequence(sm);
				stringstream sst;
				sst << "[T(" << (int)s->getValue() << ")], to pitch";
				ofxUILabel * l = sGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL);
				sequenceListLabels.push_back(l);
			}
			else if (!pitch && dur) {
				sm = new TransposeSMethod(TRhythm, (int)s->getValue());
				c->addMethodToSequence(sm);
				stringstream sst;
				sst << "[T(" << (int)s->getValue() << ")], to rhythm";
				ofxUILabel * l = sGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL);
				sequenceListLabels.push_back(l);
			}
			if (pitch && dur) {
				sm = new TransposeSMethod(TPitchAndRhythm, (int)s->getValue());
				c->addMethodToSequence(sm);
				stringstream sst;
				sst << "[T(" << (int)s->getValue() << ")], to pitch and rhythm:";
				ofxUILabel * l = sGUI3->addLabel(sst.str(), OFX_UI_FONT_SMALL);
				sequenceListLabels.push_back(l);
			}
		}
	}
	else if (name == "Add Inversion" && e.getButton()->getValue() == true){
		
		ofxUIRadio * r = (ofxUIRadio *)sGUI2->getWidget("Inversion Affects");
		bool pitch = r->getToggles()[0]->getValue();
		bool dur = r->getToggles()[1]->getValue();
		SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
		InvertSMethod * sm;
		if (pitch && !dur) {
			sm = new InvertSMethod(TPitch);
			c->addMethodToSequence(sm);
			ofxUILabel * l =sGUI3->addLabel("[I], to pitch", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
		else if (!pitch && dur) {
			sm = new InvertSMethod(TRhythm);
			c->addMethodToSequence(sm);
			ofxUILabel * l =sGUI3->addLabel("[I], to rhythm", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
		if (pitch && dur) {
			sm = new InvertSMethod(TPitchAndRhythm);
			c->addMethodToSequence(sm);
			ofxUILabel * l = sGUI3->addLabel("[I], to pitch and rhythm", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
	}
	else if (name == "Add Retrograde" && e.getButton()->getValue() == true){
		
		ofxUIRadio * r = (ofxUIRadio *)sGUI2->getWidget("Retrograde Affects");
		bool pitch = r->getToggles()[0]->getValue();
		bool dur = r->getToggles()[1]->getValue();
		SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
		RetrogradeSMethod * sm;
		if (pitch && !dur) {
			sm = new RetrogradeSMethod(TPitch);
			c->addMethodToSequence(sm);
			ofxUILabel * l = sGUI3->addLabel("[R], to pitch", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
		else if (!pitch && dur) {
			sm = new RetrogradeSMethod(TRhythm);
			c->addMethodToSequence(sm);
			ofxUILabel * l = sGUI3->addLabel("[R], to rhythm", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
		if (pitch && dur) {
			sm = new RetrogradeSMethod(TPitchAndRhythm);
			c->addMethodToSequence(sm);
			ofxUILabel * l = sGUI3->addLabel("[R], to pitch and rhythm", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
	}
	else if (name == "Add Retrograde Inversion" && e.getButton()->getValue() == true){
		
		ofxUIRadio * r = (ofxUIRadio *)sGUI2->getWidget("Retrograde Inversion Affects");
		bool pitch = r->getToggles()[0]->getValue();
		bool dur = r->getToggles()[1]->getValue();
		SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
		RetrogradeInversionSMethod * sm;
		if (pitch && !dur) {
			sm = new RetrogradeInversionSMethod(TPitch);
			c->addMethodToSequence(sm);
			ofxUILabel * l = sGUI3->addLabel("[RI], to pitch", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
		else if (!pitch && dur) {
			sm = new RetrogradeInversionSMethod(TRhythm);
			c->addMethodToSequence(sm);
			ofxUILabel * l = sGUI3->addLabel("[RI], to rhythm", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
		if (pitch && dur) {
			sm = new RetrogradeInversionSMethod(TPitchAndRhythm);
			c->addMethodToSequence(sm);
			ofxUILabel * l = sGUI3->addLabel("[RI], to pitch and rhythm", OFX_UI_FONT_SMALL);
			sequenceListLabels.push_back(l);
		}
	}
	else if (name == "Set Fixed Pitches"){
		
		ofxUILabelToggle * toggle = (ofxUILabelToggle *)e.getToggle();
		SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
		c->setFixedPitches(toggle->getValue());
	}
	else if (name == "Set Fixed Rhythm"){
		
		ofxUILabelToggle * toggle = (ofxUILabelToggle *)e.getToggle();
		SerialistComposer * c = dynamic_cast<SerialistComposer *>(composer);
		c->setFixedRhythm(toggle->getValue());
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
			
			if(composer->getType() == IndependentStochastic){
				IndependentStochasticComposer * is = dynamic_cast<IndependentStochasticComposer *>(composer);
				is->setScale(count);
			}
			else if(composer->getType() == RandomWalk){
				RandomWalkComposer * rw = dynamic_cast<RandomWalkComposer *>(composer);
				rw->setScale(count);
			}
			else if(composer->getType() == FractionalNoise){
				FractionalNoiseComposer * fs = dynamic_cast<FractionalNoiseComposer *>(composer);
				fs->setScale(count);
			}
			else if (composer->getType() == Chaotic){
				ChaoticComposer * cr = dynamic_cast<ChaoticComposer *>(composer);
				cr->setScale(count);
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
		else if(toggle->getParent()->getName() == "Figure"){
			RandomWalkComposer * rw = dynamic_cast<RandomWalkComposer *>(composer);
			
			if (toggle->getName() == "Dotted Whole")
				rw->setTypeOfFigure(DWhole);
			else if (toggle->getName() == "Whole")
				rw->setTypeOfFigure(Whole);
			else if (toggle->getName() == "Dotted Half")
				rw->setTypeOfFigure(DHalf);
			else if (toggle->getName() == "Half")
				rw->setTypeOfFigure(Half);
			else if (toggle->getName() == "Dotted Quarter")
				rw->setTypeOfFigure(DQuarter);
			else if (toggle->getName() == "Quarter")
				rw->setTypeOfFigure(Quarter);
			else if (toggle->getName() == "Dotted Eighth")
				rw->setTypeOfFigure(DEighth);
			else if (toggle->getName() == "Eighth")
				rw->setTypeOfFigure(Eighth);
			else if (toggle->getName() == "Dotted Sixteenth")
				rw->setTypeOfFigure(DSixteenth);
			else if (toggle->getName() == "Sixteenth")
				rw->setTypeOfFigure(Sixteenth);
			else if (toggle->getName() == "Dotted ThirtySecond")
				rw->setTypeOfFigure(DThirtySecond);
			else if (toggle->getName() == "ThirtySecond")
				rw->setTypeOfFigure(ThirtySecond);
			else if (toggle->getName() == "SixtyFourth")
				rw->setTypeOfFigure(SixtyFourth);
		}
		else if(toggle->getParent()->getName() == "Fixed Duration"){
			
			if (toggle->getName() == "Dotted Whole")
				c->setFixedDuration(DWhole);
			else if (toggle->getName() == "Whole")
				c->setFixedDuration(Whole);
			else if (toggle->getName() == "Dotted Half")
				c->setFixedDuration(DHalf);
			else if (toggle->getName() == "Half")
				c->setFixedDuration(Half);
			else if (toggle->getName() == "Dotted Quarter")
				c->setFixedDuration(DQuarter);
			else if (toggle->getName() == "Quarter")
				c->setFixedDuration(Quarter);
			else if (toggle->getName() == "Dotted Eighth")
				c->setFixedDuration(DEighth);
			else if (toggle->getName() == "Eighth")
				c->setFixedDuration(Eighth);
			else if (toggle->getName() == "Dotted Sixteenth")
				c->setFixedDuration(DSixteenth);
			else if (toggle->getName() == "Sixteenth")
				c->setFixedDuration(Sixteenth);
			else if (toggle->getName() == "Dotted ThirtySecond")
				c->setFixedDuration(DThirtySecond);
			else if (toggle->getName() == "ThirtySecond")
				c->setFixedDuration(ThirtySecond);
			else if (toggle->getName() == "SixtyFourth")
				c->setFixedDuration(SixtyFourth);
		}
		else if(toggle->getParent()->getName() == "PAffects"){
			
			FractionalNoiseComposer * c = dynamic_cast<FractionalNoiseComposer *>(composer);
			
			if (toggle->getName() == "Affects pitches") {
				c->setFixedPitch(-1);
				fsPitchesSlider->setVisible(false);
			}
			else if (toggle->getName() == "Fixed pitches"){
				fsPitchesSlider->setVisible(true);
			}
		}
		else if(toggle->getParent()->getName() == "DAffects"){
			
			FractionalNoiseComposer * c = dynamic_cast<FractionalNoiseComposer *>(composer);
			
			if (toggle->getName() == "Affects durations") {
				c->setFixedDuration(NotAFigure);
				fsDurationsRadio->setVisible(false);
			}
			else if (toggle->getName() == "Fixed durations"){
				fsDurationsRadio->setVisible(true);
			}
		}
		else if(toggle->getParent()->getName() == "FSDuration"){
			
			FractionalNoiseComposer * c = dynamic_cast<FractionalNoiseComposer *>(composer);
			
			if (toggle->getName() == "Dotted Whole")
				c->setFixedDuration(DWhole);
			else if (toggle->getName() == "Whole")
				c->setFixedDuration(Whole);
			else if (toggle->getName() == "Dotted Half")
				c->setFixedDuration(DHalf);
			else if (toggle->getName() == "Half")
				c->setFixedDuration(Half);
			else if (toggle->getName() == "Dotted Quarter")
				c->setFixedDuration(DQuarter);
			else if (toggle->getName() == "Quarter")
				c->setFixedDuration(Quarter);
			else if (toggle->getName() == "Dotted Eighth")
				c->setFixedDuration(DEighth);
			else if (toggle->getName() == "Eighth")
				c->setFixedDuration(Eighth);
			else if (toggle->getName() == "Dotted Sixteenth")
				c->setFixedDuration(DSixteenth);
			else if (toggle->getName() == "Sixteenth")
				c->setFixedDuration(Sixteenth);
			else if (toggle->getName() == "Dotted ThirtySecond")
				c->setFixedDuration(DThirtySecond);
			else if (toggle->getName() == "ThirtySecond")
				c->setFixedDuration(ThirtySecond);
			else if (toggle->getName() == "SixtyFourth")
				c->setFixedDuration(SixtyFourth);
		}
		else if (toggle->getParent()->getName() == "CRFunction"){
			
			ChaoticComposer * c = dynamic_cast<ChaoticComposer *>(composer);
			
			if (toggle->getName() == "Logistic Map (1D)") {
				c->setDynamicalSystem(LogisticMap);
				
				crLogisticGUI->setVisible(true);
				crHenonGUI->setVisible(false);
				crMandelbrotGUI->setVisible(false);
				crTentMapGUI->setVisible(false);
				
				ofxUISlider * Aslider = (ofxUISlider *)crLogisticGUI->getWidget("A");
				c->setA(Aslider->getValue());
				ofxUISlider * Xslider = (ofxUISlider *)crLogisticGUI->getWidget("X_0");
				c->setX0(Xslider->getValue());
			}
			else if (toggle->getName() == "Mandelbrot Set (1D)") {
				c->setDynamicalSystem(MandelbrotSet);
				
				crMandelbrotGUI->setVisible(true);
				crLogisticGUI->setVisible(false);
				crHenonGUI->setVisible(false);
				crTentMapGUI->setVisible(false);
				
				ofxUISlider * Aslider = (ofxUISlider *)crLogisticGUI->getWidget("A");
				c->setA(Aslider->getValue());
				ofxUISlider * Xslider = (ofxUISlider *)crLogisticGUI->getWidget("X_0");
				c->setX0(Xslider->getValue());
			}
			else if (toggle->getName() == "Tent Map (1D)"){
				
				c->setDynamicalSystem(TentMap);
				
				crMandelbrotGUI->setVisible(false);
				crLogisticGUI->setVisible(false);
				crHenonGUI->setVisible(false);
				crTentMapGUI->setVisible(true);
				
				ofxUISlider * Aslider = (ofxUISlider *)crLogisticGUI->getWidget("A");
				c->setA(Aslider->getValue());
				ofxUISlider * Xslider = (ofxUISlider *)crLogisticGUI->getWidget("X_0");
				c->setX0(Xslider->getValue());
			}
			else if (toggle->getName() == "Henon Map (2D)"){
				c->setDynamicalSystem(HenonMap);
				
				crLogisticGUI->setVisible(false);
				crHenonGUI->setVisible(true);
				crMandelbrotGUI->setVisible(false);
				crTentMapGUI->setVisible(false);
				
				ofxUISlider * Aslider = (ofxUISlider *)crHenonGUI->getWidget("A");
				c->setA(Aslider->getValue());
				ofxUISlider * Bslider = (ofxUISlider *)crHenonGUI->getWidget("B");
				c->setB(Bslider->getValue());
				ofxUISlider * Xslider = (ofxUISlider *)crHenonGUI->getWidget("X_0");
				c->setX0(Xslider->getValue());
				ofxUISlider * Yslider = (ofxUISlider *)crHenonGUI->getWidget("Y_0");
				c->setY0(Yslider->getValue());
			}
		}
		
    }
	
	if (kind == OFX_UI_WIDGET_LABELTOGGLE) {
		
		ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget;
		
		if (toggle->getName() == "C"){
			if (toggle->getValue() == true) {
				melodicList.push_back("C");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "C");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
		}
		else if (toggle->getName() == "C#"){
			if (toggle->getValue() == true) {
				melodicList.push_back("C#");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "C#");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
		}
		else if (toggle->getName() == "D"){
			if (toggle->getValue() == true) {
				melodicList.push_back("D");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "D");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "D#"){
			if (toggle->getValue() == true) {
				melodicList.push_back("D#");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "D#");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "E"){
			if (toggle->getValue() == true) {
				melodicList.push_back("E");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "E");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "F"){
			if (toggle->getValue() == true) {
				melodicList.push_back("F");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "F");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "F#"){
			if (toggle->getValue() == true) {
				melodicList.push_back("F#");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "F#");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "G"){
			if (toggle->getValue() == true) {
				melodicList.push_back("G");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "G");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "G#"){
			if (toggle->getValue() == true) {
				melodicList.push_back("G#");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "G#");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "A"){
			if (toggle->getValue() == true) {
				melodicList.push_back("A");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "A");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "A#"){
			if (toggle->getValue() == true) {
				melodicList.push_back("A#");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "A#");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "B"){
			if (toggle->getValue() == true) {
				melodicList.push_back("B");
			}
			else{
				vector<string>::iterator result = find(melodicList.begin(), melodicList.end(), "B");
				if (result != melodicList.end()) {
					melodicList.erase(result);
				}
			}
			
		}
		
		else{
			
			for(int i = 0; i < 12; i ++){
				
				stringstream sst;
				sst << i;
				if (toggle->getName() == sst.str()) {
					if (toggle->getValue() == true) {
						seriesList.push_back(sst.str());
						break;
					}
					else{
						vector<string>::iterator result = find(seriesList.begin(), seriesList.end(), sst.str());
						if (result != seriesList.end()) {
							seriesList.erase(result);
							break;
						}
					}
				}
			}
			
			if(composer->getType() == Serialist){
				
				stringstream sst;
				sst << "Series: ";
				for (int i = 0; i < seriesList.size(); i++) {
					sst << seriesList[i] << " ";
				}
				
				cout << sst.str() << endl;
				seriesListLabel->setTextString(sst.str());
			}
		}
		
		if(composer->getType() == Serialist){
			
			stringstream sst;
			sst << "Classes: ";
			for (int i = 0; i < melodicList.size(); i++) {
				sst << melodicList[i] << " ";
			}
			
			cout << sst.str() << endl;
			melodicListLabel->setTextString(sst.str());
		}
		
	}
	
	
	else if(kind == OFX_UI_WIDGET_IMAGETOGGLE){
		
		ofxUIImageToggle * toggle = (ofxUIImageToggle *)e.widget;
		
		if (toggle->getName() == "DWhole"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("DWhole");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "DWhole");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "Whole"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("Whole");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "Whole");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "DHalf"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("DHalf");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "DHalf");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "Half"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("Half");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "Half");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "DQuarter"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("DQuarter");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "DQuarter");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "Quarter"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("Quarter");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "Quarter");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "DEighth"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("DEighth");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "DEighth");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "Eighth"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("Eighth");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "Eighth");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "DSixteenth"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("DSixteenth");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "DSixteenth");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "Sixteenth"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("Sixteenth");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "Sixteenth");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "DThirtySecond"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("DThirtySecond");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "DThirtySecond");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		else if (toggle->getName() == "ThirtySecond"){
			if (toggle->getValue() == true) {
				rhythmicList.push_back("ThirtySecond");
			}
			else{
				vector<string>::iterator result = find(rhythmicList.begin(), rhythmicList.end(), "ThirtySecond");
				if (result != rhythmicList.end()) {
					rhythmicList.erase(result);
				}
			}
			
		}
		
		if(composer->getType() == Serialist){
			
			stringstream sst;
			sst << "Classes: ";
			for (int i = 0; i < rhythmicList.size(); i++) {
				sst << rhythmicList[i] << " ";
			}
			
			cout << sst.str() << endl;
			rhythmicListLabel->setTextString(sst.str());
		}
		
	}
	
	
}

void App::setMidiNote(int note){
	synth.setParameter("midiNumber", note);
}

void App::setIsSilence(bool t){
	if(t == false)
		synth.setParameter("trigger", 1);
	else
		synth.setParameter("trigger", 0);
}

void App::setVolume(float volume){
	
	volume /= 100.0;
	cout<<"volume "<<volume<<endl;
	synth.setParameter("volume", volume);
	
}

void App::setCurrentFigure(Figure *f){
	
	logGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_UP);
	logGUI->addTextArea("text", "\n", OFX_UI_FONT_SMALL);
	logGUI->addTextArea("text", f->getDescription(), OFX_UI_FONT_SMALL);
	logGUI->getRect()->y += 28;
	
	/*stringstream sst;
	sst << f->getDescription() << endl << endl << logText->getTextString();
	
	logText->setTextString(sst.str());*/
	
	
}

void App::addLogMessage(string s){
	
	logGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_UP);
	logGUI->addTextArea("text", "\n", OFX_UI_FONT_SMALL);
	logGUI->addTextArea("text", s, OFX_UI_FONT_SMALL);
	logGUI->getRect()->y += 28;
}

void App::initSynth(){
	
	//SYNTH SETTINGS
	
	ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
	
	ControlGenerator midiNote = synth.addParameter("midiNumber");
	
	ControlGenerator volume = synth.addParameter("volume");
	ControlGenerator trigger = synth.addParameter("trigger");
	synth.setParameter("trigger", 1);
	synth.setParameter("volume", 1.0);
	
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
	synth.setOutputGen( (tone + firstPartial + secondPartial) * volume * ADSR(0.3f, 0.0f, 0.1f, 0.6f).trigger(trigger).legato(1));
	
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
	methodGUI->setPosition(0, 0);
	methodGUI->setWidth(200);
	methodGUI->setHeight(HEIGHT - 200);
	methodGUI->addLabel("METHOD", OFX_UI_FONT_LARGE);
	methodGUI->addSpacer();
	
	vector<string> methods;
	methods.push_back("Independent Stochastic");
	methods.push_back("Markov Chains");
	methods.push_back("Random Walk");
	methods.push_back("Fractional Noise");
	methods.push_back("Chaotic Response");
	methods.push_back("Motivic Development");
	methods.push_back("Serialism");
	
	ofxUIRadio * m = methodGUI->addRadio("Method", methods);
	m->getToggles()[0]->setValue(true);
	ofAddListener(methodGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(methodGUI);
	
	//////////
	
	styleGUI = new ofxUICanvas();
	styleGUI->setFont("GUI/Lekton-Regular.ttf");
	styleGUI->addLabel("STYLE");
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
	
	generalGUI->setPosition(WIDTH - 300, HEIGHT - 200);
	generalGUI->setWidth(300);
	generalGUI->setHeight(200);
	
	generalGUI->setGlobalSliderHeight(24);
	generalGUI->setGlobalButtonDimension(50);
	generalGUI->addLabelButton("COMPOSE", false, 60, 0, 724, 10);
	generalGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	generalGUI->addLabelButton("SAVE", false, 60, 0, 724, 10);
	generalGUI->addImageButton("PLAY", "GUI/play.png", false);
	pauseToggle = generalGUI->addImageToggle("PAUSE", "GUI/pause.png", false);
	generalGUI->addImageButton("STOP", "GUI/stop.png", false);
	generalGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	generalGUI->addSlider("TEMPO", 1, 200, 120);
	generalGUI->addSpacer(0, 1);
	generalGUI->addLabel("Console log", OFX_UI_FONT_SMALL);
	ofAddListener(generalGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(generalGUI);
	
	logGUI = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	logGUI->setFont("GUI/Lekton-Regular.ttf");
	logGUI->setScrollAreaToScreen();
    logGUI->setScrollableDirections(false, true);
	logGUI->setSnapping(false);
	logGUI->setPosition(WIDTH - 300, HEIGHT - 80);
	logGUI->setHeight(80);
	logGUI->setWidth(300);
	ofAddListener(logGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(logGUI);
	
	initialY = logGUI->getRect()->y;
	
	////////////
	
	resultsGui = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	resultsGui->setFont("GUI/Lekton-Regular.ttf");
	resultsGui->setScrollAreaToScreen();
    resultsGui->setScrollableDirections(false, true);
	resultsGui->setSnapping(false);
	
	resultsGui->setPosition(0, HEIGHT - 200);
	resultsGui->setHeight(200);
	resultsGui->setWidth(WIDTH - 300);
	ofAddListener(resultsGui->newGUIEvent, this, &App::guiEvent);
	//currentFigureLabel = resultsGui->addTextArea("textarea", textString, OFX_UI_FONT_MEDIUM);
	guis.push_back(resultsGui);
	
	
	/////////////
	
	optionsGUI = new ofxUICanvas();
	optionsGUI->setPosition(200, 0);
	optionsGUI->setWidth(WIDTH - 200);
	optionsGUI->setHeight(40);
	optionsGUI->setFont("GUI/Lekton-Regular.ttf");
	optionsGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	optionsGUI->addSpacer();
	ofAddListener(optionsGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(optionsGUI);
	
	
	
	
	/* INDEPENDENT STOCHASTIC GUIs */
	
	///////////
	
	isGUI1 = new ofxUICanvas();
	isGUI1->setFont("GUI/Lekton-Regular.ttf");
	isGUI1->setHeight(360);
	isGUI1->setWidth(200);
	isGUI1->setPosition(210, 40);
	
	isGUI1->addLabel("MUSICAL PARAMETERS");
	isGUI1->addRangeSlider("Octaves", 1, 6, 2, 4);
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
	
	ofAddListener(isGUI1->newGUIEvent, this, &App::guiEvent);
	guis.push_back(isGUI1);
	
	
	//////////////////
	
	
	isGUI2 = new ofxUIScrollableCanvas();
	
	isGUI2->setScrollArea(410, 40, 360, 210);
    isGUI2->setScrollableDirections(false, true);
	isGUI2->setFont("GUI/Lekton-Regular.ttf");
	isGUI2->setPosition(410, 40);
	isGUI2->setSnapping(false);
	
	vector<string> scales(NamesOfScales, NamesOfScales + sizeof(NamesOfScales) / sizeof(string));
	scaleRadioButtons = isGUI2->addRadio("Scale", scales);
	scaleRadioButtons->getToggles()[0]->setValue(true);
	
	isGUI2->autoSizeToFitWidgets();
	isGUI2->getRect()->setWidth(210);
	isGUI2->getRect()->setHeight(360);
	isGUI2->setWidth(210);
	isGUI2->setHeight(360);
	ofAddListener(isGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(isGUI2);
	
	
	///////////////
	
	isGUI3 = new ofxUICanvas();
	isGUI3->setFont("GUI/Lekton-Regular.ttf");
	isGUI3->setPosition(620, 40);
	isGUI3->setWidth(391);
	isGUI3->setHeight(85);
	isGUI3->addLabel("DISTRIBUTIONS");
	isGUI3->addLabelButton("PITCHES", false);
	isGUI3->addLabelButton("DURATIONS", false);
	isGUI3->addLabelButton("NOTES-SILENCES", false);
	ofAddListener(isGUI3->newGUIEvent, this, &App::guiEvent);
	guis.push_back(isGUI3);
	
	
	////////////
	
	vector<float> distribution;
	for (int i = 0; i < 10; i++) {
		distribution.push_back(0.0);
	}
	distributionGUI = new ofxUICanvas();
	distributionGUI->setFont("GUI/Lekton-Regular.ttf");
	distributionGUI->setPosition(800, 125);
	distributionGUI->addLabel("PITCHES", OFX_UI_FONT_MEDIUM);
	distributionGUI->addLabel("Based on 1000 samples", OFX_UI_FONT_SMALL);
	mg = distributionGUI->addMovingGraph("distribution", distribution, 10, 0.0, 25.0, 50);
	distributionGUI->addSpacer();
	distributionGUI->autoSizeToFitWidgets();
	guis.push_back(distributionGUI);
	
	distributionGUI2 = new ofxUICanvas();
	distributionGUI2->setFont("GUI/Lekton-Regular.ttf");
	distributionGUI2->setPosition(800, 125);
	distributionGUI2->addLabel("DURATIONS", OFX_UI_FONT_MEDIUM);
	distributionGUI2->addLabel("Based on 1000 samples", OFX_UI_FONT_SMALL);
	mg2 = distributionGUI2->addMovingGraph("distribution", distribution, 10, 0.0, 25.0, 50);
	distributionGUI2->addSpacer();
	distributionGUI2->autoSizeToFitWidgets();
	guis.push_back(distributionGUI2);
	distributionGUI2->setVisible(false);
	
	distributionGUI3 = new ofxUICanvas();
	distributionGUI3->setFont("GUI/Lekton-Regular.ttf");
	distributionGUI3->setPosition(800, 125);
	distributionGUI3->addLabel("NOTES-SILENCES", OFX_UI_FONT_MEDIUM);
	distributionGUI3->addLabel("Based on 1000 samples", OFX_UI_FONT_SMALL);
	mg3 = distributionGUI3->addMovingGraph("distribution", distribution, 10, 0.0, 25.0, 50);
	distributionGUI3->addSpacer();
	distributionGUI3->autoSizeToFitWidgets();
	guis.push_back(distributionGUI3);
	distributionGUI3->setVisible(false);
	
	/////////////
	
	distributionListGUI = new ofxUICanvas();
	distributionListGUI->setFont("GUI/Lekton-Regular.ttf");
	distributionListGUI->setPosition(620, 125);
	distributionListGUI->setWidth(180);
	vector<string> distributions;
	distributions.push_back("Fixed");
	distributions.push_back("Uniform");
	distributions.push_back("Linear");
	distributions.push_back("Triangular");
	distributions.push_back("Exponential");
	distributions.push_back("Gaussian");
	distributions.push_back("Cauchy");
	distributions.push_back("Beta");
	distributions.push_back("Weibull");
	distributions.push_back("Poisson");
	
	ofxUIRadio * dis = distributionListGUI->addRadio("Distribution", distributions);
	dis->getToggles()[1]->setValue(true);
	setValuesForGraph(uniform);
	ofAddListener(distributionListGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(distributionListGUI);
	
	////////////
	
	fixedGUI = new ofxUICanvas();
	fixedGUI->setFont("GUI/Lekton-Regular.ttf");
	fixedGUI->setPosition(800, 235);
	fixedGUI->addLabel("FIXED PITCHES", OFX_UI_FONT_LARGE);
	fixedGUI->addSlider("Pitch", 36.0, 107.0, 60.0);
	fixedGUI->autoSizeToFitWidgets();
	fixedGUI->setWidth(211);
	fixedGUI->setVisible(false);
	ofAddListener(fixedGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(fixedGUI);
	
	fixedGUI2 = new ofxUICanvas();
	fixedGUI2->setFont("GUI/Lekton-Regular.ttf");
	fixedGUI2->setPosition(800, 235);
	fixedGUI2->addLabel("FIXED DURATIONS", OFX_UI_FONT_LARGE);
	
	vector<string> figure;
	figure.push_back("Dotted Whole");
	figure.push_back("Whole");
	figure.push_back("Dotted Half");
	figure.push_back("Half");
	figure.push_back("Dotted Quarter");
	figure.push_back("Quarter");
	figure.push_back("Dotted Eighth");
	figure.push_back("Eighth");
	figure.push_back("Dotted Sixteenth");
	figure.push_back("Sixteenth");
	figure.push_back("Dotted ThirtySecond");
	figure.push_back("ThirtySecond");
	figure.push_back("SixtyFourth");
	
	fixedGUI2->addRadio("Fixed Duration", figure);
	
	fixedGUI2->autoSizeToFitWidgets();
	fixedGUI2->setWidth(211);
	fixedGUI2->setVisible(false);
	
	ofAddListener(fixedGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(fixedGUI2);
	
	
		
	linearDistGUI = new ofxUICanvas();
	linearDistGUI->setFont("GUI/Lekton-Regular.ttf");
	linearDistGUI->setPosition(800, 235);
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
	
	linearDistGUI2 = new ofxUICanvas();
	linearDistGUI2->setFont("GUI/Lekton-Regular.ttf");
	linearDistGUI2->setPosition(800, 235);
	linearDistGUI2->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	linearDistGUI2->addRadio("Direction", op1);
	linearDistGUI2->autoSizeToFitWidgets();
	linearDistGUI2->setWidth(211);
	linearDistGUI2->setVisible(false);
	ofAddListener(linearDistGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(linearDistGUI2);
	linearDistGUI2->setVisible(false);
	
	linearDistGUI3 = new ofxUICanvas();
	linearDistGUI3->setFont("GUI/Lekton-Regular.ttf");
	linearDistGUI3->setPosition(800, 235);
	linearDistGUI3->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	linearDistGUI3->addRadio("Direction", op1);
	linearDistGUI3->autoSizeToFitWidgets();
	linearDistGUI3->setWidth(211);
	linearDistGUI3->setVisible(false);
	ofAddListener(linearDistGUI3->newGUIEvent, this, &App::guiEvent);
	guis.push_back(linearDistGUI3);
	linearDistGUI3->setVisible(false);
	
	
	
	triangularDistGUI = new ofxUICanvas();
	triangularDistGUI->setFont("GUI/Lekton-Regular.ttf");
	triangularDistGUI->setPosition(800, 235);
	triangularDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	triangularDistGUI->addSlider("Triangle Base", 0.01, 1.0, 1.0);
	triangularDistGUI->autoSizeToFitWidgets();
	triangularDistGUI->setWidth(211);
	triangularDistGUI->setVisible(false);
	ofAddListener(triangularDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(triangularDistGUI);
	
	triangularDistGUI2 = new ofxUICanvas();
	triangularDistGUI2->setFont("GUI/Lekton-Regular.ttf");
	triangularDistGUI2->setPosition(800, 235);
	triangularDistGUI2->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	triangularDistGUI2->addSlider("Triangle Base", 0.01, 1.0, 1.0);
	triangularDistGUI2->autoSizeToFitWidgets();
	triangularDistGUI2->setWidth(211);
	triangularDistGUI2->setVisible(false);
	ofAddListener(triangularDistGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(triangularDistGUI2);
	triangularDistGUI2->setVisible(false);
	
	triangularDistGUI3 = new ofxUICanvas();
	triangularDistGUI3->setFont("GUI/Lekton-Regular.ttf");
	triangularDistGUI3->setPosition(800, 235);
	triangularDistGUI3->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	triangularDistGUI3->addSlider("Triangle Base", 0.01, 1.0, 1.0);
	triangularDistGUI3->autoSizeToFitWidgets();
	triangularDistGUI3->setWidth(211);
	triangularDistGUI3->setVisible(false);
	ofAddListener(triangularDistGUI3->newGUIEvent, this, &App::guiEvent);
	guis.push_back(triangularDistGUI3);
	triangularDistGUI3->setVisible(false);
	
	
	
	exponentialDistGUI = new ofxUICanvas();
	exponentialDistGUI->setFont("GUI/Lekton-Regular.ttf");
	exponentialDistGUI->setPosition(800, 235);
	exponentialDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	exponentialDistGUI->addSlider("Lambda", 0.5, 10.0, 1.0);
	exponentialDistGUI->autoSizeToFitWidgets();
	exponentialDistGUI->setWidth(211);
	exponentialDistGUI->setVisible(false);
	ofAddListener(exponentialDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(exponentialDistGUI);
	
	exponentialDistGUI2 = new ofxUICanvas();
	exponentialDistGUI2->setFont("GUI/Lekton-Regular.ttf");
	exponentialDistGUI2->setPosition(800, 235);
	exponentialDistGUI2->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	exponentialDistGUI2->addSlider("Lambda", 0.5, 10.0, 1.0);
	exponentialDistGUI2->autoSizeToFitWidgets();
	exponentialDistGUI2->setWidth(211);
	exponentialDistGUI2->setVisible(false);
	ofAddListener(exponentialDistGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(exponentialDistGUI2);
	exponentialDistGUI2->setVisible(false);
	
	exponentialDistGUI3 = new ofxUICanvas();
	exponentialDistGUI3->setFont("GUI/Lekton-Regular.ttf");
	exponentialDistGUI3->setPosition(800, 235);
	exponentialDistGUI3->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	exponentialDistGUI3->addSlider("Lambda", 0.5, 10.0, 1.0);
	exponentialDistGUI3->autoSizeToFitWidgets();
	exponentialDistGUI3->setWidth(211);
	exponentialDistGUI3->setVisible(false);
	ofAddListener(exponentialDistGUI3->newGUIEvent, this, &App::guiEvent);
	guis.push_back(exponentialDistGUI3);
	exponentialDistGUI3->setVisible(false);
	
	
	
	gaussDistGUI = new ofxUICanvas();
	gaussDistGUI->setFont("GUI/Lekton-Regular.ttf");
	gaussDistGUI->setPosition(800, 235);
	gaussDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	gaussDistGUI->addSlider("Sigma", 0.01, 1.0, 0.15);
	gaussDistGUI->addSlider("Mu", -1.5, 1.5, 0.5);
	gaussDistGUI->autoSizeToFitWidgets();
	gaussDistGUI->setWidth(211);
	gaussDistGUI->setVisible(false);
	ofAddListener(gaussDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(gaussDistGUI);
	
	gaussDistGUI2 = new ofxUICanvas();
	gaussDistGUI2->setFont("GUI/Lekton-Regular.ttf");
	gaussDistGUI2->setPosition(800, 235);
	gaussDistGUI2->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	gaussDistGUI2->addSlider("Sigma", 0.01, 1.0, 0.15);
	gaussDistGUI2->addSlider("Mu", -1.5, 1.5, 0.5);
	gaussDistGUI2->autoSizeToFitWidgets();
	gaussDistGUI2->setWidth(211);
	gaussDistGUI2->setVisible(false);
	ofAddListener(gaussDistGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(gaussDistGUI2);
	gaussDistGUI2->setVisible(false);
	
	gaussDistGUI3 = new ofxUICanvas();
	gaussDistGUI3->setFont("GUI/Lekton-Regular.ttf");
	gaussDistGUI3->setPosition(800, 235);
	gaussDistGUI3->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	gaussDistGUI3->addSlider("Sigma", 0.01, 1.0, 0.15);
	gaussDistGUI3->addSlider("Mu", -1.5, 1.5, 0.5);
	gaussDistGUI3->autoSizeToFitWidgets();
	gaussDistGUI3->setWidth(211);
	gaussDistGUI3->setVisible(false);
	ofAddListener(gaussDistGUI3->newGUIEvent, this, &App::guiEvent);
	guis.push_back(gaussDistGUI3);
	gaussDistGUI3->setVisible(false);
	
	
	
	cauchyDistGUI = new ofxUICanvas();
	cauchyDistGUI->setFont("GUI/Lekton-Regular.ttf");
	cauchyDistGUI->setPosition(800, 235);
	cauchyDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	cauchyDistGUI->addSlider("Alpha", 0.1, 2.5, 1.0);
	cauchyDistGUI->autoSizeToFitWidgets();
	cauchyDistGUI->setWidth(211);
	cauchyDistGUI->setVisible(false);
	ofAddListener(cauchyDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(cauchyDistGUI);
	
	cauchyDistGUI2 = new ofxUICanvas();
	cauchyDistGUI2->setFont("GUI/Lekton-Regular.ttf");
	cauchyDistGUI2->setPosition(800, 235);
	cauchyDistGUI2->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	cauchyDistGUI2->addSlider("Alpha", 0.1, 2.5, 1.0);
	cauchyDistGUI2->autoSizeToFitWidgets();
	cauchyDistGUI2->setWidth(211);
	cauchyDistGUI2->setVisible(false);
	ofAddListener(cauchyDistGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(cauchyDistGUI2);
	cauchyDistGUI2->setVisible(false);
	
	cauchyDistGUI3 = new ofxUICanvas();
	cauchyDistGUI3->setFont("GUI/Lekton-Regular.ttf");
	cauchyDistGUI3->setPosition(800, 235);
	cauchyDistGUI3->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	cauchyDistGUI3->addSlider("Alpha", 0.1, 2.5, 1.0);
	cauchyDistGUI3->autoSizeToFitWidgets();
	cauchyDistGUI3->setWidth(211);
	cauchyDistGUI3->setVisible(false);
	ofAddListener(cauchyDistGUI3->newGUIEvent, this, &App::guiEvent);
	guis.push_back(cauchyDistGUI3);
	cauchyDistGUI3->setVisible(false);
	
	
	
	betaDistGUI = new ofxUICanvas();
	betaDistGUI->setFont("GUI/Lekton-Regular.ttf");
	betaDistGUI->setPosition(800, 235);
	betaDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	betaDistGUI->addSlider("a", 0.1, 4.0, 0.5);
	betaDistGUI->addSlider("b", 0.1, 4.0, 0.5);
	betaDistGUI->autoSizeToFitWidgets();
	betaDistGUI->setWidth(211);
	betaDistGUI->setVisible(false);
	ofAddListener(betaDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(betaDistGUI);
	
	betaDistGUI2 = new ofxUICanvas();
	betaDistGUI2->setFont("GUI/Lekton-Regular.ttf");
	betaDistGUI2->setPosition(800, 235);
	betaDistGUI2->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	betaDistGUI2->addSlider("a", 0.1, 4.0, 0.5);
	betaDistGUI2->addSlider("b", 0.1, 4.0, 0.5);
	betaDistGUI2->autoSizeToFitWidgets();
	betaDistGUI2->setWidth(211);
	betaDistGUI2->setVisible(false);
	ofAddListener(betaDistGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(betaDistGUI2);
	betaDistGUI2->setVisible(false);
	
	betaDistGUI3 = new ofxUICanvas();
	betaDistGUI3->setFont("GUI/Lekton-Regular.ttf");
	betaDistGUI3->setPosition(800, 235);
	betaDistGUI3->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	betaDistGUI3->addSlider("a", 0.1, 4.0, 0.5);
	betaDistGUI3->addSlider("b", 0.1, 4.0, 0.5);
	betaDistGUI3->autoSizeToFitWidgets();
	betaDistGUI3->setWidth(211);
	betaDistGUI3->setVisible(false);
	ofAddListener(betaDistGUI3->newGUIEvent, this, &App::guiEvent);
	guis.push_back(betaDistGUI3);
	betaDistGUI3->setVisible(false);
	
	
	
	weibullDistGUI = new ofxUICanvas();
	weibullDistGUI->setFont("GUI/Lekton-Regular.ttf");
	weibullDistGUI->setPosition(800, 235);
	weibullDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	weibullDistGUI->addSlider("T", 0.1, 10.0, 1.0);
	weibullDistGUI->addSlider("S", 0.1, 3.0, 1.0);
	weibullDistGUI->autoSizeToFitWidgets();
	weibullDistGUI->setWidth(211);
	weibullDistGUI->setVisible(false);
	ofAddListener(weibullDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(weibullDistGUI);
	
	weibullDistGUI2 = new ofxUICanvas();
	weibullDistGUI2->setFont("GUI/Lekton-Regular.ttf");
	weibullDistGUI2->setPosition(800, 235);
	weibullDistGUI2->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	weibullDistGUI2->addSlider("T", 0.1, 10.0, 1.0);
	weibullDistGUI2->addSlider("S", 0.1, 3.0, 1.0);
	weibullDistGUI2->autoSizeToFitWidgets();
	weibullDistGUI2->setWidth(211);
	weibullDistGUI2->setVisible(false);
	ofAddListener(weibullDistGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(weibullDistGUI2);
	weibullDistGUI2->setVisible(false);
	
	weibullDistGUI3 = new ofxUICanvas();
	weibullDistGUI3->setFont("GUI/Lekton-Regular.ttf");
	weibullDistGUI3->setPosition(800, 235);
	weibullDistGUI3->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	weibullDistGUI3->addSlider("T", 0.1, 10.0, 1.0);
	weibullDistGUI3->addSlider("S", 0.1, 3.0, 1.0);
	weibullDistGUI3->autoSizeToFitWidgets();
	weibullDistGUI3->setWidth(211);
	weibullDistGUI3->setVisible(false);
	ofAddListener(weibullDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(weibullDistGUI);
	weibullDistGUI3->setVisible(false);
	
	
	
	
	poissonDistGUI = new ofxUICanvas();
	poissonDistGUI->setFont("GUI/Lekton-Regular.ttf");
	poissonDistGUI->setPosition(800, 235);
	poissonDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	poissonDistGUI->addSlider("lambda", 0.1, 100.0, 100.0);
	poissonDistGUI->autoSizeToFitWidgets();
	poissonDistGUI->setWidth(211);
	poissonDistGUI->setVisible(false);
	ofAddListener(poissonDistGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(poissonDistGUI);
	
	poissonDistGUI2 = new ofxUICanvas();
	poissonDistGUI2->setFont("GUI/Lekton-Regular.ttf");
	poissonDistGUI2->setPosition(800, 235);
	poissonDistGUI2->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	poissonDistGUI2->addSlider("lambda", 0.1, 100.0, 100.0);
	poissonDistGUI2->autoSizeToFitWidgets();
	poissonDistGUI2->setWidth(211);
	poissonDistGUI2->setVisible(false);
	ofAddListener(poissonDistGUI2->newGUIEvent, this, &App::guiEvent);
	guis.push_back(poissonDistGUI2);
	poissonDistGUI2->setVisible(false);
	
	poissonDistGUI3 = new ofxUICanvas();
	poissonDistGUI3->setFont("GUI/Lekton-Regular.ttf");
	poissonDistGUI3->setPosition(800, 235);
	poissonDistGUI3->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	poissonDistGUI3->addSlider("lambda", 0.1, 100.0, 100.0);
	poissonDistGUI3->autoSizeToFitWidgets();
	poissonDistGUI3->setWidth(211);
	poissonDistGUI3->setVisible(false);
	ofAddListener(poissonDistGUI3->newGUIEvent, this, &App::guiEvent);
	guis.push_back(poissonDistGUI3);
	poissonDistGUI3->setVisible(false);
	
	
	/* MARKOV CHAINS */
	
	mcGUI1 = new ofxUICanvas();
	mcGUI1->setFont("GUI/Lekton-Regular.ttf");
	mcGUI1->setHeight(360);
	mcGUI1->setWidth(200);
	mcGUI1->setPosition(210, 40);
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
	
	mcGUI1->addSlider("Octave", 1, 6, 3);
	
	mcGUI1->addLabel("Starting Note", OFX_UI_FONT_SMALL);
	vector<string> start;
	start.push_back("C"); start.push_back("C#"); start.push_back("D"); start.push_back("D#"); start.push_back("E"); start.push_back("F"); start.push_back("F#");
	start.push_back("G"); start.push_back("G#"); start.push_back("A"); start.push_back("A#"); start.push_back("B");
	ofxUIRadio * sR = mcGUI1->addRadio("Starting Note", start);
	
	mcGUI1->autoSizeToFitWidgets();
	guis.push_back(mcGUI1);
	ofAddListener(mcGUI1->newGUIEvent, this, &App::guiEvent);
	
	showMarkovChainsGUI(false);
	
	
	/* RANDOM WALKS */
	
	rwGUI= new ofxUICanvas();
	rwGUI->setFont("GUI/Lekton-Regular.ttf");
	rwGUI->setHeight(360);
	rwGUI->setWidth(200);
	rwGUI->setPosition(210, 40);
	rwGUI->addLabel("MUSICAL PARAMETERS", OFX_UI_FONT_MEDIUM);
	
	rwGUI->addRangeSlider("Octaves", 1, 6, 2, 4);
	
	rwGUI->addSlider("Stems", 1, 20, 1);
	
	rwGUI->addLabel("Meter", OFX_UI_FONT_SMALL);
	mR = rwGUI->addRadio("Meter", meter, OFX_UI_ORIENTATION_HORIZONTAL);
	mR->getToggles()[0]->setValue(true);
	
	rwGUI->addLabel("Pattern", OFX_UI_FONT_SMALL);
	pR = rwGUI->addRadio("Pattern", pattern, OFX_UI_ORIENTATION_HORIZONTAL);
	pR->getToggles()[2]->setValue(true);
	
	rwGUI->addLabel("Figure", OFX_UI_FONT_SMALL);
	
	rwGUI->addRadio("Figure", figure);
	
	rwGUI->setVisible(false);
	rwGUI->autoSizeToFitWidgets();
	guis.push_back(rwGUI);
	ofAddListener(rwGUI->newGUIEvent, this, &App::guiEvent);
	
	
	/* MOTIVIC DEVELOPMENT */
	
	mdGUI0 = new ofxUIScrollableCanvas();
	mdGUI0->setFont("GUI/Lekton-Regular.ttf");
	mdGUI0->setPosition(200, 40);
	mdGUI0->addLabel("SET MOTIVE");
	mdGUI0->addSpacer();
	mdGUI0->setSnapping(false);
	
	
	mdGUI0->addLabel("GENERATE RANDOM MOTIVE", OFX_UI_FONT_SMALL);
	mdGUI0->addSlider("Figures", 0, 10, 5);
	mdGUI0->addRangeSlider("Octaves", 1, 6, 3, 4);
	mdGUI0->addLabelButton("Generate", false);
	
	mdGUI0->addSpacer(0, 5);

	mdGUI0->addLabel("PICK MOTIVE FROM FILE", OFX_UI_FONT_SMALL);
	mdGUI0->addLabelButton("Select .mid file", false);
	
	mdGUI0->addSpacer(0, 5);
	
	mdGUI0->addLabel("SET MANUAL MOTIVE", OFX_UI_FONT_SMALL);
	
	vector<string> notesilence;
	notesilence.push_back("Note");
	notesilence.push_back("Silence");
	
	mdGUI0->addRadio("Type", notesilence);
	
	mdGUI0->addSpacer(0, 2);
	
	mdGUI0->addRadio("Duration", figure);
	mdGUI0->addSlider("Pitch", 36.0, 107.0, 60.0);
	mdGUI0->addSlider("Velocity", 0.0, 100.0, 50.0);
	mdGUI0->addLabelButton("Add figure", false);
	mdGUI0->addLabelButton("Reset Motive", false);
	
	mdGUI0->autoSizeToFitWidgets();
	mdGUI0->setHeight(550);
	mdGUI0->setVisible(false);
	guis.push_back(mdGUI0);
	ofAddListener(mdGUI0->newGUIEvent, this, &App::guiEvent);
	
	
	mdGUI1 = new ofxUICanvas();
	mdGUI1->setFont("GUI/Lekton-Regular.ttf");
	mdGUI1->setPosition(411, 40);
	mdGUI1->addLabel("TRANSFORMATIONS");
	mdGUI1->addSpacer();
	
	mdGUI1->addLabel("REPETITION", OFX_UI_FONT_SMALL);
	mdGUI1->addLabelButton("Add repetition", false);
	
	mdGUI1->addSpacer(0, 2);

	
	mdGUI1->addLabel("TRANSPOSE", OFX_UI_FONT_SMALL);
	mdGUI1->addSlider("Transpose steps (st)", -12.0, 12.0, 0.0);
	mdGUI1->addLabelButton("Add transpose", false);
	
	mdGUI1->addSpacer(0, 2);
	
	mdGUI1->addLabel("EXPAND", OFX_UI_FONT_SMALL);
	mdGUI1->addSlider("Expand steps (st)", -12.0, 12.0, 0.0);
	mdGUI1->addLabelButton("Add expand", false);
	
	mdGUI1->addSpacer(0, 2);
	
	mdGUI1->addLabel("INVERT", OFX_UI_FONT_SMALL);
	mdGUI1->addLabelButton("Add invert", false);
	
	mdGUI1->addSpacer(0, 2);
	
	mdGUI1->addLabel("RETROGRADE", OFX_UI_FONT_SMALL);
	mdGUI1->addLabelButton("Add retrograde", false);
	
	mdGUI1->addSpacer(0, 2);
	
	mdGUI1->addLabel("REGISTER DISPLACEMENT", OFX_UI_FONT_SMALL);
	mdGUI1->addSlider("1", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	mdGUI1->addSlider("2", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->addSlider("3", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->addSlider("4", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->addSlider("5", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->addSlider("6", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->addSlider("7", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->addSlider("8", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->addSlider("9", -3.0, +3.0, 0.0, 17, 90);
	mdGUI1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
	mdGUI1->addLabelButton("Add register displacement", false);
	
	mdGUI1->addSpacer(0, 2);
	
	mdGUI1->addLabel("RHYTHM EXPAND", OFX_UI_FONT_SMALL);
	mdGUI1->addSlider("Factor", -4.0, 4.0, 0.0);
	mdGUI1->addLabelButton("Add rhythm expand", false);
	
	mdGUI1->autoSizeToFitWidgets();
	mdGUI1->setVisible(false);
	guis.push_back(mdGUI1);
	ofAddListener(mdGUI1->newGUIEvent, this, &App::guiEvent);
	
	
	mdGUI3 = new ofxUICanvas();
	mdGUI3->setFont("GUI/Lekton-Regular.ttf");
	mdGUI3->setPosition(622, 40);
	mdGUI3->addLabel("DEVELOPMENT SEQUENCE");
	mdGUI3->addSpacer();
	
	mdGUI3->addLabelButton("Reset", false);
	
	mdGUI3->autoSizeToFitWidgets();
    mdGUI3->setHeight(400);
	mdGUI3->setVisible(false);
	guis.push_back(mdGUI3);
	ofAddListener(mdGUI3->newGUIEvent, this, &App::guiEvent);
	
	
	/* SERIAL COMPOSER */
	
	sGUI0 = new ofxUICanvas();
	sGUI0->setFont("GUI/Lekton-Regular.ttf");
	sGUI0->setPosition(200, 40);
	sGUI0->addLabel("SERIES");
	sGUI0->addSpacer(420, 1);
	
	sGUI0->addLabel("MELODIC CLASSES", OFX_UI_FONT_SMALL);
	
	sGUI0->addLabelToggle("Set Fixed Pitches", false);
	
	sGUI0->addSlider("Octave", 1, 6, 3);
	
	sGUI0->addLabelToggle("C", false, 28, 28);
	sGUI0->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	sGUI0->addLabelToggle("C#", false, 28, 28);
	sGUI0->addLabelToggle("D", false, 28, 28);
	sGUI0->addLabelToggle("D#", false, 28, 28);
	sGUI0->addLabelToggle("E", false, 28, 28);
	sGUI0->addLabelToggle("F", false, 28, 28);
	sGUI0->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	sGUI0->addLabelToggle("F#", false, 28, 28);
	sGUI0->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	sGUI0->addLabelToggle("G", false, 28, 28);
	sGUI0->addLabelToggle("G#", false, 28, 28);
	sGUI0->addLabelToggle("A", false, 28, 28);
	sGUI0->addLabelToggle("A#", false, 28, 28);
	sGUI0->addLabelToggle("B", false, 28, 28);
	sGUI0->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
	melodicListLabel = sGUI0->addTextArea("Classes: ", "Classes: ", OFX_UI_FONT_SMALL);
	sGUI0->addSpacer(0, 10);
	
	sGUI0->addLabelButton("Reset Melodic Classes", false);
	sGUI0->addLabelButton("Set Melodic Classes", false);
	
	sGUI0->addSpacer(0, 10);
	
	sGUI0->addLabel("RHYTHMIC CLASSES", OFX_UI_FONT_SMALL);
	
	sGUI0->addLabelToggle("Set Fixed Rhythm", false);
	
	sGUI0->addImageToggle("DWhole", "GUI/Notes/dwhole.png", false, 24, 24);
	sGUI0->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	sGUI0->addImageToggle("Whole", "GUI/Notes/whole.png", false, 24, 24);
	sGUI0->addImageToggle("DHalf", "GUI/Notes/udhalf.png", false, 24, 24);
	sGUI0->addImageToggle("Half", "GUI/Notes/uhalf.png", false, 24, 24);
	sGUI0->addImageToggle("DQuarter", "GUI/Notes/udquarter.png", false, 24, 24);
	sGUI0->addImageToggle("Quarter", "GUI/Notes/uquarter.png", false, 24, 24);
	sGUI0->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	sGUI0->addImageToggle("DEighth", "GUI/Notes/udeighth.png", false, 24, 24);
	sGUI0->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	sGUI0->addImageToggle("Eighth", "GUI/Notes/ueighth.png", false, 24, 24);
	sGUI0->addImageToggle("DSixteenth", "GUI/Notes/udsixteenth.png", false, 24, 24);
	sGUI0->addImageToggle("Sixteenth", "GUI/Notes/usixteenth.png", false, 24, 24);
	sGUI0->addImageToggle("DThirtySecond", "GUI/Notes/udthirtysecond.png", false, 24, 24);
	sGUI0->addImageToggle("ThirtySecond", "GUI/Notes/uthirtysecond.png", false, 24, 24);
	sGUI0->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
	rhythmicListLabel = sGUI0->addTextArea("Classes: ", "Classes: ", OFX_UI_FONT_SMALL);
	sGUI0->addSpacer(0, 40);
	
	sGUI0->addLabelButton("Reset Rhythmic Classes", false);
	sGUI0->addLabelButton("Set Rhythmic Classes", false);
	
	
	sGUI1 = new ofxUICanvas();
	sGUI1->setFont("GUI/Lekton-Regular.ttf");
	sGUI1->setPosition(415, 65);
	sGUI1->addLabel("SERIES", OFX_UI_FONT_SMALL);
	
	/*vector<string> options;
	 options.push_back("Manual");
	 options.push_back("Random");
	 
	 ofxUIRadio * r = sGUI1->addRadio("Series", options);
	 r->getToggles()[0]->setValue(true);*/
	
	sGUI1->addLabelToggle("0", false, 28, 28);
	sGUI1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	sGUI1->addLabelToggle("1", false, 28, 28);
	sGUI1->addLabelToggle("2", false, 28, 28);
	sGUI1->addLabelToggle("3", false, 28, 28);
	sGUI1->addLabelToggle("4", false, 28, 28);
	sGUI1->addLabelToggle("5", false, 28, 28);
	sGUI1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	sGUI1->addLabelToggle("6", false, 28, 28);
	sGUI1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	sGUI1->addLabelToggle("7", false, 28, 28);
	sGUI1->addLabelToggle("8", false, 28, 28);
	sGUI1->addLabelToggle("9", false, 28, 28);
	sGUI1->addLabelToggle("10", false, 28, 28);
	sGUI1->addLabelToggle("11", false, 28, 28);
	sGUI1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
	seriesListLabel = sGUI1->addTextArea("Series: ", "Series: ", OFX_UI_FONT_SMALL);
	sGUI1->addSpacer(0, 10);
	
	sGUI1->addLabelButton("Reset Series", false);
	sGUI1->addLabelButton("Set Series", false);
	
	
	sGUI0->autoSizeToFitWidgets();
	sGUI0->setVisible(false);
	guis.push_back(sGUI0);
	ofAddListener(sGUI0->newGUIEvent, this, &App::guiEvent);
	
	sGUI1->autoSizeToFitWidgets();
	sGUI1->setVisible(false);
	guis.push_back(sGUI1);
	ofAddListener(sGUI1->newGUIEvent, this, &App::guiEvent);
	
	
	sGUI2 = new ofxUICanvas();
	sGUI2->setFont("GUI/Lekton-Regular.ttf");
	sGUI2->setPosition(624, 40);
	sGUI2->addLabel("SEQUENCE");
	sGUI2->addSpacer(379, 1);
	
	sGUI2->addLabel("TRANSPOSE [T(s)]", OFX_UI_FONT_SMALL);
	sGUI2->addSlider("Steps", 0.0, 12.0, 0.0, 150, 20);
	
	vector<string> affects;
	affects.push_back("Pitches");
	affects.push_back("Rhythm");
	
	ofxUIRadio * r = sGUI2->addRadio("Transpose Affects", affects);
	r->setAllowMultiple(true);
	sGUI2->addLabelButton("Add Transpose", false, 150.0f);
	
	sGUI2->addSpacer(0, 4);
	sGUI2->addLabel("INVERSION [I]", OFX_UI_FONT_SMALL);
	r = sGUI2->addRadio("Inversion Affects", affects);
	r->setAllowMultiple(true);
	sGUI2->addLabelButton("Add Inversion", false, 150.0f);
	
	sGUI2->addSpacer(0, 4);
	sGUI2->addLabel("RETROGRADE [R]", OFX_UI_FONT_SMALL);
	r = sGUI2->addRadio("Retrograde Affects", affects);
	r->setAllowMultiple(true);
	sGUI2->addLabelButton("Add Retrograde", false, 150.0f);
	
	sGUI2->addSpacer(0, 4);
	sGUI2->addLabel("RETROGRADE INVERSION [RI]", OFX_UI_FONT_SMALL);
	r = sGUI2->addRadio("Retrograde Inversion Affects", affects);
	r->setAllowMultiple(true);
	sGUI2->addLabelButton("Add Retrograde Inversion", false, 150.0f);
	
	sGUI2->autoSizeToFitWidgets();
	sGUI2->setVisible(false);
	guis.push_back(sGUI2);
	ofAddListener(sGUI2->newGUIEvent, this, &App::guiEvent);
	
	sGUI3 = new ofxUICanvas();
	sGUI3->setFont("GUI/Lekton-Regular.ttf");
	sGUI3->setPosition(800, 65);
	sGUI3->addLabelButton("Reset", false);
	
	sGUI3->autoSizeToFitWidgets();
	sGUI3->setHeight(400);
	sGUI3->setVisible(false);
	guis.push_back(sGUI3);
	ofAddListener(sGUI3->newGUIEvent, this, &App::guiEvent);
	
	
	
	/* FRACTIONAL NOISE COMPOSER */
	
	fsGUI0 = new ofxUICanvas();
	fsGUI0->setFont("GUI/Lekton-Regular.ttf");
	fsGUI0->setPosition(200, 40);
	fsGUI0->addLabel("NOISE");
	fsGUI0->addSpacer();
	
	fsGUI0->addSlider("Alpha", 0.0, 2.0, 1.0);
	
	fsGUI0->addSpacer(0, 5);
	
	vector<string> affectsPitches;
	affectsPitches.push_back("Affects pitches");
	affectsPitches.push_back("Fixed pitches");
	
	fsGUI0->addLabel("PITCHES");
	ofxUIRadio * fsr = fsGUI0->addRadio("PAffects", affectsPitches);
	fsr->getToggles()[0]->setValue(true);
	
	fsPitchesSlider = fsGUI0->addSlider("Pitch", 36.0, 107.0, 60.0);
	fsPitchesSlider->setVisible(false);
	
	fsGUI0->addSpacer(0, 10);
	
	affectsPitches.clear();
	affectsPitches.push_back("Affects durations");
	affectsPitches.push_back("Fixed durations");
	
	fsGUI0->addLabel("DURATIONS");
	fsr = fsGUI0->addRadio("DAffects", affectsPitches);
	fsr->getToggles()[0]->setValue(true);
	
	fsGUI0->addSpacer(0, 2);
	fsDurationsRadio = fsGUI0->addRadio("FSDuration", figure);

	
	fsGUI0->autoSizeToFitWidgets();
	
	fsDurationsRadio->setVisible(false);
	
	fsGUI0->setVisible(false);
	guis.push_back(fsGUI0);
	ofAddListener(fsGUI0->newGUIEvent, this, &App::guiEvent);
	
	
	fsGUI1 = new ofxUICanvas();
	fsGUI1->setFont("GUI/Lekton-Regular.ttf");
	fsGUI1->setPosition(410, 40);
	fsGUI1->addLabel("MUSICAL PARAMETERS");
	fsGUI1->addSpacer();
	
	fsGUI1->addRangeSlider("Octaves", 1, 6, 1, 6);
	fsGUI1->addSlider("Stems", 1, 20, 1);
	fsGUI1->addSpacer(210, 3);
	
	
	fsGUI1->addLabel("Meter", OFX_UI_FONT_SMALL);
	mR = fsGUI1->addRadio("Meter", meter, OFX_UI_ORIENTATION_HORIZONTAL);
	mR->getToggles()[0]->setValue(true);

	fsGUI1->addLabel("Pattern", OFX_UI_FONT_SMALL);
	pR = fsGUI1->addRadio("Pattern", pattern, OFX_UI_ORIENTATION_HORIZONTAL);
	pR->getToggles()[2]->setValue(true);
	
	fsGUI1->addSpacer(0, 3);
	fsGUI1->addLabel("Scale", OFX_UI_FONT_SMALL);

	fsGUI1->setVisible(false);
	guis.push_back(fsGUI1);
	ofAddListener(fsGUI1->newGUIEvent, this, &App::guiEvent);
	
	fsGUI2 = new ofxUIScrollableCanvas();
	
	fsGUI2->setScrollArea(410, 40, 360, 210);
    fsGUI2->setScrollableDirections(false, true);
	fsGUI2->setFont("GUI/Lekton-Regular.ttf");
	fsGUI2->setPosition(410, 233);
	fsGUI2->setSnapping(false);

	scaleRadioButtons = fsGUI2->addRadio("Scale", scales);
	scaleRadioButtons->getToggles()[0]->setValue(true);
	
	fsGUI2->autoSizeToFitWidgets();
	fsGUI2->getRect()->setWidth(210);
	fsGUI2->getRect()->setHeight(360);
	fsGUI2->setWidth(210);
	fsGUI2->setHeight(360);
	
	fsGUI2->setVisible(false);
	guis.push_back(fsGUI2);
	ofAddListener(fsGUI2->newGUIEvent, this, &App::guiEvent);
	
	
	
	/* CHAOTIC RESPONSE GUI */
	
	crGUI0 = new ofxUICanvas();
	crGUI0->setFont("GUI/Lekton-Regular.ttf");
	crGUI0->setPosition(200, 40);
	crGUI0->addLabel("FUNCTION");
	crGUI0->addSpacer();

	crGUI0->addSlider("Iterations", 1.0, 1000.0, 10.0);
	
	vector<string> functions;
	functions.push_back("Logistic Map (1D)");
	functions.push_back("Mandelbrot Set (1D)");
	functions.push_back("Tent Map (1D)");
	functions.push_back("Henon Map (2D)");
	
	ofxUIRadio * crr = crGUI0->addRadio("CRFunction", functions);
	crr->getToggles()[0]->setValue(true);
	
	crGUI0->setVisible(false);
	guis.push_back(crGUI0);
	ofAddListener(crGUI0->newGUIEvent, this, &App::guiEvent);
	
	///// HERE GOES OPTIONS FOR EVERY FUNCTION
	
	crLogisticGUI = new ofxUICanvas();
	crLogisticGUI->setFont("GUI/Lekton-Regular.ttf");
	crLogisticGUI->setPosition(200, 180);
	
	crLogisticGUI->addSlider("A", 0.0, 4.0, 1.0);
	crLogisticGUI->addSlider("X_0", 0.0, 1.0, 0.01);
	
	crLogisticGUI->setVisible(false);
	guis.push_back(crLogisticGUI);
	ofAddListener(crLogisticGUI->newGUIEvent, this, &App::guiEvent);
	
	
	crMandelbrotGUI = new ofxUICanvas();
	crMandelbrotGUI->setFont("GUI/Lekton-Regular.ttf");
	crMandelbrotGUI->setPosition(200, 180);
	
	crMandelbrotGUI->addSlider("A", -2.0, 1.0, -1.38);
	crMandelbrotGUI->addSlider("X_0", 0.0, 1.0, 0.0);
	
	crMandelbrotGUI->setVisible(false);
	guis.push_back(crMandelbrotGUI);
	ofAddListener(crMandelbrotGUI->newGUIEvent, this, &App::guiEvent);
	
	crTentMapGUI = new ofxUICanvas();
	crTentMapGUI->setFont("GUI/Lekton-Regular.ttf");
	crTentMapGUI->setPosition(200, 180);
	
	crTentMapGUI->addSlider("A", 0.0, 2.0, 1.41);
	crTentMapGUI->addSlider("X_0", -2.0, 2.0, 0.0);
	
	crTentMapGUI->setVisible(false);
	guis.push_back(crTentMapGUI);
	ofAddListener(crTentMapGUI->newGUIEvent, this, &App::guiEvent);

	
	crHenonGUI = new ofxUICanvas();
	crHenonGUI->setFont("GUI/Lekton-Regular.ttf");
	crHenonGUI->setPosition(200, 180);
	
	crHenonGUI->addSlider("A", 0.0, 2.0, 1.4);
	crHenonGUI->addSlider("B", -2.0, 2.0, 0.3);
	crHenonGUI->addSlider("X_0", 0.0, 1.0, 0.6);
	crHenonGUI->addSlider("Y_0", 0.0, 1.0, 0.2);
	
	crHenonGUI->setVisible(false);
	guis.push_back(crHenonGUI);
	ofAddListener(crHenonGUI->newGUIEvent, this, &App::guiEvent);
	
	
	crGUI1 = new ofxUICanvas();
	crGUI1->setFont("GUI/Lekton-Regular.ttf");
	crGUI1->setPosition(410, 40);
	crGUI1->addLabel("MUSICAL PARAMETERS");
	crGUI1->addSpacer();
	
	crGUI1->addRangeSlider("Octaves", 1, 6, 1, 6);
	crGUI1->addSpacer(0, 3);
	crGUI1->addLabel("Scale", OFX_UI_FONT_SMALL);
	
	crGUI1->setVisible(false);
	guis.push_back(crGUI1);
	ofAddListener(crGUI1->newGUIEvent, this, &App::guiEvent);
	
	crGUI2 = new ofxUIScrollableCanvas();
	
	crGUI2->setScrollArea(410, 40, 360, 210);
    crGUI2->setScrollableDirections(false, true);
	crGUI2->setFont("GUI/Lekton-Regular.ttf");
	crGUI2->setPosition(410, 122);
	crGUI2->setSnapping(false);
	
	scaleRadioButtons = crGUI2->addRadio("Scale", scales);
	scaleRadioButtons->getToggles()[0]->setValue(true);
	
	crGUI2->autoSizeToFitWidgets();
	crGUI2->getRect()->setWidth(210);
	crGUI2->getRect()->setHeight(360);
	crGUI2->setWidth(210);
	crGUI2->setHeight(360);
	
	crGUI2->setVisible(false);
	guis.push_back(crGUI2);
	ofAddListener(crGUI2->newGUIEvent, this, &App::guiEvent);
	
	
	
	//// HELP GUIS
	
	isHelpGUI = new ofxUICanvas();
	isHelpGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	isHelpGUI->setFont("GUI/Lekton-Regular.ttf");
	isHelpGUI->addLabel("QUICK HELP", OFX_UI_FONT_LARGE);
	isHelpGUI->addLabel("MUSICAL PARAMETERS");
	isHelpGUI->addSpacer();
	isHelpGUI->addTextArea("", "* Octaves: The range of pitches that the composer can pick.", OFX_UI_FONT_SMALL);
	isHelpGUI->addTextArea("", "* Stems: The number of bars the composition will have.", OFX_UI_FONT_SMALL);
	isHelpGUI->addTextArea("", "* Meter-Pattern: The rhythm pattern of the composition.", OFX_UI_FONT_SMALL);
	isHelpGUI->addTextArea("", "* Scale: Which scale will the compositor use for pick the pitches.", OFX_UI_FONT_SMALL);
	isHelpGUI->addSpacer(0, 4);
	isHelpGUI->addLabel("DISTRIBUTIONS");
	isHelpGUI->addSpacer();
	isHelpGUI->addTextArea("", "There are 9 (plus fixed values) probability density functions that can be modified by it's parameters. You can apply a distribution to pitches, another to durations, and another for selecting notes or silences.", OFX_UI_FONT_SMALL);
	isHelpGUI->setVisible(false);
	isHelpGUI->autoSizeToFitWidgets();
	ofAddListener(isHelpGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(isHelpGUI);
	
	
	mcHelpGUI = new ofxUICanvas();
	mcHelpGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	mcHelpGUI->setFont("GUI/Lekton-Regular.ttf");
	mcHelpGUI->addLabel("QUICK HELP", OFX_UI_FONT_LARGE);
	mcHelpGUI->addTextArea("", "First select a midi file for generating the markov chain from a previous composition.", OFX_UI_FONT_SMALL);
	mcHelpGUI->addSpacer(0, 4);
	mcHelpGUI->addLabel("MUSICAL PARAMETERS");
	mcHelpGUI->addSpacer();
	mcHelpGUI->addTextArea("", "* Stems: The number of bars the composition will have.", OFX_UI_FONT_SMALL);
	mcHelpGUI->addTextArea("", "* Meter-Pattern: The rhythm pattern of the composition.", OFX_UI_FONT_SMALL);
	mcHelpGUI->addTextArea("", "* Octave: The octave of the starting note.", OFX_UI_FONT_SMALL);
	mcHelpGUI->addTextArea("", "* Starting note: The pitch of the starting note.", OFX_UI_FONT_SMALL);
	mcHelpGUI->setVisible(false);
	mcHelpGUI->autoSizeToFitWidgets();
	ofAddListener(mcHelpGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(mcHelpGUI);
	
	rwHelpGUI = new ofxUICanvas();
	rwHelpGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	rwHelpGUI->setFont("GUI/Lekton-Regular.ttf");
	rwHelpGUI->addLabel("QUICK HELP", OFX_UI_FONT_LARGE);
	rwHelpGUI->addLabel("MUSICAL PARAMETERS");
	rwHelpGUI->addSpacer();
	rwHelpGUI->addTextArea("", "* Octaves: The range of pitches that the composer can pick.", OFX_UI_FONT_SMALL);
	rwHelpGUI->addTextArea("", "* Stems: The number of bars the composition will have.", OFX_UI_FONT_SMALL);
	rwHelpGUI->addTextArea("", "* Meter-Pattern: The rhythm pattern of the composition.", OFX_UI_FONT_SMALL);
	rwHelpGUI->addTextArea("", "* Figure: The rhythmic measure of the figure used in the random walk", OFX_UI_FONT_SMALL);
	rwHelpGUI->addTextArea("", "* Scale: The scale used (the first note of the composition is the first note of the picked scale). ", OFX_UI_FONT_SMALL);
	rwHelpGUI->setVisible(false);
	rwHelpGUI->autoSizeToFitWidgets();
	ofAddListener(rwHelpGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(rwHelpGUI);
	
	
	fsHelpGUI = new ofxUICanvas();
	fsHelpGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	fsHelpGUI->setFont("GUI/Lekton-Regular.ttf");
	fsHelpGUI->addLabel("QUICK HELP", OFX_UI_FONT_LARGE);
	fsHelpGUI->addLabel("MUSICAL PARAMETERS");
	fsHelpGUI->addSpacer();
	fsHelpGUI->addTextArea("", "* Octaves: The range of pitches that the composer can pick.", OFX_UI_FONT_SMALL);
	fsHelpGUI->addTextArea("", "* Stems: The number of bars the composition will have.", OFX_UI_FONT_SMALL);
	fsHelpGUI->addTextArea("", "* Meter-Pattern: The rhythm pattern of the composition.", OFX_UI_FONT_SMALL);
	fsHelpGUI->addTextArea("", "* Scale: Which scale will the compositor use for pick the pitches.", OFX_UI_FONT_SMALL);
	fsHelpGUI->addSpacer(0, 4);
	fsHelpGUI->addLabel("NOISE");
	fsHelpGUI->addSpacer();
	fsHelpGUI->addTextArea("", "Alpha: The value of alpha in the 1/f^(alpha) noise. Values next to zero (white noise) generates compositions without any relation of the notes. Values next to two (Brownian noise) generates compositions where only last notes have influence in the next notes. 1/f (alpha = 1) noise (pink noise) generates compositions with 'self-similarity', producing musical patterns similar to past patterns generated by the same noise.", OFX_UI_FONT_SMALL);
	fsHelpGUI->setVisible(false);
	fsHelpGUI->autoSizeToFitWidgets();
	ofAddListener(fsHelpGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(fsHelpGUI);
	
	
	crHelpGUI = new ofxUICanvas();
	crHelpGUI->setFont("GUI/Lekton-Regular.ttf");
	crHelpGUI->addLabel("QUICK HELP", OFX_UI_FONT_LARGE);
	crHelpGUI->addLabel("FUNCTION");
	crHelpGUI->addSpacer();
	crHelpGUI->addTextArea("", "* Iterations: The number of iterations that the function will make (number of notes of the composition).", OFX_UI_FONT_SMALL);
	crHelpGUI->addTextArea("", "* Parameters: Causes many different changes in the functions, generating a unique value output, an oscillating output or a chaotic output. If the function has only one output, it's mapped to the pitches of the notes. If the function has two outputs, they're mapped to the pitches and durations of the notes.", OFX_UI_FONT_SMALL);
	crHelpGUI->addSpacer(0, 4);
	crHelpGUI->addLabel("MUSICAL PARAMETERS");
	crHelpGUI->addSpacer();
	crHelpGUI->addTextArea("", "* Octaves: The range of pitches that the composer can pick.", OFX_UI_FONT_SMALL);
	crHelpGUI->addTextArea("", "* Scale: Which scale will the compositor use for pick the pitches.", OFX_UI_FONT_SMALL);
	crHelpGUI->setVisible(false);
	crHelpGUI->autoSizeToFitWidgets();
	ofAddListener(crHelpGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(crHelpGUI);
	
	mdHelpGUI = new ofxUICanvas();
	mdHelpGUI->setFont("GUI/Lekton-Regular.ttf");
	mdHelpGUI->addLabel("QUICK HELP", OFX_UI_FONT_LARGE);
	
	mdHelpGUI->setVisible(false);
	mdHelpGUI->autoSizeToFitWidgets();
	ofAddListener(mdHelpGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(mdHelpGUI);
	
	
	sHelpGUI = new ofxUICanvas();
	sHelpGUI->setFont("GUI/Lekton-Regular.ttf");
	sHelpGUI->addLabel("QUICK HELP", OFX_UI_FONT_LARGE);
	
	sHelpGUI->setVisible(false);
	sHelpGUI->autoSizeToFitWidgets();
	ofAddListener(sHelpGUI->newGUIEvent,this,&App::guiEvent);
	guis.push_back(sHelpGUI);

	
	setGUITheme(7);

}


void App::setValuesForGraph(Distribution * d){
	
	vector<float> values = d->getValuesForGraphic(1000);
	
	float max = 0.0;
	for(int i = 0; i < values.size(); i++){
		if(values[i] > max)
			max = values[i];
	}
	
	if(selectedDistribution == 1){
		mg->setBuffer(values);
		mg->setMax(max + 5);
	}
	else if (selectedDistribution == 2){
		mg2->setBuffer(values);
		mg2->setMax(max + 5);
	}
	else if (selectedDistribution == 3){
		mg3->setBuffer(values);
		mg3->setMax(max + 5);
	}
	
}


void App::showIndependentStochasticGUI(bool show){
	
	isGUI1->setVisible(show);
	isGUI2->setVisible(show);
	isGUI3->setVisible(show);
	distributionListGUI->setVisible(show);
	distributionGUI->setVisible(show);
	
	if(show == false){
		fixedGUI->setVisible(show);
		fixedGUI2->setVisible(show);
		linearDistGUI->setVisible(show);
		triangularDistGUI->setVisible(show);
		exponentialDistGUI->setVisible(show);
		gaussDistGUI->setVisible(show);
		cauchyDistGUI->setVisible(show);
		betaDistGUI->setVisible(show);
		weibullDistGUI->setVisible(show);
		poissonDistGUI->setVisible(show);
		linearDistGUI2->setVisible(show);
		triangularDistGUI2->setVisible(show);
		exponentialDistGUI2->setVisible(show);
		gaussDistGUI2->setVisible(show);
		cauchyDistGUI2->setVisible(show);
		betaDistGUI2->setVisible(show);
		weibullDistGUI2->setVisible(show);
		poissonDistGUI2->setVisible(show);
		linearDistGUI3->setVisible(show);
		triangularDistGUI3->setVisible(show);
		exponentialDistGUI3->setVisible(show);
		gaussDistGUI3->setVisible(show);
		cauchyDistGUI3->setVisible(show);
		betaDistGUI3->setVisible(show);
		weibullDistGUI3->setVisible(show);
		poissonDistGUI3->setVisible(show);
		
		distributionGUI2->setVisible(show);
		distributionGUI3->setVisible(show);
	}
}

void App::showMarkovChainsGUI(bool show){
	mcGUI1->setVisible(show);
}

void App::showRandomWalkGUI(bool show){
	rwGUI->setVisible(show);
	isGUI2->setVisible(show);
}

void App::showMotivicDevelopmentGUI(bool show){
	
	mdGUI0->setVisible(show);
	mdGUI1->setVisible(show);
	//mdGUI2->setVisible(show);
	mdGUI3->setVisible(show);
}

void App::showSerialGUI(bool show){
	
	sGUI0->setVisible(show);
	sGUI1->setVisible(show);
	sGUI2->setVisible(show);
	sGUI3->setVisible(show);
}

void App::showFractionalNoiseGUI(bool show){
	
	fsGUI0->setVisible(show);
	fsGUI1->setVisible(show);
	fsGUI2->setVisible(show);
	
}

void App::showChaoticResponseGUI(bool show){
	
	crGUI0->setVisible(show);
	crGUI1->setVisible(show);
	crGUI2->setVisible(show);
	crLogisticGUI->setVisible(show);
	
	if (!show) {
		crHenonGUI->setVisible(show);
		crMandelbrotGUI->setVisible(show);
		crTentMapGUI->setVisible(show);
	}
	
}

void App::setGUITheme(int i){
	
	for (int j = 0; j < guis.size(); j++) {
		guis[j]->setTheme(i);
		guis[j]->setDrawBack(false);
	}
}

void App::toggleDistribution(){
	
	if(selectedDistribution == 1){
		distributionGUI->setVisible(true);
		distributionGUI2->setVisible(false);
		distributionGUI3->setVisible(false);
	}
	
	else if (selectedDistribution == 2){
		distributionGUI->setVisible(false);
		distributionGUI2->setVisible(true);
		distributionGUI3->setVisible(false);
	}
	
	else if (selectedDistribution == 3){
		distributionGUI->setVisible(false);
		distributionGUI2->setVisible(false);
		distributionGUI3->setVisible(true);
	}
	
	fixedGUI->setVisible(false);
	triangularDistGUI->setVisible(false);
	linearDistGUI->setVisible(false);
	exponentialDistGUI->setVisible(false);
	gaussDistGUI->setVisible(false);
	cauchyDistGUI->setVisible(false);
	betaDistGUI->setVisible(false);
	weibullDistGUI->setVisible(false);
	poissonDistGUI->setVisible(false);
	
	fixedGUI2->setVisible(false);
	triangularDistGUI2->setVisible(false);
	linearDistGUI2->setVisible(false);
	exponentialDistGUI2->setVisible(false);
	gaussDistGUI2->setVisible(false);
	cauchyDistGUI2->setVisible(false);
	betaDistGUI2->setVisible(false);
	weibullDistGUI2->setVisible(false);
	poissonDistGUI2->setVisible(false);
	
	triangularDistGUI3->setVisible(false);
	linearDistGUI3->setVisible(false);
	exponentialDistGUI3->setVisible(false);
	gaussDistGUI3->setVisible(false);
	cauchyDistGUI3->setVisible(false);
	betaDistGUI3->setVisible(false);
	weibullDistGUI3->setVisible(false);
	poissonDistGUI3->setVisible(false);
}


void App::drawGrid(float x, float y)
{
    float w = ofGetWidth();
    float h = ofGetHeight();
    
    for(int i = 0; i < h; i+=y)
    {
        ofLine(0,i,w,i);
    }
    
    for(int j = 0; j < w; j+=x)
    {
        ofLine(j,0,j,h);
    }
}
