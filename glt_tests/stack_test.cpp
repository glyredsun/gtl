#include <stack.hpp>

#include <iostream>

int main(void)
{
	gtl::stack<int> is;
	is.push(1);
	is.push(2);
	is.push(3);

	while (!is.empty()) {
		std::cout << is.top() << std::endl;
		is.pop();
	}
	system("pause");
	return 0;
}