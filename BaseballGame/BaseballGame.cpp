#include <iostream>
#include <time.h>

int main() {
	int totalNum[9];
	int targetNum[3];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 9; i++) {
		totalNum[i] = i + 1;
	}

	int idx1, idx2, tmp;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		tmp = totalNum[idx1];
		totalNum[idx1] = totalNum[idx2];
		totalNum[idx2] = tmp;
	}

	for (int i = 0; i < 3; i++) {
		targetNum[i] = totalNum[i];
		//std::cout << targetNum[i] << "\t";
	}

	std::cout << std::endl;

	std::cout << "TargetNum 설정이 완료되었습니다." << std::endl;

	int playerNum[3], strike, ball;
	bool error = false;

	while (1) {
		strike = 0, ball = 0;
		error = false;

		std::cout << std::endl << "*\t*\t*" << std::endl << std::endl;
		std::cout << "1~9 사이의 숫자 3개를 입력하세요(0 : 종료)" << std::endl << std::endl;
		std::cin >> playerNum[0] >> playerNum[1] >> playerNum[2];
		
		/*for (int i = 0; i < 3; ++i) {
			if (playerNum[i] == 0) {
				std::cout << "게임을 종료합니다." << std::endl;
				return 0;
			}
		}*/

		if (playerNum[0] == 0 || playerNum[1] == 0 || playerNum[2] == 0) {
			std::cout << "게임을 종료합니다." << std::endl;
			return 0;
		}

		/*for (int i = 0; i < 3; ++i) {
			if (playerNum[i] < 0 || playerNum[i] > 9) {
				std::cout << "잘못된 숫자를 입력하였습니다." << std::endl;
				error = true;
				break;
			}
		}*/

		if (playerNum[0] < 0 || playerNum[0] > 9 || playerNum[1] < 0 || playerNum[1] > 9 || playerNum[2] < 0 || playerNum[2] > 9) {
			std::cout << "잘못된 숫자를 입력하였습니다." << std::endl;
			continue;
		}

		if (playerNum[0] == playerNum[1] || playerNum[0] == playerNum[2] || playerNum[1] == playerNum[2]) {
			std::cout << "중복된 숫자를 입력하였습니다." << std::endl;
			// error = true;
			continue;
		}
			
		//if (error)	continue;

		for (int i = 0; i < 3; ++i) {
			if (targetNum[i] == playerNum[i])	++strike;

			else {
				for (int j = 0; j < 3; ++j) {
					if (i == j)	continue;
					else {
						if (targetNum[i] == playerNum[j]) {
							++ball;
							break;
						}	
					}
				}
			}
		}

		if (strike == 0 && ball == 0) std::cout << "Out" << std::endl;

		else if (strike == 3) {
			std::cout << "정답입니다. 게임을 종료합니다." << std::endl;
			return 0;
		}

		else {
			std::cout << strike << "strike " << ball << "ball" << std::endl;
		}
	}

	return 0;
}