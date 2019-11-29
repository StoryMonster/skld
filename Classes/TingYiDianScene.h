#pragma once

#include "cocos2d.h"
#include "ui/UIButton.h"
#include <vector>

class TingYiDianScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(TingYiDianScene);

private:
	struct OfficialInfo
	{
		cocos2d::Sprite* sprite = nullptr;
		cocos2d::Vec2 originalPos{};
		float originalScaleX = 0;
		float originalScaleY = 0;
		bool isReporting = false;
	};

	void initOfficials();
	void letOfficerStandOut(int index);
	void letOfficerBack(int index);
	int getStandingOutOfficerIndex();

	void onTouchBegan(cocos2d::Touch*);
	int getClickedOfficialIndex(const cocos2d::Vec2&);

	cocos2d::ui::Button* btnWorldMap = nullptr;
	cocos2d::ui::Button* btnBack = nullptr;
	std::vector<OfficialInfo> officials{};
	cocos2d::EventListenerTouchOneByOne* eventListener = nullptr;
};