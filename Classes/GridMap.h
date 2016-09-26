#ifndef __GRID_MAP_H__
#define __GRID_MAP_H__

#include "cocos2d.h"
#include "Unit.h"

class Unit;

/**
	Container of 2D list of units to represent a grid-based map
 */
class GridMap
{
public:
	GridMap(const unsigned int width, const unsigned int height);
	virtual ~GridMap();

	void moveUnit(const cocos2d::Vec2& previousCoordinate, const cocos2d::Vec2& nextCoordinate);

	inline void deleteUnit(const unsigned int x, const unsigned int y) { setUnit(x, y, nullptr); }
	inline void deleteUnit(const cocos2d::Vec2& coordinate) { setUnit(coordinate, nullptr); }
	inline void setUnit(const unsigned int x, const unsigned int y, Unit* unit) { _grids[y][x] = unit; }
	inline void setUnit(const cocos2d::Vec2& coordinate, Unit* unit) { setUnit(static_cast<unsigned int>(coordinate.x), static_cast<unsigned int>(coordinate.y), unit); }
	inline Unit* getUnit(const unsigned int x, const unsigned int y) { return _grids[y][x]; }
	inline Unit* getUnit(const cocos2d::Vec2& coordinate) { return getUnit(static_cast<unsigned int>(coordinate.x), static_cast<unsigned int>(coordinate.y)); }

	inline unsigned int getWidth() { return _width; }
	inline unsigned int getHeight() { return _height; }

private:
	unsigned int _width;
	unsigned int _height;
	Unit*** _grids;
};

#endif // __GRID_MAP_H__
