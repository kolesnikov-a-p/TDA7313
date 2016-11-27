/*
  Tda7313.cpp - Library for TDA7313.
  Created by Kolesnikov Anton, 19.11.2016.
*/

#include "Tda7313.h"

Tda7313::Tda7313(){	
	Wire.begin();
	Tda7313address = 0x88;
}
 
Tda7313::Tda7313(int address){	
	Wire.begin();
	Tda7313address = address;
}


void Tda7313::sla(int arg){
	switch(arg){
		case 0:
			iSelector |= (1<<3);
			iSelector |= (1<<4);
			_sla[iInput-1] = arg;
		break;
		case 1:
			iSelector &= ~(1<<3);
			iSelector |= (1<<4);
			_sla[iInput-1] = arg;
		break;
		case 2:
			iSelector |= (1<<3);
			iSelector &= ~(1<<4);
			_sla[iInput-1] = arg;
		break;
		case 3:
			iSelector &= ~(1<<3);
			iSelector &= ~(1<<4);
			_sla[iInput-1] = arg;
		break;
	}
	
	Wire.beginTransmission(Tda7313address);
	Wire.write(iSelector);
	Wire.endTransmission();
}

void Tda7313::loud(bool loudEnabled){
	if(loudEnabled) iSelector &= ~(1<<2); else iSelector |= (1<<2);
	_loud = loudEnabled;
	Wire.beginTransmission(Tda7313address);
	Wire.write(iSelector);
	Wire.endTransmission();
}

void Tda7313::input(int arg){
	switch(arg){
		case 1:
			iSelector &= ~(1<<0);
			iSelector &= ~(1<<1);
			iInput = arg;
		break;
		case 2:
			iSelector |= (1<<0);
			iSelector &= ~(1<<1);
			iInput = arg;
		break;
		case 3:
			iSelector &= ~(1<<0);
			iSelector |= (1<<1);
			iInput = arg;
		break;
		default:
			return;
	}
	
	Wire.beginTransmission(Tda7313address);
	Wire.write(iSelector);
	Wire.endTransmission();
	
	Tda7313::sla(_sla[arg-1]);
}

void Tda7313::volume(int arg){
	if(_mute) Tda7313::mute(false);
	if((arg < 0)||(arg > 17)) return;
	iVolume = arg;
	Wire.beginTransmission(Tda7313address);
	Wire.write(VOLUME_MASK[iVolume]);
	Wire.endTransmission(); 
}

void Tda7313::mute(bool muteEnabled){
	if(muteEnabled){
		_mute = true;
		Wire.beginTransmission(Tda7313address);
		Wire.write(0x9F);
		Wire.write(0xBF);
		Wire.write(0xDF);
		Wire.write(0xFF);
		Wire.endTransmission();
	}else{
		_mute = false;
		Tda7313::attLF(iAttLF);
		Tda7313::attRF(iAttRF);
		Tda7313::attLR(iAttLR);
		Tda7313::attRR(iAttRR);
	}
}

void Tda7313::bass(int arg){
	if((arg < 0)||(arg > 14)) return;
	iBass = arg;
	Wire.beginTransmission(Tda7313address);
	Wire.write(BASS_MASK[iBass]);
	Wire.endTransmission();
}

void Tda7313::treble(int arg){
	if((arg < 0)||(arg > 14)) return;
	iTreble = arg;
	Wire.beginTransmission(Tda7313address);
	Wire.write(TREBLE_MASK[iTreble]);
	Wire.endTransmission();
}

void Tda7313::attLF(int arg){
	if((arg < 0)||(arg > 13)||(_mute)) return;
	iAttLF = arg;
	Wire.beginTransmission(Tda7313address);
	Wire.write(ATT_LF_MASK[iAttLF]);
	Wire.endTransmission();
	
}

void Tda7313::attRF(int arg){
	if((arg < 0)||(arg > 13)||(_mute)) return;
	iAttRF = arg;
	Wire.beginTransmission(Tda7313address);
	Wire.write(ATT_RF_MASK[iAttRF]);
	Wire.endTransmission();
}

void Tda7313::attLR(int arg){
	if((arg < 0)||(arg > 13)||(_mute)) return;
	iAttLR = arg;
	Wire.beginTransmission(Tda7313address);
	Wire.write(ATT_LR_MASK[iAttLR]);
	Wire.endTransmission();
}

