#include <vector.hpp>

#include <iostream>

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
	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(i);
	}

	size_t s = 0;
	for (gtl::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << ++s << ":" << *it << std::endl;
	}
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