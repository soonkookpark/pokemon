#pragma once
#include "Scene.h"
#include "Framework.h"
#include "AnimationController.h"
#include "ObjectPool.h"
#include "StringTable.h"
#include "DataTableMgr.h"

class RectangleGo;
class SpriteGo;
class TextGo;
class Monster;
class MonsterBallEffectGo;
class Player;
class SceneBattle : public Scene
{
protected:
	AnimationController animation1;//내 몬스터가 튀어나오는 이펙트
	AnimationController animation2;//몬스터볼 흔들리는 이펙트
	AnimationController animation3;//상대 몬스터볼 이펙트
	AnimationController animation4;//
	AnimationController animation5;//


	sf::Sound battleSound;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::RectangleShape rect;
	int enemySize = 56;
	int userSize = 48; //유저 사람 이미지
	int userMosterSize = 48; // 유저 포켓몬 이미지
	int bounceCount = 0;
	int shakeCount = 0;
	float enemyHpRate = 100;
	int myHpRate = 100;
	int mySpeed = 120;
	int enemyAttack;
	
	int menuIndex = 0;
	int skillIndex = 0;
	int myDamage = 150;
	int mySkillDamage1;
	int mySkillDamage2;
	int mySkillDamage3;
	int mySkillDamage4;
	int randomNum = 0; //= Utils::RandomRange(1, 100);
	int iNum = 0;
	int jNum = 0;
	int enemyDamage = 0;
	int score = 0;
	int playerLife = 0;

	float timer = 0;
	float myHp=198;
	float myNowHp;
	float enemyHp=100.f;
	float enemyNowHp;
	float ballSpeed=0;
	const float gravity = 9.81f;
	const float ballGravity = 3.f;
	const float throwAngle = 45.f;
	
	//float enemyHpy = 100.f;
	bool listMove = false;
	bool userMove = false;
	bool aniPlay = false;
	bool menuDisplay = false;
	bool trigger1 = false;
	bool trigger2 = false;
	bool gameEnd = false;
	bool throwBall = false;
	bool catchEffect = false;
	bool catchBoomEffect = false;
	bool ballUp = false;
	bool ballEffectEnd = false;
	bool ballCountCheck = false;
	bool shakeEffect = false;
	bool catchTextPrint = false;
	bool damageCheck = false;
	bool catchFailEffectbool = false;
	bool catchCheck = false;
	bool ImAlive = false;
	bool enemyAlive = false;
	bool skillSelectCheck = false;
	bool enemyTurn = false;
	bool myTurn = false;
	bool enemyDamageCheck = false;
	bool enemySkillExplainFinish = false;
	bool enemyAttackend = false;

	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;
	sf::Clock ballClock;
	sf::Clock ballTopClock;
	sf::Clock ballShakeClock;
	sf::Clock catchTextClock;
	sf::Clock failClock;
	sf::Time interfaceTime = sf::seconds(3.f);
	sf::Vector2f healthBar = { 3.54f*100,25.f  };
	sf::Vector2f myHealthBar = { 3.54f * 100,25.f };
	sf::Vector2f effectSize = { 50.f,50.f };
	sf::Vector2f textFirstPos = { 896, 680.f };
	sf::Vector2f selectFirstPos = { 820.f,688.f };
	sf::Vector2f ballStartPos;
	sf::Vector2f ballEndPos;
	sf::Vector2f ballNowPos;
	sf::Vector2f ballTopPos;
	sf::Vector2f ballPos;
	sf::Vector2f ballVelocity;
	sf::Vector2f fakeBoxScale = { 1235.f,490.f };
	sf::Vector2f fakeBoxPos = { 685.f,590.f };
	sf::Vector2f myPokemonRect;


	RectangleGo* recgo = nullptr;
	RectangleGo* pokemonHealth = nullptr;
	RectangleGo* fakeBox = nullptr;
	RectangleGo* myPokemonHealth = nullptr;
	
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
	TextGo* enemyName = nullptr;//상대 체력바 위에 표시되는 상대 포켓몬 이름
	TextGo* catchMessage1 = nullptr;
	TextGo* catchMessage2 = nullptr;
	TextGo* catchPokemonName = nullptr;//텍스트박스에서 표시되는 상대 포켓몬이름
	TextGo* myPokemonName = nullptr;
	

	//SpriteGo* list = nullptr;
	SpriteGo* mymonster = nullptr;
	SpriteGo* user = nullptr;
	SpriteGo* HpBar = nullptr;
	SpriteGo* realHpBar = nullptr;
	SpriteGo* myHpBar = nullptr;
	SpriteGo* myRealHpBar = nullptr;
	SpriteGo* selectIcon = nullptr;
	SpriteGo* menu = nullptr;
	SpriteGo* explainMenu = nullptr;
	SpriteGo* effectBall = nullptr;
	SpriteGo* shakeBall = nullptr;
	SpriteGo* effectEnemyBall = nullptr;
	SpriteGo* catchMonsterBall = nullptr;
	SpriteGo* catchFailEffect = nullptr;
	SpriteGo* ballTop = nullptr;
	SpriteGo* ballBottom = nullptr;
	SpriteGo* ball = nullptr;//몬스터볼에 몬스터가 들어왔을때의 볼
	SpriteGo* successBall = nullptr;
	SpriteGo* catchTextMenu = nullptr;
	SpriteGo* enemyExplainMenu = nullptr;

	std::wstring useskill;
	std::wstring useskill1;
	std::wstring useskill2;
	std::wstring useskill3;
	std::wstring useskill4;
	std::wstring myName;
	std::wstring enemySkill;
	ObjectPool<Monster> PokemonPool;
	Monster* monster;

	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
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
	void SelectMenu(float dt);
	void MenuText();
	void SkillSelect();
	void SkillExplain(int n);
	void EnemySkillExplain(int n);
	
	//void Bag();
	void BattleEnd();
	void MeetMonster();
	void CatchPokemon(float dt);
	void CatchSuccess();
	void CatchFail(float dt);
	/*float MoveUpBallTop(float dt);
	float MoveDownBallTop(float dt);*/
	void GoBackMenu();
	void CatchText();
	void CatchSuccessText();
	void CatchFailedText(float dt);
	void EnemyMonsterHp(float dt);
	void MyMonsterHp(float dt);
	void ChangeMyPokemon();
	void ChangeMyPokemonSkill();
	void BattleTurnDecision(float dt);
	void BattleLose();
	// 상대 스킬 선택
	sf::Vector2f CalculateOrbit(const sf::Vector2f& startPos, const sf::Vector2f& highPos, const sf::Vector2f& endPos,float moveT);
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
