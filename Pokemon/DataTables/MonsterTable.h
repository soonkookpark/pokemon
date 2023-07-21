#pragma once
#include "DataTable.h"
#include "Monster.h"

struct MonsterInfo
{
    Monster::Pokemons monsterName;
    std::string name;
    int imagePosX;
    int imagePosY;
    float maxHp;
    int power;
    float catchRate;
    //float rate;
    std::string skill1;
    int skillDamage1;
    int pp1;
    std::string skill2;
    int skillDamage2;
    int pp2;
    std::string skill3;
    int skillDamage3;
    int pp3;
    std::string skill4;
    int skillDamage4;
    int pp4;

};
class MonsterTable :
    public DataTable
{
protected:
    std::unordered_map<Monster::Pokemons, MonsterInfo> table;

public:
    MonsterTable() : DataTable(DataTable::Ids::Monster) {};
    virtual ~MonsterTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;

    const MonsterInfo& Get(Monster::Pokemons id) const;








};

