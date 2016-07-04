#include "binheap.hpp"

#include <iostream>

#include <cstdlib>

int main(void)
{
	gtl::binheap<int> h;

	h.push(9);
	h.push(1);
	h.push(5);
	h.push(6);
	h.push(11);
	h.push(956);
	h.push(61);
	h.push(95);
	h.push(24);
	h.push(436);

	for (size_t i = 0; i < h.size(); ++i)
	{
		std::cout << h.container()[i + 1] << std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}