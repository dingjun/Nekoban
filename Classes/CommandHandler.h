#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <vector>

#include "cocos2d.h"
#include "Level.h"
#include "MoveUnitCommand.h"
#include "Unit.h"

class MoveUnitCommand;

/**
	Handler of list of commands for undo and redo
 */
class CommandHandler
{
public:
	CommandHandler(Level* level);
	~CommandHandler();

	void addCommand(Command* command);

	bool addMoveUnitCommand(Unit* unit, const cocos2d::Vec2& step);

	bool undo();
	bool redo();
	bool undoAll();
	bool redoAll();

	inline unsigned int getNumCommandsDone() { return _currentIndex; }

private:
	MoveUnitCommand* createValidMoveUnitCommand(Unit* unit, const cocos2d::Vec2& step, int force = 0);

	Level* _level;
	std::vector<Command*> _commands;
	unsigned int _currentIndex;
};

#endif // __COMMAND_HANDLER_H__
