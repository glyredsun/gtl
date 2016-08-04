#include "algorithm.hpp"

#include <assert.h>
#include <cstdlib>

int main(void)
{
	int *a, *b;

	a = (int*)malloc(sizeof(int) * 1024);
	b = (int*)malloc(sizeof(int) * 1024);

	memset(a, 0, sizeof(int) * 1024);

	gtl::move(a, a + 1024, b);

	for (int i = 0; i < 1024; ++i)
	{
		assert(b[i] == 0);
	}

	return 0;
}