#include <sstream>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>

template <class T, class... Ts>
void print_all(std::ostream& os, T const& first, Ts const&... rest) {
    os << first;

    if constexpr (sizeof...(rest) > 0) {
        // this line will only be instantiated if there are further
        // arguments. if rest... is empty, there will be no call to
        // print_all(os). 
        print_all(os, rest...);
    }
}

int main()
{
    std::ostringstream o;
    print_all(o ,1, 2, "buckle my shoe", 3, 4);


    std::cout << o.str() << std::endl;
}
