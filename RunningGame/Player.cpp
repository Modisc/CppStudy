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
	// 키 입력을 받는다.
	// GetAsyncKeyState 함수는 Win32 API 에서 제공되는 키 입력 함수이다.
	// W키를 눌렀을 때 바로 반응하게 하기 위해 0x8000과 & 연산을 하여
	// 눌렀을 경우 true가 나오게 된다
	// 이건 이렇게 정해져있다. 나중에 winAPI 배울때 제대로 배운다.
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
