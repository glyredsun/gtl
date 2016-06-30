#include "sort.hpp"

#include "vector.hpp"

#include <cstdlib>
#include <cassert>

#include <vector>
#include <iostream>

int main(void)
{
	gtl::vector<int> vec{1, 5, 0, 2, 4, 9};

	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (i) {
			std::cout << ", ";
		}
		std::cout << vec[i];
	}
	std::cout << std::endl;

	insertionSort(vec.begin(), vec.end(), [](const int &a, const int &b) { return a > b; });
	//insertionSort(vec.begin(), vec.end());

	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (i) {
			std::cout << ", ";
		}
		std::cout << vec[i];
	}
	std::cout << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}