#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

Core* Core::instance = NULL;

Core::Core() : loop_(true)
{
	srand((unsigned int)time(NULL));
}

Core::~Core()
{
	ShapeManager::DestroyInstance();
	StageManager::DestroyInstance();
}

bool Core::Init()
{
	// �ܼ�â �ڵ� ����
	console_ = GetStdHandle(STD_OUTPUT_HANDLE);

	if (console_ == INVALID_HANDLE_VALUE)
		return false;

	if (!StageManager::GetInstance()->Init())
	{
		return false;
	}

	return true;
}

void Core::Run()
{
	while (loop_)
	{
		// ShapeManager::GetInstance()->Render(); ���� �ڵ尡 ������
		// ���� �ܼ�â�� Ŀ�� ��ġ�� (0, 0)�� �ƴ϶�
		// (0, 3)�� ���� ����� ��ġ�� ���ִ�.
		// �� ���·� ���� ������ �ϸ� �ش� Ŀ�� ��ġ���� ���� �������ϰ� �ǹǷ�
		// ���� ������ �þ�� �ȴ�.
		// ���� system("cls")�� ���ؼ� ������ ��µ� ������ �� �� �����
		// �ٽ� ó������ ������ �ϴ� ������ ������ �Ǿ�� �Ѵ�.
		system("cls");
		StageManager::GetInstance()->Run();
		ShapeManager::GetInstance()->Render();
		ShapeManager::GetInstance()->Update();
		
		Sleep(50); // �ʴ� 1�� ���ư���
	}
}

void Core::SetConsolePos(int x, int y)
{
	// ���� ��Ʈ���������� Ư�����ڸ� ����ؼ� �� ĭ�� ǥ���ϹǷ�
	// �� ĭ�� 2����Ʈ�� ����Ѵ�. �׷��� ������ *2�� ���ش�.
	// ���� ���� ù��° ĭ�� ���̹Ƿ� �ش� ĭ�� �Ѿ�� ��������
	// ĭ�� ������ �����.
	
	COORD pos = { (x + 1) * 2, y };
	SetConsoleCursorPosition(console_, pos);
}
