#include <iostream>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;

/*
0 : 벽
1 : 길
2 : 시작점
3 : 도착점
*/

struct Point
{
	int x;
	int y;
};

void SetMaze(char maze[21][21], Point* playerPos, Point* startPos, Point* endPos)
{
	startPos->x = startPos->y = 0;
	endPos->x = 19;
	endPos->y = 19;
	*playerPos = *startPos;

	strcpy_s(maze[0],  "21111111110000000000");
	strcpy_s(maze[1],  "00000000010000111100");
	strcpy_s(maze[2],  "00011111110000100000");
	strcpy_s(maze[3],  "00010000010000100000");
	strcpy_s(maze[4],  "00010000011111111110");
	strcpy_s(maze[5],  "00010000000000100000");
	strcpy_s(maze[6],  "00010000000000111100");
	strcpy_s(maze[7],  "00011111110000100000");
	strcpy_s(maze[8],  "00000000010000000010");
	strcpy_s(maze[9],  "00000111111111110010");
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

void OutputMaze(char maze[21][21], Point* playerPos)
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (playerPos->x == j && playerPos->y == i)	cout << "⊙";
			else if (maze[i][j] == '0') cout << "■"; 
			else if (maze[i][j] == '1')	cout << "  ";
			else if (maze[i][j] == '2')	cout << "○";
			else if (maze[i][j] == '3') cout << "☆";
			else cout << "■";
		}
		cout << endl;
	}
}

bool ComputeVisibleRange(Point* playerPos, int x, int y)
{
	if ((x == playerPos->x+1 && y == playerPos->y) || (x == playerPos->x-1 && y == playerPos->y) || (x == playerPos->x && y == playerPos->y+1) ||
		(x == playerPos->x && y == playerPos->y-1) || (x == playerPos->x+1 && y == playerPos->y+1) || (x == playerPos->x+1 && y == playerPos->y-1)
		|| (x == playerPos->x-1 && y == playerPos->y+1) || (x == playerPos->x-1 && y == playerPos->y-1))
	{
		return true;
	}
	return false;
}

void BlindOutputMaze(char maze[21][21], Point* playerPos)
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (playerPos->x == j && playerPos->y == i)	cout << "⊙";
			else if (ComputeVisibleRange(playerPos, j, i) && maze[i][j] == '0') cout << "■";
			else if (ComputeVisibleRange(playerPos, j, i) && maze[i][j] == '1')	cout << "  ";
			else if (ComputeVisibleRange(playerPos, j, i) && maze[i][j] == '2')	cout << "○";
			else if (ComputeVisibleRange(playerPos, j, i) && maze[i][j] == '3') cout << "☆";
			else if (ComputeVisibleRange(playerPos, j, i) && (i == 20 || j == 20)) cout << "■";
			else cout << "//";
		}
		cout << endl;
	}
}

void MoveUp(char maze[21][21], Point* playerPos) {
	if (playerPos->y - 1 >= 0) {
		if (maze[playerPos->y - 1][playerPos->x] != '0') {
			--playerPos->y;
		}
	}
}

void MoveDown(char maze[21][21], Point* playerPos) {
	if (playerPos->y + 1 < 20) {
		if (maze[playerPos->y + 1][playerPos->x] != '0') {
			++playerPos->y;
		}
	}
}

void MoveRight(char maze[21][21], Point* playerPos) {
	if (playerPos->x + 1 < 20) {
		if (maze[playerPos->y][playerPos->x + 1] != '0') {
			++playerPos->x;
		}
	}
}

void MoveLeft(char maze[21][21], Point* playerPos) {
	if (playerPos->x - 1 >= 0) {
		if (maze[playerPos->y][playerPos->x - 1] != '0') {
			--playerPos->x;
		}
	}
}

void MovePlayer(char maze[21][21], Point* playerPos, char input)
{
	switch (input)
	{
	case 'w':
	case 'W':
		MoveUp(maze, playerPos);
		break;
	case 'a':
	case 'A':
		MoveLeft(maze, playerPos);
		break;
	case 's':
	case 'S':
		MoveDown(maze, playerPos);
		break;
	case 'd':
	case 'D':
		MoveRight(maze, playerPos);
		break;
	}
}

int main()
{
	// 20 x 20 미로 만들기
	char maze[21][21] = {};

	Point playerPos;
	Point startPos;
	Point endPos;

	// 미로 설정
	SetMaze(maze, &playerPos, &startPos, &endPos);
	while (true)
	{
		system("cls");
		// 미로 출력
		OutputMaze(maze, &playerPos);
		// 시야 제한 미로
		cout << endl << endl;
		BlindOutputMaze(maze, &playerPos);

		if (playerPos.x == endPos.x && playerPos.y == endPos.y)
		{
			cout << "탈출했습니다." << endl;
			break;
		}

		cout << "w : 위, a : 왼쪽, s : 아래쪽, d : 오른쪽, q : 종료" << endl;
		char input = _getch();

		if (input == 'q' || input == 'Q')	break;
		MovePlayer(maze, &playerPos, input);
	}
	

	return 0;
}