#pragma once
#include "Namespaces.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <cstdint>

START_NS_COMPONENT

class SkillTableCell : public cocos2d::extension::TableViewCell
{
public:
	bool init() override;
	CREATE_FUNC(SkillTableCell);

	inline void setSkillId(std::uint32_t id) { skillId = id; }
	inline std::uint32_t getSkillId() const { return skillId; }

private:
	std::uint32_t skillId = 0;
};

class SkillTableView : public cocos2d::Layer, public cocos2d::extension::TableViewDelegate, public cocos2d::extension::TableViewDataSource
{
public:
	bool init() override;

	CREATE_FUNC(SkillTableView);

	void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) override;
	cocos2d::Size cellSizeForTable(cocos2d::extension::TableView* table) override;
	cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView* table, ssize_t idx) override;
	ssize_t numberOfCellsInTableView(cocos2d::extension::TableView* table) override;
};

END_NS_COMPONENT