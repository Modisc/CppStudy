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
	// MazeList.txt 파일을 읽어와서 미로 목록을 만든다.
	FILE* file = NULL;
	fopen_s(&file, "MazeList.txt", "rt");
	char** mazeList = {};

	if (file)
	{
		char count;

		// 문자 '4' 가 count에 들어감.
		// '4' 의 아스키값은 52.
		// 즉, count에는 정수값 52가 들어가있는 것과 마찬가지
		fread(&count, 1, 1, file);

		// 문자 '4' 를 정수값 4 로 변경하여준다.
		int mazeCount = atoi(&count);

		fread(&count, 1, 1, file); // 4 다음 '\n' 문자 읽어들이도록 한 것임.

		// 미로 개수만큼 char* 배열을 할당.
		mazeList = new char* [mazeCount];

		for (int i = 0; i < mazeCount; ++i)
		{
			int nameCount = 0;

			// 현재 미로의 파일 이름을 저장할 배열을 256개로 할당.
			// 미리 넉넉하게 할당해둔 것이다.
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

			// 파일 이름을 모두 읽었다면 문자열의 마지막에 0을 넣어서
			// 문자열의 끝을 알려준다.
			mazeList[i][nameCount] = 0;
		}

		fclose(file);

		// 읽을 파일 목록을 만들었으므로 각 파일 중 하나를 선택해서
		// 미로를 읽어와서 설정한다.

		for (int i = 0; i < mazeCount; ++i)
		{
			cout << i + 1 << ". " << mazeList[i] << endl;
		}

		cout << "미로를 선택하세요 : ";
		int input;
		cin >> input;

		fopen_s(&file, mazeList[input - 1], "rt");

		if (file)
		{
			// 미로의 세로 줄 수만큼 반복하며 각 줄 별로 읽어온다.
			for (int i = 0; i < 20; ++i)
			{
				fread(maze[i], 1, 20, file);

				// 현재 줄의 미로를 검사하여 시작점, 혹은
				// 도착점이 있는지를 판단한다.
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
				// 개행문자를 읽어온다.
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

void Fire(char maze[21][21], Player* player, Point* boombPos, int* boombCount, const Point* startPos)
{
	for (int i = 0; i < *boombCount; ++i)
	{
		maze[boombPos[i].y][boombPos[i].x] = '1';

		// 플레이어가 폭탄에 맞으면 시작점으로 강제 이동.
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