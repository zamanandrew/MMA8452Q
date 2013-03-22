/*
 * Arduino library for the MMA8452Q three-axis accelerometer.
 *
 * Copyright (c) 2013, Alessandro Ghedini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <Arduino.h>
#include <Wire.h>

#include "MMA8452Q.h"

#define MMA8452Q_ADDRESS 0x1D

enum MMA8452Q_REGISTERS {
	STATUS       = 0x00,

	OUT_X_MSB    = 0x01,
	OUT_X_LSB    = 0x02,

	OUT_Y_MSB    = 0x03,
	OUT_Y_LSB    = 0x04,

	OUT_Z_MSB    = 0x05,
	OUT_Z_LSB    = 0x06,

	SYSMOD       = 0x0B,
	INT_SOURCE   = 0x0C,
	WHO_AM_I     = 0x0D,
	XYZ_DATA_CFG = 0x0E,

	PL_STATUS    = 0x10,
	PL_CFG       = 0x11,
	PL_COUNT     = 0x12,

	CTRL_REG1    = 0x2A,
	CTRL_REG2    = 0x2B,
	CTRL_REG3    = 0x2C,
	CTRL_REG4    = 0x2D,
	CTRL_REG5    = 0x2E,

	OFF_X        = 0x2F,
	OFF_Y        = 0x30,
	OFF_Z        = 0x31
};

enum MMA8452Q_STATUS {
	ZYX_OW = 0b10000000,
	Z_OW   = 0b01000000,
	Y_OW   = 0b00100000,
	X_OW   = 0b00010000,
	ZYX_DR = 0b00001000,
	Z_DR   = 0b00000100,
	Y_DR   = 0b00000010,
	X_DR   = 0b00000001
};

enum MMA8452Q_SYSMOD {
	STANDBY = 0b00,
	WAKE    = 0b01,
	SLEEP   = 0b10
};

enum MMA8452Q_CTRL_REG1 {
	ACTIVE = 0,
	F_READ = 1,
	LNOISE = 2,
	DR0    = 3,
	DR1    = 4,
	DR2    = 5
};

enum MMA8452Q_CTRL_REG2 {
	MODS0  = 0,
	MODS1  = 1,
	SLPE   = 2,
	SMODS0 = 3,
	SMODS1 = 4,
	RST    = 6,
	ST     = 7
};

enum MMA8452Q_CTRL_REG4 {
	INT_EN_DRDY   = 0,
	INT_EN_FF_MT  = 2,
	INT_EN_PULSE  = 3,
	INT_EN_LNDPRT = 4,
	INT_EN_TRANS  = 5,
	INT_EN_ASLP   = 7
};

enum MMA8452Q_CTRL_REG5 {
	INT_CFG_DRDY   = 0,
	INT_CFG_FF_MT  = 2,
	INT_CFG_PULSE  = 3,
	INT_CFG_LNDPRT = 4,
	INT_CFG_TRANS  = 5,
	INT_CFG_ASLP   = 7
};

MMA8452Q::MMA8452Q() {
}

int MMA8452Q::begin(void) {
	uint8_t whoami;

	Wire.begin();

	whoami = this -> registerRead(WHO_AM_I);

	if (whoami != 0x2A)
		return -1;

	this -> active(true);

	return 0;
}

uint8_t MMA8452Q::status(void) {
	return this -> registerRead(STATUS);
}

uint8_t MMA8452Q::sysmod(void) {
	return this -> registerRead(SYSMOD);
}

uint8_t MMA8452Q::intSource(void) {
	return this -> registerRead(INT_SOURCE);
}

void MMA8452Q::scale(uint8_t scale) {
	uint8_t value = this -> registerRead(XYZ_DATA_CFG);

	switch (scale) {
		case 2: bitWrite(value, 0, 0); bitWrite(value, 1, 0); break;
		case 4: bitWrite(value, 0, 1); bitWrite(value, 1, 0); break;
		case 8: bitWrite(value, 0, 0); bitWrite(value, 1, 1); break;
	}
}

void MMA8452Q::offset(int8_t off_x, int8_t off_y, int8_t off_z) {
	this -> registerWrite(OFF_X, off_x);
	this -> registerWrite(OFF_Y, off_y);
	this -> registerWrite(OFF_Z, off_z);
}

void MMA8452Q::active(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG1);
	bitWrite(val, ACTIVE, enable);
	this -> registerWrite(CTRL_REG1, val);
}

void MMA8452Q::fastRead(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG1);
	bitWrite(val, F_READ, enable);
	this -> registerWrite(CTRL_REG1, val);
}

void MMA8452Q::lowNoise(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG1);
	bitWrite(val, LNOISE, enable);
	this -> registerWrite(CTRL_REG1, val);
}

void MMA8452Q::reset(void) {
	uint8_t val = this -> registerRead(CTRL_REG2);
	bitWrite(val, RST, 1);
	this -> registerWrite(CTRL_REG2, val);
}

void MMA8452Q::selfTest(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG2);
	bitWrite(val, ST, enable);
	this -> registerWrite(CTRL_REG2, val);
}

void MMA8452Q::autoSleep(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG2);
	bitWrite(val, SLPE, enable);
	this -> registerWrite(CTRL_REG2, val);
}

void MMA8452Q::intDataRdy(bool enable, uint8_t pin) {
	uint8_t val = this -> registerRead(CTRL_REG4);
	bitWrite(val, INT_EN_DRDY, enable);
	this -> registerWrite(CTRL_REG4, val);

	val = this -> registerRead(CTRL_REG5);
	bitWrite(val, INT_CFG_DRDY, pin);
	this -> registerWrite(CTRL_REG5, val);
}

void MMA8452Q::intFreefallMotion(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG4);
	bitWrite(val, INT_EN_FF_MT, enable);
	this -> registerWrite(CTRL_REG4, val);
}

void MMA8452Q::intPulse(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG4);
	bitWrite(val, INT_EN_PULSE, enable);
	this -> registerWrite(CTRL_REG4, val);
}

void MMA8452Q::intOrientation(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG4);
	bitWrite(val, INT_EN_LNDPRT, enable);
	this -> registerWrite(CTRL_REG4, val);
}

void MMA8452Q::intAutoSlp(bool enable) {
	uint8_t val = this -> registerRead(CTRL_REG4);
	bitWrite(val, INT_EN_ASLP, enable);
	this -> registerWrite(CTRL_REG4, val);
}

void MMA8452Q::axes(int axes[]) {
	uint8_t *data;
	uint8_t read_count = 0;
	uint8_t val = this -> registerRead(CTRL_REG1);

	if (bitRead(val, F_READ) == 0)
		read_count = 6;
	else
		read_count = 3;

	data = new uint8_t[read_count];

	this -> registersRead(OUT_X_MSB, data, read_count);

	for (int i = 0; i < 3; i++) {
		axes[i]  = data[i * (read_count / 3)] << 8;

		if (bitRead(val, F_READ) == 0)
			axes[i] |= data[(i * 2) + 1];

		axes[i] >>= 4;
	}

	delete[] data;
}

uint8_t MMA8452Q::registerRead(uint8_t addr) {
	Wire.beginTransmission(MMA8452Q_ADDRESS);
	Wire.write(addr);
	Wire.endTransmission(false);

	Wire.requestFrom(MMA8452Q_ADDRESS, 1);

	while (!Wire.available());
	return Wire.read();
}

void MMA8452Q::registersRead(uint8_t addr, uint8_t data[], size_t count) {
	Wire.beginTransmission(MMA8452Q_ADDRESS);
	Wire.write(addr);
	Wire.endTransmission(false);

	Wire.requestFrom(MMA8452Q_ADDRESS, count);

	while (Wire.available() < count);

	for (size_t i = 0; i < count; i++)
		data[i] = Wire.read();
}

void MMA8452Q::registerWrite(uint8_t addr, uint8_t value) {
	Wire.beginTransmission(MMA8452Q_ADDRESS);
	Wire.write(addr);
	Wire.write(value);
	Wire.endTransmission();
}

void MMA8452Q::registersWrite(uint8_t addr, uint8_t data[], size_t count) {
	Wire.beginTransmission(MMA8452Q_ADDRESS);
	Wire.write(addr);

	for (int i = 0; i < count; i++)
		Wire.write(data[i]);

	Wire.endTransmission();
}
