#pragma once
#include "Scene.h"
class SceneMyPokemon: public Scene
{
public:
	SceneMyPokemon(SceneId id = SceneId::MyPokemon);
	virtual ~SceneMyPokemon() = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

