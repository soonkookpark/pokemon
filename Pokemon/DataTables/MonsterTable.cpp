#include "stdafx.h"
#include "rapidcsv.h"
#include "MonsterTable.h"

bool MonsterTable::Load()
{
	std::string fileName = "scripts/monsterData.csv";
	
	rapidcsv::Document doc(fileName);
	
	auto keys = doc.GetRow<std::string>(0);
	auto name = doc.GetColumn<std::string>(0);
	auto ids = doc.GetColumn<int>(1);
	auto imagePosX = doc.GetColumn<int>(2);
	auto imagePosY = doc.GetColumn<int>(3);
	auto maxHp = doc.GetColumn<float>(4);
	auto power = doc.GetColumn<int>(5);
	auto catchRate = doc.GetColumn<float>(6);
	//auto meetRate = doc.GetColumn<float>(8);
	auto skill1 = doc.GetColumn<std::string>(9);
	auto skillDamage1 = doc.GetColumn<int>(10);
	auto pp1 = doc.GetColumn<int>(11);
	auto skill2 = doc.GetColumn<std::string>(12);
	auto skillDamage2 = doc.GetColumn<int>(13);
	auto pp2 = doc.GetColumn<int>(14);
	auto skill3 = doc.GetColumn<std::string>(15);
	auto skillDamage3 = doc.GetColumn<int>(16);
	auto pp3 = doc.GetColumn<int>(17);
	auto skill4 = doc.GetColumn<std::string>(18);
	auto skillDamage4 = doc.GetColumn<int>(19);
	auto pp4 = doc.GetColumn<int>(20);

	for (int i = 0; i < ids.size(); ++i)
	{
		MonsterInfo mInfo
		{
			(Monster::Pokemons)ids[i],name[i],imagePosX[i],imagePosY[i],maxHp[i],power[i],catchRate[i]/*,meetRate[i]*/,skill1[i],skillDamage1[i],pp1[i],skill2[i],skillDamage2[i],pp2[i],skill3[i],skillDamage3[i],pp3[i],skill4[i],skillDamage4[i],pp4[i]
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
