#include "WorldMapView.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../model/city/CitiesManager.h"
#include "../model/country/CountryManager.h"

USING_NS_CC;
using namespace cocostudio::timeline;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

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
	cityNodesInfo.clear();
	const std::string resPath = "res/WorldMap.csb";
    this->node = CSLoader::createNode(resPath);
	if (this->node == nullptr)
	{
		CCLOGERROR("load %s fail", resPath.c_str());
		return;
	}
	if (this->bg == nullptr)
	{
		this->bg = this->node->getChildByName("bg");
		if (this->bg == nullptr) { return; }
	}
	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(this->bg->getChildByName("btnBack"));
		if (btnBack == nullptr) { CCLOGWARN("Cannot find the btnBack in %s", resPath.c_str()); }
		else { btnBack->addClickEventListener([this](Ref*) { this->close(); }); }
	}
	if (map == nullptr)
	{
		map = reinterpret_cast<TMXTiledMap*>(this->bg->getChildByName("map"));
		if (map == nullptr) { CCLOGWARN("Cannot find the map in %s", resPath.c_str()); }
		else { this->initMap(); }
	}
	if (lblCity == nullptr)
	{
		lblCity = reinterpret_cast<ui::Text*>(this->bg->getChildByName("lblCity"));
		if (lblCity == nullptr) { CCLOGWARN("Cannot find the lblCity in %s", resPath.c_str()); }
	}

	if (lblPopulation == nullptr)
	{
		lblPopulation = reinterpret_cast<ui::Text*>(this->bg->getChildByName("lblPopulation"));
		if (lblPopulation == nullptr) { CCLOGWARN("Cannot find the lblPopulation in %s", resPath.c_str()); }
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
	CCLOG("close plugin %s", this->getPluginName().c_str());
	if (this->node != nullptr)
	{
		if (this->mapListener != nullptr)
		{
			this->map->getEventDispatcher()->removeEventListener(this->mapListener);
			this->mapListener = nullptr;
		}
		this->node->removeAllChildren();
		this->node->removeFromParent();
		this->node = nullptr;
		this->btnBack = nullptr;
		this->map = nullptr;
		this->lblCity = nullptr;
		this->lblPopulation = nullptr;
		this->bg = nullptr;
	}
}

int WorldMapView::getTheClickingCityId(Touch* touch)
{
	const auto location = touch->getLocation();
	auto mapPos = map->getPosition();
	auto bgPos = bg->getPosition();
	auto yscale = map->getScaleY() * bg->getScaleY();
	auto xscale = map->getScaleX() * bg->getScaleX();

	for (const auto& cityNode : this->cityNodesInfo)
	{
		auto x = bgPos.x + mapPos.x + cityNode.x * xscale;
		auto y = bgPos.y + mapPos.y + cityNode.y * yscale;
		auto width = cityNode.width * xscale;
		auto height = cityNode.height * yscale;
		if (x <= location.x && x + width >= location.x && y <= location.y && y + height >= location.y)
		{
			return cityNode.id;
		}
	}
	return -1;
}

void WorldMapView::initMap()
{
	if (this->map == nullptr) { return; }
	TMXObjectGroup* cities = map->getObjectGroup("cities");
	if (cities == nullptr)
	{
		CCLOGERROR("Cannot find 'cities' in the tiled map");
		return;
	}

	for (const auto& city : cities->getObjects())
	{
		try
		{
			const auto x = city.asValueMap().at("x").asInt();
			const auto y = city.asValueMap().at("y").asInt();
			const auto width = city.asValueMap().at("width").asInt();
			const auto height = city.asValueMap().at("height").asInt();
			const auto id = city.asValueMap().at("id").asInt();
			const auto name = city.asValueMap().at("name").asString();
			cityNodesInfo.push_back(CityNodeInfoInMap{id, x, y, width, height, name});
		}
		catch (const std::out_of_range& e)
		{
			CCLOGERROR("%s", e.what());
		}
	}
	if (this->mapListener == nullptr)
	{
		this->mapListener = EventListenerTouchOneByOne::create();
		this->mapListener->onTouchBegan = [this](Touch* touch, Event* event) {
			const auto id = this->getTheClickingCityId(touch);
			if (id >= 0) { this->onCityClicked(id); }
			return true;
		};
		this->map->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->mapListener, this->bg);
		this->mapListener->setSwallowTouches(true);
	}
}

void WorldMapView::onCityClicked(int id)
{
	if (lblCity == nullptr) { return; }
	std::string strCity = "无名之城";
	auto city = city::CitiesManager::getInstance().getCityModelById(static_cast<std::uint32_t>(id));
	if (city != nullptr) { strCity = city->getCityName(); }
	
	std::string strCountry = "野";
	auto country = country::CountryManager::getInstance().getCountryById(city->getCountryId());
	if (country != nullptr) { strCountry = country->getCountryName(); }
	lblCity->setString(strCity + "(" + strCountry + ")");

	if (lblPopulation != nullptr)
	{
		std::string strPopulation = "未知";
		if (city != nullptr) { strPopulation = std::to_string(city->getPopulation()); }
		lblPopulation->setString("人口: " + strPopulation);
	}
}

}