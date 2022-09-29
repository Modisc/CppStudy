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

	// FileStream �Ҹ��ڿ��� fclose ����ϱ� ������
	// ������ fclose �� ����� �ʿ䰡 ����.

	for (int i = 0; i < 10; i++)
	{
		int size = 0;
		file.ReadLine(stage_[i], size);
	}

	return true;
}

void Stage::Render()
{
	// ���� ��ũ�� ó���� �ؾ��Ѵ�. �׷��� ������ ���� �÷��̾
	// �̵��� ��ġ�κ��� ���� ������־�� �Ѵ�. ��� ũ���
	// ���� 4ĭ ���� 10ĭ���� ���ش�. ������ �÷��̾ ���� ��ġ�� �ִٰ�
	// �����ϰ� ó�� 4 x 10 ����� ���ش�.
	// 0 : ��, 1 : ��, 2 : ������, 3 : ������, 4 : ����

	Player* player = ObjectManager::GetInstance()->GetPlayer();

	int x = player->GetX();
	int y = player->GetY();

	// ���� ����� �÷��̾��� ��ġ�� �߽����� ����̴�.
	// ���δ� �÷��̾� 2ĭ ������ ��ĭ �Ʒ����� ��� => �� 4ĭ
	// ���δ� �÷��̾� ��ġ���� ������ 10ĭ���� ���.
	for (int i = y - 2; i <= y + 1; ++i) // �÷��̾� �� �� ĭ �Ʒ����� ���
	{
		for (int j = x; j < x + 10; ++j) // �÷��̾� �� 10ĭ ���
		{
			if (i == y && j == x)
				cout << "��";
			else if (stage_[i][j] == sbt_wall)
				cout << "��";
			else if (stage_[i][j] == sbt_road)
				cout << "  ";
			else if (stage_[i][j] == sbt_start)
				cout << "��";
			else if (stage_[i][j] == sbt_end)
				cout << "��";
			else if (stage_[i][j] == sbt_coin)
				cout << "��";
		}
		cout << endl;
	}
}
