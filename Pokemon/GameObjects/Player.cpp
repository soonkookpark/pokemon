#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "TileMap.h"
#include "SceneGame.h"
void Player::Init()
{
	
	/*RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleS.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleF.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleB.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/moveS.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/moveF.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/moveB.csv");*/

	//파일 입출력
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleS.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleF.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleB.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/moveS.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/moveF.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/moveB.csv"));
	animation.SetTarget(&sprite);

	tilemap = (TileMap*)sceneGame->FindGo("Tile Map");

	SetOrigin(Origins::MC);


	//clipInfos.push_back({ "IdleS", "MoveS", false, sf::Vector2f{direction.x,0 } });
	clipInfos.push_back({ "IdleB", "MoveB", true, {0.f, -1.f} });
	//clipInfos.push_back({ "IdleS", "MoveS", true, Utils::Normalize({ 1.f, -1.f }) });

	clipInfos.push_back({ "IdleS", "MoveS", false, {-1.f, 0.f} });
	clipInfos.push_back({ "IdleS", "MoveS", true, {1.f, 0.f} });

	//clipInfos.push_back({ "IdleS", "MoveS", false, Utils::Normalize({ -1.f, 1.f }) });
	clipInfos.push_back({ "IdleF", "MoveF", true,{0.f, 1.f} });
	//clipInfos.push_back({ "IdleS", "MoveS", true, Utils::Normalize({ 1.f, 1.f }) });
	//SetPosition(charPos);
	playerTileIndex = (sf::Vector2i)(charPos / 150.f);
}

void Player::Reset()
{
	animation.Play("IdleF");
	SetOrigin(origin);
	//SetPosition(charPos);
	SetFlipX(false);


	currentClipInfo = clipInfos[3];
}

void Player::Update(float dt)
{
	//FindTileIndex();
	//tilemap = (TileMap*)sceneGame->FindGo("Tile Map");
	
	
	
	/*{

			if (tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y)
			{
	if (tilemap->tiles[i].texIndex != 30)
	{
		std::cout << "여긴 바닥이 아니야" << std::endl;
		std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;
		if (player->GetDirection() == )
			player->SetPosition(playerTileIndex.x * 150.f + 225.f, playerTileIndex.y * 150.f + 75.f);
		std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;*/


	//}
	//	int tileSize = tileMap->tiles.size();
	//	for (int i = 0; i < tileSize; i++)
	//	{
	/*sf::Vector2f tilePos = GetPosition() / 150.f;
	sf::Vector2f tilePosLeft = { tilePos.x - 1.f, tilePos.y };
	sf::Vector2f tilePosRight = { tilePos.x + 1.f, tilePos.y };
	sf::Vector2f tilePosUp = { tilePos.x, tilePos.y -1.f};
	sf::Vector2f tilePosDown = { tilePos.x, tilePos.y +1.f};
	sf::Vector2f nextTileTextIndex;*/

	if (!playerCanMove) 
	{

		PlayerMoveFind();
		
	}
	else if (playerCanMove)
	{
		direction.x = 0.f;
		direction.y = 0.f;
	}
		
	float magnitude = Utils::Magnitude(direction);


	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}
	if (!wallBounds.contains(position)||!objBounds.contains(position))
	{
		position = Utils::Clamp(position, wallBoundsLT, wallBoundsRB);
	}
	
	if (direction.x != 0.f || direction.y != 0.f)
	{
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(),
			[this](const ClipInfo& lhs, const ClipInfo& rhs) {
				return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction);
			});
		currentClipInfo = *min;
	}
	//PlayerMoveCheck();
	std::string clipId = magnitude == 0.f ? currentClipInfo.idle : currentClipInfo.move;
	if (GetFlipX() != currentClipInfo.flipX)
	{
		SetFlipX(currentClipInfo.flipX);
	}

	if (animation.GetCurrentClipId() != clipId)
	{
		animation.Play(clipId);
	}

	animation.Update(dt);

	
}

