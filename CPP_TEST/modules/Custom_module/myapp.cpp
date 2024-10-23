import util;

/*
모듈 만드는 방법

https://devblogs.microsoft.com/cppblog/cpp-modules-in-visual-studio-2017/

자세한 내용은 Advenced_module 내 소스 참조
cl /EHsc /std:c++latest /MD /c /experimental:module cst_mdl.ixx

cl /EHsc /std:c++latest /MD /experimental:module /module:reference util.ifc cst_mdl.obj myapp.cpp

*/
int main()
{
	std::cout << "sum from 1 to 10 is " <<
		sum(1, 2, 3, 4, 5, 6, 7, 8, 10)
		<< std::endl;

	return 0;
}