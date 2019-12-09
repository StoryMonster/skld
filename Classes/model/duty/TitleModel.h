#pragma once
#include "Namespaces.h"
#include <cstdint>
#include <string>

START_NS_DUTY

class TitleModel
{
public:
	TitleModel(std::uint32_t id, const std::string& name);

	inline std::string getTitleName() const { return name; };

private:
	std::uint32_t id = 0;
	std::string name = "";
};

END_NS_DUTY