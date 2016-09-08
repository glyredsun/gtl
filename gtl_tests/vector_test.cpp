#include <vector.hpp>

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <string>

template <class Iterator>
void print(Iterator first, Iterator last)
{
	bool flag = false;
	while (first < last)
	{
		if (flag)
		{
			std::cout << ", ";
		}
		else
		{
			flag = true;
		}
		std::cout << *first++;
	}
}

struct S
{
	S() {}
	S(std::initializer_list<int> args)
	{
		a = args.begin()[0];
		b = args.begin()[1];
	}

	int a;
	int b;

	friend std::ostream& operator<<(std::ostream &o, const S& s)
	{
		return o << "{ a = " << s.a << ", b = " << s.b << " }";
	}
};

int main(void)
{
	gtl::vector<int> v1{ 1, 2, 3 };
	gtl::vector<int> v2{ 4, 5, 6 };
	gtl::vector<int> v3{ 7, 8, 9, 10, 11, 12, 13 };
	
	gtl::vector<int> v;
	for (size_t i = 0; i < 20; i++)
	{
		v.push_back(i);
	}
	
	std::cout << "\ncontent of v\n";
	print(v.begin(), v.end());

	std::cout << "\nerase1\n";
	v.erase(v.begin() + 2, v.begin() + 4);
	print(v.begin(), v.end());
	
	std::cout << "\ninsert1\n";
	v.insert(v.begin() + 3, 11111);
	v.insert(v.begin() + 10, 22222);
	print(v.begin(), v.end());
	
	std::cout << "\ninsert2\n";
	v.insert(v.begin() + 12, 3, 33333);
	print(v.begin(), v.end());
	
	std::cout << "\ninsert3\n";
	v.insert(v.begin() + 20, { 10001, 10002, 10003, 10004 });
	print(v.begin(), v.end());
	
	std::cout << "\ninsert4\n";
	v.insert(v.begin() + 3, v1.begin(), v1.end());
	print(v.begin(), v.end());

	std::cout << "\ninsert5\n";
	v.insert(v.begin() + 11, v2.begin(), v2.end());
	print(v.begin(), v.end());

	std::cout << "\ninsert6\n";
	v.insert(v.begin() + 20, v3.begin(), v3.end());
	print(v.begin(), v.end());

	std::cout << "\nreverse content\n";
	print(v.rbegin(), v.rend());

	gtl::vector<int> vCopy(v);
	std::cout << "\ncopy content\n";
	print(vCopy.begin(), vCopy.end());

	gtl::vector<S> vs;
	vs.push_back(S{ 1, 2 });
	vs.push_back({ 3, 4 });
	std::cout << "\nvs content\n";
	print(vs.begin(), vs.end());
	
	gtl::vector<std::string> vstr;
	for (char i = 0; i < 26; i++)
	{
		std::string s;
		for (int j = 0; j < 30; j++)
		{
			s.push_back('A' + i);
		}
		vstr.push_back(gtl::move(s));
	}
	vstr.insert(vstr.begin() + 11, "aaaaa");
	vstr.insert(vstr.begin() + 13, "bbbbb");
	std::cout << "\nvstr content\n";
	print(vstr.begin(), vstr.end());
	

	std::cout << "\n";
	system("pause");
	return 0;
}