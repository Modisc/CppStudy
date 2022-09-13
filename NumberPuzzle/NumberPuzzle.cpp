#include <iostream>
#include <time.h>
#include <cmath>

// console input output �������
// �ܼ�â���� ������ϴ� ��ɵ��� �����ϴ� ��������̴�.
#include <conio.h>

int main() {
	srand((unsigned int)time(NULL));
	int number[25];
	int idx1, idx2, tmp;

	// �迭�� �� ������ ���� �������� ó���Ѵ�.
	for (int i = 0; i < 24; ++i) {
		number[i] = i+1;
	}
	number[24] = INT_MAX;

	int currStarIdx = 24;
	bool isClear;
	int inversion = 0;

	// Parity Error�� ���ؼ� ���� Ǯ �� ���� ������ ���� �� ����
	// �׷� ��� ������ �ٽ� ������.
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
		// 1���� �迭�� 2���� �迭ó�� ó���� �� �ֵ��� �� ����.
		// �ٹ�ȣ * ���ΰ��� * ĭ��ȣ
		// �̷� ������ 2D ��鿡�� ���𰡸� ���س� �� ���� ����
		// �˾Ƶθ� ���߿� ������.
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
			std::cout << std::endl << "Ŭ���� �Ͽ����ϴ�!" << std::endl;
			break;
		}

		std::cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ����" << std::endl;

		// �÷��̾ w, a �� ���ڸ� �Է��ϸ� �ڵ����� �����ϱ⸦ ���Ѵ�.
		// cin�� �̿��� ��� ���� �Է� �� Enter�� �ľ��� �Է��� �Ϸ�ȴ�.
		// _getch() �Լ��� ���� 1���� �Է¹޴� �Լ���, Enter�� ġ�� �ʾƵ� ���ڸ� ������ ����
		// �ٷ� �� ���ڸ� ��ȯ�ϰ� ����ȴ�.
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

	std::cout << std::endl << "������ �����մϴ�." << std::endl;
	

	return 0;
}
