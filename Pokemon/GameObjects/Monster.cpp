#include "stdafx.h"
#include "Monster.h"
#include "ResourceMgr.h"
#include "DataTableMgr.h"
#include "SceneMgr.h"
#include "SceneBattle.h"
#include "MonsterTable.h"
Monster::Monster(const std::string textureId, const std::string& n)
	:SpriteGo(textureId,n)
{

}

Monster::~Monster()
{
}

void Monster::Init()
{
	SpriteGo::Init();
}

void Monster::Release()
{
	SpriteGo::Release();
}

void Monster::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;

}

void Monster::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Monster::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}


void Monster::SetType(Pokemons t)
{
	name = t;
	const MonsterInfo& info = DATATABLE_MGR.Get<MonsterTable>
		(DataTable::Ids::Monster)->Get(t);

	monName = info.name;
	imagePosX = info.imagePosX;
	imagePosY = info.imagePosY;
	maxHp = info.maxHp;
	power = info.power;
	catchRate = info.catchRate;
	//meetRate = info.rate;
	skill1 = info.skill1;
	skillDamage1 = info.skillDamage1;
	pp1 = info.pp1;
	skill2 = info.skill2;
	skillDamage2 = info.skillDamage2;
	pp2 = info.pp2;
	skill3 = info.skill3;
	skillDamage3 = info.skillDamage3;
	pp3 = info.pp3;
	skill4 = info.skill4;
	skillDamage4 = info.skillDamage4;
	pp4 = info.pp4;
}

Monster::Pokemons Monster::GetType() const
{
	return name;
}

int Monster::GetDamage()
{
	return power;
}

sf::Vector2i Monster::GetImageRectSize()
{
	return sf::Vector2i(imagePosX,imagePosY);
}


