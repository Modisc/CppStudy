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
	// 이렇게만 쓰면 오류가 발생한다.
	// T::iterator 에서 T가 타입인지, 네임스페이스인지 무엇인지 컴파일러는 알 수 없다.
	// 따라서 앞에 typename 을 붙여줘야 한다.
	// 템플릿 안에서 중첩 의존 이름(템플릿 매개변수에 종속된 것)을 참조할 경우 typename 키워드를 붙여주도록 하자.
	/*T::iterator iter;
	T::iterator iter_end = p.end();*/

	typename T::iterator iter;
	typename T::iterator iter_end = p.end();

	for (iter = p.begin(); iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	// vector 내부 초기화
	// vector의 size 0으로 초기화해줌.
	// vector의 capacity는 초기화 되지 않을 가능성이 있다.(초기화 되지 않는 것 같음)
	// 위에서 내부 각 원소들을 모두 delete하고 NULL로 바꾼 후 p.clear를 호출했는데,
	// clear() 함수만 사용해도 내부 원소들의 소멸자까지 모두 호출해서 삭제해준다. => 위의 for문이 굳이 필요한지 모르겠음.
	p.clear();
}
