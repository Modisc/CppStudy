#include "Core.h"
#include "StageManager.h"

Core* Core::instance = NULL;

Core::Core()
{
}

Core::~Core()
{
	StageManager::DestroyInstance();
}

bool Core::Init()
{
	if (!StageManager::GetInstance()->Init())
	{
		return false;
	}

	return true;
}

void Core::Run()
{
	StageManager::GetInstance()->Run();
}
