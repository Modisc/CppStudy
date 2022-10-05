#pragma once
#include "value.h"

class Core
{
public:
	bool Init();
	void Run();

private:
	int OutputMenu();

	DECLARE_SINGLE(Core)
};

