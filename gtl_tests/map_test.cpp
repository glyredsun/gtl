#include <map.hpp>

#include <string.hpp>

int main(void)
{
	gtl::map<gtl::string, gtl::string> m;

	m["abc"] = "def";
	m["123"] = "456";
	m["asdfasdfaf"] = "def";

	for (gtl::map<gtl::string, gtl::string>::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
		std::cout << itr->first << " : " <<  itr->second << std::endl;
	}
	
	system("pause");
	return 0;
}