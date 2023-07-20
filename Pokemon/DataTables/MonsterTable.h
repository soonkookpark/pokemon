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
    //float catchRate;
    float rate;

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

