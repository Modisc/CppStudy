#include "Stage.h"
#include "FileStream.h"
#include "Player.h"
#include "ObjectManager.h"

enum StageBlockType
{
	sbt_wall = '0',
	sbt_road = '1',
	sbt_start = '2',
	sbt_end = '3',
	sbt_coin = '4'
};
Stage::Stage()
{
}

Stage::~Stage()
{
}

bool Stage::Init()
{
	return true;
}

bool Stage::Init(const char * pFileName)
{
	FileStream file;

	if (!file.Open(pFileName, "rt"))
		return false;

	// FileStream 소멸자에서 fclose 사용하기 때문에
	// 별도로 fclose 를 사용할 필요가 없다.

	for (int i = 0; i < 10; i++)
	{
		int size = 0;
		file.ReadLine(stage_[i], size);
	}

	return true;
}

void Stage::Render()
{
	// 맵은 스크롤 처리를 해야한다. 그렇기 때문에 현재 플레이어가
	// 이동한 위치로부터 맵을 출력해주어야 한다. 출력 크기는
	// 세로 4칸 가로 10칸으로 해준다. 지금은 플레이어가 시작 위치에 있다고
	// 가정하고 처음 4 x 10 출력을 해준다.
	// 0 : 벽, 1 : 길, 2 : 시작점, 3 : 도착점, 4 : 코인

	Player* player = ObjectManager::GetInstance()->GetPlayer();

	int x = player->GetX();
	int y = player->GetY();

	// 맵의 출력은 플레이어의 위치를 중심으로 출력이다.
	// 세로는 플레이어 2칸 위부터 한칸 아래까지 출력 => 총 4칸
	// 가로는 플레이어 위치부터 오른쪽 10칸까지 출력.
	for (int i = y - 2; i <= y + 1; ++i) // 플레이어 발 한 칸 아래까지 출력
	{
		for (int j = x; j < x + 10; ++j) // 플레이어 앞 10칸 출력
		{
			if (i == y && j == x)
				cout << "®";
			else if (stage_[i][j] == sbt_wall)
				cout << "■";
			else if (stage_[i][j] == sbt_road)
				cout << "  ";
			else if (stage_[i][j] == sbt_start)
				cout << "◑";
			else if (stage_[i][j] == sbt_end)
				cout << "◐";
			else if (stage_[i][j] == sbt_coin)
				cout << "＠";
		}
		cout << endl;
	}
}
