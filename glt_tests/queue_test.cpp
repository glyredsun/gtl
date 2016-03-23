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

	gtl::queue<int> q1(q);
	gtl::queue<int> q2(std::move(q));

	assert(q.empty());

	while (!q1.empty()) {
		assert(q1.front() == q2.front());
		q1.pop();
		q2.pop();
	}

	assert(q2.empty());

	system("pause");
	return 0;
}