#pragma once
#include "value.h"

class Core
{
private:
	Core();
	~Core();

private:
	static Core* instance;

public:
	static Core* GetInstance()
	{
		if (!instance)
		{
			instance = new Core;
		}
		
		return instance;
	}

	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

private:
	HANDLE console_;
	bool loop_;

public:
	bool Init();
	void Run();
	void SetConsolePos(int x, int y);
	void End()
	{
		loop_ = false;
	}
};

