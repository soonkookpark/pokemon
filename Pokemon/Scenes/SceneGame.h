#pragma once
#include "Scene.h"

class Player;
class TileMap;
class SceneGame : public Scene
{
protected:
	sf::FloatRect groundBounds;
	sf::FloatRect objectBounds;
	Player* player;
	bool battleNow = false;
	float moveSpeed = 0.f;
	TileMap* tileMap = nullptr;
	//--------------------
	float transitionSpeed = 100.f; // 화면 전환 속도 (픽셀 단위)

	sf::Clock clock;
	sf::Time elapsedTime;
	bool transitionInProgress = false;
	sf::Vector2f rectSize = { 1.0f, 1.0f };



public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void CheckCollide(float dt);
	void BattleStart(float dt);
};

