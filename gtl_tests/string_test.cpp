#include <string.hpp>

#include <iostream>

#include <string>

int main(void)
{
	gtl::string s;
	s.push_back('a');
	s.push_back('b');
	s.push_back('c');

	std::cout << s << std::endl;

	gtl::string s1("def");
	std::cout << s1 << std::endl;

	gtl::string s2('A');
	std::cout << s2 << std::endl;

	s2.append("BCDE");
	std::cout << s2 << std::endl;

	system("pause");
	return 0;
}