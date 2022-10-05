#include <iostream>
#include "QueueClass.h"


int main()
{
	QueueClass<int> queue;

	for (int i = 0; i < 100; i++)
	{
		queue.Push(i + 1);
	}

	while (!queue.Empty())
	{
		cout << queue.Pop() << endl;
	}

	cout << endl << endl;

	CircleQueue<int, 10> circle_que;

	for (int i = 0; i < 10; i++)
	{
		circle_que.Push(i + 1);
	}

	cout << "3개 pop" << endl;

	for (int i = 0; i < 3; i++)
	{
		cout << circle_que.Pop() << endl;
	}

	cout << endl << "8개 push" << endl;

	for (int i = 4; i < 12; i++)
	{
		circle_que.Push(i);
	}	

	cout << "전부 pop" << endl;
	while (!circle_que.Empty())
	{
		cout << circle_que.Pop() << endl;
	}

	return 0;
}