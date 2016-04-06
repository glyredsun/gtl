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
		if (!t.insert(n)) {
			--i;
		}
	}

	t.print();

	t.remove(n);
	std::cout << "after remove " << n << std::endl;
	t.print();

	t.makeEmpty();

	system("pause");

	return 0;
}