#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "defines.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::iterator;
using std::list;

template <typename T>
T Input()
{
	T data;
	cin >> data;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return 0;
	}

	return data;
}

template <typename T>
void SafeDeleteVecList(T& p)
{
	// �̷��Ը� ���� ������ �߻��Ѵ�.
	// T::iterator ���� T�� Ÿ������, ���ӽ����̽����� �������� �����Ϸ��� �� �� ����.
	// ���� �տ� typename �� �ٿ���� �Ѵ�.
	// ���ø� �ȿ��� ��ø ���� �̸�(���ø� �Ű������� ���ӵ� ��)�� ������ ��� typename Ű���带 �ٿ��ֵ��� ����.
	/*T::iterator iter;
	T::iterator iter_end = p.end();*/

	typename T::iterator iter;
	typename T::iterator iter_end = p.end();

	for (iter = p.begin(); iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	// vector ���� �ʱ�ȭ
	// vector�� size 0���� �ʱ�ȭ����.
	// vector�� capacity�� �ʱ�ȭ ���� ���� ���ɼ��� �ִ�.(�ʱ�ȭ ���� �ʴ� �� ����)
	// ������ ���� �� ���ҵ��� ��� delete�ϰ� NULL�� �ٲ� �� p.clear�� ȣ���ߴµ�,
	// clear() �Լ��� ����ص� ���� ���ҵ��� �Ҹ��ڱ��� ��� ȣ���ؼ� �������ش�. => ���� for���� ���� �ʿ����� �𸣰���.
	p.clear();
}
