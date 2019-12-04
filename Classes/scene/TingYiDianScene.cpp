#include "TingYiDianScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "plugin/PluginCenter.h"
#include "plugin/WorldMapView.h"
#include "PalaceScene.h"


USING_NS_CC;
using namespace cocostudio::timeline;
START_NS_SCENE

constexpr int OFFICIAL_NUM = 8;

Scene* TingYiDianScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TingYiDianScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool TingYiDianScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("TingYiScene.csb");
	if (rootNode == nullptr)
	{
		CCLOGERROR("load TingYiDianScene.csb fail");
		return false;
	}
	addChild(rootNode);


	if (btnWorldMap == nullptr)
	{
		btnWorldMap = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnWorldMap"));
		if (btnWorldMap != nullptr)
		{
			btnWorldMap->addClickEventListener([](Ref*) { plugin::PluginCenter::getInstance().showPlugin(std::make_shared<plugin::WorldMapView>()); });
		}
	}

	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnQuit"));
		if (btnBack != nullptr)
		{
			btnBack->addClickEventListener([](Ref*) {
				Director::getInstance()->replaceScene(PalaceScene::createScene());
			});
		}
	}

	initOfficials();

	if (eventListener == nullptr)
	{
		eventListener = EventListenerTouchOneByOne::create();
		eventListener->onTouchBegan = [this](Touch* touch, Event*) {
			onTouchBegan(touch);
			return true;
		};
		eventListener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	}
	return true;
}

void TingYiDianScene::initOfficials()
{
	officials.resize(OFFICIAL_NUM, OfficialInfo{});

	const auto rootNode = getChildByName("Scene");
	for (int i = 0; i < OFFICIAL_NUM; ++i)
	{
		auto sprite = reinterpret_cast<Sprite*>(rootNode->getChildByName("btnMan" + std::to_string(i+1)));
		if (sprite != nullptr)
		{
			officials.at(i).sprite = sprite;
			officials.at(i).originalPos = sprite->getPosition();
			officials.at(i).originalScaleX = sprite->getScaleX();
			officials.at(i).originalScaleY = sprite->getScaleY();
		}
	}
}

void TingYiDianScene::letOfficerStandOut(int index)
{
	if (index < 0 || index >= OFFICIAL_NUM || officials.at(index).sprite == nullptr) { return; }
	officials.at(index).sprite->setScaleX(3.0);
	officials.at(index).sprite->setScaleY(3.0);
	const auto winSize = Director::getInstance()->getVisibleSize();
	const auto officialSize = officials.at(index).sprite->getContentSize();
	const auto x = (winSize.width - officialSize.width) / 2;
	const auto y = officials.at(index).sprite != nullptr ? officials.at(index).sprite->getPosition().y : 170;
	officials.at(index).sprite->setPosition(Vec2(x, y));
	officials.at(index).isReporting = true;
}

void TingYiDianScene::letOfficerBack(int index)
{
	if (index < 0 || index >= OFFICIAL_NUM || officials.at(index).sprite == nullptr) { return; }
	officials.at(index).sprite->setScaleX(officials.at(index).originalScaleX);
	officials.at(index).sprite->setScaleY(officials.at(index).originalScaleY);
	officials.at(index).sprite->setPosition(officials.at(index).originalPos);
	officials.at(index).isReporting = false;
}

int TingYiDianScene::getStandingOutOfficerIndex()
{
	for (int i = 0; i < OFFICIAL_NUM; ++i)
	{
		if (officials.at(i).sprite == nullptr) { continue; };
		if (officials.at(i).isReporting) { return i; }
	}
	return -1;
}

void TingYiDianScene::onTouchBegan(Touch* touch)
{
	auto pos = touch->getLocation();
	auto index = getClickedOfficialIndex(pos);
	if (index >= 0)
	{
		CCLOG("clicked official index %d", index);
		const auto reportingOfficerIndex = getStandingOutOfficerIndex();
		letOfficerBack(reportingOfficerIndex);
		if (reportingOfficerIndex != index) { letOfficerStandOut(index); }
	}

}

int TingYiDianScene::getClickedOfficialIndex(const Vec2& touchPos)
{
	for (int i = 0; i < OFFICIAL_NUM; ++i)
	{
		if (officials.at(i).sprite == nullptr) { continue; };
		const auto pos = officials.at(i).sprite->getPosition();
		const auto size = officials.at(i).sprite->getContentSize();

		if (pos.x <= touchPos.x && pos.x + size.width >= touchPos.x && pos.y <= touchPos.y && pos.y + size.height >= touchPos.y) { return i; }
	}
	return -1;
}
END_NS_SCENE