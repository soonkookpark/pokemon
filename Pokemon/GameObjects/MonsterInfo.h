#pragma once
#include "VertexArrayGo.h"

struct Monster
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
};


class MonsterInfo : public VertexArrayGo
{
public:
	sf::Vector2f tileSize = { 150.f, 150.f };
	sf::Vector2f texSize = { 150.f, 150.f };
public:
	MonsterInfo(const std::string& textureId = "", const std::string& n = "");
	virtual ~MonsterInfo() override;

	bool Load(const std::string& filePath);

	std::vector<Monster> monsterInfo;
	sf::Vector2f TileSize();
};

