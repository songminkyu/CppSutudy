#include <iostream>
#include <string>
#include <type_traits>


template<class, std::size_t...>
struct add_extent;

template<class T, std::size_t N>
struct add_extent<T, N> { using type = T[N]; };

template<class T, std::size_t N1, std::size_t N2>
struct add_extent<T, N1, N2> { using type = typename add_extent<T, N2>::type[N1]; };


template<class T, std::size_t N1, std::size_t N2, std::size_t... Ns>
struct add_extent<T, N1, N2, Ns...> {
    using type = typename add_extent<typename add_extent<T, Ns...>::type, N1,N2>::type;

};


int main() {
    static_assert(std::is_same< add_extent<std::string, 10, 20, 30, 40>::type, std::string[10][20][30][40] >{});
    
    add_extent<std::string*, 10, 20, 30, 40>::type strstr;
    strstr[0][0][0][1] = new std::string();
    *strstr[0][0][0][1] = "aasdasd";
    std::cout << strstr[0][0][0][1]->c_str() << std::endl;

    add_extent<std::string, 10, 20, 30, 40>::type *strstr2;
    strstr2 = new std::string[10][10][20][30][40];
    strstr2[0][0][0][0][1] = "songong";
    std::cout << strstr2[0][0][0][0][1] << std::endl;
}