#include <iostream>
#include <conio.h>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;

/*
0 : ��
1 : ��
2 : ������
3 : ������
4 : ��ź ������
5 : ��ź �Ŀ� ���� ������
6 : ���б� ������
7 : ���� ������
*/

struct Point
{
	int x;
	int y;
};

struct Player
{
	Point pos;
	bool wallPush;
	bool pushOnOff;
	bool transparency;
	int boombPower;
};

void SetMaze(char maze[21][21], Player* player, Point* startPos, Point* endPos)
{
	// MazeList.txt ������ �о�ͼ� �̷� ����� �����.
	FILE* file = NULL;
	fopen_s(&file, "MazeList.txt", "rt");
	char** mazeList = {};

	if (file)
	{
		char count;

		// ���� '4' �� count�� ��.
		// '4' �� �ƽ�Ű���� 52.
		// ��, count���� ������ 52�� ���ִ� �Ͱ� ��������
		fread(&count, 1, 1, file);

		// ���� '4' �� ������ 4 �� �����Ͽ��ش�.
		int mazeCount = atoi(&count);

		fread(&count, 1, 1, file); // 4 ���� '\n' ���� �о���̵��� �� ����.

		// �̷� ������ŭ char* �迭�� �Ҵ�.
		mazeList = new char* [mazeCount];

		for (int i = 0; i < mazeCount; ++i)
		{
			int nameCount = 0;

			// ���� �̷��� ���� �̸��� ������ �迭�� 256���� �Ҵ�.
			// �̸� �˳��ϰ� �Ҵ��ص� ���̴�.
			mazeList[i] = new char[256];

			while (true)
			{
				fread(&count, 1, 1, file);

				if (count != '\n')
				{
					mazeList[i][nameCount] = count;
					++nameCount;
				}

				else	break;
			}

			// ���� �̸��� ��� �о��ٸ� ���ڿ��� �������� 0�� �־
			// ���ڿ��� ���� �˷��ش�.
			mazeList[i][nameCount] = 0;
		}

		fclose(file);

		// ���� ���� ����� ��������Ƿ� �� ���� �� �ϳ��� �����ؼ�
		// �̷θ� �о�ͼ� �����Ѵ�.

		for (int i = 0; i < mazeCount; ++i)
		{
			cout << i + 1 << ". " << mazeList[i] << endl;
		}

		cout << "�̷θ� �����ϼ��� : ";
		int input;
		cin >> input;

		fopen_s(&file, mazeList[input - 1], "rt");

		if (file)
		{
			// �̷��� ���� �� ����ŭ �ݺ��ϸ� �� �� ���� �о�´�.
			for (int i = 0; i < 20; ++i)
			{
				fread(maze[i], 1, 20, file);

				// ���� ���� �̷θ� �˻��Ͽ� ������, Ȥ��
				// �������� �ִ����� �Ǵ��Ѵ�.
				for (int j = 0; j < 20; ++j)
				{
					if (maze[i][j] == '2')
					{
						startPos->x = j;
						startPos->y = i;
						player->pos = *startPos;
					}
					else if (maze[i][j] == '3')
					{
						endPos->x = j;
						endPos->y = i;
					}
				}
				// ���๮�ڸ� �о�´�.
				fread(&count, 1, 1, file);
			}
			fclose(file);
		}	
	}
}

void OutputMaze(char maze[21][21], Player* player)
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (maze[i][j] == '4')	cout << "��";
			else if (player->pos.x == j && player->pos.y == i)	cout << "��";
			else if (maze[i][j] == '0') cout << "��";
			else if (maze[i][j] == '1')	cout << "  ";
			else if (maze[i][j] == '2')	cout << "��";
			else if (maze[i][j] == '3') cout << "��";
			else if (maze[i][j] == '5') cout << "��";
			else if (maze[i][j] == '6') cout << "��";
			else if (maze[i][j] == '7') cout << "��";
			else cout << "//";
		}
		cout << endl;
	}

	cout << "��ź�Ŀ� : " << player->boombPower << endl;
	cout << "�� ��� : ";
	player->transparency == true ? cout << "ON\t" : cout << "OFF\t";
	cout << "�� �б� : ";
	if (player->wallPush)
	{
		cout << "���� / ";
		if (player->pushOnOff)
		{
			cout << "ON" << endl;
		}
		else
		{
			cout << "OFF" << endl;
		}
	}
	else
	{
		cout << "�Ұ��� / OFF" << endl;
	}
}

