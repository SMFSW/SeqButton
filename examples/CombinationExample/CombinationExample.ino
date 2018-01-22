/*
  Combination Example
  Prints messages to serial depending on combination read from inputs
  This example demonstrate how to make combinations with the library
  Please note this is certainly not an optimized way to treat a real keyboard.

  This example code is in the public domain.

  created 20 January 2018
  by SMFSW
 */

#include <SeqButton.h>

#define SetCombination_cback(name, b)	void Set_##name() { combination |= (1 << b); }
#define ResetCombination_cback(name, b)	void Reset_##name() { combination &= ~(1 << b); }


SeqButton		but1, but2, but3, but4;				// Declare buttons instances
SeqButton *		buttons[4] = { &but1, &but2, &but3, &but4 };

uint8_t combination = 0;	// Variable holding final value


SetCombination_cback(b1, 0);
SetCombination_cback(b2, 1);
SetCombination_cback(b3, 2);
SetCombination_cback(b4, 3);
ResetCombination_cback(b1, 0);
ResetCombination_cback(b2, 1);
ResetCombination_cback(b3, 2);
ResetCombination_cback(b4, 3);


// the setup function runs once when you press reset or power the board
void setup() {
	// initialize serial
	Serial.begin(115200);
	//while (!Serial) { };			// wait for serial port to connect. Needed for Leonardo only

	// initialize the button with callbacks on push/release (no repeat)
	but1.init(2, &Set_b1, &Reset_b1);	// Button on D2
	but2.init(3, &Set_b2, &Reset_b2);	// Button on D3
	but3.init(4, &Set_b3, &Reset_b3);	// Button on D4
	but4.init(5, &Set_b4, &Reset_b4);	// Button on D5
}

// the loop function runs over and over again forever
void loop() {
	for (unsigned int i = 0 ; i < (sizeof(buttons) / sizeof(SeqButton*)) ; i++)		{ buttons[i]->handler(); }
	treat_combination();
}


uint8_t check_combination(uint8_t val) {
	uint8_t nbBits = 0;
	for (unsigned int i = 0 ; i < 8 ; i++)	{ if (val & (1 << i))	nbBits++; }
	return nbBits;
}


void treat_combination() {
	String parity = "";
	static uint8_t mem_combination = 0;
	
	if (combination != mem_combination)
	{
		mem_combination = combination;
		
		// parity += (combination & 0x1) ? "odd" : "even";
		// Switch used in order to demonstrate different cases possible actions
		switch (combination)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 9:
			case 11:
			case 13:
			case 15:
				parity += "odd";
				break;
			
			default:
				parity += "even";
				break;
		}
		
		Serial.print("Combination ");
		Serial.print(combination);
		Serial.print(" is ");
		Serial.print(parity);
		Serial.print(" with ");
		Serial.print(check_combination(combination));
		Serial.println(" bit(s) raised.");
	}
}
