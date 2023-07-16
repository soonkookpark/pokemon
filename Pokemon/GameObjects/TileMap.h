#pragma once
#include "VertexArrayGo.h"

struct Tile
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
};

class TileMap : public VertexArrayGo
{
protected:
	//sf::VertexArray vertexArray;
	sf::Vector2f tileSize = { 150.f, 150.f };
	sf::Vector2f texSize = { 150.f, 150.f };
public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);

	std::vector<Tile> tiles;
	sf::Vector2f TileSize();
	float TileXSize();
};

