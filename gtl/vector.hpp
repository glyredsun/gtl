#include <macros.hpp>
#include <algorithm.hpp>

NS_BEGIN(gtl)

template<typename T>
class vector
{
public:
	vector(size_t initSize)
		: _size{ initSize }
		, _capacity{ initSize + SPARE_SIZE }
	{
		_datas = new T[_capacity];
	}

	~vector()
	{
		if (_datas)
			delete[] _datas;
	}

	vector(const vector& other)
		: _size{ other._size }
		, _capacity{ other._capacity }
	{
		_datas = new T[_capacity];
		for (size_t i = 0; i < _size; i++)
		{
			_datas[i] = other._datas[i];
		}
	}

	vector(vector&& other)
		: _size{ other._size }
		, _capacity{ other._size }
		, _datas{ other._datas }
	{
		other._capacity = 0;
		other._size = 0;
		other._datas = nullptr;
	}

	vector& operator=(const vector& other)
	{
		if (this != &other) {
			vector copy = other;
			std::swap(*this, copy);
		}
		return *this;
	}

	vector& operator=(vector&& other)
	{
		if (this != &other) {
			swap(this->_size, other._size);
			swap(this->_capacity, other._capacity);
			swap(this->_datas, other._datas);
		}
		return *this;
	}

	T& operator[](size_t idx) {
		assert(idx < _size, "out of range");
		return _datas[idx];
	}

	const T& operator[](size_t idx) const {
		assert(idx < _size, "out of range");
		return _datas[idx];
	}

	void resize(size_t newSize) {

	}

	void reserve(size_t capacity) {
		if (_capacity >)
	}

private:
	static const size_t SPARE_SIZE = 16;
	size_t _capacity;
	size_t _size;
	T *_datas;
};

NS_END(gtl)