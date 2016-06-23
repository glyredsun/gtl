#include <bstree.hpp>

#include <iostream>

int main(void)
{
	std::cout << "int" << std::endl;
	gtl::bstree<int> t;
	t.insert(19);
	t.insert(11);
	t.insert(1);
	t.insert(9);
	t.insert(6);
	t.insert(13);
	t.insert(23);
	t.insert(29);
	t.insert(24);
	t.insert(5);
	t.insert(2);
	t.insert(35);
	t.insert(7);
	t.insert(10);

	t.print();

	std::cout << std::endl << std::endl << std::endl;

	t.midorderTraverse([](int n) {
		std::cout << n << std::endl;
	});

	gtl::bstree<int> t1(std::move(t));
	t1.remove(11);
	t1.remove(19);
	std::cout << "after remove" << std::endl;
	t1.midorderTraverse([](int n) {
		std::cout << n << std::endl;
	});

	std::cout << "string" << std::endl;
	gtl::bstree<std::string> ts;
	ts.insert("dasfase");
	ts.insert("23");
	ts.insert("3rfgrgasdf");
	ts.insert("dasfrg123");
	ts.insert("y72124");

	system("pause");
	return 0;
}