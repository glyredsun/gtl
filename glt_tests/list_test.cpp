#include <list.hpp>

#include <list.h>

#include <iostream>

#include <list>
int main(void)
{
	gtl::list<int> *il = new gtl::list<int>;
	il->push_back(1);
	il->push_front(2);
	il->push_back(3);
	il->push_front(4);

	//std::list<int> l;
	//il->pop_back();
	//while (!il.empty())
	//{
	//	std::cout << il.front() << std::endl;
	//	il.pop_front();
	//}

	for (gtl::list<int>::iterator it = il->begin(); it != il->end(); ++it)
	{
		std::cout << *it << std::endl;
	}

 	system("pause"); 
	delete il;
	system("pause");

	printf("c list test\n");
	struct list_head h = LIST_HEAD_INIT(h);
	struct S
	{
		int n;
		struct list_head list;
	};
	S s1 = {1, LIST_HEAD_INIT(s1.list)};
	S s2 = {2, LIST_HEAD_INIT(s2.list)};
	S s3 = {3, LIST_HEAD_INIT(s3.list)};
	S s4 = {4, LIST_HEAD_INIT(s4.list)};
	S s5 = {5, LIST_HEAD_INIT(s5.list) };
	list_add(&s1.list, &h);
	list_add(&s2.list, &h);
	list_add(&s3.list, &h);
	list_add(&s4.list, &h);
	list_add_tail(&s5.list, &h);
	struct list_head *p;
	struct list_head *n;
	S *tmp;
	list_foreach_safe(p, n, &h)
	{
		tmp = container_of(p, S, list);
		printf("%d\n", tmp->n);
		if (tmp->n == 2 || tmp->n == 5) {
			list_del(p);
		}
	}

	putchar('\n');

	list_foreach_prev(p, &h)
	{
		tmp = container_of(p, S, list);
		printf("%d\n", tmp->n);
	}

	system("pause");
	return 0;
}
 
