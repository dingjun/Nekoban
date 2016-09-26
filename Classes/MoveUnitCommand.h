#ifndef __MOVE_UNIT_COMMAND_H__
#define __MOVE_UNIT_COMMAND_H__

#include "cocos2d.h"
#include "Command.h"
#include "Unit.h"

/**
	Command to move an assigned unit
 */
class MoveUnitCommand : public Command
{
public:
	MoveUnitCommand(Unit* unit, const cocos2d::Vec2& coordinate, MoveUnitCommand* connectedCommand = nullptr);
	virtual ~MoveUnitCommand();

	virtual void execute();
	virtual void undo();

private:
	Unit* _unit;
	cocos2d::Vec2 _step;
	MoveUnitCommand* _connectedCommand;
};

#endif // __MOVE_UNIT_COMMAND_H__
