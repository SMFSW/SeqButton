/*!\file SeqButton.h
** \author SMFSW
** \date 2017/11/21
** \copyright BSD 3-Clause License (c) 2017, SMFSW
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
	uint32_t	memTime;			//!< Previously recorded timer
	bool		butState;			//!< Memorised button state
	bool		pusDone;			//!< ON function already called
	bool		relDone;			//!< OFF function already called
	
	uint8_t		Pin;				//!< Pin on which button is connected
	uint32_t	timFilter;			//!< Filtering time (in ms)
	bool		Logic;				//!< Button logic: LOW for NO / HIGH for NC (internal pullup for input is enabled)
	bool		Repeat;				//!< Push callback repeated calls
	
	void		(*onPush)();		//!< Push callback ON function pointer
	void		(*onRelease)();		//!< Push callback OFF function pointer

public:
	/*!	\brief Initialisation routine
	**	\note Input pin is configured with device internal pullup
	**	\param [in] pin - Pin on which button is connected
	**	\param [in] cbckON - callback function on press (NULL when no callback needed)
	**	\param [in] cbckOFF - callback function on release (NULL when no callback needed)
	**	\param [in] repeat - callback called repeatedly when set to true
	**	\param [in] logic - Button logic: LOW for NO / HIGH for NC (internal pullup for input is enabled)
	**	\param [in] filter - filtering time (in ms)
	**	\return nothing
	**/
	void init(const uint8_t pin, void (*cbckON)(void), void (*cbckOFF)(void), const bool repeat, const bool logic=LOW, const uint32_t filter=50);
	
	/*!	\brief Initialisation routine
	**	\note Input pin is configured with device internal pullup
	**	\param [in] pin - Pin on which button is connected
	**	\param [in] cbckON - callback function on press (NULL when no callback needed)
	**	\param [in] cbckOFF - callback function on release (NULL when no callback needed)
	**	\return nothing
	**/
	void init(uint8_t pin, void (*cbckON)(void), void (*cbckOFF)(void)=NULL);
	
	/*!	\brief Check button state and perform callbacks accordingly
	**	\note handler for button, this function has to be called in a pseudo main loop to work properly
	**	\return Current button state
	**/
	bool handler(void);

	/*!	\brief Get button state
	**	\return Current button state
	**/
	bool getButton(void) __attribute__((always_inline)) {
		return butState; }
};


#endif /* SeqButton_h */
