
#include "StaticOperatorFunctions.h"
#include <chrono>
#include <random>

#pragma warning(disable:26451)

template <typename... Seqs>
static detail::seq<typename detail::zip_iterator<typename Seqs::const_iterator...>>
multi_zip_range(const Seqs&... seqs)
{
	return detail::seq<typename detail::zip_iterator<typename Seqs::const_iterator...>>(
		detail::zip_iterator<typename Seqs::const_iterator...>(std::begin(seqs)...),
		detail::zip_iterator<typename Seqs::const_iterator...>(std::end(seqs)...));
}

int Generator(int low, int high)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> ndis(low, high);
	return ndis(gen);
}

std::vector<int> RandomVectorInt(int size, int low, int high)
{
	std::vector<int> v;
	for (int i = 0; i < size; i++)
	{
		v.push_back(Generator(low, high));
	}
	return v;
}


void bubbleSort(std::vector<int>& arr) {
	int temp;
	int n = arr.size();

	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - 1 - i; ++j) {
			if (arr[j] > arr[j + 1]) {		

				std::cout << "asd" << std::endl;
				//swap if found bigger
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;				
			}
		}
	}
}

template <typename T>
void QuickSort(std::vector<T>& a, int left, int right)
{
	int index;
	if (left < right)
	{
		T pivot = a[right];
		int i = left - 1;
		for (int j = left; j <= right - 1; j++)
		{
			if (a[j] < pivot)
			{				
				i++;
				std::swap(a[i], a[j]);
			}			
		}
		std::swap(a[i + 1], a[right]);
		index = i + 1;
		QuickSort(a, left, index - 1);
		QuickSort(a, index + 1, right);
	}
}



template <typename T>
void Merge(std::vector<T>& a, int left, int middle, int right)
{
	int s1 = middle - left + 1;
	int s2 = right - middle;
	std::vector<T> temp1(s1);
	std::vector<T> temp2(s2);
	for (int i = 0; i < s1; i++)
	{
		temp1[i] = a[left + i];
	}
	for (int i = 0; i < s2; i++)
	{
		temp2[i] = a[middle + 1 + i];
	}
	int index = left, i = 0, j = 0;
	while (i < s1 && j < s2)
	{
		if (temp1[i] <= temp2[j])
		{
			a[index] = temp1[i];
			i++;
		}
		else
		{
			a[index] = temp2[j];
			j++;
		}
		index++;
	}
	while (i < s1)
	{
		a[index] = temp1[i];
		index++;
		i++;
	}
	while (j < s2)
	{
		a[index] = temp2[j];
		index++;
		j++;
	}
}

template <typename T>
void MergeSort(std::vector<T>& a, int left, int right)
{
	if (left < right)
	{		
		int middle = left + (right - left) / 2;
		MergeSort(a, left, middle);
		MergeSort(a, middle + 1, right);
		Merge(a, left, middle, right);		
	}
}

void selectionSort(std::vector<int>& arr) {
	int temp;
	int el;
	int n = arr.size();

	for (int i = 0; i < n - 1; ++i)
	{
		el = i;
		for (int j = i + 1; j < n; ++j) {
			if (arr[j] < arr[el]) {
				std::cout << "asdasd" << std::endl;
				el = j;				
			}
		}

		//swap elements
		temp = arr[el];
		arr[el] = arr[i];
		arr[i] = temp;
	}
}

int minimumSwaps(std::vector<int>& arr) {
	int count = 0;
	for (int i = 0; i < arr.size() - 1; i++) {
		if (arr[i] == i + 1) continue;
		count++;
		int tmp = arr[i];
		arr[i] = arr[tmp - 1];
		arr[tmp - 1] = tmp;
		i--;
	}
	return count;
}

void multi_zip_range_test()
{
	std::vector<int> a{ 1,2,3,4 };
	std::vector<int> b{ 7,8,9,0 };

	for (auto [_a, _b] : multi_zip_range(a, b))
	{
		std::cout << _a << " " << _b << std::endl;
	}
}

void sorting_test()
{

	std::vector<int> a{ 7,1,3,4,5,6,2,8,10,9 };
	std::vector<int> arr(10);
	for (int i = 0; i < 10; i++) {
		arr[i] = a[i];
	}

	auto start = std::chrono::system_clock::now();			
	
	int res = minimumSwaps(arr);	
	auto end = std::chrono::system_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);	
	//std::cout << time.count() << std::endl;

	for (auto&& i : arr)
	{
		std::cout << i << std::endl;
	}
	//std::cout << r << std::endl;
}
int main()
{
	sorting_test();
}