// 각 난이도 별로 스테이지 클래스를 두고
// 난이도별 스테이지 클래스들이 상속받는 부모 스테이지 클래스를 만들 예정
// 이렇게 만드는 이유 : 스테이지 난이도별로 단순히 클래스를 만든다면 타입이 다 달라짐.
// 즉, 스테이지가 늘어날 때마다 해당 스테이지 타입을 다 추가해줘야 한다.
// 그 모든 스테이지 관리를 여기서 함.
#pragma once
#include "value.h"

enum class StageType
{
	none,
	easy,
	normal,
	hard,
	back
};

class StageManager
{
private:
	vector<class Stage*> vec_stage_;

public:
	bool Init();
	void Run();

private:
	bool CreateStage(StageType type);

	DECLARE_SINGLE(StageManager)
};

