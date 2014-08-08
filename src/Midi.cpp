//
//  Midi.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 07/07/14.
//
//

#include "Midi.h"
#include "Note.h"
#include "Silence.h"

using namespace MIDIConstants;
typedef unsigned char uchar;

vector<Figure *> Midi::readMidiFile(string filename){
	
	vector<Figure *> figures;
	int ppqn = 0;
	
	MIDIFileReader fr(filename);
	if (!fr.isOK()) {
		std::cerr << "Error: " << fr.getError().c_str() << std::endl;
		
	}
	
	else{
		MIDIComposition c = fr.load();
		
		switch (fr.getFormat()) {
			case MIDI_SINGLE_TRACK_FILE: cout << "Format: MIDI Single Track File" << endl; break;
			case MIDI_SIMULTANEOUS_TRACK_FILE: cout << "Format: MIDI Simultaneous Track File" << endl; break;
			case MIDI_SEQUENTIAL_TRACK_FILE: cout << "Format: MIDI Sequential Track File" << endl; break;
			default: cout << "Format: Unknown MIDI file format?" << endl; break;
		}
		
		cout << "Tracks: " << c.size() << endl;
		
		int td = fr.getTimingDivision();
		if (td < 32768) {
			cout << "Timing division: " << fr.getTimingDivision() << " ppq" << endl;
			ppqn = fr.getTimingDivision();
			
		} else {
			int frames = 256 - (td >> 8);
			int subframes = td & 0xff;
			cout << "SMPTE timing: " << frames << " fps, " << subframes << " subframes" << endl;
		}
		
		for (MIDIComposition::const_iterator i = c.begin(); i != c.end(); ++i) {
			
			cout << "Start of track: " << i->first+1 << endl;
			
			for (MIDITrack::const_iterator j = i->second.begin(); j != i->second.end(); ++j) {
				
				unsigned int t = j->getTime();
				int ch = j->getChannelNumber();
				
				if (j->isMeta()) {
					int code = j->getMetaEventCode();
					string name;
					bool printable = true;
					switch (code) {
							
						case MIDI_END_OF_TRACK:
							cout << t << ": End of track" << endl;
							break;
							
						case MIDI_TEXT_EVENT: name = "Text"; break;
						case MIDI_COPYRIGHT_NOTICE: name = "Copyright"; break;
						case MIDI_TRACK_NAME: name = "Track name"; break;
						case MIDI_INSTRUMENT_NAME: name = "Instrument name"; break;
						case MIDI_LYRIC: name = "Lyric"; break;
						case MIDI_TEXT_MARKER: name = "Text marker"; break;
						case MIDI_SEQUENCE_NUMBER: name = "Sequence number"; printable = false; break;
						case MIDI_CHANNEL_PREFIX_OR_PORT: name = "Channel prefix or port"; printable = false; break;
						case MIDI_CUE_POINT: name = "Cue point"; break;
						case MIDI_CHANNEL_PREFIX: name = "Channel prefix"; printable = false; break;
						case MIDI_SEQUENCER_SPECIFIC: name = "Sequencer specific"; printable = false; break;
						case MIDI_SMPTE_OFFSET: name = "SMPTE offset"; printable = false; break;
							
						case MIDI_SET_TEMPO:
						{
							int m0 = j->getMetaMessage()[0];
							int m1 = j->getMetaMessage()[1];
							int m2 = j->getMetaMessage()[2];
							long tempo = (((m0 << 8) + m1) << 8) + m2;
							
							cout << t << ": Tempo: " << 60000000.0 / double(tempo) << endl;
						}
							break;
							
						case MIDI_TIME_SIGNATURE:
						{
							int numerator = j->getMetaMessage()[0];
							int denominator = 1 << (int)j->getMetaMessage()[1];
							
							cout << t << ": Time signature: " << numerator << "/" << denominator << endl;
						}
							
						case MIDI_KEY_SIGNATURE:
						{
							int accidentals = j->getMetaMessage()[0];
							int isMinor = j->getMetaMessage()[1];
							bool isSharp = accidentals < 0 ? false : true;
							accidentals = accidentals < 0 ? -accidentals : accidentals;
							cout << t << ": Key signature: " << accidentals << " "
							<< (isSharp ?
								(accidentals > 1 ? "sharps" : "sharp") :
								(accidentals > 1 ? "flats" : "flat"))
							<< (isMinor ? ", minor" : ", major") << endl;
						}
							
					}
					
					
					if (name != "") {
						if (printable) {
							cout << t << ": File meta event: code " << code
							<< ": " << name << ": \"" << j->getMetaMessage()
							<< "\"" << endl;
						} else {
							cout << t << ": File meta event: code " << code
							<< ": " << name << ": ";
							for (int k = 0; k < j->getMetaMessage().length(); ++k) {
								cout << (int)j->getMetaMessage()[k] << " ";
							}
						}
					}
					continue;
				}
				
				Note * note;
				
				switch (j->getMessageType()) {
						
					case MIDI_NOTE_ON:
												
						cout << t << ": Note: channel " << ch
						<< " duration " << j->getDuration()
						<< " pitch " << j->getPitch()
						<< " velocity " << j->getVelocity()
						<< endl;
						
						note = new Note(Figure::MIDIDurationToType(ppqn, j->getDuration()), j->getPitch(), j->getVelocity());
						note->printMyself();
						
						figures.push_back(note);
						
						break;
						
					case MIDI_POLY_AFTERTOUCH:
						cout << t << ": Polyphonic aftertouch: channel " << ch
						<< " pitch " << j->getPitch()
						<< " pressure " << j->getData2() << endl;
						break;
						
					case MIDI_CTRL_CHANGE:
					{
						int controller = j->getData1();
						string name;
						switch (controller) {
							case MIDI_CONTROLLER_BANK_MSB: name = "Bank select MSB"; break;
							case MIDI_CONTROLLER_VOLUME: name = "Volume"; break;
							case MIDI_CONTROLLER_BANK_LSB: name = "Bank select LSB"; break;
							case MIDI_CONTROLLER_MODULATION: name = "Modulation wheel"; break;
							case MIDI_CONTROLLER_PAN: name = "Pan"; break;
							case MIDI_CONTROLLER_SUSTAIN: name = "Sustain"; break;
							case MIDI_CONTROLLER_RESONANCE: name = "Resonance"; break;
							case MIDI_CONTROLLER_RELEASE: name = "Release"; break;
							case MIDI_CONTROLLER_ATTACK: name = "Attack"; break;
							case MIDI_CONTROLLER_FILTER: name = "Filter"; break;
							case MIDI_CONTROLLER_REVERB: name = "Reverb"; break;
							case MIDI_CONTROLLER_CHORUS: name = "Chorus"; break;
							case MIDI_CONTROLLER_NRPN_1: name = "NRPN 1"; break;
							case MIDI_CONTROLLER_NRPN_2: name = "NRPN 2"; break;
							case MIDI_CONTROLLER_RPN_1: name = "RPN 1"; break;
							case MIDI_CONTROLLER_RPN_2: name = "RPN 2"; break;
							case MIDI_CONTROLLER_SOUNDS_OFF: name = "All sounds off"; break;
							case MIDI_CONTROLLER_RESET: name = "Reset"; break;
							case MIDI_CONTROLLER_LOCAL: name = "Local"; break;
							case MIDI_CONTROLLER_ALL_NOTES_OFF: name = "All notes off"; break;
						}
						cout << t << ": Controller change: channel " << ch
						<< " controller " << j->getData1();
						if (name != "") cout << " (" << name << ")";
						cout << " value " << j->getData2() << endl;
					}
						break;
						
					case MIDI_PROG_CHANGE:
						cout << t << ": Program change: channel " << ch
						<< " program " << j->getData1() << endl;
						break;
						
					case MIDI_CHNL_AFTERTOUCH:
						cout << t << ": Channel aftertouch: channel " << ch
						<< " pressure " << j->getData1() << endl;
						break;
						
					case MIDI_PITCH_BEND:
						cout << t << ": Pitch bend: channel " << ch
						<< " value " << (int)j->getData2() * 128 + (int)j->getData1() << endl;
						break;
						
					case MIDI_SYSTEM_EXCLUSIVE:
						cout << t << ": System exclusive: code "
						<< (int)j->getMessageType() << " message length " <<
						j->getMetaMessage().length() << endl;
						break;
						
						
				}
				
				
			}
			
		}
	
	}
	
	return figures;
}

