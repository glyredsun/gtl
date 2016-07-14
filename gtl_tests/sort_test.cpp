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

	//insertionSort(vec.begin(), vec.end(), [](const int &a, const int &b) { return a > b; });
	//insertionSort(vec.begin(), vec.end());

	gtl::vector<int> vec1 = vec;
	shellSort(vec1.begin(), vec1.end());

	for (size_t i = 0; i < vec1.size(); ++i)
	{
		if (i) {
			std::cout << ", ";
		}
		std::cout << vec1[i];
	}
	std::cout << std::endl;

	gtl::vector<int> vec2 = vec;
	mergeSort(vec2.begin(), vec2.end());

	for (size_t i = 0; i < vec2.size(); ++i)
	{
		if (i) {
			std::cout << ", ";
		}
		std::cout << vec2[i];
	}
	std::cout << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}