#include "stdafx.h"
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

void SceneGame::Init() // �ȹٲ�Ÿ� ����
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y/2 };

	player = (Player*)AddGo(new Player());
	player->sortLayer = 1;
	player->sprite.setScale(1.f, 1.f);
	
	
	
	
	
	
	
	
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
	tileMap = (TileMap*)AddGo(new TileMap("graphics/Resource.png", "Tile Map"));

	for (auto go : gameObjects)
	{
		go->Init();
	}

	tileMap->Load("map/mapData.csv");
	tileMap->SetOrigin(Origins::MC);
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

	worldView.setCenter(player->GetPosition());
	//���밡����.
	tileMap = (TileMap*)FindGo("Tile Map");
	sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / tileMap->TileSize()); // �÷��̾ ���� Ÿ���� �ε���
	int a= tileMap->tiles.size();
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return))
	{
		std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
		std::cout << a << std::endl;
	}
	
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


//void SceneGame::CheckCollide()
/* {
	// �÷��̾� �����ǿ� �ش��ϴ� Ÿ�� ã�� !!!!!!!!!!!
	sf::Vector2i playerTileIndex = (sf::Vector2i)(player->GetPosition() / 30.f); // �÷��̾ ���� Ÿ���� �ε���
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return))
		std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	int tileSize = tileMap->tiles.size();
	for (int i = 0; i < tileSize; i++)
	{
		if (tileMap->tiles[i].texIndex == 4)
		{
			continue;
		}
		if (tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y) // �ε����� ������
		{
			player->SetSpeed(0.f);
			break;
		}
	}
	// �ش��ϴ� Ÿ���� �ؽ��ε����� 4�� �ƴϸ� �浹ó��
}*/