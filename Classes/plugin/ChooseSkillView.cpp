#include "ChooseSkillView.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "model/skill/SkillManager.h"

USING_NS_CC;
using namespace cocostudio::timeline;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

START_NS_PLUGIN

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
			auto scrollbar = bgSkills->getChildByName("scrollbar");
			if (scrollbar != nullptr)
			{
				btnNext = reinterpret_cast<ui::Button*>(scrollbar->getChildByName("btnNext"));
				btnPrev = reinterpret_cast<ui::Button*>(scrollbar->getChildByName("btnPrev"));
				btnSlider = reinterpret_cast<ui::Button*>(scrollbar->getChildByName("btnSlider"));
			}
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

	if (btnNext != nullptr)
	{
		btnNext->addClickEventListener([](Ref*) { CCLOG("clicked btnNext"); });
	}

	if (btnPrev != nullptr)
	{
		btnPrev->addClickEventListener([](Ref*) { CCLOG("clicked btnPrev"); });
	}

	if (btnSlider != nullptr)
	{
		btnSlider->addClickEventListener([](Ref*) { CCLOG("clicked btnSlider"); });
	}

	fillData();
}

void ChooseSkillView::fillData()
{
	for (auto i = 0; i < items.size(); ++i)
	{
		auto lbl = reinterpret_cast<ui::Text*>(items[i]->getChildByName("lblSkillName"));
		const auto skill = skill::SkillManager::getInstance().getSkillById(i+1);
		if (lbl != nullptr)
		{
			lbl->setString(skill->getSkillName());
		}
	}
}

void ChooseSkillView::onItemClicked(std::uint32_t index)
{
	if (index >= items.size()) { return; }
	CCLOG("clicked item %d", index);
}
END_NS_PLUGIN