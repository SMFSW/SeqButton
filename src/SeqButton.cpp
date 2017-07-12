/*!\file SeqButton.cpp
** \author SMFSW
** \version 1.2
** \date 2017/07/12
** \copyright BSD 3-Clause License (c) 2017, SMFSW
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

#define		TIME	((uint16_t) millis())


void SeqButton::init(uint8_t pin, void (*cbckON)(), void (*cbckOFF)(), bool repeat, bool logic, uint16_t filter)
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
	
	pusDone = false;
	relDone = true;
	butState = LOW;
	memTime = TIME;
}

void SeqButton::init(uint8_t pin, void (*cbckON)(), void (*cbckOFF)())
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
		if ((uint16_t) (TIME - memTime) >= timFilter)
		{
			relDone = false;
			butState = HIGH;
			if (!pusDone)
			{
				if(onPush)	// only if callback is defined
				{
					#if defined(DBG_SEQBUTTON)
						Serial.print("Push\n");
						dbg = true;
					#endif
					onPush();
				}
			}
			if (!Repeat)	{ pusDone = true; }
		}
	}
	else
	{
		memTime = TIME;
		pusDone = false;
		butState = LOW;
		
		if (!relDone)
		{
			relDone = true;
			if (onRelease)	{ onRelease(); }	// only if callback is defined
			#if defined(DBG_SEQBUTTON)
				Serial.print("Release\n");
				dbg = false;
			#endif
		}
	}
	
	return butState;
}

