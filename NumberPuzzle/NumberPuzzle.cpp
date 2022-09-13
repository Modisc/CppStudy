#include <iostream>
#include <time.h>
#include <cmath>

// console input output 헤더파일
// 콘솔창에서 입출력하는 기능들을 제공하는 헤더파일이다.
#include <conio.h>

int main() {
	srand((unsigned int)time(NULL));
	int number[25];
	int idx1, idx2, tmp;

	// 배열의 맨 마지막 값을 공백으로 처리한다.
	for (int i = 0; i < 24; ++i) {
		number[i] = i+1;
	}
	number[24] = INT_MAX;

	int currStarIdx = 24;
	bool isClear;
	int inversion = 0;

	// Parity Error에 의해서 절대 풀 수 없는 퍼즐이 나올 수 있음
	// 그런 경우 퍼즐을 다시 생성함.
	while(true) {
		for (int i = 0; i < 100; ++i) {
			idx1 = rand() % 24;
			idx2 = rand() % 24;

			tmp = number[idx1];
			number[idx1] = number[idx2];
			number[idx2] = tmp;
		}

		for (int i = 0; i < 23; ++i) {
			if (number[i] > number[i + 1])		++inversion;
		}

		if (sizeof(number) / sizeof(number[0]) % 2 == 0) {
			if (inversion % 2 != 0)		break;
		}

		else {
			if (inversion % 2 == 0)		break;
		}
	}
	

	while (true) {
		system("cls");
		// 1차원 배열을 2차원 배열처럼 처리할 수 있도록 한 것임.
		// 줄번호 * 가로개수 * 칸번호
		// 이런 공식이 2D 평면에서 무언가를 구해낼 때 많이 사용됨
		// 알아두면 나중에 유용함.
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; j++) {
				if (number[i * 5 + j] == INT_MAX)		std::cout << "*\t";
				else	std::cout << number[i * 5 + j] << "\t";
			}
			std::cout << std::endl;
		}

		isClear = true;
		for (int i = 0; i < 24; ++i) {
			if (number[i] != i + 1) {
				isClear = false;
				break;
			}
		}

		if (isClear) {
			std::cout << std::endl << "클리어 하였습니다!" << std::endl;
			break;
		}

		std::cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료" << std::endl;

		// 플레이어가 w, a 등 문자만 입력하면 자동으로 동작하기를 원한다.
		// cin을 이용할 경우 문자 입력 후 Enter를 쳐야지 입력이 완료된다.
		// _getch() 함수는 문자 1개를 입력받는 함수로, Enter를 치지 않아도 문자를 누르는 순간
		// 바로 그 문자를 반환하고 종료된다.
		char playerInput = _getch();

		if (playerInput == 'q' || playerInput == 'Q')		break;
		
		switch (playerInput) {
		case 'w':
		case'W':
			if (currStarIdx > 4) {
				number[currStarIdx] = number[currStarIdx - 5];
				number[currStarIdx - 5] = INT_MAX;
				currStarIdx -= 5;
			}
			break;
		case 's':
		case'S':
			if (currStarIdx < 20) {
				number[currStarIdx] = number[currStarIdx + 5];
				number[currStarIdx + 5] = INT_MAX;
				currStarIdx += 5;
			}
			break;
		case 'a':
		case'A':
			if (currStarIdx % 5 != 0) {
				number[currStarIdx] = number[currStarIdx - 1];
				number[currStarIdx - 1] = INT_MAX;
				currStarIdx -= 1;
			}
			break;
		case 'd':
		case'D':
			if (currStarIdx % 5 != 4) {
				number[currStarIdx] = number[currStarIdx + 1];
				number[currStarIdx + 1] = INT_MAX;
				currStarIdx += 1;
			}
			break;
		default:
			break;
		}
	}

	std::cout << std::endl << "게임을 종료합니다." << std::endl;
	

	return 0;
}
