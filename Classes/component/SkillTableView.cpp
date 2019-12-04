#include "SkillTableView.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "model/skill/SkillManager.h"

USING_NS_CC;

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

START_NS_COMPONENT

bool SkillTableCell::init()
{
	if (!extension::TableViewCell::init()) { return false; }
	const std::string resPath = "res/res/SkillItem.csb";
	auto node = CSLoader::createNode(resPath);
	if (node == nullptr)
	{
		CCLOGERROR("Cannot find %s!", resPath.c_str());
		return false;
	}
	addChild(node);
	return true;
}

bool SkillTableView::init()
{
	if (!Layer::init()) { return false; }
	auto tableView = extension::TableView::create(this, Size(100, 150));
	if (tableView == nullptr) { return false; }
	tableView->setDirection(extension::ScrollView::Direction::VERTICAL);
	tableView->setDelegate(this);
	tableView->setAnchorPoint(Vec2(0.5, 0.5));
	tableView->setVerticalFillOrder(extension::TableView::VerticalFillOrder::TOP_DOWN);
	addChild(tableView);
	const auto parentSize = getContentSize();
	const auto tableViewSize = tableView->getContentSize();
	const auto x = (parentSize.width - tableViewSize.width) / 2;
	const auto y = (parentSize.height - tableViewSize.height) / 2;
	tableView->setPosition(Vec2(x, y));
	tableView->reloadData();
	CCLOG("SkillTableView create successfully");
	return true;
}

void SkillTableView::tableCellTouched(extension::TableView* table, extension::TableViewCell* cell)
{
	const std::uint32_t skillid = reinterpret_cast<SkillTableCell*>(cell)->getSkillId();
	const auto skill = skill::SkillManager::getInstance().getSkillById(skillid);
	if (skill != nullptr)
	{
		CCLOG("pressed skill %s", skill->getSkillName().c_str());
	}
	else
	{
		CCLOG("touched unknown position");
	}
}

Size SkillTableView::cellSizeForTable(extension::TableView* table)
{
	return Size(100, 30);
}

extension::TableViewCell* SkillTableView::tableCellAtIndex(extension::TableView* table, ssize_t idx)
{
	auto cell = table->dequeueCell();
	if (cell == nullptr)
	{
		cell = SkillTableCell::create();
		if (cell == nullptr) { return nullptr; }
	}
	auto lblSkillName = reinterpret_cast<ui::Text*>(cell->getChildByName("SkillItem")->getChildByName("lblSkillName"));
	auto skill = skill::SkillManager::getInstance().getSkillById(idx+1);
	if (skill != nullptr)
	{
		lblSkillName->setString(skill->getSkillName());
		reinterpret_cast<SkillTableCell*>(cell)->setSkillId(idx+1);
	}
	return cell;
}

ssize_t SkillTableView::numberOfCellsInTableView(extension::TableView* table)
{
	return 5;
}

END_NS_COMPONENT