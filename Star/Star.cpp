#include <iostream>

int main() {
	int num;
	std::cin >> num;
	std::cout << std::endl;

	// ������� �����
	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= i; j++) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// ������� �����
	for (int i = 1; i <= num; i++) {
		for (int j = num; j >= i; j--) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// �ﰢ�� �����
	for (int i = 1; i <= num; i++) {
		for (int j = num; j > i; j--) {
			std::cout << " ";
		}

		for (int j = 1; j <= ((i * 2) - 1); j++) {
			std::cout << "*";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	// ���̾Ƹ�� �����
	for (int i = 1; i < num * 2; i++) {
		if (i <= num) {
			for (int j = num; j > i; j--) {
				std::cout << " ";
			}

			for (int j = 1; j <= ((i * 2) - 1); j++) {
				std::cout << "*";
			}

			std::cout << std::endl;
		}
		else {
			for (int j = num; j < i; j++) {
				std::cout << " ";
			}

			int count = (num * 2) - i;

			for (int j = 1; j <= (count*2)-1; j++) {
				std::cout << "*";
			}

			std::cout << std::endl;
		}
	}
}