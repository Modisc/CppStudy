#include "Core.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Player.h"

Core* Core::core_instance_ = NULL;

// cpp 파일에는 클래스의 구현부분이 있다.
Core::Core()
{
}

Core::~Core()
{
	MapManager::DestroyInst();
	ObjectManager::DestroyInst();
}

Core* Core::GetInstance()
{
	if (!core_instance_)
		core_instance_ = new Core;
	
	return core_instance_;
}

void Core::DestroyInst()
{
	SAFE_DELETE(core_instance_);
}

bool Core::Init()
{
	// 맵 관리자를 초기화한다. 실패시 false를 리턴한다.
	if (!MapManager::GetInstance()->Init())
		return false;

	// 오브젝트 관리자 초기화
	if (!ObjectManager::GetInstance()->Init())
		return false;

	return true;
}

void Core::Run()
{
	//CMapManager::GetInst()->Render();
	Player* player = ObjectManager::GetInstance()->GetPlayer();
	while (true)
	{
		system("cls");

		player->Update();

		MapManager::GetInstance()->Render();

		// 위에 코드대로만 실행하면 화면 전환이 너무 빠르다.
		// Sleep도 WinAPI에서 제공하는 함수.
		// Sleep 함수의 인자로 주는 숫자의 ms초만큼 잠시 멈춘다.
		// 여기선 500ms 씩 멈춘다. 즉 0.5초씩 멈춤.
		// 1/1000초 단위로 컨트롤 할 수도 있다.
		Sleep(100);
	}
}
