#include "Core.h"
#include "StageManager.h"

DEFINITION_SINGLE(Core)

enum class MainMenu
{
	none,
	stage,
	store,
	inventoty,
	status,
	exit
};

Core::Core()
{

}

Core::~Core()
{
	DESTROY_SINGLE(StageManager);
}

bool Core::Init()
{
	// Stage �ʱ�ȭ
	if (!GET_SINGLE(StageManager)->Init())
		return false;

	return true;
}

void Core::Run()
{
	while (true)
	{
		switch (OutputMenu())
		{
		case static_cast<int>(MainMenu::stage):
			GET_SINGLE(StageManager)->Run();
			break;
		case static_cast<int>(MainMenu::store):
			break;
		case static_cast<int>(MainMenu::inventoty):
			break;
		case static_cast<int>(MainMenu::status):
			break;
		case static_cast<int>(MainMenu::exit):
			return;
		}
	}
}

int Core::OutputMenu()
{
	system("cls");
	cout << "1. ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. �κ��丮" << endl;
	cout << "4. ĳ���� ����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int menu = Input<int>();

	if (menu <= static_cast<int>(MainMenu::none) || menu > static_cast<int>(MainMenu::exit))
		return static_cast<int>(MainMenu::none);

	return menu;
}
