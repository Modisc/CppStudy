#include <iostream>
#include <conio.h>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;

/*
0 : 벽
1 : 길
2 : 시작점
3 : 도착점
4 : 폭탄 아이템
5 : 폭탄 파워 증가 아이템
6 : 벽밀기 아이템
7 : 투명 아이템
8 : 웜홀
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
	startPos->x = startPos->y = 0;
	endPos->x = 19;
	endPos->y = 19;
	player->pos = *startPos;

	strcpy_s(maze[0], "21111111110000000000");
	strcpy_s(maze[1], "00000000010000111100");
	strcpy_s(maze[2], "00011111110000100000");
	strcpy_s(maze[3], "00010000010000100000");
	strcpy_s(maze[4], "00010000011111111110");
	strcpy_s(maze[5], "00010000000000100000");
	strcpy_s(maze[6], "00010000000000111100");
	strcpy_s(maze[7], "00011111110000100000");
	strcpy_s(maze[8], "00000000010000000010");
	strcpy_s(maze[9], "00000111111111110010");
	strcpy_s(maze[10], "00000100000000010010");
	strcpy_s(maze[11], "01111100000000010010");
	strcpy_s(maze[12], "00000001111111110010");
	strcpy_s(maze[13], "00000111000000010010");
	strcpy_s(maze[14], "00000100000000010010");
	strcpy_s(maze[15], "00000100111111111110");
	strcpy_s(maze[16], "00111100000000000010");
	strcpy_s(maze[17], "00000111111111110010");
	strcpy_s(maze[18], "00000000001000000000");
	strcpy_s(maze[19], "01111111111111111113");
}

void OutputMaze(char maze[21][21], Player* player)
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (maze[i][j] == '4')	cout << "♨";
			else if (player->pos.x == j && player->pos.y == i)	cout << "⊙";
			else if (maze[i][j] == '0') cout << "■";
			else if (maze[i][j] == '1')	cout << "  ";
			else if (maze[i][j] == '2')	cout << "○";
			else if (maze[i][j] == '3') cout << "☆";
			else if (maze[i][j] == '5') cout << "®";
			else if (maze[i][j] == '6') cout << "※";
			else if (maze[i][j] == '7') cout << "§";
			else cout << "//";
		}
		cout << endl;
	}

	cout << "폭탄파워 : " << player->boombPower << endl;
	cout << "벽 통과 : ";
	player->transparency == true ? cout << "ON\t" : cout << "OFF\t";
	cout << "벽 밀기 : ";
	if (player->wallPush)
	{
		cout << "가능 / ";
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
		cout << "불가능 / OFF" << endl;
	}
}

bool AddItem(char itemType, Player* player)
{
	if (itemType == '5')
	{
		if(player->boombPower < 5)	++player->boombPower;
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

		// 벽밀기 아이템이 있고, 이동하려는 칸이 벽일 경우, 내가 현재 있는 칸이 길일 경우
		else if (player->wallPush && maze[player->pos.y - 1][player->pos.x] == '0' && maze[player->pos.y][player->pos.x] == '1')
		{
			// 벽밀기 여부가 ON이고, 이동하려는 칸의 다음칸이 맵 범위 내부이고, 그 칸이 길일 때만 벽을 밀 수 있다.
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

// 포인터 변수를 const로 생성하면 가리키는 대상의 값을 변경할 수 없다.
void CreateBomb(char maze[21][21], const Player* player, Point* boombPos, int* boombCount)
{
	// 폭탄 최대 설치 개수 5개
	if (*boombCount == 5)		return;
	// 투명화 상태일 때 벽을 통과할 수 있음. 벽 위에 있다면 폭탄 설치 불가.
	else if (maze[player->pos.y][player->pos.x] == '0')	return;

	for (int i = 0; i < *boombCount; ++i)
	{
		// 중복 설치를 막음
		if (player->pos.x == boombPos[i].x && player->pos.y == boombPos[i].y) {
			return;
		}
	}

	boombPos[(*boombCount)++] = player->pos;
	maze[player->pos.y][player->pos.x] = '4';
}

void Fire(char maze[21][21], Player* player, Point* boombPos, int* boombCount)
{
	for (int i = 0; i < *boombCount; ++i)
	{
		maze[boombPos[i].y][boombPos[i].x] = '1';

		// 플레이어가 폭탄에 맞으면 시작점으로 강제 이동.
		if ((player->pos.x == boombPos[i].x && player->pos.y == boombPos[i].y))
		{
			player->pos.x = player->pos.y = 0;
		}

		for (int j = 1; j <= player->boombPower; ++j)
		{
			if ((player->pos.x == boombPos[i].x && player->pos.y == boombPos[i].y + j) || (player->pos.x == boombPos[i].x && player->pos.y == boombPos[i].y - j)
				|| (player->pos.x == boombPos[i].x + j && player->pos.y == boombPos[i].y) || (player->pos.x == boombPos[i].x - j && player->pos.y == boombPos[i].y))
			{
				player->pos.x = player->pos.y = 0;
			}

			if (boombPos[i].y - j >= 0)
			{
				if (maze[boombPos[i].y - j][boombPos[i].x] == '0')
				{
					// 아이템 드랍 확률을 구한다
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

	// 20 x 20 미로 만들기
	char maze[21][21] = {};

	Player player = {};
	Point startPos;
	Point endPos;

	player.boombPower = 1;

	int boombCount = 0;
	int addBoomb = 0;

	Point boombPos[5];

	// 미로 설정
	SetMaze(maze, &player, &startPos, &endPos);
	while (true)
	{
		system("cls");
		// 미로 출력
		OutputMaze(maze, &player);

		if (player.pos.x == endPos.x && player.pos.y == endPos.y)
		{
			cout << "탈출했습니다." << endl;
			break;
		}

		cout << "t : 폭탄 설치, u : 폭탄 터트리기 i : 벽밀기 ON/OFF" << endl;
		cout << "w : 위, a : 왼쪽, s : 아래쪽, d : 오른쪽, q : 종료" << endl;
		char input = _getch();

		if (input == 'q' || input == 'Q')	break;
		else if (input == 't' || input == 'T')	CreateBomb(maze, &player, boombPos, &boombCount);
		else if (input == 'u' || input == 'U')	Fire(maze, &player, boombPos, &boombCount);
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