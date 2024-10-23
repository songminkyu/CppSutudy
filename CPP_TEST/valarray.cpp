#include <iostream>
#include <valarray>

void valarray_test_1()
{
	std::valarray<char> v0("songminkyu", 11);
	std::valarray<char> v1("ABCDE", 5);

	v0[std::slice(1, 2, 3)] = v1;

	for (auto && item : v0)
	{
		std::cout << item;
	}
}

void valarray_test_2()
{
	std::size_t addr[] = { 2,3,7,4,5 };
	std::valarray<size_t> indirect(addr, 5);
	std::valarray<double> a(0., 10), b(1., 5);

	a[indirect] = b;

	for (auto && item : a)
	{
		std::cout << item << ' ';
	}
}

void valarray_test_3()
{
	std::valarray<int> sample(12);
	// initialising valarray 
	for (int i = 0; i < 13; ++i)
		sample[i] = i;

	for (auto&& item : sample)
	{
		std::cout << item << ' ';
	}


	// using slice from start 1 and size 3 and stride 4 
	std::valarray<int> bar = sample[std::slice(2, 3, 4)];

	// display slice result 
	std::cout << "slice(2, 3, 4):";
	for (std::size_t n = 0; n < bar.size(); n++)
		std::cout << ' ' << bar[n];
	std::cout << '\n';

}
void valarray_test_4()
{
	// row and column of matrix 
	int row = 3, col = 3;

	// matrix of size row*col in row major form. 
	std::valarray<int> matrix(row * col);

	// initialising matrix 
	for (int i = 0; i < row * col; ++i)
		matrix[i] = i + 1;

	// using slice from start 0 with size as col and stride col+1 
	std::valarray<int> diagonal = matrix[std::slice(0, col, col + 1)];

	// finding trace using diagonal we got using slice 
	int index = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			std::cout << matrix[index++] << " "; // same as matrix[i][j] 
		std::cout << std::endl;
	}

	int sum = 0; // initialising sum as 0 
	// calculating trace of matrix 
	for (int i = 0; i < diagonal.size(); i++)
		sum += diagonal[i];
	std::cout << "Trace of matrix is : ";
	std::cout << sum << std::endl; // sum is trace of matrix 	
}

int main()
{
	valarray_test_3();
	//valarray_test_2();
}