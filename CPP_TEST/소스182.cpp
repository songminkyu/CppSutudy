#include <iostream>
#include <variant>
#include <vector>

int main() {
    std::variant<std::string, std::vector<int>> dat{        
        std::in_place_type_t<std::vector<int>>{},
        {1,2,3,4,5,6,7,8,9,10}
    };   
    for (auto&& mitem : get<1>(dat)) {
        std::cout << mitem;
    } 
}
