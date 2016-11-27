/*
  Tda7313_example.ino - Library for TDA7313.
  Created by Kolesnikov Anton, 19.11.2016.
*/

#include "Tda7313.h"

Tda7313 tda; // Tda7313 tda(0x44); 

void setup() {
	tda.input(1);	// 1,2,3    Stereo 1, Stereo 2, Stereo 3
	tda.loud(true);	// Lound on (true,false)
	tda.mute(false);// Mute off (true,false)
	tda.volume(10);	//  0.......15  -78.75dB...........0dB
	tda.bass(7);	// 0....7...14  -14dB.....0dB....+14dB
	tda.treble(7);	// 0....7...14  -14dB.....0dB....+14dB
	
	tda.sla(0);// 0,1,2,3  0dB, +3.75dB, +7.5dB, +11.25dB
	
	tda.attLF(0);	//  0.......13  0dB.........-36.25dB
	tda.attRF(0);	//  0.......13  0dB.........-36.25dB
	tda.attLR(0);	//  0.......13  0dB.........-36.25dB
	tda.attRR(0);	//  0.......13  0dB.........-36.25dB
}

void loop() {

}
