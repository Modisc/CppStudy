#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#define NAME_SIZE 32

enum MAP_TYPE
{
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_END
};

enum MAIN_MENU {
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
};

struct Monster {
	char name[NAME_SIZE];
	int attackMax;
	int attackMin;
	int armorMax;
	int armorMin;
	int hp;
	int hpMax;
	int mp;
	int mpMax;
	int level;
	int exp; // 몬스터 사냥 시 얻는 경험치
	 // 몬스터 사냥 시 얻는 골드
	int goldMax;
	int goldMin;
};

int InputInt();

void AddMonster(Monster* monster);

bool SaveMonster(Monster* monster);

bool LoadMonster(Monster* monster);

void PrintMonster(Monster* monster);

void Output(Monster* monster);

int main()
{
	Monster monster[MT_END] = {};

	while (true)
	{
		system("cls");
		cout << "1. 몬스터 추가" << endl;
		cout << "2. 읽어오기" << endl;
		cout << "3. 저장하기" << endl;
		cout << "4. 몬스터 출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		int menu = InputInt();

		if (menu == MM_EXIT)
			break;
		switch (menu)
		{
		case MM_ADD:
			AddMonster(monster);
			break;
		case MM_LOAD:
			LoadMonster(monster);
			break;
		case MM_SAVE:
			SaveMonster(monster);
			break;
		case MM_OUTPUT:
			Output(monster);
			break;
		}
	}

	// 프로그램 종료 시 자동 저장
	SaveMonster(monster);

	return 0;
}

int InputInt() {
	int input;
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX; // 잘못된 값이 입력됐다는 의미
	}

	return input;
}

void AddMonster(Monster* monster)
{
	int menu = 0;

	while (true)
	{
		system("cls");
		cout << "1. 쉬움" << endl;
		cout << "2. 보통" << endl;
		cout << "3. 어려움" << endl;
		cout << "4. 취소" << endl;
		cout << "추가할 몬스터의 난이도를 선택하세요 : ";
		menu = InputInt();

		if (menu == 4)
			return;

		else if (menu < 1 || menu > 4)
			continue;

		// 선택지가 1번부터 시작이므로 1을 빼줘야 인덱스에 0번부터
		// 정상적으로 저장이 된다.
		--menu;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	// 몬스터 이름
	cout << "Monster 이름 : ";
	cin.getline(monster[menu].name, NAME_SIZE - 1); // 문자열 마지막에 NULL이 들어가야 하므로 마지막 한 칸은 비워줘야 함.

	cout << "최소 공격력 : ";
	monster[menu].attackMin = InputInt();

	cout << "최대 공격력 : ";
	monster[menu].attackMax = InputInt();

	cout << "최소 방어력 : ";
	monster[menu].armorMin = InputInt();

	cout << "최대 방어력 : ";
	monster[menu].armorMax = InputInt();

	cout << "체력 : ";
	monster[menu].hp = InputInt();
	monster[menu].hpMax = monster[menu].hp;

	cout << "마나 : ";
	monster[menu].mp = InputInt();
	monster[menu].mpMax = monster[menu].mp;

	cout << "레벨 : ";
	monster[menu].level = InputInt();

	cout << "획득 경험치 : ";
	monster[menu].exp = InputInt();

	cout << "획득 최소 골드 : ";
	monster[menu].goldMin = InputInt();

	cout << "획득 최대 골드 : ";
	monster[menu].goldMax = InputInt();

	cout << endl << "몬스터 추가 완료" << endl;
	system("pause");
}

bool SaveMonster(Monster* monster)
{
	FILE* file = NULL;

	fopen_s(&file, "Monster.mst", "wb");

	if (file)
	{
		fwrite(monster, sizeof(Monster), MT_END, file);
		fclose(file);
		return true;
	}

	return false;
}

bool LoadMonster(Monster* monster)
{
	FILE* file = NULL;

	fopen_s(&file, "Monster.mst", "rb");

	if (file)
	{
		fread(monster, sizeof(Monster), MT_END, file);
		fclose(file);
		return true;
	}

	return false;
}

void PrintMonster(Monster* monster) {
	cout << "=========================== Monster ===========================" << endl;
	cout << "이름 : " << monster->name << "\t레벨 : " << monster->level << endl;
	cout << "공격력 : " << monster->attackMin << " - " << monster->attackMax << endl;
	cout << "방어력 : " << monster->armorMin << " - " << monster->armorMax << endl;
	cout << "체력 : " << monster->hp << " / " << monster->hpMax << "\t마나 : " << monster->mp << " / " << monster->mpMax << endl;
	cout << "획득 가능한 경험치 : " << monster->exp << "\t획득 가능한 골드 : " << monster->goldMin << " - " << monster->goldMax << endl << endl;
}

void Output(Monster* monster)
{
	system("cls");

	for (int i = 0; i < MT_END; ++i)
	{
		PrintMonster(&monster[i]);
	}

	system("pause");
}
