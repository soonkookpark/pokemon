#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "scene.h"

class TileMap;
class Player : public SpriteGo
{
public:
	struct ClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point;
	};

protected:
	AnimationController animation; //�ִϸ����� ����Ʈ�ѷ��� ����� ��������Ʈ�� �ϳ����� ���� ����ϰ���� �ִϸ��̼��� �����ӿ� ���� ��ǥ�� �����ϴ� ����� �־���. ����� ����ϳ� �ִϸ��̼� ��ü���� �ʱ�ȭ�ؾ���. �ִϸ��̼� Ŭ����. Ŭ������ �߰�����߰���? �ֵ�Ŭ���� �װ��ϴ°ž�
	// ������ �μ�Ʈ �ϟꤾ�� init�� ������  animationŬ���� �մ°͵� Ȯ��
	sf::Vector2f direction;
	float speed = 500.f;

	bool filpX = false;
	bool isGround = true;

	std::vector<ClipInfo> clipInfos;
	std::string resourceListPath1;
	ClipInfo currentClipInfo;
	TileMap* tilemap;
	sf::Vector2f charPos = { -2.5f * 150,19.5f * 150 };
	sf::FloatRect wallBounds;
	sf::Vector2f wallBoundsLT;
	sf::Vector2f wallBoundsRB;

	int tileScale = 0;
public:
	
	Player(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Player() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	bool GetFlipX() const;
	void SetFlipX(bool filp);
	sf::Vector2f GetDirection(int a);
	void SetWallBounds(const sf::FloatRect& bounds);
};

