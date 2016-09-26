#ifndef __RESOURCE_H__
#define __RESOURCE_H__

static const char sNekobanTitle[] = "Nekoban";

// TODO: dynamic load files
static const char sLevel_1[] = "Levels/Level-1.txt";
static const char sLevel_2[] = "Levels/Level-2.txt";
static const char sLevel_3[] = "Levels/Level-3.txt";
static const char sLevel_4[] = "Levels/Level-4.txt";
static const char sLevel_5[] = "Levels/Level-5.txt";
static const char sLevel_6[] = "Levels/Level-6.txt";

static const char sSpriteSheet[] = "SpriteSheet.plist";
static const char sUndoSprite[] = "ic_undo_white_48dp_1x.png";
static const char sBoxSprite[] = "Box.png";
static const char sFloorSprite[] = "Floor.png";
static const char sGoalSprite[] = "Goal.png";
static const char sNekoSprite[] = "Neko.png";
static const char sWallSprite[] = "Wall.png";

static const int sUnitPixelSize = 32;

static const int sMaxLevelWidth = 20;
static const int sMaxLevelHeight = 20;

static const int sDefaultZOrder = 0;
static const int sStaticZOrder = sDefaultZOrder;
static const int sDynamicZOrder = sStaticZOrder + 1;

static const int sBoxZOrder = sDynamicZOrder;
static const int sFloorZOrder = sStaticZOrder;
static const int sGoalZOrder = sStaticZOrder;
static const int sNekoZOrder = sDynamicZOrder;
static const int sWallZOrder = sStaticZOrder;

static const float sMoveUnitCommandSeconds = 0.1f;

#endif // __RESOURCE_H__
