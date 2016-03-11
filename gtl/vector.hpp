#include <macros.hpp>
#include <algorithm>

NS_BEGIN(gtl)

template<typename T>
class vector
{
public:
	vector(size_t initSize = 0)
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
			vector copy(other);
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
		return _datas[idx];
	}

	const T& operator[](size_t idx) const {
		return _datas[idx];
	}

	void resize(size_t newSize) {
		if (newSize > _capacity) {
			reserve(newSize * 2);
		}
		_size = newSize;
	}

	void reserve(size_t newCapacity) {
		if (newCapacity <= _size) {
			return;
		}

		T *newDatas = new T[newCapacity];

		for (size_t i = 0; i < _size; i++)
		{
			newDatas[i] = std::move(_datas[i]);
		}

		_capacity = newCapacity;
		delete[] _datas;
		_datas = newDatas;
	}

	void push_back(T&& data) {
		resize(_size + 1);
		_datas[_size - 1] = data;
	}

	void push_back(const T& data) {
		T copy = data;
		push_back(std::move(copy));
	}

public:
	class iterator
	{
	public:
		iterator(vector &v, size_t idx)
			: vectPtr(&v), idx(idx)
		{

		}

		iterator operator ++(int)
		{
			iterator copy = *this;
			++idx;
			return copy;
		}

		iterator& operator ++()
		{
			++idx;
			return *this;
		}

		iterator& operator =(const iterator& other)
		{
			if (&other !== this)
			{
				this->vectPtr = other.vectPtr;
				this->idx = other.idx;
			}
			return *this;
		}

		T& operator ->()
		{
			return (*vectPtr)[idx];
		}

		const T& operator ->() const
		{
			return (*vectPtr)[idx];
		}

		T& operator*()
		{
			return (*vectPtr)[idx];
		}

		bool operator == (const iterator& other)
		{
			if (&other == this)
			{
				return true;
			}
			return vectPtr == other.vectPtr && idx == other.idx;
		}

		bool operator != (const iterator &other)
		{
			return !(*this == other);
		}

	private:
		vector *vectPtr;
		size_t idx;
	};

public:

	iterator begin()
	{
		return iterator(*this, 0);
	}

	iterator end()
	{
		return iterator(*this, _size);
	}

private:
	static const size_t SPARE_SIZE = 16;
	size_t _capacity;
	size_t _size;
	T *_datas;
};

NS_END(gtl)