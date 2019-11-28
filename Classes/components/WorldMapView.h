#pragma once

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include <string>
#include <vector>

namespace components
{
struct CityNodeInfoInMap
{
	int id = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	std::string name = "";
};

class WorldMapView
{
public:
	static WorldMapView* createPlugin();
	static std::string getPluginName();
	static WorldMapView* instance;

	cocos2d::Node* getNode() noexcept;

	void close();

private:
	WorldMapView();
	void init();
	void initMap();
	void onCityClicked(int);
	int getTheClickingCityId(cocos2d::Touch*);

	cocos2d::Node* node = nullptr;
	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::ui::Text* lblCity = nullptr;
	cocos2d::ui::Text* lblPopulation = nullptr;
	cocos2d::TMXTiledMap* map = nullptr;
	cocos2d::EventListenerTouchOneByOne* mapListener = nullptr;
	std::vector<CityNodeInfoInMap> cityNodesInfo{};
};


}