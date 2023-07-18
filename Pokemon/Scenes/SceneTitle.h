#pragma once
#include "Scene.h"
#include "Framework.h"
#include "AnimationController.h"
class SceneTitle :
    public Scene
{
protected:
	AnimationController animation;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
public:

	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

