#include <avltree.hpp>

int main(void)
{
	gtl::avltree<int> t;

	for (int i = 0; i < 31; i++)
	{
		t.insert(i);
		t.print();
		std::cout << std::endl;
	}

	system("pause");

	return 0;
}