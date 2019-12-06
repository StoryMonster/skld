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

	inline std::vector<std::uint32_t> getBoughtSkills() const { return boughtSkills; }
	inline void buyASkill(std::uint32_t id) { boughtSkills.push_back(id); }

	inline std::vector<std::uint32_t> getLearntSkills() const { return learntSkills; }
	inline void understandSkill(std::uint32_t id) { learntSkills.push_back(id); }

	std::int32_t learnSkill(std::uint32_t id);

private:
	Player();

	std::string name = "";
	std::uint32_t countryId = 0;
	std::uint32_t knowledge = 0;
	std::uint32_t strength = 0;
	std::vector<std::uint32_t> learntSkills{};
	std::vector<std::pair<std::uint32_t, std::uint32_t>> learningSkills{};
	std::vector<std::uint32_t> boughtSkills{};
};