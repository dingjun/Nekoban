#include "GridMap.h"

USING_NS_CC;

GridMap::GridMap(const unsigned int width, const unsigned int height)
	: _width(width)
	, _height(height)
{
	// dynamically allocate 2d array
	_grids = new Unit**[height];
	for (unsigned int y = 0; y < _height; ++y)
	{
		_grids[y] = new Unit*[width];

		// initialize each grid
		for (unsigned int x = 0; x < width; ++x)
		{
			_grids[y][x] = nullptr;
		}
	}
}

GridMap::~GridMap()
{
	// deallocate 2d array
	for (unsigned int y = 0; y < _height; ++y)
	{
		delete[] _grids[y];
	}
	delete[] _grids;
}

void GridMap::moveUnit(const Vec2& previousCoordinate, const Vec2& nextCoordinate)
{
	setUnit(nextCoordinate, getUnit(previousCoordinate));
	deleteUnit(previousCoordinate);
}
