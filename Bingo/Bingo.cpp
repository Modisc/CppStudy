#include <iostream>
#include <time.h>
#include <conio.h>

enum AI_MODE {
	AI_EASY = 1,
	AI_HARD
};

// AI 하드모드에서 가로 5줄, 세로 5줄, 대각선 2줄 중에서
// 가장 빙고 가능성이 높은 줄을 선택할 때 사용할 변수
enum LINE_NUMBER {
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};

int main() {
	int bingoMap[25];
	int inputNum;
	int idx1, idx2, tmp;
	int rowStar, colStar;
	int bingoCount = 0;
	bool isDuplicate = true;

	int aiBingoMap[25];
	int aiMode;
	int aiRowStar, aiColStar;
	int aiBingoCount = 0;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 25; ++i) {
		bingoMap[i] = i + 1;
		aiBingoMap[i] = i + 1;
	}

	for (int i = 0; i < 100; ++i) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		tmp = bingoMap[idx1];
		bingoMap[idx1] = bingoMap[idx2];
		bingoMap[idx2] = tmp;

		// AI 빙고판도 숫자를 섞어줌.
		// 위의 idx 그대로 사용하면 플레이어 빙고 판과 똑같아짐.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		tmp = aiBingoMap[idx1];
		aiBingoMap[idx1] = aiBingoMap[idx2];
		aiBingoMap[idx2] = tmp;
	}

	// AI의 값 선택 기회를 줘야함. 이 때, 단순 랜덤함수 사용은 중복 확률이 존재하므로 문제가 된다.
	// AI 빙고 판 중에서 *로 변경되지 않은 숫자 중 임의의 숫자 하나를 선택한다. (Easy Mode)
	// AI 빙고 판 중에서 *로 변경되지 않은 숫자 중 *로 바꿨을 때 빙고가 될 확률이 높은 숫자를 선택한다. (Hard Mode)
	// AI 난이도 선택
	while (true) {
		system("cls");
		std::cout << "AI 모드를 선택해주세요." << std::endl << "1. Easy" << std::endl << "2. Hard" << std::endl;
		std::cin >> aiMode;

		if (aiMode >= AI_EASY && aiMode <= AI_HARD)		break;
	}

	// EasyMode
	// 현재 AI의 숫자 목록 중 *로 변경되지 않은 숫자 목록을 만든다.
	// 그 목록 중 하나를 랜덤하게 선택한다.
	int noneSelected[25];
	int noneSelectedCount = 0;
	

	while (true) {
		system("cls");

		std::cout << "================= Player =================" << std::endl;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (bingoMap[i * 5 + j] == INT_MAX)	std::cout << "*\t";
				else	std::cout << bingoMap[i * 5 + j] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "Player Bingo Count : " << bingoCount << std::endl;

		std::cout << std::endl << "================= AI =================" << std::endl;
		
		switch (aiMode)
		{
		case AI_EASY:
			std::cout << "AI MODE : EASY" << std::endl << std::endl;
			break;
		case AI_HARD:
			std::cout << "AI MODE : HARD" << std::endl << std::endl;
			break;
		}

		// AI 빙고 판은 *만 출력되도록 함.
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				/*if (aiBingoMap[i * 5 + j] == INT_MAX)	std::cout << "*\t";
				else	std::cout << aiBingoMap[i * 5 + j] << "\t";*/
				std::cout << "*\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "AI Bingo Count : " << aiBingoCount << std::endl;

		if (bingoCount >= 5) {
			std::cout << std::endl << "Player 5줄 빙고 완성 ! 플레이어 승리 ! " << std::endl;
			break;
		}

		else if (aiBingoCount >= 5) {
			std::cout << std::endl << "AI 5줄 빙고 완성 ! 플레이어 패배 ! " << std::endl;
			break;
		}

		bingoCount = 0;
		aiBingoCount = 0;

		std::cout << std::endl << "1~25 사이의 숫자를 입력하세요(0 : 종료) : ";
		std::cin >> inputNum;

		if (inputNum == 0)		break;

		if (inputNum < 0 || inputNum>25)	continue;

		isDuplicate = true;

		// 플레이어 값 입력 시, 중복 체크 및 해당 숫자 삭제
		for (int i = 0; i < 25; ++i) {
			if (inputNum == bingoMap[i]) {
				bingoMap[i] = INT_MAX;
				isDuplicate = false;
			}
		}

		if (isDuplicate)		continue;

		// 플레이어 값 입력 시, AI 숫자 삭제
		for (int i = 0; i < 25; ++i) {
			if (inputNum == aiBingoMap[i]) {
				aiBingoMap[i] = INT_MAX;
				// 플레이어가 입력한 숫자를 찾아서 *로 바꿨으므로
				// 선택안된 숫자 개수가 1 줄어든다.
			}
		}

		// AI의 선택. AI MODE에 따라서 선택하는 방식이 달라진다
		switch (aiMode)
		{
			// 지워지지 않은 숫자 중 임의의 숫자 선택하는 모드
		case AI_EASY:
			// 선택 안 된 숫자목록을 만들어준다.
			// 선택 안 된 숫자 개수는 목록을 만들 때 함께 계산된다.
			noneSelectedCount = 0;
			for (int i = 0; i < 25; ++i) {
				if (aiBingoMap[i] != INT_MAX) {
					noneSelected[noneSelectedCount++] = aiBingoMap[i];
				}
			}
			inputNum = noneSelected[rand() % noneSelectedCount];
			break;
			
			// 빙고 가능성이 높은 숫자를 선택하는 모드
			// 현재의 HARD 모드는 선택된 라인 중에서 가장 앞에 있는 숫자를 제거한다.
			// 차후 Vector 혹은 동적할당을 이용해서 선택한 라인 중 제거되지 않은 숫자들을 배열로 받아서
			// 그 숫자들 중 다시 임의선택 하는 방식으로 게임을 진행해도 나쁘지 않을 것 같다.
		case AI_HARD:
			// 1. 빙고 가능성이 가장 높은 줄을 선택한다(가로, 세로, 대각선 중)
			// 2. 그 줄에 있는 숫자 중 하나를 *로 만들어준다.
			int line = 0;
			int starCount = 0;
			int saveCount = 0; // 이전에 확인한 줄의 별 개수. 최댓값을 저장하고 있음.

			// 가로 라인 중 가장 별이 많은 라인 찾기
			for (int i = 0; i < 5; ++i) {
				starCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (aiBingoMap[i * 5 + j] == INT_MAX) ++starCount;
				}
				
				// 별이 5개 미만이어야 빙고가 아닌 상태이고 기존에 별이 가장 많던 라인보다
				// 현재 라인의 별이 더 많아야 현재 라인을 가장 별이 많은 라인으로 선택함.
				if (starCount < 5 && starCount > saveCount) {
					// 가로 라인은 0~4로 의미 부여함.(위의 LINE_NUMBER 열거형)
					line = i;
					saveCount = starCount;
				}
			}

			// 가로 라인 중 별이 가장 많은 라인은 이미 구해짐.
			// 이 라인과 세로 라인들을 비교하여 별이 가장 많은 라인을 구한다.
			for (int i = 0; i < 5; ++i) {
				starCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (aiBingoMap[j * 5 + i] == INT_MAX) ++starCount;
				}

				if (starCount < 5 && starCount > saveCount) {
					// 세로 라인은 5~9로 의미 부여함.(위의 LINE_NUMBER 열거형)
					line = i + 5;
					saveCount = starCount;
				}
			}

			// 좌상단 대각선과 앞에서 구한 라인을 비교하여 별이 가장 많은 라인 선택
			starCount = 0;
			for (int i = 0; i < 25; i += 6) {
				if (aiBingoMap[i] == INT_MAX)		++starCount;
			}

			if (starCount < 5 && starCount > saveCount) {
				// 좌상단 대각선 라인은 10 으로 의미 부여함.(위의 LINE_NUMBER 열거형)
				line = LN_LT;
				saveCount = starCount;
			}

			// 우상단 대각선과 앞에서 구한 라인들을 비교하여 별이 가장 많은 라인 선택
			starCount = 0;
			for (int i = 4; i <= 20; i += 4) {
				if (aiBingoMap[i] == INT_MAX)		++aiRowStar;
			}

			if (starCount < 5 && starCount > saveCount) {
				// 우상단 대각선 라인은 11 로 의미 부여함.(위의 LINE_NUMBER 열거형)
				line = LN_RT;
				saveCount = starCount;
			}

			// 모든 라인을 조사했으므로 line에는 빙고 가능성이 가장 높은 줄 번호가 저장되었음.
			// 해당 줄에 있는 *이 아닌 숫자 중 1개를 선택하면 된다.
			
			// 가로 줄일 경우
			if (line <= LN_H5) {
				for (int i = 0; i < 5; ++i) {
					if (aiBingoMap[line * 5 + i] != INT_MAX) {
						inputNum = aiBingoMap[line * 5 + i];
						break;
					}
				}
			}

			// 세로 줄일 경우
			else if (line <= LN_V5) {
				for (int i = 0; i < 5; ++i) {
					if (aiBingoMap[i * 5 + (line - 5)] != INT_MAX) {
						inputNum = aiBingoMap[i * 5 + (line - 5)];
						break;
					}
				}
			}

			// 좌상단 대각선
			else if (line == LN_LT) {
				for (int i = 0; i < 25; i += 6) {
					if (aiBingoMap[i] != INT_MAX) {
						inputNum = aiBingoMap[i];
						break;
					}
				}
			}

			// 우상단 대각선
			else if (line == LN_RT) {
				for (int i = 0; i <= 20; i += 4) {
					if (aiBingoMap[i] != INT_MAX) {
						inputNum = aiBingoMap[i];
						break;
					}
				}
			}

			break;
		}

		// AI 값 입력 시,  해당 숫자 삭제
		for (int i = 0; i < 25; ++i) {
			if (inputNum == bingoMap[i]) {
				bingoMap[i] = INT_MAX;
			}
		}

		// AI 값 입력 시, AI 숫자 삭제
		for (int i = 0; i < 25; ++i) {
			if (inputNum == aiBingoMap[i]) {
				aiBingoMap[i] = INT_MAX;
				// 플레이어가 입력한 숫자를 찾아서 *로 바꿨으므로
				// 선택안된 숫자 개수가 1 줄어든다.
				--noneSelectedCount;
			}
		}

		//가로 세로 빙고 확인
		for (int i = 0; i < 5; ++i) {
			rowStar = colStar = 0;
			aiRowStar = aiColStar = 0;
			for (int j = 0; j < 5; ++j) {
				if (bingoMap[i * 5 + j] == INT_MAX)	++rowStar;
				if (bingoMap[j * 5 + i] == INT_MAX)	++colStar;
				if (aiBingoMap[i * 5 + j] == INT_MAX)	++aiRowStar;
				if (aiBingoMap[j * 5 + i] == INT_MAX)	++aiColStar;
			}
			if (rowStar == 5)	++bingoCount;
			if (colStar == 5)	++bingoCount;
			if (aiRowStar == 5)	++aiBingoCount;
			if (aiColStar == 5)	++aiBingoCount;
		}

		//좌측 상단 대각선 빙고 확인
		rowStar = 0;
		aiRowStar = 0;
		for (int i = 0; i < 25; i += 6) {
			if (bingoMap[i] == INT_MAX)		++rowStar;
			if (aiBingoMap[i] == INT_MAX)		++aiRowStar;
		}
		if (rowStar == 5)	++bingoCount;
		if (aiRowStar == 5)	++aiBingoCount;

		//우측 상단 대각선 빙고 확인
		rowStar = 0;
		aiRowStar = 0;
		for (int i = 4; i <= 20; i += 4) {
			if (bingoMap[i] == INT_MAX)		++rowStar;
			if (aiBingoMap[i] == INT_MAX)		++aiRowStar;
		}
		if (rowStar == 5)	++bingoCount;
		if (aiRowStar == 5)	++aiBingoCount;

	}

	std::cout << std::endl << "게임을 종료합니다" << std::endl;

	return 0;
}