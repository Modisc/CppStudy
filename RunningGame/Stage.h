#pragma once

#include "value.h"

class Stage
{
public:
	Stage();
	~Stage();

private:
	char stage_[10][50];

public:
	// �� �Լ��� �׳� �ʱ�ȭ�� ������ �Լ��̴�.
	bool Init();

	// �� �Լ��� ���Ͽ��� ������ �о�ͼ� ������ ������ �Լ��̴�.
	bool Init(const char* pFileName);
	void Render();
};

