#include "sort.hpp"

#include "vector.hpp"

#include <cstdlib>
#include <cassert>

#include <iostream>

template <typename Iterator>
static void printAll(Iterator begin, Iterator end)
{
	bool flag = false;
	while (begin < end)
	{
		if (flag)
			std::cout << ", ";
		else
			flag = true;

		std::cout << *begin++;
	}
	std::cout << std::endl;
}

int main(void)
{
	gtl::vector<int> vec{1, 5, 0, 2, 4, 9};
	printAll(vec.begin(), vec.end());

	gtl::vector<int> vec1 = vec;
	insertionSort(vec1.begin(), vec1.end());
	printAll(vec1.begin(), vec1.end());

	gtl::vector<int> vec2 = vec;
	gtl::shellSort(vec2.begin(), vec2.end());
	printAll(vec2.begin(), vec2.end());
	
	gtl::vector<int> vec3 = vec;
	gtl::mergeSort(vec3.begin(), vec3.end());
	printAll(vec3.begin(), vec3.end());

	system("pause");

	return EXIT_SUCCESS;
}