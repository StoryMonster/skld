#include "PalaceScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "components/WorldMapView.h"
#include "plugin/PluginCenter.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* PalaceScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PalaceScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool PalaceScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	palaces.clear();
	auto rootNode = CSLoader::createNode("PalaceScene.csb");
	if (rootNode == nullptr)
	{
		CCLOGERROR("load PalaceScene.csb fail");
		return false;
	}
	addChild(rootNode);

	initPalaces();

	if (btnWorldMap == nullptr)
	{
		btnWorldMap = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnWorldMap"));
		if (btnWorldMap != nullptr)
		{
			btnWorldMap->addClickEventListener([](Ref*) { plugin::showPlugin<components::WorldMapView>(); });
		}
	}

	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	if (eventListener != nullptr)
	{
		eventListener->onTouchBegan = [this](Touch* touch, Event*) {
			auto location = touch->getLocation();
			auto palaceMap = this->getChildByName("Scene")->getChildByName("palace");
			if (palaceMap != nullptr)
			{
				auto mapPos = palaceMap->getPosition();
				auto mapSize = palaceMap->getContentSize();
				if (location.x >= mapPos.x && location.x <= mapPos.x + mapSize.width && location.y >= mapPos.y && location.y <= mapPos.y + mapSize.height)
				{
					this->onPalaceMapClicked(location);
				}
			}
			return true;
		};
		eventListener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	}

	return true;
}

int PalaceScene::getClickedPalaceId(const cocos2d::Vec2& pos)
{
	TMXTiledMap* map = reinterpret_cast<TMXTiledMap*>(getChildByName("Scene")->getChildByName("palace"));

	auto mapPos = map->getPosition();
	auto yscale = map->getScaleY();
	auto xscale = map->getScaleX();

	for (const auto& palace : palaces)
	{
		auto x = mapPos.x + palace.x * xscale;
		auto y = mapPos.y + palace.y * yscale;
		auto width = palace.width * xscale;
		auto height = palace.height * yscale;
		if (x <= pos.x && x + width >= pos.x && y <= pos.y && y + height >= pos.y)
		{
			return palace.id;
		}
	}
	return -1;
}

void PalaceScene::onPalaceMapClicked(const cocos2d::Vec2& pos)
{
	const int id = getClickedPalaceId(pos);
	if (id < 0) { return; }
	CCLOG("clicked palace %d", id);
}

void PalaceScene::initPalaces()
{
	TMXTiledMap* map = reinterpret_cast<TMXTiledMap*>(getChildByName("Scene")->getChildByName("palace"));

	TMXObjectGroup* objGroup = map->getObjectGroup("palaces");
	if (objGroup == nullptr) { return; }


	for (const auto& palace : objGroup->getObjects())
	{
		try
		{
			const auto x = palace.asValueMap().at("x").asInt();
			const auto y = palace.asValueMap().at("y").asInt();
			const auto width = palace.asValueMap().at("width").asInt();
			const auto height = palace.asValueMap().at("height").asInt();
			const auto id = palace.asValueMap().at("id").asInt();
			palaces.push_back(PalaceInfo{ id, x, y, width, height });
		}
		catch (const std::out_of_range& e)
		{
			CCLOGERROR("%s", e.what());
		}
	}
}
