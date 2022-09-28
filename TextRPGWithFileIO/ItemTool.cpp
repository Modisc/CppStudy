#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#define NAME_SIZE 32
#define ITEM_DESC_SIZE 512 // 아이템 설명
#define STORE_WEAPON_MAX 3 // 상점에서 판매하는 무기 개수
#define STORE_ARMOR_MAX 3 // 상점에서 판매하는 방어구 개수


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
	int price; // 구매 가격
	int sell; // 상점에 되팔때 판매 가격
	char description[ITEM_DESC_SIZE]; // 아이템 설명
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
		cout << "1. 아이템 추가" << endl;
		cout << "2. 읽어오기" << endl;
		cout << "3. 저장하기" << endl;
		cout << "4. 아이템 출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
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

	// 프로그램 종료 시 자동 저장
	SaveStore(weaponArr, armorArr);

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

void AddItem(Item* weaponStore, Item* armorStore)
{
	int menu = 0;

	while (true)
	{
		system("cls");
		cout << "1. 무기상점" << endl;
		cout << "2. 방어구상점" << endl;
		cout << "3. 취소" << endl;
		cout << "추가할 상점을 선택하세요 : ";
		menu = InputInt();

		if (menu == 3)
			return;

		else if (menu < 1 || menu > 3)
			continue;

		// 선택지가 1번부터 시작이므로 1을 빼줘야 인덱스에 0번부터
		// 정상적으로 저장이 된다.
		break;
	}

	int levelMenu = 0;
	while (true)
	{
		system("cls");
		cout << "1. 초급" << endl;
		cout << "2. 중급" << endl;
		cout << "3. 고급" << endl;
		cout << "4. 취소" << endl;
		cout << "추가할 아이템 수준을 선택하세요 : ";
		levelMenu = InputInt();

		if (levelMenu == 4)
			return;

		else if (levelMenu < 1 || levelMenu > 4)
			continue;

		// 선택지가 1번부터 시작이므로 1을 빼줘야 인덱스에 0번부터
		// 정상적으로 저장이 된다.
		--levelMenu;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	Item* item = NULL;

	// 인자로 무기상점에서 사용할 아이템 배열과
	// 방어구 상점에서 사용할 아이템 배열을 따로 추가함.
	// 아이템 추가할 때도 상점을 먼저 선택하고 아이템 수준에 따라
	// 아이템을 배열에 추가하여 준다.
	if (menu == SM_WEAPON)
	{
		item = &weaponStore[levelMenu];
		item->type = IT_WEAPON;
		strcpy_s(item->typeName, "무기");
	}

	else
	{
		item = &armorStore[levelMenu];
		item->type = IT_ARMOR;
		strcpy_s(item->typeName, "방어구");
	}
		

	// 아이템 이름
	cout << "아이템 이름 : ";
	cin.getline(item->name, NAME_SIZE - 1); // 문자열 마지막에 NULL이 들어가야 하므로 마지막 한 칸은 비워줘야 함.

	cout << "아이템 설명 : ";
	cin.getline(item->description, ITEM_DESC_SIZE - 1);

	cout << "최소 능력치 : ";
	item->min = InputInt();

	cout << "최대 능력치 : ";
	item->max = InputInt();

	cout << "판매가 : ";
	item->price = InputInt();

	cout << "반품가 : ";
	item->sell = InputInt();

	cout << endl << "아이템 추가 완료" << endl;
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
		cout << i + 1 << ". 이름 : " << weaponStore[i].name << "\t종류 : " << weaponStore[i].typeName << endl;
		cout << "공격력 : " << weaponStore[i].min << " - " << weaponStore[i].max << endl;
		cout << "판매 가격 : " << weaponStore[i].price << "\t구매 가격 : " << weaponStore[i].sell << endl;
		cout << "설명 : " << weaponStore[i].description << endl << endl;
	}

	for (int i = 0; i < STORE_ARMOR_MAX; ++i)
	{
		cout << i + 1 << ". 이름 : " << armorStore[i].name << "\t종류 : " << armorStore[i].typeName << endl;
		cout << "방어력 : " << armorStore[i].min << " - " << armorStore[i].max << endl;
		cout << "판매 가격 : " << armorStore[i].price << "\t구매 가격 : " << armorStore[i].sell << endl;
		cout << "설명 : " << armorStore[i].description << endl << endl;
	}

	system("pause");
}
