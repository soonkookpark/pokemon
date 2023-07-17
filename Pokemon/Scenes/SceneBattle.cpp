#include "stdafx.h"
#include "SceneBattle.h"
#include "Framework.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "RectangleGo.h"
#include "SpriteGo.h"

SceneBattle::SceneBattle() : Scene(SceneId::Battle)
{
	resourceListPath = "scripts/SceneBattleResourceList.csv";
}

void SceneBattle::Init()
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	//std::cout << "hi" << std::endl;
	worldView.setSize(windowSize);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);
	AddGo(new RectangleGo(windowSize, "square"));
	SpriteGo* monsterList = (SpriteGo*)AddGo(new SpriteGo("graphics/PokemonList.png", "List"));
	SpriteGo* userList = (SpriteGo*)AddGo(new SpriteGo("graphics/User.png", "User"));
	//std::cout<<rect.getPosition().x << std::endl;
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneBattle::Release()
{


	for (auto go : gameObjects)
	{
		//go->Release(); 소멸자에서 호출
		delete go;
	}
}

void SceneBattle::Enter()
{
	if (listMove)
	{
		listMove = false;
	}
	if (userMove)
	{
		userMove = false;
	}
	auto size = FRAMEWORK.GetWindowSize();
	//auto centerPos = size / 2.f;
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	Scene::Enter();
	RectangleGo* recgo = (RectangleGo*)FindGo("square");
	recgo->rectangle.setFillColor(sf::Color::White);
	recgo->SetOrigin(Origins::MC);
	recgo->rectangle.setPosition(0,0);

	SpriteGo* list = (SpriteGo*)FindGo("List");
	//한개 사이즈가 57,188
	//상대 이미지는 56,56
	//내 이미지는 48,48
	sf::IntRect monsterImageRect(1, 18, enemySize, enemySize);
	list->sprite.setTextureRect(monsterImageRect);
	list->sprite.setPosition(-size.x/2, -size.y/2);
	list->SetOrigin(Origins::TL);
	list->sprite.setScale(8.5f, 8.5f);
	SpriteGo* user = (SpriteGo*)FindGo("User");
	sf::IntRect userImageRect(72, 374, userSize, userSize);
	user->sprite.setTextureRect(userImageRect);
	user->sprite.setPosition(size.x / 2, size.y / 2);
	user->SetOrigin(Origins::BR);
	user->sprite.setScale(8.5f, 8.5f);
}

void SceneBattle::Exit()
{
	Scene::Exit();
}

void SceneBattle::Update(float dt)
{
	SpriteGo* list = (SpriteGo*)FindGo("List");
	list->SetOrigin(Origins::TR);
	SpriteGo* user = (SpriteGo*)FindGo("User");
	user->SetOrigin(Origins::BL);
	if (!listMove) {
		list->sprite.move(4.f, 0);
	}
	if (list->sprite.getPosition().x == windowSize.x/2)
	{
		list->sprite.move(0.f, 0.f);
		//list->SetPosition()
		listMove = true;
	}

	if (!userMove) 
	{
		user->sprite.move(-4.f, 0.f);
	}
	if (user->sprite.getPosition().x == -windowSize.x / 2)
	{
		user->sprite.move(0.f, 0.f);
		//list->SetPosition()
		userMove = true;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
		SCENE_MGR.ChangeScene(SceneId::Game);


	Scene::Update(dt);
}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneBattle::BattleEnd()
{
	SCENE_MGR.ChangeScene(SceneId::Game);
}
