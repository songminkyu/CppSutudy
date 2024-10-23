#include <nlohmann/json.hpp>
#include <iostream>
#include <boost\optional\optional.hpp>

using nlohmann::json;


class address {
public:
    std::string street;
    int housenumber;
    int postcode;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(address, street, housenumber, postcode)
};

struct move_only_type {
    move_only_type() = delete;
    move_only_type(int ii) : i(ii) {}
    move_only_type(const move_only_type&) = delete;
    move_only_type(move_only_type&&) = default;
    int i;
};

namespace nlohmann {
    template <typename T>
    struct adl_serializer<boost::optional<T>> {

        static void to_json(json& j, const boost::optional<T>& opt) {
            if (opt == boost::none) {
                j = nullptr;
            }
            else {
                j = *opt; // this will call adl_serializer<T>::to_json which will
                          // find the free function to_json in T's namespace!
            }
        }

        static void from_json(const json& j, boost::optional<T>& opt) {
            if (j.is_null()) {
                opt = boost::none;
            }
            else {
                opt = j.get<T>(); // same as above, but with
                                  // adl_serializer<T>::from_json
            }
        }
    };

    template <>
    struct adl_serializer<move_only_type> {
        // note: the return type is no longer 'void', and the method only takes
        // one argument
        static move_only_type from_json(const json& j) {
            return { j.get<int>() };
        }

        // Here's the catch! You must provide a to_json method! Otherwise you
        // will not be able to convert move_only_type to json, since you fully
        // specialized adl_serializer on that type
        static void to_json(json& j, move_only_type t) {
            j = t.i;
        }
    };


    template<typename T, typename SFINAE = typename std::enable_if<sizeof(T) <= 32>::type>
    struct less_than_32_serializer {
        template <typename BasicJsonType>
        static void to_json(BasicJsonType& j, T value) {
            // we want to use ADL, and call the correct to_json overload
            using nlohmann::to_json; // this method is called by adl_serializer,
                                     // this is where the magic happens
            to_json(j, value);
        }

        template <typename BasicJsonType>
        static void from_json(const BasicJsonType& j, T& value) {
            // same thing here
            using nlohmann::from_json;
            from_json(j, value);
        }
    };

    template <typename T, typename Tv = void>
    struct bad_serializer
    {
        template <typename BasicJsonType>
        static void to_json(BasicJsonType& j, const T& value) {
            // this calls BasicJsonType::json_serializer<T>::to_json(j, value);
            // if BasicJsonType::json_serializer == bad_serializer ... oops!
            j = value;
        }

        template <typename BasicJsonType>
        static void to_json(const BasicJsonType& j, T& value) {
            // this calls BasicJsonType::json_serializer<T>::from_json(j, value);
            // if BasicJsonType::json_serializer == bad_serializer ... oops!
            value = j.template get<T>(); // oops!
        }
    };

}
int main()
{
    json j;

    address to_addr;
    to_addr.street = "954 - 20 Bongcheon - dong, Gwanak - gu, Seoul";
    to_addr.postcode = 84520;
    to_addr.housenumber = 9660;

    nlohmann::adl_serializer<boost::optional<address>>::to_json(j, to_addr);
     
    boost::optional<address> from_addr;
    nlohmann::adl_serializer<boost::optional<address>>::from_json(j, from_addr);
  
    std::cout << from_addr.get().street << std::endl;
    std::cout << from_addr.get().postcode << std::endl;
    std::cout << from_addr.get().housenumber << std::endl;
}