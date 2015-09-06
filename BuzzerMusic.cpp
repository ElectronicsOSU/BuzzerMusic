#include "BuzzerMusic.h"
/*
void CompileScaleNotes();
int GetKeyPitchIndex();
int GetNumScaleNotes();
*/
// Sequential pitches, as defined in "pitches.h"
const int PITCHES[] = { NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, 
						NOTE_B1, NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2,
						NOTE_B2, NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, 
						NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, 
						NOTE_B4, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, 
						NOTE_B5, NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, 
						NOTE_B6, NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, 
						NOTE_B7, NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8 };
// number of pitches available. used to make sure no out-of-array-bounds errors occur
const int NUM_PITCHES = sizeof(PITCHES)/sizeof(int);

/* Constructors */
BuzzerMusic::BuzzerMusic(int key, int scale, int octaves)
{
	Key = key;
	Scale = scale;
	Octaves = octaves;
	int blank[] = {0,0,0,0,0,0,0,0,0,0,0,0,
	               0,0,0,0,0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,0,0,0,0}; // worst case is chromatic scale with 12 notes/octave and 3 octaves
	//ScaleNotes = blank;
	CompileScaleNotes();
}

BuzzerMusic::BuzzerMusic(int key, int scale)
{
	Key = key;
	Scale = scale;
	Octaves = 1;
	int blank[] = {0,0,0,0,0,0,0,0,0,0,0,0,
	               0,0,0,0,0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,0,0,0,0}; // worst case is chromatic scale with 12 notes/octave and 3 octaves
	//ScaleNotes = blank;
	CompileScaleNotes();
}

/* Get and Set */
int BuzzerMusic::GetKey()
{
	return Key; 
}
int BuzzerMusic::GetScale()
{
	return Scale;
}
int BuzzerMusic::GetOctaves()
{
	return Octaves;
}
int BuzzerMusic::GetNoteCount()
{
	//This note count is a function of the scale selected as well as the number of octaves
	int sum = GetNumScaleNotes()*Octaves;
	return sum;
}
int BuzzerMusic::GetFrequency(int scaleNoteIndex)
{
	return ScaleNotes[scaleNoteIndex];
}

int* BuzzerMusic::GetScaleNotes()
{
	return ScaleNotes;
}

void BuzzerMusic::SetKey(int key)
{
	//Key must be a valid note as defined by "pitches.h"
	Key = key;
	CompileScaleNotes();
}
void BuzzerMusic::SetScale(int scale)
{
	//Scale must be a valid as defined by "scales.h"
	Scale = scale;
	CompileScaleNotes();
}
void BuzzerMusic::SetOctaves(int octaves)
{
	//Octaves must be either 1, 2 or 3
	Octaves = octaves;
	if (octaves > 3) { Octaves = 3; }
	if (octaves < 1) { Octaves = 1; }
	CompileScaleNotes();
}

/* Helper Functions */
void BuzzerMusic::CompileScaleNotes()
{
	int rootIndex = GetKeyPitchIndex();
	int notesInScale = GetNumScaleNotes();
	int notesUsed = 0;
	
	for(int j = 0; j < Octaves; j++){	
		notesUsed = 0;
		for(int i = 0; i<16; i++){
			if((Scale >> i) & 1)
			{
				ScaleNotes[notesInScale*j+notesUsed] = PITCHES[rootIndex+12*j+i];
				notesUsed++;
			}
		}
	}
}

int BuzzerMusic::GetKeyPitchIndex()
{
/* returns the index in the PITCHES array that matches with the Key selected */
	for(int i = 0; i<NUM_PITCHES; i++)
	{
		if(PITCHES[i] == Key){ return i; }
	}
	//if the pitch was not found, there was an error
	return -1;
}

int BuzzerMusic::GetNumScaleNotes()
{
/* returns the number of notes in one octave of the currently selected scale
   note: this doesn't count the octave of the root note */
	int sum = 0;
	//Scale is a 16 bit number, so shift 16 times and count number of 1's 
	for(int i = 0; i < 16; i++)
	{
		sum += (Scale >> i) & 1;
	}	
	return sum;
}




