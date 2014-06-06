#include "App.h"

//--------------------------------------------------------------
void App::setup(){
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
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}
