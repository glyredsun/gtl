#include <list.hpp>

#include <list.h>

#include <iostream>

#include <list>
#include <assert.h>


struct S1 {
	int a;
	std::string b;
};

std::ostream& operator <<(std::ostream &out, const S1 s)
{
	out << s.a << ", " << s.b.c_str();
	return out;
}

int main(void)
{
	gtl::list<int> *il = new gtl::list<int>;

	gtl::list<int>::iterator it1 = il->begin();
	il->insert(it1, 10000);

	il->push_back(1);
	il->push_front(2);
	il->push_back(3);
	il->push_front(4);

	gtl::list<int>::iterator it2 = il->begin();
	il->insert(it2, 1000);
	++it2; ++it2;
	il->insert(it2, 100);
	il->insert(--it2, {11111, 22222, 33333, 44444});

	std::cout << "traverse il by iterator" << std::endl;
	for (gtl::list<int>::iterator it = il->begin(); it != il->end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	std::cout << "erase1" << std::endl;
	il->erase(il->begin() + 1, il->begin() + 3);
	
	for (gtl::list<int>::iterator it = il->begin(); it != il->end(); ++it)
	{
		std::cout << *it << std::endl;
	}


	gtl::list<int> il1(*il);
	gtl::list<int> il2;
	il2.push_back(1);
	il2.push_back(2);
	il2.push_back(3);
	il2.push_back(4);
	il2.push_back(5);
	il2.push_back(6);
	il2 = *il;
	gtl::list<int> *il3 = new gtl::list<int>(std::move(*il));

	
	gtl::list<S1> s1l;
	s1l.push_back({ 1, "a" });
	s1l.push_back({ 2, "b" });
	s1l.push_back({ 3, "c" });
	for (gtl::list<S1>::iterator it = s1l.begin(); it != s1l.end(); ++it)
	{
		std::cout << it->a << ", " << it->b.c_str() << std::endl;
	}
	for (gtl::list<S1>::reverse_iterator it = s1l.rbegin(); it != s1l.rend(); ++it)
	{
		std::cout << it->a << ", " << it->b.c_str() << std::endl;
	}


	std::cout << "before delete il" << std::endl;
	delete il;
	std::cout << "after delete il" << std::endl;

	std::cout << "before delete il3" << std::endl;
	delete il3;
	std::cout << "after delete il3" << std::endl;

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
	S *s6 = (S*)malloc(sizeof(*s6));
	list_init(&s6->list);
	s6->n = 6;

	list_add(&s6->list, &h);
	list_add(&s1.list, &h);
	list_add(&s2.list, &h);
	list_add(&s3.list, &h);
	list_add(&s4.list, &h);
	list_add_tail(&s5.list, &h);

	struct list_head *p;
	struct list_head *n;
	S *tmp;

	printf("list_foreach_safe\n");
	list_foreach_safe(p, n, &h)
	{
		tmp = container_of(p, S, list);
		printf("%d\n", tmp->n);
		if (tmp->n == 6) {
			list_del_init(p);
			free(tmp);
		}
	}
	
	
	printf("list_foreach_entry\n");
	list_foreach_entry(tmp, S, &h, list)
	{
		printf("%d\n", tmp->n);
	}

	printf("list_foreach_entry_reverse\n");
	list_foreach_entry_reverse(tmp, S, &h, list)
	{
		printf("%d\n", tmp->n);
	}

	printf("list_foreach_prev_safe\n");
	list_foreach_prev_safe(p, n, &h)
	{
		tmp = container_of(p, S, list);
		printf("%d\n", tmp->n);
		list_del(p);
	}

	assert(list_empty(&h));
	assert(!list_is_singular(&h));
	system("pause");
	return 0;
}
 
