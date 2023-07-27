#include "stdafx.h"
#include "SceneBattle.h"
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
#include "Monster.h"
#include "Player.h"

SceneBattle::SceneBattle() : Scene(SceneId::Battle)
{
	resourceListPath = "scripts/SceneBattleResourceList.csv";
}

void SceneBattle::Init()
{
	Release();
	
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);
	recgo = (RectangleGo*)AddGo(new RectangleGo(windowSize, "square"));
	pokemonHealth = (RectangleGo*)AddGo(new RectangleGo(healthBar, "healthBar"));
	myPokemonHealth = (RectangleGo*)AddGo(new RectangleGo(myHealthBar, "healthBar"));
	
	mymonster = (SpriteGo*)AddGo(new SpriteGo("graphics/PokemonList.png", "myMonster"));
	user =(SpriteGo*)AddGo(new SpriteGo("graphics/User.png", "User"));
	HpBar= (SpriteGo*)AddGo(new SpriteGo("graphics/HpBar.png", "HpBar"));
	realHpBar = (SpriteGo*)AddGo(new SpriteGo("graphics/RealHpBar.png", "RealHpBar"));
	myHpBar = (SpriteGo*)AddGo(new SpriteGo("graphics/HpBar.png", "MyHpBar"));
	myRealHpBar = (SpriteGo*)AddGo(new SpriteGo("graphics/RealHpBar.png", "MyRealHpBar"));

	selectIcon = (SpriteGo*)AddGo(new SpriteGo("graphics/selectIcon.png", "Select"));
	menu = (SpriteGo*)AddGo(new SpriteGo("graphics/menuBox.png", "Menu"));
	explainMenu = (SpriteGo*)AddGo(new SpriteGo("graphics/menuBox.png", "ExplainMenu"));
	catchTextMenu = (SpriteGo*)AddGo(new SpriteGo("graphics/menuBox.png", "CatchTextMenu"));

	//몬스터볼 위아래 이미지
	ballTop = (SpriteGo*)AddGo(new SpriteGo("graphics/ThrowBallEffectMove.png", "BallTop"));
	ballBottom = (SpriteGo*)AddGo(new SpriteGo("graphics/ThrowBallEffectMove.png", "BallBottom"));
	ball = (SpriteGo*)AddGo(new SpriteGo("graphics/ThrowBallEffectMove.png", "Ball"));
	successBall = (SpriteGo*)AddGo(new SpriteGo("graphics/ThrowBallEffectMove.png", "SuccessBall"));
	//몬스터볼 연출 효과
	effectBall = (SpriteGo*)AddGo(new SpriteGo("","MonsterBallEffect"));
	shakeBall = (SpriteGo*)AddGo(new SpriteGo("", "ShakeBallEffect"));
	effectEnemyBall = (SpriteGo*)AddGo(new SpriteGo("", "MonsterBallEffect"));
	catchMonsterBall = (SpriteGo*)AddGo(new SpriteGo("", "ShakeBallEffect"));
	catchFailEffect = (SpriteGo*)AddGo(new SpriteGo("", "CatchFailEffect"));
	
	menuText1 = (TextGo*)AddGo(new TextGo("menuMessage1", "fonts/DOSPilgi.ttf"));
	menuText2 = (TextGo*)AddGo(new TextGo("menuMessage2", "fonts/DOSPilgi.ttf"));
	menuText3 = (TextGo*)AddGo(new TextGo("menuMessage3", "fonts/DOSPilgi.ttf"));
	menuText4 = (TextGo*)AddGo(new TextGo("menuMessage4", "fonts/DOSPilgi.ttf"));
	skillMessage1 = (TextGo*)AddGo(new TextGo("SkillMessage1", "fonts/DOSPilgi.ttf"));
	skillMessage2 = (TextGo*)AddGo(new TextGo("SkillMessage2", "fonts/DOSPilgi.ttf"));
	skillMessage3 = (TextGo*)AddGo(new TextGo("SkillMessage3", "fonts/DOSPilgi.ttf"));
	skillMessage4 = (TextGo*)AddGo(new TextGo("SkillMessage4", "fonts/DOSPilgi.ttf"));
	skillExplain = (TextGo*)AddGo(new TextGo("SkillExplain", "fonts/DOSPilgi.ttf"));
	skillText = (TextGo*)AddGo(new TextGo("SkillText", "fonts/DOSPilgi.ttf"));
	enemyName = (TextGo*)AddGo(new TextGo("EnemyPokemonName", "fonts/GANGWONSTATE.ttf"));
	catchMessage1 = (TextGo*)AddGo(new TextGo("CatchMessage1", "fonts/DOSPilgi.ttf"));
	catchMessage2 = (TextGo*)AddGo(new TextGo("CatchMessage2", "fonts/DOSPilgi.ttf"));
	catchPokemonName = (TextGo*)AddGo(new TextGo("CatchPokemonName", "fonts/DOSPilgi.ttf"));
	myPokemonName = (TextGo*)AddGo(new TextGo("MyPokemonName", "fonts/GANGWONSTATE.ttf"));
	myName = stringTable->GetUni("Pikachu", Languages::KOR);
	myPokemonName->text.setCharacterSize(50);
	myPokemonName->text.setString(myName);
	myPokemonName->text.setFillColor(sf::Color::Black);
	myPokemonName->SetOrigin(Origins::TL);
	myPokemonName->SetPosition(128,745);
	myPokemonName->sortLayer = 207;
	//최초 내 포켓몬
	myPokemonRect = { 12,2 };
	sf::IntRect myMonsterImageRect(9 + (57 * myPokemonRect.x), 140 + (188 * myPokemonRect.y), userMosterSize, userMosterSize);
	mymonster->sprite.setTextureRect(myMonsterImageRect);
	mymonster->sprite.setPosition(180, 428);
	mymonster->SetOrigin(Origins::TL);
	mymonster->sprite.setScale(6.5f, 6.5f);
	mymonster->sortLayer = 204;
	mymonster->SetActive(false);
	myNowHp = myHp;
	
	HpBar->SetOrigin(Origins::TL);
	HpBar->sprite.setScale(1.f, 3.f);
	HpBar->SetPosition(186, 95);
	HpBar->sortLayer = 201;
	HpBar->SetActive(false);
	
	realHpBar->SetOrigin(Origins::TL);
	realHpBar->sprite.setScale(1.2f, 2.f);
	realHpBar->SetPosition(336, 95);
	realHpBar->sortLayer = 202;
	realHpBar->SetActive(false);
	enemyName->SetActive(false);

	useskill1 = stringTable->GetUni("THUNDER", Languages::KOR);
	useskill2 = stringTable->GetUni("SPEED_ATTACK", Languages::KOR);
	useskill3 = stringTable->GetUni("TENMILLIONBOLT", Languages::KOR);
	useskill4 = stringTable->GetUni("IRONTAIL", Languages::KOR);
	
	mySkillDamage1=110;
	mySkillDamage2=60;
	mySkillDamage3=70;
	mySkillDamage4=85;

	fakeBox = (RectangleGo*)AddGo(new RectangleGo(fakeBoxScale, "fakeBox"));
	
	PokemonPool.OnCreate = [this](Monster* pokemon)
	{
		Monster::Pokemons pokemonSetting = (Monster::Pokemons)Utils::RandomRange(0, Monster::TotalMonster);
		pokemon->SetType(pokemonSetting);
		pokemon->textureId = "graphics/PokemonList.png";
		sf::IntRect monsterImageRect(1 + (57 * pokemon->GetImageRectSize().x), 18 + (188 * pokemon->GetImageRectSize().y), enemySize, enemySize);
		pokemon->sprite.setPosition(0, 0);
		pokemon->SetOrigin(Origins::TL);
		pokemon->sprite.setTextureRect(monsterImageRect);
		pokemon->sprite.setScale(6.5f, 6.5f);
		pokemon->sortLayer = 204;
		
	};
	PokemonPool.Init();


	//메뉴 내 사각형 아이콘

	animation1.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MonsterBallEffect.csv"));
	animation2.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/ShakeBallEffect.csv"));
	animation3.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MonsterBallEffect.csv"));
	animation4.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/ShakeBallEffect.csv"));
	animation5.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MonsterBallEffect.csv"));
	animation1.SetTarget(&effectBall->sprite);
	animation2.SetTarget(&shakeBall->sprite);
	animation3.SetTarget(&effectEnemyBall->sprite);
	animation4.SetTarget(&catchMonsterBall->sprite);//애니메이션 객체를 만들어라 다음부턴. 뒤늦게 이해함.
	animation5.SetTarget(&catchFailEffect->sprite);
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneBattle::Release()
{
	PokemonPool.Release();

	for (auto go : gameObjects)
	{
		//go->Release(); 소멸자에서 호출
		delete go;
	}
}

