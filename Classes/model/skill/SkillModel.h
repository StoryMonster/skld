#pragma once
#include "Namespaces.h"
#include <cstdint>
#include <string>

START_NS_SKILL

enum class SkillType
{
	Unknown = 0,
	MagicSkill,
	PhysicSkill,
	SpiritSkill,
};

class SkillModel
{
public:
    explicit SkillModel(std::uint32_t id, const std::string& name, SkillType type);
	inline std::uint32_t getSkillId() const { return id; }
	inline SkillType getSkillType() const { return type; }
	inline std::string getSkillName() const { return name; }
	inline void setDescription(const std::string& desc) { description = desc; }
	inline std::string getDescription() const { return description; }

private:
	std::uint32_t id = 0;
	SkillType type = SkillType::Unknown;
	std::string name = "";
	std::string description = "";
};

END_NS_SKILL