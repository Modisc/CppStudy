#include "core.h"

int main()
{
	if (!GET_SINGLE(Core)->Init())
	{
		DESTROY_SINGLE(Core);
		return 0;
	}

	GET_SINGLE(Core)->Run();

	DESTROY_SINGLE(Core);

	return 0;
}