#include <algorithm.hpp>

#include <assert.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>

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

	int arr[] = {0, 1, 2, 3, 4, 5};
	int idx = gtl::search(arr, 11);
	std::cout << "idx is " << idx << std::endl;

	system("pause");
	return 0;
}