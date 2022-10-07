#pragma once
#include "value.h"

class Shape
{
public:
	Shape();
	virtual ~Shape();

protected:
	char base_shape_[4][4];
	Position pos_; // �������� �������� ���� ��ġ�� �����ϱ� ���� ����
	Position pivot_; // ������ ������(�� �������� �������� �ؼ� �������� ������ ������ �����.) ���� ȸ���� ���ؼ��� �ʿ�
	int width_count_; // ���� �������� ���� �Ʒ��� ������Ƿ�, ������ ���� ���̸� �˸� �������� ���� ������ ������ ������ �ʰ� ������ ������ �� �ִ�.

public:
	// 2���� �迭�� �迭 �� ��ü�� ��ȯ�ޱⰡ ��ƴ�. ���� �Ʒ��� ����
	// �迭�� ���Ҹ� ���ε��� �޴°� ���ϴ�.
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