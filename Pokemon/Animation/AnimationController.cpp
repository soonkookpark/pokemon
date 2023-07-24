#include "stdafx.h"
#include "AnimationController.h"
#include "ResourceMgr.h"

void AnimationController::AddClip(AnimationClip& newClip)
{
	if (clips.find(newClip.id) == clips.end()) //�ʿ��� �˻��̷��� ��.
	{
		clips.insert({ newClip.id,&newClip });
	}
}

void AnimationController::Update(float dt)
{
	if (!isPlaying)
		return;

	accumTime +=dt * speed;
	if (accumTime < clipDuration)
		return;

	accumTime = 0.f;
	++currentFrame;//�������� ����Ǵ� ������.
	
	if (currentFrame == totalFrame)
	{
		if (!queue.empty()) //ť�� �Ⱥ��������
		{
			std::string id = queue.front(); //queue�� ��� �ֵ��� 1���� �����´�,
			queue.pop();
			Play(id, false);
			return;
		}
		else
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				return;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;
				break;
			}
		}
	}

	



	//if ((currentClip->frames[currentFrame]).action != nullptr)
	//{
	//	currentClip->frames[currentFrame].action();
	//}


	if (target != nullptr)
	{
		SetFrame(currentClip->frames[currentFrame]);
	}

}

void AnimationController::Play(const std::string& clipId, bool ClearQueue) //���⼭ �ϴ°� ������ִ� ������ �����Ѵ�. ����� �ִϸ��̼��� ������ ���缭. �׷��� ������ ���ְ� �������� �������ְ� �����ϰ��ִ������� ���� �������� ���̳� 
{
	if (ClearQueue)
	{
		while(!queue.empty())//queue�� ��������� ������������� pop �� ��Ŵ
			queue.pop();//���ִ� queue�� ��.
	}
	auto find = clips.find(clipId);// ���°��
	if (find == clips.end())	// ���°��
	{
		Stop();
		std::cout << "ERR: NotExist Clip" << std::endl;
		return;
	}

	isPlaying = true;
	currentClip = find->second;
	currentFrame = 0;
	totalFrame = (int)currentClip->frames.size();
	clipDuration = 1.f / currentClip->fps;
	accumTime = 0.f;


	SetFrame(currentClip->frames[currentFrame]);
}

void AnimationController::PlayQueue(const std::string& clipId)
{
	queue.push(clipId);
}

void AnimationController::Stop()
{
	isPlaying = false;
}

void AnimationController::SetFrame(const AnimationFrame& frame)
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture(frame.textureId);

	target->setTexture(*tex);
	target->setTextureRect(frame.texCoord);
}

std::string AnimationController::GetCurrentClipId()
{
	return currentClip->id;
}
