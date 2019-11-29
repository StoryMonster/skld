#pragma once

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"

namespace components
{

class XiWuFangView
{
public:
	static XiWuFangView* createPlugin();
	static std::string getPluginName();
	static XiWuFangView* instance;

	cocos2d::Node* getNode() noexcept;
	void close();

private:
	XiWuFangView();
	void init();
	void playTheAnimation();
	void setTrainingSubject(const std::string&);

	cocos2d::Node* node = nullptr;
	cocos2d::Node* bg = nullptr;
	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::ui::Button* btnTeacher = nullptr;
	cocos2d::ui::Text* txtTraining = nullptr;
};

}