#include "stdafx.h"
#include "rapidcsv.h"
#include "MonsterTable.h"

bool MonsterTable::Load()
{
	std::string fileName = "tables/monsterData.csv";
	
	rapidcsv::Document doc(fileName);
	
	auto keys = doc.GetRow<std::string>(0);
	auto name = doc.GetColumn<std::string>(0);
	auto ids = doc.GetColumn<int>(1);
	auto imagePosX = doc.GetColumn<int>(2);
	auto imagePosY = doc.GetColumn<int>(3);
	auto maxHp = doc.GetColumn<float>(4);
	auto power = doc.GetColumn<int>(6);
	auto meetRate = doc.GetColumn<float>(9);

	for (int i = 0; i < ids.size(); ++i)
	{
		MonsterInfo mInfo
		{
			(Monster::Pokemons)ids[i],name[i],imagePosX[i],imagePosY[i],maxHp[i],power[i],meetRate[i]
		};
		table.insert({ (Monster::Pokemons)ids[i] , mInfo });
	}
	return true;
}

void MonsterTable::Release()
{
	table.clear();
}

const MonsterInfo& MonsterTable::Get(Monster::Pokemons id) const
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "ERR: Failed to MonsterTable Load" << std::endl;
		exit(-1);
	}
	return find->second;
	
}
