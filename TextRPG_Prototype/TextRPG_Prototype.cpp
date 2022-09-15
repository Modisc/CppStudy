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
	MM_MAP = 1,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE {
	MT_EASY = 1,
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
	BATTLE_ATTACK = 1,
	BATTLE_BACK
};

enum ITEM_TYPE {
	IT_WEAPON = 1,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_WEAPON = 1,
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
	int	hPMin;
	int	hPMax;
	int	mPMin;
	int	mPMax;
};

int main() {
	srand((unsigned int)time(NULL));
	int menu;
	int attackMin;
	int attackMax;
	int attack;
	int armor;
	int damage;
	int exp;
	int gold;
	
	const int levelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };

	LevelUpStatus levelUpTable[JOB_EXIT - 1] = {};

	levelUpTable[JOB_KNIGHT - 1].attackMin = 4;
	levelUpTable[JOB_KNIGHT - 1].attackMax = 10;
	levelUpTable[JOB_KNIGHT - 1].armorMin = 8;
	levelUpTable[JOB_KNIGHT - 1].armorMax = 16;
	levelUpTable[JOB_KNIGHT - 1].hPMin = 50;
	levelUpTable[JOB_KNIGHT - 1].hPMax = 100;
	levelUpTable[JOB_KNIGHT - 1].mPMin = 10;
	levelUpTable[JOB_KNIGHT - 1].mPMax = 20;

	levelUpTable[JOB_ARCHER - 1].attackMin = 10;
	levelUpTable[JOB_ARCHER - 1].attackMax = 15;
	levelUpTable[JOB_ARCHER - 1].armorMin = 5;
	levelUpTable[JOB_ARCHER - 1].armorMax = 10;
	levelUpTable[JOB_ARCHER - 1].hPMin = 30;
	levelUpTable[JOB_ARCHER - 1].hPMax = 60;
	levelUpTable[JOB_ARCHER - 1].mPMin = 30;
	levelUpTable[JOB_ARCHER - 1].mPMax = 50;

	levelUpTable[JOB_WIZARD - 1].attackMin = 15;
	levelUpTable[JOB_WIZARD - 1].attackMax = 20;
	levelUpTable[JOB_WIZARD - 1].armorMin = 3;
	levelUpTable[JOB_WIZARD - 1].armorMax = 7;
	levelUpTable[JOB_WIZARD - 1].hPMin = 20;
	levelUpTable[JOB_WIZARD - 1].hPMax = 40;
	levelUpTable[JOB_WIZARD - 1].mPMin = 50;
	levelUpTable[JOB_WIZARD - 1].mPMax = 100;

	// 플레이어 생성
	Player player = {};
	int playerJob = JOB_NONE;
	cout << "Player 이름 : ";
	cin.getline(player.name, NAME_SIZE - 1); // 문자열 마지막에 NULL이 들어가야 하므로 마지막 한 칸은 비워줘야 함.
	
	while (playerJob == JOB_NONE) {
		system("cls");
		cout << " ******************************** 직업 선택 ******************************** " << endl;
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		cin >> playerJob;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		// 추후 직업이 추가됐을 경우에도 JOB_EXIT 앞에 값을 입력한다면
		// 항상 JOB_EXIT 는 마지막 값이 되므로 확장성이 좋다.
		if (playerJob <= JOB_NONE || playerJob >= JOB_EXIT) {
			playerJob = JOB_NONE;
			continue;
		}

		player.level = 1;
		player.exp = 0;
		player.job = (JOB)playerJob;
		player.inventory.gold = 10000;

		switch (playerJob) {
		case JOB_KNIGHT:
			strcpy_s(player.jobName, "기사");
			player.attackMax = 10;
			player.attackMin = 5;
			player.armorMax = 20;
			player.armorMin = 15;
			player.hpMax = 500;
			player.hp = 500;
			player.mpMax = 100;
			player.mp = 100;
			break;
		case JOB_ARCHER:
			strcpy_s(player.jobName, "궁수");
			player.attackMax = 20;
			player.attackMin = 15;
			player.armorMax = 15;
			player.armorMin = 10;
			player.hpMax = 350;
			player.hp = 350;
			player.mpMax = 200;
			player.mp = 200;
			break;
		case JOB_WIZARD:
			strcpy_s(player.jobName, "마법사");
			player.attackMax = 30;
			player.attackMin = 25;
			player.armorMax = 10;
			player.armorMin = 5;
			player.hpMax = 150;
			player.hp = 150;
			player.mpMax = 400;
			player.mp = 400;
			break;
			
		}
	}

	// 몬스터 생성
	Monster monsterArr[MT_BACK - 1] = {}; // 맵 종류만큼 몬스터 생성

	// 고블린 생성(Easy Mode)
	strcpy_s(monsterArr[MT_EASY - 1].name, "고블린");
	monsterArr[MT_EASY - 1].attackMax = 20;
	monsterArr[MT_EASY - 1].attackMin = 15;
	monsterArr[MT_EASY - 1].armorMax = 10;
	monsterArr[MT_EASY - 1].armorMin = 5;
	monsterArr[MT_EASY - 1].hpMax = 100;
	monsterArr[MT_EASY - 1].hp = 100;
	monsterArr[MT_EASY - 1].mpMax = 10;
	monsterArr[MT_EASY - 1].mp = 5;
	monsterArr[MT_EASY - 1].level = 1;
	monsterArr[MT_EASY - 1].exp = 1000;
	monsterArr[MT_EASY - 1].goldMax = 1500;
	monsterArr[MT_EASY - 1].goldMin = 500;

	// 트롤 생성(Easy Mode)
	strcpy_s(monsterArr[MT_NORMAL - 1].name, "트롤");
	monsterArr[MT_NORMAL - 1].attackMax = 80;
	monsterArr[MT_NORMAL - 1].attackMin = 130;
	monsterArr[MT_NORMAL - 1].armorMax = 60;
	monsterArr[MT_NORMAL - 1].armorMin = 90;
	monsterArr[MT_NORMAL - 1].hpMax = 2000;
	monsterArr[MT_NORMAL - 1].hp = 2000;
	monsterArr[MT_NORMAL - 1].mpMax = 100;
	monsterArr[MT_NORMAL - 1].mp = 100;
	monsterArr[MT_NORMAL - 1].level = 5;
	monsterArr[MT_NORMAL - 1].exp = 7000;
	monsterArr[MT_NORMAL - 1].goldMax = 8000;
	monsterArr[MT_NORMAL - 1].goldMin = 6000;

	// 오우거 생성(Easy Mode)
	strcpy_s(monsterArr[MT_HARD - 1].name, "오우거");
	monsterArr[MT_HARD - 1].attackMax = 250;
	monsterArr[MT_HARD - 1].attackMin = 200;
	monsterArr[MT_HARD - 1].armorMax = 400;
	monsterArr[MT_HARD - 1].armorMin = 200;
	monsterArr[MT_HARD - 1].hpMax = 30000;
	monsterArr[MT_HARD - 1].hp = 30000;
	monsterArr[MT_HARD - 1].mpMax = 500;
	monsterArr[MT_HARD - 1].mp = 500;
	monsterArr[MT_HARD - 1].level = 10;
	monsterArr[MT_HARD - 1].exp = 30000;
	monsterArr[MT_HARD - 1].goldMax = 50000;
	monsterArr[MT_HARD - 1].goldMin = 20000;

	// 상점에서 판매할 아이템 목록 생성
	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	// 각 아이템 정보들을 설정해준다.

	// 무기 - 나무
	strcpy_s(storeWeapon[0].name, "나무 무기");
	strcpy_s(storeWeapon[0].typeName, "무기");
	strcpy_s(storeWeapon[0].description, "초보자가 사용하는 나무 무기");
	storeWeapon[0].type = IT_WEAPON;
	storeWeapon[0].min = 5;
	storeWeapon[0].max = 10;
	storeWeapon[0].price = 3000;
	storeWeapon[0].sell = 500;

	// 무기 - 철
	strcpy_s(storeWeapon[1].name, "철 무기");
	strcpy_s(storeWeapon[1].typeName, "무기");
	strcpy_s(storeWeapon[1].description, "중급자가 사용하는 철 무기");
	storeWeapon[1].type = IT_WEAPON;
	storeWeapon[1].min = 40;
	storeWeapon[1].max = 70;
	storeWeapon[1].price = 7000;
	storeWeapon[1].sell = 3500;

	// 무기 - 미스릴
	strcpy_s(storeWeapon[2].name, "미스릴 무기");
	strcpy_s(storeWeapon[2].typeName, "무기");
	strcpy_s(storeWeapon[2].description, "고급자가 사용하는 미스릴 무기");
	storeWeapon[2].type = IT_WEAPON;
	storeWeapon[2].min = 90;
	storeWeapon[2].max = 150;
	storeWeapon[2].price = 100000;
	storeWeapon[2].sell = 50000;

	// 방어구 - 천갑옷
	strcpy_s(storeArmor[0].name, "천갑옷");
	strcpy_s(storeArmor[0].typeName, "방어구");
	strcpy_s(storeArmor[0].description, "초보자가 사용하는 천갑옷");
	storeArmor[0].type = IT_ARMOR;
	storeArmor[0].min = 2;
	storeArmor[0].max = 5;
	storeArmor[0].price = 1000;
	storeArmor[0].sell = 500;

	// 방어구 - 가죽갑옷
	strcpy_s(storeArmor[1].name, "가죽갑옷");
	strcpy_s(storeArmor[1].typeName, "방어구");
	strcpy_s(storeArmor[1].description, "중급자가 사용하는 가죽갑옷");
	storeArmor[1].type = IT_ARMOR;
	storeArmor[1].min = 20;
	storeArmor[1].max = 30;
	storeArmor[1].price = 7000;
	storeArmor[1].sell = 3500;

	// 방어구 - 풀플레이트아머
	strcpy_s(storeArmor[2].name, "풀 플레이트 아머");
	strcpy_s(storeArmor[2].typeName, "방어구");
	strcpy_s(storeArmor[2].description, "고급자가 사용하는 풀 플레이트 아머");
	storeArmor[2].type = IT_ARMOR;
	storeArmor[2].min = 70;
	storeArmor[2].max = 90;
	storeArmor[2].price = 30000;
	storeArmor[2].sell = 15000;

	while(true){
		system("cls");
		cout << " ******************************** 로비 ******************************** " << endl;
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;

		cout << "메뉴를 선택하세요 : ";
		cin >> menu;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (menu == MM_EXIT) break;

		switch (menu)
		{
		case MM_MAP:
			while (true) {
				system("cls");
				cout << " ******************************** 맵 ******************************** " << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기" << endl;

				cout << "맵을 선택하세요 : ";
				cin >> menu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (menu == MT_BACK) break;
				
				Monster monster = monsterArr[menu - 1];

				while (true) {
					system("cls");
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

					// 플레이어 정보 출력
					cout << "=========================== Player ===========================" << endl;
					cout << "이름 : " << player.name << "\t직업 : " << player.jobName << endl;
					cout << "레벨 : " << player.level << "\t경험치 : " << player.exp << endl;

					// 무기 장착 시 무기 공격력 함께 출력
					if (player.equipCheck[EQ_WEAPON] == true) {
						cout << "공격력 : " << player.attackMin << "(+" << player.currEquipItem[EQ_WEAPON].min << ") - "
							<< player.attackMax << "(+" << player.currEquipItem[EQ_WEAPON].max << ")" << endl;
					}

					else {
						cout << "공격력 : " << player.attackMin << " - " << player.attackMax << endl;
					}

					// 방어구 장착 시 방어구 방어력 함께 출력
					if (player.equipCheck[EQ_ARMOR] == true) {
						cout << "방어력 : " << player.armorMin << "(+" << player.currEquipItem[EQ_ARMOR].min << ") - "
							<< player.armorMax << "(+" << player.currEquipItem[EQ_ARMOR].max << ")" << endl;
					}

					else {
						cout << "방어력 : " << player.armorMin << " - " << player.armorMax << endl;
					}

					// 착용중인 무기 출력
					if (player.equipCheck[EQ_WEAPON] == true) {
						cout << "장착 무기 : " << player.currEquipItem[EQ_WEAPON].name << endl;
					}

					else {
						cout << "장착 무기 : 없음" << endl;
					}

					// 착용중인 방어구 출력
					if (player.equipCheck[EQ_ARMOR] == true) {
						cout << "장착 방어구 : " << player.currEquipItem[EQ_ARMOR].name << endl;
					}

					else {
						cout << "장착 방어구 : 없음" << endl;
					}

					cout << "체력 : " << player.hp << " / " << player.hpMax << "\t마나 : " << player.mp << " / " << player.mpMax << endl;
					cout << "보유골드 : " << player.inventory.gold << "Gold" << endl << endl;

					// 몬스터 정보 출력
					cout << "=========================== Monster ===========================" << endl;
					cout << "이름 : " << monster.name << "\t레벨 : " << monster.level << endl;
					cout << "공격력 : " << monster.attackMin << " - " << monster.attackMax << endl;
					cout << "방어력 : " << monster.armorMin << " - " << monster.armorMax << endl;
					cout << "체력 : " << monster.hp << " / " << monster.hpMax << "\t마나 : " << monster.mp << " / " << monster.mpMax << endl;
					cout << "획득 가능한 경험치 : " << monster.exp << "\t획득 가능한 골드 : " << monster.goldMin << " - " << monster.goldMax << endl << endl;

					cout << "1. 공격" << endl;
					cout << "2. 도망" << endl;
					cout << "메뉴를 선택하세요 : ";
					cin >> menu;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					else if (menu == BATTLE_BACK)		break;

					switch (menu)
					{
					case BATTLE_ATTACK:
						// attackMin ~ attackMax 경계값이 모두 포함돼야 한다.
						// +1을 하고나서 나머지 연산을 해야 0~5 까지의 값만 구해진다.
						// 나머지 연산을 하고 나서 1을 더해주면 1~5 까지의 값이 생성된다.

						attackMin = player.attackMin;
						attackMax = player.attackMax;

						// 무기 공격력 추가 적용
						if (player.equipCheck[EQ_WEAPON]) {
							attackMin += player.currEquipItem[EQ_WEAPON].min;
							attackMax += player.currEquipItem[EQ_WEAPON].max;
						}

						attack = (rand() % (attackMax - attackMin + 1)) + attackMin;
						armor = (rand() % (monster.armorMax - monster.armorMin + 1)) + monster.armorMin;

						damage = attack - armor;
						damage = damage < 1 ? 1 : damage;

						monster.hp -= damage;

						cout << player.name << "가 " << monster.name << "에게 " << damage << "만큼 피해를 입혔습니다." << endl;

						// 몬스터 사망
						if (monster.hp <= 0) {
							cout << "몬스터 " << monster.name << "이(가) 사망하였습니다." << endl;
							player.exp += monster.exp;
							gold = (rand() % (monster.goldMax - monster.goldMin + 1)) + monster.goldMin;
							
							player.inventory.gold += gold;

							cout << monster.exp << " 경험치를 획득하였습니다." << endl;
							cout << gold << " Gold를 획득하였습니다." << endl;

							monster.hp = monster.hpMax;
							monster.mp = monster.mpMax;

							// 플레이어 레벨업 유무 체크
							if (player.exp >= levelUpExp[player.level - 1]) {
								player.exp -= levelUpExp[player.level - 1];
								++player.level;

								cout << "레벨업 하였습니다." << endl;

								// 능력치 상승
								int jobIndex = player.job - 1;
								int hpUp = rand() % (levelUpTable[jobIndex].hPMax - levelUpTable[jobIndex].hPMin + 1) + levelUpTable[jobIndex].hPMin;
								int mpUp = rand() % (levelUpTable[jobIndex].mPMax - levelUpTable[jobIndex].mPMin + 1) + levelUpTable[jobIndex].mPMin;

								player.attackMax += levelUpTable[jobIndex].attackMax;
								player.attackMin += levelUpTable[jobIndex].attackMin;
								player.armorMax += levelUpTable[jobIndex].armorMax;
								player.armorMin += levelUpTable[jobIndex].armorMin;

								player.hpMax += hpUp;
								player.mpMax += mpUp;

								// 레벨업 하였으므로 체력, 마나 회복
								player.hp = player.hpMax;
								player.mp = player.mpMax;
								
							}

							system("pause");
							break;
						}

						// 몬스터 생존시 플레이어 공격
						else {
							attack = (rand() % (monster.attackMax - monster.attackMin + 1)) + monster.attackMin;
							armor = (rand() % (player.armorMax - player.armorMin + 1)) + player.armorMin;

							damage = attack - armor;
							damage = damage < 1 ? 1 : damage;

							player.hp -= damage;

							cout << monster.name << "가 " << player.name << "에게 " << damage << "만큼 피해를 입혔습니다." << endl;

							if (player.hp <= 0) {
								cout << "플레이어 " << player.name << "이(가) 사망하였습니다." << endl;
								exp = player.exp * 0.1f;
								gold = player.inventory.gold * 0.1f;

								player.exp -= exp;
								player.inventory.gold -= gold;

								cout << exp << " 경험치를 잃었습니다." << endl;
								cout << gold << " 골드를 잃었습니다." << endl;

								// 플레이어의 HP와 MP 회복
								player.hp = player.hpMax;
								player.mp = player.mpMax;
								
							}

							system("pause");
						}
						break;
					}
				}

			}
			break;
		case MM_STORE:
			while (true) {
				system("cls");
				cout << " ******************************** 상점 ******************************** " << endl;
				cout << "1. 무기 상점" << endl;
				cout << "2. 방어구 상점" << endl;
				cout << "3. 뒤로가기" << endl;
				cout << "상점을 선택하세요 : ";
				cin >> menu;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (menu == SM_BACK)	break;

				switch (menu) {
				case SM_WEAPON:
					while (true) {
						// 판매 목록을 보여준다
						system("cls");
						cout << " ******************************** 무기 상점 ******************************** " << endl;
						for (int i = 0; i < STORE_WEAPON_MAX; ++i) {
							cout << i + 1 << ". 이름 : " << storeWeapon[i].name << "\t종류 : " << storeWeapon[i].typeName << endl;
							cout << "공격력 : " << storeWeapon[i].min << " - " << storeWeapon[i].max << endl;
							cout << "판매 가격 : " << storeWeapon[i].price << "\t구매 가격 : " << storeWeapon[i].sell << endl;
							cout << "설명 : " << storeWeapon[i].description << endl << endl;
						}

						cout << STORE_WEAPON_MAX + 1 << ". 뒤로 가기" << endl << endl;
						cout << "보유 금액 : " << player.inventory.gold << endl;
						cout << "여유 공간 : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "메뉴를 선택하세요 : ";
						cin >> menu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (menu == STORE_WEAPON_MAX + 1)	break;

						else if (menu < 1 || menu > STORE_WEAPON_MAX + 1) {
							cout << "잘못 선택하였습니다. " << endl;
							system("pause");
							continue;
						}

						int weaponIndex = menu - 1;

						if (player.inventory.itemCount >= INVENTORY_MAX) {
							cout << "여유 공간이 부족합니다." << endl;
							system("pause");
							continue;
						}

						else if (player.inventory.gold < storeWeapon[weaponIndex].price) {
							cout << "보유 금액이 부족합니다." << endl;
							system("pause");
							continue;
						}

						player.inventory.gold -= storeWeapon[weaponIndex].price;
						player.inventory.item[player.inventory.itemCount] = storeWeapon[weaponIndex];
						++player.inventory.itemCount;

						cout << "아이템을 구매하였습니다." << endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true) {
						// 판매 목록을 보여준다
						system("cls");
						cout << " ******************************** 방어구 상점 ******************************** " << endl;
						for (int i = 0; i < STORE_ARMOR_MAX; ++i) {
							cout << i + 1 << ". 이름 : " << storeArmor[i].name << "\t종류 : " << storeArmor[i].typeName << endl;
							cout << "방어력 : " << storeArmor[i].min << " - " << storeArmor[i].max << endl;
							cout << "판매 가격 : " << storeArmor[i].price << "\t구매 가격 : " << storeArmor[i].sell << endl;
							cout << "설명 : " << storeArmor[i].description << endl << endl;
						}

						cout << STORE_ARMOR_MAX + 1 << ". 뒤로 가기" << endl << endl;
						cout << "보유 금액 : " << player.inventory.gold << endl;
						cout << "여유 공간 : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "메뉴를 선택하세요 : ";
						cin >> menu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (menu == STORE_ARMOR_MAX + 1)	break;

						else if (menu < 1 || menu > STORE_ARMOR_MAX + 1) {
							cout << "잘못 선택하였습니다. " << endl;
							system("pause");
							continue;
						}

						int weaponIndex = menu - 1;

						if (player.inventory.itemCount >= INVENTORY_MAX) {
							cout << "여유 공간이 부족합니다." << endl;
							system("pause");
							continue;
						}

						else if (player.inventory.gold < storeArmor[weaponIndex].price) {
							cout << "보유 금액이 부족합니다." << endl;
							system("pause");
							continue;
						}

						player.inventory.gold -= storeArmor[weaponIndex].price;
						player.inventory.item[player.inventory.itemCount] = storeArmor[weaponIndex];
						++player.inventory.itemCount;

						cout << "아이템을 구매하였습니다." << endl;
						system("pause");
					}
					break;
				}
			}
			break;
		case MM_INVENTORY:
			while (true) {
				system("cls");
				cout << " ******************************** 가방 ******************************** " << endl;
				cout << "=========================== Player ===========================" << endl;
				cout << "이름 : " << player.name << "\t직업 : " << player.jobName << endl;
				cout << "레벨 : " << player.level << "\t경험치 : " << player.exp << endl;

				// 무기 장착 시 무기 공격력 함께 출력
				if (player.equipCheck[EQ_WEAPON] == true) {
					cout << "공격력 : " << player.attackMin << "(+" << player.currEquipItem[EQ_WEAPON].min << ") - "
						<< player.attackMax << "(+" << player.currEquipItem[EQ_WEAPON].max << ")" << endl;
				}

				else {
					cout << "공격력 : " << player.attackMin << " - " << player.attackMax << endl;
				}

				// 방어구 장착 시 방어구 방어력 함께 출력
				if (player.equipCheck[EQ_ARMOR] == true) {
					cout << "방어력 : " << player.armorMin << "(+" << player.currEquipItem[EQ_ARMOR].min << ") - "
						<< player.armorMax << "(+" << player.currEquipItem[EQ_ARMOR].max << ")" << endl;
				}

				else {
					cout << "방어력 : " << player.armorMin << " - " << player.armorMax << endl;
				}

				// 착용중인 무기 출력
				if (player.equipCheck[EQ_WEAPON] == true) {
					cout << "장착 무기 : " << player.currEquipItem[EQ_WEAPON].name << endl;
				}

				else {
					cout << "장착 무기 : 없음" << endl;
				}

				// 착용중인 방어구 출력
				if (player.equipCheck[EQ_ARMOR] == true) {
					cout << "장착 방어구 : " << player.currEquipItem[EQ_ARMOR].name << endl;
				}

				else {
					cout << "장착 방어구 : 없음" << endl;
				}

				cout << "체력 : " << player.hp << " / " << player.hpMax << "\t마나 : " << player.mp << " / " << player.mpMax << endl;
				cout << "보유골드 : " << player.inventory.gold << "Gold" << endl << endl;

				for (int i = 0; i < player.inventory.itemCount; ++i) {
					cout << i + 1 << ". 이름 : " << player.inventory.item[i].name << "\t종류 : " << player.inventory.item[i].typeName << endl;
					cout << "성능 : " << player.inventory.item[i].min << " - " << player.inventory.item[i].max << endl;
					cout << "판매 가격 : " << player.inventory.item[i].price << "\t구매 가격 : " << player.inventory.item[i].sell << endl;
					cout << "설명 : " << player.inventory.item[i].description << endl << endl;
				}

				cout << player.inventory.itemCount + 1 << ". 뒤로 가기" << endl;
				cout << "장착할 장비를 선택하세요 : ";
				cin >> menu;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (menu == player.inventory.itemCount + 1)		break;

				else if (menu<1 || menu > player.inventory.itemCount + 1) {
					cout << "잘못 입력하였습니다." << endl;
					system("pause");
					continue;
				}

				int itemIndex = menu - 1;

				EQUIP eq;

				// 선택한 인벤토리 아이템의 무기 타입 체크
				switch (player.inventory.item[itemIndex].type) {
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				// 해당 타입의 무기를 이미 장착하고 있다면, 장비 변경
				if (player.equipCheck[eq] == true) {
					Item swap = player.currEquipItem[eq];
					player.currEquipItem[eq] = player.inventory.item[itemIndex];
					player.inventory.item[itemIndex] = swap;
				}

				else {
					player.currEquipItem[eq] = player.inventory.item[itemIndex];

					for (int i = itemIndex; i < player.inventory.itemCount - 1; ++i) {
						player.inventory.item[i] = player.inventory.item[i + 1];
					}
					--player.inventory.itemCount;

					// 아이템을 장착했으므로 true로 변경한다.
					player.equipCheck[eq] = true;
				}

				cout << "장비를 장착하였습니다." << endl;

				system("pause");
			}
			break;
		default:
			cout << "잘못 선택하였습니다." << endl;
			break;
		}

	}

	return 0;
}