#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include "CountryModel.h"
#include "json/document.h"

START_NS_COUNTRY
class CountryManager
{
public:
	static CountryManager& getInstance();
	void loadCountries();
	::std::shared_ptr<CountryModel> getCountryById(::std::uint32_t);

private:
	CountryManager();
	bool allCountryMemberCorrect(const rapidjson::Value&);

	::std::map<::std::uint32_t, ::std::shared_ptr<CountryModel>> allCountries{};
};

END_NS_COUNTRY