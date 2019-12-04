#pragma once
#include "Namespaces.h"
#include "cocos2d.h"
#include "ui/UIButton.h"

START_NS_SCENE

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

private:
	cocos2d::ui::Button* btnGameStart = nullptr;
	cocos2d::ui::Button* btnQuitGame = nullptr;
};

END_NS_SCENE

