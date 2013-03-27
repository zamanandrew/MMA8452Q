/*
 * Move the mouse of a PC according to the inclination of the accelerometer.
 *
 * (Only works with Arduino Leonardo and Micro)
 */

#include <MMA8452Q.h>

MMA8452Q accel;

int axes[3];

void setup() {
	Serial.begin(9600);

	Mouse.begin();
	accel.begin();
}

void loop() {
	int move_x = 0,
	    move_y = 0;

	accel.axes(axes);

	move_x = map(axes[0], -1024, 1024, -100, 100);
	move_y = map(axes[1], -1024, 1024, -100, 100);

	Mouse.move(move_x, move_y, 0);

	delay(100);
}
