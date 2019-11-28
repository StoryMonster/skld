#pragma once
#include <cstdint>
#include <string>

namespace country
{

class CountryModel
{
public:
	CountryModel(::std::uint32_t id, const ::std::string& name, ::std::uint32_t kingCode);
	inline ::std::string getCountryName() const { return name; }

private:
	::std::uint32_t countryId = 0;
	::std::string name = "";
	::std::uint32_t kingCode = 0;
};
}