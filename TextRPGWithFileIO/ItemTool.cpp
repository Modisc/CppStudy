#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#define NAME_SIZE 32
#define ITEM_DESC_SIZE 512 // ������ ����
#define STORE_WEAPON_MAX 3 // �������� �Ǹ��ϴ� ���� ����
#define STORE_ARMOR_MAX 3 // �������� �Ǹ��ϴ� �� ����


enum MAIN_MENU {
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
};

enum ITEM_TYPE {
	IT_WEAPON = 1,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

struct Item {
	char name[NAME_SIZE];
	char typeName[NAME_SIZE];
	ITEM_TYPE type;
	int min;
	int max;
	int price; // ���� ����
	int sell; // ������ ���ȶ� �Ǹ� ����
	char description[ITEM_DESC_SIZE]; // ������ ����
};

int InputInt();

void AddItem(Item* weaponStore, Item* armorStore);

bool SaveStore(Item* weaponStore, Item* armorStore);

bool LoadStore(Item* weaponStore, Item* armorStore);

void Output(Item* weaponStore, Item* armorStore);

int main()
{
	Item weaponArr[STORE_WEAPON_MAX] = {};
	Item armorArr[STORE_ARMOR_MAX] = {};

	while (true)
	{
		system("cls");
		cout << "1. ������ �߰�" << endl;
		cout << "2. �о����" << endl;
		cout << "3. �����ϱ�" << endl;
		cout << "4. ������ ���" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
		int menu = InputInt();

		if (menu == MM_EXIT)
			break;
		switch (menu)
		{
		case MM_ADD:
			AddItem(weaponArr, armorArr);
			break;
		case MM_LOAD:
			LoadStore(weaponArr, armorArr);
			break;
		case MM_SAVE:
			SaveStore(weaponArr, armorArr);
			break;
		case MM_OUTPUT:
			Output(weaponArr, armorArr);
			break;
		}
	}

	// ���α׷� ���� �� �ڵ� ����
	SaveStore(weaponArr, armorArr);

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

void AddItem(Item* weaponStore, Item* armorStore)
{
	int menu = 0;

	while (true)
	{
		system("cls");
		cout << "1. �������" << endl;
		cout << "2. ������" << endl;
		cout << "3. ���" << endl;
		cout << "�߰��� ������ �����ϼ��� : ";
		menu = InputInt();

		if (menu == 3)
			return;

		else if (menu < 1 || menu > 3)
			continue;

		// �������� 1������ �����̹Ƿ� 1�� ����� �ε����� 0������
		// ���������� ������ �ȴ�.
		break;
	}

	int levelMenu = 0;
	while (true)
	{
		system("cls");
		cout << "1. �ʱ�" << endl;
		cout << "2. �߱�" << endl;
		cout << "3. ���" << endl;
		cout << "4. ���" << endl;
		cout << "�߰��� ������ ������ �����ϼ��� : ";
		levelMenu = InputInt();

		if (levelMenu == 4)
			return;

		else if (levelMenu < 1 || levelMenu > 4)
			continue;

		// �������� 1������ �����̹Ƿ� 1�� ����� �ε����� 0������
		// ���������� ������ �ȴ�.
		--levelMenu;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	Item* item = NULL;

	// ���ڷ� ����������� ����� ������ �迭��
	// �� �������� ����� ������ �迭�� ���� �߰���.
	// ������ �߰��� ���� ������ ���� �����ϰ� ������ ���ؿ� ����
	// �������� �迭�� �߰��Ͽ� �ش�.
	if (menu == SM_WEAPON)
	{
		item = &weaponStore[levelMenu];
		item->type = IT_WEAPON;
		strcpy_s(item->typeName, "����");
	}

	else
	{
		item = &armorStore[levelMenu];
		item->type = IT_ARMOR;
		strcpy_s(item->typeName, "��");
	}
		

	// ������ �̸�
	cout << "������ �̸� : ";
	cin.getline(item->name, NAME_SIZE - 1); // ���ڿ� �������� NULL�� ���� �ϹǷ� ������ �� ĭ�� ������ ��.

	cout << "������ ���� : ";
	cin.getline(item->description, ITEM_DESC_SIZE - 1);

	cout << "�ּ� �ɷ�ġ : ";
	item->min = InputInt();

	cout << "�ִ� �ɷ�ġ : ";
	item->max = InputInt();

	cout << "�ǸŰ� : ";
	item->price = InputInt();

	cout << "��ǰ�� : ";
	item->sell = InputInt();

	cout << endl << "������ �߰� �Ϸ�" << endl;
	system("pause");
}

bool SaveStore(Item* weaponStore, Item* armorStore)
{
	FILE* file = NULL;

	fopen_s(&file, "Store.sto", "wb");

	if (file)
	{
		fwrite(weaponStore, sizeof(Item), STORE_WEAPON_MAX, file);
		fwrite(armorStore, sizeof(Item), STORE_ARMOR_MAX, file);
		fclose(file);
		return true;
	}

	return false;
}

bool LoadStore(Item* weaponStore, Item* armorStore)
{
	FILE* file = NULL;

	fopen_s(&file, "Store.sto", "rb");

	if (file)
	{
		fread(weaponStore, sizeof(Item), STORE_WEAPON_MAX, file);
		fread(armorStore, sizeof(Item), STORE_ARMOR_MAX, file);
		fclose(file);
		return true;
	}

	return false;
}

void Output(Item* weaponStore, Item* armorStore)
{
	system("cls");
	cout << "=========================== Store ===========================" << endl;
	for (int i = 0; i < STORE_WEAPON_MAX; ++i)
	{
		cout << i + 1 << ". �̸� : " << weaponStore[i].name << "\t���� : " << weaponStore[i].typeName << endl;
		cout << "���ݷ� : " << weaponStore[i].min << " - " << weaponStore[i].max << endl;
		cout << "�Ǹ� ���� : " << weaponStore[i].price << "\t���� ���� : " << weaponStore[i].sell << endl;
		cout << "���� : " << weaponStore[i].description << endl << endl;
	}

	for (int i = 0; i < STORE_ARMOR_MAX; ++i)
	{
		cout << i + 1 << ". �̸� : " << armorStore[i].name << "\t���� : " << armorStore[i].typeName << endl;
		cout << "���� : " << armorStore[i].min << " - " << armorStore[i].max << endl;
		cout << "�Ǹ� ���� : " << armorStore[i].price << "\t���� ���� : " << armorStore[i].sell << endl;
		cout << "���� : " << armorStore[i].description << endl << endl;
	}

	system("pause");
}
