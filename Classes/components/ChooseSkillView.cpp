#include "ChooseSkillView.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

namespace components
{
ChooseSkillView* ChooseSkillView::instance = new ChooseSkillView();

ChooseSkillView::ChooseSkillView() {}

ChooseSkillView* ChooseSkillView::createPlugin()
{
	ChooseSkillView::instance->init();
	return ChooseSkillView::instance;
}

void ChooseSkillView::init()
{
	if (this->node != nullptr) { return; }

	const std::string resPath = "res/res/SkillsPanel.csb";
	this->node = CSLoader::createNode(resPath);
	this->sprite = reinterpret_cast<Sprite*>(node);
	if (this->node == nullptr)
	{
		CCLOGERROR("load %s fail", resPath.c_str());
		return;
	}

	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(this->node->getChildByName("btnBack"));
		if (btnBack == nullptr) { CCLOGWARN("Cannot find the quit in %s", resPath.c_str()); }
		else { btnBack->addClickEventListener([this](Ref*) { this->close(); }); }
	}

}

std::string ChooseSkillView::getPluginName()
{
	return "ChooseSkillPanel";
}

void ChooseSkillView::close()
{
	CCLOG("close plugin %s", this->getPluginName().c_str());
	if (this->node != nullptr)
	{
		this->node->removeAllChildren();
		this->node->removeFromParent();
		this->node = nullptr;
		this->btnBack = nullptr;
		this->btnLeft = nullptr;
		this->btnRight = nullptr;
		this->txtSkillDetail = nullptr;
		this->txtSkillName = nullptr;
		this->txtTalk = nullptr;
	}
}
}