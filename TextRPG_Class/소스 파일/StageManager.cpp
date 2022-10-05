#include "StageManager.h"
#include "StageEasy.h"
#include "StageNormal.h"
#include "StageHard.h"

DEFINITION_SINGLE(StageManager)



StageManager::StageManager()
{

}

StageManager::~StageManager()
{
	// 벡터 내부에 있는 값 모두 삭제
	SafeDeleteVecList(vec_stage_);
}

bool StageManager::Init()
{
	if (!CreateStage(StageType::easy))
		return false;
	if (!CreateStage(StageType::normal))
		return false;
	if (!CreateStage(StageType::hard))
		return false;

	return true;
}

void StageManager::Run()
{

}

bool StageManager::CreateStage(StageType type)
{
	Stage* stage = NULL;

	switch (type)
	{
	case StageType::easy:
		stage = new StageEasy;
		break;
	case StageType::normal:
		stage = new StageNormal;
		break;
	case StageType::hard:
		stage = new StageHard;
		break;
	}

	if (!stage->Init())
	{
		SAFE_DELETE(stage);
		return false;
	}

	vec_stage_.emplace_back(stage);

	return true;
}
