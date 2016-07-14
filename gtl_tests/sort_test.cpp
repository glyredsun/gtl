#include "sort.hpp"

#include "vector.hpp"

#include <cstdlib>
#include <cassert>

#include <iostream>
#include <chrono>
#include <random>

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

class TimeCounter
{
public:
	using system_clock = std::chrono::system_clock;
	using time_point = system_clock::time_point;

	TimeCounter()
	{
		reset();
	}

	void reset()
	{
		begin = system_clock::now();
	}

	double count()
	{
		auto d = system_clock::now() - begin;
		return std::chrono::duration < double, std::ratio<1, 1>> (d).count();
	}

private:
	time_point begin;
};

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

	std::cout << "begin merge sort" << std::endl;
	tc.reset();
	gtl::vector<int> vec3 = vec;
	gtl::mergeSort(vec3.begin(), vec3.end());
	std::cout << "merge sort cost " << tc.count() << "s" << std::endl;

	std::cout << "begin shell sort" << std::endl;
	tc.reset();
	gtl::vector<int> vec2 = vec;
	gtl::shellSort(vec2.begin(), vec2.end());
	std::cout << "shell sort cost " << tc.count() << "s" << std::endl;
	
	std::cout << "begin insertion sort" << std::endl;
	tc.reset();
	gtl::vector<int> vec1 = vec;
	gtl::insertionSort(vec1.begin(), vec1.end());
	std::cout << "insertion sort cost " << tc.count() << "s" << std::endl;

	for (size_t i = 0; i < VEC_LEN; ++i)
	{
		assert(vec1[i] == vec2[i] && vec1[i] == vec3[i]);
	}

	system("pause");

	return EXIT_SUCCESS;
}