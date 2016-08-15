#include <queue.hpp>

#include <iostream>
#include <queue>
#include <algorithm>

#include <assert.h>

int main(void)
{
	gtl::queue<int> q;
	for (int i = 0; i < 128; i++)
	{
		q.push(i);
	}

	for (int i = 0; i < 32; i++)
	{
		q.pop();
	}

	for (int i = 128; i < 256; i++)
	{
		q.push(i);
	}

	size_t s = q.size();
	printf("q size %d\n", s);
	gtl::queue<int> q1(q);
	gtl::queue<int> q2;
	q2 = q;
	gtl::queue<int> q3(std::move(q));
	

	assert(s == q1.size() && s == q2.size() && s == q3.size());

	assert(q.empty());

	while (!q1.empty()) {
		assert(q1.front() == q2.front() && q2.front() == q3.front());
		printf("front is %d\n", q2.front());
		q1.pop();
		q2.pop();
		q3.pop();
	}

	assert(q2.empty());
	assert(q3.empty());

	printf("-------------------------------------------------------------\n");

	q.clear();
	
	gtl::priority_queue<int> pq;

	pq.push(11);
	pq.push(423);
	pq.push(1);
	pq.push(42);
	pq.push(31);
	pq.push(892);
	pq.push(19);

	std::cout << "pq content" << std::endl;
	while (!pq.empty()) {
		std::cout << pq.top() << std::endl;
		pq.pop();
	}

	system("pause");
	
	return 0;
}