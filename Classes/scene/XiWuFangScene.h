#pragma once
#include "Namespaces.h"
#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"

START_NS_SCENE

class XiWuFangScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(XiWuFangScene);

private:
	void playTheAnimation();
	void setTrainingSubject(const std::string&);
	void quit();
	void onTrainingEnd();
	void onTeacherClicked();

	cocos2d::ui::Button* btnBack = nullptr;
	cocos2d::ui::Button* btnTeacher = nullptr;
	cocos2d::ui::Text* txtTraining = nullptr;
	std::uint32_t trainingSkillId = 0;
};
END_NS_SCENE