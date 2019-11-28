#include "CountryModel.h"

namespace country
{

CountryModel::CountryModel(std::uint32_t id, const std::string& name, std::uint32_t kingCode)
	: countryId{id}
	, name{name}
	, kingCode{kingCode}
{
}

}
