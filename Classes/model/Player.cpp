#include "Player.h"
#include "cocos2d.h"
#include "model/country/CountryManager.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

Player::Player() {}

Player& Player::getInstance()
{
	static Player instance;
	return instance;
}

void Player::setCountryToGovern(std::uint32_t countryId)
{
	auto country = country::CountryManager::getInstance().getCountryById(countryId);
	if (country == nullptr)
	{
		CCLOGERROR("Apply Country to player fail!");
		return;
	}
	this->countryId = countryId;
	this->name = country->getCountryName() + "Íõ";
}
