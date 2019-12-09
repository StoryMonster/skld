#pragma once
#include "Namespaces.h"
#include "DutyModel.h"
#include <map>
#include <cstdint>
#include <memory>

START_NS_DUTY

class DutyManager
{
public:
	static DutyManager& getInstance();
	std::shared_ptr<DutyModel> getDutyById(std::uint32_t);

private:
	DutyManager();

	std::map<std::uint32_t, std::shared_ptr<DutyModel>> duties{};
};

END_NS_DUTY