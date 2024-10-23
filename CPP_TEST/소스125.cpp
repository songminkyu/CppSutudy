#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>

using nlohmann::json;

std::string binary_to_string(const std::vector<uint8_t>& source)
{
	static char syms[] = "0123456789ABCDEF";
	std::stringstream ss;
	for (std::vector<unsigned char>::const_iterator it = source.begin(); it != source.end(); it++)
		ss << syms[((*it >> 4) & 0xf)] << syms[*it & 0xf];

	return ss.str();
}
std::vector<unsigned char> string_to_binary(const std::string& source)
{
	static int nibbles[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15 };
	std::vector<unsigned char> retval;
	for (std::string::const_iterator it = source.begin(); it < source.end(); it += 2) {
		unsigned char v = 0;
		if (std::isxdigit(*it))
			v = nibbles[std::toupper(*it) - '0'] << 4;
		if (it + 1 < source.end() && std::isxdigit(*(it + 1)))
			v += nibbles[std::toupper(*(it + 1)) - '0'];
		retval.push_back(v);
	}
	return retval;
}

void binary_json_test1()
{
	/*

	Binary formats (BSON, CBOR, MessagePack, and UBJSON)
	Though JSON is a ubiquitous data format, it is not a very compact format suitable for data exchange, 
	for instance over a network. Hence, the library supports BSON (Binary JSON), CBOR (Concise Binary Object Representation), 
	MessagePack, and UBJSON (Universal Binary JSON Specification) to efficiently encode JSON values to byte vectors and to 
	decode such vectors.	

	*/

	// create a JSON value
	json j = R"({"compact": true, "schema": 0})"_json;

	// serialize to BSON
	std::vector<std::uint8_t> v_bson = json::to_bson(j);

	// 0x1B, 0x00, 0x00, 0x00, 0x08, 0x63, 0x6F, 0x6D, 0x70, 0x61, 0x63, 0x74, 0x00, 0x01, 0x10, 0x73, 0x63, 0x68, 0x65, 0x6D, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	// roundtrip
	json j_from_bson = json::from_bson(v_bson);

	// serialize to CBOR
	std::vector<std::uint8_t> v_cbor = json::to_cbor(j);

	// 0xA2, 0x67, 0x63, 0x6F, 0x6D, 0x70, 0x61, 0x63, 0x74, 0xF5, 0x66, 0x73, 0x63, 0x68, 0x65, 0x6D, 0x61, 0x00

	// roundtrip
	json j_from_cbor = json::from_cbor(v_cbor);

	// serialize to MessagePack
	std::vector<std::uint8_t> v_msgpack = json::to_msgpack(j);

	// 0x82, 0xA7, 0x63, 0x6F, 0x6D, 0x70, 0x61, 0x63, 0x74, 0xC3, 0xA6, 0x73, 0x63, 0x68, 0x65, 0x6D, 0x61, 0x00

	// roundtrip
	json j_from_msgpack = json::from_msgpack(v_msgpack);

	// serialize to UBJSON
	std::vector<std::uint8_t> v_ubjson = json::to_ubjson(j);

	// 0x7B, 0x69, 0x07, 0x63, 0x6F, 0x6D, 0x70, 0x61, 0x63, 0x74, 0x54, 0x69, 0x06, 0x73, 0x63, 0x68, 0x65, 0x6D, 0x61, 0x69, 0x00, 0x7D

	// roundtrip
	json j_from_ubjson = json::from_ubjson(v_ubjson);

	std::cout << j_from_ubjson.dump() << std::endl;
}

void binary_json_test2()
{

	/*
	The library also supports binary types from BSON, CBOR (byte strings), 
	and MessagePack (bin, ext, fixext). They are stored by default as std::vector<std::uint8_t> 
	to be processed outside of the library.
	*/
	std::vector<std::uint8_t> v = { 0x42, 0xCA, 0xFE };

	// read value
	json j = json::from_cbor(v);

	// the JSON value has type binary
	j.is_binary(); // true

	// get reference to stored binary value
	auto& binary = j.get_binary();

	// the binary value has no subtype (CBOR has no binary subtypes)
	binary.has_subtype(); // false

	// access std::vector<std::uint8_t> member functions
	std::cout << binary.size() << std::endl; // 2
	std::cout << binary[0] << std::endl; // 0xCA
	std::cout << binary[1] << std::endl; // 0xFE
	// set subtype to 0x10
	binary.set_subtype(0x10);

	// serialize to MessagePack
	auto cbor = json::to_msgpack(j); // 0xD5 (fixext2), 0x10, 0xCA, 0xFE

	std::string str = binary_to_string(cbor);

	std::cout << str << std::endl;

}
int main()
{
	
	binary_json_test1();
	binary_json_test2();


}