#pragma once
#include "Namespaces.h"
#include "IPlugin.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"


namespace component
{
class SkillTableView;
}

START_NS_PLUGIN

class ChooseSkillView : public IPlugin
{
public:
	std::string getPluginName() override { return "ChooseSkill"; };
	void init() override;

private:
	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::ui::Text* txtTalk = nullptr;
	component::SkillTableView* skillsView = nullptr;
};

END_NS_PLUGIN