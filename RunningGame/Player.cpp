#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Init()
{
	x_ = 0;
	y_ = 8;
	return true;
}

void Player::Update()
{
	// Ű �Է��� �޴´�.
	// GetAsyncKeyState �Լ��� Win32 API ���� �����Ǵ� Ű �Է� �Լ��̴�.
	// WŰ�� ������ �� �ٷ� �����ϰ� �ϱ� ���� 0x8000�� & ������ �Ͽ�
	// ������ ��� true�� ������ �ȴ�
	// �̰� �̷��� �������ִ�. ���߿� winAPI ��ﶧ ����� ����.
	if (GetAsyncKeyState('A') & 0x8000)
	{
		--x_;
		if (x_ < 0)
			x_ = 0;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		++x_;
		if (x_ >= 50)
			x_ = 49;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{

	}
}
