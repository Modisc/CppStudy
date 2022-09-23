#include <iostream>
#include <time.h>

using std::cout;
using std::endl;
using std::cin;

#define NAME_SIZE 32 // �̸�
#define ITEM_DESC_SIZE 512 // ������ ����
#define INVENTORY_MAX 20 // ���� �ִ� ũ��
#define STORE_WEAPON_MAX 3 // �������� �Ǹ��ϴ� ���� ����
#define STORE_ARMOR_MAX 3 // �������� �Ǹ��ϴ� �� ����
#define LEVEL_MAX 10 // �ִ� ����

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_EXIT
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
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

enum EQUIP {
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
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

struct Inventory {
	Item item[INVENTORY_MAX];
	int itemCount;
	int gold;
};

struct Player {
	char name[NAME_SIZE];
	char jobName[NAME_SIZE];
	JOB job;
	int attackMax;
	int attackMin;
	int armorMax;
	int armorMin;
	int hp;
	int hpMax;
	int mp;
	int mpMax;
	int exp;
	int level;
	Inventory inventory;
	Item currEquipItem[EQ_MAX]; // ���� �������� ������
	bool equipCheck[EQ_MAX]; // �������� ���� ������ üũ
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

struct LevelUpStatus {
	int	attackMin;
	int	attackMax;
	int	armorMin;
	int	armorMax;
	int	hpMin;
	int	hpMax;
	int	mpMin;
	int	mpMax;
};

// �������� �ʿ��� ����ġ ���
const int levelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
// �������� ���� ����ġ ���� ���̺�
LevelUpStatus levelUpTable[JOB_EXIT - 1] = {};


int InputInt();

int PrintMainMenu();

int PrintMapMenu();

void PrintBattleTag(int menu);

void PrintPlayer(Player* player);

void PrintMonster(Monster* monster);

LevelUpStatus CreateLvUpStatus(int attackMin, int attackMax, int armorMin, int armorMax, int hpMin, int hpMax, int mpMin, int mpMax);

int PrintBattleMenu();

void RunBattle(Player* player, Monster* monsterArr, int menu);

void RunMap(Player* player, Monster* monsterArr);

int SelectPlayerJob();

void SetPlayer(Player* player);

Monster CreateMonster(const char* name, int attackMin,
	int attackMax, int armorMin, int armorMax, int hp,
	int mp, int level, int exp, int goldMin, int goldMax);

void SetMonster(Monster* monsterArr);

void Battle(Player* player, Monster* monster);

int PrintStoreMenu();

int PrintStoreItemList(Inventory* inventory, Item* store, int itemCount);

void BuyItem(Inventory* inventory, Item* store, int itemCount, int storeType);

void RunStore(Inventory* inventory, Item* weapon, Item* armor);

Item CreateItem(const char* name, ITEM_TYPE type, int min, int max, int price, int sell, const char* desc);

int PrintInventory(Player* player);

EQUIP ComputeEquipType(ITEM_TYPE type);

void RunInventory(Player* player);

int main() {
	srand((unsigned int)time(NULL));
	Player player = {};
	SetPlayer(&player);
	
	// ���� ����
	Monster monsterArr[MT_BACK - 1] = {}; // �� ������ŭ ���� ����
	SetMonster(monsterArr);

	levelUpTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10, 8, 16, 50, 100, 10, 20);
	levelUpTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15, 5, 10, 30, 60, 30, 50);
	levelUpTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20, 3, 7, 20, 40, 50, 100);

	// �������� �Ǹ��� ������ ��� ����
	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	storeWeapon[0] = CreateItem("���� ����", IT_WEAPON, 5, 10, 3000, 500, "�ʺ��ڰ� ����ϴ� ���� ����");
	storeWeapon[1] = CreateItem("ö ����", IT_WEAPON, 40, 70, 7000, 3500, "�߱��ڰ� ����ϴ� ö ����");
	storeWeapon[2] = CreateItem("�̽��� ����", IT_WEAPON, 90, 150, 100000, 50000, "����ڰ� ����ϴ� �̽��� ����");

	storeArmor[0] = CreateItem("õ ����", IT_ARMOR, 2, 5, 1000, 500, "�ʺ��ڰ� ����ϴ� õ ����");
	storeArmor[1] = CreateItem("���� ����", IT_ARMOR, 20, 30, 7000, 3500, "�߱��ڰ� ����ϴ� ���� ����");
	storeArmor[2] = CreateItem("Ǯ �÷���Ʈ �Ƹ�", IT_ARMOR, 70, 90, 30000, 15000, "����ڰ� ����ϴ� Ǯ �÷���Ʈ �Ƹ�");

	bool loop = true;
	while (loop) {
		switch (PrintMainMenu())
		{
		case MM_MAP:
			RunMap(&player, monsterArr);
			break;
		case MM_STORE:
			RunStore(&player.inventory, storeWeapon, storeArmor);
			break;
		case MM_INVENTORY:
			RunInventory(&player);
			break;
		case MM_EXIT:
			loop = false;
			break;
		default:
			cout << "�߸� �����Ͽ����ϴ�." << endl;
			break;
		}
	}
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

