#include "Core.h"

int main()
{
	if (!Core::GetInstance()->Init())
	{
		Core::DestroyInstance();
		return 0;
	}

	Core::GetInstance()->Run();

	Core::DestroyInstance();

	return 0;
}