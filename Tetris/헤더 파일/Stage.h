#pragma once
#include "value.h"

class Stage
{
private:
	Stage();
	~Stage();

private:
	friend class StageManager;

private:
	char stage_arr_[STAGE_HEIGHT][STAGE_WIDTH];
	int speed_;

public:
	int GetSpeed() const
	{
		return speed_;
	}

	void SetSpeed(int speed)
	{
		speed_ = speed;
	}

public:
	void AddBlock(class Shape* shape, const Position& pos);
	bool CheckBlock(int x, int y);

public:
	bool Init();
	void Render();
};

