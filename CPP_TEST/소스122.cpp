#include <nlohmann/json.hpp>
#include <iostream>

using nlohmann::json;

/*
Arbitrary types conversions

Every type can be serialized in JSON, not just STL containers and scalar types.
Usually, you would do something along those lines:

*/
namespace ns {
	// a simple struct to model a person
	struct person {
		std::string name;
		std::string address;
		int age;
		
	};

	/*
	Basic usage
	To make this work with one of your types, you only need to provide two functions:
	*/
	void to_json(json& j, const person& p) {
		j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
	}

	void from_json(const json& j, person& p) {
		j.at("name").get_to(p.name);
		j.at("address").get_to(p.address);
		j.at("age").get_to(p.age);
	}
}

int main()
{
	ns::person p{ " Ned Flanders " , " 744 Evergreen Terrace " , 60 };
	
	json j = p;
	std::cout << j << std::endl;
	// { "address": "744 Evergreen Terrace", "age": 60, "name": "Ned Flanders"}
	// º¯È¯ :
	auto p2 = j.get <ns::person>();
	
	
	std::cout << p2.name << std::endl;
	std::cout << p2.address << std::endl;
	std::cout << p2.age << std::endl;
}