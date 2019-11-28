#include "CountryManager.h"
#include "cocos2d.h"
#include "CountryModel.h"

using namespace rapidjson;
USING_NS_CC;

namespace country
{
CountryManager::CountryManager() {}

CountryManager& CountryManager::getInstance()
{
	static CountryManager instance;
	return instance;
}

void CountryManager::loadCountries()
{
	const std::string filename = "original/countries.json";
	const std::string strJson = FileUtils::getInstance()->getStringFromFile(filename);
	if (strJson.size() == 0)
	{
		CCLOGERROR("no content was found in %s, load countries fail", filename.c_str());
		return;
	}

	Document jsonDoc;
	jsonDoc.Parse<0>(strJson.c_str());
	if (jsonDoc.HasParseError())
	{
		CCLOGERROR("parse %s fail, load countries fail", filename.c_str());
		return;
	}
	if (jsonDoc.IsObject())
	{
		if (!jsonDoc.HasMember("countries") || !jsonDoc["countries"].IsArray())
		{
			CCLOGERROR("'countries' is not found in %s or 'countries' is not an array", filename.c_str());
			return;
		}
		for (unsigned int i = 0; i < jsonDoc["countries"].Size(); ++i)
		{
			const auto& country = jsonDoc["countries"][i];
			if (!allCountryMemberCorrect(country))
			{
				CCLOGERROR("One city configuration if error!");
				continue;
			}
			const std::uint32_t id = country["id"].GetInt();
			const std::string name = country["name"].GetString();
			const std::uint32_t kingCode = country["kingCode"].GetUint();
			if (allCountries.find(id) == allCountries.end())
			{
				allCountries.emplace(id, std::make_shared<CountryModel>(id, name, kingCode));
			}
		}
	}
}

bool CountryManager::allCountryMemberCorrect(const rapidjson::Value& country)
{
	return country.HasMember("id") && country["id"].IsUint() &&
		country.HasMember("name") && country["name"].IsString() &&
		country.HasMember("kingCode") && country["kingCode"].IsUint();
}

std::shared_ptr<CountryModel> CountryManager::getCountryById(std::uint32_t id)
{
	if (allCountries.find(id) == allCountries.end()) { return nullptr; }
	return allCountries.at(id);
}
}