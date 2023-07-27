#include "stdafx.h"
#include "Utils.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Framework.h"
#include "RectangleGo.h"
#include "UIButton.h"
#include "TileMap.h"
#include "TextGo.h"
#include <sstream>;

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init() // �ȹٲ�Ÿ� ����
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y / 2 };
	tileMap = (TileMap*)AddGo(new TileMap("graphics/Resource.png", "Tile Map"));
	tileMap->Load("map/mapData.csv");
	tileMap->SetOrigin(Origins::TL);
	tileMap->sortLayer = -1;
	tileMap->SetPosition(0, 0);
	
	player = (Player*)AddGo(new Player("player",""));
	player->SetSceneGame(this);
	player->sortLayer = 1;
	player->sprite.setScale(1.f, 1.f);
	
	groundBounds = tileMap->vertexArray.getBounds();
	groundBounds.width -= (tileMap->TileSize().x * 2.f);
	groundBounds.height -= (tileMap->TileSize().y * 2.f);
	groundBounds.left += (tileMap->TileSize().x);
	groundBounds.top += (tileMap->TileSize().y);
	player->SetWallBounds(groundBounds);
	
	RectangleGo* rect = (RectangleGo*)AddGo(new RectangleGo(rectSize,"FadeOut"));
	scoreBoard = (RectangleGo*)AddGo(new RectangleGo(boardSize, "ScoreBoard"));

	for (auto go : gameObjects)
	{
		go->Init();
	}

}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter() //���͸� ������ �ٲ�°� ����
{

	auto size = FRAMEWORK.GetWindowSize();
	
	meetPokemon = false;
	ingameSound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sounds/Ingame.wav"));
	ingameSound.setLoop(true);
	ingameSound.play();
	ingameSound.setVolume(50);
	
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	
	if (playerPos == sf::Vector2f{0, 0})
	{
		player->SetPosition({ 18.5 * 150, 39.5 * 150 });
	}
	RectangleGo* rect = (RectangleGo*)FindGo("FadeOut");
	rect->SetPosition(uiView.getSize());
	rect->SetOrigin(Origins::MC);
	rect->rectangle.setScale(rectSize);
	rect->rectangle.setFillColor(sf::Color::Transparent);
	sceneClock.restart();
	battleNow = false;
	randomNum = 0;

	end = sf::Color::Black;
	start1 = { 255, 255, 255, 100 };
	
	Scene::Enter();

}

void SceneGame::Exit()
{
	ingameSound.stop();
	playerPos = player->GetPosition();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	
	CheckCollide(dt);

	worldView.setCenter(player->GetPosition());
	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneId::Battle);
	}*/
	tileMap = (TileMap*)FindGo("Tile Map");
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::CheckCollide(float dt)
 {

	tileMap = (TileMap*)FindGo("Tile Map");
	//�÷��̾� �����ǿ� �ش��ϴ� Ÿ�� ã�� !!!!!!!!!!!
	sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / 150.f);// �÷��̾ ���� Ÿ���� �ε���
	
	int tileSize = tileMap->tiles.size();
	for (int i = 0; i < tileSize; i++)
	{
			
		if (tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y)
		{
			int texIndex = static_cast<int>(tileMap->tiles[i].texIndex);
			
			if (texIndex == static_cast<int>(TileInformation::GrassHigh)||
				texIndex == static_cast<int>(TileInformation::GrassLow))
			{
				if (appearTime < sceneClock.getElapsedTime()&&!checkMonster)
				{
					randomNum = Utils::RandomRange(1, 100);
					sceneClock.restart();
					std::cout << randomNum << std::endl;
					checkMonster = true;
				}
				else if(!battleNow)
				{
					checkMonster = false;
				}
				if (!battleNow&&randomNum>=80)
				{
					if (!player->GetPlayerMove())
					{
						player->ChangePlayerMove();
					}
					clock.restart();
					battleNow = true;
				}
				if(battleNow)
				{
					BattleStart(dt);
				}
				if (!battleNow) {
					if (player->GetPlayerMove())
					{
						player->ChangePlayerMove();
					}
				}
			}
		}
	}
}

void SceneGame::BattleStart(float dt)
{

	if (sceneChangeTime < clock.getElapsedTime())
		SCENE_MGR.ChangeScene(SceneId::Battle);

}