int PrintMainMenu() {
	
	system("cls");
	cout << " ******************************** �κ� ******************************** " << endl;
	cout << "1. ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "4. ����" << endl;

	cout << "�޴��� �����ϼ��� : ";
	int inputMenu = InputInt();
	if (inputMenu == INT_MAX || inputMenu <= MM_NONE || inputMenu > MM_EXIT)
		return MM_NONE;

	return inputMenu;
}

int PrintMapMenu() {
	system("cls");
	cout << " ******************************** �� ******************************** " << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �����" << endl;
	cout << "4. �ڷΰ���" << endl;

	cout << "�޴��� �����ϼ��� : ";
	int inputMenu = InputInt();
	if (inputMenu == INT_MAX || inputMenu <= MT_NONE || inputMenu > MT_BACK)
		return MT_NONE;

	return inputMenu;
}

void PrintBattleTag(int menu) {
	switch (menu) {
	case MT_EASY:
		cout << " ******************************** ���� ******************************** " << endl;
		break;
	case MT_NORMAL:
		cout << " ******************************** ���� ******************************** " << endl;
		break;
	case MT_HARD:
		cout << " ******************************** ����� ******************************** " << endl;
		break;
	}
}

void PrintPlayer(Player* player) {
	// �÷��̾� ���� ���
	cout << "=========================== Player ===========================" << endl;
	cout << "�̸� : " << player->name << "\t���� : " << player->jobName << endl;
	cout << "���� : " << player->level << "\t����ġ : " << player->exp << endl;

	// ���� ���� �� ���� ���ݷ� �Բ� ���
	if (player->equipCheck[EQ_WEAPON] == true) {
		cout << "���ݷ� : " << player->attackMin << "(+" << player->currEquipItem[EQ_WEAPON].min << ") - "
			<< player->attackMax << "(+" << player->currEquipItem[EQ_WEAPON].max << ")" << endl;
	}

	else {
		cout << "���ݷ� : " << player->attackMin << " - " << player->attackMax << endl;
	}

	// �� ���� �� �� ���� �Բ� ���
	if (player->equipCheck[EQ_ARMOR] == true) {
		cout << "���� : " << player->armorMin << "(+" << player->currEquipItem[EQ_ARMOR].min << ") - "
			<< player->armorMax << "(+" << player->currEquipItem[EQ_ARMOR].max << ")" << endl;
	}

	else {
		cout << "���� : " << player->armorMin << " - " << player->armorMax << endl;
	}

	// �������� ���� ���
	if (player->equipCheck[EQ_WEAPON] == true) {
		cout << "���� ���� : " << player->currEquipItem[EQ_WEAPON].name << endl;
	}

	else {
		cout << "���� ���� : ����" << endl;
	}

	// �������� �� ���
	if (player->equipCheck[EQ_ARMOR] == true) {
		cout << "���� �� : " << player->currEquipItem[EQ_ARMOR].name << endl;
	}

	else {
		cout << "���� �� : ����" << endl;
	}

	cout << "ü�� : " << player->hp << " / " << player->hpMax << "\t���� : " << player->mp << " / " << player->mpMax << endl;
	cout << "������� : " << player->inventory.gold << "Gold" << endl << endl;
}

void PrintMonster(Monster* monster) {
	cout << "=========================== Monster ===========================" << endl;
	cout << "�̸� : " << monster->name << "\t���� : " << monster->level << endl;
	cout << "���ݷ� : " << monster->attackMin << " - " << monster->attackMax << endl;
	cout << "���� : " << monster->armorMin << " - " << monster->armorMax << endl;
	cout << "ü�� : " << monster->hp << " / " << monster->hpMax << "\t���� : " << monster->mp << " / " << monster->mpMax << endl;
	cout << "ȹ�� ������ ����ġ : " << monster->exp << "\tȹ�� ������ ��� : " << monster->goldMin << " - " << monster->goldMax << endl << endl;
}

int PrintBattleMenu() {
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int menu = InputInt();

	if (menu == INT_MAX || menu <= BATTLE_NONE || menu > BATTLE_BACK)
		return BATTLE_NONE;

	return menu;
}

