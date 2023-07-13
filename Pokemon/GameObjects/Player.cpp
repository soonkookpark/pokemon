#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
void Player::Init()
{
	
	/*RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleS.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleF.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleB.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/moveS.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/moveF.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/moveB.csv");*/

	//���� �����
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleS.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleF.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleB.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/moveS.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/moveF.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/moveB.csv"));


	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);


	clipInfos.push_back({ "IdleS", "MoveS", false, Utils::Normalize({ -1.f, -1.f }) });
	clipInfos.push_back({ "IdleB", "MoveB", true, {0.f, -1.f} });
	clipInfos.push_back({ "IdleS", "MoveS", true, Utils::Normalize({ 1.f, -1.f }) });

	clipInfos.push_back({ "IdleS", "MoveS", false, {-1.f, 0.f} });
	clipInfos.push_back({ "IdleS", "MoveS", true, {1.f, 0.f} });

	clipInfos.push_back({ "IdleS", "MoveS", false, Utils::Normalize({ -1.f, 1.f }) });
	clipInfos.push_back({ "IdleF", "MoveF", true,{0.f, 1.f} });
	clipInfos.push_back({ "IdleS", "MoveS", true, Utils::Normalize({ 1.f, 1.f }) });
}

void Player::Reset()
{
	animation.Play("IdleF");
	SetOrigin(origin);
	SetPosition({ 0, 0 });
	SetFlipX(false);

	currentClipInfo = clipInfos[6];
}

void Player::Update(float dt)
{
	//�̵�
	direction.x = INPUT_MGR.GetAxis(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxis(Axis::Vertical);
	float magnitude = Utils::Magnitude(direction);
	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}

	position += direction * speed * dt;
	SetPosition(position);

	if (direction.x != 0.f || direction.y != 0.f)
	{
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(),
			[this](const ClipInfo& lhs, const ClipInfo& rhs) {
				return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction);
			});
		currentClipInfo = *min;
	}

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
	//��ġ �ľ�
	if (direction.x == 0.f && direction.y == 0.f)
	{
		std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;
	}
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
sf::Vector2f Player::GetDirection(int a)
{
	if (a == 1)
		return { direction.x,0 };
	if (a == 2)
		return { 0,direction.y };
	if (a == 3)
		return { direction.x,direction.y };
}