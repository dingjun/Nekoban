#include "InputComponent.h"

#include "Level.h"
#include "MoveUnitCommand.h"

USING_NS_CC;

InputComponent::InputComponent()
{

}

InputComponent::~InputComponent()
{

}

void InputComponent::handleKeyboardInput(EventKeyboard::KeyCode keyCode, Unit* unit)
{
	Level* level = unit->getLevel();

	// ignore input when level is completed
	if (level->isCompleted())
	{
		return;
	}

	Vec2 step = Vec2::ZERO;

	// check keyboard input
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:			// left
	case EventKeyboard::KeyCode::KEY_A:
		step.x -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:			// right
	case EventKeyboard::KeyCode::KEY_D:
		step.x += 1;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:				// up
	case EventKeyboard::KeyCode::KEY_W:
		step.y -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:			// down
	case EventKeyboard::KeyCode::KEY_S:
		step.y += 1;
		break;
	default:
		return;
	}

	level->getCommandHandler()->addMoveUnitCommand(unit, step);
}