bool AddItem(char itemType, Player* player)
{
	if (itemType == '5')
	{
		if (player->boombPower < 5)	++player->boombPower;
		return true;
	}

	else if (itemType == '6')
	{
		player->wallPush = true;
		player->pushOnOff = true;
		return true;
	}

	else if (itemType == '7')
	{
		player->transparency = true;
		return true;
	}

	else return false;
}

void MoveUp(char maze[21][21], Player* player) {
	if (player->pos.y - 1 >= 0)
	{
		if (maze[player->pos.y - 1][player->pos.x] != '0' && maze[player->pos.y - 1][player->pos.x] != '4')
			--player->pos.y;

		// ���б� �������� �ְ�, �̵��Ϸ��� ĭ�� ���� ���, ���� ���� �ִ� ĭ�� ���� ���
		else if (player->wallPush && maze[player->pos.y - 1][player->pos.x] == '0' && maze[player->pos.y][player->pos.x] == '1')
		{
			// ���б� ���ΰ� ON�̰�, �̵��Ϸ��� ĭ�� ����ĭ�� �� ���� �����̰�, �� ĭ�� ���� ���� ���� �� �� �ִ�.
			if (player->pushOnOff)
			{
				if (player->pos.y - 2 >= 0)
				{
					if (maze[player->pos.y - 2][player->pos.x] != '1')
					{
						if (player->transparency)
						{
							--player->pos.y;
						}
					}
					else if (maze[player->pos.y - 2][player->pos.x] == '1')
					{
						maze[player->pos.y - 2][player->pos.x] = '0';
						maze[player->pos.y - 1][player->pos.x] = '1';
						--player->pos.y;
					}
				}
				else if (player->transparency)
				{
					--player->pos.y;
				}
			}

			else if (player->transparency)
			{
				--player->pos.y;
			}
		}

		else if (player->transparency)	--player->pos.y;

		if (AddItem(maze[player->pos.y][player->pos.x], player))
		{
			maze[player->pos.y][player->pos.x] = '1';
		}
	}
}

void MoveDown(char maze[21][21], Player* player) {
	if (player->pos.y + 1 < 20) {
		if (maze[player->pos.y + 1][player->pos.x] != '0' && maze[player->pos.y + 1][player->pos.x] != '4')
		{
			++player->pos.y;
		}

		else if (player->wallPush && maze[player->pos.y + 1][player->pos.x] == '0' && maze[player->pos.y][player->pos.x] == '1')
		{
			if (player->pushOnOff)
			{
				if (player->pos.y + 2 < 20)
				{
					if (maze[player->pos.y + 2][player->pos.x] != '1')
					{
						if (player->transparency)
						{
							++player->pos.y;
						}
					}
					else if (maze[player->pos.y + 2][player->pos.x] == '1')
					{
						maze[player->pos.y + 2][player->pos.x] = '0';
						maze[player->pos.y + 1][player->pos.x] = '1';
						++player->pos.y;
					}
				}
				else if (player->transparency)
				{
					++player->pos.y;
				}
			}

			else if (player->transparency)
			{
				++player->pos.y;
			}
		}

		else if (player->transparency)	++player->pos.y;

		if (AddItem(maze[player->pos.y][player->pos.x], player))
		{
			maze[player->pos.y][player->pos.x] = '1';
		}
	}
}

