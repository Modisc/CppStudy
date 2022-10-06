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

public:
	bool Init();
	void Run();
};

