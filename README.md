# SeqButton

[![author](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/auth_SMFSW.json)](https://github.com/SMFSW)
![badge](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/SeqButton_status_badge.json)
[![license](https://img.shields.io/badge/License-BSD3-darkred.svg)](LICENSE)
[![CodeFactor](https://www.codefactor.io/repository/github/smfsw/seqbutton/badge)](https://www.codefactor.io/repository/github/smfsw/seqbutton)

![platform](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/platform_INO.json)

[![doxy](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/tool_DOXY.json)](https://smfsw.github.io/SeqButton)
[![re_note](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/tool_RN.json)](ReleaseNotes.md)

Sequential Button Arduino Library

Handling filtered button press with callbacks for push (with or without repeat) and release, logic, filtering time and sequences.

## Usage

- Declare a `SeqButton` instance (called `sb` below)
- Create callback function(s) of type `void func()`
- Initialize instance with `sb.init(uint8_t pin, void (*cbckON)(SeqButton*), void (*cbckOFF)(SeqButton*), bool repeat, bool logic=LOW, uint16_t filter=50)`
  - `pin`: pin on which button is connected
  - `cbckON`: callback function on press (`NULL` when no callback needed)
  - `cbckOFF`: callback function on release (`NULL` when no callback needed)
  - `repeat`: callback called repeatedly when set to true
  - `logic`: Button logic: `LOW` for NO / `HIGH` for NC (internal pullup for input is enabled)
  - `filter`: filtering time (in ms)
- Call the handler in a loop using `sb.handler()` -> handler returns the current button value (if needed)
- `sb.getState()` or `sb.getButton()` can be used to get current button state at any time
- `sb.getPin()` can be used to check pin assigned to instance
- `sb.getHoldTime()` can be used on a release callback to get hold duration of button

## Examples included

- [AdvancedButton.ino](examples/AdvancedButton/AdvancedButton.ino): Toggle a LED at each button press (showing all init parameters)
- [CallbacksExample.ino](examples/CallbacksExample/CallbacksExample.ino): Toggle a LED at each push on button 1 and at each release on button 2
- [CombinationExample.ino](examples/CombinationExample/CombinationExample.ino): Prints messages to serial depending on combination read from inputs
- [OffTimerButton.ino](examples/OffTimerButton/OffTimerButton.ino): Turns a LED on when button is pressed, turning off 1s after release
- [RepeatButton.ino](examples/RepeatButton/RepeatButton.ino): Toggle a LED repeatedly when button pressed
- [SequenceExample.ino](examples/SequenceExample/SequenceExample.ino): Prints messages to serial depending on sequence read from inputs
- [TimingExample.ino](examples/TimingExample/TimingExample.ino): Toggle a LED at each push on button 1 or 2 if held for more than 1s
- [ToggleButton.ino](examples/ToggleButton/ToggleButton.ino): Toggle a LED at each button press
