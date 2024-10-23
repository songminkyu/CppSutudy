#include <utility> // {make_}index_sequence
#include <iostream> // for demo purposes only


/*
* 
Cute C++ trick of the day: it's surprisingly difficult to 
interleave (i.e., zip + flatten) two parameter packs in C++.

Here's the best way to do so that I've come up with; does 
anyone else have anything more clever?

*/
//이건 clang 언어에서만 되는 컴파일.... msvc(x), gcc(x), llvm(o)

/*
컴파일 방법
clang++ -std=c++2a -o hellowolrd 소스228.cpp 
*/

template <class, std::size_t> concept Any = true;
template <std::size_t N> auto at(auto... args) 
{
    return[&]<std::size_t... I>(std::index_sequence<I...>) {
        return [](Any<I> auto..., auto arg, auto...) { return arg; }(args...);
    }(std::make_index_sequence<N>{});
}
auto interleave(auto p1, auto p2, auto cb) 
{
    return p1([&](auto... args1) {
        return p2([&](auto... args2) {
            static_assert(sizeof...(args1) == sizeof...(args2));
            // problem: given args1 and args2, how do I call `cb` with something like (pseudocode):
            //  cb(args1[0], args2[0], args1[1], args2[1], ...) ?
            return[&]<std::size_t... Idx>(std::index_sequence<Idx...>) {
                return cb(at<Idx / 2 + (Idx % 2 != 0) * sizeof...(args1)>(args1..., args2...)...);
            }(std::make_index_sequence<2 * sizeof...(args1)>{});
        });
    });
}

int main() {
    interleave(
        /* p1 = */ [](auto cb) { cb(1, 2, "hello", 'd'); },
        /* p2 = */ [](auto cb) { cb('a', 'b', "world", 4); },
        /* callback = */ [](auto... args) {
            ((std::cout << args << " "), ...) << std::endl;
        }
    );
}