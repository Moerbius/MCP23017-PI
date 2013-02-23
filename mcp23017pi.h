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
#ifndef MCP23017PI_H
#define MCP23017PI_H

#include "bcm2835.h"

#include <stdint.h>

typedef unsigned int word;
typedef uint8_t byte;

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define OUTPUT 0x01
#define INPUT  0x00

//TODO: instead of using MCP23017PI_IODIR need to implement a GPIO choice in digitalWrite()
#define MCP23017PI_IODIRA 0x00
#define MCP23017PI_IODIRB 0x01

#define MCP23017PI_IODIR 0x01


#define MCP23017PI_IPOL 0x2
#define MCP23017PI_GPPU 0x0C

//TODO: instead of using MCP23017PI_GPIO need to implement a GPIO choice in digitalWrite()
#define MCP23017PI_GPIOA 0x12
#define MCP23017PI_GPIOB 0x13

#define MCP23017PI_GPIO 0x13

#define MCP23017PI_I2C_BASE_ADDRESS 0x40

class MCP23017PI
{
  public:
    //NB the i2c address here is the value of the A0, A1, A2 pins ONLY
    //as the class takes care of its internal base address.
    //so i2cAddress should be between 0 and 7
    MCP23017PI();
    void begin(int i2cAddress);
    void init();
    void end();

    //These functions provide an 'arduino'-like functionality for accessing
    //pin states/pullups etc.
    void pinMode(int pin, int mode);
    void digitalWrite(int pin, int val);
    int digitalRead(int pin);

    //These provide a more advanced mapping of the chip functionality
    //See the data sheet for more information on what they do

    //Returns a word with the current pin states (ie contents of the GPIO register)
    word digitalWordRead();

    //Allows you to write a word to the GPIO register
    void digitalWordWrite(word w);

    //Sets up the polarity mask that the MCP23017 supports
    //if set to 1, it will flip the actual pin value.
    void inputPolarityMask(word mask);

    //Sets which pins are inputs or outputs (1 = input, 0 = output) NB Opposite to arduino's
    //definition for these
    void inputOutputMask(word mask);

    //Allows enabling of the internal 100k pullup resisters (1 = enabled, 0 = disabled)
    void internalPullupMask(word mask);

    //Interrupt functionality (not yet implemented)


  private:
  void writeRegister(int regaddress, byte val);
	void writeRegister(int regaddress, word val);
	word readRegister(int regaddress);

	//Our actual i2c address
	byte _i2cAddress;

	//Cached copies of the register vales
	word _GPIO, _IODIR, _GPPU;
};
#endif
