#include "CityModel.h"

START_NS_CITY

CityModel::CityModel(std::uint32_t cityCode, const std::string& name, std::uint32_t countryCode, std::uint32_t officialCode, std::uint32_t population, bool isCapital)
	: cityCode{cityCode}
	, countryCode{countryCode}
	, officialCode{officialCode}
	, population{population}
	, name{name}
	, isCapital{ isCapital }
{}

CityModel::~CityModel()
{}

void CityModel::doEducatition()
{
}

void CityModel::doBusiness()
{
}

void CityModel::doAgricultural()
{
}

void CityModel::doIndustrial()
{

}

void CityModel::doIncreaseBornRate()
{

}

void CityModel::doDecreaseBornRate()
{
}

void CityModel::setTax(std::uint8_t val)
{

}

void CityModel::doConstription()
{
}

void CityModel::doLayoffs()
{

}

void CityModel::increasePeopleLoyalty(uint8_t val)
{
}

void CityModel::decreasePeopleLoyalty(uint8_t val)
{
}

void CityModel::increaseSoldierAmount(std::uint32_t val)
{
}

void CityModel::decreaseSoldierAmount(std::uint32_t val)
{
}

void CityModel::increasePopulation(std::uint32_t)
{
}
void CityModel::decreasePopulation(std::uint32_t)
{
}

END_NS_CITY