void SceneBattle::Enter()
{
	MeetMonster();
	
	battleSound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sounds/Battle.wav"));
	battleSound.setLoop(true);
	battleSound.play();
	battleSound.setVolume(50);

	myPokemonName->text.setString(myName);
	myPokemonName->SetActive(false);
	enemyHpRate = (enemyNowHp / enemyHp) * 100;
	myHpRate = (myNowHp / myHp) * 100;
	myHpRate = 100;
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });
	damageCheck = false;

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	ballStartPos = { 437,740 };
	ballEndPos = { 1697,350 };
	HpBar->sprite.setScale(0.f, 0.f);
	//realHpBar->sprite.setScale(0.f, 0.f);
	selectIcon->SetActive(false);
	menu->SetActive(false);
	explainMenu->SetActive(false);
	catchTextMenu->SetActive(false);
	//내 몬스터볼에서 나올때
	effectBall->sprite.setPosition(267, 530);
	effectBall->sprite.setScale(3.f, 3.f);
	effectBall->sortLayer = 204;
	//초기 방구 설정
	effectBall->SetOrigin(Origins::TL);
	effectBall->SetActive(true);
	//몬스터볼 흔들리는 애니메이션 이미지
	shakeBall->sprite.setPosition(0, 0);
	shakeBall->sprite.setScale(3.1f, 3.1f);
	shakeBall->SetOrigin(Origins::MC);
	shakeBall->sortLayer = 222;
	shakeBall->SetActive(false);
	ballNowPos = shakeBall->GetPosition();
	effectEnemyBall->sprite.setPosition(shakeBall->GetPosition());
	effectEnemyBall->sprite.setScale(3.f, 3.f);
	effectEnemyBall->sortLayer=205;
	effectEnemyBall->SetActive(false);
	catchMonsterBall->SetOrigin(Origins::TL);
	catchMonsterBall->sprite.setScale(3.f, 3.f);
	catchMonsterBall->SetActive(false);
	catchMonsterBall->sortLayer = 205;
	catchFailEffect->SetActive(false);
	catchFailEffect->sprite.setPosition(shakeBall->GetPosition());
	catchFailEffect->sprite.setScale(3.f, 3.f);
	catchFailEffect->sortLayer = 205;

	//날라간 뒤 몬스터볼 이미지
	sf::IntRect ballTopImageRect(0, 96, 16, 8);
	ballTop->sprite.setTextureRect(ballTopImageRect);
	ballTop->SetOrigin(Origins::BC);
	ballTop->sprite.setScale(3.f, 3.f);
	ballTop->sortLayer = 224;
	ballTop->SetActive(false);
	
	sf::IntRect ballBottomImageRect(0, 108, 16, 8);
	ballBottom->sprite.setTextureRect(ballBottomImageRect);
	ballBottom->SetOrigin(Origins::TC);
	ballBottom->sprite.setScale(3.f, 3.f);
	ballBottom->sortLayer = 223;
	ballBottom->SetActive(false);
	ballTopPos = { 1721, 378 };

	sf::IntRect ballImageRect(0, 0, 16, 16);
	ball->sprite.setTextureRect(ballImageRect);
	ball->SetOrigin(Origins::MC);
	ball->sprite.setScale(3.f, 3.f);
	ball->sortLayer = 224;
	ball->SetActive(false);

	sf::IntRect successBallRect(0, 124, 16, 16);
	successBall->sprite.setTextureRect(successBallRect);
	successBall->SetOrigin(Origins::MC);
	successBall->sprite.setScale(3.f, 3.f);
	successBall->sortLayer = 224;
	successBall->SetActive(false);

	skillMessage1->SetActive(false);
	skillMessage2->SetActive(false);
	skillMessage3->SetActive(false);
	skillMessage4->SetActive(false);
	skillExplain->SetActive(false);
	skillText->SetActive(false);
	fakeBox->rectangle.setFillColor({ 248,248,248 });
	fakeBox->rectangle.setPosition(fakeBoxPos);
	fakeBox->sortLayer = 220;
	fakeBox->SetActive(true);
	catchMessage1->SetActive(false);
	catchMessage2->SetActive(false);
	catchPokemonName->SetActive(false);
	
	listMove = false;
	userMove = false;
	aniPlay = false;
	menuDisplay = false;
	trigger1 = false;
	trigger2 = false;
	catchTextPrint = false;
	//gameEnd = false;
	menuIndex = 0;
	skillIndex = 0;
	//RectangleGo* recgo = (RectangleGo*)FindGo("square");
	recgo->rectangle.setFillColor({248,248,248});
	recgo->SetOrigin(Origins::MC);
	recgo->rectangle.setPosition(0,0);

	//한개 사이즈가 57,188
	//상대 이미지는 56,56
	//내 이미지는 48,48
	randomNum = Utils::RandomRange(1, 100);

	//내 몬스터
	sf::IntRect myMonsterImageRect(9 + (57 * myPokemonRect.x), 140 + (188 * myPokemonRect.y), userMosterSize, userMosterSize);
	mymonster->sprite.setTextureRect(myMonsterImageRect);
	mymonster->sprite.setPosition(180, 428);
	mymonster->SetOrigin(Origins::TL);
	mymonster->sprite.setScale(6.5f, 6.5f);
	mymonster->sortLayer = 204;
	mymonster->SetActive(false);

	sf::IntRect userImageRect(72, 374, userSize, userSize);
	user->sprite.setTextureRect(userImageRect);
	user->sprite.setPosition(size.x, 690);
	user->SetOrigin(Origins::BL);
	user->sprite.setScale(8.5f, 8.5f);
	user->SetActive(true);
	user->sortLayer = 221;
	clock.restart();

	HpBar->SetOrigin(Origins::TL);
	HpBar->sprite.setScale(1.f, 3.f);
	HpBar->SetPosition(186, 95);
	HpBar->sortLayer = 201;
	HpBar->SetActive(false);

	realHpBar->SetOrigin(Origins::TL);
	realHpBar->sprite.setScale(1.2f, 2.f);
	realHpBar->SetPosition(336, 95);
	realHpBar->sortLayer = 202;
	realHpBar->SetActive(false);
	enemyName->SetActive(false);

	healthBar = { 3.54f * enemyHpRate,30.f };
	pokemonHealth->SetOrigin(Origins::TL);
	pokemonHealth->rectangle.setPosition(453,109);
	pokemonHealth->rectangle.setSize(healthBar);
	pokemonHealth->rectangle.setFillColor(sf::Color::Green);
	pokemonHealth->sortLayer = 203;
	pokemonHealth->SetActive(false);

	myHpBar->SetOrigin(Origins::TR);
	myHpBar->sprite.setScale(-0.7f, 2.1f);
	myHpBar->SetPosition(13, 810);
	myHpBar->sortLayer = 201;
	myHpBar->SetActive(false);
	myRealHpBar->SetOrigin(Origins::TL);
	myRealHpBar->sprite.setScale(0.84f, 1.4f);
	myRealHpBar->SetPosition(125, 810);
	myRealHpBar->sortLayer = 202;
	myRealHpBar->SetActive(false);
	
	myHealthBar = { 2.5f * myHpRate,25.f };
	myPokemonHealth->SetOrigin(Origins::TL);
	myPokemonHealth->rectangle.setPosition(206, 824);
	myPokemonHealth->rectangle.setSize(myHealthBar);
	myPokemonHealth->rectangle.setFillColor(sf::Color::Green);
	myPokemonHealth->sortLayer = 203;
	myPokemonHealth->SetActive(false);

	throwBall = false;
	catchEffect = false;
	catchBoomEffect = false;
	ballUp = false;
	ballEffectEnd = false;
	ballCountCheck = false;
	shakeEffect = false;
	bounceCount = 0;
	shakeCount = 0;
	skillSelectCheck = false;
	enemyTurn = false;
	myTurn = false;
	enemyDamageCheck = false;
	
	Scene::Enter();
	
}

