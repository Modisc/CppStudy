#include <iostream>
#include <time.h>

int main() {
	enum RSP {
		RSP_R,
		RSP_S,
		RSP_P,
		RSP_END
	};

	srand((unsigned int)time(NULL));
	
	int player, npc;

	while (true) {
		std::cout << "0. Rock" << std::endl;
		std::cout << "1. Scissors" << std::endl;
		std::cout << "2. Paper" << std::endl;
		std::cout << "3. Exit" << std::endl;

		std::cout << "0 ~ 3���� ��ȣ�� �������ּ��� : ";
		std::cin >> player;
		std::cout << std::endl;

		if (player < RSP_R || player > RSP_END) {
			std::cout << "Error" << std::endl;
			system("pause");
			continue;
		}

		else if (player == RSP_END) {
			std::cout << "������ �����մϴ�." << std::endl;
			break;
		}

		switch (player) {
		case RSP_R:
			std::cout << "player : Rock" << std::endl;
			break;
		case RSP_S:
			std::cout << "player : Scissors" << std::endl;
			break;
		case RSP_P:
			std::cout << "player : Paper" << std::endl;
			break;
		}

		npc = rand() % 3;

		switch (npc) {
		case RSP_R:
			std::cout << "AI : Rock" << std::endl;
			break;
		case RSP_S:
			std::cout << "AI : Scissors" << std::endl;
			break;
		case RSP_P:
			std::cout << "AI : Paper" << std::endl;
			break;
		}

		int condition = player - npc;

		switch (condition)
		{
		case 0:
			std::cout << "�����ϴ�!" << std::endl;
			break;
		case 1:
		case -2:
			std::cout << "�����ϴ�!" << std::endl;
			break;
		default:
			std::cout << "�̰���ϴ�!" << std::endl;
			break;
		}

		/*if (player - npc == 0) {
			std::cout << "�����ϴ�!" << std::endl;
		}
		else if (player - npc == 1 || player - npc == -2) {
			std::cout << "�����ϴ�!" << std::endl;
		}
		else {
			std::cout << "�̰���ϴ�!" << std::endl;
		}*/

		std::cout << std::endl;
	}
}