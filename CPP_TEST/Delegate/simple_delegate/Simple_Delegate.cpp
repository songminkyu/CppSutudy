
#include <list>
#include <functional>
#include <iostream>


template <class T> class Delegate;
template <class R, class... ARGS>
class Delegate<R(ARGS...)>
{
protected:
	std::list<std::function<R(ARGS...)>> funcs;
public:
	using iterator = typename std::list<std::function<R(ARGS...)>>::iterator;

	R operator () (const ARGS... args)
	{
		R result;
		for (auto func : funcs)
		{
			result = func(args...);
		}
		return result;
	}

	Delegate<R(ARGS...)>& operator += (std::function<R(ARGS...)> const& arg)
	{
		funcs.push_back(arg);
		return *this;
	}

	Delegate<R(ARGS...)>& operator -= (std::function<R(ARGS...)> const& arg)
	{
		R(* const* ptr)(ARGS...) = arg.template target<R(*)(ARGS...)>();
		if (nullptr == ptr)
		{
			return *this;
		}

		for (auto itr = funcs.begin(); itr != funcs.end(); itr++)
		{
			R(* const* delegate_ptr)(ARGS...) = (*itr).template target<R(*)(ARGS...)>();
			if (nullptr != delegate_ptr && *ptr == *delegate_ptr)
			{
				funcs.erase(itr);
				return *this;
			}
		}

		return *this;
	}

	iterator begin() noexcept
	{
		return funcs.begin();
	}
	iterator end() noexcept
	{
		return funcs.end();
	}
	void clear()
	{
		funcs.clear();
	}
};

template <class... ARGS>
class Delegate<void(ARGS...)>
{
	std::list<std::function<void(ARGS...)>> funcs;
public:
	using iterator = typename std::list<std::function<void(ARGS...)>>::iterator;

	void operator () (const ARGS... args)
	{
		for (auto func : funcs)
		{
			func(args...);
		}
	}

	Delegate<void(ARGS...)>& operator += (std::function<void(ARGS...)> const& arg)
	{
		funcs.push_back(arg);
		return *this;
	}

	Delegate<void(ARGS...)>& operator -= (std::function<void(ARGS...)> const& arg)
	{
		void (* const* ptr)(ARGS...) = arg.template target<void(*)(ARGS...)>();
		if (nullptr == ptr)
		{
			return *this;
		}

		for (auto itr = funcs.begin(); itr != funcs.end(); itr++)
		{
			void (* const* delegate_ptr)(ARGS...) = (*itr).template target<void(*)(ARGS...)>();
			if (nullptr != delegate_ptr && *ptr == *delegate_ptr)
			{
				funcs.erase(itr);
				return *this;
			}
		}

		return *this;
	}

	iterator begin() noexcept
	{
		return funcs.begin();
	}
	iterator end() noexcept
	{
		return funcs.end();
	}
	void clear()
	{
		funcs.clear();
	}
};

int f_1(int a, int b) { return a + b; }
int g_1(int a, int b){ return a - b; }

void f_2(int a, int b) { std::cout << a + b << std::endl; }

void g_2(int a, int b){ std::cout << a - b << std::endl; }

int main()
{

	Delegate<int(int, int)> delegate_1;
	delegate_1 += f_1;
	delegate_1 += g_1;
	std::cout << delegate_1(100, 10) << std::endl; // print 90 only
	for (auto itr = delegate_1.begin(); itr != delegate_1.end(); itr++)
	{
		std::cout << (*itr)(100, 10) << std::endl; // print 110 and 90
	}

	Delegate<void(int, int)> delegate_2;
	delegate_2 += f_2;
	delegate_2 += g_2;	
	delegate_2(100, 10); // print 110 and 90

	return 0;

}
