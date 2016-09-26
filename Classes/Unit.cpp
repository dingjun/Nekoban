#include "Unit.h"

using namespace std;
USING_NS_CC;

Unit::Unit(Level* level, UnitType& unitType, const Vec2& coordinate)
	: _level(level)
	, _unitType(unitType)
{
	_coordinate.set(coordinate);
}

Unit::~Unit()
{

}

bool Unit::init()
{
	this->setPosition(_level->getPositionFromCoordinate(_coordinate));

	// add graphics component
	_graphicsComponent = Sprite::createWithSpriteFrameName(_unitType.getName());
	if (_graphicsComponent)
	{
		this->addChild(_graphicsComponent);
		return true;
	}
	return false;
}

bool Unit::hasSameUnitType(UnitType& unitType)
{
	return _unitType.isSame(unitType);
}

void Unit::moveBy(const float duration, const Vec2& step)
{
	// update level
	_level->moveDynamicUnit(_coordinate, _coordinate + step);

	// update coordinate
	_coordinate.add(step);

	// move
	MoveBy* moveByAction = MoveBy::create(duration, _level->getPositionFromCoordinate(step));
	this->runAction(moveByAction);
}

void Unit::setCoordinate(const Vec2& coordinate)
{
	// update level
	_level->moveDynamicUnit(_coordinate, coordinate);

	// update coordinate
	_coordinate.set(coordinate);

	// update position
	this->setPosition(_level->getPositionFromCoordinate(_coordinate));
}

Unit* Unit::create(Level* level, UnitType& unitType, const Vec2& coordinate)
{
	Unit* unit = new (nothrow) Unit(level, unitType, coordinate);

	if (unit && unit->init())
	{
		unit->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(unit);
	}
	return unit;
}
