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

static const int Chromatic[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // 0 - 11 /
static const int Pentatonic[5] = {0, 2, 4, 7, 9}; // 0 - 4 /

static const int CMajor[7] = {0, 2, 4, 5, 7, 9, 11}; // 0 - 6 /
static const int AMinor[7] = {9, 11, 0, 2, 4, 5, 7}; // 2 - 1
static const int AMinorH[7] = {9, 11, 0, 2, 4, 5, 8}; // 2 - 1

static const int GMajor[7] = {7, 9, 11, 0, 2, 4, 6}; // 3 - 2
static const int EMinor[7] = {2, 4, 6, 7, 9, 11, 0}; // 6 - 5
static const int EMinorH[7] = {2, 4, 6, 7, 9, 11, 1}; //6 - 5

static const int DMajor[7] = {2, 4, 6, 7, 9, 11, 1}; // 6 - 5
static const int BMinor[7] = {11, 1, 2, 4, 6, 7, 9}; // 1 - 0
static const int BMinorH[7] = {11, 1, 2, 4, 6, 7, 10}; // 1 - 0

static const int AMajor[7] = {9, 11, 1, 2, 4, 6, 8}; // 2 - 1
static const int FfMinor[7] = {6, 8, 9, 11, 1, 2, 4}; // 4
static const int FfMinorH[7] = {6, 8, 9, 11, 1, 2, 5}; // 4

static const int EMajor[7] = {4, 6, 8, 9, 11, 1, 3}; // 5
static const int CfMinor[7] = {1, 3, 4, 6, 8, 9, 11}; // 0
static const int CfMinorH[7] = {1, 3, 4, 6, 8, 9, 0}; // 6

static const int BMajor[7] = {11, 1, 3, 4, 6, 8, 10}; // 1
static const int GfMinor[7] = {8, 10, 11, 1, 3, 4, 6}; // 3
static const int GfMinorH[7] = {8, 10, 11, 1, 3, 4, 7}; // 3

static const int FfMajor[7] = {6, 8, 10, 11, 1, 3, 5}; // 4
static const int DfMinor[7] = {3, 5, 6, 8, 10, 11, 1}; // 6
static const int DfMinorH[7] = {3, 5, 6, 8, 10, 11, 2}; // 6

static const int FMajor[7] = {5, 7, 9, 10, 0, 2, 4}; // 4
static const int DMinor[7] = {2, 4, 5, 7, 9, 10, 0}; // 6
static const int DMinorH[7] = {2, 4, 5, 7, 9, 10, 1}; // 6

static const int BbMajor[7] = {10, 0, 2, 3, 5, 7, 9}; // 1
static const int GMinor[7] = {7, 9, 10, 0, 2, 3, 5}; // 3
static const int GMinorH[7] = {7, 9, 10, 0, 2, 3, 6}; // 3

static const int EbMajor[7] = {3, 5, 7, 8, 10, 0, 2}; // 5
static const int CMinor[7] = {0, 2, 3, 5, 7, 8, 10}; // 0 /
static const int CMinorH[7] = {0, 2, 3, 5, 7, 8, 11}; // 0 /

static const int AbMajor[7] = {8, 10, 0, 1, 3, 5, 7}; // 2
static const int FMinor[7] = {5, 7, 8, 10, 0, 1, 3}; // 4
static const int FMinorH[7] = {5, 7, 8, 10, 0, 1, 4}; // 4

static const int DbMajor[7] = {1, 3, 5, 6, 8, 10, 0}; // 6
static const int BbMinor[7] = {10, 0, 1, 3, 5, 6, 8}; // 1
static const int BbMinorH[7] = {10, 0, 1, 3, 5, 6, 9}; // 1

static const string NamesOfScales[38] = {"Chromatic", "Pentatonic", "C Major", "C Minor", "C Minor Harmonic", "C# Minor", "C# Minor Harmonic", "Db Major", "D Major", "D Minor", "D Minor Harmonic", "D# Minor", "D# Minor Harmonic",  "Eb Major", "E Major", "E Minor", "E Minor Harmonic", "F Major", "F Minor", "F Minor Harmonic", "F# Major", "F# Minor", "F# Minor Harmonic", "G Major", "G Minor", "G Minor Harmonic", "G# Minor", "G# Minor Harmonic", "Ab Major", "A Major", "A Minor", "A Minor Harmonic", "Bb Major", "Bb Minor", "Bb Minor Harmonic", "B Major", "B Minor", "B Minor Harmonic"};

static const int* ListOfScales[38] = {Chromatic, Pentatonic, CMajor, CMinor, CMinorH, CfMinor, CfMinorH, DbMajor, DMajor, DMinor, DMinorH, DfMinor, DfMinorH, EbMajor, EMajor, EMinor, EMinorH, FMajor, FMinor, FMinorH, FfMajor, FfMinor, FfMinorH, GMajor, GMinor, GMinorH, GfMinor, GfMinorH, AbMajor, AMajor, AMinor, AMinorH, BbMajor, BbMinor, BbMinorH, BMajor, BMinor, BMinorH};

static const int OctaveUp[38] = {0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 5, 5, 6, 6, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1};
static const int OctaveDown[38] = {11, 4, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 4, 4, 5, 5, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};