void Midi::writeMidiFile(string filename, vector<Figure *> figures){
	
	
	MidiFile outputfile;        // create an empty MIDI file with one track
	outputfile.absoluteTime();  // time information stored as absolute time
	// (will be coverted to delta time when written)
	outputfile.addTrack(1);     // Add another two tracks to the MIDI file
	Array<uchar> midievent;     // temporary storage for MIDI events
	midievent.setSize(3);       // set the size of the array to 3 bytes
	int tpq = 120;              // default value in MIDI file is 48
	outputfile.setTicksPerQuarterNote(tpq);
	
	int actiontime = 0;      // temporary storage for MIDI event time
	midievent[2] = 64;
	
	for(int i = 0; i < figures.size(); i++){
		
		if(figures[i]->getKind() == KNote){
			Note * n = dynamic_cast<Note *>(figures[i]);
			midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
			midievent[1] = n->getPitch();
			outputfile.addEvent(1, actiontime, midievent);
			actiontime += Figure::TypeToMIDIDuration(tpq, figures[i]->getType());
			midievent[0] = 0x80;     // store a note off command (MIDI channel 1)
			outputfile.addEvent(1, actiontime, midievent);
			
			cout << i << " - NOTE -  Action time: " << actiontime << endl;
		}
		else if (figures[i]->getKind() == KSilence){
			actiontime += Figure::TypeToMIDIDuration(tpq, figures[i]->getType());
			cout << i << " - SILENCE -  Action time: " << actiontime << endl;
		}
	
		//actiontime += tpq * mrhythm[i];

	}
	
	std::size_t found = filename.find(".mid");
	if (found == std::string::npos)
		filename += ".mid";
	
	outputfile.write(filename.c_str());
	
}