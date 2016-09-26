#ifndef __PLAY_LEVEL_SCENE_H__
#define __PLAY_LEVEL_SCENE_H__

#include "cocos2d.h"

class PlayLevelScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(PlayLevelScene);
};

#endif // __PLAY_LEVEL_SCENE_H__
