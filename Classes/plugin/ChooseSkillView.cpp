#include "ChooseSkillView.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "component/SkillTableView.h"

USING_NS_CC;
using namespace cocostudio::timeline;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

START_NS_PLUGIN

void ChooseSkillView::init()
{
	const std::string resPath = "res/res/TalkBaseLayer.csb";
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

	if (txtTalk == nullptr) { txtTalk = reinterpret_cast<ui::Text*>(this->node->getChildByName("lblTalk")); }

	if (skillsView == nullptr)
	{
		skillsView = component::SkillTableView::create();
		if (skillsView == nullptr) {}
		else { this->node->addChild(skillsView); }
	}
}
END_NS_PLUGIN