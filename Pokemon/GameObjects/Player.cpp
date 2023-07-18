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

	SetOrigin(Origins::MC);


	//clipInfos.push_back({ "IdleS", "MoveS", false, sf::Vector2f{direction.x,0 } });
	clipInfos.push_back({ "IdleB", "MoveB", true, {0.f, -1.f} });
	//clipInfos.push_back({ "IdleS", "MoveS", true, Utils::Normalize({ 1.f, -1.f }) });

	clipInfos.push_back({ "IdleS", "MoveS", false, {-1.f, 0.f} });
	clipInfos.push_back({ "IdleS", "MoveS", true, {1.f, 0.f} });

	//clipInfos.push_back({ "IdleS", "MoveS", false, Utils::Normalize({ -1.f, 1.f }) });
	clipInfos.push_back({ "IdleF", "MoveF", true,{0.f, 1.f} });
	//clipInfos.push_back({ "IdleS", "MoveS", true, Utils::Normalize({ 1.f, 1.f }) });

}

void Player::Reset()
{
	animation.Play("IdleF");
	SetOrigin(origin);
	SetPosition(charPos);
	SetFlipX(false);


	currentClipInfo = clipInfos[3];
}

void Player::Update(float dt)
{
	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Left)) 
	{
		direction.x = -100.f;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Right))
	{
		direction.x = 100.f;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
	{
		direction.y = 100.f;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
	{
		direction.y = -100.f;
	}*/
	
	tilemap = (TileMap*)sceneGame->FindGo("Tile Map");
	/*sf::Vector2f tilePos = GetPosition() / 150.f;
	sf::Vector2f tilePosLeft = { tilePos.x - 1.f, tilePos.y };
	sf::Vector2f tilePosRight = { tilePos.x + 1.f, tilePos.y };
	sf::Vector2f tilePosUp = { tilePos.x, tilePos.y -1.f};
	sf::Vector2f tilePosDown = { tilePos.x, tilePos.y +1.f};
	sf::Vector2f nextTileTextIndex;*/

	if (!playerCanMove) 
	{
		speed = 500.f;
		direction.x = INPUT_MGR.GetAxis(Axis::Horizontal);
		direction.y = INPUT_MGR.GetAxis(Axis::Vertical);
	}
	else if (playerCanMove)
	{
		direction.x = 0.f;
		direction.y = 0.f;
	}
		
	//이동
	//if (INPUT_MGR.GetAxis(Axis::Horizontal) || INPUT_MGR.GetAxis(Axis::Vertical))
	//{

	//	if (direction.x != 0.f || direction.y != 0.f)
	//	{
	//		// 다음 타일의 인덱스를 계산합니다.
	//		sf::Vector2i nextTilePos = (sf::Vector2i(GetPosition()) + sf::Vector2i(direction.x, direction.y))/150;

	//		// 이동 가능한 타일이면 플레이어 위치 업데이트
	//		if (tilemap->GetTile(nextTilePos.x, nextTilePos.y).texIndex == (int)TileInformation::Grass)
	//		{
	//			sf::Vector2f nextPos = sf::Vector2f(nextTilePos) * 150.f;
	//			SetPosition(nextPos);
	//		}
	//	}
	//}
	
	
	
	
	
	
	
	
	
	
	
	float magnitude = Utils::Magnitude(direction);


	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}
	if (!wallBounds.contains(position)||!objBounds.contains(position))
	{
		position = Utils::Clamp(position, wallBoundsLT, wallBoundsRB);
	}
	position += direction*speed * dt;
	SetPosition(position);
	
	/*SetPosition(position);*/

	//position += direction * speed * dt;
	//SetPosition(position);
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::LShift))
	//{
	//	speed *= 1.2f;
	//}
	//if (INPUT_MGR.GetKeyUp(sf::Keyboard::LShift))
	//{
	//	speed /= 1.2f;
	//}
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

	//std::cout <<&tilemap->GetVertexArray()<< std::endl;
	


	//std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;

	//위치 파악
	/*if (direction.x == 0.f && direction.y == 0.f)
	{
	}*/
	//FRAMEWORK.GetWindowSize()
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
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	//{
	//	//std::cout << playerTileIndex.x << "," << playerTileIndex.y << std::endl;
	//	int tileSize = tileMap->tiles.size();
	//	for (int i = 0; i < tileSize; i++)
	//	{

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
