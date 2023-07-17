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
	
	/*resources.push_back(std::make_tuple(ResourceTypes::Texture,"graphics/sprite_sheet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/RubySheet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/button.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/clickButton.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/park.png"));*/
}

void SceneGame::Init() // 안바뀔거면 여기
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
	std::cout << groundBounds.height <<","<<
		groundBounds.left << "," <<
		groundBounds.top << "," <<
		groundBounds.width << std::endl;
	player->SetWallBounds(groundBounds);

	//gpt
	RectangleGo* rect = (RectangleGo*)AddGo(new RectangleGo(rectSize,"FadeOut"));
	transitionInProgress = false;
	transitionSpeed = 50.0f;
	//rect.setSize(sf::Vector2f(1.0f, 1.0f));
	rect->rectangle.setFillColor(sf::Color::Black);
	rect->SetOrigin(Origins::TL);
	rect->SetPosition(sf::Vector2f(0.0f, 0.0f));
	elapsedTime = sf::Time::Zero;







	/*objectBounds = tileMap->vertexArray.getBounds();
	objectBounds.width -= (tileMap->TileXSize() + 75.f);
	objectBounds.height -= (tileMap->TileXSize() + 75.f);
	groundBounds.left += (tileMap->TileXSize() + 75.f);
	groundBounds.top += (tileMap->TileXSize() + 75.f);
	player->ObjBounds(objectBounds);*/
	
	//버튼
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
	
	//배경이미지 생성 test
	/*SpriteGo* BG = (SpriteGo*)AddGo(new SpriteGo("graphics/Park.png","Park"));
	BG->sprite.setScale(10.f, 10.f);
	BG->sortLayer = 0;
	BG->SetOrigin(Origins::MC);
	BG->SetPosition(0, 0);*/
	
	//포켓몬 생성해보기
	/*SpriteGo* subject = (SpriteGo*)AddGo(new SpriteGo("graphics/chikorita.png", "Subject"));
	subject->sprite.setPosition(-30, -30);
	subject->SetOrigin(Origins::TR);
	subject->sprite.setScale(1.0f, 1.0f);
	subject->sprite.setFillColor(sf::Color::Magenta);*/
	
	//사각형 생성
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

void SceneGame::Enter() //엔터를 누르면 바뀌는건 여기
{
	auto size = FRAMEWORK.GetWindowSize();
	//auto centerPos = size / 2.f;
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	elapsedTime = clock.restart();
	Scene::Enter();
	/*SpriteGo* subject = (SpriteGo*)FindGo("Subject");
	subject->SetPosition(player->GetPosition().x - 180.f, player->GetPosition().y - 180.f);*/
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	
	//test
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	// test


	



	//tileMap = (TileMap*)FindGo("Tile Map");
	//sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / 40.f); // 플레이어가 속한 타일의 인덱스
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

	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


void SceneGame::CheckCollide(float dt)
 {

	 //플레이어 포지션에 해당하는 타일 찾기 !!!!!!!!!!!
	tileMap = (TileMap*)FindGo("Tile Map");
	sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / 150.f);// 플레이어가 속한 타일의 인덱스
	//std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
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
					//std::cout << "여긴 바닥이 아니야" << std::endl;
					if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
					{
						std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;
						(int)tileMap->tiles[i].texIndex;
					}

					if (player->GetDirection().x < 0)
						player->SetPosition(playerTileIndex.x * 150.f + 150.f, player->GetPosition().y);
					if (player->GetDirection().x > 0)
						player->SetPosition(playerTileIndex.x * 150.f, player->GetPosition().y);
					if (player->GetDirection().y < 0)
						player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150 + 150);
					if (player->GetDirection().y > 0)
						player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150);
					std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;


				}

				if (texIndex == static_cast<int>(TileInformation::GrassHigh)||
					texIndex == static_cast<int>(TileInformation::GrassLow))
				{
					int randomNum = Utils::RandomRange(1, 10000);
					if (randomNum>=99)
					{
						std::cout << "배틀을 시작하지" << std::endl;
						BattleStart(dt);

					}
				}
				
				/*if ((tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y) != 30)
				{*/
				//}
				
			}
		}
	}
	 //해당하는 타일의 텍스인덱스가 4가 아니면 충돌처리
}

void SceneGame::BattleStart(float dt)
{
	RectangleGo* rect = (RectangleGo*)FindGo("FadeOut");
	if (transitionInProgress)
	{
		// 사각형 크기 변경
		float targetWidth = static_cast<float>(window.getSize().x);
		float targetHeight = static_cast<float>(window.getSize().y);
		float newWidth = rect->rectangle.getSize().x + transitionSpeed * dt;
		float newHeight =rect->rectangle.getSize().y + transitionSpeed * dt;
		rect->rectangle.setSize(sf::Vector2f(newWidth, newHeight));

		// 가운데로 이동
		float offsetX = (targetWidth - newWidth) / 2.0f;
		float offsetY = (targetHeight - newHeight) / 2.0f;
		rect->rectangle.setPosition(offsetX, offsetY);

		// 전환 완료 처리
		if (newWidth >= targetWidth && newHeight >= targetHeight)
		{
			transitionInProgress = false;
			// 다음 씬으로 전환
			SCENE_MGR.ChangeScene(SceneId::Battle);
		}
	}

	//SCENE_MGR.ChangeScene(SceneId::Battle);
}
