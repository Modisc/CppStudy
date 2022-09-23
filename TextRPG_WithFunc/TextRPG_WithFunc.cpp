#include <iostream>
#include <time.h>

using std::cout;
using std::endl;
using std::cin;

#define NAME_SIZE 32 // 이름
#define ITEM_DESC_SIZE 512 // 아이템 설명
#define INVENTORY_MAX 20 // 가방 최대 크기
#define STORE_WEAPON_MAX 3 // 상점에서 판매하는 무기 개수
#define STORE_ARMOR_MAX 3 // 상점에서 판매하는 방어구 개수
#define LEVEL_MAX 10 // 최대 레벨

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
	int price; // 구매 가격
	int sell; // 상점에 되팔때 판매 가격
	char description[ITEM_DESC_SIZE]; // 아이템 설명
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
	Item currEquipItem[EQ_MAX]; // 현재 장착중인 아이템
	bool equipCheck[EQ_MAX]; // 아이템을 장착 중인지 체크
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

// 레벨업에 필요한 경험치 목록
const int levelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
// 레벨업에 따른 경험치 증가 테이블
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
	
	// 몬스터 생성
	Monster monsterArr[MT_BACK - 1] = {}; // 맵 종류만큼 몬스터 생성
	SetMonster(monsterArr);

	levelUpTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10, 8, 16, 50, 100, 10, 20);
	levelUpTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15, 5, 10, 30, 60, 30, 50);
	levelUpTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20, 3, 7, 20, 40, 50, 100);

	// 상점에서 판매할 아이템 목록 생성
	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	storeWeapon[0] = CreateItem("나무 무기", IT_WEAPON, 5, 10, 3000, 500, "초보자가 사용하는 나무 무기");
	storeWeapon[1] = CreateItem("철 무기", IT_WEAPON, 40, 70, 7000, 3500, "중급자가 사용하는 철 무기");
	storeWeapon[2] = CreateItem("미스릴 무기", IT_WEAPON, 90, 150, 100000, 50000, "고급자가 사용하는 미스릴 무기");

	storeArmor[0] = CreateItem("천 갑옷", IT_ARMOR, 2, 5, 1000, 500, "초보자가 사용하는 천 갑옷");
	storeArmor[1] = CreateItem("가죽 갑옷", IT_ARMOR, 20, 30, 7000, 3500, "중급자가 사용하는 가죽 갑옷");
	storeArmor[2] = CreateItem("풀 플레이트 아머", IT_ARMOR, 70, 90, 30000, 15000, "고급자가 사용하는 풀 플레이트 아머");

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
			cout << "잘못 선택하였습니다." << endl;
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
		return INT_MAX; // 잘못된 값이 입력됐다는 의미
	}

	return input;
}

int PrintMainMenu() {
	
	system("cls");
	cout << " ******************************** 로비 ******************************** " << endl;
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 가방" << endl;
	cout << "4. 종료" << endl;

	cout << "메뉴를 선택하세요 : ";
	int inputMenu = InputInt();
	if (inputMenu == INT_MAX || inputMenu <= MM_NONE || inputMenu > MM_EXIT)
		return MM_NONE;

	return inputMenu;
}

int PrintMapMenu() {
	system("cls");
	cout << " ******************************** 맵 ******************************** " << endl;
	cout << "1. 쉬움" << endl;
	cout << "2. 보통" << endl;
	cout << "3. 어려움" << endl;
	cout << "4. 뒤로가기" << endl;

	cout << "메뉴를 선택하세요 : ";
	int inputMenu = InputInt();
	if (inputMenu == INT_MAX || inputMenu <= MT_NONE || inputMenu > MT_BACK)
		return MT_NONE;

	return inputMenu;
}

void PrintBattleTag(int menu) {
	switch (menu) {
	case MT_EASY:
		cout << " ******************************** 쉬움 ******************************** " << endl;
		break;
	case MT_NORMAL:
		cout << " ******************************** 보통 ******************************** " << endl;
		break;
	case MT_HARD:
		cout << " ******************************** 어려움 ******************************** " << endl;
		break;
	}
}

void PrintPlayer(Player* player) {
	// 플레이어 정보 출력
	cout << "=========================== Player ===========================" << endl;
	cout << "이름 : " << player->name << "\t직업 : " << player->jobName << endl;
	cout << "레벨 : " << player->level << "\t경험치 : " << player->exp << endl;

	// 무기 장착 시 무기 공격력 함께 출력
	if (player->equipCheck[EQ_WEAPON] == true) {
		cout << "공격력 : " << player->attackMin << "(+" << player->currEquipItem[EQ_WEAPON].min << ") - "
			<< player->attackMax << "(+" << player->currEquipItem[EQ_WEAPON].max << ")" << endl;
	}

	else {
		cout << "공격력 : " << player->attackMin << " - " << player->attackMax << endl;
	}

	// 방어구 장착 시 방어구 방어력 함께 출력
	if (player->equipCheck[EQ_ARMOR] == true) {
		cout << "방어력 : " << player->armorMin << "(+" << player->currEquipItem[EQ_ARMOR].min << ") - "
			<< player->armorMax << "(+" << player->currEquipItem[EQ_ARMOR].max << ")" << endl;
	}

	else {
		cout << "방어력 : " << player->armorMin << " - " << player->armorMax << endl;
	}

	// 착용중인 무기 출력
	if (player->equipCheck[EQ_WEAPON] == true) {
		cout << "장착 무기 : " << player->currEquipItem[EQ_WEAPON].name << endl;
	}

	else {
		cout << "장착 무기 : 없음" << endl;
	}

	// 착용중인 방어구 출력
	if (player->equipCheck[EQ_ARMOR] == true) {
		cout << "장착 방어구 : " << player->currEquipItem[EQ_ARMOR].name << endl;
	}

	else {
		cout << "장착 방어구 : 없음" << endl;
	}

	cout << "체력 : " << player->hp << " / " << player->hpMax << "\t마나 : " << player->mp << " / " << player->mpMax << endl;
	cout << "보유골드 : " << player->inventory.gold << "Gold" << endl << endl;
}

