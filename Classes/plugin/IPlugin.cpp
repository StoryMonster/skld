#include "IPlugin.h"
#include "PluginCenter.h"


START_NS_PLUGIN

IPlugin::~IPlugin() {}

cocos2d::Node* IPlugin::getNode()
{
	return node;
}

void IPlugin::close()
{
	if (node != nullptr)
	{
		node->removeFromParent();
		node = nullptr;
		PluginCenter::getInstance().destroyPlugin(this->getPluginName());
	}
}

std::string IPlugin::getPluginName() { return "unknown plugin"; }

void IPlugin::init() {}

END_NS_PLUGIN