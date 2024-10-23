import tpf.vctr;

/*

module 만드는 방법

1. x64 Native Tools command prompt for vs 2019 오픈

2. my_vctr.ixx 있는곳으로 이동

3. cl /EHsc /std:c++latest /MD /c /experimental:module my_vctr.ixx 

4. cl /EHsc /std:c++latest /MD /experimental:module /module:reference tpf.vctr.ifc my_vctr.obj main.cpp 

*/
int main()
{
	tpf::vctr v1{ 1,2,3 };
	tpf::vctr v2{ 3,2,1 };

	std::cout << v1 << "+" << v2 << std::endl;
	std::cout << v1 + v2 << std::endl;

	
	std::vector<int> devector;
	devector.push_back(10);
	devector.push_back(11);
	devector.push_back(12);

	for (auto&& item : devector)
	{
		printf("%d \n", item);
	}

	return 0;
}