#include "App.h"

//--------------------------------------------------------------
void App::setup(){
    
    
    ofBackground(ofxUIColor::crimson);

    
    guiTabBar = new ofxUITabBar();
    
    //SETTING GUI
    guiTabBar->setFont("GUI/Lekton-Regular.ttf");
    guiTabBar->setFontSize(OFX_UI_FONT_LARGE, 18);
    guiTabBar->setFontSize(OFX_UI_FONT_MEDIUM, 14);
    guiTabBar->setFontSize(OFX_UI_FONT_SMALL, 10);
    guiTabBar->setName("Metodo");
    guiTabBar->addLabel("Metodo");
    guiTabBar->addSpacer();
    guiTabBar->autoSizeToFitWidgets();
    
    ofxUICanvas* gui1 = new ofxUICanvas();
    gui1->setFont("GUI/Lekton-Regular.ttf");
    gui1->setFontSize(OFX_UI_FONT_LARGE, 18);
    gui1->setFontSize(OFX_UI_FONT_MEDIUM, 14);
    gui1->setFontSize(OFX_UI_FONT_SMALL, 10);
    gui1->setName("Estocastico");
    gui1->addLabel("Estocastico");
    gui1->addSpacer();
    gui1->autoSizeToFitWidgets();
    ofAddListener(gui1->newGUIEvent,this,&App::guiEvent);
    guiTabBar->addCanvas(gui1);
    guis.push_back(gui1);

    ofxUICanvas* gui2 = new ofxUICanvas();
    gui2->setFont("GUI/Lekton-Regular.ttf");
    gui2->setFontSize(OFX_UI_FONT_LARGE, 18);
    gui2->setFontSize(OFX_UI_FONT_MEDIUM, 14);
    gui2->setFontSize(OFX_UI_FONT_SMALL, 10);
    gui2->setName("Determinista");
    gui2->addLabel("Determinista");
    gui2->addSpacer();
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent,this,&App::guiEvent);
    guiTabBar->addCanvas(gui2);
    guis.push_back(gui2);

    ofxUICanvas* gui3 = new ofxUICanvas();
    gui3->setFont("GUI/Lekton-Regular.ttf");
    gui3->setFontSize(OFX_UI_FONT_LARGE, 18);
    gui3->setFontSize(OFX_UI_FONT_MEDIUM, 14);
    gui3->setFontSize(OFX_UI_FONT_SMALL, 10);
    gui3->setName("Gramatical");
    gui3->addLabel("Gramatical");
    gui3->addSpacer();
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent,this,&App::guiEvent);
    guiTabBar->addCanvas(gui3);
    guis.push_back(gui3);
    
    ofxUICanvas* gui4 = new ofxUICanvas();
    gui4->setFont("GUI/Lekton-Regular.ttf");
    gui4->setFontSize(OFX_UI_FONT_LARGE, 18);
    gui4->setFontSize(OFX_UI_FONT_MEDIUM, 14);
    gui4->setFontSize(OFX_UI_FONT_SMALL, 10);
    gui4->setName("Evolutivo");
    gui4->addLabel("Evolutivo");
    gui4->addSpacer();
    gui4->autoSizeToFitWidgets();
    ofAddListener(gui4->newGUIEvent,this,&App::guiEvent);
    guiTabBar->addCanvas(gui4);
    guis.push_back(gui4);
    
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
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
    synth.setOutputGen( tone * tremeloSine );
}

//--------------------------------------------------------------
void App::update(){

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
