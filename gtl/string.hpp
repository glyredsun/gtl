#include <macros.hpp>
#include <vector.hpp>

#include <ostream>
#include <cstring>

GTL_BEGIN_NS

template <class CharType, class BaseType = vector<CharType>>
class basic_string : public BaseType
{
public:

	typedef typename BaseType::size_type size_type;
	typedef typename BaseType::value_type value_type;
	typedef typename BaseType::pointer pointer;
	typedef typename BaseType::const_pointer const_pointer;
	typedef typename BaseType::reference reference;
	typedef typename BaseType::const_reference const_reference;
	typedef typename BaseType::rvalue_reference rvalue_reference;
	typedef typename BaseType::iterator iterator;
	typedef typename BaseType::const_iterator const_iterator;
	typedef typename BaseType::const_reverse_iterator const_reverse_iterator;
	typedef typename BaseType::reverse_iterator reverse_iterator;
	
	basic_string() {}

	basic_string(const value_type* cstr)
		: BaseType(cstr, cstr + strlen(cstr))
	{

	}
	
	basic_string(value_type ch)
		: BaseType(&ch, &ch + 1)
	{

	}

	const_iterator append(const value_type* cstr)
	{
		return insert(end(), cstr, cstr + strlen(cstr));
	}
};

typedef basic_string<char> string;

template <class CharType, class BaseType>
std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& o, const basic_string<CharType, BaseType>& s)
{
	return o.write(s.begin(), s.size());
}

GTL_END_NS