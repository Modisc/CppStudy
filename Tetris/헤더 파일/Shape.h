#pragma once
#include "value.h"

class Shape
{
public:
	Shape();
	virtual ~Shape();

protected:
	char base_shape_[4][4];
	Position pos_; // 스테이지 내에서의 도형 위치를 설정하기 위한 변수
	Position pivot_; // 도형의 기준점(이 기준점을 기준으로 해서 스테이지 내에서 도형을 출력함.) 도형 회전을 위해서도 필요
	int width_count_; // 도형 기준점이 왼쪽 아래를 잡았으므로, 도형의 가로 길이만 알면 스테이지 범위 밖으로 도형이 나가지 않게 범위를 설정할 수 있다.

public:
	// 2차원 배열은 배열 그 자체를 반환받기가 어렵다. 따라서 아래와 같이
	// 배열의 원소를 따로따로 받는게 편하다.
	char GetBlock(int x, int y) const
	{
		return base_shape_[y][x];
	}

	void SetPosition(int x, int y)
	{
		pos_.x = x;
		pos_.y = y;
	}

	void SetPosition(const Position& pos)
	{
		pos_ = pos;
	}

	Position GetPosition() const
	{
		return pos_;
	}

	Position GetPivot() const
	{
		return pivot_;
	}

public:
	virtual bool Init();

public:
	void Render();
	void RenderNext();
	bool MoveDown();
	void MoveLeft();
	void MoveRight();
};