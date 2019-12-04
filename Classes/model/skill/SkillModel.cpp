#include "SkillModel.h"

START_NS_SKILL

SkillModel::SkillModel(std::uint32_t id, const std::string& name, SkillType type)
	: id{ id }, name{ name }, type{type}
{
}

END_NS_SKILL