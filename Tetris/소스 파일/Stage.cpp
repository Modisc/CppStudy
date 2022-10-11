#include "Stage.h"
#include "Core.h"
#include "Shape.h"

Stage::Stage() : speed_(3)
{
}

Stage::~Stage()
{
}

void Stage::AddBlock(Shape* shape, const Position& pos)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (shape->GetBlock(j, i) == '0')
			{
				stage_arr_[pos.y - (3 - i)][pos.x + j] = '0';
				
				// 현재 줄을 체크한다.
				bool line = true;
				for (int k = 0; k < STAGE_WIDTH; ++k)
				{
					if (stage_arr_[pos.y - (3 - i)][k] != '0')
					{
						line = false;
						break;
					}
						
				}

				// 현재 블럭이 채워진 줄이 모두 블럭으로 채워져 있다면 해당 줄을 지워준다
				// 위의 블럭들을 모두 한칸씩 내려준다
				if (line)
				{
					for (int k = pos.y - (3 - i); k > 0; k--)
					{
						for (int m = 0; m < STAGE_WIDTH; ++m)
						{
							stage_arr_[k][m] = stage_arr_[k - 1][m];
						}

					}
				}
			}
				
		}
	}
}

bool Stage::CheckBlock(int x, int y)
{
	// 바닥에 닿았을 경우에 true
	if (y >= STAGE_HEIGHT)
		return true;

	// 실제 Shape의 pos_.x 와 콘솔창에 블럭이 그려지는 x좌표보다 한 칸 왼쪽이다.
	// Core.cpp의 SetConsoleCursorPosition 에서 (x + 1) * 2 를 해주기 때문이다.
	// => 처음부터 (x + 1) 하지말고 칸을 0부터 제대로 셌으면 안 헷갈렸을 것 같음.
	else if (x < 0 || x >= STAGE_WIDTH)
		return true;

	// 블럭에 닿았어도 true
	return stage_arr_[y][x] == '0';
}

bool Stage::Init()
{
	memset(stage_arr_, '1', STAGE_HEIGHT * STAGE_WIDTH);

	return true;
}

void Stage::Render()
{
	for (int i = 0; i < STAGE_HEIGHT + 1; i++) // 게임 Stage 외부를 블럭을 둘러서 막을 것임. 
	{
		for (int j = 0; j < STAGE_WIDTH + 2; j++)
		{
			if (i == 0 && (j == 0 || j == STAGE_WIDTH + 1))
				cout << "■";
			else if (j == 0)
				cout << "■";
			else if (i == STAGE_HEIGHT)
				cout << "■";
			else if (j == STAGE_WIDTH + 1)
				cout << "■";
			else
			{
				if(stage_arr_[i][j - 1] == '1') // j가 STAGE_WIDTH 까지 커지면 안 됨. 인덱스 범위가 벗어남
					cout << "  ";

				else
					cout << "■";
			}
			
		}

		cout << endl;
	}

	// 스테이지 오른쪽에 다음에 나올 도형을 미리 출력해줄
	// 칸을 만들어준다.
	for (int i = 0; i < 7; ++i)
	{
		Core::GetInstance()->SetConsolePos(17, i);
		cout << "■";
	}

	for (int i = 0; i < 6; ++i)
	{
		Core::GetInstance()->SetConsolePos(11+i, 6);
		cout << "■";
	}
}
