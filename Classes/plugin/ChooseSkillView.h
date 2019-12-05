#pragma once
#include "Namespaces.h"
#include "IPlugin.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"

START_NS_PLUGIN

class ChooseSkillView : public IPlugin
{
public:
	std::string getPluginName() override { return "ChooseSkill"; };
	void init() override;

private:
	void onItemClicked(std::uint32_t index);
	void fillData();

	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::Node* bgSkills = nullptr;
	std::vector<cocos2d::ui::Button*> items{};
	cocos2d::ui::Button* btnNext = nullptr;
	cocos2d::ui::Button* btnPrev = nullptr;
	cocos2d::ui::Button* btnSlider = nullptr;
};

END_NS_PLUGIN