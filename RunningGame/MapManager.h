#pragma once

#include "value.h"

// Ŭ���� ���漱�� : �̰����� ���漱���� Ŭ������ �ִ� ��� �ν��ϰ� �����.
// ���漱�� �� �κп����� ������ �ϴ� ���̱� ������ ���漱���� Ŭ������ ��ü
// �� �����ϴ��� ����� ����� ����� �� ����.
// �ܼ��� ������ ������ ������ �������� �ַ� ����ϰ� ���漱���� ���������
// �� ������� ����� #include �ϴ� ��Ȳ�� �����ְ� cpp���� ���� �����
// �� include�� ���־ ������� ���� include�ϴ� ��Ȳ�� ������ �� �ִ�.
class Stage;
class MapManager
{
private:
	MapManager();
	~MapManager();

private:
	static MapManager*	map_manager_instance_;

public:
	static MapManager* GetInstance();
	static void DestroyInst();

private:
	Stage*		stage_[STAGE_MAX_COUNT];

public:
	bool Init();
	void Run();
	void Render();
};

