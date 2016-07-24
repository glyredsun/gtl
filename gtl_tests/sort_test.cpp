
#include <sort.hpp>
#include <vector.hpp>
#include <algorithm.hpp>

#include "TimeCounter.hpp"

#include <cstdlib>
#include <cassert>

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

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
	const int VEC_LEN = 10000000;
	gtl::vector<int> vec(VEC_LEN);
	for (size_t i = 0; i < VEC_LEN; ++i)
	{
		vec[i] = i;
	}
	std::random_device rndDevice;
	std::mt19937 eng(rndDevice());
	std::uniform_int_distribution<int> dist(0, VEC_LEN - 1);
	for (int i = 0; i < VEC_LEN / 2; ++i)
	{
		int idx1 = dist(eng);
		int idx2 = dist(eng);
		gtl::swap(vec[idx1], vec[idx2]);
	}

	TimeCounter tc;

	gtl::vector<int> vec4 = vec;
	std::cout << "begin parallelize merge sort" << std::endl;
	tc.reset();
	gtl::mergeSortParallel(vec4.begin(), vec4.end());
	std::cout << "parallelize merge sort cost " << tc.count() << "s" << std::endl;

	gtl::vector<int> vec3 = vec;
	std::cout << "begin merge sort" << std::endl;
	tc.reset();
	gtl::mergeSort(vec3.begin(), vec3.end());
	std::cout << "merge sort cost " << tc.count() << "s" << std::endl;

	gtl::vector<int> vec2 = vec;
	std::cout << "begin shell sort" << std::endl;
	tc.reset();
	gtl::shellSort(vec2.begin(), vec2.end());
	std::cout << "shell sort cost " << tc.count() << "s" << std::endl;
	
	//gtl::vector<int> vec1 = vec;
	//std::cout << "begin insertion sort" << std::endl;
	//tc.reset();
	//gtl::insertionSort(vec1.begin(), vec1.end());
	//std::cout << "insertion sort cost " << tc.count() << "s" << std::endl;

	for (size_t i = 0; i < VEC_LEN; ++i)
	{
		//assert(vec1[i] == vec2[i] && vec1[i] == vec3[i]);
		if (i) {
			assert(vec2[i] >= vec2[i - 1]);
		}
		assert(vec2[i] == vec3[i] && vec3[i] == vec4[i]);
	}

	gtl::vector<int>::iterator result = gtl::search(vec4.begin(), vec4.end(), 5999);
	assert(result != vec4.end());
	std::cout << "search result " << *result << std::endl;

	result = gtl::search(vec4.begin(), vec4.end(), -1);
	assert(result == vec4.end());

	system("pause");

	return EXIT_SUCCESS;
}