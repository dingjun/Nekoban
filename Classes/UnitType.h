#ifndef __UNIT_TYPE_H__
#define __UNIT_TYPE_H__

#include "cocos2d.h"
#include "Level.h"
#include "Unit.h"
#include "Resource.h"

class Level;
class Unit;

/**
	Unit type for unit to reference
 */
class UnitType
{
public:
	UnitType(const char* _name, const int zOrder = sDefaultZOrder);
	virtual ~UnitType();

	Unit* createUnit(Level* level, const cocos2d::Vec2& coordinate);

	inline bool isSame(UnitType& unitType) { return this == &unitType; }

	inline const char* getName() { return _name; }
	inline int getZOrder() { return _zOrder; }

private:
	const char* _name;			// also represent sprite frame name
	int _zOrder;
};

#endif // __UNIT_TYPE_H__
