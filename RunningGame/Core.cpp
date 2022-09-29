#include "Core.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Player.h"

Core* Core::core_instance_ = NULL;

// cpp ���Ͽ��� Ŭ������ �����κ��� �ִ�.
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
	// �� �����ڸ� �ʱ�ȭ�Ѵ�. ���н� false�� �����Ѵ�.
	if (!MapManager::GetInstance()->Init())
		return false;

	// ������Ʈ ������ �ʱ�ȭ
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

		// ���� �ڵ��θ� �����ϸ� ȭ�� ��ȯ�� �ʹ� ������.
		// Sleep�� WinAPI���� �����ϴ� �Լ�.
		// Sleep �Լ��� ���ڷ� �ִ� ������ ms�ʸ�ŭ ��� �����.
		// ���⼱ 500ms �� �����. �� 0.5�ʾ� ����.
		// 1/1000�� ������ ��Ʈ�� �� ���� �ִ�.
		Sleep(100);
	}
}
