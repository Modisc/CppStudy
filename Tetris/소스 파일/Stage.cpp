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
				
				// ���� ���� üũ�Ѵ�.
				bool line = true;
				for (int k = 0; k < STAGE_WIDTH; ++k)
				{
					if (stage_arr_[pos.y - (3 - i)][k] != '0')
					{
						line = false;
						break;
					}
						
				}

				// ���� ���� ä���� ���� ��� ������ ä���� �ִٸ� �ش� ���� �����ش�
				// ���� ������ ��� ��ĭ�� �����ش�
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
	// �ٴڿ� ����� ��쿡 true
	if (y >= STAGE_HEIGHT)
		return true;

	// ���� Shape�� pos_.x �� �ܼ�â�� ���� �׷����� x��ǥ���� �� ĭ �����̴�.
	// Core.cpp�� SetConsoleCursorPosition ���� (x + 1) * 2 �� ���ֱ� �����̴�.
	// => ó������ (x + 1) �������� ĭ�� 0���� ����� ������ �� �򰥷��� �� ����.
	else if (x < 0 || x >= STAGE_WIDTH)
		return true;

	// ���� ��Ҿ true
	return stage_arr_[y][x] == '0';
}

bool Stage::Init()
{
	memset(stage_arr_, '1', STAGE_HEIGHT * STAGE_WIDTH);

	return true;
}

void Stage::Render()
{
	for (int i = 0; i < STAGE_HEIGHT + 1; i++) // ���� Stage �ܺθ� ���� �ѷ��� ���� ����. 
	{
		for (int j = 0; j < STAGE_WIDTH + 2; j++)
		{
			if (i == 0 && (j == 0 || j == STAGE_WIDTH + 1))
				cout << "��";
			else if (j == 0)
				cout << "��";
			else if (i == STAGE_HEIGHT)
				cout << "��";
			else if (j == STAGE_WIDTH + 1)
				cout << "��";
			else
			{
				if(stage_arr_[i][j - 1] == '1') // j�� STAGE_WIDTH ���� Ŀ���� �� ��. �ε��� ������ ���
					cout << "  ";

				else
					cout << "��";
			}
			
		}

		cout << endl;
	}

	// �������� �����ʿ� ������ ���� ������ �̸� �������
	// ĭ�� ������ش�.
	for (int i = 0; i < 7; ++i)
	{
		Core::GetInstance()->SetConsolePos(17, i);
		cout << "��";
	}

	for (int i = 0; i < 6; ++i)
	{
		Core::GetInstance()->SetConsolePos(11+i, 6);
		cout << "��";
	}
}
