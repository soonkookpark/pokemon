#pragma once
#include "Scene.h"
#include "Framework.h"
#include "AnimationController.h"
#include "StringTable.h"
#include "DataTableMgr.h"
class SpriteGo;
class TextGo;
class SceneTitle :
    public Scene
{
protected:
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	AnimationController animation1;
	AnimationController animation2;
	AnimationController animation3;
	AnimationController animation4;

	SpriteGo* mainPikachu = nullptr;
	SpriteGo* mainSpinda = nullptr;;
	SpriteGo* mainHooh1 = nullptr;
	SpriteGo* mainHooh2 = nullptr;

	sf::Clock titleClock;
	bool timeCheck;

	TextGo* title = nullptr;
	sf::Sound openSound;
	std::wstring startMessage;

	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);

public:

	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void ChangeScene();
};

