#include "stdafx.h"
#include "SceneTitle.h"
#include "Framework.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "RectangleGo.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "StringTable.h"
#include "DataTableMgr.h"

SceneTitle::SceneTitle() :Scene(SceneId::Title)
{
	resourceListPath = "scripts/SceneTitleResourceList.csv";
}

void SceneTitle::Init()
{
	Release();

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter(centerPos);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);
	mainHooh1 = (SpriteGo*)AddGo(new SpriteGo("", "TitleMonsterImage"));
	mainHooh2 = (SpriteGo*)AddGo(new SpriteGo("", "TitleMonsterImage2"));
	mainPikachu = (SpriteGo*)AddGo(new SpriteGo("", "TitleMonsterImage3"));
	mainSpinda = (SpriteGo*)AddGo(new SpriteGo("", "TitleMonsterImage4"));
	title = (TextGo*)AddGo(new TextGo("titleMessage", "fonts/DOSPilgi.ttf"));
	SpriteGo* BackGround = (SpriteGo*)AddGo(new SpriteGo("graphics/TitleImage.png","Background"));
	BackGround->sortLayer = -1;

	animation1.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/TitleAnimationMonster.csv"));
	animation2.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/TitleAnimationMonster2.csv"));
	animation3.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/TitleAnimationMonster3.csv"));
	animation4.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/TitleAnimationMonster4.csv"));
	animation1.SetTarget(&mainHooh1->sprite);
	animation2.SetTarget(&mainHooh2->sprite);
	animation3.SetTarget(&mainPikachu->sprite);
	animation4.SetTarget(&mainSpinda->sprite);
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release(); 소멸자에서 호출
		delete go;
	}
}

void SceneTitle::Enter()
{
	SpriteGo* BackGround = (SpriteGo*)FindGo("Background");
	BackGround->SetOrigin(Origins::MC);
	BackGround->SetPosition(FRAMEWORK.GetWindowSize().x / 2.f, FRAMEWORK.GetWindowSize().y / 2.f);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter(centerPos);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);
	mainHooh1->sortLayer = 200;
	mainHooh2->sortLayer = 200;
	mainPikachu->sortLayer = 200;
	mainSpinda->sortLayer = 200;
	
	mainHooh1->SetPosition(windowSize.x/2.f,windowSize.y/2.f+150.f);
	mainHooh1->sprite.setScale(8.0, 8.0);
	mainHooh2->SetPosition(1788,249);
	mainHooh2->sprite.setScale(3.0, 3.0);
	mainPikachu->SetPosition(1526, 160);
	mainPikachu->sprite.setScale(-2.0, 2.0);
	mainSpinda->SetPosition(1640,160);
	mainSpinda->sprite.setScale(1.5, 1.5);

	mainHooh1->SetOrigin(Origins::MC);
	mainHooh2->SetOrigin(Origins::MC);
	mainPikachu->SetOrigin(Origins::BC);
	mainSpinda->SetOrigin(Origins::BC);
	animation1.Play("TitleMonsterImage");
	animation2.Play("TitleMonsterImage2");
	animation3.Play("TitleMonsterImage3");
	animation4.Play("TitleMonsterImage4");
	openSound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sounds/Opening.wav"));
	openSound.setLoop(true);
	openSound.play();
	openSound.setVolume(50);

	Scene::Enter();
	std::string startMessage1 = stringTable->Get("TITLEMESSAGE", Languages::KOR);
	title->text.setString(startMessage1); 
	//title->text.setScale()
	title->text.setCharacterSize(50);
	//title->text.setOutlineThickness(5.f);
	title->text.setFillColor(sf::Color::Black);
	//title->text.setOutlineColor(sf::Color::Black);
	title->SetOrigin(Origins::MC);
	title->SetPosition(centerPos.x, centerPos.y +centerPos.y* 0.75);
	title->sortLayer = 1;
	title->SetActive(true);
	
}

void SceneTitle::Exit()
{
	openSound.stop();
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos(); //마우스 위치
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	ChangeScene();
	
	if (!timeCheck)
	{
		titleClock.restart();
		timeCheck = true;
	}

	if(titleClock.getElapsedTime()>sf::seconds(1.f))
	{
		timeCheck = false;
		title->SetActive(true);
	}
	else if (titleClock.getElapsedTime() > sf::seconds(0.5f))
	{
		title->SetActive(false);
	}

	animation1.Update(dt);
	animation2.Update(dt);
	animation3.Update(dt);
	animation4.Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneTitle::ChangeScene()
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
}
