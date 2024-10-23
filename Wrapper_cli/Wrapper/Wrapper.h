#pragma once
using namespace System;
namespace Wrapper {


	template<typename Elem>
	public class MyArithmetic_T
	{
	public:				
		Elem Add_T(Elem a, Elem b);				
		Elem Subtract_T(Elem a, Elem b);				
		Elem Multiply_T(Elem a, Elem b);			
		Elem Divide_T(Elem a, Elem b);		
	};

	public ref class MyArithmetic
	{
	public:					
		int Add(int a, int b);
		int Subtract(int a, int b);
		int Multiply(int a, int b);
		int Divide(int a, int b);
	public:
		MyArithmetic_T<int> *m;
			
	};	
}
