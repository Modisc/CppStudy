#include <iostream>
#include <time.h>
#include <conio.h>

enum AI_MODE {
	AI_EASY = 1,
	AI_HARD
};

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

void SetBingoMap(int* map);
void Shuffle(int* map);
AI_MODE SelectAIMode();
void PrintMap(int* map, int bingoCount, bool isAiMap = false);
bool DeleteNumber(int* map, int inputNum);
int SelectAiNumber(int* map, AI_MODE aiMode);
int BingoCounting(int* map);
int BingoCountingRow(int* map);
int BingoCountingCol(int* map);
int BingoCountingLT(int* map);
int BingoCountingRT(int* map);

int main() {
	int bingoMap[25];
	int inputNum;
	int bingoLine = 0;

	bool isDuplicate = true;

	int aiBingoMap[25];
	AI_MODE aiMode;
	int aiRowStar = 0, aiColStar = 0;
	int aiBingoLine = 0;
	srand((unsigned int)time(NULL));

	SetBingoMap(bingoMap);
	SetBingoMap(aiBingoMap);

	Shuffle(bingoMap);
	Shuffle(aiBingoMap);

	aiMode = SelectAIMode();

	while (true) {
		system("cls");

		std::cout << "================= Player =================" << std::endl;
		PrintMap(bingoMap, bingoLine);

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

		PrintMap(aiBingoMap, aiBingoLine);

		if (bingoLine >= 5) {
			std::cout << std::endl << "Player 5줄 빙고 완성 ! 플레이어 승리 ! " << std::endl;
			break;
		}

		else if (aiBingoLine >= 5) {
			std::cout << std::endl << "AI 5줄 빙고 완성 ! 플레이어 패배 ! " << std::endl;
			break;
		}


		std::cout << std::endl << "1~25 사이의 숫자를 입력하세요(0 : 종료) : ";
		std::cin >> inputNum;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			continue;
		}

		else if (inputNum == 0)		break;

		else if (inputNum < 0 || inputNum>25)	continue;

		bingoLine = 0;
		aiBingoLine = 0;

		isDuplicate = DeleteNumber(bingoMap, inputNum);

		if (isDuplicate)		continue;

		DeleteNumber(aiBingoMap, inputNum);

		inputNum = SelectAiNumber(aiBingoMap, aiMode);

		DeleteNumber(bingoMap, inputNum);
		DeleteNumber(aiBingoMap, inputNum);

		bingoLine = BingoCounting(bingoMap);
		aiBingoLine = BingoCounting(aiBingoMap);

	}

	std::cout << std::endl << "게임을 종료합니다" << std::endl;

	return 0;
}



void SetBingoMap(int* map) {
	for (int i = 0; i < 25; ++i) {
		map[i] = i + 1;
	}
}

void Shuffle(int* map) {
	int idx1, idx2, tmp;
	for (int i = 0; i < 100; ++i) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		tmp = map[idx1];
		map[idx1] = map[idx2];
		map[idx2] = tmp;
	}
}

AI_MODE SelectAIMode() {
	int aiMode;
	while (true) {
		system("cls");
		std::cout << "AI 모드를 선택해주세요." << std::endl << "1. Easy" << std::endl << "2. Hard" << std::endl;
		std::cin >> aiMode;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			continue;
		}

		else if (aiMode >= AI_EASY && aiMode <= AI_HARD)		break;
	}

	return (AI_MODE)aiMode;
}

