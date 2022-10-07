#include "StageManager.h"
#include "Stage.h"
#include "Shape.h"
#include "Core.h"

Shape::Shape()
{
    width_count_ = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            base_shape_[i][j] = '1';
        }
    }
}

Shape::~Shape()
{
}

bool Shape::Init()
{
    // ������ �������� ���� ���� �Ʒ��� ��´�.
    pivot_.x = 0;
    pivot_.y = 3;

    return true;
}

void Shape::Render()
{  
    // ���⼭ �ܼ� �ڵ��� �����ع����� �ݺ������� �� �ѱ�� �ٽ� Ŀ���� x = 0 �� ��ġ�� �̵���.
    // ���� Ŀ�� ��ġ�� �ݺ��� �ȿ��� ��� �ٲ������.
    // Core::GetInstance()->SetConsolePos(pos_.x, pos_.y);

    int y;
    for (int i = 0; i < 4; i++)
    {
        // �ܼ�â�� ����� ��ǥ�� ������ �Ŀ� ����Ѵ�.
        // pos_.y �� �����ϸ� �ݺ��� ���� ���� Ŀ�� ��ġ�� ��� (4, 0)��
        // �����Ǿ ����� �̻��ϰ� �ȴ�.
        // ���� pos_.y�� �ݺ����� �̵��ϸ鼭 �Բ� ���ƾ� �ϰ�
        // ������ �� �ۿ� �ִٰ� ���پ� ��Ÿ���� �ϹǷ� pos_.y + i �� �ƴ϶�
        // pos_.y - (3-i) �� �ؼ� ���ϴ� ��ġ���� ���������� �ݺ����� ���鼭 �������� �ؾ��Ѵ�.
        y = pos_.y - (3 - i);
        if (y < 0) continue;

        Core::GetInstance()->SetConsolePos(pos_.x, y);

        for (int j = 0; j < 4; j++)
        {
            if (pos_.x + j >= STAGE_WIDTH)
                continue;

            if (base_shape_[i][j] == '0')
                cout << "��";
        }
        cout << endl;
    }
}

void Shape::RenderNext()
{
    int y;
    for (int i = 0; i < 4; i++)
    {
        y = pos_.y - (3 - i);
        if (y < 0) continue;

        Core::GetInstance()->SetConsolePos(pos_.x, y);

        for (int j = 0; j < 4; j++)
        {
            if (base_shape_[i][j] == '0')
                cout << "��";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

// true�� ������ ��� �ٴڿ� ��Ҵٴ� ����.
bool Shape::MoveDown()
{
    Stage* stage = StageManager::GetInstance()->GetCurrentStage();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // base_shape�� 4x4 2���� �迭�̴�. ���⼭ 4x4�� �Ϻ� ĭ�� ���� ���� �Ǵ� ���̹Ƿ�
            // ���� �� ���϶��� ���ؼ� ���縦 �ؾ��Ѵ�.
            if (base_shape_[i][j] == '0')
            {
                // �� �� ���� �Ʒ� �ٷ� ��ĭ�� �����ؾ� ��.
                if (stage->CheckBlock(pos_.x + j, pos_.y - (2 - i)))
                {
                    return true;
                }
            }
           
        }
    }

    ++pos_.y;

    return false;
}

void Shape::MoveLeft()
{
    /*if (pos_.x == 0)
        return;*/

    Stage* stage = StageManager::GetInstance()->GetCurrentStage();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (base_shape_[i][j] == '0')
            {
                if (stage->CheckBlock(pos_.x + j - 1, pos_.y - (3 - i)))
                {
                    return;
                }
            }
        }
    }

    --pos_.x;
}

void Shape::MoveRight()
{
    /*if (pos_.x + width_count_ == STAGE_WIDTH)
        return;*/

    Stage* stage = StageManager::GetInstance()->GetCurrentStage();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (base_shape_[i][j] == '0')
            {
                if (stage->CheckBlock(pos_.x + j + 1, pos_.y - (3 - i)))
                {
                    return;
                }
            }
        }
    }

    ++pos_.x;
}
