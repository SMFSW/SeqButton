/*!\file SeqButton.cpp
** \author SMFSW
** \date 2018/07/15
** \copyright BSD 3-Clause License (c) 2017-2018, SMFSW
** \brief Sequential Button Arduino Library
** \details Handling filtered button press with callbacks for push (with or without repeat) and release, logic and filtering time
**/


#if ARDUINO > 22
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#if defined(DBG_SEQBUTTON)
#include <HardwareSerial.h>
#endif

#include "SeqButton.h"

#define		TIME	millis()


void SeqButton::init(const uint8_t pin, void (*cbckON)(SeqButton*), void (*cbckOFF)(SeqButton*), const bool repeat, const bool logic, const uint32_t filter)
{
	#if defined(DBG_SEQBUTTON)
		Serial.begin(115200);
	#endif

	pinMode(pin, INPUT_PULLUP);

	Pin = pin;
	Logic = logic;
	Repeat = repeat;
	timFilter = filter;

	onPush = cbckON;
	onRelease = cbckOFF;

	holdDone = false;
	pusDone = false;
	relDone = true;

	butState = LOW;
	holdTime = 0;
	memTime = TIME;
}

void SeqButton::init(const uint8_t pin, void (*cbckON)(SeqButton*), void (*cbckOFF)(SeqButton*))
{
	init(pin, cbckON, cbckOFF, false, LOW, 50);
}

bool SeqButton::handler(void)
{
	#if defined(DBG_SEQBUTTON)
		static bool dbg = false;
	#endif

	if (digitalRead(Pin) == Logic)
	{
		if ((TIME - memTime >= timFilter) || (holdDone))
		{
			relDone = false;
			butState = HIGH;

			if (!pusDone)
			{
				if (onPush)	// only if callback is defined
				{
					#if defined(DBG_SEQBUTTON)
						Serial.print("Push\n");
						dbg = true;
					#endif
					onPush(this);
				}
			}

			if (!Repeat)	{ pusDone = true; }

			if (!holdDone)
			{
				memTime = TIME;		// Store current time for holdTime calculations
				holdDone = true;
			}

			holdTime = TIME - memTime;
		}
	}
	else
	{
		holdTime = TIME - memTime;	// Compute holdTime once more before memTime is re-written
		memTime = TIME;
		pusDone = false;
		holdDone = false;
		butState = LOW;

		if (!relDone)
		{
			relDone = true;
			if (onRelease)	{ onRelease(this); }	// only if callback is defined
			#if defined(DBG_SEQBUTTON)
				Serial.print("Release\n");
				dbg = false;
			#endif
		}
	}

	return butState;
}

