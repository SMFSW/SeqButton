/*!\file SeqButton.h
** \author SMFSW
** \date 2018/07/15
** \copyright BSD 3-Clause License (c) 2017-2018, SMFSW
** \brief Sequential Button Arduino Library
** \details Handling filtered button press with callbacks for push (with or without repeat) and release, logic and filtering time
**/

#ifndef SeqButton_h
#define SeqButton_h

#include <inttypes.h>

//#define		DBG_SEQBUTTON


/*!	\class SeqButton SeqButton.h "SeqButton/SeqButton.h"
**	\brief Class containing the required methods for handling sequential button
**/
class SeqButton
{
private:
	uint32_t	memTime;					//!< Previously recorded timer
	uint32_t	holdTime;					//!< Time button held
	bool		butState;					//!< Memorized button state
	uint8_t		holdDone		:1;			//!< Time for button hold already memorized
	uint8_t		pusDone			:1;			//!< ON function already called
	uint8_t		relDone			:1;			//!< OFF function already called

	uint8_t		Pin;						//!< Pin on which button is connected
	uint32_t	timFilter;					//!< Filtering time (in ms)
	bool		Logic;						//!< Button logic: LOW for NO / HIGH for NC (internal pullup for input is enabled)
	bool		Repeat;						//!< Push callback repeated calls

	void		(*onPush)(SeqButton*);		//!< Push callback ON function pointer
	void		(*onRelease)(SeqButton*);	//!< Push callback OFF function pointer

public:
	/*!	\brief Initialization routine
	**	\note Input pin is configured with device internal pullup
	**	\param [in] pin - Pin on which button is connected
	**	\param [in] repeat - callback called repeatedly when set to true
	**	\param [in] logic - Button logic: LOW for NO / HIGH for NC (internal pullup for input is enabled)
	**	\param [in] filter - filtering time (in ms)
	**	\param [in] cbckON - callback function on press (NULL when no callback needed)
	**	\param [in] cbckOFF - callback function on release (NULL when no callback needed)
	**	\note Callbacks have to be declared using an SeqButton* as parameter (instance is passed to the callback function)
	**	\return nothing
	**/
	void init(const uint8_t pin, void (*cbckON)(SeqButton*), void (*cbckOFF)(SeqButton*), const bool repeat, const bool logic=LOW, const uint32_t filter=50);

	/*!	\brief Initialization routine
	**	\note Input pin is configured with device internal pullup
	**	\param [in] pin - Pin on which button is connected
	**	\param [in] cbckON - callback function on press (NULL when no callback needed)
	**	\param [in] cbckOFF - callback function on release (NULL when no callback needed)
	**	\note Callbacks have to be declared using an SeqButton* as parameter (instance is passed to the callback function)
	**	\return nothing
	**/
	void init(uint8_t pin, void (*cbckON)(SeqButton*), void (*cbckOFF)(SeqButton*)=NULL);

	/*!	\brief Check button state and perform callbacks accordingly
	**	\note handler for button, this function has to be called in a pseudo main loop to work properly
	**	\return Current button state
	**/
	bool handler(void);

	/*!	\brief Get button pin
	**	\return Current pin assigned to instance
	**/
	uint8_t getPin(void) __attribute__((always_inline)) {
		return Pin; }

	/*!	\brief Get button state
	**	\return Current button state
	**/
	bool getState(void) __attribute__((always_inline)) {
		return butState; }

	/*!	\brief Get button state
	**	\deprecated getButton was already used in SeqButton lib, alias is made to keep compatibility with earlier versions
	**	\return Current button state
	**/
	bool getButton(void) __attribute__((always_inline)) {
		return getState(); }

	/*!	\brief Get button hold duration
	**	\return Current button hold duration
	**/
	uint32_t getHoldTime(void) __attribute__((always_inline)) {
		return holdTime; }
};


#endif /* SeqButton_h */
