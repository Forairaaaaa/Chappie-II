/*
	Button - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/

#include "Button.h"
#include <Arduino.h>

__Button::__Button(uint8_t pin, uint16_t debounce_ms)
:  _pin(pin)
,  _delay(debounce_ms)
,  _state(HIGH)
,  _ignore_until(0)
,  _has_changed(false)
{
    pinMode(pin, INPUT_PULLUP);
}

void __Button::begin()
{
	pinMode(_pin, INPUT_PULLUP);
}

// 
// public methods
// 

bool __Button::read()
{
	// ignore pin changes until after this delay time
	if (_ignore_until > millis())
	{
		// ignore any changes during this period
	}
	
	// pin has changed 
	else if (digitalRead(_pin) != _state)
	{
		_ignore_until = millis() + _delay;
		_state = !_state;
		_has_changed = true;
	}
	
	return _state;
}

// has the button been toggled from on -> off, or vice versa
bool __Button::toggled()
{
	read();
	return has_changed();
}

// mostly internal, tells you if a button has changed after calling the read() function
bool __Button::has_changed()
{
	if (_has_changed)
	{
		_has_changed = false;
		return true;
	}
	return false;
}

// has the button gone from off -> on
bool __Button::pressed()
{
	return (read() == PRESSED && has_changed());
}

// has the button gone from on -> off
bool __Button::released()
{
	return (read() == RELEASED && has_changed());
}