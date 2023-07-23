#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player;
//struct Monster
//{
//	int x = 0;
//	int y = 0;
//	int texIndex = 0;
//};

class Monster : public SpriteGo
{
public:

	enum class Pokemons
	{
		Mew,
		MewTwo,
		Thunder,
		Dragonite,
		Evee,
		Pikachu,
		Psyduck,
		Chikorita,
		Gengar

	};

	static const int TotalMonster = 9;
protected:
	Pokemons name;
	std::string monName;
	int imagePosX = 0;
	int	imagePosY = 0;
	int maxHp = 0;
	int hp = 0;
	int power = 0;
	float catchRate = 0;
	//float meetRate = 0;
	std::string skill1;
	int skillDamage1=0;
	int pp1=0;
	std::string skill2;
	int skillDamage2=0;
	int pp2=0;
	std::string skill3;
	int skillDamage3=0;
	int pp3=0;
	std::string skill4;
	int skillDamage4=0;
	int pp4=0;
	int enemySize = 56;


public:
	Monster(const std::string textureId = "",const std::string & n = "");
	virtual ~Monster() override;

	virtual void Init() override;
	virtual void Release() override; 
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetType(Pokemons t);
	Pokemons GetType() const;
	int GetDamage();
	sf::Vector2i GetImageRectSize();
	std::string GetMonsterName();
};

