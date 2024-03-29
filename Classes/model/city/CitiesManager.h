#pragma once
#include "Namespaces.h"
#include <string>
#include <map>
#include <memory>
#include "CityModel.h"
#include "json/document.h"

START_NS_CITY

class CitiesManager
{
public:
    static CitiesManager& getInstance();
    void loadCities();
	std::shared_ptr<CityModel> getCityModelById(std::uint32_t);

private:
    CitiesManager();
	bool allCityMemberCorrect(const rapidjson::Value&);

	std::map<std::uint32_t, std::shared_ptr<CityModel>> allCities{};
};
END_NS_CITY