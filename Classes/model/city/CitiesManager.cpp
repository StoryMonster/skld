#include "CitiesManager.h"
#include "cocos2d.h"
#include "json/document.h"
//#include "json/writer.h"
//#include "json/stringbuffer.h"

using namespace rapidjson;
USING_NS_CC;

namespace city
{

CitiesManager::CitiesManager()
{

}

CitiesManager& CitiesManager::getInstance()
{
    static CitiesManager instance;
    return instance;
}

void CitiesManager::loadCities()
{
	const std::string filename = "original/cities.json";
	std::string jsonStr = FileUtils::getInstance()->getStringFromFile(filename);
	if (jsonStr.size() == 0)
	{
		CCLOGERROR("failed to read content from %s, load cities fail", filename.c_str());
		return;
	}

	Document jsonDoc;
	jsonDoc.Parse<0>(jsonStr.c_str());
	if (jsonDoc.HasParseError())
	{
		CCLOGERROR("parse %s fail, load cities fail", filename.c_str());
		return;
	}
	if (jsonDoc.IsObject())
	{
		if (!jsonDoc.HasMember("cities") || !jsonDoc["cities"].IsArray())
		{
			CCLOGERROR("'cities' is not found in %s or 'cities' is not an array", filename.c_str());
			return;
		}
		for (int i = 0; i < jsonDoc["cities"].Size(); ++i)
		{
			const auto& city = jsonDoc["cities"][i];
			if (!allCityMemberCorrect(city))
			{
				CCLOGERROR("One city configuration if error!");
				continue;
			}
			const std::uint32_t id = city["id"].GetInt();
			const std::string name = city["name"].GetString();
			const std::uint32_t population = city["population"].GetUint();
			const bool isCapital = city["isCapital"].GetBool();
			const std::uint32_t countryCode = city["countryCode"].GetUint();
			const std::uint32_t officialCode = city["officialCode"].GetUint();
			if (allCities.find(id) == allCities.end())
			{
				allCities.emplace(id, std::make_shared<CityModel>(id, name, countryCode, officialCode, population, isCapital));
			}
		}
	}
}

bool CitiesManager::allCityMemberCorrect(const rapidjson::Value& city)
{
	return city.HasMember("id") && city["id"].IsUint() &&
		city.HasMember("name") && city["name"].IsString() &&
		city.HasMember("population") && city["population"].IsUint() &&
		city.HasMember("countryCode") && city["countryCode"].IsUint() &&
		city.HasMember("officialCode") && city["officialCode"].IsUint() &&
		city.HasMember("isCapital") && city["isCapital"].IsBool();
}

std::shared_ptr<CityModel> CitiesManager::getCityModelById(std::uint32_t id)
{
	if (allCities.find(id) == allCities.end()) { return nullptr; }
	return allCities.at(id);
}
}