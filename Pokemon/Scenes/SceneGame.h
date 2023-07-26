#pragma once
#include "Scene.h"
#include "Framework.h"
class Player;
class TileMap;
class RectangleGo;
class TextGo;
class SceneGame : public Scene
{
protected:
	sf::FloatRect groundBounds;
	sf::FloatRect objectBounds;
	Player* player;
	
	bool battleNow = false;
	bool meetPokemon = false;
	float moveSpeed = 0.f;
	TileMap* tileMap = nullptr;

	//--------------------
	float transitionSpeed = 100.f; // 화면 전환 속도 (픽셀 단위)

	sf::Clock clock; // 효과 시간 ,전투준비시잔
	sf::Clock sceneClock; // 신전환 타임
	sf::Time battleWaitTime = sf::seconds(3.f);//전투 준비 시간
	sf::Time sceneChangeTime = sf::seconds(2.f);//신전환 시간.
	sf::Time magnitudeTime = sf::seconds(0.2f);
	sf::Time appearTime = sf::seconds(2.f);

	sf::Sound ingameSound;

	bool transitionInProgress = false;
	sf::Vector2f rectSize = { FRAMEWORK.GetWindowSize().x,FRAMEWORK.GetWindowSize().y };
	int playerWidth = FRAMEWORK.GetWindowSize().x;
	int playerHeight = FRAMEWORK.GetWindowSize().y;
	int rectSnailSize = 10;
	sf::Vector2f textPos = uiView.getSize();
	sf::Vector2f boardSize = { 200,100 };
	int timer = 0.f;
	float duration = 5.f;
	float fadeOut = 2.f;
	bool magnitudeScene = false;
	int randomNum; //랜덤넘버
	int score = 0;
	int life = 0;
	bool checkMonster = false;
	sf::Vector2f playerPos;
	RectangleGo* scoreBoard;

	TextGo* scoreText;
	TextGo* lifeText;
	std::string scoreMessage;
	std::string lifeMessage;
public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void CheckCollide(float dt);
	void BattleStart(float dt);
	void SceneChange(float dt);
	void ShowInfo();
	
};

