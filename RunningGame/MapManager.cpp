#include "MapManager.h"
#include "Stage.h"

MapManager* MapManager::map_manager_instance_ = NULL;

MapManager::MapManager()
{
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		stage_[i] = NULL;
	}
}

MapManager::~MapManager()
{
	// 스테이지 메모리 해제
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		SAFE_DELETE(stage_[i]);
	}
}

MapManager* MapManager::GetInstance()
{
	if (!map_manager_instance_)
		map_manager_instance_ = new MapManager;

	return map_manager_instance_;
}

void MapManager::DestroyInst()
{
	SAFE_DELETE(map_manager_instance_);
}

bool MapManager::Init()
{
	const char* stage_file[3] = { "Stage1.txt", "Stage2.txt", "Stage3.txt" };
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		stage_[i] = new Stage;

		if (!stage_[i]->Init(stage_file[i]))
			return false;
	}

	return true;
}

void MapManager::Run()
{
}

void MapManager::Render()
{
	stage_[0]->Render();
}
