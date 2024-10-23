#include <nlohmann/json.hpp>
#include <iostream>
#include <set>
#include <unordered_set>
#include <deque>
using namespace nlohmann;

/*
Conversion from STL containers

Any sequence container (std::array, std::vector, std::deque, std::forward_list, std::list) 
whose values can be used to construct JSON values (e.g., integers, floating point numbers, 
Booleans, string types, or again STL containers described in this section) can be used to 
create a JSON array. 
The same holds for similar associative containers (std::set, std::multiset, std::unordered_set, 
std::unordered_multiset), but in these cases the order of the elements of the array depends on 
how the elements are ordered in the respective STL container.

*/
int main()
{
	std::vector<int> c_vector{ 1, 2, 3, 4 };
	json j_vec(c_vector);
	// [1, 2, 3, 4]

	std::deque<double> c_deque{ 1.2, 2.3, 3.4, 5.6 };
	json j_deque(c_deque);
	// [1.2, 2.3, 3.4, 5.6]

	std::list<bool> c_list{ true, true, false, true };
	json j_list(c_list);
	// [true, true, false, true]

	std::forward_list<int64_t> c_flist{ 12345678909876, 23456789098765, 34567890987654, 45678909876543 };
	json j_flist(c_flist);
	// [12345678909876, 23456789098765, 34567890987654, 45678909876543]

	std::array<unsigned long, 4> c_array{ {1, 2, 3, 4} };
	json j_array(c_array);
	// [1, 2, 3, 4]

	std::set<std::string> c_set{ "one", "two", "three", "four", "one" };
	json j_set(c_set); // only one entry for "one" is used
	// ["four", "one", "three", "two"]

	std::unordered_set<std::string> c_uset{ "one", "two", "three", "four", "one" };
	json j_uset(c_uset); // only one entry for "one" is used
	// maybe ["two", "three", "four", "one"]

	std::multiset<std::string> c_mset{ "one", "two", "one", "four" };
	json j_mset(c_mset); // both entries for "one" are used
	// maybe ["one", "two", "one", "four"]

	std::unordered_multiset<std::string> c_umset{ "one", "two", "one", "four" };
	json j_umset(c_umset); // both entries for "one" are used
	// maybe ["one", "two", "one", "four"]
	
	
	
	
	/*
	Likewise, any associative key - value containers(std::map, std::multimap, 
	std::unordered_map, std::unordered_multimap) whose keys can construct 
	an std::string and whose values can be used to construct JSON values
	(see examples above) can be used to create a JSON object.Note that in case 
	of multimaps only one key is used in the JSON objectand the value depends 
	on the internal order of the STL container.
	*/
	std::map<std::string, int> c_map{ {"one", 1}, {"two", 2}, {"three", 3} };
	json j_map(c_map);
	// {"one": 1, "three": 3, "two": 2 }

	std::unordered_map<const char*, double> c_umap{ {"one", 1.2}, {"two", 2.3}, {"three", 3.4} };
	json j_umap(c_umap);
	// {"one": 1.2, "two": 2.3, "three": 3.4}

	std::multimap<std::string, bool> c_mmap{ {"one", true}, {"two", true}, {"three", false}, {"three", true} };
	json j_mmap(c_mmap); // only one entry for key "three" is used
	// maybe {"one": true, "two": true, "three": true}

	std::unordered_multimap<std::string, bool> c_ummap{ {"one", true}, {"two", true}, {"three", false}, {"three", true} };
	json j_ummap(c_ummap); // only one entry for key "three" is used
	// maybe {"one": true, "two": true, "three": true}

}