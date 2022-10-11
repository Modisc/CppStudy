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
	// 콘솔창 핸들 생성
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
		// ShapeManager::GetInstance()->Render(); 까지 코드가 돌고나면
		// 현재 콘솔창의 커서 위치가 (0, 0)이 아니라
		// (0, 3)과 같이 변경된 위치에 들어가있다.
		// 그 상태로 맵을 렌더링 하면 해당 커서 위치부터 맵을 렌더링하게 되므로
		// 맵이 밑으로 늘어나게 된다.
		// 따라서 system("cls")를 통해서 기존에 출력된 내용을 한 번 지우고
		// 다시 처음부터 렌더링 하는 식으로 진행이 되어야 한다.
		system("cls");
		StageManager::GetInstance()->Run();
		ShapeManager::GetInstance()->Render();
		ShapeManager::GetInstance()->Update();
		
		Sleep(50); // 초당 1번 돌아가기
	}
}

void Core::SetConsolePos(int x, int y)
{
	// 현재 테트리스에서는 특수문자를 사용해서 한 칸을 표현하므로
	// 한 칸은 2바이트를 사용한다. 그렇기 때문에 *2를 해준다.
	// 또한 제일 첫번째 칸은 벽이므로 해당 칸은 넘어가고 다음부터
	// 칸을 세도록 만든다.
	
	COORD pos = { (x + 1) * 2, y };
	SetConsoleCursorPosition(console_, pos);
}