void SceneBattle::Exit()
{
	battleSound.stop();
	ClearObjectPool(PokemonPool);
	Scene::Exit();
}

void SceneBattle::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::X))
	{
		std::cout << "적 총 체력: " << enemyHp << std::endl;
		std::cout << "적 현재 체력: " << enemyNowHp << std::endl;
		std::cout << "내 공격 데미지: " << myDamage << std::endl;
		std::cout << "계산된 체력 비율: " << enemyNowHp / enemyHp << std::endl;
		std::cout << "체력 비율: " << enemyHpRate << std::endl;
	}
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos(); //마우스 위치
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	monster->SetOrigin(Origins::TR);
	if (!listMove) //처음 몬스터 이미지 움직임
	{
		monster->sprite.move(4.f, 0);
		clock.restart();
	}
	if (monster->sprite.getPosition().x == windowSize.x)
	{
		monster->sprite.move(0.f, 0.f);
		listMove = true;
	}
	user->SetOrigin(Origins::BL);
	if (!userMove)
	{
		user->sprite.move(-4.f, 0.f);
	}
	if (user->sprite.getPosition().x == 0)
	{
		user->sprite.move(0.f, 0.f);
		userMove = true;
	}
	if (listMove)
	{
		pokemonHealth->SetActive(true);
		realHpBar->SetActive(true);
		HpBar->SetActive(true);
		enemyName->SetActive(true);
			
	}
	if (userMove && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		userMove = false;
	}
				
	if (user->GetActive() && user->sprite.getPosition().x <= -400)
	{
		user->SetActive(false);
		userMove = true;
	}
	if (!user->GetActive() && !aniPlay)
	{
 		animation1.Play("MonsterBallEffect");
		std::cout << "실행했다." << std::endl;
		aniPlay = true;
		clock.restart();
	}

	if (aniPlay && clock.getElapsedTime() > sf::seconds(0.4f))
	{
		effectBall->SetActive(false);
		myHpBar->SetActive(true);
		myPokemonHealth->SetActive(true);
		myRealHpBar->SetActive(true);
	}
	if (!effectBall->GetActive())
	{
		mymonster->SetActive(true);
		myPokemonName->SetActive(true);
	}
	//-----------------------여기까지가 몬스터 출현 셋팅
	if (mymonster->GetActive())
	{
		Battle(dt);
		if (!trigger1)
		{
			MoveCursorMenu();
		}
		if (trigger1)
		{
			SelectMenu(dt);
		}
		if (!trigger2)
		{
			if (!enemyTurn && !myTurn &&!damageCheck) 
			{
				MoveCursorSkill();
			}
		}
		if (skillSelectCheck&&!trigger2 && (clock2.getElapsedTime() > sf::seconds(0.5f)))
		{
			BattleTurnDecision(dt);
				
		}
	}
	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}*/

	animation1.Update(dt);
	animation2.Update(dt);
	animation3.Update(dt);
	animation4.Update(dt);
	animation5.Update(dt);
}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneBattle::Battle(float dt)
{
	menu->sprite.setScale(1.65f, 1.38f);
	menu->SetPosition(700, 600);
	menu->sortLayer = 205;
	menu->SetActive(true);

	fakeBox->SetActive(false);

	selectIcon->sprite.setScale(10.f, 10.f);
	selectIcon->sprite.setPosition(selectFirstPos);
	selectIcon->sortLayer = 210;
	selectIcon->SetActive(true);
	
	MenuText();
}


