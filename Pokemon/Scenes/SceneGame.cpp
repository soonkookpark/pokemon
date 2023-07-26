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

void SceneGame::Init() // 안바뀔거면 여기
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y / 2 };
	tileMap = (TileMap*)AddGo(new TileMap("graphics/Resource.png", "Tile Map"));
	tileMap->Load("map/mapData.csv");
	tileMap->SetOrigin(Origins::TL);
	tileMap->sortLayer = -1;
	//tileMap->SetOrigin(Origins::MC);
	tileMap->SetPosition(0, 0);
	
	player = (Player*)AddGo(new Player("player",""));
	//player->SetPosition({ 18.5 * 150, 39.5 * 150 });
	player->SetSceneGame(this);
	player->sortLayer = 1;
	player->sprite.setScale(1.f, 1.f);
	
	
	/*scoreText= (TextGo*)AddGo(new TextGo("Score", "fonts/GANGWONSTATE.ttf"));
	lifeText = (TextGo*)AddGo(new TextGo("Life", "fonts/GANGWONSTATE.ttf"));*/
	
	


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

	/*sf::VertexArray& vertexArray = tileMap->GetVertexArray();
	std::cout <<tile*/
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter() //엔터를 누르면 바뀌는건 여기
{

	auto size = FRAMEWORK.GetWindowSize();
	
	meetPokemon = false;
	ingameSound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sounds/Ingame.wav"));
	ingameSound.setLoop(true);
	ingameSound.play();
	ingameSound.setVolume(50);
	
	//auto centerPos = size / 2.f;
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	/*if (playerPos != sf::Vector2f{18.5 * 150, 39.5 * 150})
	{
		player->SetPosition(playerPos);
	}*/
	/*scoreBoard->rectangle.setFillColor(sf::Color::Magenta);
	scoreBoard->sortLayer = 211;
	scoreBoard->SetPosition(0, 0);*/

	/*std::stringstream ss;
	ss << "score: " << score;
	std::stringstream ss1;
	ss1 << "Life: " << life;
	scoreText->text.setCharacterSize(30);
	scoreText->text.setString(ss.str());
	scoreText->SetOrigin(Origins::TL);
	scoreText->text.setPosition(10, 10);
	scoreText->sortLayer = 212;

	lifeText->text.setCharacterSize(30);
	lifeText->text.setString(ss1.str());
	lifeText->SetOrigin(Origins::TL);
	lifeText->text.setPosition(10, 50);
	lifeText->sortLayer = 212;*/


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
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneId::Battle);
	}
	tileMap = (TileMap*)FindGo("Tile Map");
	//int randomNum = Utils::RandomRange(1, 100);
	//sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / 150.f);// 플레이어가 속한 타일의 인덱스
	//int tileSize = tileMap->tiles.size();
	/*for (int i = 0; i < tileSize; i++)
	{
		if (tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y)
		{
			int texIndex = static_cast<int>(tileMap->tiles[i].texIndex);
			if (randomNum < 10 && (static_cast<int>(TileInformation::GrassHigh) ||
				static_cast<int>(TileInformation::GrassHigh)))
			{
				BattleStart();
			}
		}
	}*/

	/*std::stringstream ss;
	ss << "score: " << score;
	std::stringstream ss1;
	ss1 << "Life: " << life;*/
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::CheckCollide(float dt)
 {

	tileMap = (TileMap*)FindGo("Tile Map");
	//플레이어 포지션에 해당하는 타일 찾기 !!!!!!!!!!!
	sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / 150.f);// 플레이어가 속한 타일의 인덱스
	//std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	
	//std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	int tileSize = tileMap->tiles.size();
	for (int i = 0; i < tileSize; i++)
	{
			
		if (tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y)
		{
			int texIndex = static_cast<int>(tileMap->tiles[i].texIndex);
			//if (texIndex != static_cast<int>(TileInformation::Grass) &&
			//	texIndex != static_cast<int>(TileInformation::GrassFlowerHalf) &&
			//	texIndex != static_cast<int>(TileInformation::GrassHigh) &&
			//	texIndex != static_cast<int>(TileInformation::GrassLow) &&
			//	texIndex != static_cast<int>(TileInformation::Floor) &&
			//	texIndex != static_cast<int>(TileInformation::Carpet))
			//{
			//	//std::cout << "여긴 바닥이 아니야" << std::endl;
			//	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
			//	{
			//		std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;
			//		(int)tileMap->tiles[i].texIndex;
			//		player->ChangePlayerMove(); 
			//		battleNow = false;
			//	}

				//if (player->GetDirection().x < 0)
				//	player->SetPosition(playerTileIndex.x * 150.f/* + 150.f*/, player->GetPosition().y);
				//if (player->GetDirection().x > 0)
				//	player->SetPosition(playerTileIndex.x * 150.f, player->GetPosition().y);
				//if (player->GetDirection().y < 0)
				//	player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150 /*+ 150*/);
				//if (player->GetDirection().y > 0)
				//	player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150);
				//std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;


			//}

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
					std::cout << "배틀을 시작하지" << std::endl;
					clock.restart();
					battleNow = true;

					std::cout << "이걸 했다." << std::endl;
					//sceneClock.restart();
				}
				if(battleNow/*&&battleWaitTime < sceneClock.getElapsedTime()*/)
				{
					BattleStart(dt);
					/*if (player->GetPlayerMove())
					{
						player->ChangePlayerMove();
					} */
					std::cout << "0여기 왔다." << std::endl;
					//battleNow = false;
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
	if (duration <= 0.f)
	{
		duration = 2.f;
	}
	/*if (dt > 1.5f)
	{
		dt = 0.f;
	}*/
	
		SceneChange(dt);
	

	if (sceneChangeTime < clock.getElapsedTime())
		SCENE_MGR.ChangeScene(SceneId::Battle);

}

void SceneGame::SceneChange(float dt)
{
	timer += dt;

	RectangleGo* rect = (RectangleGo*)FindGo("FadeOut");
	rect->SetPosition(uiView.getSize());
	rect->SetOrigin(Origins::MC);
	rect->rectangle.setScale(rectSize);
	sf::Color end = sf::Color::Black;
	
	sf::Color start1 = { 255, 255, 255, 0 }; //{ 255,255,255,0 };

	sf::Color color1 = Utils::Lerp(end, start1, duration - timer);//duration - timer<0 투명화

	rect->rectangle.setFillColor(sf::Color::Color(color1));

}

void SceneGame::ShowInfo()
{
}
