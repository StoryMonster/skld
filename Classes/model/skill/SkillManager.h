#pragma once
#include "Namespaces.h"
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include "SkillModel.h"
#include "json/document.h"

START_NS_SKILL

class SkillManager
{
public:
	static SkillManager& getInstance();
	void loadSkills();
	std::shared_ptr<SkillModel> getSkillById(std::uint32_t);

private:
	SkillManager();
	bool allSkillMemberCorrect(const rapidjson::Value&);

	::std::map<::std::uint32_t, ::std::shared_ptr<SkillModel>> allSkills{};
};

END_NS_SKILL