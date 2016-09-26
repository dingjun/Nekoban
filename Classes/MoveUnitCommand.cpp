#include "MoveUnitCommand.h"

#include "Level.h"
#include "Resource.h"

USING_NS_CC;

MoveUnitCommand::MoveUnitCommand(Unit* unit, const Vec2& step, MoveUnitCommand* connectedCommand)
	: _unit(unit)
	, _connectedCommand(connectedCommand)
{
	_step.set(step);
}

MoveUnitCommand::~MoveUnitCommand()
{

}

void MoveUnitCommand::execute()
{
	Level* level = _unit->getLevel();

	if (_connectedCommand)
	{
		_connectedCommand->execute();
	}

	// move unit
	_unit->moveBy(sMoveUnitCommandSeconds, _step);
}

void MoveUnitCommand::undo()
{
	Level* level = _unit->getLevel();

	// move unit
	_unit->moveBy(sMoveUnitCommandSeconds, -_step);

	if (_connectedCommand)
	{
		_connectedCommand->undo();
	}
}
