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
	
	player = (Player*)AddGo(new Player());
	player->SetSceneGame(this);
	player->sortLayer = 1;
	player->sprite.setScale(1.f, 1.f);
	groundBounds = tileMap->vertexArray.getBounds();
	groundBounds.width -= (tileMap->TileSize().x * 2.f-150.f);
	groundBounds.height -= (tileMap->TileSize().y * 2.f-150.f);
	groundBounds.left += (tileMap->TileSize().x-75.f);
	groundBounds.top += (tileMap->TileSize().y-75.f);
	player->SetWallBounds(groundBounds);
	
	
	/*std::cout << groundBounds.height <<","<<
		groundBounds.left << "," <<
		groundBounds.top << "," <<
		groundBounds.width << std::endl;*/
	
	//gpt
	RectangleGo* rect = (RectangleGo*)AddGo(new RectangleGo(rectSize,"FadeOut"));

	
	/*rect->rectangle.setFillColor(sf::Color::Black);
	rect->SetOrigin(Origins::TL);*/
	//rect->SetPosition(sf::Vector2f(0.0f, 0.0f));
	//rect->rectangle.setSize({ 10.f, 10.f });
	//elapsedTime = sf::Time::Zero;
	/*objectBounds = tileMap->vertexArray.getBounds();
	objectBounds.width -= (tileMap->TileXSize() + 75.f);
	objectBounds.height -= (tileMap->TileXSize() + 75.f);
	groundBounds.left += (tileMap->TileXSize() + 75.f);
	groundBounds.top += (tileMap->TileXSize() + 75.f);
	player->ObjBounds(objectBounds);*/
	
	//��ư
	/*UIButton* button = (UIButton*)AddGo(new UIButton("graphics/button.png"));
	button->SetOrigin(Origins::TR);
	button->sortLayer = 100;
	button->SetPosition(windowSize.x,0.f);

	button->OnEnter = [button]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/clickButton.png");
		button->sprite.setTexture(*tex);
		std::cout << "Enter" << std::endl;
	};
	button->OnExit = [button]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture(button->textureId);
		button->sprite.setTexture(*tex);
		std::cout << "Exit" << std::endl;
	};
	button->OnClick = []() {
		std::cout << "Click" << std::endl;
	};*/
	
	//����̹��� ���� test
	/*SpriteGo* BG = (SpriteGo*)AddGo(new SpriteGo("graphics/Park.png","Park"));
	BG->sprite.setScale(10.f, 10.f);
	BG->sortLayer = 0;
	BG->SetOrigin(Origins::MC);
	BG->SetPosition(0, 0);*/
	
	//���ϸ� �����غ���
	/*SpriteGo* subject = (SpriteGo*)AddGo(new SpriteGo("graphics/chikorita.png", "Subject"));
	subject->sprite.setPosition(-30, -30);
	subject->SetOrigin(Origins::TR);
	subject->sprite.setScale(1.0f, 1.0f);
	subject->sprite.setFillColor(sf::Color::Magenta);*/
	
	//�簢�� ����
	/*RectangleGo* ground = (RectangleGo*)AddGo(new RectangleGo(groundSize, "Ground"));
	ground->SetPosition(0, 0);
	ground->rectangle.setFillColor(sf::Color::Cyan);
	ground->SetOrigin(Origins::TC);
	groundBounds = ground->rectangle.getGlobalBounds();//
	groundBounds.height -= groundSize.y;*/

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

void SceneGame::Enter() //���͸� ������ �ٲ�°� ����
{
	auto size = FRAMEWORK.GetWindowSize();
	//auto centerPos = size / 2.f;
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	/*if (playerPos != sf::Vector2f{18.5 * 150, 39.5 * 150})
	{
		player->SetPosition(playerPos);
	}*/
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
	/*SpriteGo* subject = (SpriteGo*)FindGo("Subject");
	subject->SetPosition(player->GetPosition().x - 180.f, player->GetPosition().y - 180.f);*/
}

void SceneGame::Exit()
{

	playerPos = player->GetPosition();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	
	//test
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	// test


	



	//tileMap = (TileMap*)FindGo("Tile Map");
	//sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / 40.f); // �÷��̾ ���� Ÿ���� �ε���
	//int a= tileMap->tiles.size();
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return))

	/*std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	std::cout << a << std::endl;*/
	CheckCollide(dt);

	worldView.setCenter(player->GetPosition());
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneId::Battle);
	}
	tileMap = (TileMap*)FindGo("Tile Map");
	//int randomNum = Utils::RandomRange(1, 100);
	//sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / 150.f);// �÷��̾ ���� Ÿ���� �ε���
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
	//std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	
	//std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	int tileSize = tileMap->tiles.size();
	for (int i = 0; i < tileSize; i++)
	{
			
		if (tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y)
		{
			int texIndex = static_cast<int>(tileMap->tiles[i].texIndex);
			if (texIndex != static_cast<int>(TileInformation::Grass) &&
				texIndex != static_cast<int>(TileInformation::GrassFlowerHalf) &&
				texIndex != static_cast<int>(TileInformation::GrassHigh) &&
				texIndex != static_cast<int>(TileInformation::GrassLow) &&
				texIndex != static_cast<int>(TileInformation::Floor) &&
				texIndex != static_cast<int>(TileInformation::Carpet))
			{
				//std::cout << "���� �ٴ��� �ƴϾ�" << std::endl;
				if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
				{
					std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;
					(int)tileMap->tiles[i].texIndex;
					player->ChangePlayerMove(); 
					battleNow = false;
				}

				if (player->GetDirection().x < 0)
					player->SetPosition(playerTileIndex.x * 150.f/* + 150.f*/, player->GetPosition().y);
				if (player->GetDirection().x > 0)
					player->SetPosition(playerTileIndex.x * 150.f, player->GetPosition().y);
				if (player->GetDirection().y < 0)
					player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150 /*+ 150*/);
				if (player->GetDirection().y > 0)
					player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150);
				std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;


			}

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
					std::cout << "��Ʋ�� ��������" << std::endl;
					clock.restart();
					battleNow = true;

					std::cout << "�̰� �ߴ�." << std::endl;
					//sceneClock.restart();
				}
				if(battleNow/*&&battleWaitTime < sceneClock.getElapsedTime()*/)
				{
					BattleStart(dt);
					/*if (player->GetPlayerMove())
					{
						player->ChangePlayerMove();
					} */
					std::cout << "0���� �Դ�." << std::endl;
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
	sf::Color end = sf::Color::White;
	//sf::Color start2 = sf::Color::Black;
	sf::Color start1 = sf::Color::Black;//{ 255,255,255,0 };

	sf::Color color1 = Utils::Lerp(end, start1, duration - timer);//duration - timer<0 ����ȭ

	rect->rectangle.setFillColor(sf::Color::Color(color1));
	
	//transparency = true;

}
