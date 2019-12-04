#include "PalaceScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "plugin/WorldMapView.h"
#include "plugin/PluginCenter.h"
#include "plugin/PlayerInfoView.h"
#include "XiuWenFangScene.h"
#include "XiWuFangScene.h"
#include "TingYiDianScene.h"
#include "MainScene.h"


USING_NS_CC;
using namespace cocostudio::timeline;
START_NS_SCENE

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
			btnWorldMap->addClickEventListener([](Ref*) { plugin::PluginCenter::getInstance().showPlugin(std::make_shared<plugin::WorldMapView>()); });
		}
	}

	if (btnExit == nullptr)
	{
		btnExit = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnExit"));
		if (btnExit != nullptr)
		{
			btnExit->addClickEventListener([](Ref*) { Director::getInstance()->replaceScene(MainScene::createScene()); });
		}
	}

	if (btnShop == nullptr)
	{
		btnShop = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnShop"));
		if (btnShop != nullptr)
		{
			btnShop->addClickEventListener([](Ref*) { CCLOG("clicked the shop"); });
		}
	}

	if (btnSetting == nullptr)
	{
		btnSetting = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnSetting"));
		if (btnSetting != nullptr)
		{
			btnSetting->addClickEventListener([](Ref*) { CCLOG("clicked the setting"); });
		}
	}

	if (btnHead == nullptr)
	{
		btnHead = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnHead"));
		if (btnHead != nullptr)
		{
			btnHead->addClickEventListener([](Ref*) { plugin::PluginCenter::getInstance().showPlugin(std::make_shared<plugin::PlayerInfoView>()); });
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
				auto xscale = palaceMap->getScaleX();
				auto yscale = palaceMap->getScaleY();
				auto width = mapSize.width * xscale;
				auto height = mapSize.height * yscale;
				if (location.x >= mapPos.x && location.x <= mapPos.x + width && location.y >= mapPos.y && location.y <= mapPos.y + height)
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
	switch (id)
	{
	case 1:
		Director::getInstance()->replaceScene(TingYiDianScene::createScene());
		break;
	case 2:
		Director::getInstance()->replaceScene(XiuWenFangScene::createScene());
		break;
	case 3:
		Director::getInstance()->replaceScene(XiWuFangScene::createScene());
		break;
	default:
		CCLOGWARN("No palace found for id=%d", id);
	}
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
END_NS_SCENE