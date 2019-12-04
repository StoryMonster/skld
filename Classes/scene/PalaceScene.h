#pragma once
#include "Namespaces.h"
#include "cocos2d.h"
#include "ui/UIButton.h"
#include <vector>

START_NS_SCENE
struct PalaceInfo
{
	int id = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};

class PalaceScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PalaceScene);

private:
	void initPalaces();

	void onPalaceMapClicked(const cocos2d::Vec2&);
	int getClickedPalaceId(const cocos2d::Vec2&);

	cocos2d::ui::Button* btnWorldMap = nullptr;
	cocos2d::ui::Button* btnExit = nullptr;
	cocos2d::ui::Button* btnShop = nullptr;
	cocos2d::ui::Button* btnSetting = nullptr;
	cocos2d::ui::Button* btnHead = nullptr;
	std::vector<PalaceInfo> palaces{};
};

END_NS_SCENE