LevelUpStatus CreateLvUpStatus(int attackMin, int attackMax, int armorMin, int armorMax, int hpMin, int hpMax, int mpMin, int mpMax) {
	
	LevelUpStatus status = {};
	
	status.attackMin = attackMin;
	status.attackMax = attackMax;
	status.armorMin = armorMin;
	status.armorMax = armorMax;
	status.hpMin = hpMin;
	status.hpMax = hpMax;
	status.mpMin = mpMin;
	status.mpMax = mpMax;

	return status;
}

void Battle(Player* player, Monster* monster) {
	int attackMin = player->attackMin;
	int attackMax = player->attackMax;

	// ���� ���ݷ� �߰� ����
	if (player->equipCheck[EQ_WEAPON]) {
		attackMin += player->currEquipItem[EQ_WEAPON].min;
		attackMax += player->currEquipItem[EQ_WEAPON].max;
	}

	int attack = (rand() % (attackMax - attackMin + 1)) + attackMin;
	int armor = (rand() % (monster->armorMax - monster->armorMin + 1)) + monster->armorMin;

	int damage = attack - armor;
	damage = damage < 1 ? 1 : damage;

	monster->hp -= damage;

	cout << player->name << "�� " << monster->name << "���� " << damage << "��ŭ ���ظ� �������ϴ�." << endl;

	// ���� ���
	if (monster->hp <= 0) {
		cout << "���� " << monster->name << "��(��) ����Ͽ����ϴ�." << endl;
		player->exp += monster->exp;
		int gold = (rand() % (monster->goldMax - monster->goldMin + 1)) + monster->goldMin;

		player->inventory.gold += gold;

		cout << monster->exp << " ����ġ�� ȹ���Ͽ����ϴ�." << endl;
		cout << gold << " Gold�� ȹ���Ͽ����ϴ�." << endl;

		monster->hp = monster->hpMax;
		monster->mp = monster->mpMax;

		// �÷��̾� ������ ���� üũ
		if (player->exp >= levelUpExp[player->level - 1]) {
			player->exp -= levelUpExp[player->level - 1];
			++player->level;

			cout << "������ �Ͽ����ϴ�." << endl;

			// �ɷ�ġ ���
			int jobIndex = player->job - 1;
			int hpUp = rand() % (levelUpTable[jobIndex].hpMax - levelUpTable[jobIndex].hpMin + 1) + levelUpTable[jobIndex].hpMin;
			int mpUp = rand() % (levelUpTable[jobIndex].mpMax - levelUpTable[jobIndex].mpMin + 1) + levelUpTable[jobIndex].mpMin;

			player->attackMax += levelUpTable[jobIndex].attackMax;
			player->attackMin += levelUpTable[jobIndex].attackMin;
			player->armorMax += levelUpTable[jobIndex].armorMax;
			player->armorMin += levelUpTable[jobIndex].armorMin;

			player->hpMax += hpUp;
			player->mpMax += mpUp;

			// ������ �Ͽ����Ƿ� ü��, ���� ȸ��
			player->hp = player->hpMax;
			player->mp = player->mpMax;

		}
		return;
	}

	// ���� ������ �÷��̾� ����
	else {
		attack = (rand() % (monster->attackMax - monster->attackMin + 1)) + monster->attackMin;
		armor = (rand() % (player->armorMax - player->armorMin + 1)) + player->armorMin;

		damage = attack - armor;
		damage = damage < 1 ? 1 : damage;

		player->hp -= damage;

		cout << monster->name << "�� " << player->name << "���� " << damage << "��ŭ ���ظ� �������ϴ�." << endl;

		if (player->hp <= 0) {
			cout << "�÷��̾� " << player->name << "��(��) ����Ͽ����ϴ�." << endl;
			int exp = player->exp * 0.1f;
			int gold = player->inventory.gold * 0.1f;

			player->exp -= exp;
			player->inventory.gold -= gold;

			cout << exp << " ����ġ�� �Ҿ����ϴ�." << endl;
			cout << gold << " ��带 �Ҿ����ϴ�." << endl;

			// �÷��̾��� HP�� MP ȸ��
			player->hp = player->hpMax;
			player->mp = player->mpMax;

		}
		return;
	}
}

void RunBattle(Player* player, Monster* monsterArr, int menu) {
	Monster monster = monsterArr[menu - 1];

	while (true) {
		system("cls");
		PrintBattleTag(menu);

		// �÷��̾� ���
		PrintPlayer(player);

		// ���� ���
		PrintMonster(&monster);

		switch (PrintBattleMenu()) {
		case BATTLE_ATTACK:
			Battle(player, &monster);
			system("pause");
			break;
		case BATTLE_BACK:
			return;
		}
	}
}

