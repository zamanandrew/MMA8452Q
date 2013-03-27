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

#ifndef MMA8452Q_H
#define MMA8452Q_H

enum MMA8452Q_INTERRUPTS {
	MMA8452Q_INT1 = 1,
	MMA8452Q_INT2 = 0
};

class MMA8452Q {
	public:
		MMA8452Q();

		int begin(void);

		uint8_t status(void);
		uint8_t sysmod(void);
		uint8_t intSource(void);

		void scale(uint8_t scale);
		void offset(int8_t off_x, int8_t off_y, int8_t off_z);

		void axes(int axes[]);

		void active(bool enable);
		void fastRead(bool enable);
		void lowNoise(bool enable);

		void reset(void);
		void selfTest(bool enable);
		void autoSleep(bool enable);

		void intDataRdy(bool enable, uint8_t pin);
		void intFreefallMotion(bool enable, uint8_t pin);
		void intPulse(bool enable, uint8_t pin);
		void intOrientation(bool enable, uint8_t pin);
		void intAutoSlp(bool enable, uint8_t pin);
};

#endif
