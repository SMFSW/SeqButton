/*
  Sequence Example
  Prints messages to serial depending on sequence read from inputs

  This example code is in the public domain.

  created 20 January 2018
  modified 15 July 2018
  by SMFSW
 */

#include <string.h>
#include <SeqButton.h>

#define		k1					1		// Value for button 1
#define		k2					2		// Value for button 2
#define		k3					3		// Value for button 3

#define		SEQUENCE_TIMEOUT	700		// Timeout for sequence (in ms)

#define Action_cback(name, msg)			void Msg_##name() { Serial.println(msg); }


typedef struct sequence {	// Sequence structure and output message
	uint8_t	seq[5];
	uint8_t	nb;
	void (*action)(void);
} sequence;

SeqButton		but1, but2, but3;				// Declare buttons instances
SeqButton *		buttons[3] = { &but1, &but2, &but3 };

uint8_t seq_tab[6];			// Tab holding sequence
uint8_t idx_seq_tab;		// Variable holding current index in the sequence tab

uint32_t mem_timeout = 0;	// Timeout for sequence


Action_cback(seq1, "Try again!");
Action_cback(seq2, "Niaga yrt!");
Action_cback(seq3, "This gets better...");
Action_cback(seq4, "You're almost there...");
Action_cback(seq5, "YOU WON!!!");


sequence seq[5] = {
	// NOTE 1: sequences have to be declared in order (lowest number of keys sequence to highest)
	// NOTE 2: don't use circular buffer in code, otherwise when checking on whole tab, it could find the inappropriate sequence first
	{ { k1,	k2,	0,	0,	0	}, 2, &Msg_seq1 },
	{ { k2,	k1,	0,	0,	0	}, 2, &Msg_seq2 },
	{ { k3,	k1,	k2,	0,	0	}, 3, &Msg_seq3 },
	{ { k3,	k1,	k2,	k1,	0	}, 4, &Msg_seq4 },
	{ { k3,	k1,	k2,	k1,	k3	}, 5, &Msg_seq5 }
};


// the setup function runs once when you press reset or power the board
void setup() {
	// initialize serial
	Serial.begin(115200);
	//while (!Serial) { };			// wait for serial port to connect. Needed for Leonardo only

	// Erase sequence tab
	sequence_reset(seq_tab, sizeof(seq_tab), &idx_seq_tab);

	// initialize the button with callbacks on push/release (no repeat)
	but1.init(2, &AddToSequence_cback);	// Button on D2
	but2.init(3, &AddToSequence_cback);	// Button on D3
	but3.init(4, &AddToSequence_cback);	// Button on D4
}

// the loop function runs over and over again forever
void loop() {
	for (unsigned int i = 0 ; i < (sizeof(buttons) / sizeof(SeqButton*)) ; i++)		{ buttons[i]->handler(); }
	sequence_handler(seq, sizeof(seq) / sizeof(sequence), seq_tab, sizeof(seq_tab), &idx_seq_tab);
}


void AddToSequence_cback(SeqButton * button) {
	sequence_append(button->getPin() - 1, seq_tab, sizeof(seq_tab), &idx_seq_tab);	// pin - 1 : buttons on pins 2, 3, 4
	mem_timeout = millis(); }


void sequence_handler(sequence * pMatch, const uint8_t szMatch, uint8_t * pSeq, const uint8_t szSeq, uint8_t * pIdx) {
	if (	(mem_timeout != 0)
		&&	((millis() - mem_timeout) >= SEQUENCE_TIMEOUT))
	{
		mem_timeout = 0;
		sequence_find(pMatch, szMatch, pSeq, szSeq, pIdx);
	}
}

void sequence_reset(uint8_t * pSeq, const uint8_t szSeq, uint8_t * pIdx) {
	*pIdx = 0;					// Clear index
	memset(pSeq, 0, szSeq);		// Clear tab
}

void sequence_append(uint8_t val, uint8_t * pSeq, const uint8_t szSeq, uint8_t * pIdx)
{
	if (*pIdx < szSeq)	{ pSeq[(*pIdx)++] = val; }	// Tab not totally filled, append value to current cell & increment
	else											// Tab totally filled
	{
		memcpy(&pSeq[0], &pSeq[1], szSeq-1);		// Move cells to cells-1
		pSeq[*pIdx - 1] = val;						// Append value to last cell
	}
}

void sequence_find(sequence * pMatch, const uint8_t szMatch, uint8_t * pSeq, const uint8_t szSeq, uint8_t * pIdx)
{
	bool seq_found = false;

	pMatch = &pMatch[szMatch - 1];							// Sequence pointer positioned on last entry
	for (int s = 0 ; s < szMatch ; s++)						// Sequence to check loop
	{
		for (int j = 0 ; j < szSeq ; j++)					// Input sequence positioning loop
		{
			// If check sequence length is greater than remaining input sequence, break input sequence positioning loop
			if (pMatch->nb > (szSeq - j))	{ break; }

			for (int i = 0, idx = j; i < pMatch->nb ; i++)	// Match check loop
			{
				if (pMatch->seq[i] == pSeq[idx])			// Matching
				{
					// If numbers of cells validated correspond to sequence size, sequence is found
					if (i == pMatch->nb - 1)	{ seq_found = true; }
					// Input sequence cell increment
					if (++idx >= szSeq)			{ idx = 0; }
				}
				else break;										// Not matching, break match check loop
			}
		}

		if (seq_found)	{ break; }	// If sequence is found, break current sequence to check loop
		pMatch--;					// Previous sequence
	}

	if (seq_found)	{ pMatch->action(); }	// Execute action if sequence found

	sequence_reset(pSeq, szSeq, pIdx);		// Reset sequence
}
