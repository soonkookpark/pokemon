#pragma once
#include "Scene.h"
#include"Framework.h"
class SceneBattle : public Scene
{
protected:
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::RectangleShape rect;
	int enemySize = 56;
	int userSize = 48; //���� ��� �̹���
	int userMosterSize = 48; // ���� ���ϸ� �̹���
	bool listMove = false;
	bool userMove = false;
public:

	SceneBattle();
	virtual ~SceneBattle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void BattleEnd();
};

