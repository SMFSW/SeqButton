/*
  Toggle Button
  Toggle a LED at each button press

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  created 20 March 2017
  modified 15 July 2018
  by SMFSW
 */

#include <SeqButton.h>

SeqButton	but;				// Declare button

void ToggleLED(SeqButton * button)
{
	static boolean LEDState = LOW;	// State HIGH/LOW

	LEDState = !LEDState;			// Change LED
	digitalWrite(13, LEDState);		// turn the LED into LEDState

	(void) button;	// Dummy read of instance to avoid warning by compiler
}

// the setup function runs once when you press reset or power the board
void setup() {
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);

	// initialize the button with callback (no repeat)
	but.init(2, &ToggleLED);
}

// the loop function runs over and over again forever
void loop() {
	but.handler();
}
