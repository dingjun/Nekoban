#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "Unit.h"

class Unit;

/**
	Component of unit to handle input
 */
class InputComponent
{
public:
	InputComponent();
	virtual ~InputComponent();

	void handleKeyboardInput(cocos2d::EventKeyboard::KeyCode keyCode, Unit* unit);
};

#endif // __INPUT_COMPONENT_H__
