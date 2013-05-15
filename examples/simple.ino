#include <MMA8452Q.h>

MMA8452Q accel;

int axes[3];
uint8_t orientation;

void setup() {
	Serial.begin(9600);

	if (accel.begin())
		while (1); /* error */

	/* the board MUST be inactive during setup */
	accel.active(false);

	/* set scale to 2g (default) */
	accel.scale(2);

	/* disable fast read (default) */
	accel.fastRead(false);

	/* enable orientation detection */
	accel.detectOrientation(true);

	/* enable auto-sleep/wake mode */
	/* accel.autoSleep(true); */

	/* enable low noise mode */
	/* accel.lowNoise(true); */

	/* calibrate axes */
	/* accel.offset(-10, -2, 0); */

	/* enable the board */
	accel.active(true);
}

void loop() {
	/* check board current mode */
	switch (accel.sysmod()) {
		case MMA8452Q::STANDBY:
			Serial.println("StandBy");
			break;

		case MMA8452Q::SLEEP:
			Serial.println("Sleep");
			break;

		case MMA8452Q::WAKE:
			Serial.println("Wake");
			break;
	}

	/* get and print raw axes values */
	accel.axes(axes);

	Serial.print("x: ");
	Serial.print(axes[0]);
	Serial.print(", y: ");
	Serial.print(axes[1]);
	Serial.print(", z: ");
	Serial.println(axes[2]);

	/* get orientation status and check if it changed from last read */
	if (accel.orientation(&orientation)) {
		/* get and print portrait orientation status */
		switch (accel.portrait(orientation)) {
			case HIGH:
				Serial.println("Portrait Up");
				break;

			case LOW:
				Serial.println("Portrait Down");
				break;

			default:
				Serial.println("No Portrait");
				break;
		}

		/* get and print landscape orientation status */
		switch (accel.landscape(orientation)) {
			case HIGH:
				Serial.println("Landscape Right");
				break;

			case LOW:
				Serial.println("Landscape Left");
				break;

			default:
				Serial.println("No Landscape");
				break;
		}

		/* get and print back/front orientation status */
		if (accel.backFront(orientation))
			Serial.println("Back");
		else
			Serial.println("Front");
	}

	delay(1000);
}
