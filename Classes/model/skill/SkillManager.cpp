#include "SkillManager.h"
#include "cocos2d.h"

using namespace rapidjson;
USING_NS_CC;
START_NS_SKILL

SkillType convert(std::uint32_t val)
{
	switch (val)
	{
	case 1: return SkillType::KnowledgeSkill;
	case 2: return SkillType::StrengthSkill;
	case 3: return SkillType::MagicSkill;
	case 4: return SkillType::WarSkill;
	default: return SkillType::Unknown;
	}
}

SkillManager::SkillManager()
{
}

SkillManager& SkillManager::getInstance()
{
	static SkillManager instance;
	return instance;
}

void SkillManager::loadSkills()
{
	const std::string filename = "original/skills.json";
	const std::string strJson = FileUtils::getInstance()->getStringFromFile(filename);
	if (strJson.size() == 0)
	{
		CCLOGERROR("no content was found in %s, load skills fail", filename.c_str());
		return;
	}

	Document jsonDoc;
	jsonDoc.Parse<0>(strJson.c_str());
	if (jsonDoc.HasParseError())
	{
		CCLOGERROR("parse %s fail, load skills fail", filename.c_str());
		return;
	}
	if (jsonDoc.IsObject())
	{
		if (!jsonDoc.HasMember("skills") || !jsonDoc["skills"].IsArray())
		{
			CCLOGERROR("'skills' is not found in %s or 'skills' is not an array", filename.c_str());
			return;
		}
		for (unsigned int i = 0; i < jsonDoc["skills"].Size(); ++i)
		{
			const auto& skill = jsonDoc["skills"][i];
			if (!allSkillMemberCorrect(skill))
			{
				CCLOGERROR("One city configuration if error!");
				continue;
			}
			const std::uint32_t id = skill["id"].GetInt();
			const SkillType type = convert(skill["type"].GetInt());
			const std::string name = skill["name"].GetString();
			const std::string description = skill["description"].GetString();
			if (allSkills.find(id) == allSkills.end())
			{
				allSkills.emplace(id, std::make_shared<SkillModel>(id, name, type));
				allSkills.at(id)->setDescription(description);
			}
		}
	}
}

std::shared_ptr<SkillModel> SkillManager::getSkillById(std::uint32_t id)
{
	if (allSkills.find(id) != allSkills.end())
	{
		return allSkills.at(id);
	}
	return nullptr;
}

bool SkillManager::allSkillMemberCorrect(const rapidjson::Value& skill)
{
	return skill.HasMember("id") && skill["id"].IsUint() &&
		skill.HasMember("name") && skill["name"].IsString() &&
		skill.HasMember("type") && skill["type"].IsUint() &&
		skill.HasMember("description") && skill["description"].IsString();
}


END_NS_SKILL