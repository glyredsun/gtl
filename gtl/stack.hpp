#include <macros.hpp>

NS_BEGIN(gtl)

template<typename T>
class stack
{
public:

	stack(int capacity)
		: _capacity(capacity)
	{
		if (_capacity > 0) {
			_datas = new T[_capacity];
		}
	}

	

	~stack()
	{
		if (_data) {
			delete[] _datas;
		}
	}



	void push(const T &data) {
		++_size;
		if (_size > _capacity) {

		}
	}

	T& top() {
		return _data[_size];
	}

	const T& top() const {
		return _datas[_size];
	}

private:
	int _capacity;
	int _size;
	T* _datas;
};

NS_END(gtl)