void SceneBattle::MenuText()
{
	if (!menuDisplay) 
	{
		std::wstring attack = stringTable->GetUni("ATTACK", Languages::KOR);
		menuText1->text.setCharacterSize(70);
		menuText1->text.setString(attack);
		menuText1->text.setFillColor(sf::Color::Black);
		menuText1->SetOrigin(Origins::TL);
		menuText1->SetPosition(textFirstPos);
		menuText1->sortLayer = 207;
		std::wstring myPokemon = stringTable->GetUni("POKEMON", Languages::KOR);
		menuText2->text.setCharacterSize(70);
		menuText2->text.setString(myPokemon);
		menuText2->text.setFillColor(sf::Color::Black);
		menuText2->SetOrigin(Origins::TL);
		menuText2->SetPosition(textFirstPos.x+454, textFirstPos.y);
		menuText2->sortLayer = 207;
		std::wstring myBag = stringTable->GetUni("BAG", Languages::KOR);
		menuText3->text.setCharacterSize(70);
		menuText3->text.setString(myBag);
		menuText3->text.setFillColor(sf::Color::Black);
		menuText3->SetOrigin(Origins::TL);
		menuText3->SetPosition(textFirstPos.x, textFirstPos.y+170);
		menuText3->sortLayer = 207;
		std::wstring run = stringTable->GetUni("RUN", Languages::KOR);
		menuText4->text.setCharacterSize(70);
		menuText4->text.setString(run);
		menuText4->text.setFillColor(sf::Color::Black);
		menuText4->SetOrigin(Origins::TL);
		menuText4->SetPosition(textFirstPos.x+454, textFirstPos.y + 170);
		menuText4->sortLayer = 207;
	}
	if (!menuDisplay&&INPUT_MGR.GetKeyUp(sf::Keyboard::Enter))
	{
		menuDisplay = true;
		std::cout << "여디야" << std::endl;
	}
	if (menuDisplay&&!trigger1) {
		trigger1 = true;
	}
	
}

void SceneBattle::SelectMenu(float dt)
{
	switch (menuIndex)
	{
	case (int)Menu::Skill:
		SkillSelect();
			
		break;
	case (int)Menu::Bag:
		
		SkillSelect();

		break;
	case (int)Menu::Pokemon:

		CatchText();
		if (catchTextClock.getElapsedTime() > sf::seconds(1.f))
		{
			CatchPokemon(dt);
		}
		break;
	case (int)Menu::Run:
		BattleEnd();
		break;
	}
}

void SceneBattle::SkillSelect()
{
	if (menuDisplay) 
	{
		menuText1->text.setCharacterSize(70);
		menuText1->text.setString(useskill1);
		menuText1->text.setFillColor(sf::Color::Black);
		menuText1->SetOrigin(Origins::TL);
		menuText1->SetPosition(textFirstPos);
		menuText1->sortLayer = 207;

		menuText2->text.setCharacterSize(70);
		menuText2->text.setString(useskill2);
		menuText2->text.setFillColor(sf::Color::Black);
		menuText2->SetOrigin(Origins::TL);
		menuText2->SetPosition(textFirstPos.x + 454, textFirstPos.y);
		menuText2->sortLayer = 207;

		menuText3->text.setCharacterSize(70);
		menuText3->text.setString(useskill3);
		menuText3->text.setFillColor(sf::Color::Black);
		menuText3->SetOrigin(Origins::TL);
		menuText3->SetPosition(textFirstPos.x, textFirstPos.y + 170);
		menuText3->sortLayer = 207;
		
		menuText4->text.setCharacterSize(70);
		menuText4->text.setString(useskill4);
		menuText4->text.setFillColor(sf::Color::Black);
		menuText4->SetOrigin(Origins::TL);
		menuText4->SetPosition(textFirstPos.x + 454, textFirstPos.y + 170);
		menuText4->sortLayer = 207;
	}

	if (!skillSelectCheck &&!trigger2&&INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		skillSelectCheck = true;
		selectIcon->SetActive(false);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape)&&!trigger2)//스킬선택전인경우
	{
		GoBackMenu();
	}
}

