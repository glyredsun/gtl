#include <type_traits.hpp>

#include <iostream>

class A
{
public:
	A()
	{
		std::cout << "A()" << std::endl;
	}

	A(const A &other)
	{
		std::cout << "A(const A &other)" << std::endl;
	}

	A(A &&other)
	{
		std::cout << "A(A &&other)" << std::endl;
	}

	~A()
	{
		std::cout << "~A()" << std::endl;
	}

	A& operator = (const A &other)
	{
		std::cout << "A& operator = (const A &other)" << std::endl;
		return *this;
	}

	A& operator = (A&& other)
	{
		std::cout << "A& operator = (A&& other)" << std::endl;
		return *this;
	}

};

int main(void)
{
	A a1, a2, a3;

	A a4(a1);
	A a5(gtl::move(a1));
	a1 = a2;
	a2 = std::move(a3);

	system("pause");
	return 0;
}