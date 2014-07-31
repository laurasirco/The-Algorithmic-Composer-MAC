//
//  Midi.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 07/07/14.
//
//

#ifndef __The_Algorithmic_Composer__Midi__
#define __The_Algorithmic_Composer__Midi__

#include <iostream>
#include <string>
#include <vector>
#include "Figure.h"
#include "MIDIFileReader.h"
#include "MidiFile.h"

using namespace std;

class Midi {

public:
	static vector<Figure *> readMidiFile(string filename);
	static void writeMidiFile(string filename, vector<Figure *> figures);

};

#endif /* defined(__The_Algorithmic_Composer__Midi__) */
