#include "DutyManager.h"

START_NS_DUTY

DutyManager::DutyManager() {}

DutyManager& DutyManager::getInstance()
{
	static DutyManager instance;
	return instance;
}

std::shared_ptr<DutyModel> DutyManager::getDutyById(std::uint32_t id)
{
	return duties.find(id) != duties.end() ? duties.at(id) : nullptr;
}



END_NS_DUTY