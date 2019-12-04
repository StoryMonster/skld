#include "PlayerInfoView.h"
#include "cocostudio/CocoStudio.h"
#include "model/Player.h"

USING_NS_CC;
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

START_NS_PLUGIN

void PlayerInfoView::init()
{
	const std::string resPath = "res/res/PlayerInfo.csb";
	node = CSLoader::createNode(resPath);
	if (node == nullptr) { return; }

	if (btnBack == nullptr)
	{
		btnBack = reinterpret_cast<ui::Button*>(node->getChildByName("btnBack"));
		if (btnBack != nullptr) { btnBack->addClickEventListener([this](Ref*) { close(); }); }
		else { CCLOG("btnBack is not found in %s", resPath.c_str()); }
	}

	if (txtName == nullptr)
	{
		txtName = reinterpret_cast<ui::Text*>(node->getChildByName("txtName"));
		if (txtName != nullptr) { txtName->setString(Player::getInstance().getName()); }
	}

	if (txtKnowledge == nullptr)
	{
		txtKnowledge = reinterpret_cast<ui::Text*>(node->getChildByName("txtKnowledge"));
		if (txtKnowledge != nullptr) { txtKnowledge->setString("÷«¡¶: " + std::to_string(Player::getInstance().getKnowledge())); }
	}

	if (txtStrength == nullptr)
	{
		txtStrength = reinterpret_cast<ui::Text*>(node->getChildByName("txtStrength"));
		if (txtKnowledge != nullptr) { txtKnowledge->setString("Œ‰¡¶: " + std::to_string(Player::getInstance().getStrength())); }
	}

}

END_NS_PLUGIN