void SceneBattle::SetSkill()
{
	switch (skillIndex)
	{
	case (int)SkillNum::Skill1:
		SkillExplain((int)SkillNum::Skill1);

		break;
	case (int)SkillNum::Skill2:
		SkillExplain((int)SkillNum::Skill2);
		break;
	case (int)SkillNum::Skill3:
		SkillExplain((int)SkillNum::Skill3);
		break;
	case (int)SkillNum::Skill4:
		SkillExplain((int)SkillNum::Skill4);
		break;
	}
}

void SceneBattle::SkillExplain(int n)
{
	explainMenu->SetActive(true);
	explainMenu->sprite.setScale(1.5f, 1.38f);
	explainMenu->SetPosition(900, 600);
	explainMenu->sortLayer = 211;
	
	std::wstring skill= stringTable->GetUni("SKILLEXPLAIN", Languages::KOR);
	skillExplain->text.setCharacterSize(40);
	skillExplain->text.setFillColor(sf::Color::Black);
	skillExplain->text.setString(skill);
	skillExplain->SetOrigin(Origins::TL);
	skillExplain->SetPosition(973,678);
	skillExplain->sortLayer = 212;
	skillExplain->SetActive(menu->GetActive());
	skillText->text.setCharacterSize(80);
	
	switch (n)
	{
	case 0:
		useskill = useskill1;
		break;
	case 1:
		useskill = useskill2;
		break;
	case 2:
		useskill = useskill3;
		break;
	case 3:
		useskill = useskill4;
		break;
	}

	skillText->text.setFillColor(sf::Color::Black);
	skillText->text.setString(useskill);
	skillText->SetOrigin(Origins::TL);
	skillText->SetPosition(973,837);
	skillText->sortLayer = 212;
	skillText->SetActive(true);
}

void SceneBattle::BattleEnd()
{
	SCENE_MGR.ChangeScene(SceneId::Game);
}

void SceneBattle::MeetMonster()
{
	monster = PokemonPool.Get();
	monster->SetPosition(0, 0);
	std::cout << monster->GetImageRectSize().x <<"," << monster->GetImageRectSize().y << std::endl;
	AddGo(monster);
	std::wstring monsterName = stringTable->GetUni(monster->GetMonsterName(), Languages::KOR);
	enemyName->text.setCharacterSize(40);
	enemyName->text.setFillColor(sf::Color::Black);
	enemyName->text.setString(monsterName);
	enemyName->SetPosition(realHpBar->GetPosition().x, realHpBar->GetPosition().y-50);
	enemyName->sortLayer = 212;
	enemyHp = monster->GetMonsterHp();
	enemyNowHp = enemyHp;
	myNowHp = myHp;
}

void SceneBattle::CatchPokemon(float dt)
{
	if (!throwBall)
	{
		shakeBall->SetActive(true);
		animation2.Play("ShakeBallEffect");
		shakeBall->SetPosition(ballStartPos);
		
		ballSpeed = 0.8f;
		timer = 0.f;
		throwBall = true;
	}
	if (shakeBall->GetActive())
	{
		timer += dt * ballSpeed;

		if (timer > 1.f)
		{
			timer = 1.f;
		}
		//볼 날라가는 곡선
		ballNowPos = CalculateOrbit(ballStartPos, sf::Vector2f{abs(ballEndPos.x - ballStartPos.x), abs(ballEndPos.y - ballStartPos.y) / 5}, ballEndPos, timer);
		shakeBall->SetPosition(ballNowPos);
		if (shakeBall->GetPosition().x == ballEndPos.x)
		{
			ballSpeed = 0.f;
			if (!catchEffect)
			{
				ballClock.restart();
				catchEffect = true;
			}
		}
	}
	//볼이 다 날라간 후
	if (catchEffect)
	{
		shakeBall->SetActive(false);
	}
	if (!ballTop->GetActive())
	{
		ballTopClock.restart();
	}
	//볼 벌어지는 이펙트 & 볼이 사라진 뒤
	if (!shakeBall->GetActive()&&catchEffect)
	{
		
		ballTop->SetPosition(ballTopPos);
		ballBottom->SetPosition(1721, 375);
		if (!catchBoomEffect)
		{
			ballTop->SetActive(true);
			ballBottom->SetActive(true);
			effectEnemyBall->SetActive(true);
			animation3.Play("MonsterBallEffect");
			effectEnemyBall->SetPosition(ballTopPos.x, ballTopPos.y + 50.f);
			effectEnemyBall->SetOrigin(Origins::BC);
			catchBoomEffect = true;
			ballVelocity = {0,-300.f };//볼 속도 초기화 던질때마다.
		}
		if (!ballUp&&ballTopPos.y >= 100)
		{
			ballTopPos.y -= 3.0f;
			ballClock.restart();
		}
		if (ballTopPos.y < 100)
		{
			monster->SetActive(false);
			ballUp = true;
		}
		if (!ballEffectEnd && ballClock.getElapsedTime() >= sf::seconds(0.5f))
		{
			ballTopPos.y += 3.0f;
			if (ballTopPos.y >= ballBottom->GetPosition().y)
			{
				ballEffectEnd = true;
				ballBottom->SetActive(false);
				ballTop->SetActive(false);
				ball->SetPosition(ballBottom->GetPosition());
				ball->SetActive(true);
				ballPos = ball->GetPosition();
			}
		}
	}
	if (ballEffectEnd&&bounceCount<5)
	{
		ballPos += ballVelocity*dt;
		ballVelocity.y += ballGravity;
		if (ballVelocity.y > 0 && !ballCountCheck)
		{
			ballCountCheck = true;
			bounceCount++;
			
		}
	}
	if (ballCountCheck && ballPos.y >=380)
	{
		ballVelocity.y = -300.f * (5 - bounceCount) / 5;
		ballCountCheck = false;
		ballTopClock.restart();
	}
	if (!shakeEffect&&ball->GetActive() && bounceCount == 5)
	{
		ballPos.y = ballBottom->GetPosition().y;
		ball->SetActive(false);
		
		shakeEffect = true;
		catchMonsterBall->SetActive(true);
		catchMonsterBall->SetPosition(1695, 355);
	}
	ball->SetPosition(ballPos);
	if (catchMonsterBall->GetActive()&& !shakeEffect && shakeCount < 2)
	{
		ballShakeClock.restart();
		shakeCount++;
		shakeEffect = true;
	}
	if (ballShakeClock.getElapsedTime() > sf::seconds(1.5f)&&shakeEffect)
	{
		animation4.Play("ShakeBallEffect");
		shakeEffect = false;
	}
	if (ballShakeClock.getElapsedTime() > sf::seconds(3.7f)&&shakeCount>=2)
	{
		if (!catchCheck)
		{
			randomNum = Utils::RandomRange(1, 101);
			if ((enemyNowHp / monster->GetMonsterHp()) <= 0.25)
			{
				randomNum += 30;
			}
			else if ((enemyNowHp / monster->GetMonsterHp()) <= 0.5)
			{
				randomNum += 10;
			}
		}
		if(randomNum<monster->GetMonsterCatchRate())
		{
			catchCheck = true;
			CatchFail(dt);
		}
		else if(randomNum>= monster->GetMonsterCatchRate())
		{
			catchCheck = true;
			
			CatchSuccess();
			
		}
	}
}

