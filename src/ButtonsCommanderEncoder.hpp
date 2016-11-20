//-------------------------------------------------------------------
#ifndef __buttonsCommanderEncoder_H__
#define __buttonsCommanderEncoder_H__
//-------------------------------------------------------------------

#include "Commanders.h"
#ifndef NO_BUTTONSCOMMANDER
#ifndef NO_BUTTONSCOMMANDERENCODER

class ButtonsCommanderPush;

//-------------------------------------------------------------------

class ButtonsCommanderEncoder : public ButtonsCommanderButton
{
 private:
	int currentValue;
	int startingCurrentValue;
	GPIO_pin_t pin1;
	GPIO_pin_t pin2;
	int mini, maxi;
	int lastEncoded;

 public:
	ButtonsCommanderEncoder();

	inline int GetPosition() const { return this->currentValue; }
	inline void ResetStartingPosition() { this->currentValue = this->startingCurrentValue; }

	void begin(unsigned long inId, int inPin1, int inPin2, int inStartingCurrentValue = 0, int inMinimum = 0, int inMaximum = 0);
	unsigned long loop();
#ifdef COMMANDERS_PRINT_COMMANDERS
	void printCommander();
#endif
};
//-------------------------------------------------------------------
#endif
#endif
#endif
