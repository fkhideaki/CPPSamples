#pragma once



namespace rbf
{


template<class T>
class ReverseAdapter
{
public:
	ReverseAdapter(T& container) :
		container(container)
	{}

	typename T::reverse_iterator begin()
	{
		return container.rbegin();
	}
	typename T::reverse_iterator end()
	{
		return container.rend();
	}

private:
	T& container;
};

template<class T>
class ConstReverseAdapter
{
public:
	ConstReverseAdapter(const T& container) :
		container(container)
	{}

	typename T::const_reverse_iterator begin()
	{
		return container.rbegin();
	}
	typename T::const_reverse_iterator end()
	{
		return container.rend();
	}

private:
	const T& container;
};

template<class T>
ReverseAdapter<T> Reverse(T& container)
{
	return ReverseAdapter<T>(container);
}

template<class T>
ConstReverseAdapter<T> Reverse(const T& container)
{
	return ConstReverseAdapter<T>(container);
}


}
