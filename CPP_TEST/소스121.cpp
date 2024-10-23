#include <nlohmann/json.hpp>
#include <iostream>
using namespace nlohmann;

/*
JSON Pointer and JSON Patch

The library supports JSON Pointer (RFC 6901) as alternative means to address structured values.
On top of this, JSON Patch (RFC 6902) allows to describe differences between two JSON 
values - effectively allowing patch and diff operations known from Unix.
*/
int main()
{
	// a JSON value
	json j_original = R"({
  "baz": ["one", "two", "three"],
  "foo": "bar"
})"_json;

	// access members with a JSON pointer (RFC 6901)
	j_original["/baz/1"_json_pointer];
	// "two"

	// a JSON patch (RFC 6902)
	json j_patch = R"([
  { "op": "replace", "path": "/baz", "value": "boo" },
  { "op": "add", "path": "/hello", "value": ["world"] },
  { "op": "remove", "path": "/foo"}
])"_json;

	// apply the patch
	json j_result = j_original.patch(j_patch);
	// {
	//    "baz": "boo",
	//    "hello": ["world"]
	// }

	// calculate a JSON patch from two JSON values
	json::diff(j_result, j_original);
	// [
	//   { "op":" replace", "path": "/baz", "value": ["one", "two", "three"] },
	//   { "op": "remove","path": "/hello" },
	//   { "op": "add", "path": "/foo", "value": "bar" }
	// ]
}