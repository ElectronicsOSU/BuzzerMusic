#ifndef BuzzerMusic_h
#define BuzzerMusic_h

#include "scales.h"
#include "pitches.h"

class BuzzerMusic {
public:
/* Constructors */
	//Full constructor
	BuzzerMusic(int key, int scale, int octaves);
	//number of Octaves defaulted to 1 
	BuzzerMusic(int key, int scale);
/* Get and Set */
	int GetKey();
	int GetScale();
	int GetOctaves();
	int GetNoteCount(); 
	int GetFrequency(int scaleNoteIndex);
	int* GetScaleNotes();
	void SetKey(int key);
	void SetScale(int scale);
	void SetOctaves(int octaves);
	
private:
/* Properties */
	volatile int Key;
	volatile int Scale;
	volatile int Octaves; // limited to either 1, 2 or 3 octaves
	int ScaleNotes[36];
/* Helper Functions */
	void CompileScaleNotes();
	int GetKeyPitchIndex();
	int GetNumScaleNotes();

};

#endif
