//
//  Player.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 12/06/14.
//
//

#include "Player.h"
#include "App.h"
#include "Note.h"

Player::Player(int b){
	count = 0;
	BPM = b;
	i = 0;
	allPlayed = true;
	
	
	/*
	 Generators and ControlGenerators both output a steady stream of data.
	 Generators output at the sample rate (in this case, 44100 hertz.
	 ControlGenerators output at the control rate, which is much lower than the sample rate.
	 */
	
	// create a named parameter on the synth which we can set at runtime
	ControlGenerator midiNote = synth.addParameter("midiNumber");
	
	// convert a midi note to a frequency (plugging that parameter into another object)
	ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
	
	// Here's the actual noise-making object
	Generator tone = SawtoothWave().freq( noteFreq );
	
	// Let's put a filter on the tone
	tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 2) + SineWave().freq(3) * 0.5 * noteFreq);
	
	// It's just a steady tone until we modulate the amplitude with an envelope
	ControlGenerator envelopeTrigger = synth.addParameter("trigger");
	Generator toneWithEnvelope = tone * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(true);
	
	// let's send the tone through some delay
	Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.1).feedback(0.2);
	
	synth.setOutputGen( toneWithDelay );

}

Player::~Player(){
	
}

void Player::play(std::vector<Figure*> f){
	
	float FPS = App::getFramerate();
	fragment = f;
	i = 0;
	count = 0;
	allPlayed = false;
	
	float framesQuarter = (60/BPM)/(1/FPS);
	
	float duration = fragment[i]->getDuration();
	
	if (duration == 1)
		x = framesQuarter * 4;
	else if (duration == 0.5)
		x = framesQuarter * 2;
	else if(duration == 0.25)
		x = framesQuarter;
	else if(duration == 0.125)
		x = framesQuarter / 2;
	else if(duration == 0.0625)
		x = framesQuarter / 4;
	else if(duration == 0.03125)
		x = framesQuarter / 8;
	else if(duration == 0.015625)
		x = framesQuarter / 16;
	
	//play note here
	cout<<"Total notes: "<<fragment.size()<<endl;
	cout<<"playing note: "<<i; fragment[i]->printMyself();
	
	if(fragment[i]->getKind() == KNote){
		Note * n = (Note *)fragment[i];
		synth.setParameter("midiNumber", n->getPitch());
	}
		
}

void Player::update(){
	
	if((count == x) && (i+1 < fragment.size())){ //next note
		
		i++;
		count = 0;
		
		float FPS = App::getFramerate();
		float framesQuarter = (60/BPM)/(1/FPS);
		
		float duration = fragment[i]->getDuration();
		
		if (duration == 1)
			x = framesQuarter * 4;
		else if (duration == 0.5)
			x = framesQuarter * 2;
		else if(duration == 0.25)
			x = framesQuarter;
		else if(duration == 0.125)
			x = framesQuarter / 2;
		else if(duration == 0.0625)
			x = framesQuarter / 4;
		else if(duration == 0.03125)
			x = framesQuarter / 8;
		else if(duration == 0.015625)
			x = framesQuarter / 16;
		
		//play note here
		cout<<"playing note: "<<i<<" "; fragment[i]->printMyself();
		
		if(fragment[i]->getKind() == KNote){
			Note * n = (Note *)fragment[i];
			synth.setParameter("midiNumber", n->getPitch());
		}
		
	}
	
	if (i == fragment.size() - 1 && (count == x)) {
		allPlayed = true;
	}
	else{
		//cout<<"Count "<<count<<" to x "<<x<<endl;
		count++;
	}

}