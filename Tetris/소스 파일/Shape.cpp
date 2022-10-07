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
    // 도형의 기준점을 가장 왼쪽 아래로 잡는다.
    pivot_.x = 0;
    pivot_.y = 3;

    return true;
}

void Shape::Render()
{  
    // 여기서 콘솔 핸들을 설정해버리면 반복문에서 줄 넘기면 다시 커서가 x = 0 의 위치로 이동됨.
    // 따라서 커서 위치도 반복문 안에서 계속 바꿔줘야함.
    // Core::GetInstance()->SetConsolePos(pos_.x, pos_.y);

    int y;
    for (int i = 0; i < 4; i++)
    {
        // 콘솔창에 출력할 좌표를 설정한 후에 출력한다.
        // pos_.y 만 선언하면 반복문 도는 동안 커서 위치가 계속 (4, 0)에
        // 고정되어서 출력이 이상하게 된다.
        // 따라서 pos_.y도 반복문이 이동하면서 함께 돌아야 하고
        // 도형은 맵 밖에 있다가 한줄씩 나타나야 하므로 pos_.y + i 가 아니라
        // pos_.y - (3-i) 를 해서 원하는 위치보다 위에서부터 반복문을 돌면서 나오도록 해야한다.
        y = pos_.y - (3 - i);
        if (y < 0) continue;

        Core::GetInstance()->SetConsolePos(pos_.x, y);

        for (int j = 0; j < 4; j++)
        {
            if (pos_.x + j >= STAGE_WIDTH)
                continue;

            if (base_shape_[i][j] == '0')
                cout << "★";
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
                cout << "★";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

// true를 리턴할 경우 바닥에 닿았다는 뜻임.
bool Shape::MoveDown()
{
    Stage* stage = StageManager::GetInstance()->GetCurrentStage();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // base_shape는 4x4 2차원 배열이다. 여기서 4x4중 일부 칸만 실제 블럭이 되는 것이므로
            // 실제 내 블럭일때에 한해서 조사를 해야한다.
            if (base_shape_[i][j] == '0')
            {
                // 내 블럭 가장 아래 바로 밑칸을 조사해야 함.
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