void SceneBattle::CatchSuccess()
{
	CatchSuccessText();
	successBall->SetActive(true);
	successBall->sprite.setPosition(1719, 379);
	catchMonsterBall->SetActive(false);
	ChangeMyPokemon();
	ChangeMyPokemonSkill();
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Z))
	{
		
		BattleEnd();
	}
}

void SceneBattle::MoveCursorMenu()
{
	if (!enemyTurn && !myTurn)
	{
		if (menuIndex == 0)
		{
			selectIcon->sprite.setPosition(selectFirstPos);
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Right))
			{
				menuIndex++;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
			{
				menuIndex++;
				menuIndex++;
			}
		}
		if (menuIndex == 1)
		{
			selectIcon->sprite.setPosition(selectFirstPos.x + 454.f, selectFirstPos.y);
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Left))
			{
				menuIndex--;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
			{
				menuIndex++;
				menuIndex++;
			}
		}
		if (menuIndex == 2)
		{
			selectIcon->sprite.setPosition(selectFirstPos.x, selectFirstPos.y + 175.f);
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
			{
				menuIndex--;
				menuIndex--;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Right))
			{
				menuIndex++;
			}
		}
		if (menuIndex == 3)
		{
			selectIcon->sprite.setPosition(selectFirstPos.x + 454.f, selectFirstPos.y + 175.f);
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Left))
			{
				menuIndex--;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
			{
				menuIndex--;
				menuIndex--;
			}
		}
	}
}

void SceneBattle::MoveCursorSkill()
{
	if (!enemyTurn && !myTurn)
	{
		if (skillIndex == 0)
		{
			selectIcon->sprite.setPosition(selectFirstPos);
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Right))
			{
				skillIndex++;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
			{
				skillIndex++;
				skillIndex++;
			}
		}
		if (skillIndex == 1)
		{
			selectIcon->sprite.setPosition(selectFirstPos.x + 454.f, selectFirstPos.y);
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Left))
			{
				skillIndex--;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
			{
				skillIndex++;
				skillIndex++;
			}
		}
		if (skillIndex == 2)
		{
			selectIcon->sprite.setPosition(selectFirstPos.x, selectFirstPos.y + 175.f);
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
			{
				skillIndex--;
				skillIndex--;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Right))
			{
				skillIndex++;
			}
		}
		if (skillIndex == 3)
		{
			selectIcon->sprite.setPosition(selectFirstPos.x + 454.f, selectFirstPos.y + 175.f);
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Left))
			{
				skillIndex--;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
			{
				skillIndex--;
				skillIndex--;
			}
		}
	}
}

sf::Vector2f SceneBattle::CalculateOrbit(const sf::Vector2f& startPos, const sf::Vector2f& highPos, const sf::Vector2f& endPos, float moveT)
{
	float u = 1.f - moveT;
	float tt = moveT * moveT;
	float uu = u * u;
	sf::Vector2f p = uu * startPos;
	p += 1.2f* u * moveT * highPos;
	p += tt * endPos;
	return p;
}

void SceneBattle::GoBackMenu()
{
	menuIndex = 0;
	skillIndex = 0;
	menuDisplay = false;
	trigger1 = false;
	skillText->SetActive(false);
	explainMenu->SetActive(false);
	skillExplain->SetActive(false);
	trigger2 = false;
	damageCheck = false;
	catchTextMenu->SetActive(false);
	catchMessage1->SetActive(false);
	catchMessage2->SetActive(false);
	catchTextPrint = false;
	throwBall = false;
	catchEffect = false;
	shakeBall->SetActive(false);
	catchMonsterBall->SetActive(false);
	catchBoomEffect = false;
	ballUp = false;
	ballEffectEnd = false;
	ballCountCheck = false;
	shakeEffect = false;
	bounceCount = 0;
	shakeCount = 0;
	catchFailEffect->SetActive(false);
	catchFailEffectbool = false;
	catchCheck = false;
	skillSelectCheck = false;
	enemyTurn = false;
	myTurn = false;
	enemySkillExplainFinish = false;
	ImAlive = false;
	enemyAlive = false;
	enemyAttackend = false;
	selectIcon->SetActive(true);
}

