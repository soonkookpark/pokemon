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
	AnimationController animation; //애니메이터 컨ㄹ트롤러를 만들어 스프라이트를 하나집어 현재 재생하고싶은 애니메이션의 프레임에 맞춰 좌표를 변경하는 기능을 넣었다. 사용을 어떻게하나 애니메이션 개체마다 초기화해야함. 애니메이션 클립들. 클립들을 추가해줘야겟지? 애드클립이 그걸하는거야
	// 가보면 인서트 하잕ㅎ아 init랑 쌍으로  animation클립에 잇는것들 확인
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
	sf::Vector2i playerTileIndex = (sf::Vector2i)(charPos/ 150.f); // 플레이어가 속한 타일의 인덱스

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

