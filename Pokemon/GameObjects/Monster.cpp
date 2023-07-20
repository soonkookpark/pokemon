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
	meetRate = info.rate;
}

Monster::Pokemons Monster::GetType() const
{
	return name;
}

int Monster::GetDamage()
{
	return power;
}
