#pragma once
#include "Namespaces.h"
#include "IPlugin.h"

START_NS_PLUGIN

class PluginCenter
{
public:
	static PluginCenter& getInstance();
	void showPlugin(std::shared_ptr<IPlugin> thePlugin);
	void destroyPlugin(const std::string& pluginName);

private:
	std::vector<std::shared_ptr<IPlugin>> plugins{};
};

END_NS_PLUGIN