bool Player::GetFlipX() const
{
	return filpX;
}

void Player::SetFlipX(bool filp)
{
	filpX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
	
}
sf::Vector2f Player::GetDirection()
{
	return direction;
}

bool Player::GetPlayerMove()
{
	return playerCanMove;
}

void Player::PlayerMoveFind()
{
	//sf::Vector2i playerTileIndex = (sf::Vector2i)(GetPosition() / 150.f); // 플레이어가 속한 타일의 인덱스
	//1. 갈곳의 좌표를찾는다.
	//2. 좌표의 texIndex를 검사한다.
	//3. 문제가 없을경우 이동한다.
	if (!move)
	{
		myDirLeft = (playerTileIndex.x)-1;
		myDirRight = playerTileIndex.x + 1;
		myDirUp = playerTileIndex.y - 1;
		myDirDown = playerTileIndex.y + 1;
		move = true;
		//std::cout << myDirLeft<< std::endl;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Left)&& direction == sf::Vector2f{0, 0})
	{
		if (CheckTileInfo({ (float)playerTileIndex.x - 1, (float)playerTileIndex.y }))
			direction.x = -1;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Right) && direction == sf::Vector2f{0, 0})
	{
		if (CheckTileInfo({ (float)playerTileIndex.x + 1, (float)playerTileIndex.y }))
			direction.x = 1.f;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up) && direction == sf::Vector2f{0, 0})
	{
		if (CheckTileInfo({ (float)playerTileIndex.x, (float)playerTileIndex.y - 1 }))
			direction.y = -1.f;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down) && direction == sf::Vector2f{0, 0})
	{
		if (CheckTileInfo({ (float)playerTileIndex.x, (float)playerTileIndex.y + 1 }))
			direction.y = 1.f;
		
	}
	
	if (direction == sf::Vector2f{0,0})
	{
		move = false;
	}
	if (myDirLeft * 150+75== (int)charPos.x)
	{
		direction.x = 0;
		std::cout << "저기" << std::endl;
		move = false;
	}
	if (myDirRight * 150 + 75 == (int)charPos.x)
	{
		direction.x = 0;
		std::cout << "저기" << std::endl;
		move = false;
	}
	if (myDirUp * 150 + 75 == (int)charPos.y)
	{
		direction.y = 0;
		std::cout << "저기" << std::endl;
		move = false;
	}
	if (myDirDown * 150 + 75 == (int)charPos.y)
	{
		direction.y= 0;
		std::cout << "저기" << std::endl;
		move = false;
	}
	
	charPos += direction;
	SetPosition(charPos);
	FindTileInfo();

	
}

int Player::GetScore()
{
	return score;
}

void Player::ScoreUp()
{
	score++;
}

int Player::GetLife()
{
	return playerLife;
}

void Player::LifeDown()
{
	playerLife--;
}

void Player::FindTileInfo()
{
	int tileSize = tilemap->tiles.size();
	playerTileIndex = (sf::Vector2i)(charPos / 150.f);
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == playerTileIndex.x && tilemap->tiles[i].y == playerTileIndex.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);
			if (texIndex != static_cast<int>(TileInformation::Grass) &&
				texIndex != static_cast<int>(TileInformation::GrassFlowerHalf) &&
				texIndex != static_cast<int>(TileInformation::GrassHigh) &&
				texIndex != static_cast<int>(TileInformation::GrassLow) &&
				texIndex != static_cast<int>(TileInformation::Floor)/* &&
				texIndex != (int)(TileInformation::Carpet)*/)
			{
				//std::cout << "여긴 바닥이 아니야" << std::endl;
				/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
				{
					(int)tileMap->tiles[i].texIndex;
					player->ChangePlayerMove();
					battleNow = false;
				}*/
					//std::cout << texIndex << std::endl;

				if (direction.x < 0)
					direction.x = 0;
				//player->SetPosition(playerTileIndex.x * 150.f/* + 150.f*/, player->GetPosition().y);
				if (direction.x > 0)
					direction.x = 0;
				//player->SetPosition(playerTileIndex.x * 150.f, player->GetPosition().y);
				if (direction.y < 0)
					direction.y = 0; //player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150 /*+ 150*/);

				if (direction.y > 0)
					direction.y = 0;
				//player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150);
				//std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;


			}
		}
	}
}

