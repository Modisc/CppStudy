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
	// 바닥에 쌓인 도형을 표현한다.
	// 바닥에 쌓인 도형은 스테이지의 일부분으로 변경해버릴 것임
	// list<class Shape*> shape_list_;
	// 현재 나와있는 도형을 표현한다.
	class Shape* curr_shape_;
	// 다음에 나올 도형을 표현한다.
	class Shape* next_shape_;

	// 도형을 움직일 틱을 정한다.
	int speed_;

public:
	void Update();
	void Render();
	class Shape* CreateRandomShape();
	class Shape* CreateShape(ShapeType type);

};