void RunMap(Player* player, Monster* monsterArr) {
	bool loop = true;
	while (loop) {
		int menu = PrintMapMenu();

		if (menu == MT_BACK)		return;

		// ���� ����
		RunBattle(player, monsterArr, menu);

	}
}

int SelectPlayerJob() {
	int playerJob = JOB_NONE;
	while (playerJob == JOB_NONE) {
		system("cls");
		cout << " ******************************** ���� ���� ******************************** " << endl;
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
		playerJob = InputInt();

		// ���� ������ �߰����� ��쿡�� JOB_EXIT �տ� ���� �Է��Ѵٸ�
		// �׻� JOB_EXIT �� ������ ���� �ǹǷ� Ȯ�强�� ����.
		if (playerJob <= JOB_NONE || playerJob >= JOB_EXIT) {
			playerJob = JOB_NONE;
		}
	}
	return playerJob;
}

void SetPlayer(Player* player) {
	// �÷��̾� ����

	cout << "Player �̸� : ";
	cin.getline(player->name, NAME_SIZE - 1); // ���ڿ� �������� NULL�� ���� �ϹǷ� ������ �� ĭ�� ������ ��.

	player->level = 1;
	player->exp = 0;
	player->job = (JOB)SelectPlayerJob();
	player->inventory.gold = 10000;

	switch (player->job) {
	case JOB_KNIGHT:
		strcpy_s(player->jobName, "���");
		player->attackMax = 10;
		player->attackMin = 5;
		player->armorMax = 20;
		player->armorMin = 15;
		player->hpMax = 500;
		player->hp = 500;
		player->mpMax = 100;
		player->mp = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(player->jobName, "�ü�");
		player->attackMax = 20;
		player->attackMin = 15;
		player->armorMax = 15;
		player->armorMin = 10;
		player->hpMax = 350;
		player->hp = 350;
		player->mpMax = 200;
		player->mp = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(player->jobName, "������");
		player->attackMax = 30;
		player->attackMin = 25;
		player->armorMax = 10;
		player->armorMin = 5;
		player->hpMax = 150;
		player->hp = 150;
		player->mpMax = 400;
		player->mp = 400;
		break;

	}
}

Monster CreateMonster(const char* name, int attackMin,
	int attackMax, int armorMin, int armorMax, int hp,
	int mp, int level, int exp, int goldMin, int goldMax)
{
	Monster monster = {};
	strcpy_s(monster.name, name);
	monster.attackMax = attackMax;
	monster.attackMin = attackMin;
	monster.armorMax = armorMax;
	monster.armorMin = armorMin;
	monster.hpMax = hp;
	monster.hp = hp;
	monster.mpMax = mp;
	monster.mp = mp;
	monster.level = level;
	monster.exp = exp;
	monster.goldMax = goldMax;
	monster.goldMin = goldMin;

	return monster;
}

void SetMonster(Monster* monsterArr) {
	monsterArr[0] = CreateMonster("���", 20, 30, 2, 5,
		100, 10, 1, 1000, 500, 1500);
	monsterArr[1] = CreateMonster("Ʈ��", 80, 130, 60, 90,
		2000, 100, 5, 7000, 6000, 8000);
	monsterArr[2] = CreateMonster("�巡��", 250, 500, 200, 400,
		30000, 20000, 10, 30000, 20000, 50000);
}

int PrintStoreMenu() {
	system("cls");
	cout << " ******************************** ���� ******************************** " << endl;
	cout << "1. ���� ����" << endl;
	cout << "2. �� ����" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "������ �����ϼ��� : ";
	int menu = InputInt();
	if (menu <= SM_NONE || menu > SM_BACK) {
		return SM_NONE;
	}

	return menu;
}

int PrintStoreItemList(Inventory *inventory, Item* store, int itemCount) {
	for (int i = 0; i < itemCount; ++i) {
		cout << i + 1 << ". �̸� : " << store[i].name << "\t���� : " << store[i].typeName << endl;
		cout << "���ݷ� : " << store[i].min << " - " << store[i].max << endl;
		cout << "�Ǹ� ���� : " << store[i].price << "\t���� ���� : " << store[i].sell << endl;
		cout << "���� : " << store[i].description << endl << endl;
	}

	cout << itemCount + 1 << ". �ڷ� ����" << endl << endl;
	cout << "���� �ݾ� : " << inventory->gold << endl;
	cout << "���� ���� : " << INVENTORY_MAX - inventory->itemCount << endl;
	cout << "�޴��� �����ϼ��� : ";
	int menu = InputInt();

	if (menu < 1 || menu > itemCount + 1) {
		return INT_MAX;
	}

	return menu;
}

