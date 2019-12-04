#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PalaceScene.h"

USING_NS_CC;
using namespace cocostudio::timeline;
START_NS_SCENE

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
	if (rootNode == nullptr)
	{
		CCLOGERROR("load MainScene.csb fail");
		return false;
	}
    addChild(rootNode);

	if (btnGameStart == nullptr)
	{
		btnGameStart = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnStartGame"));
		if (btnGameStart != nullptr) { btnGameStart->addClickEventListener([](Ref*) {
			auto scene = PalaceScene::createScene();
			Director::getInstance()->runWithScene(scene);
		}); }
	}

	if (btnQuitGame == nullptr)
	{
		btnQuitGame = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnQuitGame"));
		if (btnQuitGame != nullptr) {
			btnQuitGame->addClickEventListener([](Ref*) { exit(0); });
		}
	}

    return true;
}
END_NS_SCENE