#include <iostream>
#include <time.h>

int main() {
	int lotto[45];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 45; ++i) {
		lotto[i] = i + 1;
	}

	int idx1, idx2, tmp;

	for (int i = 0; i < 100; ++i) {
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		tmp = lotto[idx1];
		lotto[idx1] = lotto[idx2];
		lotto[idx2] = tmp;

		// �̷��� �� ��� idx1 �� ���� �̹� idx2 ��ġ ���� �������Ƿ� lotto[tmp] �غ��� idx2 ���� �� ���̴�.
		/*tmp = idx1;
		lotto[idx1] = lotto[idx2];
		lotto[idx2] = lotto[tmp];*/
	}

	for (int i = 0; i < 45; ++i) {
		std::cout << lotto[i] << "\t";
	}

	std::cout << std::endl << std::endl;

	for (int i = 0; i < 6; ++i) {
		std::cout << lotto[i] << "\t";
	}

	std::cout << "���ʽ� ��ȣ : " << lotto[6] << std::endl;
	

}