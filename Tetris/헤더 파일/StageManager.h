#pragma once
#include "value.h"

class StageManager
{
private:
	StageManager();
	~StageManager();

private:
	static StageManager* instance;

public:
	static StageManager* GetInstance()
	{
		if (!instance)
		{
			instance = new StageManager;
		}

		return instance;
	}

	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

private:
	class Stage* curr_stage_;

public:
	class Stage* GetCurrentStage() const
	{
		return curr_stage_;
	}

public:
	bool Init();
	void Run();
};

