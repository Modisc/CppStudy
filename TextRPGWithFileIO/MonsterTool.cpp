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
	int exp; // ���� ��� �� ��� ����ġ
	 // ���� ��� �� ��� ���
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
		cout << "1. ���� �߰�" << endl;
		cout << "2. �о����" << endl;
		cout << "3. �����ϱ�" << endl;
		cout << "4. ���� ���" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
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

	// ���α׷� ���� �� �ڵ� ����
	SaveMonster(monster);

	return 0;
}

int InputInt() {
	int input;
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX; // �߸��� ���� �Էµƴٴ� �ǹ�
	}

	return input;
}

void AddMonster(Monster* monster)
{
	int menu = 0;

	while (true)
	{
		system("cls");
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3. �����" << endl;
		cout << "4. ���" << endl;
		cout << "�߰��� ������ ���̵��� �����ϼ��� : ";
		menu = InputInt();

		if (menu == 4)
			return;

		else if (menu < 1 || menu > 4)
			continue;

		// �������� 1������ �����̹Ƿ� 1�� ����� �ε����� 0������
		// ���������� ������ �ȴ�.
		--menu;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	// ���� �̸�
	cout << "Monster �̸� : ";
	cin.getline(monster[menu].name, NAME_SIZE - 1); // ���ڿ� �������� NULL�� ���� �ϹǷ� ������ �� ĭ�� ������ ��.

	cout << "�ּ� ���ݷ� : ";
	monster[menu].attackMin = InputInt();

	cout << "�ִ� ���ݷ� : ";
	monster[menu].attackMax = InputInt();

	cout << "�ּ� ���� : ";
	monster[menu].armorMin = InputInt();

	cout << "�ִ� ���� : ";
	monster[menu].armorMax = InputInt();

	cout << "ü�� : ";
	monster[menu].hp = InputInt();
	monster[menu].hpMax = monster[menu].hp;

	cout << "���� : ";
	monster[menu].mp = InputInt();
	monster[menu].mpMax = monster[menu].mp;

	cout << "���� : ";
	monster[menu].level = InputInt();

	cout << "ȹ�� ����ġ : ";
	monster[menu].exp = InputInt();

	cout << "ȹ�� �ּ� ��� : ";
	monster[menu].goldMin = InputInt();

	cout << "ȹ�� �ִ� ��� : ";
	monster[menu].goldMax = InputInt();

	cout << endl << "���� �߰� �Ϸ�" << endl;
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
	cout << "�̸� : " << monster->name << "\t���� : " << monster->level << endl;
	cout << "���ݷ� : " << monster->attackMin << " - " << monster->attackMax << endl;
	cout << "���� : " << monster->armorMin << " - " << monster->armorMax << endl;
	cout << "ü�� : " << monster->hp << " / " << monster->hpMax << "\t���� : " << monster->mp << " / " << monster->mpMax << endl;
	cout << "ȹ�� ������ ����ġ : " << monster->exp << "\tȹ�� ������ ��� : " << monster->goldMin << " - " << monster->goldMax << endl << endl;
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
