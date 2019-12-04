#include "XiWuFangScene.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "plugin/ChooseSkillView.h"
#include "plugin/PluginCenter.h"
#include "PalaceScene.h"

USING_NS_CC;
using namespace cocostudio::timeline;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

START_NS_SCENE

Scene* XiWuFangScene::createScene()
{
	auto scene = Scene::create();
	auto layer = XiWuFangScene::create();
	scene->addChild(layer);
	return scene;
}

bool XiWuFangScene::init()
{
	if (!Layer::init()) { return false; }

	const std::string resPath = "res/XiWuFangScene.csb";
	auto rootNode = CSLoader::createNode(resPath);
	if (rootNode == nullptr)
	{
		CCLOGERROR("load %s fail", resPath.c_str());
		return false;
	}
	addChild(rootNode);
	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(rootNode->getChildByName("quit"));
		if (btnBack == nullptr) { CCLOGWARN("Cannot find the quit in %s", resPath.c_str()); }
		else { btnBack->addClickEventListener([this](Ref*) { quit(); }); }
	}

	if (txtTraining == nullptr)
	{
		txtTraining = reinterpret_cast<ui::Text*>(rootNode->getChildByName("txtTraining"));
		setTrainingSubject("体能训练");
	}

	if (btnTeacher == nullptr)
	{
		btnTeacher = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnTeacher"));
		if (btnTeacher == nullptr) { CCLOGWARN("Cannot find the btnTeacher in %s", resPath.c_str()); }
		else { btnTeacher->addClickEventListener([this](Ref*) { plugin::PluginCenter::getInstance().showPlugin(std::make_shared<plugin::ChooseSkillView>()); }); }
	}

	playTheAnimation();
	return true;
}

void XiWuFangScene::quit()
{
	auto scene = PalaceScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void XiWuFangScene::playTheAnimation()
{
	auto action = CSLoader::createTimeline("res/XiWuFangScene.csb");
	if (action == nullptr)
	{
		CCLOGWARN("Xi Wu animation is not found!");
		return;
	}
	this->runAction(action);
	action->addFrameEndCallFunc(4, "", []() { CCLOG("One round animation end"); });
	action->gotoFrameAndPlay(0, false);
}

void XiWuFangScene::setTrainingSubject(const std::string& name)
{
	if (this->txtTraining == nullptr) { return; }
	this->txtTraining->setString("今日课程: " + name);
}

END_NS_SCENE