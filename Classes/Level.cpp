#include "Level.h"

#include <string>

#include "Resource.h"

using namespace std;
USING_NS_CC;

Level::Level(const float gridSize)
	: _gridSize(gridSize)
	, _numGoalsLeft(0)
	, _staticUnits(nullptr)
	, _dynamicUnits(nullptr)
{
	_unitTypeHandler = new UnitTypeHandler();
	_commandHandler = new CommandHandler(this);
}

Level::~Level()
{
	delete _unitTypeHandler;
	delete _commandHandler;
	delete _staticUnits;
	delete _dynamicUnits;
}

bool Level::init(const char* levelFileName)
{
	// open level file
	ifstream levelFile(FileUtils::getInstance()->fullPathForFilename(levelFileName));
	if (!levelFile.is_open())
	{
		CCLOG("Unable to open file");
		return false;
	}
	
	// read level file
	bool isSuccess = construct(levelFile);
	levelFile.close();

	// create and add status label
	_statusLabel = Label::createWithSystemFont("", "Arial", 16);
	_statusLabel->setAnchorPoint(Vec2(0, 0));
	_statusLabel->setPosition(Vec2(0, 10));
	updateStatusLabel();
	this->addChild(_statusLabel);

	return isSuccess;
}

Level* Level::create(const char* levelFileName)
{
	Level* level = new (nothrow) Level(sUnitPixelSize / Director::getInstance()->getContentScaleFactor());

	if (level && level->init(levelFileName))
	{
		level->autorelease();

		// TODO: dynamic center
		level->setPosition(120, 220);
	}
	else
	{
		CC_SAFE_DELETE(level);
	}
	return level;
}

void Level::moveDynamicUnit(const Vec2& previousCoordinate, const Vec2& nextCoordinate)
{
	_dynamicUnits->moveUnit(previousCoordinate, nextCoordinate);

	// update number of goals left
	if (getDynamicUnit(nextCoordinate)->hasSameUnitType(_unitTypeHandler->getBoxUnitType()))
	{
		Unit* currentStaticUnit = getStaticUnit(previousCoordinate);
		Unit* nextStaticUnit = getStaticUnit(nextCoordinate);

		if (currentStaticUnit->hasSameUnitType(_unitTypeHandler->getGoalUnitType()))
		{
			++_numGoalsLeft;
		}
		if (nextStaticUnit->hasSameUnitType(_unitTypeHandler->getGoalUnitType()))
		{
			--_numGoalsLeft;
		}
	}
}

Unit* Level::getStaticUnit(const Vec2& coordinate)
{
	return _staticUnits->getUnit(coordinate);
}

Unit* Level::getDynamicUnit(const Vec2& coordinate)
{
	return _dynamicUnits->getUnit(coordinate);
}

void Level::updateStatusLabel()
{
	string status = "Step: ";

	if (isCompleted())
	{
		status = "COMPLETE!\n" + status;
	}

	_statusLabel->setString(status + to_string(_commandHandler->getNumCommandsDone()));
}

bool Level::construct(ifstream& levelFile)
{
	// TODO: dynamically set size of grid map
	_staticUnits = new GridMap(sMaxLevelWidth, sMaxLevelHeight);
	_dynamicUnits = new GridMap(sMaxLevelWidth, sMaxLevelHeight);

	bool hasNeko = false;
	int numBoxesLeft = 0;
	int y = 0;
	string line;

	while (getline(levelFile, line))
	{
		int lineSize = line.size();

		// check level size limitation
		if (lineSize > sMaxLevelWidth || y >= sMaxLevelHeight)
		{
			return false;
		}

		for (int x = 0; x < lineSize; ++x)
		{
			Vec2 coordinate = Vec2(x, y);

			// add unitf
			switch (line[x])
			{
			case '#':			// wall
				if (addUnit(coordinate, _unitTypeHandler->getWallUnitType()))
				{
					break;
				}
				return false;
			case '_':			// floor			// TODO: use ' ' instead
				if (addUnit(coordinate, _unitTypeHandler->getFloorUnitType()))
				{
					break;
				}
				return false;
			case '.':			// goal
				if (addUnit(coordinate, _unitTypeHandler->getGoalUnitType()))
				{
					++_numGoalsLeft;
					break;
				}
				return false;
			case '$':			// box
				if (addUnit(coordinate, _unitTypeHandler->getFloorUnitType()) && addUnit(coordinate, _unitTypeHandler->getBoxUnitType()))
				{
					++numBoxesLeft;
					break;
				}
				return false;
			case '@':			// neko
				if (!hasNeko && addUnit(coordinate, _unitTypeHandler->getFloorUnitType()) && addUnit(coordinate, _unitTypeHandler->getNekoUnitType()))
				{
					hasNeko = true;
					break;
				}
				return false;
			case '*':			// goal and box
				if (addUnit(coordinate, _unitTypeHandler->getGoalUnitType()) && addUnit(coordinate, _unitTypeHandler->getBoxUnitType()))
				{
					break;
				}
				return false;
			case '+':			// goal and neko
				if (!hasNeko && addUnit(coordinate, _unitTypeHandler->getGoalUnitType()) && addUnit(coordinate, _unitTypeHandler->getFloorUnitType()))
				{
					++_numGoalsLeft;
					hasNeko = true;
					break;
				}
				return false;
			default:
				return false;
			}
		}

		++y;
	}

	// fail if neko doesn't exist, or number of boxes is not equal to number of goals
	if (!hasNeko || numBoxesLeft != _numGoalsLeft)
	{
		return false;
	}
	return true;
}

bool Level::addUnit(const Vec2& coordinate, UnitType& unitType)
{
	Unit* unit = unitType.createUnit(this, coordinate);
	if (unit)
	{
		int zOrder = unitType.getZOrder();
		this->addChild(unit, zOrder);
		if (zOrder <= sDefaultZOrder)
		{
			_staticUnits->setUnit(coordinate, unit);
		}
		else
		{
			_dynamicUnits->setUnit(coordinate, unit);
		}

		// add input component to neko
		if (unitType.isSame(_unitTypeHandler->getNekoUnitType()))
		{
			unit->setInputComponent(new InputComponent());
			auto listener = EventListenerKeyboard::create();
			listener->onKeyPressed = [unit](EventKeyboard::KeyCode keyCode, Event* event)
			{
				unit->getInputComponent()->handleKeyboardInput(keyCode, unit);
			};
			unit->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, unit);
		}

		return true;
	}
	return false;
}
