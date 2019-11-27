#pragma once
#include <string>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;

namespace plugin
{

template <typename T>
void showPlugin()
{
	auto scene = Director::getInstance()->getRunningScene();
	const auto pluginName = T::getPluginName();
	if (scene == nullptr)
	{
		CCLOGERROR("load current scene error when trying to show plugin %s", pluginName.c_str());
		return;
	}
	T* thePlugin = T::createPlugin();
	if (thePlugin == nullptr)
	{
		CCLOGERROR("create plugin fail when trying to show plugin %s", pluginName.c_str());
		return;
	}
	if (scene->getChildByName(pluginName) == nullptr)
	{
		scene->addChild(thePlugin->getNode());
		CCLOG("Create plugin %s", pluginName.c_str());
	}
	CCLOGINFO("show plugin successfully");
}

}