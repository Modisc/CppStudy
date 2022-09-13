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

		// 이렇게 할 경우 idx1 의 값은 이미 idx2 위치 값이 들어가있으므로 lotto[tmp] 해봤자 idx2 값만 들어갈 뿐이다.
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

	std::cout << "보너스 번호 : " << lotto[6] << std::endl;
	

}