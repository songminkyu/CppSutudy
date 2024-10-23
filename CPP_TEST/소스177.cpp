#include <iostream>
#include <sstream>
#include <fstream>

/* Serialize a function by writing out a pointer to its location in memory.
 * This will only work between two processes running identical binaries.
 *
 * One difficulty is ASLR:
 * Address space layout randomization (ASLR) puts functions in a different
 * place in memory everytime a program is loaded. Within a given binary
 * though, the memory locations should be consistent. So, we actually
 * serialize the memory offset of the function from a baseline.
 *
 * compile with:
 * g++ -o crazy function_serialize.cpp --std=c++11
 *
 * Try:
 * ./crazy write
 * less data
 * ./crazy read
 */

void serialization_baseline() {
    std::cout << "BASELINE" << std::endl;
};
static auto baseline_loc = reinterpret_cast<intptr_t>(
    static_cast<void (*)()>(serialization_baseline)
    );

template <typename ResultT, typename... Args>
std::string serialize(ResultT(*f)(Args...))
{
    auto f_loc = reinterpret_cast<intptr_t>(f);
    auto offset = f_loc - baseline_loc;

    auto data = reinterpret_cast<const char*>(&offset);
    return std::string(data, sizeof(offset));
}

// Syntax for returning a function pointer from a function is really gross.
template <typename ResultT, typename... Args>
ResultT(*deserialize(std::string str))(Args...)
{
    auto offset = *reinterpret_cast<intptr_t*>(const_cast<char*>(str.c_str()));
    auto f_loc = baseline_loc + offset;
    return reinterpret_cast<ResultT(*)(Args...)>(f_loc);
}

void serialize_test()
{
    auto data = serialize(static_cast<int (*)(int)>(
        [](int a) {return a * 2; })
    );
   
    std::ofstream ofs("data");
    ofs << data;

}


void Deserialize_test()
{
    std::ifstream ifs("data");
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    auto f_deserialized = deserialize<int, int>(buffer.str());
    std::cout << "doubling with deserialized function pointer: 2 * 15 = "
        << f_deserialized(15) << std::endl;

}

int main(int argc, char** argv)
{
#if false
    if (std::string(argv[1]) == "write") {
        auto data = serialize(static_cast<int (*)(int)>(
            [](int a) {return a * 2; })
        );
        std::ofstream f("data");
        f << data;
    }
    else if (std::string(argv[1]) == "read") {
        std::ifstream f("data");
        std::stringstream buffer;
        buffer << f.rdbuf();
        auto f_deserialized = deserialize<int, int>(buffer.str());
        std::cout << "doubling with deserialized function pointer: 2 * 15 = "
            << f_deserialized(15) << std::endl;
    }
#else
    serialize_test();
    Deserialize_test();      
#endif
}