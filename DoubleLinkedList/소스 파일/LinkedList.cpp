#include <iostream>
#include "LinkedList.h"

using std::cout;
using std::cin;
using std::endl;

/*
reverse iterator 기능 만들기
reverse iterator는 뒤에서부터 순회하는 기능이다.
일반 iterator의 반대 기능이다.

reverse iterator 클래스를 제작해서
iterator 만들듯이 제작하기.
*/

int main()
{
	// 지역변수이므로 프로그램 실행 끝나면 자동으로 사라진다.
	// 노드들은 LinkedList의 소멸자에서 모두 삭제해주므로 메모리 누수 현상이 발생하지 않는다.
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
