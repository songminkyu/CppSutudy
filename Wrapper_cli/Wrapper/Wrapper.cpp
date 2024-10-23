#include "pch.h"
#include "Wrapper.h"
namespace Wrapper
{
	template<typename Elem>
	inline Elem MyArithmetic_T<Elem>::Add_T(Elem a, Elem b)
	{
		return a + b;
	}
	template<typename Elem>
	inline Elem MyArithmetic_T<Elem>::Subtract_T(Elem a, Elem b)
	{
		return a - b;
	}
	template<typename Elem>
	inline Elem MyArithmetic_T<Elem>::Multiply_T(Elem a, Elem b)
	{
		return a * b;
	}
	template<typename Elem>
	inline Elem MyArithmetic_T<Elem>::Divide_T(Elem a, Elem b)
	{
		return a / b;
	}


	int MyArithmetic::Add(int a, int b)
	{						
		return m->Add_T(a,b);
	}
	int MyArithmetic::Subtract(int a, int b)
	{
		return m->Subtract_T(a, b);
	}
	int MyArithmetic::Multiply(int a, int b)
	{
		return  m->Multiply_T(a, b);
	}
	int MyArithmetic::Divide(int a, int b)
	{
		return m->Divide_T(a, b);
	}
}