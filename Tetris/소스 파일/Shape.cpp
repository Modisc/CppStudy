#include "StageManager.h"
#include "Stage.h"
#include "Shape.h"
#include "Core.h"

Shape::Shape()
{
    dir_ = static_cast<int>(RotationDir::up);
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

        for (int j = 0; j < 4; j++)
        {
            if (pos_.x + j >= STAGE_WIDTH)
                continue;

            if (base_shape_[i][j] == '0')
            {
                // 도형이 네모일 때는 1차 반복문에서 바로 커서를 설정해도 상관 없었지만
                // 도형을 추가했을 때는 현재 도형을 그리면서 빈 여백을 출력하지 않기 때문에
                // 커서를 자동으로 이동하도록 해야한다.
                // 그렇지 않으면 ㄱ 과 같은 모양을 그릴 때 여백 부분엔 아무 것도 출력하지 않으므로
                // 커서가 여백 부분에서 머물다가 도형을 그려주게 된다.
                Core::GetInstance()->SetConsolePos(pos_.x + j, y);
                cout << "☆";
            }
                
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

        for (int j = 0; j < 4; j++)
        {
            if (base_shape_[i][j] == '0')
            {
                // 도형이 네모일 때는 1차 반복문에서 바로 커서를 설정해도 상관 없었지만
                // 도형을 추가했을 때는 현재 도형을 그리면서 빈 여백을 출력하지 않기 때문에
                // 커서를 자동으로 이동하도록 해야한다.
                // 그렇지 않으면 ㄱ 과 같은 모양을 그릴 때 여백 부분엔 아무 것도 출력하지 않으므로
                // 커서가 여백 부분에서 머물다가 도형을 그려주게 된다.
                Core::GetInstance()->SetConsolePos(pos_.x + j, y);
                cout << "★";
            }
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
                    // 바닥에 닿은 후 현재 도형의 블럭인 부분이 하나라도 좌표가 0보다 작다면 종료한다.
                    for (int k = 0; k < 4; ++k)
                    {
                        for (int m = 0; m < 4; ++m)
                        {
                            if (base_shape_[k][m] == '0')
                            {
                                if (pos_.y - (3 - k) < 0)
                                {
                                    Core::GetInstance()->End();
                                    Core::GetInstance()->SetConsolePos(0, 17);
                                    cout << "\t게임 종료!!!" << endl;
                                    break;
                                }
                            }
                        }
                    }
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