void SceneBattle::CatchText()
{
	if(!catchTextPrint)
	{
		catchTextMenu->SetActive(true);
		catchTextMenu->sprite.setScale(1.5f, 1.38f);
		catchTextMenu->SetPosition(900, 600);
		catchTextMenu->sortLayer = 211;

		std::wstring catchExplain1 = stringTable->GetUni("CATCH1", Languages::KOR);
		catchMessage1->text.setCharacterSize(40);
		catchMessage1->text.setFillColor(sf::Color::Black);
		catchMessage1->text.setString(catchExplain1);
		catchMessage1->SetOrigin(Origins::TL);
		catchMessage1->SetPosition(973, 678);
		catchMessage1->sortLayer = 212;
		catchMessage1->SetActive(catchTextMenu->GetActive());

		std::wstring catchExplain2 = stringTable->GetUni("CATCH2", Languages::KOR);
		catchMessage2->text.setCharacterSize(40);
		catchMessage2->text.setFillColor(sf::Color::Black);
		catchMessage2->text.setString(catchExplain2);
		catchMessage2->SetOrigin(Origins::TL);
		catchMessage2->SetPosition(973, 837);
		catchMessage2->sortLayer = 212;
		catchMessage2->SetActive(catchTextMenu->GetActive());
		catchTextPrint = true;
	}
	
}

void SceneBattle::CatchSuccessText()
{
	if (catchTextPrint)
	{
		std::wstring catchFinish1 = stringTable->GetUni("CATCHFINISH1", Languages::KOR);
		catchMessage1->text.setCharacterSize(40);
		catchMessage1->text.setFillColor(sf::Color::Black);
		catchMessage1->text.setString(catchFinish1);
		catchMessage1->SetOrigin(Origins::TL);
		catchMessage1->SetPosition(973, 678);
		catchMessage1->sortLayer = 212;

		catchPokemonName->SetActive(true);
		std::wstring monsterName = stringTable->GetUni(monster->GetMonsterName(), Languages::KOR);
		catchPokemonName->text.setCharacterSize(40);
		catchPokemonName->text.setFillColor(sf::Color::Black);
		catchPokemonName->text.setString(monsterName);
		catchPokemonName->SetPosition(1268,678);
		catchPokemonName->sortLayer = 212;

		std::wstring catchFinish2 = stringTable->GetUni("CATCHFINISH2", Languages::KOR);
		catchMessage2->text.setCharacterSize(40);
		catchMessage2->text.setFillColor(sf::Color::Black);
		catchMessage2->text.setString(catchFinish2);
		catchMessage2->SetOrigin(Origins::TL);
		catchMessage2->SetPosition(973, 837);
		catchMessage2->sortLayer = 212;
	}
}


void SceneBattle::CatchFail(float dt)
{
	if (!catchFailEffect->GetActive())
	{
		clock3.restart();
	}
	catchFailEffect->SetActive(true);
	
	if (!catchFailEffectbool)
	{
		animation5.Play("MonsterBallEffect");
		catchFailEffect->SetOrigin(Origins::BC);
		catchFailEffect->SetPosition(effectEnemyBall->GetPosition());
		monster->SetActive(true);
		catchFailEffectbool = true;
		failClock.restart();
	}
	CatchFailedText(dt);
}

void SceneBattle::CatchFailedText(float dt)
{
	std::wstring catchFailed1 = stringTable->GetUni("CATCHFAILED1", Languages::KOR);
	catchMessage1->text.setCharacterSize(40);
	catchMessage1->text.setFillColor(sf::Color::Black);
	catchMessage1->text.setString(catchFailed1);
	catchMessage1->SetOrigin(Origins::TL);
	catchMessage1->SetPosition(973, 678);
	catchMessage1->sortLayer = 212;

	std::wstring catchFailed2 = stringTable->GetUni("CATCHFAILED2", Languages::KOR);
	catchMessage2->text.setCharacterSize(40);
	catchMessage2->text.setFillColor(sf::Color::Black);
	catchMessage2->text.setString(catchFailed2);
	catchMessage2->SetOrigin(Origins::TL);
	catchMessage2->SetPosition(973, 837);
	catchMessage2->sortLayer = 212;
	catchMonsterBall->SetActive(false);
		
	if (clock3.getElapsedTime() > sf::seconds(1.0f))
	{
		GoBackMenu();
		BattleEnd();
	}
}

void SceneBattle::ChangeMyPokemon()
{
	myPokemonRect.x = monster->GetImageRectSize().x;
	myPokemonRect.y = monster->GetImageRectSize().y;
	myName = stringTable->GetUni(monster->GetMonsterName(), Languages::KOR);
	mySpeed = monster->GetSpeed();
	myHp = monster->GetMonsterHp();
}

void SceneBattle::ChangeMyPokemonSkill()
{
	useskill1 = stringTable->GetUni(monster->GetSkillName(0), Languages::KOR);
	useskill2 = stringTable->GetUni(monster->GetSkillName(1), Languages::KOR);
	useskill3 = stringTable->GetUni(monster->GetSkillName(2), Languages::KOR);
	useskill4 = stringTable->GetUni(monster->GetSkillName(3), Languages::KOR);
	mySkillDamage1 = monster->GetSkillDamage(0);
	mySkillDamage2 = monster->GetSkillDamage(1);
	mySkillDamage3 = monster->GetSkillDamage(2);
	mySkillDamage4 = monster->GetSkillDamage(3);
}

void SceneBattle::EnemySkillExplain(int n)
{
	explainMenu->SetActive(true);
	explainMenu->sprite.setScale(1.5f, 1.38f);
	explainMenu->SetPosition(900, 600);
	explainMenu->sortLayer = 211;

	std::wstring skill = stringTable->GetUni("ENEMYSKILLEXPLAIN", Languages::KOR);
	skillExplain->text.setCharacterSize(40);
	skillExplain->text.setFillColor(sf::Color::Black);
	skillExplain->text.setString(skill);
	skillExplain->SetOrigin(Origins::TL);
	skillExplain->SetPosition(973, 678);
	skillExplain->sortLayer = 212;
	skillExplain->SetActive(menu->GetActive());
	skillText->text.setCharacterSize(80);

	switch (n)
	{
	case 0:
		enemySkill = stringTable->GetUni(monster->GetSkillName(0), Languages::KOR);
		break;
	case 1:
		enemySkill = stringTable->GetUni(monster->GetSkillName(1), Languages::KOR);
		break;
	case 2:
		enemySkill = stringTable->GetUni(monster->GetSkillName(2), Languages::KOR);
		break;
	case 3:
		enemySkill = stringTable->GetUni(monster->GetSkillName(3), Languages::KOR);
		break;
	}
	skillText->text.setFillColor(sf::Color::Black);
	skillText->text.setString(enemySkill);
	skillText->SetOrigin(Origins::TL);
	skillText->SetPosition(973, 837);
	skillText->sortLayer = 212;
	skillText->SetActive(true);
}

