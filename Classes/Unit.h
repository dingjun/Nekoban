#ifndef __UNIT_H__
#define __UNIT_H__

#include <queue>

#include "cocos2d.h"
#include "Level.h"
#include "UnitType.h"
#include "InputComponent.h"

class Level;
class InputComponent;

/**
	Unit to represent a game object
 */
class Unit : public cocos2d::Node
{
	friend class UnitType;

public:
	Unit(Level* level, UnitType& unitType, const cocos2d::Vec2& coordinate);
	virtual ~Unit();

	virtual bool init();

	bool hasSameUnitType(UnitType& unitType);

	void moveBy(const float duration, const cocos2d::Vec2& step);

	inline Level* getLevel() { return _level; }

	void setCoordinate(const cocos2d::Vec2& coordinate);
	inline cocos2d::Vec2 getCoordinate() { return _coordinate; }

	inline void setInputComponent(InputComponent* inputComponent) { _inputComponent = inputComponent; }
	inline InputComponent* getInputComponent() { return _inputComponent; }

private:
	static Unit* create(Level* level, UnitType& unitType, const cocos2d::Vec2& coordinate);

	Level* _level;
	UnitType& _unitType;
	cocos2d::Vec2 _coordinate;
	cocos2d::Sprite* _graphicsComponent;
	InputComponent* _inputComponent;
};

#endif // __UNIT_H__
