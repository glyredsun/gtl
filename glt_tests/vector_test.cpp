#include <vector.hpp>

#include <iostream>
#include <memory>
#include <vector>
int main(void)
{
	std::vector<int> sv1{1, 2, 3};
	std::vector<int> sv2{ 4, 5, 6 };
	
	sv1 = std::move(sv2);
	
	struct S
	{
		int a;
		int b;
	};
	
	gtl::vector<int> v;
	for (size_t i = 0; i < 20; i++)
	{
		v.push_back(i);
	}
	
	size_t s = 0;
	std::cout << "content of v" << std::endl;
	for (gtl::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << s++ << ":" << *it << std::endl;
	}

	std::cout << "erase1" << std::endl;
	v.erase(v.begin() + 2, v.begin() + 4);
	s = 0;
	for (gtl::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << s++ << ":" << *it << std::endl;
	}
	
	std::cout << "insert1" << std::endl;
	v.insert(v.begin() + 3, 11111);
	v.insert(v.begin() + 10, 22222);
	s = 0;
	for (gtl::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << s++ << ":" << *it << std::endl;
	}

	std::cout << "insert2" << std::endl;
	v.insert(v.begin() + 12, 3, 33333);
	s = 0;
	for (gtl::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << s++ << ":" << *it << std::endl;
	}

	std::cout << "insert3" << std::endl;
	v.insert(v.begin() + 20, { 10001, 10002, 10003, 10004 });
	s = 0;
	for (gtl::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << s++ << ":" << *it << std::endl;
	}
	
	std::cout << "reverse content" << std::endl;
	for (gtl::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
	{
		std::cout << s-- << ":" << *it << std::endl;
	}

	gtl::vector<int> v1(v);
	gtl::vector<int> v2(std::move(v));

	gtl::vector<S> vs;
	vs.push_back({ 1, 2 });
	for (gtl::vector<S>::iterator it = vs.begin(); it != vs.end(); it++)
	{
		std::cout << it->a << " " << it->b << std::endl;
	}
	
	system("pause");
	return 0;
}