#pragma once
#include "Scene.h"
#include "Framework.h"
#include "AnimationController.h"
class SceneBattle : public Scene
{
protected:
	AnimationController animation;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::RectangleShape rect;
	int enemySize = 56;
	int userSize = 48; //유저 사람 이미지
	int userMosterSize = 48; // 유저 포켓몬 이미지
	int timer = 0;
	bool listMove = false;
	bool userMove = false;
	bool aniPlay = false;
	sf::Clock clock;
	sf::Time interfaceTime = sf::seconds(3.f);
	sf::Vector2f healthBar = { 354.f,25.f };
	sf::Vector2f effectSize = { 50.f,50.f };

public:

	SceneBattle();
	virtual ~SceneBattle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void Battle(float dt);
	void PlayerMenu();
	void SkillSelect();
	//void Bag();
	void BattleEnd();
};

