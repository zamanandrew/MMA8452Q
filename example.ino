#include <MMA8452Q.h>

MMA8452Q accel;

int axes[3];

void setup() {
	Serial.begin(9600);

	if (accel.begin())
		while (1); /* error */

	accel.active(false);

	accel.scale(2);
	accel.fastRead(false);
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

	delay(1000);
}
