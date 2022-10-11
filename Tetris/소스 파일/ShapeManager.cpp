#include "ShapeManager.h"
#include "ShapeRectangle.h"
#include "ShapeGun.h"
#include "ShapeLine.h"
#include "ShapeReverseGun.h"
#include "ShapeS.h"
#include "ShapeT.h"
#include "ShapeZ.h"
#include "StageManager.h"
#include "Stage.h"

ShapeManager* ShapeManager::instance = NULL;

ShapeManager::ShapeManager():curr_shape_(NULL), next_shape_(NULL)
{
	curr_shape_ = CreateRandomShape();
	next_shape_ = CreateRandomShape();\
	speed_ = 0;
}

ShapeManager::~ShapeManager()
{
	// for�� �ȿ��� end() �Լ��� ȣ���ع�����, for���� ���ư��鼭
	// ��� end() �Լ��� ȣ���ϰ� �ȴ�. end() ���� �Լ� ȣ���̹Ƿ�
	// �������� �Ҵ� �� ����� �Ҹ��ϰ� �� ���̴�. ����, �Ʒ��� ����
	// end() �Լ��� �ѹ� ȣ���ؼ� ������ ��Ƶΰ� �� ������ for������ ����ϴ� ��
	// �ξ� ȿ�����̴�.
	/*list<Shape*>::iterator iter_end = shape_list_.end();
	for (list<Shape*>::iterator iter = shape_list_.begin();
		iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	�ٴڿ� ���� �״°� �ƴ϶�, �ٴڿ� ���� ������ ���� ���������� �Ϻκ����� �ٲٴ� ������
	ó���� ���̱� ������ �ش� �κ��� ���̻� �ʿ䰡 ����.*/

	SAFE_DELETE(curr_shape_);
	SAFE_DELETE(next_shape_);
}

void ShapeManager::Update()
{
	Stage* curr_stage = StageManager::GetInstance()->GetCurrentStage();
	
	++speed_;
	if (curr_stage->GetSpeed() == speed_)
	{
		// true�� ��� �ٴڿ� ������Ƿ� ����Ʈ�� �߰��ϰ�
		// ���� ������ ���� �������� ������ش�.
		// �� �� �ٽ� ���� ������ �߰��Ѵ�.
		if(curr_shape_->MoveDown())
		{
			//shape_list_.push_back(curr_shape_);

			curr_stage->AddBlock(curr_shape_, curr_shape_->GetPosition());
			SAFE_DELETE(curr_shape_);
			curr_shape_ = next_shape_;
			// next_shape�� pos_.x, pos_.y �� SetPosition �Լ��� �̿��ؼ� 12, 4�� ������ ����� ������
			// curr_shape�� next_shape�� �޾ƿ� �� �ٽ� SetPosition�� ���� ��ġ�� �缳�� �Ѵ�.
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

	if (GetAsyncKeyState('W') & 0x8000)
	{
		curr_shape_->Rotation();
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
	// ���� Render �Լ��ε� ó���� �����ߴµ�, ������ ������ ������ ���� ��,
	// ���� ����� ���ϵ��� �ϱ� ���� ����ó�� ������ Render�Լ��� �״�� �� ���� ����
	// ���� RenderNext �Լ��� ������ ������ش�.
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
		shape = new class ShapeRectangle;
		break;
	case ShapeType::gun:
		shape = new class ShapeGun;
		break;
	case ShapeType::line:
		shape = new class ShapeLine;
		break;
	case ShapeType::reverse_gun:
		shape = new class ShapeReverseGun;
		break;
	case ShapeType::s:
		shape = new class ShapeS;
		break;
	case ShapeType::t:
		shape = new class ShapeT;
		break;
	case ShapeType::z:
		shape = new class ShapeZ;
		break;

	}

	if (!shape->Init())
	{
		SAFE_DELETE(shape);
		return NULL;
	}

	return shape;
}
