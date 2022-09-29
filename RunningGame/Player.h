#pragma once

#include "value.h"

class Player
{
public:
	Player();
	~Player();

private:
	int x_;
	int y_;

public:
	void SetPos(int x, int y)
	{
		x_ = x;
		y_ = y;
	}

public:
	int GetX() { return x_; }
	int GetY() { return y_; }

public:
	bool Init();
	void Update();
};

