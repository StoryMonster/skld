#pragma once
#include "Namespaces.h"
#include <cstdint>
#include <string>

START_NS_CITY

class CityModel
{
public:
    CityModel(std::uint32_t cityCode, const std::string& name, std::uint32_t countryCode, std::uint32_t officialCode, std::uint32_t population, bool isCapital);
    ~CityModel();

    void doEducatition();
    void doBusiness();
    void doAgricultural();
    void doIndustrial();
    void doConstription();
    void doLayoffs();

    void doIncreaseBornRate();
    void doDecreaseBornRate();

    void setTax(std::uint8_t);

	inline std::uint32_t getPopulation() const { return population; }
	inline std::string getCityName() const { return name; };
	inline std::uint32_t getCountryId() const { return countryCode; }

private:
    void increasePeopleLoyalty(uint8_t);
    void decreasePeopleLoyalty(uint8_t);
    void increasePopulation(std::uint32_t);
    void decreasePopulation(std::uint32_t);
    void increaseSoldierAmount(std::uint32_t);
    void decreaseSoldierAmount(std::uint32_t);

    std::uint32_t cityMoney = 0;
    std::uint32_t business = 0;
    std::uint32_t agricultural = 0;
    std::uint32_t industrial = 0;

	std::uint32_t cityCode = 0;
    std::uint32_t countryCode = 0;
	std::uint32_t officialCode = 0;
	std::uint32_t population = 0;

    std::uint32_t troopAmount = 0;
    std::uint32_t horseAmount = 0;
    std::uint32_t soldierAmount = 0;

    std::uint8_t peopleLoyalty = 0;
    std::uint8_t taxRate = 0;
    std::uint8_t safeRate = 0;
    std::uint8_t bornRate = 0;

    std::string name = "";
	bool isCapital = false;
};
END_NS_CITY