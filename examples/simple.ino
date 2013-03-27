#include <MMA8452Q.h>

MMA8452Q accel;

int axes[3];
uint8_t orientation;

void setup() {
	Serial.begin(9600);

	if (accel.begin())
		while (1); /* error */

	accel.active(false);

	/* set scale to 2g (default) */
	accel.scale(2);

	/* disable fast read (default) */
	accel.fastRead(false);

	/* enable orientation detection */
	accel.detectOrientation(true);

	/* calibrate axes */
	/* accel.offset(-10, -2, 0); */

	accel.active(true);
}

void loop() {
	accel.axes(axes);

	Serial.print("x: ");
	Serial.print(axes[0]);
	Serial.print(", y: ");
	Serial.print(axes[1]);
	Serial.print(", z: ");
	Serial.println(axes[2]);

	if (accel.orientation(&orientation)) {
		switch (accel.portrait(orientation)) {
			case HIGH: Serial.println("Portrait Up"); break;
			case LOW: Serial.println("Portrait Down"); break;
		}

		switch (accel.landscape(orientation)) {
			case HIGH: Serial.println("Landscape Right"); break;
			case LOW: Serial.println("Landscape Left"); break;
		}

		if (accel.backFront(orientation))
			Serial.println("Back");
		else
			Serial.println("Front");
	}

	delay(1000);
}
