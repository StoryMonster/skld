#include "ChooseSkillView.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "model/player.h"
#include "model/skill/SkillManager.h"
#include <cmath>

USING_NS_CC;
using namespace cocostudio::timeline;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

START_NS_PLUGIN

ChooseSkillView::ChooseSkillView(const std::vector<skill::SkillType>& allowedSkillTypes)
	: IPlugin()
	, allowedSkillTypes{allowedSkillTypes}
{
}

void ChooseSkillView::init()
{
	const std::string resPath = "res/res/ChooseSkillPanel.csb";
	this->node = CSLoader::createNode(resPath);

	if (this->node == nullptr)
	{
		CCLOGERROR("load %s fail", resPath.c_str());
		return;
	}

	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(this->node->getChildByName("btnBack"));
		if (btnBack == nullptr) { CCLOGWARN("Cannot find the btnBack in %s", resPath.c_str()); }
		else { btnBack->addClickEventListener([this](Ref*) { this->close(); }); }
	}

	items.clear();
	if (bgSkills == nullptr)
	{
		bgSkills = node->getChildByName("bgSkills");
		if (bgSkills != nullptr)
		{
			for (auto i = 0; i < 5; ++i)
			{
				auto item = reinterpret_cast<ui::Button*>(bgSkills->getChildByName("skillitem" + std::to_string(i+1)));
				if (item != nullptr)
				{
					items.push_back(item);
					item->addClickEventListener([this, i](Ref*) { onItemClicked(i); });
				}
			}
		}
	}

	if (btnNext == nullptr)
	{
		btnNext = reinterpret_cast<ui::Button*>(this->node->getChildByName("btnNext"));
		if (btnNext != nullptr)
		{
			btnNext->addClickEventListener([this](Ref*) { onBtnNextClicked(); });
		}
	}

	if (btnPrev == nullptr)
	{
		btnPrev = reinterpret_cast<ui::Button*>(this->node->getChildByName("btnPrev"));
		if (btnPrev != nullptr)
		{
			btnPrev->addClickEventListener([this](Ref*) { onBtnPrevClicked(); });
		}
	}

	if (txtPageCounter == nullptr)
	{
		txtPageCounter = reinterpret_cast<ui::Text*>(this->node->getChildByName("txtPageCounter"));
	}

	extractPlayerBoughtSkills();
	onBtnNextClicked();
}

void ChooseSkillView::extractPlayerBoughtSkills()
{
	skillIds.clear();
	const auto allSkillIds = Player::getInstance().getBoughtSkills();
	for (const auto skillId : allSkillIds)
	{
		if (std::find_if(allowedSkillTypes.begin(), allowedSkillTypes.end(), [this, skillId](const auto type) {
			const auto skill = skill::SkillManager::getInstance().getSkillById(skillId);
			if (skill == nullptr) { return false; }
			return skill->getSkillType() == type;
		    }) != allowedSkillTypes.end())
		{
			skillIds.push_back(skillId);
		}
	}
}

void ChooseSkillView::updateButtonStatus(std::uint32_t startIndex, std::uint32_t endIndex)
{
	if (btnPrev != nullptr)
	{
		btnPrev->setTouchEnabled(startIndex > 0);
	}

	if (btnNext != nullptr)
	{
		btnNext->setTouchEnabled(endIndex < skillIds.size());
	}
}

void ChooseSkillView::onBtnNextClicked()
{
	++currentPageIndex;
	const auto startIndex = items.size() * (currentPageIndex - 1);
	const auto endIndex = std::min(items.size() * currentPageIndex, skillIds.size());
	updateButtonStatus(startIndex, endIndex);
	fillData(startIndex, endIndex);
}

void ChooseSkillView::onBtnPrevClicked()
{
	if (currentPageIndex <= 1) { return; }
	--currentPageIndex;
	const auto startIndex = items.size() * (currentPageIndex - 1);
	const auto endIndex = std::min(items.size() * currentPageIndex, skillIds.size());
	updateButtonStatus(startIndex, endIndex);
	fillData(startIndex, endIndex);
}

void ChooseSkillView::fillData(std::uint32_t startIndex, std::uint32_t endIndex)
{
	for (size_t i = 0; i < items.size(); ++i)
	{
		auto lbl = reinterpret_cast<ui::Text*>(items[i]->getChildByName("lblSkillName"));
		if (lbl == nullptr) { continue; }
		lbl->setString("");
		items[i]->setTouchEnabled(false);
		if (startIndex + i < endIndex)
		{
			const auto skill = skill::SkillManager::getInstance().getSkillById(skillIds.at(startIndex + i));
			if (skill != nullptr)
			{
				lbl->setString(skill->getSkillName());
				items[i]->setTouchEnabled(true);
			}
		}
	}
	if (txtPageCounter != nullptr)
	{
		const std::uint32_t totalPageNum = ceil(skillIds.size() * 1.0 / items.size());
		txtPageCounter->setString(std::to_string(currentPageIndex)+ "/" + std::to_string(totalPageNum));
	}
}

void ChooseSkillView::onItemClicked(std::uint32_t index)
{
	if (index >= items.size()) { return; }

	time_t now = time(0);
	if (difftime(now, lastClickSkillTime) < 1) { return; }
	lastClickSkillTime = now;

	const auto skillId = skillIds.at(items.size() * (currentPageIndex - 1) + index);
	const auto skill = skill::SkillManager::getInstance().getSkillById(skillId);
	if (skill != nullptr && node != nullptr)
	{
		CCLOG("clicked skill %s", skill->getSkillName().c_str());
		node->getEventDispatcher()->dispatchCustomEvent("EVT_CHOOSE_SKILL_TO_TRAIN", reinterpret_cast<void*>(const_cast<std::uint32_t*>(&skillId)));
		close();
	}
}
END_NS_PLUGIN