void MoveRight(char maze[21][21], Player* player) {
	if (player->pos.x + 1 < 20) {
		if (maze[player->pos.y][player->pos.x + 1] != '0' && maze[player->pos.y][player->pos.x + 1] != '4')
		{
			++player->pos.x;
		}

		else if (player->wallPush && maze[player->pos.y][player->pos.x + 1] == '0' && maze[player->pos.y][player->pos.x] == '1')
		{
			if (player->pushOnOff)
			{
				if (player->pos.x + 2 < 20)
				{
					if (maze[player->pos.y][player->pos.x + 2] != '1')
					{
						if (player->transparency)
						{
							++player->pos.x;
						}
					}
					else if (maze[player->pos.y][player->pos.x + 2] == '1')
					{
						maze[player->pos.y][player->pos.x + 2] = '0';
						maze[player->pos.y][player->pos.x + 1] = '1';
						++player->pos.x;
					}
				}
				else if (player->transparency)
				{
					++player->pos.x;
				}
			}

			else if (player->transparency)
			{
				++player->pos.x;
			}
		}

		else if (player->transparency)	++player->pos.x;

		if (AddItem(maze[player->pos.y][player->pos.x], player))
		{
			maze[player->pos.y][player->pos.x] = '1';
		}
	}
}

void MoveLeft(char maze[21][21], Player* player) {
	if (player->pos.x - 1 >= 0) {
		if (maze[player->pos.y][player->pos.x - 1] != '0' && maze[player->pos.y][player->pos.x - 1] != '4')
		{
			--player->pos.x;
		}

		else if (player->wallPush && maze[player->pos.y][player->pos.x - 1] == '0' && maze[player->pos.y][player->pos.x] == '1')
		{
			if (player->pushOnOff)
			{
				if (player->pos.x - 2 >= 0)
				{
					if (maze[player->pos.y][player->pos.x - 2] != '1')
					{
						if (player->transparency)
						{
							--player->pos.x;
						}
					}
					else if (maze[player->pos.y][player->pos.x - 2] == '1')
					{
						maze[player->pos.y][player->pos.x - 2] = '0';
						maze[player->pos.y][player->pos.x - 1] = '1';
						--player->pos.x;
					}
				}
				else if (player->transparency)
				{
					--player->pos.x;
				}
			}

			else if (player->transparency)
			{
				--player->pos.x;
			}
		}

		else if (player->transparency)	--player->pos.x;

		if (AddItem(maze[player->pos.y][player->pos.x], player))
		{
			maze[player->pos.y][player->pos.x] = '1';
		}
	}
}

void MovePlayer(char maze[21][21], Player* player, char input)
{
	switch (input)
	{
	case 'w':
	case 'W':
		MoveUp(maze, player);
		break;
	case 'a':
	case 'A':
		MoveLeft(maze, player);
		break;
	case 's':
	case 'S':
		MoveDown(maze, player);
		break;
	case 'd':
	case 'D':
		MoveRight(maze, player);
		break;
	}
}

// ������ ������ const�� �����ϸ� ����Ű�� ����� ���� ������ �� ����.
void CreateBomb(char maze[21][21], const Player* player, Point* boombPos, int* boombCount)
{
	// ��ź �ִ� ��ġ ���� 5��
	if (*boombCount == 5)		return;
	// ����ȭ ������ �� ���� ����� �� ����. �� ���� �ִٸ� ��ź ��ġ �Ұ�.
	else if (maze[player->pos.y][player->pos.x] == '0')	return;

	for (int i = 0; i < *boombCount; ++i)
	{
		// �ߺ� ��ġ�� ����
		if (player->pos.x == boombPos[i].x && player->pos.y == boombPos[i].y) {
			return;
		}
	}

	boombPos[(*boombCount)++] = player->pos;
	maze[player->pos.y][player->pos.x] = '4';
}

