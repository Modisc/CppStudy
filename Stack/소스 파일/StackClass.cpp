#include <iostream>
#include "StackClass.h"

int main()
{
	StackClass<int> stack;

	for (int i = 0; i < 100; i++)
	{
		stack.Push(i + 1);
	}

	while (!stack.Empty())
	{
		cout << stack.Pop() << endl;
	}
}
