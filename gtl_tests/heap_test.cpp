#include "binheap.hpp"

#include "vector.hpp"
#include "algorithm.hpp"

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

	int min;
	while (!h.empty())
	{
		h.pop(min);
		std::cout << min << std::endl;
	}

	std::cout << "test heap algorithms" << std::endl;
	gtl::vector<int> v{3, 6, 4, 7, 12, 1};
	for (auto elem : v)
	{
		std::cout << elem << std::endl;
	}
	std::cout << std::endl;
	gtl::make_heap(v.begin(), v.end());
	std::cout << "after make_heap" << std::endl;
	for (auto elem : v)
	{
		std::cout << elem << std::endl;
	}
	std::cout << std::endl;
	v.push_back(19);
	gtl::push_heap(v.begin(), v.end());
	std::cout << "after push 19" << std::endl;
	for (auto elem : v)
	{
		std::cout << elem << std::endl;
	}
	v.push_back(2);
	gtl::push_heap(v.begin(), v.end());
	std::cout << "after push 2" << std::endl;
	for (auto elem : v)
	{
		std::cout << elem << std::endl;
	}
	gtl::sort_heap(v.begin(), v.end());
	std::cout << "after sort_heap" << std::endl;
	for (auto elem : v)
	{
		std::cout << elem << std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}