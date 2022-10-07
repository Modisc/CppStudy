#include "ShapeManager.h"
#include "Rectangle.h"
#include "StageManager.h"
#include "Stage.h"

ShapeManager* ShapeManager::instance = NULL;

ShapeManager::ShapeManager():curr_shape_(NULL), next_shape_(NULL)
{
	curr_shape_ = CreateRandomShape();
	next_shape_ = CreateRandomShape();
	speed_ = 0;
}

ShapeManager::~ShapeManager()
{
	// for문 안에서 end() 함수를 호출해버리면, for문이 돌아가면서
	// 계속 end() 함수를 호출하게 된다. end() 또한 함수 호출이므로
	// 지역변수 할당 등 비용을 소모하게 될 것이다. 따라서, 아래와 같이
	// end() 함수를 한번 호출해서 변수에 담아두고 그 변수를 for문에서 사용하는 게
	// 훨씬 효율적이다.
	/*list<Shape*>::iterator iter_end = shape_list_.end();
	for (list<Shape*>::iterator iter = shape_list_.begin();
		iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	바닥에 블럭을 쌓는게 아니라, 바닥에 블럭이 닿으면 블럭을 스테이지의 일부분으로 바꾸는 식으로
	처리할 것이기 때문에 해당 부분은 더이상 필요가 없음.*/

	SAFE_DELETE(curr_shape_);
	SAFE_DELETE(next_shape_);
}

void ShapeManager::Update()
{
	Stage* curr_stage = StageManager::GetInstance()->GetCurrentStage();
	
	++speed_;
	if (curr_stage->GetSpeed() == speed_)
	{
		// true일 경우 바닥에 닿았으므로 리스트에 추가하고
		// 다음 도형을 현재 도형으로 만들어준다.
		// 그 뒤 다시 다음 도형을 추가한다.
		if(curr_shape_->MoveDown())
		{
			//shape_list_.push_back(curr_shape_);

			curr_stage->AddBlock(curr_shape_, curr_shape_->GetPosition());
			SAFE_DELETE(curr_shape_);
			curr_shape_ = next_shape_;
			// next_shape의 pos_.x, pos_.y 를 SetPosition 함수를 이용해서 12, 4로 고정을 해줬기 때문에
			// curr_shape에 next_shape를 받아온 후 다시 SetPosition을 통해 위치를 재설정 한다.
			curr_shape_->SetPosition(4, 0);
			next_shape_ = CreateRandomShape();
		}
		speed_ = 0;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		curr_shape_->MoveLeft();
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		curr_shape_->MoveRight();
	}
		
}

void ShapeManager::Render()
{
	/*list<Shape*>::iterator iter_end = shape_list_.end();
	for (list<Shape*>::iterator iter = shape_list_.begin();
		iter != iter_end; ++iter)
	{
		(*iter)->Render();
	}*/

	curr_shape_->Render();
	next_shape_->SetPosition(12, 4);
	// 기존 Render 함수로도 처리가 가능했는데, 도형이 오른쪽 끝까지 갔을 때,
	// 맵을 벗어나지 못하도록 하기 위한 예외처리 때문에 Render함수를 그대로 쓸 수는 없음
	// 따라서 RenderNext 함수를 별도로 만들어준다.
	// next_shape_->Render(); 
	next_shape_->RenderNext();
}

Shape* ShapeManager::CreateRandomShape()
{
	int type = rand() % static_cast<int>(ShapeType::end);
	return CreateShape((ShapeType)type);
}

Shape* ShapeManager::CreateShape(ShapeType type)
{
	Shape* shape = NULL;

	switch (type)
	{
	case ShapeType::rect:
		shape = new class Rectangle;
		break;
	}

	if (!shape->Init())
	{
		SAFE_DELETE(shape);
		return NULL;
	}

	return shape;
}
