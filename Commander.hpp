//-------------------------------------------------------------------
#ifndef __commander_H__
#define __commander_H__
//-------------------------------------------------------------------

#define  GPIO2_PREFER_SPEED    1
#ifdef VISUALC
#include "VStudio/arduino2.hpp"
#else
#include "arduino2.hpp"
#endif

enum COMMANDERS_EVENT_TYPE
{
	EVENT_NONE = 0,			// Should never appear
	EVENT_SELECTED = 1,		// If a push button or similar is pressed
	EVENT_ABSOLUTEMOVE = 2,	// If a potentiometer or similar is moved
	EVENT_RELATIVEMOVE = 3	// If an encoder or similar is moved
};

class Commander;

typedef void(*EventHandlerFunction)(unsigned long inId, COMMANDERS_EVENT_TYPE inEvent, int inData);

#ifndef UNDEFINED_ID
#define UNDEFINED_ID	((unsigned long)-1)
#endif

class Commander
{
	public:
		unsigned long Id;
		Commander *pNextCommander;

		// Start of the linked list of all commanders. Each commander have the address of its follower or NULL !
		static Commander *pFirstCommander;
		static EventHandlerFunction EventHandler;

	public:
		inline Commander() { AddCommander(this); pNextCommander = 0; }
		
	public:
		virtual void Setup() {}
		inline virtual unsigned long Loop() { return UNDEFINED_ID; }
		inline virtual void PriorityLoop() { }
		void CommanderPriorityLoop();

		static void AddCommander(Commander *inCommander);
		static void Loops();

#ifdef DEBUG_MODE
	public:
		void CheckIndex(byte inIndex, const __FlashStringHelper *infunc);
#endif
};

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
