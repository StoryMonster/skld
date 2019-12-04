#pragma once
#include <string>
#include "cocos2d.h"
#include "Namespaces.h"


START_NS_PLUGIN

class IPlugin
{
public:
	virtual ~IPlugin();
	cocos2d::Node* getNode();

	virtual std::string getPluginName();
	virtual void init();
	virtual void close();

protected:
	cocos2d::Node* node = nullptr;
};

END_NS_PLUGIN