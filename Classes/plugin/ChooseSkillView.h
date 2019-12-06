#pragma once
#include "Namespaces.h"
#include "IPlugin.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include "model/skill/SkillModel.h"
#include <thread>

START_NS_PLUGIN

class ChooseSkillView : public IPlugin
{
public:
	ChooseSkillView(const std::vector<skill::SkillType>& allowedSkillTypes);
	std::string getPluginName() override { return "ChooseSkill"; };
	void init() override;

private:
	void onItemClicked(std::uint32_t index);
	void onBtnNextClicked();
	void onBtnPrevClicked();
	void updateButtonStatus(std::uint32_t, std::uint32_t);
	void fillData(std::uint32_t, std::uint32_t);
	void extractPlayerBoughtSkills();

	cocos2d::Node* bgSkills = nullptr;
	std::vector<cocos2d::ui::Button*> items{};
	cocos2d::ui::Button* btnNext = nullptr;
	cocos2d::ui::Button* btnPrev = nullptr;
	cocos2d::ui::Text* txtPageCounter = nullptr;
	cocos2d::ui::Button* btnBack = nullptr;

	std::uint32_t currentPageIndex = 0;
	std::vector<std::uint32_t> skillIds{};
	std::vector<skill::SkillType> allowedSkillTypes{};

	time_t lastClickSkillTime = 0;
};

END_NS_PLUGIN