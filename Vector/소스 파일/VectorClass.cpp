#include <iostream>
#include "VectorClass.h"

int main()
{
	VectorClass<int> vec_int;

	// �̷��� ����ϸ� Resize() �Լ��� ������� �����Ƿ�
	// ���� ���� ���� �̼��ϰԶ� ������ �� ������ ��.
	vec_int.Reserve(100);
	// VectorClass<int> vec_int(100); ������ �Լ� �����ε��� �ص����Ƿ� �̰͵� Reserve() �Լ��� ���� ����� ��

	for (int i = 0; i < 100; i++)
	{
		vec_int.PushBack(i + 1);
	}

	for (int i = 0; i < vec_int.GetSize(); i++)
	{
		cout << vec_int[i] << endl;
	}

	cout << endl << vec_int.GetSize() << endl << endl;

	VectorClass<int>::Iterator iter;
	for (iter = vec_int.begin(); iter < vec_int.end(); ++iter)
	{
		cout << *iter << endl;
	}

	return 0;
}
