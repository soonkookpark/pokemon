#pragma once

enum class AnimationLoopTypes
{
	Single,	//�ѹ��� ���
	Loop,	// ����
};

struct AnimationFrame 
{
	std::string textureId;
	sf::IntRect	texCoord;//floatRect�� �ְ� �̳� �ִ�.
	//std::function<void()> action/*= nullptr*/;//Ư���� �������� �����Ҷ� ȣ���� �Լ��� �ִ°ž� �̰� �׸��� �ʱ�ȭ�ؾ���.
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;//�ִϸ��̼��̺�Ʈ
	AnimationLoopTypes loopType;
	int fps;

	bool LoadFromFile(const std::string path);

	//AnimationClip(const AnimationClip& other) = delete;
};

