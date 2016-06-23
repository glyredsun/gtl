#include <map.hpp>

#include <map>
#include <string>

int main(void)
{
	gtl::map<std::string, std::string> m;

	m["abc"] = "def";
	m["123"] = "456";
	m["asdfasdfaf"] = "def";

	for (gtl::map<std::string, std::string>::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
		std::cout << itr->first << " : " <<  itr->second << std::endl;
	}
	
	system("pause");
	return 0;
}