/*
  Off Timer Button
  Turns a LED on when button is pressed, turning off 1s after release

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

void callbackPush(SeqButton * button)
{
	digitalWrite(13, HIGH);		// turn the LED ON

	(void) button;	// Dummy read of instance to avoid warning by compiler
}

void callbackRelease(SeqButton * button)
{
	delay(1000);
	digitalWrite(13, LOW);		// turn the LED OFF

	(void) button;	// Dummy read of instance to avoid warning by compiler
}

// the setup function runs once when you press reset or power the board
void setup() {
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);

	// initialize the button with callbacks
	but.init(2, &callbackPush, &callbackRelease, false, LOW, 50);
}

// the loop function runs over and over again forever
void loop() {
	but.handler();
}
