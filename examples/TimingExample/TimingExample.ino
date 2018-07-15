/*
  Timing Example
  Toggle a LED at each push on button 1 or 2 if held for more than 1s
  Actions for button 3 discarded from the callbacks for example

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  created 15 July 2018
  by SMFSW
 */

#include <SeqButton.h>

#define B1_PIN		2		// Pin assigned to button 1
#define B2_PIN		3		// Pin assigned to button 2
#define B3_PIN		4		// Pin assigned to button 3

#define HOLD_TIME	1000	// Time to hold a button

SeqButton	but1, but2, but3;		// Declare buttons
uint32_t	time_b1, time_b2;		// Variables to keep track of time when buttons pushed

void ToggleLED(void)
{
	static boolean LEDState = LOW;	// State HIGH/LOW

	LEDState = !LEDState;			// Change LED
	digitalWrite(13, LEDState);		// turn the LED into LEDState
}

// the setup function runs once when you press reset or power the board
void setup() {
	// initialize serial
	Serial.begin(115200);
	//while (!Serial) { };			// wait for serial port to connect. Needed for Leonardo only

	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);

	// initialize the buttons handled with callbacks on push & release
	but1.init(B1_PIN, &Push_callback, &Release_callback);
	but2.init(B2_PIN, &Push_callback, &Release_callback);
	but3.init(B3_PIN, &Push_callback, &Release_callback);
}

// the loop function runs over and over again forever
void loop() {
	but1.handler();
	but2.handler();
	but3.handler();
}

void Push_callback(uint8_t pin) {
	uint32_t * var;

	switch (pin)
	{
		case B1_PIN:
			var = &time_b1;
			break;

		case B2_PIN:
			var = &time_b2;
			break;

		default:
			return;
	}

	*var = millis();
}

void Release_callback(uint8_t pin) {
	uint32_t time_push = 0;

	switch (pin)
	{
		case B1_PIN:
			time_push = millis() - time_b1;
			Serial.print("B1 held for: ");
			break;

		case B2_PIN:
			time_push = millis() - time_b2;
			Serial.print("B2 held for: ");
			break;

		default:
			Serial.println("Button not handled, discarding action");
			return;
	}
	Serial.print(time_push);
	Serial.println("ms");

	if (time_push > HOLD_TIME)
	{
		Serial.println("Toggling LED");
		ToggleLED();
	}
}
