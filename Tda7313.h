/*
  Tda7313.h - Library for TDA7313.
  Created by Kolesnikov Anton, 19.11.2016.
*/

#ifndef Tda7313_h
#define Tda7313_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <EEPROM.h>

#define VOLUME	1
#define BASS_TREBLE 2
#define ATT	3
#define SLA 4

const float VOLUME_PRINT[18] = {-78.75,-56.25,-47.50,-41.25,-36.25,-30.00,-25.00,-22.50,-18.75,-16.25,-12.50,-10.00,-7.50,-6.25,-5.00,-3.75,-1.25,0};
const int BASS_TREBLE_PRINT[15] = {-14,-12,-10,-8,-6,-4,-2,0,2,4,6,8,10,12,14};
const float ATT_PRINT[14] = {0,-1.25,-3.75,-5,-6.25,-7.5,-10,-12.5,-16.25,-18.75,-22.5,-25,-30,-36.25};
const float SLA_PRINT[4] = {0,3.75,7.5,11.25};

const byte VOLUME_MASK[18] = {0x3F,0x2D,0x26,0x21,0x1D,0x18,0x14,0x12,0x0F,0x0D,0x0A,0x08,0x06,0x05,0x04,0x03,0x01,0x00};
const byte BASS_MASK[15] = {0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x6F,0x6E,0x6D,0x6C,0x6B,0x6A,0x69,0x68};
const byte TREBLE_MASK[15] = {0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x7F,0x7E,0x7D,0x7C,0x7B,0x7A,0x79,0x78};
const byte ATT_LF_MASK[14] = {0x80,0x81,0x83,0x84,0x85,0x86,0x88,0x8A,0x8D,0x8F,0x92,0x94,0x98,0x9D};
const byte ATT_RF_MASK[14] = {0xA0,0xA1,0xA3,0xA4,0xA5,0xA6,0xA8,0xAA,0xAD,0xAF,0xB2,0xB4,0xB8,0xBD};
const byte ATT_LR_MASK[14] = {0xC0,0xC1,0xC3,0xC4,0xC5,0xC6,0xC8,0xCA,0xCD,0xCF,0xD2,0xD4,0xD8,0xDD};
const byte ATT_RR_MASK[14] = {0xE0,0xE1,0xE3,0xE4,0xE5,0xE6,0xE8,0xEA,0xED,0xEF,0xF2,0xF4,0xF8,0xFD};


	
class Tda7313
{
  public:
	Tda7313();
	Tda7313(int address);
	
	void save_eeprom();
	void save_eeprom(int arg);
	void restore_eeprom();
	void restore_eeprom(int arg);
	
	void sla(int arg);			// 0,1,2,3      0dB, +3.75dB, +7.5dB, +11.25dB
	void loud(bool loudEnabled);	// Loudness
	void input(int arg);			// 1,2,3    Stereo 1, Stereo 2, Stereo 3
	void volume(int arg);			//  0.......17    -78.75dB............0dB
	void mute(bool muteEnabled);	// Mute
	void bass(int arg);				// 0....7...14  -14dB.....0dB....+14dB
	void treble(int arg);			// 0....7...14  -14dB.....0dB....+14dB
	void attLF(int arg);			//  0.......13  0dB.........-36.25dB
	void attRF(int arg);			//  0.......13  0dB.........-36.25dB
	void attLR(int arg);			//  0.......13  0dB.........-36.25dB
	void attRR(int arg);			//  0.......13  0dB.........-36.25dB
	
	int sla();					// 0...3
	bool loud();					// TRUE - FALSE
	int input();					// 1...3
	int volume();					//  0.......15
	bool mute();					// TRUE - FALSE
	int bass();						// 0....7...14
	int treble();					// 0....7...14
	int attLF();					//  0.......13
	int attRF();					//  0.......13
	int attLR();					//  0.......13
	int attRR();					//  0.......13
	
	String Tda7313::print(int value,int type);
	
  private:
	int Tda7313address;
	byte iSelector = 0x5F;
	
	int iVolume,iBass,iTreble,iAttLF,iAttRF,iAttLR,iAttRR,iInput;
	int _sla[3] = {0,0,0};
	bool _mute = false;
	bool _loud = false;
};
 
#endif
