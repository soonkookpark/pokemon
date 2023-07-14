#pragma once
#include "Scene.h"

class Player;
class TileMap;
class SceneGame : public Scene
{
protected:
	sf::FloatRect groundBounds;
	Player* player;
	bool battleNow = false;
	float moveSpeed = 0.f;
	TileMap* tileMap = nullptr;

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

