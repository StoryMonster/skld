#include "Player.h"
#include "cocos2d.h"
#include "model/country/CountryManager.h"
#include "model/skill/SkillManager.h"
#include <random>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

std::uint32_t getRandomSkillExperience()
{
	static std::random_device rd;
	static std::default_random_engine e(rd());
	std::uniform_int_distribution<std::uint32_t> d(0, 100);
	return d(e);
}

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

/*
 @function learnSkill
 @param id: ready to learn skill id
 @return >=0: experience value got
         -1: experience value reach to max
		 -2: skill is already learnt
		 -3: player didn't buy this skill
		 -4: the skill is unknown
*/
std::int32_t Player::learnSkill(std::uint32_t id)
{
	if (std::find(learntSkills.begin(), learntSkills.end(), id) != learntSkills.end()) { return -2; }
	if (std::find(boughtSkills.begin(), boughtSkills.end(), id) == boughtSkills.end()) { return -3; }
	const auto skill = skill::SkillManager::getInstance().getSkillById(id);
	if (skill == nullptr) { return -4; }

	auto learningSkillInfo = std::find_if(learningSkills.begin(), learningSkills.end(), [id](const auto& skillInfo) noexcept { return skillInfo.first == id; });
	if (learningSkillInfo == learningSkills.end())
	{
		learningSkills.emplace_back(id, 0);
		//learningSkillInfo = std::find_if(learningSkills.begin(), learningSkills.end(), [id](const auto& skillInfo) noexcept { return skillInfo.first == id; });
		learningSkillInfo = learningSkills.end() - 1;
	}
	const auto experienceVal = getRandomSkillExperience();
	const auto currentExperience = learningSkillInfo->second;
	const auto maxExp = skill->getMaxExperience();
	if (currentExperience + experienceVal >= maxExp)
	{
		learningSkills.erase(learningSkillInfo);
		boughtSkills.erase(std::remove(boughtSkills.begin(), boughtSkills.end(), id), boughtSkills.end());
		understandSkill(id);
		return -1;
	}
	learningSkillInfo->second += experienceVal;
	return experienceVal;
}
