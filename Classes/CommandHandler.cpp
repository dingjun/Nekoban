#include "CommandHandler.h"

#include "Level.h"
#include "UnitTypeHandler.h"

USING_NS_CC;

CommandHandler::CommandHandler(Level* level)
	: _level(level)
	, _currentIndex(0)
{

}

CommandHandler::~CommandHandler()
{
	for (auto command : _commands)
	{
		delete command;
	}
	_commands.clear();
}

void CommandHandler::addCommand(Command* command)
{
	command->execute();

	// delete the commands after the current commands
	_commands.erase(_commands.begin() + _currentIndex, _commands.end());

	_commands.push_back(command);
	_currentIndex = _commands.size();
	_level->updateStatusLabel();
}

bool CommandHandler::addMoveUnitCommand(Unit* unit, const Vec2& step)
{
	Command* command = createValidMoveUnitCommand(unit, step, 1);
	if (command)
	{
		addCommand(command);
		return true;
	}
	return false;
}

bool CommandHandler::undo()
{
	if (_currentIndex == 0)
	{
		return false;
	}

	_commands[--_currentIndex]->undo();
	_level->updateStatusLabel();
	return true;
}

bool CommandHandler::redo()
{
	if (_currentIndex == _commands.size())
	{
		return false;
	}

	_commands[_currentIndex++]->execute();
	_level->updateStatusLabel();
	return true;
}

bool CommandHandler::undoAll()
{
	if (undo())
	{
		while (undo());
		return true;
	}
	return false;
}

bool CommandHandler::redoAll()
{
	if (redo())
	{
		while (redo());
		return true;
	}
	return false;
}

MoveUnitCommand* CommandHandler::createValidMoveUnitCommand(Unit* unit, const Vec2& step, int force)
{
	Level* level = unit->getLevel();
	UnitTypeHandler* unitTypeHandler = level->getUnitTypeHandler();
	Vec2 coordinate = unit->getCoordinate() + step;
	Unit* staticUnit = level->getStaticUnit(coordinate);
	Unit* dynamicUnit = level->getDynamicUnit(coordinate);

	// no static unit or it is wall
	if (!staticUnit || staticUnit->hasSameUnitType(unitTypeHandler->getWallUnitType()))
	{
		return nullptr;
	}

	// no dynamic unit
	if (!dynamicUnit)
	{
		return new MoveUnitCommand(unit, step);
	}

	// dynamic unit is box
	if (dynamicUnit->hasSameUnitType(unitTypeHandler->getBoxUnitType()))
	{
		if (--force < 0)
		{
			return nullptr;
		}

		// recursively check
		MoveUnitCommand* connectedCommand = createValidMoveUnitCommand(dynamicUnit, step, force);
		if (connectedCommand)
		{
			return new MoveUnitCommand(unit, step, connectedCommand);
		}
		return nullptr;
	}

	return nullptr;
}
