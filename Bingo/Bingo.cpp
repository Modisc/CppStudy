#include <iostream>
#include <time.h>
#include <conio.h>

enum AI_MODE {
	AI_EASY = 1,
	AI_HARD
};

// AI �ϵ��忡�� ���� 5��, ���� 5��, �밢�� 2�� �߿���
// ���� ���� ���ɼ��� ���� ���� ������ �� ����� ����
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

		// AI �����ǵ� ���ڸ� ������.
		// ���� idx �״�� ����ϸ� �÷��̾� ���� �ǰ� �Ȱ�����.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		tmp = aiBingoMap[idx1];
		aiBingoMap[idx1] = aiBingoMap[idx2];
		aiBingoMap[idx2] = tmp;
	}

	// AI�� �� ���� ��ȸ�� �����. �� ��, �ܼ� �����Լ� ����� �ߺ� Ȯ���� �����ϹǷ� ������ �ȴ�.
	// AI ���� �� �߿��� *�� ������� ���� ���� �� ������ ���� �ϳ��� �����Ѵ�. (Easy Mode)
	// AI ���� �� �߿��� *�� ������� ���� ���� �� *�� �ٲ��� �� ���� �� Ȯ���� ���� ���ڸ� �����Ѵ�. (Hard Mode)
	// AI ���̵� ����
	while (true) {
		system("cls");
		std::cout << "AI ��带 �������ּ���." << std::endl << "1. Easy" << std::endl << "2. Hard" << std::endl;
		std::cin >> aiMode;

		if (aiMode >= AI_EASY && aiMode <= AI_HARD)		break;
	}

	// EasyMode
	// ���� AI�� ���� ��� �� *�� ������� ���� ���� ����� �����.
	// �� ��� �� �ϳ��� �����ϰ� �����Ѵ�.
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

		// AI ���� ���� *�� ��µǵ��� ��.
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
			std::cout << std::endl << "Player 5�� ���� �ϼ� ! �÷��̾� �¸� ! " << std::endl;
			break;
		}

		else if (aiBingoCount >= 5) {
			std::cout << std::endl << "AI 5�� ���� �ϼ� ! �÷��̾� �й� ! " << std::endl;
			break;
		}

		bingoCount = 0;
		aiBingoCount = 0;

		std::cout << std::endl << "1~25 ������ ���ڸ� �Է��ϼ���(0 : ����) : ";
		std::cin >> inputNum;

		if (inputNum == 0)		break;

		if (inputNum < 0 || inputNum>25)	continue;

		isDuplicate = true;

		// �÷��̾� �� �Է� ��, �ߺ� üũ �� �ش� ���� ����
		for (int i = 0; i < 25; ++i) {
			if (inputNum == bingoMap[i]) {
				bingoMap[i] = INT_MAX;
				isDuplicate = false;
			}
		}

		if (isDuplicate)		continue;

		// �÷��̾� �� �Է� ��, AI ���� ����
		for (int i = 0; i < 25; ++i) {
			if (inputNum == aiBingoMap[i]) {
				aiBingoMap[i] = INT_MAX;
				// �÷��̾ �Է��� ���ڸ� ã�Ƽ� *�� �ٲ����Ƿ�
				// ���þȵ� ���� ������ 1 �پ���.
			}
		}

		// AI�� ����. AI MODE�� ���� �����ϴ� ����� �޶�����
		switch (aiMode)
		{
			// �������� ���� ���� �� ������ ���� �����ϴ� ���
		case AI_EASY:
			// ���� �� �� ���ڸ���� ������ش�.
			// ���� �� �� ���� ������ ����� ���� �� �Բ� ���ȴ�.
			noneSelectedCount = 0;
			for (int i = 0; i < 25; ++i) {
				if (aiBingoMap[i] != INT_MAX) {
					noneSelected[noneSelectedCount++] = aiBingoMap[i];
				}
			}
			inputNum = noneSelected[rand() % noneSelectedCount];
			break;
			
			// ���� ���ɼ��� ���� ���ڸ� �����ϴ� ���
			// ������ HARD ���� ���õ� ���� �߿��� ���� �տ� �ִ� ���ڸ� �����Ѵ�.
			// ���� Vector Ȥ�� �����Ҵ��� �̿��ؼ� ������ ���� �� ���ŵ��� ���� ���ڵ��� �迭�� �޾Ƽ�
			// �� ���ڵ� �� �ٽ� ���Ǽ��� �ϴ� ������� ������ �����ص� ������ ���� �� ����.
		case AI_HARD:
			// 1. ���� ���ɼ��� ���� ���� ���� �����Ѵ�(����, ����, �밢�� ��)
			// 2. �� �ٿ� �ִ� ���� �� �ϳ��� *�� ������ش�.
			int line = 0;
			int starCount = 0;
			int saveCount = 0; // ������ Ȯ���� ���� �� ����. �ִ��� �����ϰ� ����.

			// ���� ���� �� ���� ���� ���� ���� ã��
			for (int i = 0; i < 5; ++i) {
				starCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (aiBingoMap[i * 5 + j] == INT_MAX) ++starCount;
				}
				
				// ���� 5�� �̸��̾�� ���� �ƴ� �����̰� ������ ���� ���� ���� ���κ���
				// ���� ������ ���� �� ���ƾ� ���� ������ ���� ���� ���� �������� ������.
				if (starCount < 5 && starCount > saveCount) {
					// ���� ������ 0~4�� �ǹ� �ο���.(���� LINE_NUMBER ������)
					line = i;
					saveCount = starCount;
				}
			}

			// ���� ���� �� ���� ���� ���� ������ �̹� ������.
			// �� ���ΰ� ���� ���ε��� ���Ͽ� ���� ���� ���� ������ ���Ѵ�.
			for (int i = 0; i < 5; ++i) {
				starCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (aiBingoMap[j * 5 + i] == INT_MAX) ++starCount;
				}

				if (starCount < 5 && starCount > saveCount) {
					// ���� ������ 5~9�� �ǹ� �ο���.(���� LINE_NUMBER ������)
					line = i + 5;
					saveCount = starCount;
				}
			}

			// �»�� �밢���� �տ��� ���� ������ ���Ͽ� ���� ���� ���� ���� ����
			starCount = 0;
			for (int i = 0; i < 25; i += 6) {
				if (aiBingoMap[i] == INT_MAX)		++starCount;
			}

			if (starCount < 5 && starCount > saveCount) {
				// �»�� �밢�� ������ 10 ���� �ǹ� �ο���.(���� LINE_NUMBER ������)
				line = LN_LT;
				saveCount = starCount;
			}

			// ���� �밢���� �տ��� ���� ���ε��� ���Ͽ� ���� ���� ���� ���� ����
			starCount = 0;
			for (int i = 4; i <= 20; i += 4) {
				if (aiBingoMap[i] == INT_MAX)		++aiRowStar;
			}

			if (starCount < 5 && starCount > saveCount) {
				// ���� �밢�� ������ 11 �� �ǹ� �ο���.(���� LINE_NUMBER ������)
				line = LN_RT;
				saveCount = starCount;
			}

			// ��� ������ ���������Ƿ� line���� ���� ���ɼ��� ���� ���� �� ��ȣ�� ����Ǿ���.
			// �ش� �ٿ� �ִ� *�� �ƴ� ���� �� 1���� �����ϸ� �ȴ�.
			
			// ���� ���� ���
			if (line <= LN_H5) {
				for (int i = 0; i < 5; ++i) {
					if (aiBingoMap[line * 5 + i] != INT_MAX) {
						inputNum = aiBingoMap[line * 5 + i];
						break;
					}
				}
			}

			// ���� ���� ���
			else if (line <= LN_V5) {
				for (int i = 0; i < 5; ++i) {
					if (aiBingoMap[i * 5 + (line - 5)] != INT_MAX) {
						inputNum = aiBingoMap[i * 5 + (line - 5)];
						break;
					}
				}
			}

			// �»�� �밢��
			else if (line == LN_LT) {
				for (int i = 0; i < 25; i += 6) {
					if (aiBingoMap[i] != INT_MAX) {
						inputNum = aiBingoMap[i];
						break;
					}
				}
			}

			// ���� �밢��
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

		// AI �� �Է� ��,  �ش� ���� ����
		for (int i = 0; i < 25; ++i) {
			if (inputNum == bingoMap[i]) {
				bingoMap[i] = INT_MAX;
			}
		}

		// AI �� �Է� ��, AI ���� ����
		for (int i = 0; i < 25; ++i) {
			if (inputNum == aiBingoMap[i]) {
				aiBingoMap[i] = INT_MAX;
				// �÷��̾ �Է��� ���ڸ� ã�Ƽ� *�� �ٲ����Ƿ�
				// ���þȵ� ���� ������ 1 �پ���.
				--noneSelectedCount;
			}
		}

		//���� ���� ���� Ȯ��
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

		//���� ��� �밢�� ���� Ȯ��
		rowStar = 0;
		aiRowStar = 0;
		for (int i = 0; i < 25; i += 6) {
			if (bingoMap[i] == INT_MAX)		++rowStar;
			if (aiBingoMap[i] == INT_MAX)		++aiRowStar;
		}
		if (rowStar == 5)	++bingoCount;
		if (aiRowStar == 5)	++aiBingoCount;

		//���� ��� �밢�� ���� Ȯ��
		rowStar = 0;
		aiRowStar = 0;
		for (int i = 4; i <= 20; i += 4) {
			if (bingoMap[i] == INT_MAX)		++rowStar;
			if (aiBingoMap[i] == INT_MAX)		++aiRowStar;
		}
		if (rowStar == 5)	++bingoCount;
		if (aiRowStar == 5)	++aiBingoCount;

	}

	std::cout << std::endl << "������ �����մϴ�" << std::endl;

	return 0;
}