void Fire(char maze[21][21], Player* player, Point* boombPos, int* boombCount, const Point* startPos)
{
	for (int i = 0; i < *boombCount; ++i)
	{
		maze[boombPos[i].y][boombPos[i].x] = '1';

		// �÷��̾ ��ź�� ������ ���������� ���� �̵�.
		if ((player->pos.x == boombPos[i].x && player->pos.y == boombPos[i].y))
		{
			player->pos = *startPos;
		}

		for (int j = 1; j <= player->boombPower; ++j)
		{
			if ((player->pos.x == boombPos[i].x && player->pos.y == boombPos[i].y + j) || (player->pos.x == boombPos[i].x && player->pos.y == boombPos[i].y - j)
				|| (player->pos.x == boombPos[i].x + j && player->pos.y == boombPos[i].y) || (player->pos.x == boombPos[i].x - j && player->pos.y == boombPos[i].y))
			{
				player->pos = *startPos;
			}

			if (boombPos[i].y - j >= 0)
			{
				if (maze[boombPos[i].y - j][boombPos[i].x] == '0')
				{
					// ������ ��� Ȯ���� ���Ѵ�
					if (rand() % 100 < 5)
					{
						int percent = rand() % 100;
						if (percent < 70)
						{
							maze[boombPos[i].y - j][boombPos[i].x] = '5';
						}
						else if (percent < 80)
						{
							maze[boombPos[i].y - j][boombPos[i].x] = '6';
						}
						else
						{
							maze[boombPos[i].y - j][boombPos[i].x] = '7';
						}
					}

					else	maze[boombPos[i].y - j][boombPos[i].x] = '1';
				}
			}

			if (boombPos[i].y + j < 20)
			{
				if (maze[boombPos[i].y + j][boombPos[i].x] == '0')
				{
					if (rand() % 100 < 5)
					{
						int percent = rand() % 100;
						if (percent < 70)
						{
							maze[boombPos[i].y + j][boombPos[i].x] = '5';
						}
						else if (percent < 80)
						{
							maze[boombPos[i].y + j][boombPos[i].x] = '6';
						}
						else
						{
							maze[boombPos[i].y + j][boombPos[i].x] = '7';
						}
					}

					else	maze[boombPos[i].y + j][boombPos[i].x] = '1';
				}
			}

			if (boombPos[i].x - j >= 0)
			{
				if (maze[boombPos[i].y][boombPos[i].x - j] == '0')
				{
					if (rand() % 100 < 5)
					{
						int percent = rand() % 100;
						if (percent < 70)
						{
							maze[boombPos[i].y][boombPos[i].x - j] = '5';
						}
						else if (percent < 80)
						{
							maze[boombPos[i].y][boombPos[i].x - j] = '6';
						}
						else
						{
							maze[boombPos[i].y][boombPos[i].x - j] = '7';
						}
					}

					else	maze[boombPos[i].y][boombPos[i].x - j] = '1';
				}
			}

			if (boombPos[i].x + j < 20)
			{
				if (maze[boombPos[i].y][boombPos[i].x + j] == '0')
				{
					if (rand() % 100 < 5)
					{
						int percent = rand() % 100;
						if (percent < 70)
						{
							maze[boombPos[i].y][boombPos[i].x + j] = '5';
						}
						else if (percent < 80)
						{
							maze[boombPos[i].y][boombPos[i].x + j] = '6';
						}
						else
						{
							maze[boombPos[i].y][boombPos[i].x + j] = '7';
						}
					}

					else	maze[boombPos[i].y][boombPos[i].x + j] = '1';
				}
			}
		}
	}

	*boombCount = 0;
}

int main()
{
	srand((unsigned int)time(NULL));

	// 20 x 20 �̷� �����
	char maze[21][21] = {};

	Player player = {};
	Point startPos;
	Point endPos;

	player.boombPower = 1;

	int boombCount = 0;
	int addBoomb = 0;

	Point boombPos[5];

	// �̷� ����
	SetMaze(maze, &player, &startPos, &endPos);
	while (true)
	{
		system("cls");
		// �̷� ���
		OutputMaze(maze, &player);

		if (player.pos.x == endPos.x && player.pos.y == endPos.y)
		{
			cout << "Ż���߽��ϴ�." << endl;
			break;
		}

		cout << "t : ��ź ��ġ, u : ��ź ��Ʈ���� i : ���б� ON/OFF" << endl;
		cout << "w : ��, a : ����, s : �Ʒ���, d : ������, q : ����" << endl;
		char input = _getch();

		if (input == 'q' || input == 'Q')	break;
		else if (input == 't' || input == 'T')	CreateBomb(maze, &player, boombPos, &boombCount);
		else if (input == 'u' || input == 'U')	Fire(maze, &player, boombPos, &boombCount, &startPos);
		else if (input == 'i' || input == 'I')
		{
			if (player.wallPush)
			{
				player.pushOnOff = !player.pushOnOff;
			}
		}
		else
		{
			MovePlayer(maze, &player, input);
		}

	}


	return 0;
}