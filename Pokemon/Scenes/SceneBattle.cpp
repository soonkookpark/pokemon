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
	AddGo(new SpriteGo("graphics/PokemonList.png", "List"));
	AddGo(new SpriteGo("graphics/PokemonList.png", "myMonster"));
	AddGo(new SpriteGo("graphics/User.png", "User"));
	SpriteGo* HpBar= (SpriteGo*)AddGo(new SpriteGo("graphics/HpBar.png", "HpBar"));
	SpriteGo* RealHpBar = (SpriteGo*)AddGo(new SpriteGo("graphics/RealHpBar.png", "RealHpBar"));
	HpBar->sprite.setScale(0.f, 0.f);
	RealHpBar->sprite.setScale(0.f, 0.f);
	AddGo(new RectangleGo(healthBar, "healthBar"));
	//std::cout<<rect.getPosition().x << std::endl;
	
	
	SpriteGo* effectBall = (SpriteGo*)AddGo(new SpriteGo("","Effect"));
	effectBall->sprite.setPosition(267, 530);
	effectBall->sprite.setScale(3.f, 3.f);
	effectBall->sortLayer = 204;

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MonsterBallEffect.csv"));
	animation.SetTarget(&effectBall->sprite);
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

	//한개 사이즈가 57,188
	//상대 이미지는 56,56
	//내 이미지는 48,48
	SpriteGo* list = (SpriteGo*)FindGo("List");
	sf::IntRect monsterImageRect(1, 18, enemySize, enemySize);
	list->sprite.setTextureRect(monsterImageRect);
	list->sprite.setPosition(-size.x/2, -size.y/2);
	list->SetOrigin(Origins::TL);
	list->sprite.setScale(8.5f, 8.5f);

	//내 몬스터
	SpriteGo* mymonster = (SpriteGo*)FindGo("myMonster");
	sf::IntRect myMonsterImageRect(693, 516, userMosterSize, userMosterSize);
	mymonster->sprite.setTextureRect(myMonsterImageRect);
	mymonster->sprite.setPosition(180, 428);
	mymonster->SetOrigin(Origins::TL);
	mymonster->sprite.setScale(6.5f, 6.5f);
	mymonster->sortLayer = 204;
	mymonster->SetActive(false);

	SpriteGo* user = (SpriteGo*)FindGo("User");
	sf::IntRect userImageRect(72, 374, userSize, userSize);
	user->sprite.setTextureRect(userImageRect);
	user->sprite.setPosition(size.x / 2, 150);
	user->SetOrigin(Origins::BR);
	user->sprite.setScale(8.5f, 8.5f);
	clock.restart();
	

	SpriteGo* HpBar = (SpriteGo*)FindGo("HpBar");
	HpBar->SetOrigin(Origins::TL);
	HpBar->sprite.setScale(1.f, 3.f);
	HpBar->SetPosition(186, 95);
	HpBar->sortLayer = 201;
	HpBar->SetActive(false);
	SpriteGo* realHpBar = (SpriteGo*)FindGo("RealHpBar");
	realHpBar->SetOrigin(Origins::TL);
	realHpBar->sprite.setScale(1.2f, 2.f);
	realHpBar->SetPosition(336, 95);
	realHpBar->sortLayer = 202;
	realHpBar->SetActive(false);
	RectangleGo* pokemonHealth = (RectangleGo*)FindGo("healthBar");
	pokemonHealth->SetOrigin(Origins::TL);
	pokemonHealth->rectangle.setPosition(452, 111);
	pokemonHealth->rectangle.setFillColor(sf::Color::Green);
	pokemonHealth->sortLayer = 203;
	pokemonHealth->SetActive(false);
}

void SceneBattle::Exit()
{
	Scene::Exit();
}

void SceneBattle::Update(float dt)
{
	//test code
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos(); //마우스 위치
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);

	SpriteGo* list = (SpriteGo*)FindGo("List");
	list->SetOrigin(Origins::TR);
	SpriteGo* mymonster = (SpriteGo*)FindGo("myMonster");
	SpriteGo* effectBall = (SpriteGo*)FindGo("Effect");
	SpriteGo* user = (SpriteGo*)FindGo("User");
	user->SetOrigin(Origins::BL);
	if (!listMove) {
		list->sprite.move(4.f, 0);
		clock.restart();
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
	if (listMove)
	{
		RectangleGo* pokemonHealth = (RectangleGo*)FindGo("healthBar");
		SpriteGo* realHpBar = (SpriteGo*)FindGo("RealHpBar");
		SpriteGo* HpBar = (SpriteGo*)FindGo("HpBar");
		pokemonHealth->SetActive(true);
		realHpBar->SetActive(true);
		HpBar->SetActive(true);
	}
	if (clock.getElapsedTime() > interfaceTime)
	{
		if (userMove&&INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			userMove = false;
			//user->sprite.move(-5.f, 0.f);
			//user->SetActive(false);
		}
	}
	/*std::cout << user->sprite.getPosition().x << std::endl;
	std::cout << -windowSize.x << std::endl;*/
	if (user->GetActive() && user->sprite.getPosition().x <= -windowSize.x)
	{
		user->SetActive(false);
	}
	if (!user->GetActive()&&!aniPlay)
	{
		animation.Play("MonsterBallEffect");
		
		std::cout << "실행했다." << std::endl;
		aniPlay = true;
		clock.restart();
	}

	if (aniPlay && clock.getElapsedTime() > sf::seconds(0.4f))
	{
		effectBall->SetActive(false);
	}
	if (!effectBall->GetActive())
	{
		mymonster->SetActive(true);
	}
	if (clock.getElapsedTime() > interfaceTime)
	{
		if (userMove&&INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			userMove = false;
			//user->sprite.move(-5.f, 0.f);
			//user->SetActive(false);
		}
	}
	/*std::cout << user->sprite.getPosition().x << std::endl;
	std::cout << -windowSize.x << std::endl;*/
	if (user->GetActive() && user->sprite.getPosition().x <= -windowSize.x)
	{
		user->SetActive(false);
	}
	if (!user->GetActive()&&!aniPlay)
	{
		animation.Play("MonsterBallEffect");
		
		std::cout << "실행했다." << std::endl;
		aniPlay = true;
		clock.restart();
	}

	if (aniPlay && clock.getElapsedTime() > sf::seconds(0.4f))
	{
		effectBall->SetActive(false);
	}
	if (!effectBall->GetActive())
	{
		mymonster->SetActive(true);
	}
	if (mymonster->GetActive())
	{
		Battle(dt);
	}











	animation.Update(dt);










	Scene::Update(dt);
	
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}


	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << mousePos.x << "," << mousePos.y << std::endl;
	}
}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneBattle::Battle(float dt)
{
	timer += dt;
	int turn = 0;
	RectangleGo* pokemonHealth = (RectangleGo*)FindGo("healthBar");
//	pokemonHealth
}

void SceneBattle::BattleEnd()
{
	SCENE_MGR.ChangeScene(SceneId::Game);
}
