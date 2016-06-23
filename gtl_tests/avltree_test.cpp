#include <avltree.hpp>

#include <random>

#define	TREE_DEPTH	6

int main(void)
{
	gtl::avltree<uint64_t> t;
	int nodesNum = static_cast<int>(pow(2, TREE_DEPTH)) - 1;
	std::random_device rnd;
	uint64_t n;

	for (int i = 1; i <= nodesNum; i++)
	{
		n = rnd() % nodesNum;
		if (t.find(n) != t.end()) {
			--i;
		}
		else {
			t.insert(n);
		}
	}

	t.print();

	std::cout << "iteration" << std::endl;
	for (gtl::avltree<uint64_t>::iterator itr = t.begin(); itr != t.end(); ++itr)
	{
		std::cout << *itr << std::endl;
	}

	t.remove(n);
	std::cout << "after remove " << n << std::endl;
	t.print();

	std::cout << "iteration" << std::endl;
	for (gtl::avltree<uint64_t>::iterator itr = t.begin(); itr != t.end(); ++itr)
	{
		std::cout << *itr << std::endl;
	}

	t.makeEmpty();

	system("pause");

	return 0;
}