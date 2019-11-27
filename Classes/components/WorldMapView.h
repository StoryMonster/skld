#pragma once

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include <string>

namespace components
{

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

	cocos2d::Node* node = nullptr;
	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::ui::Text* lblCity = nullptr;
	cocos2d::TMXTiledMap* map = nullptr;
};


}