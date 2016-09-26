#include "LevelHandler.h"

USING_NS_CC;

LevelHandler::LevelHandler()
	: _nextLevelIndex(0)
	, _level(nullptr)
{
	// TODO: dynamic load level files
	_numLevels = 6;
	_levelNames = new const char*[_numLevels];
	_levelNames[0] = sLevel_1;
	_levelNames[1] = sLevel_2;
	_levelNames[2] = sLevel_3;
	_levelNames[3] = sLevel_4;
	_levelNames[4] = sLevel_5;
	_levelNames[5] = sLevel_6;
}

LevelHandler::~LevelHandler()
{
	delete[] _levelNames;
	removeLevel();
}

bool LevelHandler::nextLevel(Node* node)
{
	removeLevel();
	_level = Level::create(_levelNames[_nextLevelIndex++]);

	// loop levels for now
	if (_nextLevelIndex == _numLevels)
	{
		_nextLevelIndex = 0;
	}

	// attach level
	if (_level)
	{
		node->addChild(_level);
		return true;
	}
	return false;
}

bool LevelHandler::undo()
{
	if (_level)
	{
		return _level->getCommandHandler()->undo();
	}
	return false;
}

bool LevelHandler::redo()
{
	if (_level)
	{
		return _level->getCommandHandler()->redo();
	}
	return false;
}

bool LevelHandler::undoAll()
{
	if (_level)
	{
		return _level->getCommandHandler()->undoAll();
	}
	return false;
}

bool LevelHandler::redoAll()
{
	if (_level)
	{
		return _level->getCommandHandler()->redoAll();
	}
	return false;
}

void LevelHandler::removeLevel()
{
	if (_level)
	{
		_level->removeFromParentAndCleanup(true);
	}
}