bool Player::CheckTileInfo(sf::Vector2f info)
{
	int tileSize = tilemap->tiles.size();
	playerTileIndex = (sf::Vector2i)(charPos / 150.f);
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == info.x && tilemap->tiles[i].y == info.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);
			if (texIndex != static_cast<int>(TileInformation::Grass) &&
				texIndex != static_cast<int>(TileInformation::GrassFlowerHalf) &&
				texIndex != static_cast<int>(TileInformation::GrassHigh) &&
				texIndex != static_cast<int>(TileInformation::GrassLow) &&
				texIndex != static_cast<int>(TileInformation::Floor) /*&&
				texIndex != (int)(TileInformation::Carpet)*/)
			{
				//std::cout << "여긴 바닥이 아니야" << std::endl;
				/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
				{
					(int)tileMap->tiles[i].texIndex;
					player->ChangePlayerMove();
					battleNow = false;
				}*/
				//std::cout << texIndex << std::endl;

				//if (direction.x < 0)
				//	direction.x = 0;
				////player->SetPosition(playerTileIndex.x * 150.f/* + 150.f*/, player->GetPosition().y);
				//if (direction.x > 0)
				//	direction.x = 0;
				////player->SetPosition(playerTileIndex.x * 150.f, player->GetPosition().y);
				//if (direction.y < 0)
				//	direction.y = 0; //player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150 /*+ 150*/);
				//if (direction.y > 0)
				//	direction.y = 0;
				//player->SetPosition(player->GetPosition().x, playerTileIndex.y * 150);
				//std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;

				return 0;
			}
			return 1;
		}
	}
}

bool Player::ChangePlayerMove()
{
	playerCanMove = !playerCanMove;

	return playerCanMove;
}

void Player::SetWallBounds(const sf::FloatRect& bounds)
{
	sf::Vector2f halfSize = { sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 };
	
	wallBounds = bounds;

	wallBoundsLT = { wallBounds.left + halfSize.x,
		wallBounds.top + halfSize.y };
	wallBoundsRB = { wallBounds.left - halfSize.x + wallBounds.width,
		wallBounds.top - halfSize.y + wallBounds.height };
}

//void Player::PlayerMoveCheck()
//{
	//tilemap = (TileMap*)Go("Tile Map");
	//sf::Vector2i playerTileIndex = (sf::Vector2i)(GetPosition() / 150.f); // 플레이어가 속한 타일의 인덱스
	//std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	

	//		if (tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y)
	//		{
	//if (tilemap->tiles[i].texIndex != 30)
	//{
	//	//std::cout << "여긴 바닥이 아니야" << std::endl;
	//	std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;
	//	if (player->GetDirection() == )
	//		player->SetPosition(playerTileIndex.x * 150.f + 225.f, playerTileIndex.y * 150.f + 75.f);
	//	std::cout << player->GetPosition().x << "," << player->GetPosition().y << std::endl;


	//}
//}

//void Player::ObjBounds(const sf::FloatRect& bounds)
//{
//	sf::Vector2f halfSize = { sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 };
//
//	wallBounds = bounds;
//
//	wallBoundsLT = { wallBounds.left + halfSize.x,
//		wallBounds.top + halfSize.y };
//	wallBoundsRB = { wallBounds.left - halfSize.x + wallBounds.width,
//		wallBounds.top - halfSize.y + wallBounds.height };
//}