void Tda7313::attRR(int arg){
	if((arg < 0)||(arg > 13)||(_mute)) return;
	iAttRR = arg;
	Wire.beginTransmission(Tda7313address);
	Wire.write(ATT_RR_MASK[iAttRR]);
	Wire.endTransmission();
}


int Tda7313::sla(){ 
	return _sla[iInput-1];
}

bool Tda7313::loud(){
	return _loud;
}

int Tda7313::input(){ 
	return iInput;
}

int Tda7313::volume(){
	return iVolume;
}

bool Tda7313::mute(){
	return _mute;
}

int Tda7313::bass(){
	return iBass;
}

int Tda7313::treble(){
	return iTreble;
}

int Tda7313::attLF(){
	return iAttLF;
}

int Tda7313::attRF(){
	return iAttRF;
}

int Tda7313::attLR(){
	return iAttLR;
}

int Tda7313::attRR(){
	return iAttRR;
}


void Tda7313::save_eeprom(){
	Tda7313::save_eeprom(0);
}
void Tda7313::save_eeprom(int arg){
	if(EEPROM.read(arg) != iVolume) EEPROM.write(arg, iVolume);
	if(EEPROM.read(arg+1) != iTreble) EEPROM.write(arg+1, iTreble);
	if(EEPROM.read(arg+2) != iAttLF) EEPROM.write(arg+2, iAttLF);
	if(EEPROM.read(arg+3) != iAttRF) EEPROM.write(arg+3, iAttRF);
	if(EEPROM.read(arg+4) != iAttLR) EEPROM.write(arg+4, iAttLR);
	if(EEPROM.read(arg+5) != iAttRR) EEPROM.write(arg+5, iAttRR);
	if(EEPROM.read(arg+6) != iInput) EEPROM.write(arg+6, iInput);
	if(EEPROM.read(arg+7) != _mute) EEPROM.write(arg+7, _mute);
	if(EEPROM.read(arg+8) != _loud) EEPROM.write(arg+8, _loud);
	if(EEPROM.read(arg+9) != iBass) EEPROM.write(arg+9, iBass);
	if(EEPROM.read(arg+10) != _sla[0]) EEPROM.write(arg+10, _sla[0]);
	if(EEPROM.read(arg+11) != _sla[1]) EEPROM.write(arg+11, _sla[1]);
	if(EEPROM.read(arg+12) != _sla[2]) EEPROM.write(arg+12, _sla[2]);
}

void Tda7313::restore_eeprom(){
	Tda7313::restore_eeprom(0);
}
void Tda7313::restore_eeprom(int arg){
	Tda7313::volume(EEPROM.read(arg));
	Tda7313::treble(EEPROM.read(arg+1));
	Tda7313::attLF(EEPROM.read(arg+2));
	Tda7313::attRF(EEPROM.read(arg+3));
	Tda7313::attLR(EEPROM.read(arg+4));
	Tda7313::attRR(EEPROM.read(arg+5));
	Tda7313::input(EEPROM.read(arg+6));
	Tda7313::mute(EEPROM.read(arg+7));
	Tda7313::loud(EEPROM.read(arg+8));
	Tda7313::bass(EEPROM.read(arg+9));
	_sla[0] = EEPROM.read(arg+10);
	_sla[1] = EEPROM.read(arg+11);
	_sla[2] = EEPROM.read(arg+12);
	
	if((_sla[0] < 0)||(_sla[0] > 4)) _sla[0] = 0;
	if((_sla[1] < 0)||(_sla[1] > 4)) _sla[1] = 0;
	if((_sla[2] < 0)||(_sla[2] > 4)) _sla[2] = 0;
	
	Tda7313::sla(_sla[iInput-1]);
}


String Tda7313::print(int value,int type){
	switch(type){
		case VOLUME:
			return String(VOLUME_PRINT[value]);
		break;
		case BASS_TREBLE:
			return String(BASS_TREBLE_PRINT[value]);
		break;
		case ATT:
			return String(ATT_PRINT[value]);
		break;
		case SLA:
			return String(SLA_PRINT[value]);
		break;
	}
	return "";
}