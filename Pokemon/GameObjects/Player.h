#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "Scene.h"

class TileMap;
class SceneGame;
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
	float tileSize = 1600.f;
	int texInfo;

	int myDirLeft;
	int myDirRight;
	int myDirUp;
	int myDirDown;

	bool filpX = false;
	bool isGround = true;

	std::vector<ClipInfo> clipInfos;
	std::string resourceListPath1;
	ClipInfo currentClipInfo;
	TileMap* tilemap;
	sf::Vector2f charPos = { 18.5*150,38.5*150 };
	sf::FloatRect wallBounds;
	sf::Vector2f wallBoundsLT;
	sf::Vector2f wallBoundsRB;
	sf::Vector2f newPosition;
	sf::Vector2i playerTileIndex = (sf::Vector2i)(charPos/ 150.f); // �÷��̾ ���� Ÿ���� �ε���

	sf::FloatRect objBounds;
	sf::Vector2f objBoundsLT;
	sf::Vector2f objBOundsRB;
	SceneGame* sceneGame;
	int tileScale = 0;
	bool playerCanMove = false;
	bool move = false;


public:
	
	Player(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Player() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	bool GetFlipX() const;
	void SetFlipX(bool filp);
	sf::Vector2f GetDirection();
	void SetWallBounds(const sf::FloatRect& bounds);
	//void ObjBounds(const sf::FloatRect& bounds);
	//void PlayerMoveCheck();
	void SetSceneGame(SceneGame* scene) { sceneGame = scene; }
	bool ChangePlayerMove();
	bool GetPlayerMove();
	void PlayerMoveFind();
	int FindTileIndex();
	void FindTileInfo();
	bool CheckTileInfo(sf::Vector2f info);
};