void PrintMap(int* map, int bingoLine, bool isAiMap) {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (isAiMap == true) {
				std::cout << "*\t";
			}
			else {
				if (map[i * 5 + j] == INT_MAX)	std::cout << "*\t";
				else	std::cout << map[i * 5 + j] << "\t";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "Bingo Line : " << bingoLine << std::endl;
}

bool DeleteNumber(int* map, int inputNum) {
	for (int i = 0; i < 25; ++i) {
		if (inputNum == map[i]) {
			map[i] = INT_MAX;
			return false;
		}
	}
	return true;
}

int SelectAiNumber(int* map, AI_MODE aiMode) {

	int noneSelected[25];
	int noneSelectedCount = 0;

	switch (aiMode)
	{
	case AI_EASY:
		noneSelectedCount = 0;
		for (int i = 0; i < 25; ++i) {
			if (map[i] != INT_MAX) {
				noneSelected[noneSelectedCount++] = map[i];
			}
		}
		return noneSelected[rand() % noneSelectedCount];
		
	case AI_HARD:
		int line = 0;
		int starCount = 0;
		int saveCount = 0;

		for (int i = 0; i < 5; ++i) {
			starCount = 0;
			for (int j = 0; j < 5; ++j) {
				if (map[i * 5 + j] == INT_MAX) ++starCount;
			}

			if (starCount < 5 && starCount > saveCount) {
				line = i;
				saveCount = starCount;
			}
		}

		for (int i = 0; i < 5; ++i) {
			starCount = 0;
			for (int j = 0; j < 5; ++j) {
				if (map[j * 5 + i] == INT_MAX) ++starCount;
			}

			if (starCount < 5 && starCount > saveCount) {
				line = i + 5;
				saveCount = starCount;
			}
		}

		starCount = 0;
		for (int i = 0; i < 25; i += 6) {
			if (map[i] == INT_MAX)		++starCount;
		}

		if (starCount < 5 && starCount > saveCount) {
			line = LN_LT;
			saveCount = starCount;
		}

		starCount = 0;
		for (int i = 4; i <= 20; i += 4) {
			if (map[i] == INT_MAX)		++starCount;
		}

		if (starCount < 5 && starCount > saveCount) {
			line = LN_RT;
			saveCount = starCount;
		}

		if (line <= LN_H5) {
			for (int i = 0; i < 5; ++i) {
				if (map[line * 5 + i] != INT_MAX) {
					return map[line * 5 + i];
				}
			}
		}

		else if (line <= LN_V5) {
			for (int i = 0; i < 5; ++i) {
				if (map[i * 5 + (line - 5)] != INT_MAX) {
					return map[i * 5 + (line - 5)];
				}
			}
		}

		else if (line == LN_LT) {
			for (int i = 0; i < 25; i += 6) {
				if (map[i] != INT_MAX) {
					return map[i];
				}
			}
		}

		else if (line == LN_RT) {
			for (int i = 0; i <= 20; i += 4) {
				if (map[i] != INT_MAX) {
					return map[i];
				}
			}
		}

		break;
	}

	return -1;
}

int BingoCounting(int* map) {
	int bingoCount = 0;

	bingoCount += BingoCountingRow(map);
	bingoCount += BingoCountingCol(map);
	bingoCount += BingoCountingLT(map);
	bingoCount += BingoCountingRT(map);

	return bingoCount;
}

int BingoCountingRow(int* map) {
	int rowStar = 0, bingoCount = 0;
	for (int i = 0; i < 5; ++i) {
		rowStar = 0;
		for (int j = 0; j < 5; ++j) {
			if (map[i * 5 + j] == INT_MAX)	++rowStar;
		}
		if (rowStar == 5)	++bingoCount;
	}
	return bingoCount;
}

int BingoCountingCol(int* map) {
	int colStar = 0, bingoCount = 0;
	for (int i = 0; i < 5; ++i) {
		colStar = 0;
		for (int j = 0; j < 5; ++j) {
			if (map[j * 5 + i] == INT_MAX)	++colStar;
		}
		if (colStar == 5)	++bingoCount;
	}
	return bingoCount;
}

int BingoCountingLT(int* map) {
	int rowStar = 0, bingoCount = 0;
	for (int i = 0; i < 25; i += 6) {
		if (map[i] == INT_MAX)		++rowStar;
	}
	if (rowStar == 5)	++bingoCount;
	return bingoCount;
}

int BingoCountingRT(int* map) {
	int rowStar = 0, bingoCount = 0;
	for (int i = 4; i <= 20; i += 4) {
		if (map[i] == INT_MAX)		++rowStar;
	}
	if (rowStar == 5)	++bingoCount;
	return bingoCount;
}