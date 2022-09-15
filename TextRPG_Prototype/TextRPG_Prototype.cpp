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

	// �÷��̾� ����
	Player player = {};
	int playerJob = JOB_NONE;
	cout << "Player �̸� : ";
	cin.getline(player.name, NAME_SIZE - 1); // ���ڿ� �������� NULL�� ���� �ϹǷ� ������ �� ĭ�� ������ ��.
	
	while (playerJob == JOB_NONE) {
		system("cls");
		cout << " ******************************** ���� ���� ******************************** " << endl;
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
		cin >> playerJob;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		// ���� ������ �߰����� ��쿡�� JOB_EXIT �տ� ���� �Է��Ѵٸ�
		// �׻� JOB_EXIT �� ������ ���� �ǹǷ� Ȯ�强�� ����.
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
			strcpy_s(player.jobName, "���");
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
			strcpy_s(player.jobName, "�ü�");
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
			strcpy_s(player.jobName, "������");
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

	// ���� ����
	Monster monsterArr[MT_BACK - 1] = {}; // �� ������ŭ ���� ����

	// ��� ����(Easy Mode)
	strcpy_s(monsterArr[MT_EASY - 1].name, "���");
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

	// Ʈ�� ����(Easy Mode)
	strcpy_s(monsterArr[MT_NORMAL - 1].name, "Ʈ��");
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

	// ����� ����(Easy Mode)
	strcpy_s(monsterArr[MT_HARD - 1].name, "�����");
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

	// �������� �Ǹ��� ������ ��� ����
	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	// �� ������ �������� �������ش�.

	// ���� - ����
	strcpy_s(storeWeapon[0].name, "���� ����");
	strcpy_s(storeWeapon[0].typeName, "����");
	strcpy_s(storeWeapon[0].description, "�ʺ��ڰ� ����ϴ� ���� ����");
	storeWeapon[0].type = IT_WEAPON;
	storeWeapon[0].min = 5;
	storeWeapon[0].max = 10;
	storeWeapon[0].price = 3000;
	storeWeapon[0].sell = 500;

	// ���� - ö
	strcpy_s(storeWeapon[1].name, "ö ����");
	strcpy_s(storeWeapon[1].typeName, "����");
	strcpy_s(storeWeapon[1].description, "�߱��ڰ� ����ϴ� ö ����");
	storeWeapon[1].type = IT_WEAPON;
	storeWeapon[1].min = 40;
	storeWeapon[1].max = 70;
	storeWeapon[1].price = 7000;
	storeWeapon[1].sell = 3500;

	// ���� - �̽���
	strcpy_s(storeWeapon[2].name, "�̽��� ����");
	strcpy_s(storeWeapon[2].typeName, "����");
	strcpy_s(storeWeapon[2].description, "����ڰ� ����ϴ� �̽��� ����");
	storeWeapon[2].type = IT_WEAPON;
	storeWeapon[2].min = 90;
	storeWeapon[2].max = 150;
	storeWeapon[2].price = 100000;
	storeWeapon[2].sell = 50000;

	// �� - õ����
	strcpy_s(storeArmor[0].name, "õ����");
	strcpy_s(storeArmor[0].typeName, "��");
	strcpy_s(storeArmor[0].description, "�ʺ��ڰ� ����ϴ� õ����");
	storeArmor[0].type = IT_ARMOR;
	storeArmor[0].min = 2;
	storeArmor[0].max = 5;
	storeArmor[0].price = 1000;
	storeArmor[0].sell = 500;

	// �� - ���װ���
	strcpy_s(storeArmor[1].name, "���װ���");
	strcpy_s(storeArmor[1].typeName, "��");
	strcpy_s(storeArmor[1].description, "�߱��ڰ� ����ϴ� ���װ���");
	storeArmor[1].type = IT_ARMOR;
	storeArmor[1].min = 20;
	storeArmor[1].max = 30;
	storeArmor[1].price = 7000;
	storeArmor[1].sell = 3500;

	// �� - Ǯ�÷���Ʈ�Ƹ�
	strcpy_s(storeArmor[2].name, "Ǯ �÷���Ʈ �Ƹ�");
	strcpy_s(storeArmor[2].typeName, "��");
	strcpy_s(storeArmor[2].description, "����ڰ� ����ϴ� Ǯ �÷���Ʈ �Ƹ�");
	storeArmor[2].type = IT_ARMOR;
	storeArmor[2].min = 70;
	storeArmor[2].max = 90;
	storeArmor[2].price = 30000;
	storeArmor[2].sell = 15000;

	while(true){
		system("cls");
		cout << " ******************************** �κ� ******************************** " << endl;
		cout << "1. ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ����" << endl;

		cout << "�޴��� �����ϼ��� : ";
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
				cout << " ******************************** �� ******************************** " << endl;
				cout << "1. ����" << endl;
				cout << "2. ����" << endl;
				cout << "3. �����" << endl;
				cout << "4. �ڷΰ���" << endl;

				cout << "���� �����ϼ��� : ";
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
						cout << " ******************************** ���� ******************************** " << endl;
						break;
					case MT_NORMAL:
						cout << " ******************************** ���� ******************************** " << endl;
						break;
					case MT_HARD:
						cout << " ******************************** ����� ******************************** " << endl;
						break;
					}

					// �÷��̾� ���� ���
					cout << "=========================== Player ===========================" << endl;
					cout << "�̸� : " << player.name << "\t���� : " << player.jobName << endl;
					cout << "���� : " << player.level << "\t����ġ : " << player.exp << endl;

					// ���� ���� �� ���� ���ݷ� �Բ� ���
					if (player.equipCheck[EQ_WEAPON] == true) {
						cout << "���ݷ� : " << player.attackMin << "(+" << player.currEquipItem[EQ_WEAPON].min << ") - "
							<< player.attackMax << "(+" << player.currEquipItem[EQ_WEAPON].max << ")" << endl;
					}

					else {
						cout << "���ݷ� : " << player.attackMin << " - " << player.attackMax << endl;
					}

					// �� ���� �� �� ���� �Բ� ���
					if (player.equipCheck[EQ_ARMOR] == true) {
						cout << "���� : " << player.armorMin << "(+" << player.currEquipItem[EQ_ARMOR].min << ") - "
							<< player.armorMax << "(+" << player.currEquipItem[EQ_ARMOR].max << ")" << endl;
					}

					else {
						cout << "���� : " << player.armorMin << " - " << player.armorMax << endl;
					}

					// �������� ���� ���
					if (player.equipCheck[EQ_WEAPON] == true) {
						cout << "���� ���� : " << player.currEquipItem[EQ_WEAPON].name << endl;
					}

					else {
						cout << "���� ���� : ����" << endl;
					}

					// �������� �� ���
					if (player.equipCheck[EQ_ARMOR] == true) {
						cout << "���� �� : " << player.currEquipItem[EQ_ARMOR].name << endl;
					}

					else {
						cout << "���� �� : ����" << endl;
					}

					cout << "ü�� : " << player.hp << " / " << player.hpMax << "\t���� : " << player.mp << " / " << player.mpMax << endl;
					cout << "������� : " << player.inventory.gold << "Gold" << endl << endl;

					// ���� ���� ���
					cout << "=========================== Monster ===========================" << endl;
					cout << "�̸� : " << monster.name << "\t���� : " << monster.level << endl;
					cout << "���ݷ� : " << monster.attackMin << " - " << monster.attackMax << endl;
					cout << "���� : " << monster.armorMin << " - " << monster.armorMax << endl;
					cout << "ü�� : " << monster.hp << " / " << monster.hpMax << "\t���� : " << monster.mp << " / " << monster.mpMax << endl;
					cout << "ȹ�� ������ ����ġ : " << monster.exp << "\tȹ�� ������ ��� : " << monster.goldMin << " - " << monster.goldMax << endl << endl;

					cout << "1. ����" << endl;
					cout << "2. ����" << endl;
					cout << "�޴��� �����ϼ��� : ";
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
						// attackMin ~ attackMax ��谪�� ��� ���Եž� �Ѵ�.
						// +1�� �ϰ��� ������ ������ �ؾ� 0~5 ������ ���� ��������.
						// ������ ������ �ϰ� ���� 1�� �����ָ� 1~5 ������ ���� �����ȴ�.

						attackMin = player.attackMin;
						attackMax = player.attackMax;

						// ���� ���ݷ� �߰� ����
						if (player.equipCheck[EQ_WEAPON]) {
							attackMin += player.currEquipItem[EQ_WEAPON].min;
							attackMax += player.currEquipItem[EQ_WEAPON].max;
						}

						attack = (rand() % (attackMax - attackMin + 1)) + attackMin;
						armor = (rand() % (monster.armorMax - monster.armorMin + 1)) + monster.armorMin;

						damage = attack - armor;
						damage = damage < 1 ? 1 : damage;

						monster.hp -= damage;

						cout << player.name << "�� " << monster.name << "���� " << damage << "��ŭ ���ظ� �������ϴ�." << endl;

						// ���� ���
						if (monster.hp <= 0) {
							cout << "���� " << monster.name << "��(��) ����Ͽ����ϴ�." << endl;
							player.exp += monster.exp;
							gold = (rand() % (monster.goldMax - monster.goldMin + 1)) + monster.goldMin;
							
							player.inventory.gold += gold;

							cout << monster.exp << " ����ġ�� ȹ���Ͽ����ϴ�." << endl;
							cout << gold << " Gold�� ȹ���Ͽ����ϴ�." << endl;

							monster.hp = monster.hpMax;
							monster.mp = monster.mpMax;

							// �÷��̾� ������ ���� üũ
							if (player.exp >= levelUpExp[player.level - 1]) {
								player.exp -= levelUpExp[player.level - 1];
								++player.level;

								cout << "������ �Ͽ����ϴ�." << endl;

								// �ɷ�ġ ���
								int jobIndex = player.job - 1;
								int hpUp = rand() % (levelUpTable[jobIndex].hPMax - levelUpTable[jobIndex].hPMin + 1) + levelUpTable[jobIndex].hPMin;
								int mpUp = rand() % (levelUpTable[jobIndex].mPMax - levelUpTable[jobIndex].mPMin + 1) + levelUpTable[jobIndex].mPMin;

								player.attackMax += levelUpTable[jobIndex].attackMax;
								player.attackMin += levelUpTable[jobIndex].attackMin;
								player.armorMax += levelUpTable[jobIndex].armorMax;
								player.armorMin += levelUpTable[jobIndex].armorMin;

								player.hpMax += hpUp;
								player.mpMax += mpUp;

								// ������ �Ͽ����Ƿ� ü��, ���� ȸ��
								player.hp = player.hpMax;
								player.mp = player.mpMax;
								
							}

							system("pause");
							break;
						}

						// ���� ������ �÷��̾� ����
						else {
							attack = (rand() % (monster.attackMax - monster.attackMin + 1)) + monster.attackMin;
							armor = (rand() % (player.armorMax - player.armorMin + 1)) + player.armorMin;

							damage = attack - armor;
							damage = damage < 1 ? 1 : damage;

							player.hp -= damage;

							cout << monster.name << "�� " << player.name << "���� " << damage << "��ŭ ���ظ� �������ϴ�." << endl;

							if (player.hp <= 0) {
								cout << "�÷��̾� " << player.name << "��(��) ����Ͽ����ϴ�." << endl;
								exp = player.exp * 0.1f;
								gold = player.inventory.gold * 0.1f;

								player.exp -= exp;
								player.inventory.gold -= gold;

								cout << exp << " ����ġ�� �Ҿ����ϴ�." << endl;
								cout << gold << " ��带 �Ҿ����ϴ�." << endl;

								// �÷��̾��� HP�� MP ȸ��
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
				cout << " ******************************** ���� ******************************** " << endl;
				cout << "1. ���� ����" << endl;
				cout << "2. �� ����" << endl;
				cout << "3. �ڷΰ���" << endl;
				cout << "������ �����ϼ��� : ";
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
						// �Ǹ� ����� �����ش�
						system("cls");
						cout << " ******************************** ���� ���� ******************************** " << endl;
						for (int i = 0; i < STORE_WEAPON_MAX; ++i) {
							cout << i + 1 << ". �̸� : " << storeWeapon[i].name << "\t���� : " << storeWeapon[i].typeName << endl;
							cout << "���ݷ� : " << storeWeapon[i].min << " - " << storeWeapon[i].max << endl;
							cout << "�Ǹ� ���� : " << storeWeapon[i].price << "\t���� ���� : " << storeWeapon[i].sell << endl;
							cout << "���� : " << storeWeapon[i].description << endl << endl;
						}

						cout << STORE_WEAPON_MAX + 1 << ". �ڷ� ����" << endl << endl;
						cout << "���� �ݾ� : " << player.inventory.gold << endl;
						cout << "���� ���� : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "�޴��� �����ϼ��� : ";
						cin >> menu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (menu == STORE_WEAPON_MAX + 1)	break;

						else if (menu < 1 || menu > STORE_WEAPON_MAX + 1) {
							cout << "�߸� �����Ͽ����ϴ�. " << endl;
							system("pause");
							continue;
						}

						int weaponIndex = menu - 1;

						if (player.inventory.itemCount >= INVENTORY_MAX) {
							cout << "���� ������ �����մϴ�." << endl;
							system("pause");
							continue;
						}

						else if (player.inventory.gold < storeWeapon[weaponIndex].price) {
							cout << "���� �ݾ��� �����մϴ�." << endl;
							system("pause");
							continue;
						}

						player.inventory.gold -= storeWeapon[weaponIndex].price;
						player.inventory.item[player.inventory.itemCount] = storeWeapon[weaponIndex];
						++player.inventory.itemCount;

						cout << "�������� �����Ͽ����ϴ�." << endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true) {
						// �Ǹ� ����� �����ش�
						system("cls");
						cout << " ******************************** �� ���� ******************************** " << endl;
						for (int i = 0; i < STORE_ARMOR_MAX; ++i) {
							cout << i + 1 << ". �̸� : " << storeArmor[i].name << "\t���� : " << storeArmor[i].typeName << endl;
							cout << "���� : " << storeArmor[i].min << " - " << storeArmor[i].max << endl;
							cout << "�Ǹ� ���� : " << storeArmor[i].price << "\t���� ���� : " << storeArmor[i].sell << endl;
							cout << "���� : " << storeArmor[i].description << endl << endl;
						}

						cout << STORE_ARMOR_MAX + 1 << ". �ڷ� ����" << endl << endl;
						cout << "���� �ݾ� : " << player.inventory.gold << endl;
						cout << "���� ���� : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "�޴��� �����ϼ��� : ";
						cin >> menu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (menu == STORE_ARMOR_MAX + 1)	break;

						else if (menu < 1 || menu > STORE_ARMOR_MAX + 1) {
							cout << "�߸� �����Ͽ����ϴ�. " << endl;
							system("pause");
							continue;
						}

						int weaponIndex = menu - 1;

						if (player.inventory.itemCount >= INVENTORY_MAX) {
							cout << "���� ������ �����մϴ�." << endl;
							system("pause");
							continue;
						}

						else if (player.inventory.gold < storeArmor[weaponIndex].price) {
							cout << "���� �ݾ��� �����մϴ�." << endl;
							system("pause");
							continue;
						}

						player.inventory.gold -= storeArmor[weaponIndex].price;
						player.inventory.item[player.inventory.itemCount] = storeArmor[weaponIndex];
						++player.inventory.itemCount;

						cout << "�������� �����Ͽ����ϴ�." << endl;
						system("pause");
					}
					break;
				}
			}
			break;
		case MM_INVENTORY:
			while (true) {
				system("cls");
				cout << " ******************************** ���� ******************************** " << endl;
				cout << "=========================== Player ===========================" << endl;
				cout << "�̸� : " << player.name << "\t���� : " << player.jobName << endl;
				cout << "���� : " << player.level << "\t����ġ : " << player.exp << endl;

				// ���� ���� �� ���� ���ݷ� �Բ� ���
				if (player.equipCheck[EQ_WEAPON] == true) {
					cout << "���ݷ� : " << player.attackMin << "(+" << player.currEquipItem[EQ_WEAPON].min << ") - "
						<< player.attackMax << "(+" << player.currEquipItem[EQ_WEAPON].max << ")" << endl;
				}

				else {
					cout << "���ݷ� : " << player.attackMin << " - " << player.attackMax << endl;
				}

				// �� ���� �� �� ���� �Բ� ���
				if (player.equipCheck[EQ_ARMOR] == true) {
					cout << "���� : " << player.armorMin << "(+" << player.currEquipItem[EQ_ARMOR].min << ") - "
						<< player.armorMax << "(+" << player.currEquipItem[EQ_ARMOR].max << ")" << endl;
				}

				else {
					cout << "���� : " << player.armorMin << " - " << player.armorMax << endl;
				}

				// �������� ���� ���
				if (player.equipCheck[EQ_WEAPON] == true) {
					cout << "���� ���� : " << player.currEquipItem[EQ_WEAPON].name << endl;
				}

				else {
					cout << "���� ���� : ����" << endl;
				}

				// �������� �� ���
				if (player.equipCheck[EQ_ARMOR] == true) {
					cout << "���� �� : " << player.currEquipItem[EQ_ARMOR].name << endl;
				}

				else {
					cout << "���� �� : ����" << endl;
				}

				cout << "ü�� : " << player.hp << " / " << player.hpMax << "\t���� : " << player.mp << " / " << player.mpMax << endl;
				cout << "������� : " << player.inventory.gold << "Gold" << endl << endl;

				for (int i = 0; i < player.inventory.itemCount; ++i) {
					cout << i + 1 << ". �̸� : " << player.inventory.item[i].name << "\t���� : " << player.inventory.item[i].typeName << endl;
					cout << "���� : " << player.inventory.item[i].min << " - " << player.inventory.item[i].max << endl;
					cout << "�Ǹ� ���� : " << player.inventory.item[i].price << "\t���� ���� : " << player.inventory.item[i].sell << endl;
					cout << "���� : " << player.inventory.item[i].description << endl << endl;
				}

				cout << player.inventory.itemCount + 1 << ". �ڷ� ����" << endl;
				cout << "������ ��� �����ϼ��� : ";
				cin >> menu;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (menu == player.inventory.itemCount + 1)		break;

				else if (menu<1 || menu > player.inventory.itemCount + 1) {
					cout << "�߸� �Է��Ͽ����ϴ�." << endl;
					system("pause");
					continue;
				}

				int itemIndex = menu - 1;

				EQUIP eq;

				// ������ �κ��丮 �������� ���� Ÿ�� üũ
				switch (player.inventory.item[itemIndex].type) {
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				// �ش� Ÿ���� ���⸦ �̹� �����ϰ� �ִٸ�, ��� ����
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

					// �������� ���������Ƿ� true�� �����Ѵ�.
					player.equipCheck[eq] = true;
				}

				cout << "��� �����Ͽ����ϴ�." << endl;

				system("pause");
			}
			break;
		default:
			cout << "�߸� �����Ͽ����ϴ�." << endl;
			break;
		}

	}

	return 0;
}