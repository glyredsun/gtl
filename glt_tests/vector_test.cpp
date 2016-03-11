#include <vector.hpp>

#include <iostream>

int main(void)
{
	
	gtl::vector<int> v;
	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(i);
	}

	size_t s = 0;
	for (gtl::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << ++s << ":" << *it << std::endl;
	}

	return 0;
}