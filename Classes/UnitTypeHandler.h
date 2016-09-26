#ifndef __UNIT_TYPE_HANDLER_H__
#define __UNIT_TYPE_HANDLER_H__

#include "UnitType.h"

class UnitType;

/**
	Handler to set up various unit types
 */
class UnitTypeHandler
{
public:
	UnitTypeHandler() {}
	~UnitTypeHandler() {}

	inline UnitType& getWallUnitType() { return _wallUnitType; }
	inline UnitType& getFloorUnitType() { return _floorUnitType; }
	inline UnitType& getGoalUnitType() { return _goalUnitType; }
	inline UnitType& getBoxUnitType() { return _boxUnitType; }
	inline UnitType& getNekoUnitType() { return _nekoUnitType; }

private:
	static UnitType _wallUnitType;
	static UnitType _floorUnitType;
	static UnitType _goalUnitType;
	static UnitType _boxUnitType;
	static UnitType _nekoUnitType;
};

#endif // __UNIT_TYPE_HANDLER_H__
