#include "UnitType.h"

USING_NS_CC;

UnitType::UnitType(const char* name, const int zOrder)
	: _name(name)
	, _zOrder(zOrder)
{

}

UnitType::~UnitType()
{

}

Unit* UnitType::createUnit(Level* level, const Vec2& coordinate)
{
	return Unit::create(level, *this, coordinate);
}
