/*  MCP23017PI library for Raspberry PI converted from Arduino library
    Copyright (C) 2009 David Pye    <davidmpye@gmail.com> (Original Arduino Library)
    Copyright (C) 2012 Kasper Skårhøj <kasperskaarhoj@gmail.com> (Original Arduino Library)
    Copyright (C) 2013 Isaias Lourenco <isaias.lourenco@swp.pt> (PI conversion)

    Version 0.1

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mcp23017pi.h"
#include <stdio.h>

MCP23017PI::MCP23017PI() {}

void MCP23017PI::begin(int i2cAddress) {
  _i2cAddress = (MCP23017PI_I2C_BASE_ADDRESS >>1) | (i2cAddress & 0x07);

	//Default state is 0 for our pins
	_GPIO = 0x0000;
	_IODIR = 0x0000;
	_GPPU = 0x0000;

    if(!bcm2835_init())
    {
        printf("Error initializing GPIO.");
    }

}

void MCP23017PI::init()	{

}

void MCP23017PI::pinMode(int pin, int mode) {
	mode = !mode;
	if (mode) _IODIR |= 1 << pin;
	else _IODIR &= ~(1 << pin);
	writeRegister(MCP23017PI_IODIR, (word)_IODIR);
}

//TODO: implement and test
int MCP23017PI::digitalRead(int pin) {
	_GPIO = readRegister(MCP23017PI_GPIO);
	if ( _GPIO & (1 << pin)) return HIGH;
	else return LOW;
}

void MCP23017PI::digitalWrite(int pin, int val) {
	//If this pin is an INPUT pin, a write here will
	//enable the internal pullup
	//otherwise, it will set the OUTPUT voltage
	//as appropriate.
	bool isOutput = !(_IODIR & 1<<pin);

	if (isOutput) {
		//This is an output pin so just write the value
		if (val) _GPIO |= 1 << pin;
		else _GPIO &= ~(1 << pin);
		writeRegister(MCP23017PI_GPIO, (word)_GPIO);
	}
	else {
		//This is an input pin, so we need to enable the pullup
		if (val) _GPPU |= 1 << pin;
		else _GPPU &= ~(1 << pin);
		writeRegister(MCP23017PI_GPPU, (word)_GPPU);
	}
}

word MCP23017PI::digitalWordRead() {
	_GPIO = readRegister(MCP23017PI_GPIO);
	return _GPIO;
}
void MCP23017PI::digitalWordWrite(word w) {
	_GPIO = w;
	writeRegister(MCP23017PI_GPIO, (word)_GPIO);
}

void MCP23017PI::inputPolarityMask(word mask) {
	writeRegister(MCP23017PI_IPOL, mask);
}

void MCP23017PI::inputOutputMask(word mask) {
	_IODIR = mask;
	writeRegister(MCP23017PI_IODIR, (word)_IODIR);
}

void MCP23017PI::internalPullupMask(word mask) {
	_GPPU = mask;
	writeRegister(MCP23017PI_GPPU, (word)_GPPU);
}

//PRIVATE
void MCP23017PI::writeRegister(int regAddress, byte data) {
	char buffer[] = {regAddress, data};

	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(_i2cAddress);
	bcm2835_i2c_write(buffer, sizeof(buffer));
    bcm2835_i2c_end();
}

void MCP23017PI::writeRegister(int regAddress, word data) {
    char buffer[] = {regAddress, data};

 	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(_i2cAddress);
	bcm2835_i2c_write(buffer, sizeof(buffer));
}

//TODO: implement
word MCP23017PI::readRegister(int regAddress) {
	word returnword = 0x00;
	//Wire.beginTransmission(_i2cAddress);
	//Wire.write(regAddress);
	//Wire.endTransmission();
	//Wire.requestFrom((int)_i2cAddress, 2);

    //int c=0;
	//Wait for our 2 bytes to become available
	//while (Wire.available()) {
        //high byte
        //if (c==0)   { returnword = Wire.read() << 8; }
        //low byte
        //if (c==1)   { returnword |= Wire.read(); }
        //c++;
    //}

	return returnword;
}

void MCP23017PI::end()
{
    bcm2835_i2c_end();
}
