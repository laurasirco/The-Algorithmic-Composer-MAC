//
//  Scales.h
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 16/06/14.
//
//

#include <string>
#include <iostream>
using namespace std;

const int Chromatic[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; //
const int Pentatonic[5] = {0, 2, 4, 7, 9}; //

const int CMajor[7] = {0, 2, 4, 5, 7, 9, 11}; //
const int AMinor[7] = {9, 11, 0, 2, 4, 5, 7}; //
const int AMinorH[7] = {9, 11, 0, 2, 4, 5, 8}; //

const int GMajor[7] = {7, 9, 11, 0, 2, 4, 6}; //
const int EMinor[7] = {2, 4, 6, 7, 9, 11, 0}; //
const int EMinorH[7] = {2, 4, 6, 7, 9, 11, 1}; //

const int DMajor[7] = {2, 4, 6, 7, 9, 11, 1}; //
const int BMinor[7] = {11, 1, 2, 4, 6, 7, 9}; //
const int BMinorH[7] = {11, 1, 2, 4, 6, 7, 10}; //

const int AMajor[7] = {9, 11, 1, 2, 4, 6, 8}; //
const int FfMinor[7] = {6, 8, 9, 11, 1, 2, 4}; //
const int FfMinorH[7] = {6, 8, 9, 11, 1, 2, 5}; //

const int EMajor[7] = {4, 6, 8, 9, 11, 1, 3}; //
const int CfMinor[7] = {1, 3, 4, 6, 8, 9, 11}; //
const int CfMinorH[7] = {1, 3, 4, 6, 8, 9, 0}; //

const int BMajor[7] = {11, 1, 3, 6, 8, 10}; //
const int GfMinor[7] = {8, 10, 11, 1, 3, 6}; //
const int GfMinorH[7] = {8, 10, 11, 1, 3, 7}; //

const int FfMajor[7] = {6, 8, 10, 11, 1, 3, 5}; //
const int DfMinor[7] = {3, 5, 6, 8, 10, 11, 1}; //
const int DfMinorH[7] = {3, 5, 6, 8, 10, 11, 2}; //

const int FMajor[7] = {5, 7, 9, 10, 0, 2, 4}; //
const int DMinor[7] = {2, 4, 5, 7, 9, 10, 0}; //
const int DMinorH[7] = {2, 4, 5, 7, 9, 10, 1}; //

const int BbMajor[7] = {10, 0, 2, 3, 5, 7, 9};
const int GMinor[7] = {7, 9, 10, 0, 2, 3, 5}; //
const int GMinorH[7] = {7, 9, 10, 0, 2, 3, 6}; //

const int EbMajor[7] = {3, 5, 7, 8, 10, 0, 2}; //
const int CMinor[7] = {0, 2, 3, 5, 7, 8, 10}; //
const int CMinorH[7] = {0, 2, 3, 5, 7, 8, 11}; //

const int AbMajor[7] = {8, 10, 0, 1, 3, 5, 7}; //
const int FMinor[7] = {5, 7, 8, 10, 0, 1, 3}; //
const int FMinorH[7] = {5, 7, 8, 10, 0, 1, 4}; //

const int DbMajor[7] = {1, 3, 5, 6, 8, 10, 0}; //
const int BbMinor[7] = {10, 0, 1, 3, 5, 6, 8}; //
const int BbMinorH[7] = {10, 0, 1, 3, 5, 6, 9}; //

const string NamesOfScales[38] = {"Chromatic", "Pentatonic", "C Major", "C Minor", "C Minor Harmonic", "C# Minor", "C# Minor Harmonic", "Db Major", "D Major", "D Minor", "D Minor Harmonic", "D# Minor", "D# Minor Harmonic",  "Eb Major", "E Major", "E Minor", "E Minor Harmonic", "F Major", "F Minor", "F Minor Harmonic", "F# Major", "F# Minor", "F# Minor Harmonic", "G Major", "G Minor", "G Minor Harmonic", "G# Minor", "G# Minor Harmonic", "Ab Major", "A Major", "A Minor", "A Minor Harmonic", "Bb Major", "Bb Minor", "Bb Minor Harmonic", "B Major", "B Minor", "B Minor Harmonic"};

const int* ListOfScales[38] = {Chromatic, Pentatonic, CMajor, CMinor, CMinorH, CfMinor, CMinorH, DbMajor, DMajor, DMinor, DMinorH, DfMinor, DfMinorH, EbMajor, EMajor, EMinor, EMinorH, FMajor, FMinor, FMinorH, FfMajor, FfMinor, FfMinorH, GMajor, GMinor, GMinorH, GfMinor, GfMinorH, AbMajor, AMajor, AMinor, AMinorH, BbMajor, BbMinor, BbMinorH, BMajor, BMinor, BMinorH};