void BuyItem(Inventory* inventory, Item* store, int itemCount, int storeType) {
	while (true) {
		system("cls");
		switch (storeType) {
		case SM_WEAPON:
			cout << " ******************************** ���� ���� ******************************** " << endl;
			break;
		case SM_ARMOR:
			cout << " ******************************** �� ���� ******************************** " << endl;
			break;
		}
		int input = PrintStoreItemList(inventory, store, itemCount);

		if (input == INT_MAX) {
			cout << "�߸� �Է��Ͽ����ϴ�." << endl;
			system("pause");
			continue;
		}

		else if (input == itemCount + 1)		break;

		int itemIndex = input - 1;

		if (inventory->itemCount >= INVENTORY_MAX) {
			cout << "���� ������ �����մϴ�." << endl;
			system("pause");
			continue;
		}

		else if (inventory->gold < store[itemIndex].price) {
			cout << "���� �ݾ��� �����մϴ�." << endl;
			system("pause");
			continue;
		}

		inventory->gold -= store[itemIndex].price;
		inventory->item[inventory->itemCount] = store[itemIndex];
		++inventory->itemCount;

		cout << "�������� �����Ͽ����ϴ�." << endl;
		system("pause");
	}
}

void RunStore(Inventory* inventory, Item* weapon, Item* armor) {
	while (true) {
		switch (PrintStoreMenu()) {
		case SM_WEAPON:
			BuyItem(inventory, weapon, STORE_WEAPON_MAX, SM_WEAPON);
			break;
		case SM_ARMOR:
			BuyItem(inventory, armor, STORE_ARMOR_MAX, SM_ARMOR);
			break;
		case SM_BACK:
			return;

		}
	}
}

Item CreateItem(const char* name, ITEM_TYPE type, int min, int max, int price, int sell, const char* desc) {
	Item item = {};

	strcpy_s(item.name, name);
	strcpy_s(item.description, desc);
	item.type = type;
	switch (type) {
	case IT_WEAPON:
		strcpy_s(item.typeName, "����");
		break;
	case IT_ARMOR:
		strcpy_s(item.typeName, "��");
		break;
	}

	item.min = min;
	item.max = max;
	item.price = price;
	item.sell = sell;

	return item;
}

int PrintInventory(Player* player) {
	system("cls");
	cout << " ******************************** ���� ******************************** " << endl;

	PrintPlayer(player);

	for (int i = 0; i < player->inventory.itemCount; ++i) {
		cout << i + 1 << ". �̸� : " << player->inventory.item[i].name << "\t���� : " << player->inventory.item[i].typeName << endl;
		cout << "���� : " << player->inventory.item[i].min << " - " << player->inventory.item[i].max << endl;
		cout << "�Ǹ� ���� : " << player->inventory.item[i].price << "\t���� ���� : " << player->inventory.item[i].sell << endl;
		cout << "���� : " << player->inventory.item[i].description << endl << endl;
	}

	cout << player->inventory.itemCount + 1 << ". �ڷ� ����" << endl;
	cout << "������ ��� �����ϼ��� : ";
	int menu = InputInt();

	if (menu < 1 || menu > player->inventory.itemCount + 1)
		return INT_MAX;

	return menu;
}

EQUIP ComputeEquipType(ITEM_TYPE type) {
	EQUIP eq;
	 
	switch (type) {
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	}

	return eq;
}

void RunInventory(Player* player) {
	while (true) {
		int input = PrintInventory(player);
		if (input == INT_MAX)	continue;

		else if (input == player->inventory.itemCount + 1)	break;

		int itemIndex = input - 1;

		EQUIP eq = ComputeEquipType(player->inventory.item[itemIndex].type);

		if (player->equipCheck[eq] == true) {
			Item swap = player->currEquipItem[eq];
			player->currEquipItem[eq] = player->inventory.item[itemIndex];
			player->inventory.item[itemIndex] = swap;
		}

		else {
			player->currEquipItem[eq] = player->inventory.item[itemIndex];

			for (int i = itemIndex; i < player->inventory.itemCount - 1; ++i) {
				player->inventory.item[i] = player->inventory.item[i + 1];
			}
			--player->inventory.itemCount;

			player->equipCheck[eq] = true;
		}

		cout << "��� �����Ͽ����ϴ�." << endl;

		system("pause");
	}
}