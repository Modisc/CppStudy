#pragma once
#include "value.h"

class ShapeManager
{
private:
	ShapeManager();
	~ShapeManager();

private:
	static ShapeManager* instance;

public:
	static ShapeManager* GetInstance()
	{
		if (!instance)
		{
			instance = new ShapeManager;
		}

		return instance;
	}

	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

private:
	// �ٴڿ� ���� ������ ǥ���Ѵ�.
	// �ٴڿ� ���� ������ ���������� �Ϻκ����� �����ع��� ����
	// list<class Shape*> shape_list_;
	// ���� �����ִ� ������ ǥ���Ѵ�.
	class Shape* curr_shape_;
	// ������ ���� ������ ǥ���Ѵ�.
	class Shape* next_shape_;

	// ������ ������ ƽ�� ���Ѵ�.
	int speed_;

public:
	void Update();
	void Render();
	class Shape* CreateRandomShape();
	class Shape* CreateShape(ShapeType type);

};