void SceneBattle::BattleTurnDecision(float dt)
{
	if (mySpeed < monster->GetSpeed()&&!ImAlive&&!enemyAlive&& !catchFailEffectbool)
	{
		if (!enemyTurn)
		{
			MyMonsterHp(dt);
			
		}
		if(enemyTurn&&!myTurn)
		{
			EnemyMonsterHp(dt); //내가 상대를 공격할때
		}
		if (enemyTurn && myTurn) 
		{
			GoBackMenu();
		}

	}
	else if (mySpeed >= monster->GetSpeed() && !ImAlive && !enemyAlive&& !catchFailEffectbool)
	{
		if (!myTurn)
		{
			EnemyMonsterHp(dt); //내가 상대를 공격할때
		}
		if (!enemyTurn && myTurn)
		{
			MyMonsterHp(dt);
		}
		if (enemyTurn && myTurn)
		{
			enemyDamageCheck = false;
			GoBackMenu();
		}
	}
}

void SceneBattle::EnemyMonsterHp(float dt)
{
	switch (skillIndex)
	{
	case 0:
		myDamage = mySkillDamage1;
		break;
	case 1:
		myDamage = mySkillDamage2;
		break;
	case 2:
		myDamage = mySkillDamage3;
		break;
	case 3:
		myDamage = mySkillDamage4;
		break;
	}
	SkillExplain(skillIndex);
	if (!damageCheck)
	{
		if (enemyHp == enemyNowHp)
		{
			enemyNowHp = enemyHp - myDamage;
		}
		else {
			enemyNowHp = enemyNowHp - myDamage;
		}
		damageCheck = true;
	}
	if (enemyHpRate <= 0)
	{
		myDamage = 0;
		enemyNowHp = 0;
	}
	
	if ((enemyNowHp/enemyHp)*100 <= enemyHpRate&& ballTopClock.getElapsedTime()>sf::seconds(0.02f))
	{
		enemyHpRate -= myDamage*dt;
		ballTopClock.restart();
	}

	healthBar.x = enemyHpRate * 3.54f;
	pokemonHealth->rectangle.setSize(healthBar);

	if (enemyHpRate <= 50 &&
		enemyHpRate > 25)
	{
		pokemonHealth->rectangle.setFillColor({ 234,157,40 });
	}
	else if (enemyHpRate <= 25.1 &&
		enemyHpRate> 0)
	{
		pokemonHealth->rectangle.setFillColor(sf::Color::Red);
	}
	else if (enemyHpRate <= 0)
	{
		enemyHpRate = 0;
		monster->sprite.move(0.f, 5.f);
	}
	if (enemyHpRate!= 0&&damageCheck && ballTopClock.getElapsedTime()>sf::seconds(1.f))
	{
		myTurn = true;
		std::cout << "여기왜 지났다?" << std::endl;
	}
	

	if (monster->sprite.getPosition().y >= windowSize.y)
	{
		std::cout << "탈출포인트 여기 지났다" << std::endl;
		BattleEnd();
	}
}


void SceneBattle::MyMonsterHp(float dt)
{
	if (skillSelectCheck&&!enemySkillExplainFinish)//랜덤 숫자 뽑기
	{
		enemyAttack= Utils::RandomRange(0, 4);
		enemySkillExplainFinish = true;
	}
	switch (enemyAttack)
	{
	case 0:
		enemyDamage = monster->GetSkillDamage(0);
		break;
	case 1:
		enemyDamage = monster->GetSkillDamage(1);
		break;
	case 2:
		enemyDamage = monster->GetSkillDamage(2);
		break;
	case 3:
		enemyDamage = monster->GetSkillDamage(3);
		break;
	}
	EnemySkillExplain(enemyAttack);
	if (!enemyDamageCheck)
	{
		if (myHp == myNowHp)
		{
			myNowHp = myHp - enemyDamage;
			
		}
		else {
			myNowHp = myNowHp - enemyDamage;
		}
		enemyDamageCheck = true;
	}
	if (myHpRate <= 0)
	{
		enemyDamage = 0;
		myNowHp = 0;
	}
	if ((myNowHp / myHp) * 100 <= myHpRate && ballTopClock.getElapsedTime() > sf::seconds(0.02f))
	{
		myHpRate -= enemyDamage * dt;
		std::cout << "악 내피" << std::endl;
		ballTopClock.restart();
	}

	myHealthBar.x = myHpRate * 2.5f;
	myPokemonHealth->rectangle.setSize(myHealthBar);

	if (myHpRate <= 50 && myHpRate > 25)
	{
		myPokemonHealth->rectangle.setFillColor({ 234,157,40 });
	}
	else if (myHpRate <= 25.1 && myHpRate > 0)
	{
		myPokemonHealth->rectangle.setFillColor(sf::Color::Red);
	}
	else if (myHpRate <= 0)
	{
		myHpRate = 0;
		mymonster->sprite.move(0.f, 5.f);
	}
	if (myHpRate != 0 && enemyDamageCheck && ballTopClock.getElapsedTime() > sf::seconds(1.f))
	{
		enemyTurn = true;
		std::cout << "여기왜 지났다?" << std::endl;
	}
	
	if (mymonster->sprite.getPosition().y >= windowSize.y)
	{
		std::cout << "탈출포인트 여기 지났다" << std::endl;
		BattleEnd();
	}
}
