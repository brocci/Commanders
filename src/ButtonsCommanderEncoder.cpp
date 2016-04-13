/*************************************************************
project: <Commanders>
author: <Thierry PARIS>
description: <Encoder returning a current value, or a moving direction.>
*************************************************************/

#include "ButtonsCommanderEncoder.hpp"

ButtonsCommanderEncoder::ButtonsCommanderEncoder(unsigned long inId, int inStartingValue, int inMinimum, int inMaximum, bool inAssociatedPushButton) : ButtonsCommanderButton(inId)
{
	this->mini = inMinimum;
	this->maxi = inMaximum;
	this->currentValue = inStartingValue;

	if (inAssociatedPushButton)
	{
		this->pPush = new ButtonsCommanderPush((byte)1);
	}
	else
	{
		this->pPush = 0;
	}
}

void ButtonsCommanderEncoder::begin(int inPin1, int inPin2)
{
	this->pin1 = Arduino_to_GPIO_pin(inPin1);
	this->pin2 = Arduino_to_GPIO_pin(inPin2);
	pinMode2f(this->pin1, INPUT);
	pinMode2f(this->pin2, INPUT);
	digitalWrite2f(this->pin1, HIGH); //turn pullup resistor on
	digitalWrite2f(this->pin2, HIGH); //turn pullup resistor on
	this->lastEncoded = 0;
}

unsigned long ButtonsCommanderEncoder::loop()
{
	int MSB = digitalRead2f(this->pin1); //MSB = most significant bit
	int LSB = digitalRead2f(this->pin2); //LSB = least significant bit

	int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
	if (encoded == 0)
		return UNDEFINED_ID;
	int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

	char inc = 0;
	if (sum == 13 || sum == 4 || sum == 2 || sum == 11) inc = 1;
	if (sum == 14 || sum == 7 || sum == 1 || sum ==  8) inc = -1;
	
	lastEncoded = encoded; //store this value for next time

	if (this->mini != this->maxi)
	{
		// If the encoder has been defined with a mini/maxi interval,
		// move the value and return it !
		this->currentValue += inc;

		if (this->currentValue > this->maxi)
			this->currentValue = this->maxi;

		if (this->currentValue < this->mini)
			this->currentValue = this->mini;

		eventType = COMMANDERS_EVENT_ABSOLUTEMOVE;
		eventData = this->currentValue;
	}
	else
	{
		// if no interval defined, just return the move direction.
		eventType = COMMANDERS_EVENT_RELATIVEMOVE;
		eventData = inc;
	}

	Commander::RaiseEvent(this->GetId(), eventType, eventData);
	return this->GetId();
}
