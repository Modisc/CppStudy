#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

bool Stage::Init()
{
	memset(stage_arr_, 0, STAGE_HEIGHT * STAGE_WIDTH);

	return true;
}

void Stage::Render()
{
	for (int i = 0; i < STAGE_HEIGHT + 2; i++) // 게임 Stage 외부를 블럭을 둘러서 막을 것임. 
	{
		for (int j = 0; j < STAGE_WIDTH + 2; j++)
		{
			if (i == 0)
				cout << "  ";
			else if (i == 1 && (j == 0 || j == STAGE_WIDTH + 1))
				cout << "■";
			else if (j == 0)
				cout << "■";
			else if (i == STAGE_HEIGHT + 1)
				cout << "■";
			else if (j == STAGE_WIDTH + 1)
				cout << "■";
			else
				cout << "  ";
		}

		cout << endl;
	}
}
