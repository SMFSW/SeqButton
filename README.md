# SeqButton
Sequential Button Arduino Library

Handling filtered button press with callbacks for push (with or without repeat) and release, logic and filtering time.


## Usage: 
- Declare a SeqButton instance (called _sb_ below)
- Create callback function(s) of type _void func()_
- Initialise instance with _sb.init(uint8_t pin, void (*cbckON)(), void (*cbckOFF)(), bool repeat, bool logic=LOW, uint16_t filter=50)_
  - pin - Pin on which button is connected
  - cbckON: callback function on press (NULL when no callback needed)
  - cbckOFF: callback function on release (NULL when no callback needed)
  - repeat: callback called repeatedly when set to true
  - logic: Button logic: LOW for NO / HIGH for NC (internal pullup for input is enabled)
  - filter: filtering time (in ms)
- Call the handler in a loop using _sb.handler()_ -> handler returns the current button value (if needed)
- _sb.getButton()_ can be used to get current button state at any time

## Examples included:
- AdvancedButton.ino: Toggle a LED at each button press (showing all init parameters)
- CallbacksExample.ino: Toggle a LED at each push on button 1 and at each release on button 2
- OffTimerButton.ino: Turns a LED on when button is pressed, turnig off 1s after releae
- RepeatButton.ino: Toggle a LED repeatedly when button pressed
- ToggleButton.ino: Toggle a LED at each button press

## Misc:
Doxygen doc can be generated for the class using doxyfile.

Feel free to share your thoughts @ xgarmanboziax@gmail.com about:
  - issues encountered
  - optimisations
  - improvements & new functionalities
