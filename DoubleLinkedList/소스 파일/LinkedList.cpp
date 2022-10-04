#include <iostream>
#include "LinkedList.h"

using std::cout;
using std::cin;
using std::endl;

/*
reverse iterator ��� �����
reverse iterator�� �ڿ������� ��ȸ�ϴ� ����̴�.
�Ϲ� iterator�� �ݴ� ����̴�.

reverse iterator Ŭ������ �����ؼ�
iterator ������� �����ϱ�.
*/

int main()
{
	// ���������̹Ƿ� ���α׷� ���� ������ �ڵ����� �������.
	// ������ LinkedList�� �Ҹ��ڿ��� ��� �������ֹǷ� �޸� ���� ������ �߻����� �ʴ´�.
	LinkedList<int> list_int;
	LinkedList<float> list_float;

	for (int i = 0; i < 100; i++)
	{
		list_int.insert_back(i + 1);
	}

	cout << list_int.GetSize() << endl << endl;

	LinkedList<int>::Iterator iter;
	for (iter = list_int.begin(); iter != list_int.end(); ++iter)
	{
		cout << *iter << endl;
	}

	cout << endl;

	LinkedList<int>::ReverseIterator reiter;
	for (reiter = list_int.last(); reiter != list_int.first(); --reiter)
	{
		cout << *reiter << endl;
	}

	return 0;
}
