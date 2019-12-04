#include "CountryModel.h"

START_NS_COUNTRY

CountryModel::CountryModel(std::uint32_t id, const std::string& name, std::uint32_t kingCode)
	: countryId{id}
	, name{name}
	, kingCode{kingCode}
{
}

END_NS_COUNTRY
