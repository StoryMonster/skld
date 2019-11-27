#include "WorldMapView.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;

namespace components
{

WorldMapView* WorldMapView::instance = new WorldMapView();

WorldMapView::WorldMapView() {}

WorldMapView* WorldMapView::createPlugin()
{
	WorldMapView::instance->init();
	return WorldMapView::instance;
}

void WorldMapView::init()
{
	if (this->node != nullptr) { return; }
	const std::string resPath = "res/WorldMap.csb";
    this->node = CSLoader::createNode(resPath);
	if (this->node == nullptr)
	{
		CCLOGERROR("load %s fail", resPath.c_str());
		return;
	}
	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(this->node->getChildByName("btnBack"));
		if (btnBack == nullptr) { CCLOGERROR("Cannot find the btnBack in %s", resPath.c_str()); }
		else { btnBack->addClickEventListener([this](Ref*) { this->close(); }); }
	}
	if (map == nullptr)
	{
		map = reinterpret_cast<TMXTiledMap*>(this->node->getChildByName("map"));
		if (map == nullptr) { CCLOGERROR("Cannot find the map in %s", resPath.c_str()); }
		else { this->initMap(); }
	}
}

Node* WorldMapView::getNode() noexcept
{
	return this->node;
}

std::string WorldMapView::getPluginName()
{
	return "WorldMap";
}

void WorldMapView::close()
{
	CCLOG("close plugin %s", this->getPluginName());
	if (this->node != nullptr)
	{
		this->node->removeAllChildren();
		this->node->removeFromParent();
		this->node = nullptr;
		this->btnBack = nullptr;
		this->map = nullptr;
		this->lblCity = nullptr;
	}
}

void WorldMapView::initMap()
{
	if (this->map == nullptr) { return; }
	CCTMXObjectGroup* cities = map->getObjectGroup("cities");
	if (cities == nullptr)
	{
		CCLOGERROR("Cannot find 'cities' in the tiled map");
		return;
	}

	for (const auto& city : cities->getObjects())
	{
		try
		{
			auto x = city.asValueMap().at("x").asInt();
			auto y = city.asValueMap().at("y").asInt();
			auto width = city.asValueMap().at("width").asInt();
			auto height = city.asValueMap().at("height").asInt();
			auto id = 0;
			auto btnCity = ui::Button::create();
			if (btnCity != nullptr)
			{
				btnCity->addClickEventListener([this, id](Ref*) { this->onCityClicked(id); });
				this->node->addChild(btnCity);
			}
		}
		catch (...)
		{
			CCLOGERROR("a city init failed");
		}
	}
}

void WorldMapView::onCityClicked(int id)
{
	CCLOG("city %d clicked!", id);
}

}