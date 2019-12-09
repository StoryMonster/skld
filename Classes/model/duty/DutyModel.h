#pragma once
#include "Namespaces.h"
#include <cstdint>
#include <string>

START_NS_DUTY

class DutyModel
{
public:
	explicit DutyModel(std::uint32_t id, const std::string& name);

	inline std::string getDutyName() { return name; };

private:
	std::uint32_t id = 0;
	std::string name = "";
};

END_NS_DUTY