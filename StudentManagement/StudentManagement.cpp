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

		// 메뉴를 출력한다.
		std::cout << "1. 학생 등록" << std::endl;
		std::cout << "2. 학생 삭제" << std::endl;
		std::cout << "3. 학생 검색" << std::endl;
		std::cout << "4. 학생 출력" << std::endl;
		std::cout << "5. 종료" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		std::cin >> menu;

		/* 
		cin은 입력받을 변수의 타입에 맞춰서 값을 입력해야 한다.
		변수의 타입에 맞지 않게 값을 입력할 경우 에러가 발생한다.
		따라서 예외처리로 에러가 발생했는지를 체크하여 에러가 발생하면
		cin 내부의 에러버퍼를 비워주고 cin 내부의 입력버퍼를 순회하여 버퍼 내부의 \n을 지워준다.
		(cin은 내부의 입력버퍼에 입력한 값을 저장해두고, 그 값을 변수에 넣어주는 역할을 한다.)
		*/ 

		if (std::cin.fail()) {
			std::cin.clear(); // 입력버퍼 비워주기

			// 입력버퍼에 남아있는 \n 검색 후 삭제
			// 첫번째 인자는 검색하고자 하는 버퍼 크기. 여기서는 1024로 큰 값을 넉넉하게 설정해둠.
			// 두번째 인자는 찾고자 하는 문자.
			// 입력버퍼 처음부터 \n이 있는 곳까지 찾아서 그 부분을 모두 삭제하여 다시 입력받을 수 있도록 해준다.
			std::cin.ignore(1024, '\n');
			
			continue;
		}

		if (menu == MENU_EXIT)	break;

		switch (menu) {
		case MENU_INSERT:
			system("cls");
			std::cout << "================= 학생 추가 =================" << std::endl << std::endl;
			// 학생 정보 추가. 이름, 전화번호, 국어, 영어, 수학 점수 까지는 입력받음
			// 학번, 총점, 평균은 계산을 통해 구해준다.
			std::cout << "이름 : ";
			std::cin >> studentArr[studentCount].name;
			std::cin.ignore(1024, '\n');
			std::cout << "전화번호 : ";
			std::cin.getline(studentArr[studentCount].phone, PHONENUMBER_MAX);
			std::cout << "국어 성적 : ";
			std::cin >> studentArr[studentCount].korScore;
			std::cout << "영어 성적 : ";
			std::cin >> studentArr[studentCount].engScore;
			std::cout << "수학 성적 : ";
			std::cin >> studentArr[studentCount].mathScore;

			studentArr[studentCount].totalScore = studentArr[studentCount].korScore + studentArr[studentCount].engScore + studentArr[studentCount].mathScore;
			studentArr[studentCount].avg = studentArr[studentCount].totalScore / 3.0f;
			studentArr[studentCount].number = studentNum;
			++studentCount;
			++studentNum;
			break;

		case MENU_DELETE:
			system("cls");
			std::cout << "================= 학생 삭제 =================" << std::endl << std::endl;
			std::cout << "삭제할 이름을 입력하세요 : ";
			std::cin.ignore(1024, '\n');
			std::cin.getline(studentName, NAME_SIZE);

			for (int i = 0; i < studentCount; ++i) {
				if (strcmp(studentName, studentArr[i].name) == 0) {
					for (int j = i; j < studentCount - 1; ++j) {
						studentArr[j] = studentArr[j + 1];
					}
					--studentCount;
					std::cout << std::endl << "학생을 삭제하였습니다." << std::endl << std::endl;
					break;
				}
			}
			break;

		case MENU_SEARCH:
			system("cls");
			std::cout << "================= 학생 검색 =================" << std::endl << std::endl;
			std::cout << "검색할 이름을 입력하세요 : ";
			std::cin.ignore(1024, '\n');
			std::cin.getline(studentName, NAME_SIZE);
			
			for (int i = 0; i < studentCount; ++i) {
				if (strcmp(studentName, studentArr[i].name) == 0) {
					std::cout << "이름 : " << studentArr[i].name << std::endl;
					std::cout << "학번 : " << studentArr[i].number << std::endl;
					std::cout << "전화번호 : " << studentArr[i].phone << std::endl;
					std::cout << "국어 성적 : " << studentArr[i].korScore << std::endl;
					std::cout << "영어 성적 : " << studentArr[i].engScore << std::endl;
					std::cout << "수학 성적 : " << studentArr[i].mathScore << std::endl;
					std::cout << "성적 총 합 : " << studentArr[i].totalScore << std::endl;
					std::cout << "평균 : " << studentArr[i].avg << std::endl << std::endl;
					break;
				}
			}
			break;

		case MENU_OUTPUT:
			system("cls");
			std::cout << "================= 학생 출력 =================" << std::endl << std::endl;
			if (studentCount == 0) {
				std::cout << std::endl << "등록된 학생이 없습니다." << std::endl << std::endl;
				break;
			}
			for (int i = 0; i < studentCount; ++i) {
				std::cout << "이름 : " << studentArr[i].name << std::endl;
				std::cout << "학번 : " << studentArr[i].number << std::endl;
				std::cout << "전화번호 : " << studentArr[i].phone << std::endl;
				std::cout << "국어 성적 : " << studentArr[i].korScore << std::endl;
				std::cout << "영어 성적 : " << studentArr[i].engScore << std::endl;
				std::cout << "수학 성적 : " << studentArr[i].mathScore << std::endl;
				std::cout << "성적 총 합 : " << studentArr[i].totalScore << std::endl;
				std::cout << "평균 : " << studentArr[i].avg << std::endl<<std::endl;
			}

			break;

		default:
			std::cout << std::endl << "잘못된 메뉴를 선택하였습니다." << std::endl << std::endl;
			break;
		}

		// pause 시키지 않으면 system("cls") 때문에 출력되는 내용이 전혀 보이지 않고 바로 사라짐.
		// 따라서 pause 시켜서 프로그램을 잠시 멈추게 한다.
		system("pause");
	}

	std::cout << std::endl << "프로그램이 종료되었습니다. " << std::endl;
	
	return 0;
}