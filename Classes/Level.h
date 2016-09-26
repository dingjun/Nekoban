#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <fstream>

#include "cocos2d.h"
#include "UnitTypeHandler.h"
#include "CommandHandler.h"
#include "GridMap.h"
#include "UnitType.h"
#include "Unit.h"

class LevelHandler;
class UnitTypeHandler;
class CommandHandler;
class GridMap;

/**
	Handler for a level of puzzle
 */
class Level : public cocos2d::Node
{
public:
	Level(const float gridSize);
	virtual ~Level();

	virtual bool init(const char* levelFileName);

	static Level* create(const char* levelFileName);

	void moveDynamicUnit(const cocos2d::Vec2& currentCoordinate, const cocos2d::Vec2& nextCoordinate);

	Unit* getStaticUnit(const cocos2d::Vec2& coordinate);
	Unit* getDynamicUnit(const cocos2d::Vec2& coordinate);

	void updateStatusLabel();

	inline bool isCompleted() { return _numGoalsLeft == 0; }

	inline cocos2d::Vec2 getCoordinateFromPosition(const cocos2d::Vec2& position) { return cocos2d::Vec2(position.x / _gridSize, -position.y / _gridSize); }
	inline cocos2d::Vec2 getPositionFromCoordinate(const cocos2d::Vec2& coordinate) { return cocos2d::Vec2(coordinate.x * _gridSize, -coordinate.y * _gridSize); }

	inline UnitTypeHandler* getUnitTypeHandler() { return _unitTypeHandler; }
	inline CommandHandler* getCommandHandler() { return _commandHandler; }

private:
	bool construct(std::ifstream& levelFile);

	bool addUnit(const cocos2d::Vec2& coordinate, UnitType& unitType);

	float _gridSize;
	int _numGoalsLeft;

	cocos2d::Label* _statusLabel;

	UnitTypeHandler* _unitTypeHandler;
	CommandHandler* _commandHandler;

	GridMap* _staticUnits;
	GridMap* _dynamicUnits;
};

#endif // __LEVEL_H__
