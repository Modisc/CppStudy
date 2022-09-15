#include <iostream>

#define NAME_SIZE 32
#define STUDENT_MAX 10
#define PHONENUMBER_MAX 128

struct Student {
	char name[NAME_SIZE];
	char phone[PHONENUMBER_MAX];
	int number;
	int korScore;
	int engScore;
	int mathScore;
	int totalScore;
	float avg;

};

enum MENU {
	MENU_INSERT = 1,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

int main() {
	
	Student studentArr[STUDENT_MAX] = {};
	char studentName[NAME_SIZE] = {};
	int studentCount = 0;
	int studentNum = 1;
	int menu;


	while (true) {
		system("cls");

		if (studentCount >= STUDENT_MAX) break;

		// �޴��� ����Ѵ�.
		std::cout << "1. �л� ���" << std::endl;
		std::cout << "2. �л� ����" << std::endl;
		std::cout << "3. �л� �˻�" << std::endl;
		std::cout << "4. �л� ���" << std::endl;
		std::cout << "5. ����" << std::endl;
		std::cout << "�޴��� �����ϼ��� : ";
		std::cin >> menu;

		/* 
		cin�� �Է¹��� ������ Ÿ�Կ� ���缭 ���� �Է��ؾ� �Ѵ�.
		������ Ÿ�Կ� ���� �ʰ� ���� �Է��� ��� ������ �߻��Ѵ�.
		���� ����ó���� ������ �߻��ߴ����� üũ�Ͽ� ������ �߻��ϸ�
		cin ������ �������۸� ����ְ� cin ������ �Է¹��۸� ��ȸ�Ͽ� ���� ������ \n�� �����ش�.
		(cin�� ������ �Է¹��ۿ� �Է��� ���� �����صΰ�, �� ���� ������ �־��ִ� ������ �Ѵ�.)
		*/ 

		if (std::cin.fail()) {
			std::cin.clear(); // �Է¹��� ����ֱ�

			// �Է¹��ۿ� �����ִ� \n �˻� �� ����
			// ù��° ���ڴ� �˻��ϰ��� �ϴ� ���� ũ��. ���⼭�� 1024�� ū ���� �˳��ϰ� �����ص�.
			// �ι�° ���ڴ� ã���� �ϴ� ����.
			// �Է¹��� ó������ \n�� �ִ� ������ ã�Ƽ� �� �κ��� ��� �����Ͽ� �ٽ� �Է¹��� �� �ֵ��� ���ش�.
			std::cin.ignore(1024, '\n');
			
			continue;
		}

		if (menu == MENU_EXIT)	break;

		switch (menu) {
		case MENU_INSERT:
			system("cls");
			std::cout << "================= �л� �߰� =================" << std::endl << std::endl;
			// �л� ���� �߰�. �̸�, ��ȭ��ȣ, ����, ����, ���� ���� ������ �Է¹���
			// �й�, ����, ����� ����� ���� �����ش�.
			std::cout << "�̸� : ";
			std::cin >> studentArr[studentCount].name;
			std::cin.ignore(1024, '\n');
			std::cout << "��ȭ��ȣ : ";
			std::cin.getline(studentArr[studentCount].phone, PHONENUMBER_MAX);
			std::cout << "���� ���� : ";
			std::cin >> studentArr[studentCount].korScore;
			std::cout << "���� ���� : ";
			std::cin >> studentArr[studentCount].engScore;
			std::cout << "���� ���� : ";
			std::cin >> studentArr[studentCount].mathScore;

			studentArr[studentCount].totalScore = studentArr[studentCount].korScore + studentArr[studentCount].engScore + studentArr[studentCount].mathScore;
			studentArr[studentCount].avg = studentArr[studentCount].totalScore / 3.0f;
			studentArr[studentCount].number = studentNum;
			++studentCount;
			++studentNum;
			break;

		case MENU_DELETE:
			system("cls");
			std::cout << "================= �л� ���� =================" << std::endl << std::endl;
			std::cout << "������ �̸��� �Է��ϼ��� : ";
			std::cin.ignore(1024, '\n');
			std::cin.getline(studentName, NAME_SIZE);

			for (int i = 0; i < studentCount; ++i) {
				if (strcmp(studentName, studentArr[i].name) == 0) {
					for (int j = i; j < studentCount - 1; ++j) {
						studentArr[j] = studentArr[j + 1];
					}
					--studentCount;
					std::cout << std::endl << "�л��� �����Ͽ����ϴ�." << std::endl << std::endl;
					break;
				}
			}
			break;

		case MENU_SEARCH:
			system("cls");
			std::cout << "================= �л� �˻� =================" << std::endl << std::endl;
			std::cout << "�˻��� �̸��� �Է��ϼ��� : ";
			std::cin.ignore(1024, '\n');
			std::cin.getline(studentName, NAME_SIZE);
			
			for (int i = 0; i < studentCount; ++i) {
				if (strcmp(studentName, studentArr[i].name) == 0) {
					std::cout << "�̸� : " << studentArr[i].name << std::endl;
					std::cout << "�й� : " << studentArr[i].number << std::endl;
					std::cout << "��ȭ��ȣ : " << studentArr[i].phone << std::endl;
					std::cout << "���� ���� : " << studentArr[i].korScore << std::endl;
					std::cout << "���� ���� : " << studentArr[i].engScore << std::endl;
					std::cout << "���� ���� : " << studentArr[i].mathScore << std::endl;
					std::cout << "���� �� �� : " << studentArr[i].totalScore << std::endl;
					std::cout << "��� : " << studentArr[i].avg << std::endl << std::endl;
					break;
				}
			}
			break;

		case MENU_OUTPUT:
			system("cls");
			std::cout << "================= �л� ��� =================" << std::endl << std::endl;
			if (studentCount == 0) {
				std::cout << std::endl << "��ϵ� �л��� �����ϴ�." << std::endl << std::endl;
				break;
			}
			for (int i = 0; i < studentCount; ++i) {
				std::cout << "�̸� : " << studentArr[i].name << std::endl;
				std::cout << "�й� : " << studentArr[i].number << std::endl;
				std::cout << "��ȭ��ȣ : " << studentArr[i].phone << std::endl;
				std::cout << "���� ���� : " << studentArr[i].korScore << std::endl;
				std::cout << "���� ���� : " << studentArr[i].engScore << std::endl;
				std::cout << "���� ���� : " << studentArr[i].mathScore << std::endl;
				std::cout << "���� �� �� : " << studentArr[i].totalScore << std::endl;
				std::cout << "��� : " << studentArr[i].avg << std::endl<<std::endl;
			}

			break;

		default:
			std::cout << std::endl << "�߸��� �޴��� �����Ͽ����ϴ�." << std::endl << std::endl;
			break;
		}

		// pause ��Ű�� ������ system("cls") ������ ��µǴ� ������ ���� ������ �ʰ� �ٷ� �����.
		// ���� pause ���Ѽ� ���α׷��� ��� ���߰� �Ѵ�.
		system("pause");
	}

	std::cout << std::endl << "���α׷��� ����Ǿ����ϴ�. " << std::endl;
	
	return 0;
}