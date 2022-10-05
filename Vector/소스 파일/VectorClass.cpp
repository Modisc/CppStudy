#include <iostream>
#include "VectorClass.h"

int main()
{
	VectorClass<int> vec_int;

	// 이렇게 사용하면 Resize() 함수가 실행되지 않으므로
	// 실제 사용시 아주 미세하게라도 성능이 더 좋아질 것.
	vec_int.Reserve(100);
	// VectorClass<int> vec_int(100); 생성자 함수 오버로딩도 해뒀으므로 이것도 Reserve() 함수와 같은 기능을 함

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
