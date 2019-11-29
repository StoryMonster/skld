#include "XiWuFangView.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "components/ChooseSkillView.h"
#include "plugin/PluginCenter.h"

USING_NS_CC;
using namespace cocostudio::timeline;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

namespace components
{

XiWuFangView* XiWuFangView::instance = new XiWuFangView();

XiWuFangView::XiWuFangView() {}

XiWuFangView* XiWuFangView::createPlugin()
{
	XiWuFangView::instance->init();
	return XiWuFangView::instance;
}

void XiWuFangView::init()
{
	if (this->node != nullptr) { return; }

	const std::string resPath = "res/res/XiWuFang.csb";
    this->node = CSLoader::createNode(resPath);
	if (this->node == nullptr)
	{
		CCLOGERROR("load %s fail", resPath.c_str());
		return;
	}
	if (this->bg == nullptr)
	{
		this->bg = this->node->getChildByName("bg");
		if (this->bg == nullptr) { return; }
	}
	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(this->bg->getChildByName("quit"));
		if (btnBack == nullptr) { CCLOGWARN("Cannot find the quit in %s", resPath.c_str()); }
		else { btnBack->addClickEventListener([this](Ref*) { this->close(); }); }
	}

	if (txtTraining == nullptr)
	{
		txtTraining = reinterpret_cast<ui::Text*>(this->bg->getChildByName("txtTraining"));
		setTrainingSubject("体能训练");
	}

	if (btnTeacher == nullptr)
	{
		btnTeacher = reinterpret_cast<ui::Button*>(this->bg->getChildByName("btnTeacher"));
		if (btnTeacher == nullptr) { CCLOGWARN("Cannot find the btnTeacher in %s", resPath.c_str()); }
		else { btnTeacher->addClickEventListener([this](Ref*) { plugin::showPlugin<ChooseSkillView>(); }); }
	}

	playTheAnimation();
}

Node* XiWuFangView::getNode() noexcept
{
	return this->node;
}

std::string XiWuFangView::getPluginName()
{
	return "XiWuFang";
}

void XiWuFangView::close()
{
	CCLOG("close plugin %s", this->getPluginName().c_str());
	if (this->node != nullptr)
	{
		this->node->removeAllChildren();
		this->node->removeFromParent();
		this->node = nullptr;
		this->btnBack = nullptr;
		this->bg = nullptr;
	}
}

void XiWuFangView::playTheAnimation()
{
	auto action = CSLoader::createTimeline("res/res/XiWuFang.csb");
	if (action == nullptr)
	{
		CCLOGWARN("Xi Wu animation is not found!");
		return;
	}
	this->node->runAction(action);
	action->addFrameEndCallFunc(4, "", []() { CCLOG("One round animation end"); });
	action->gotoFrameAndPlay(0, false);
}

void XiWuFangView::setTrainingSubject(const std::string& name)
{
	if (this->txtTraining == nullptr) { return; }
	this->txtTraining->setString("今日课程: " + name);
}

}