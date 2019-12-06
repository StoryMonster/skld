#include "XiuWenFangScene.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "plugin/ChooseSkillView.h"
#include "plugin/PluginCenter.h"
#include "model/skill/SkillManager.h"
#include "model/Player.h"
#include "PalaceScene.h"

USING_NS_CC;
using namespace cocostudio::timeline;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

START_NS_SCENE

Scene* XiuWenFangScene::createScene()
{
	auto scene = Scene::create();
	auto layer = XiuWenFangScene::create();
	scene->addChild(layer);
	return scene;
}

bool XiuWenFangScene::init()
{
	if (!Layer::init()) { return false; }

	const std::string resPath = "res/XiuWenFangScene.csb";
    auto rootNode = CSLoader::createNode(resPath);
	if (rootNode == nullptr)
	{
		CCLOGERROR("load %s fail", resPath.c_str());
		return false;
	}
	addChild(rootNode);

	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(rootNode->getChildByName("quit"));
		if (btnBack == nullptr) { CCLOGWARN("Cannot find the quit in %s", resPath.c_str()); }
		else { btnBack->addClickEventListener([this](Ref*) { this->quit(); }); }
	}

	if (btnTeacher == nullptr)
	{
		btnTeacher = reinterpret_cast<ui::Button*>(rootNode->getChildByName("btnTeacher"));
		if (btnTeacher == nullptr) { CCLOGWARN("Cannot find the btnTeacher in %s", resPath.c_str()); }
		else { btnTeacher->addClickEventListener([this](Ref*) { onTeacherClicked(); }); }
	}

	if (txtTraining == nullptr)
	{
		txtTraining = reinterpret_cast<ui::Text*>(rootNode->getChildByName("txtTraining"));
	}

	return true;
}

void XiuWenFangScene::onTeacherClicked()
{
	if (trainingSkillId != 0)
	{
		CCLOG("Today is too late, please come here next time!");
		return;
	}
	const std::vector<skill::SkillType> type{ skill::SkillType::KnowledgeSkill, skill::SkillType::MagicSkill };
	plugin::PluginCenter::getInstance().showPlugin(std::make_shared<plugin::ChooseSkillView>(type));

	_eventDispatcher->addCustomEventListener("EVT_CHOOSE_SKILL_TO_TRAIN", [this](const EventCustom* event) {
		_eventDispatcher->removeCustomEventListeners("EVT_CHOOSE_SKILL_TO_TRAIN");
		CCLOG("custom event received");
		const auto skillId = reinterpret_cast<std::uint32_t*>(event->getUserData());
		const auto skill = skill::SkillManager::getInstance().getSkillById(*skillId);
		if (skill != nullptr)
		{
			trainingSkillId = *skillId;
			setTrainingSubject(skill->getSkillName());
			playTheAnimation();
		}
	});
}

void XiuWenFangScene::quit()
{
	auto scene = PalaceScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void XiuWenFangScene::playTheAnimation()
{
	auto action = CSLoader::createTimeline("res/XiuWenFangScene.csb");
	if (action == nullptr)
	{
		CCLOGWARN("Xiu Wen animation is not found!");
		return;
	}
	CCLOG("Playing XiuWenFang animation");
	this->runAction(action);
	action->addFrameEndCallFunc(4, "", [this]() { onTrainingEnd(); });
	action->gotoFrameAndPlay(0, false);
}

void XiuWenFangScene::setTrainingSubject(const std::string& name)
{
	if (this->txtTraining == nullptr) { return; }
	this->txtTraining->setString("½ñÈÕ¿Î³Ì: " + name);
}

void XiuWenFangScene::onTrainingEnd()
{
	if (trainingSkillId == 0) { return; }
	const auto skill = skill::SkillManager::getInstance().getSkillById(trainingSkillId);
	const auto ret = Player::getInstance().learnSkill(trainingSkillId);
	if (ret == -1)
	{
		CCLOG("Congratuation! You learnt %s", skill->getSkillName().c_str());
	}
	else if (ret == -2)
	{
		CCLOG("You have already learnt %s, so you learn it fail", skill->getSkillName().c_str());
		trainingSkillId = 0;
	}
	else if (ret == -3)
	{
		CCLOG("You cannot learnt %s, since you don't have it", skill->getSkillName().c_str());
		trainingSkillId = 0;
	}
	else if (ret == -4)
	{
		CCLOG("%s is unknown", skill->getSkillName().c_str());
		trainingSkillId = 0;
	}
	else if (ret >= 0)
	{
		CCLOG("%s exp + %d", skill->getSkillName().c_str(), ret);
	}
}

END_NS_SCENE