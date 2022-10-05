// �� ���̵� ���� �������� Ŭ������ �ΰ�
// ���̵��� �������� Ŭ�������� ��ӹ޴� �θ� �������� Ŭ������ ���� ����
// �̷��� ����� ���� : �������� ���̵����� �ܼ��� Ŭ������ ����ٸ� Ÿ���� �� �޶���.
// ��, ���������� �þ ������ �ش� �������� Ÿ���� �� �߰������ �Ѵ�.
// �� ��� �������� ������ ���⼭ ��.
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

