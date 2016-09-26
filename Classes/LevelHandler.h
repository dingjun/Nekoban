#ifndef __LEVEL_HANDLER_H__
#define __LEVEL_HANDLER_H__

#include "cocos2d.h"
#include "Level.h"

class Level;

/**
	Handler to load various levels
 */
class LevelHandler
{
public:
	LevelHandler();
	~LevelHandler();

	bool nextLevel(cocos2d::Node* node);
	bool undo();
	bool redo();
	bool undoAll();
	bool redoAll();

private:
	void removeLevel();

	const char** _levelNames;
	unsigned int _numLevels;
	unsigned int _nextLevelIndex;
	Level* _level;
};

#endif // __LEVEL_HANDLER_H__
