#include "App.h"
#include "IndependentStochasticComposer.h"
#include "MarkovChainsComposer.h"
#include "RandomWalkComposer.h"
#include "Figure.h"
#include "Silence.h"
#include "Scales.h"
#include "Midi.h"

#include <vector>
#include <string>
#include <sstream>

#define WIDTH 1024
#define HEIGHT 768

using namespace std;

//--------------------------------------------------------------
ofxTonicSynth App::synth = ofxTonicSynth();
ofxUITextArea * App::currentFigureLabel = NULL;
ofxUIScrollableCanvas * App::resultsGui = NULL;
Player * App::player = new Player();

void App::setup(){
    
	mv = new MusicVisualizer();
	
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

}

//--------------------------------------------------------------
void App::update(){
	
	if(!player->isAllPlayed())
		player->update();
	else
		synth.setParameter("volume", 0);
	
	mv->update();
}

//--------------------------------------------------------------
void App::draw(){
	
	ofxUIColor c = generalGUI->getColorFill();

	backgroundColor = ofColor(red, green, blue);
    ofBackground(backgroundColor);

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
		if (selectedDistribution == 1) {
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
		}
		else if (selectedDistribution == 2) {
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
		}
		else if (selectedDistribution == 2) {
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
		}
		else if (selectedDistribution == 2) {
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
		}
		else if (selectedDistribution == 2) {
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
		}
		else if (selectedDistribution == 2) {
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
		}
		else if (selectedDistribution == 2) {
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
	
	
	else if(name == "Beta"){
		if (selectedDistribution == 1) {
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
		}
		else if (selectedDistribution == 2) {
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
		}
		else if (selectedDistribution == 2) {
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
		}
		else if (selectedDistribution == 2) {
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
		composition.clear();
		composition = composer->compose();
		resultsGui->removeWidgets();
	}
	else if(name == "PLAY" && composition.size() > 0 && !player->isPlaying()  && e.getButton()->getValue() == true){
		
		if(!player->isPaused())
			player->play(composition);
		else{
			player->unpause();
			pauseToggle->setValue(false);
		}
		
		
		vector<Figure *> fs;
		Silence * s = new Silence(Whole);
		Silence * s1 = new Silence(Half);
		Silence * s2 = new Silence(SixtyFourth);
		fs.push_back(s);
		fs.push_back(s1);
		fs.push_back(s2);
		fs.push_back(s);
		fs.push_back(s1);
		fs.push_back(s2);
		
		
		mv->drawFigures(fs);
	}
	else if (name == "PAUSE"){
		if(e.getToggle()->getValue() == true)
			player->pause();
		else
			player->unpause();
	}
	else if (name == "STOP" && e.getButton()->getValue() == true){
		player->stop();
		resultsGui->removeWidgets();
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

		composer = new IndependentStochasticComposer(uniform);
	}
	else if (name == "Markov Chains"){
		showIndependentStochasticGUI(false);
		showRandomWalkGUI(false);
		showMarkovChainsGUI(true);
		
		composer = new MarkovChainsComposer();
		
		MarkovChainsComposer * mc = dynamic_cast<MarkovChainsComposer *>(composer);
		mc->addMidiToChain("../../../data/mozart_eine_kleine.mid");
		fileLabel->setLabel("mozart_eine_kleine.mid");
		composition = Midi::readMidiFile("../../../data/mozart_eine_kleine.mid");
	}
	else if(name == "Random Walk"){
		showMarkovChainsGUI(false);
		showIndependentStochasticGUI(false);
		showRandomWalkGUI(true);
		
		composer = new RandomWalkComposer();
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
				composition = Midi::readMidiFile(openFileResult.getPath());
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
	
	
	resultsGui->addTextArea("text", "\n", OFX_UI_FONT_SMALL);
	resultsGui->addTextArea("text", f->getDescription(), OFX_UI_FONT_SMALL);
	
	
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
	SawtoothWave tone = SawtoothWave();
	// create a sine wave we'll use for some vibrato
	SawtoothWave vibratoOsc = SawtoothWave();
	vibratoOsc.freq(10);
	
	// you can use the regular arithmatic operators on Generators and their subclasses (SineWave extends Generator)
	Generator frequency = noteFreq + (vibratoOsc * noteFreq * 0.01);
	
	// plug that frequency generator into the frequency slot of the main audio-producing sine wave
	tone.freq(noteFreq);
	
	// Partials
	SawtoothWave firstPartial = SawtoothWave().freq(noteFreq * 2);
	SawtoothWave secondPartial = SawtoothWave().freq(noteFreq * 3);
	
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
	generalGUI->addLabelButton("COMPOSE", false, 120, 0, 724, 10);
	generalGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	generalGUI->addImageButton("PLAY", "GUI/play.png", false);
	pauseToggle = generalGUI->addImageToggle("PAUSE", "GUI/pause.png", false);
	generalGUI->addImageButton("STOP", "GUI/stop.png", false);
	generalGUI->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	generalGUI->addSlider("TEMPO", 1, 200, 120);
	generalGUI->addSpacer(300, 10);
	generalGUI->addLabelButton("SAVE", false, 120, 0, 724, 10);
	generalGUI->addLabelButton("DELETE", false);
	ofAddListener(generalGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(generalGUI);
	
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
	dis->getToggles()[0]->setValue(true);
	setValuesForGraph(uniform);
	ofAddListener(distributionListGUI->newGUIEvent, this, &App::guiEvent);
	guis.push_back(distributionListGUI);
	
	////////////
	
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
	
	rwGUI->addRangeSlider("Octaves", 0, 10, 2, 4);
	
	rwGUI->addSlider("Stems", 1, 20, 1);
	
	rwGUI->addLabel("Meter", OFX_UI_FONT_SMALL);
	mR = rwGUI->addRadio("Meter", meter, OFX_UI_ORIENTATION_HORIZONTAL);
	mR->getToggles()[0]->setValue(true);
	
	rwGUI->addLabel("Pattern", OFX_UI_FONT_SMALL);
	pR = rwGUI->addRadio("Pattern", pattern, OFX_UI_ORIENTATION_HORIZONTAL);
	pR->getToggles()[2]->setValue(true);
	
	rwGUI->addLabel("Figure", OFX_UI_FONT_SMALL);
	
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
	
	rwGUI->addRadio("Figure", figure);
	
	rwGUI->setVisible(false);
	rwGUI->autoSizeToFitWidgets();
	guis.push_back(rwGUI);
	ofAddListener(rwGUI->newGUIEvent, this, &App::guiEvent);
	
	setGUITheme(3);
	
	
	/*RandomWalkComposer * rw = new RandomWalkComposer();
	rw->setPattern(16);
	rw->setStems(50);
	rw->setScale(1);
	composition = rw->compose();
	player->play(composition);*/
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

void App::setGUITheme(int i){
	
	for (int j = 0; j < guis.size(); j++) {
		guis[j]->setTheme(i);
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
	
	triangularDistGUI->setVisible(false);
	linearDistGUI->setVisible(false);
	exponentialDistGUI->setVisible(false);
	gaussDistGUI->setVisible(false);
	cauchyDistGUI->setVisible(false);
	betaDistGUI->setVisible(false);
	weibullDistGUI->setVisible(false);
	poissonDistGUI->setVisible(false);

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
