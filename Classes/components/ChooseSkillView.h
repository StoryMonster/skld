#pragma once

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"

namespace components
{

class ChooseSkillView
{
public:
	static ChooseSkillView* createPlugin();
	static std::string getPluginName();
	static ChooseSkillView* instance;

	inline cocos2d::Node* getNode() noexcept { return node; };
	void close();

private:
	ChooseSkillView();
	void init();

	cocos2d::Node* node = nullptr;
	cocos2d::Sprite* sprite = nullptr;
	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::ui::Button* btnLeft = nullptr;
	cocos2d::ui::Button* btnRight = nullptr;
	cocos2d::ui::Text* txtTalk = nullptr;
	cocos2d::ui::Text* txtSkillName = nullptr;
	cocos2d::ui::Text* txtSkillDetail = nullptr;
};

}