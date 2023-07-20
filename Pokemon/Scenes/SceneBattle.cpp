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

SceneBattle::SceneBattle() : Scene(SceneId::Battle)
{
	resourceListPath = "scripts/SceneBattleResourceList.csv";
}

void SceneBattle::Init()
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	//std::cout << "hi" << std::endl;
	worldView.setSize(windowSize);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);
	AddGo(new RectangleGo(windowSize, "square"));
	AddGo(new SpriteGo("graphics/PokemonList.png", "List"));
	AddGo(new SpriteGo("graphics/PokemonList.png", "myMonster"));
	AddGo(new SpriteGo("graphics/User.png", "User"));
	SpriteGo* HpBar= (SpriteGo*)AddGo(new SpriteGo("graphics/HpBar.png", "HpBar"));
	SpriteGo* RealHpBar = (SpriteGo*)AddGo(new SpriteGo("graphics/RealHpBar.png", "RealHpBar"));
	HpBar->sprite.setScale(0.f, 0.f);
	RealHpBar->sprite.setScale(0.f, 0.f);
	AddGo(new RectangleGo(healthBar, "healthBar"));
	SpriteGo* select = (SpriteGo*)AddGo(new SpriteGo("graphics/selectIcon.png", "Select"));
	select->SetActive(false);
	SpriteGo* menu = (SpriteGo*)AddGo(new SpriteGo("graphics/menuBox.png", "Menu"));
	menu->SetActive(false);
	SpriteGo* explainMenu = (SpriteGo*)AddGo(new SpriteGo("graphics/menuBox.png", "ExplainMenu"));
	explainMenu->SetActive(false);
	//std::cout<<rect.getPosition().x << std::endl;
	//몬스터볼 연출 효과
	SpriteGo* effectBall = (SpriteGo*)AddGo(new SpriteGo("","Effect"));
	effectBall->sprite.setPosition(267, 530);
	effectBall->sprite.setScale(3.f, 3.f);
	effectBall->sortLayer = 204;

	AddGo(new TextGo("menuMessage1", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("menuMessage2", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("menuMessage3", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("menuMessage4", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("SkillMessage1", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("SkillMessage2", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("SkillMessage3", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("SkillMessage4", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("SkillExplain", "fonts/DOSPilgi.ttf"));
	AddGo(new TextGo("SkillText", "fonts/DOSPilgi.ttf"));
	
	RectangleGo* fakeBox = (RectangleGo*)AddGo(new RectangleGo(fakeBoxScale, "fakeBox"));
	fakeBox->rectangle.setFillColor({ 248,248,248 });
	fakeBox->rectangle.setPosition(fakeBoxPos);
	fakeBox->sortLayer = 220;
	fakeBox->SetActive(true);

	//메뉴 내 사각형 아이콘

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MonsterBallEffect.csv"));
	animation.SetTarget(&effectBall->sprite);
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneBattle::Release()
{


	for (auto go : gameObjects)
	{
		//go->Release(); 소멸자에서 호출
		delete go;
	}
}

void SceneBattle::Enter()
{
	
	TextGo* SkillMessage1 = (TextGo*)FindGo("SkillMessage1");
	TextGo* SkillMessage2 = (TextGo*)FindGo("SkillMessage2");
	TextGo* SkillMessage3 = (TextGo*)FindGo("SkillMessage3");
	TextGo* SkillMessage4 = (TextGo*)FindGo("SkillMessage4");
	TextGo* SkillExplain = (TextGo*)FindGo("SkillExplain");
	TextGo* SkillText = (TextGo*)FindGo("SkillText");
	SkillMessage1->SetActive(false);
	SkillMessage2->SetActive(false);
	SkillMessage3->SetActive(false);
	SkillMessage4->SetActive(false);
	SkillExplain->SetActive(false);
	SkillText->SetActive(false);

	auto size = FRAMEWORK.GetWindowSize();
	//auto centerPos = size / 2.f;
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	
	
	
	listMove = false;
	userMove = false;
	aniPlay = false;
	menuDisplay = false;
	trigger1 = false;
	trigger2 = false;
	//gameEnd = false;
	menuIndex = 0;
	skillIndex = 0;
	RectangleGo* recgo = (RectangleGo*)FindGo("square");
	recgo->rectangle.setFillColor({248,248,248});
	recgo->SetOrigin(Origins::MC);
	recgo->rectangle.setPosition(0,0);

	//한개 사이즈가 57,188
	//상대 이미지는 56,56
	//내 이미지는 48,48
	SpriteGo* list = (SpriteGo*)FindGo("List");
	randomNum = Utils::RandomRange(1, 100);
	iNum = randomNum % 30;
	jNum = randomNum % 25;

	SpriteGo* effectBall = (SpriteGo*)FindGo("Effect");
	effectBall->SetActive(true);



	sf::IntRect monsterImageRect(1+(57*iNum), 18+(188*jNum), enemySize, enemySize);
	list->sprite.setTextureRect(monsterImageRect);
	list->sprite.setPosition(0,0);
	list->SetOrigin(Origins::TL);
	list->sprite.setScale(8.5f, 8.5f);
	list->sortLayer = 204;

	//내 몬스터
	SpriteGo* mymonster = (SpriteGo*)FindGo("myMonster");
	sf::IntRect myMonsterImageRect(693, 516, userMosterSize, userMosterSize);
	mymonster->sprite.setTextureRect(myMonsterImageRect);
	mymonster->sprite.setPosition(180, 428);
	mymonster->SetOrigin(Origins::TL);
	mymonster->sprite.setScale(6.5f, 6.5f);
	mymonster->sortLayer = 204;
	mymonster->SetActive(false);

	SpriteGo* user = (SpriteGo*)FindGo("User");
	sf::IntRect userImageRect(72, 374, userSize, userSize);
	user->sprite.setTextureRect(userImageRect);
	user->sprite.setPosition(size.x, 690);
	user->SetOrigin(Origins::BL);
	user->sprite.setScale(8.5f, 8.5f);
	user->SetActive(true);
	user->sortLayer = 221;
	clock.restart();
	

	SpriteGo* HpBar = (SpriteGo*)FindGo("HpBar");
	HpBar->SetOrigin(Origins::TL);
	HpBar->sprite.setScale(1.f, 3.f);
	HpBar->SetPosition(186, 95);
	HpBar->sortLayer = 201;
	HpBar->SetActive(false);
	SpriteGo* realHpBar = (SpriteGo*)FindGo("RealHpBar");
	realHpBar->SetOrigin(Origins::TL);
	realHpBar->sprite.setScale(1.2f, 2.f);
	realHpBar->SetPosition(336, 95);
	realHpBar->sortLayer = 202;
	realHpBar->SetActive(false);
	
	/*SpriteGo* select = (SpriteGo*)FindGo("Select");
	select->SetPosition(100, 100);
	select->sprite.setScale(10.f, 10.f);*/
	
	healthBar = { 3.54f * 100,25.f };
	RectangleGo* pokemonHealth = (RectangleGo*)FindGo("healthBar");
	pokemonHealth->SetOrigin(Origins::TL);
	pokemonHealth->rectangle.setPosition(452, 111);
	pokemonHealth->rectangle.setSize(healthBar);
	pokemonHealth->rectangle.setFillColor(sf::Color::Green);
	pokemonHealth->sortLayer = 203;
	pokemonHealth->SetActive(false);
	
	SpriteGo* menu = (SpriteGo*)FindGo("Menu");
	menu->SetActive(false);
	SpriteGo* explainMenu = (SpriteGo*)FindGo("ExplainMenu");
	explainMenu->SetActive(false);
	RectangleGo* fakeBox = (RectangleGo*)FindGo("fakeBox");
	fakeBox->SetActive(true);

	gameEnd = false;
	Scene::Enter();

}

void SceneBattle::Exit()
{
	Scene::Exit();

	listMove = false;
	//userMove = false;
	trigger1 = false;
	trigger2 = false;
	//aniPlay = false;
	menuDisplay = false;
	menuIndex = 0;
	skillIndex = 0;
	SpriteGo* user = (SpriteGo*)FindGo("User");
	user->SetActive(false);
	SpriteGo* mymonster = (SpriteGo*)FindGo("myMonster");
	mymonster->SetActive(false);
	SpriteGo* select = (SpriteGo*)FindGo("Select");
	select->SetActive(false);
	
	
	SpriteGo* effectBall = (SpriteGo*)FindGo("Effect");
	effectBall->SetActive(true);
	/*TextGo* SkillMessage1 = (TextGo*)FindGo("SkillMessage1");
	TextGo* SkillMessage2 = (TextGo*)FindGo("SkillMessage2");
	TextGo* SkillMessage3 = (TextGo*)FindGo("SkillMessage3");
	TextGo* SkillMessage4 = (TextGo*)FindGo("SkillMessage4");
	TextGo* SkillExplain = (TextGo*)FindGo("SkillExplain");
	TextGo* SkillText = (TextGo*)FindGo("SkillText");
	SkillMessage1->SetActive(false);
	SkillMessage2->SetActive(false);
	SkillMessage3->SetActive(false);
	SkillMessage4->SetActive(false);
	SkillExplain->SetActive(false);
	SkillText->SetActive(false);*/


}

void SceneBattle::Update(float dt)
{
	Scene::Update(dt);
	
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos(); //마우스 위치
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	if (!gameEnd) 
	{

		//std::cout << menuIndex << std::endl;
		//test code

		SpriteGo* list = (SpriteGo*)FindGo("List");
		list->SetOrigin(Origins::TR);
		SpriteGo* mymonster = (SpriteGo*)FindGo("myMonster");
		SpriteGo* effectBall = (SpriteGo*)FindGo("Effect");
		SpriteGo* user = (SpriteGo*)FindGo("User");
		SpriteGo* HpBar = (SpriteGo*)FindGo("HpBar");
		//SpriteGo* list = (SpriteGo*)FindGo("List");
		
		if (!listMove) //처음 몬스터 이미지 움직임
		{
			list->sprite.move(4.f, 0);
			clock.restart();
		}
		if (list->sprite.getPosition().x == windowSize.x)
		{
			list->sprite.move(0.f, 0.f);
			//list->SetPosition()
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
			//list->SetPosition()
			userMove = true;

		}
		if (listMove)
		{
			RectangleGo* pokemonHealth = (RectangleGo*)FindGo("healthBar");
			SpriteGo* realHpBar = (SpriteGo*)FindGo("RealHpBar");

			pokemonHealth->SetActive(true);
			realHpBar->SetActive(true);
			HpBar->SetActive(true);
		}
		//if (clock.getElapsedTime() > interfaceTime)
		{
			if (userMove && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
			{
				
				userMove = false;
				//user->sprite.move(-5.f, 0.f);
				//user->SetActive(false);
			}

		}
		std::cout << user->sprite.getPosition().x << std::endl;
		//std::cout << -user->sprite.getScale().x << std::endl;
		//std::cout << -user->sprite.getScale().x << std::endl;
		/*std::cout << -windowSize.x << std::endl;*/
		if (user->GetActive() && user->sprite.getPosition().x <= -400)
		{
			user->SetActive(false);
		}
		if (!user->GetActive() && !aniPlay)
		{
 			animation.Play("MonsterBallEffect");
			
			std::cout << "실행했다." << std::endl;
			aniPlay = true;
			clock.restart();
		}

		if (aniPlay && clock.getElapsedTime() > sf::seconds(0.4f))
		{
			effectBall->SetActive(false);
		}
		if (!effectBall->GetActive())
		{
			mymonster->SetActive(true);
		}
		if (mymonster->GetActive())
		{
			Battle(dt);
			if (!trigger1)
			{
				MoveCursorMenu();
			}
			if (trigger1)
			{
				SelectMenu();
			}
			if (!trigger2)
			{
				MoveCursorSkill();
				clock2.restart();
			}
			if (trigger2 && (clock2.getElapsedTime() > sf::seconds(0.5f)))
			{
				std::cout << "적체력깎음" << std::endl;

				if (healthBar.x <= 0)
				{
					damage = 0;
				}
				else {
					damage = 150;
				}
				healthBar.x -= damage * dt;
				RectangleGo* pokemonHealth = (RectangleGo*)FindGo("healthBar");
				pokemonHealth->rectangle.setSize(healthBar);
				if (healthBar.x < 265 &&
					healthBar.x > 106)
				{
					pokemonHealth->rectangle.setFillColor({ 234,157,40 });
				}
				else if (healthBar.x < 106 &&
					healthBar.x > 0)
				{
					pokemonHealth->rectangle.setFillColor(sf::Color::Red);
				}
				else if (healthBar.x <= 0)
				{
					healthBar.x = 0;
					//damage = 0;

					list->sprite.move(0.f, 5.f);

				}

				

			}
			if (list->sprite.getPosition().y >= windowSize.y)
			{
				std::cout << "탈출포인트 여기 지났다" << std::endl;
				BattleEnd();
				gameEnd = true;
			}

		}


		
	}
	animation.Update(dt);
	//test code
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
		//BattleEnd();
	}
	//ui view 좌표 확ㅇ니
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << mousePos.x << "," << mousePos.y << std::endl;
	}
	//MoveCursorMenu();

}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneBattle::Battle(float dt)
{
	//timer += dt;
	//int turn = 0;
	//RectangleGo* pokemonHealth = (RectangleGo*)FindGo("healthBar");
	SpriteGo* menu = (SpriteGo*)FindGo("Menu");
	menu->sprite.setScale(1.65f, 1.38f);
	menu->SetPosition(700, 600);
	menu->sortLayer = 205;
	menu->SetActive(true);

	RectangleGo* fakeBox = (RectangleGo*)FindGo("fakeBox");
	fakeBox->SetActive(false);

	SpriteGo* selectIcon = (SpriteGo*)FindGo("Select");
	selectIcon->sprite.setScale(10.f, 10.f);
	selectIcon->sprite.setPosition(selectFirstPos);
	selectIcon->sortLayer = 210;
	selectIcon->SetActive(true);
	//PlayerMenu();
	MenuText();
	//if (clock.getElapsedTime() > sf::seconds(0.4f)) {}
//	pokemonHealth
}

//void SceneBattle::PlayerMenu()
//{
//
//	SpriteGo* menu = (SpriteGo*)FindGo("Menu");
//	menu->SetActive(true);
//	menu->sprite.setScale(1.65f, 1.38f);
//	menu->SetPosition(700, 600);
//	menu->sortLayer = 205;
//
//	SpriteGo* selectIcon = (SpriteGo*)FindGo("Select");
//	selectIcon->sprite.setScale(10.f, 10.f);
//	selectIcon->sprite.setPosition(selectFirstPos);
//	selectIcon->SetActive(true);
//	selectIcon->sortLayer = 210;
//	//if (!menuSelect)
//	MenuText();
//	
//
//	
//	//std::cout << "여기지나감." << std::endl;
//	/*TextGo* menuText1 = (TextGo*)FindGo("menuMessage1");
//	std::wstring attack = stringTable->GetUni("ATTACK", Languages::KOR);
//	menuText1->text.setCharacterSize(70);
//	menuText1->text.setString(attack);
//	menuText1->text.setFillColor(sf::Color::Black);
//	menuText1->SetOrigin(Origins::TL);
//	menuText1->SetPosition(896,675);
//	menuText1->sortLayer = 207;
//	TextGo* menuText2 = (TextGo*)FindGo("menuMessage2");
//	std::wstring myPokemon = stringTable->GetUni("POKEMON", Languages::KOR);
//	menuText2->text.setCharacterSize(70);
//	menuText2->text.setString(myPokemon);
//	menuText2->text.setFillColor(sf::Color::Black);
//	menuText2->SetOrigin(Origins::TL);
//	menuText2->SetPosition(1350, 675);
//	menuText2->sortLayer = 207;
//	TextGo* menuText3 = (TextGo*)FindGo("menuMessage3");
//	std::wstring myBag = stringTable->GetUni("BAG", Languages::KOR);
//	menuText3->text.setCharacterSize(70);
//	menuText3->text.setString(myBag);
//	menuText3->text.setFillColor(sf::Color::Black);
//	menuText3->SetOrigin(Origins::TL);
//	menuText3->SetPosition(896, 850);
//	menuText3->sortLayer = 207;
//	TextGo* menuText4 = (TextGo*)FindGo("menuMessage4");
//	std::wstring run = stringTable->GetUni("RUN", Languages::KOR);
//	menuText4->text.setCharacterSize(70);
//	menuText4->text.setString(run);
//	menuText4->text.setFillColor(sf::Color::Black);
//	menuText4->SetOrigin(Origins::TL);
//	menuText4->SetPosition(1350, 850);
//	menuText4->sortLayer = 207;*/
//
//}



void SceneBattle::MenuText()
{
	//기본으로 보여줄 메뉴들
	if (!menuDisplay) {

		StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
		TextGo* menuText1 = (TextGo*)FindGo("menuMessage1");
		std::wstring attack = stringTable->GetUni("ATTACK", Languages::KOR);
		menuText1->text.setCharacterSize(70);
		menuText1->text.setString(attack);
		menuText1->text.setFillColor(sf::Color::Black);
		menuText1->SetOrigin(Origins::TL);
		menuText1->SetPosition(textFirstPos);
		menuText1->sortLayer = 207;
	
		TextGo* menuText2 = (TextGo*)FindGo("menuMessage2");
		std::wstring myPokemon = stringTable->GetUni("POKEMON", Languages::KOR);
		menuText2->text.setCharacterSize(70);
		menuText2->text.setString(myPokemon);
		menuText2->text.setFillColor(sf::Color::Black);
		menuText2->SetOrigin(Origins::TL);
		menuText2->SetPosition(textFirstPos.x+454, textFirstPos.y);
		menuText2->sortLayer = 207;
		TextGo* menuText3 = (TextGo*)FindGo("menuMessage3");
		std::wstring myBag = stringTable->GetUni("BAG", Languages::KOR);
		menuText3->text.setCharacterSize(70);
		menuText3->text.setString(myBag);
		menuText3->text.setFillColor(sf::Color::Black);
		menuText3->SetOrigin(Origins::TL);
		menuText3->SetPosition(textFirstPos.x, textFirstPos.y+170);
		menuText3->sortLayer = 207;
		TextGo* menuText4 = (TextGo*)FindGo("menuMessage4");
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
		//menuIndex = 0;
		menuDisplay = true;
		std::cout << "여디야" << std::endl;
	}
	if (menuDisplay&&!trigger1) {
		trigger1 = true;
	}
	/*if (menuIndex == 0)
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
		selectIcon->sprite.setPosition(selectFirstPos.x + 454.f, selectFirstPos.y+175.f);
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Left))
		{
			menuIndex--;
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
		{
			menuIndex--;
			menuIndex--;
		}
	}*/
}

void SceneBattle::SelectMenu()
{
	//MoveCursorMenu();

	//if(INPUT_MGR.GetKeyUp(sf::Keyboard::Enter)){
		switch (menuIndex)
		{
		case (int)Menu::Skill:
			SkillSelect();
			
			break;
		case (int)Menu::Bag:
			SkillSelect();
			break;
		case (int)Menu::Pokemon:
			SkillSelect();
			break;
		case (int)Menu::Run:
			BattleEnd();
			break;
		}
	//}

	
}

void SceneBattle::SkillSelect()
{
	if (menuDisplay) {
		StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);

	
		TextGo* menuText1 = (TextGo*)FindGo("menuMessage1");
		std::wstring skill1 = stringTable->GetUni("THUNDER", Languages::KOR);
		menuText1->text.setCharacterSize(70);
		menuText1->text.setString(skill1);
		menuText1->text.setFillColor(sf::Color::Black);
		menuText1->SetOrigin(Origins::TL);
		menuText1->SetPosition(textFirstPos);
		menuText1->sortLayer = 207;

		TextGo* menuText2 = (TextGo*)FindGo("menuMessage2");
		std::wstring skill2 = stringTable->GetUni("SPEED_ATTACK", Languages::KOR);
		menuText2->text.setCharacterSize(70);
		menuText2->text.setString(skill2);
		menuText2->text.setFillColor(sf::Color::Black);
		menuText2->SetOrigin(Origins::TL);
		menuText2->SetPosition(textFirstPos.x + 454, textFirstPos.y);
		menuText2->sortLayer = 207;
		TextGo* menuText3 = (TextGo*)FindGo("menuMessage3");
		std::wstring skill3 = stringTable->GetUni("TENMILLIONBOLT", Languages::KOR);
		menuText3->text.setCharacterSize(70);
		menuText3->text.setString(skill3);
		menuText3->text.setFillColor(sf::Color::Black);
		menuText3->SetOrigin(Origins::TL);
		menuText3->SetPosition(textFirstPos.x, textFirstPos.y + 170);
		menuText3->sortLayer = 207;
		TextGo* menuText4 = (TextGo*)FindGo("menuMessage4");
		std::wstring skill4 = stringTable->GetUni("IRONTAIL", Languages::KOR);
		menuText4->text.setCharacterSize(70);
		menuText4->text.setString(skill4);
		menuText4->text.setFillColor(sf::Color::Black);
		menuText4->SetOrigin(Origins::TL);
		menuText4->SetPosition(textFirstPos.x + 454, textFirstPos.y + 170);
		menuText4->sortLayer = 207;
	


	}

	if (!trigger2&&INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		trigger2 = true;
		std::cout << "Trigger2는 거짓" << std::endl;
		//SkillExplain(SetSkill());
	}
	if(trigger2)
	{
		std::cout << "Trigger2는 참" << std::endl;
		SetSkill();
	}
}

void SceneBattle::SetSkill()
{
	std::cout << "setSkill을 들어옴" << std::endl;
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter)) 
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

}

void SceneBattle::SkillExplain(int n)
{
	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
	
	SpriteGo* menu = (SpriteGo*)FindGo("ExplainMenu");
	menu->SetActive(true);
	//menu->sprite.setColor(sf::Color::White);
	menu->sprite.setScale(1.5f, 1.38f);
	menu->SetPosition(900, 600);
	menu->sortLayer = 211;
	std::wstring useskill;
	TextGo* skillExplain = (TextGo*)FindGo("SkillExplain");
	std::wstring skill= stringTable->GetUni("SKILLEXPLAIN", Languages::KOR);
	skillExplain->text.setCharacterSize(40);
	skillExplain->text.setFillColor(sf::Color::Black);
	skillExplain->text.setString(skill);
	skillExplain->SetOrigin(Origins::TL);
	skillExplain->SetPosition(973,678);
	skillExplain->sortLayer = 212;
	skillExplain->SetActive(menu->GetActive());
	switch (n)
	{
	case 0:
		useskill = stringTable->GetUni("THUNDER", Languages::KOR);
		break;
	case 1:
		useskill = stringTable->GetUni("SPEED_ATTACK", Languages::KOR);
		break;
	case 2:
		useskill = stringTable->GetUni("TENMILLIONBOLT", Languages::KOR);
		break;
	case 3:
		useskill = stringTable->GetUni("IRONTAIL", Languages::KOR);
		break;
	}
	TextGo* skillText = (TextGo*)FindGo("SkillText");
	skillText->text.setCharacterSize(80);
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

void SceneBattle::MoveCursorMenu()
{
	SpriteGo* selectIcon = (SpriteGo*)FindGo("Select");
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
	/*if (INPUT_MGR.GetKeyUp(sf::Keyboard::Enter))
	{
		return menuIndex;
	}*/
}

void SceneBattle::MoveCursorSkill()
{
	SpriteGo* selectIcon = (SpriteGo*)FindGo("Select");
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
	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		return skillIndex;
	}*/
}