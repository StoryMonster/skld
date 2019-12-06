#pragma once
#include "Namespaces.h"
#include <cstdint>
#include <string>

START_NS_SKILL

enum class SkillType
{
	Unknown = 0,
	KnowledgeSkill,
	StrengthSkill,
	MagicSkill,
	WarSkill,
};

class SkillModel
{
public:
    explicit SkillModel(std::uint32_t id, const std::string& name, SkillType type);

	inline std::uint32_t getSkillId() const { return id; }
	inline SkillType getSkillType() const { return type; }
	inline std::string getSkillName() const { return name; }

	inline std::uint32_t getMaxExperience() const { return maxExperience; }
	inline void setMaxExperience(std::uint32_t val) { maxExperience = val; }

	inline void setDescription(const std::string& desc) { description = desc; }
	inline std::string getDescription() const { return description; }

private:
	std::uint32_t id = 0;
	SkillType type = SkillType::Unknown;
	std::string name = "";
	std::string description = "";
	std::uint32_t maxExperience = 100;
};

END_NS_SKILL