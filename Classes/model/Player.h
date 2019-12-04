#pragma once
#include <cstdint>
#include <vector>
#include <string>

class Player
{
public:
	static Player& getInstance();
	void setCountryToGovern(std::uint32_t);

	inline void setKnowledge(std::uint32_t val) { knowledge = val; }
	inline std::uint32_t getKnowledge() const { return knowledge; }
	inline void setStrength(std::uint32_t val) { strength = val; }
	inline std::uint32_t getStrength() const { return strength; }
	inline std::string getName() const { return name; }

private:
	Player();
	std::string name = "";
	std::uint32_t countryId = 0;
	std::uint32_t knowledge = 0;
	std::uint32_t strength = 0;
	std::vector<std::uint32_t> skills{};

};