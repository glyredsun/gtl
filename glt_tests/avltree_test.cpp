#include <avltree.hpp>

#include <random>

#define	TREE_DEPTH	6

int main(void)
{
	gtl::avltree<uint64_t> t;
	int nodesNum = static_cast<int>(pow(2, TREE_DEPTH)) - 1;
	std::random_device rnd;

	for (int i = 1; i <= nodesNum; i++)
	{
		uint64_t n = rnd() % nodesNum;
		if (!t.insert(n)) {
			--i;
		}
	}

	t.print();

	t.makeEmpty();

	system("pause");

	return 0;
}