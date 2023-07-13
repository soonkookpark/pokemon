#pragma once
class AnimationController
{

protected:
	std::unordered_map<std::string/*ID*/, AnimationClip> clips;
	std::queue<std::string> queue; //�ִϸ��̼� ť.





	float speed = 1.f; // �ִϸ��̼� ��� ���� 2�� 2������� �����基������
	bool isPlaying = false;

	AnimationClip* currentClip = nullptr;
	int currentFrame = -1;
	int totalFrame = 0;
	float clipDuration = 0.f; //�� �����Ӵ� �󸶳� �������
	float accumTime = 0.f; //Ÿ�̸� �󸶳� �ð��� ��������~ Ŭ������������ �����ϰ� �������


	sf::Sprite* target = nullptr;

public:
	void AddClip(const AnimationClip& newClip);
	void SetTarget(sf::Sprite* sprite) { target = sprite; }
	sf::Sprite* GetTarget() const { return target; }
	bool IsPlaying() { return isPlaying; }
	void SetSpeed(float s) { speed = s; }
	float Speed() const { return speed; }

	void Update(float dt);

	void Play(const std::string& clipId, bool ClearQueue = true);
	void PlayQueue(const std::string& clipId);

	void Stop();

	void SetFrame(const AnimationFrame& frame);
	std::string GetCurrentClipId();
};

