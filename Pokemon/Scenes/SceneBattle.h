#pragma once
#include "Scene.h"
#include "Framework.h"
#include "AnimationController.h"
#include "ObjectPool.h"

class RectangleGo;
class SpriteGo;
class TextGo;
class Monster;
class SceneBattle : public Scene
{
protected:
	AnimationController animation;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::RectangleShape rect;
	int enemySize = 56;
	int userSize = 48; //유저 사람 이미지
	int userMosterSize = 48; // 유저 포켓몬 이미지
	int timer = 0;
	float myHp=100;
	float enemyHp=100.f;
	//
	//float enemyHpy = 100.f;
	bool listMove = false;
	bool userMove = false;
	bool aniPlay = false;
	bool menuDisplay = false;
	bool trigger1 = false;
	bool trigger2 = false;
	bool gameEnd = false;
	sf::Clock clock;
	sf::Clock clock2;
	sf::Time interfaceTime = sf::seconds(3.f);
	sf::Vector2f healthBar = { 3.54f*100,25.f  };
	sf::Vector2f effectSize = { 50.f,50.f };
	sf::Vector2f textFirstPos = { 896, 680.f };
	sf::Vector2f selectFirstPos = { 820.f,688.f };
	int menuIndex = 0;
	int skillIndex = 0;
	float damage = 150.f;
	int randomNum = 0; //= Utils::RandomRange(1, 100);
	int iNum = 0;
	int jNum = 0;
	sf::Vector2f fakeBoxScale = { 1235.f,490.f };
	sf::Vector2f fakeBoxPos = { 685.f,590.f };

	RectangleGo* recgo = nullptr;
	RectangleGo* pokemonHealth = nullptr;
	RectangleGo* fakeBox = nullptr;

	
	TextGo* menuText1 = nullptr;
	TextGo* menuText2 = nullptr;
	TextGo* menuText3 = nullptr;
	TextGo* menuText4 = nullptr;
	TextGo* skillMessage1 = nullptr;
	TextGo* skillMessage2 = nullptr;
	TextGo* skillMessage3 = nullptr;
	TextGo* skillMessage4 = nullptr;
	TextGo* skillExplain = nullptr;
	TextGo* skillText = nullptr;


	SpriteGo* list = nullptr;
	SpriteGo* mymonster = nullptr;
	SpriteGo* user = nullptr;
	SpriteGo* HpBar = nullptr;
	SpriteGo* realHpBar = nullptr;
	SpriteGo* selectIcon = nullptr;
	SpriteGo* menu = nullptr;
	SpriteGo* explainMenu = nullptr;
	SpriteGo* effectBall = nullptr;

	ObjectPool<Monster> PokemonPool;
public:

	SceneBattle();
	virtual ~SceneBattle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	template <typename T>
	void ClearObjectPool(ObjectPool<T>& pool);

	void Battle(float dt);
	//void PlayerMenu();
	void MoveCursorMenu();
	void MoveCursorSkill();
	void SetSkill();
	void SelectMenu();
	void MenuText();
	void SkillSelect();
	void SkillExplain(int n);
	
	//void Bag();
	void BattleEnd();
};

template<typename T>
inline void SceneBattle::ClearObjectPool(ObjectPool<T>& pool)
{
	for (auto obj : pool.GetUseList())
	{
		RemoveGo(obj);
	}
	pool.Clear();
}
