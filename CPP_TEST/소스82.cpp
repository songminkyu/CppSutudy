// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <type_traits>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>


template<class BidirectionalIterator>
void evolve(BidirectionalIterator first, BidirectionalIterator last,
	std::bidirectional_iterator_tag) {
	// more generic, but less efficient algorithm

	std::cout << "BidirectionalIterator" << std::endl;
}

template<class RandomAccessIterator>
void evolve(RandomAccessIterator first, RandomAccessIterator last,
	std::random_access_iterator_tag) {
	// more efficient, but less generic algorithm

	std::cout << "RandomAccessIterator" << std::endl;
}

template<class Iterator>
inline void
evolve(Iterator first, Iterator last) {
	evolve(first, last, typename std::iterator_traits<Iterator>::iterator_category());
}

int main()
{
	std::vector<int> v;
	evolve(v.begin(), v.end());

	std::list<int> l;
	evolve(l.begin(), l.end());

	std::deque<int> d;
	evolve(d.begin(), d.end());
	
	std::map<int, char> m;
	evolve(m.begin(), m.end());
	

	std::set<int, char> s;
	evolve(s.begin(), s.end());
	
}
