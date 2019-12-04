#include "PluginCenter.h"

USING_NS_CC;
START_NS_PLUGIN


PluginCenter& PluginCenter::getInstance()
{
	static PluginCenter instance;
	return instance;
}

void PluginCenter::showPlugin(std::shared_ptr<IPlugin> thePlugin)
{
	auto scene = Director::getInstance()->getRunningScene();
	const auto pluginName = thePlugin->getPluginName();
	if (scene == nullptr)
	{
		CCLOGERROR("load current scene error when trying to show plugin %s", pluginName.c_str());
		return;
	}

	if (scene->getChildByName(pluginName) == nullptr)
	{
		thePlugin->init();
		auto node = thePlugin->getNode();
		if (node != nullptr)
		{
			scene->addChild(node);
			plugins.push_back(thePlugin);
			const auto parentSize = scene->getContentSize();
			const auto childSize = node->getContentSize();
			const auto x = (parentSize.width - childSize.width) / 2;
			const auto y = (parentSize.height - childSize.height) / 2;
			node->setPosition(Vec2(x, y));
			CCLOG("Create plugin %s", pluginName.c_str());
		}
		else
		{
			CCLOGERROR("the node is nullptr of %s", pluginName.c_str());
		}
	}
	CCLOG("displaying plugin %s", pluginName.c_str());
}

void PluginCenter::destroyPlugin(const std::string& pluginName)
{
	auto it = std::find_if(plugins.begin(), plugins.end(), [&pluginName](const auto& plugin) { return plugin->getPluginName() == pluginName; });
	if (it != plugins.end())
	{
		plugins.erase(it);
		CCLOG("destroyed plugin %s", pluginName.c_str());
	}
}

END_NS_PLUGIN