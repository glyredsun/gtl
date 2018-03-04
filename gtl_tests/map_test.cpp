#include <map.hpp>

#include <string.hpp>

int main(void)
{
	gtl::map<gtl::string, gtl::string> m;

	m["abc"] = "def";
	m["asdfasdfaf"] = "def";
	m["143dsf"] = "2i3e";
	m["25315131"] = "2odkkasdf";
	m["z3taedfadsf"] = "f23w312";
	m["123"] = "456";
	m["abc"] = "111";

	for (gtl::map<gtl::string, gtl::string>::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
		std::cout << itr->first << " : " <<  itr->second << std::endl;
	}
	
	system("pause");
	return 0;
}