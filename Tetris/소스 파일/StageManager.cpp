#include "StageManager.h"
#include "Stage.h"

StageManager* StageManager::instance = NULL;

StageManager::StageManager() : curr_stage_(NULL)
{
}

StageManager::~StageManager()
{
}

bool StageManager::Init()
{
	// 기본 스테이지를 생성한다.
	curr_stage_ = new Stage;

	if (!curr_stage_->Init())
	{
		return false;
	}
		

	return true;
}

void StageManager::Run()
{
	curr_stage_->Render();
}
