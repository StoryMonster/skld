#pragma once
#include "Namespaces.h"
#include "IPlugin.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include <string>
#include <vector>

START_NS_PLUGIN

struct CityNodeInfoInMap
{
	int id = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	std::string name = "";
};

class WorldMapView : public IPlugin
{
public:
	std::string getPluginName() override { return "WorldMap"; };
	void init() override;

private:
	void initMap();
	void onCityClicked(int);
	int getTheClickingCityId(cocos2d::Touch*);

	cocos2d::Node* bg = nullptr;
	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::ui::Text* lblCity = nullptr;
	cocos2d::ui::Text* lblPopulation = nullptr;
	cocos2d::TMXTiledMap* map = nullptr;
	cocos2d::EventListenerTouchOneByOne* mapListener = nullptr;
	std::vector<CityNodeInfoInMap> cityNodesInfo{};
};

END_NS_PLUGIN