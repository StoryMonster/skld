#pragma once
#include "Namespaces.h"
#include "cocos2d.h"
#include "IPlugin.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"


START_NS_PLUGIN

class PlayerInfoView : public IPlugin
{
public:
	std::string getPluginName() override { return "PlayerInfo"; };
	void init() override;

private:
	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::ui::Text* txtName = nullptr;
	cocos2d::ui::Text* txtKnowledge = nullptr;
	cocos2d::ui::Text* txtStrength = nullptr;
};

END_NS_PLUGIN