#include <list.hpp>

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
	return 0;
}
 
