#include <iostream>

/*
Cute C++ trick of the day: Need to represent multiple variadic parameter 
packs in a function signature? You can (and maybe should) just use std::tuple, 
but here's another cute idiom for this: https://godbolt.org/z/cdbeGd

(Caveat: perfect forwarding with this is harder than it looks.)
*/


template <class Pack1, class Pack2, class Pack3>
void foo(Pack1 p1, Pack2 p2, Pack3 p3) {
    p1([&](auto... p1_args) {
        p2([&](auto... p2_args) {
            p3([&](auto... p3_args) {

                std::cout << "Pack 1 Args:";
                ((std::cout << " " << p1_args), ...) << std::endl;
                
                std::cout << "Pack 2 Args:";
                ((std::cout << " " << p2_args), ...) << std::endl;
                
                std::cout << "Pack 3 Args:";
                ((std::cout << " " << p3_args), ...) << std::endl;
                });
            });
        });
}
int main() {
    foo(
        [](auto pack) { pack(1, "hello", 3.14); },
        [](auto pack) { pack("world", 2, 3, 4, 5); },
        [](auto pack) { pack(2.78, "goodbye"); }
    );       
        
}