void PrintMonster(Monster* monster) {
	cout << "=========================== Monster ===========================" << endl;
	cout << "이름 : " << monster->name << "\t레벨 : " << monster->level << endl;
	cout << "공격력 : " << monster->attackMin << " - " << monster->attackMax << endl;
	cout << "방어력 : " << monster->armorMin << " - " << monster->armorMax << endl;
	cout << "체력 : " << monster->hp << " / " << monster->hpMax << "\t마나 : " << monster->mp << " / " << monster->mpMax << endl;
	cout << "획득 가능한 경험치 : " << monster->exp << "\t획득 가능한 골드 : " << monster->goldMin << " - " << monster->goldMax << endl << endl;
}

int PrintBattleMenu() {
	cout << "1. 공격" << endl;
	cout << "2. 도망" << endl;
	cout << "메뉴를 선택하세요 : ";
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

	// 무기 공격력 추가 적용
	if (player->equipCheck[EQ_WEAPON]) {
		attackMin += player->currEquipItem[EQ_WEAPON].min;
		attackMax += player->currEquipItem[EQ_WEAPON].max;
	}

	int attack = (rand() % (attackMax - attackMin + 1)) + attackMin;
	int armor = (rand() % (monster->armorMax - monster->armorMin + 1)) + monster->armorMin;

	int damage = attack - armor;
	damage = damage < 1 ? 1 : damage;

	monster->hp -= damage;

	cout << player->name << "가 " << monster->name << "에게 " << damage << "만큼 피해를 입혔습니다." << endl;

	// 몬스터 사망
	if (monster->hp <= 0) {
		cout << "몬스터 " << monster->name << "이(가) 사망하였습니다." << endl;
		player->exp += monster->exp;
		int gold = (rand() % (monster->goldMax - monster->goldMin + 1)) + monster->goldMin;

		player->inventory.gold += gold;

		cout << monster->exp << " 경험치를 획득하였습니다." << endl;
		cout << gold << " Gold를 획득하였습니다." << endl;

		monster->hp = monster->hpMax;
		monster->mp = monster->mpMax;

		// 플레이어 레벨업 유무 체크
		if (player->exp >= levelUpExp[player->level - 1]) {
			player->exp -= levelUpExp[player->level - 1];
			++player->level;

			cout << "레벨업 하였습니다." << endl;

			// 능력치 상승
			int jobIndex = player->job - 1;
			int hpUp = rand() % (levelUpTable[jobIndex].hpMax - levelUpTable[jobIndex].hpMin + 1) + levelUpTable[jobIndex].hpMin;
			int mpUp = rand() % (levelUpTable[jobIndex].mpMax - levelUpTable[jobIndex].mpMin + 1) + levelUpTable[jobIndex].mpMin;

			player->attackMax += levelUpTable[jobIndex].attackMax;
			player->attackMin += levelUpTable[jobIndex].attackMin;
			player->armorMax += levelUpTable[jobIndex].armorMax;
			player->armorMin += levelUpTable[jobIndex].armorMin;

			player->hpMax += hpUp;
			player->mpMax += mpUp;

			// 레벨업 하였으므로 체력, 마나 회복
			player->hp = player->hpMax;
			player->mp = player->mpMax;

		}
		return;
	}

	// 몬스터 생존시 플레이어 공격
	else {
		attack = (rand() % (monster->attackMax - monster->attackMin + 1)) + monster->attackMin;
		armor = (rand() % (player->armorMax - player->armorMin + 1)) + player->armorMin;

		damage = attack - armor;
		damage = damage < 1 ? 1 : damage;

		player->hp -= damage;

		cout << monster->name << "가 " << player->name << "에게 " << damage << "만큼 피해를 입혔습니다." << endl;

		if (player->hp <= 0) {
			cout << "플레이어 " << player->name << "이(가) 사망하였습니다." << endl;
			int exp = player->exp * 0.1f;
			int gold = player->inventory.gold * 0.1f;

			player->exp -= exp;
			player->inventory.gold -= gold;

			cout << exp << " 경험치를 잃었습니다." << endl;
			cout << gold << " 골드를 잃었습니다." << endl;

			// 플레이어의 HP와 MP 회복
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

		// 플레이어 출력
		PrintPlayer(player);

		// 몬스터 출력
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

		// 전투 시작
		RunBattle(player, monsterArr, menu);

	}
}

int SelectPlayerJob() {
	int playerJob = JOB_NONE;
	while (playerJob == JOB_NONE) {
		system("cls");
		cout << " ******************************** 직업 선택 ******************************** " << endl;
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		playerJob = InputInt();

		// 추후 직업이 추가됐을 경우에도 JOB_EXIT 앞에 값을 입력한다면
		// 항상 JOB_EXIT 는 마지막 값이 되므로 확장성이 좋다.
		if (playerJob <= JOB_NONE || playerJob >= JOB_EXIT) {
			playerJob = JOB_NONE;
		}
	}
	return playerJob;
}

void SetPlayer(Player* player) {
	// 플레이어 생성

	cout << "Player 이름 : ";
	cin.getline(player->name, NAME_SIZE - 1); // 문자열 마지막에 NULL이 들어가야 하므로 마지막 한 칸은 비워줘야 함.

	player->level = 1;
	player->exp = 0;
	player->job = (JOB)SelectPlayerJob();
	player->inventory.gold = 10000;

	switch (player->job) {
	case JOB_KNIGHT:
		strcpy_s(player->jobName, "기사");
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
		strcpy_s(player->jobName, "궁수");
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
		strcpy_s(player->jobName, "마법사");
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
	monsterArr[0] = CreateMonster("고블린", 20, 30, 2, 5,
		100, 10, 1, 1000, 500, 1500);
	monsterArr[1] = CreateMonster("트롤", 80, 130, 60, 90,
		2000, 100, 5, 7000, 6000, 8000);
	monsterArr[2] = CreateMonster("드래곤", 250, 500, 200, 400,
		30000, 20000, 10, 30000, 20000, 50000);
}

int PrintStoreMenu() {
	system("cls");
	cout << " ******************************** 상점 ******************************** " << endl;
	cout << "1. 무기 상점" << endl;
	cout << "2. 방어구 상점" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "상점을 선택하세요 : ";
	int menu = InputInt();
	if (menu <= SM_NONE || menu > SM_BACK) {
		return SM_NONE;
	}

	return menu;
}

int PrintStoreItemList(Inventory *inventory, Item* store, int itemCount) {
	for (int i = 0; i < itemCount; ++i) {
		cout << i + 1 << ". 이름 : " << store[i].name << "\t종류 : " << store[i].typeName << endl;
		cout << "공격력 : " << store[i].min << " - " << store[i].max << endl;
		cout << "판매 가격 : " << store[i].price << "\t구매 가격 : " << store[i].sell << endl;
		cout << "설명 : " << store[i].description << endl << endl;
	}

	cout << itemCount + 1 << ". 뒤로 가기" << endl << endl;
	cout << "보유 금액 : " << inventory->gold << endl;
	cout << "여유 공간 : " << INVENTORY_MAX - inventory->itemCount << endl;
	cout << "메뉴를 선택하세요 : ";
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
			cout << " ******************************** 무기 상점 ******************************** " << endl;
			break;
		case SM_ARMOR:
			cout << " ******************************** 방어구 상점 ******************************** " << endl;
			break;
		}
		int input = PrintStoreItemList(inventory, store, itemCount);

		if (input == INT_MAX) {
			cout << "잘못 입력하였습니다." << endl;
			system("pause");
			continue;
		}

		else if (input == itemCount + 1)		break;

		int itemIndex = input - 1;

		if (inventory->itemCount >= INVENTORY_MAX) {
			cout << "여유 공간이 부족합니다." << endl;
			system("pause");
			continue;
		}

		else if (inventory->gold < store[itemIndex].price) {
			cout << "보유 금액이 부족합니다." << endl;
			system("pause");
			continue;
		}

		inventory->gold -= store[itemIndex].price;
		inventory->item[inventory->itemCount] = store[itemIndex];
		++inventory->itemCount;

		cout << "아이템을 구매하였습니다." << endl;
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
		strcpy_s(item.typeName, "무기");
		break;
	case IT_ARMOR:
		strcpy_s(item.typeName, "방어구");
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
	cout << " ******************************** 가방 ******************************** " << endl;

	PrintPlayer(player);

	for (int i = 0; i < player->inventory.itemCount; ++i) {
		cout << i + 1 << ". 이름 : " << player->inventory.item[i].name << "\t종류 : " << player->inventory.item[i].typeName << endl;
		cout << "성능 : " << player->inventory.item[i].min << " - " << player->inventory.item[i].max << endl;
		cout << "판매 가격 : " << player->inventory.item[i].price << "\t구매 가격 : " << player->inventory.item[i].sell << endl;
		cout << "설명 : " << player->inventory.item[i].description << endl << endl;
	}

	cout << player->inventory.itemCount + 1 << ". 뒤로 가기" << endl;
	cout << "장착할 장비를 선택하세요 : ";
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

		cout << "장비를 장착하였습니다." << endl;

		system("pause");
	}
}