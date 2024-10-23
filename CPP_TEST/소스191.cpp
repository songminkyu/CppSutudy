#include <sstream>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>

template<typename Arg, typename ...Args>
std::ostream & Write(std::ostream & o, Arg&& arg, Args&&... args)
{
    o << std::forward<Arg>(arg);
    
    using expander = int[];
    (void) expander{ (o << ", " << std::forward<Args>(args), void(), 0)... };
    
    return o;
}

int main()
{
    std::ostringstream o;

    Write(o, 1, "Hello", 2, "World", 3, 1.4857);

    // o should contain the string of characters "1, Hello, 2, World, 3, 1.4857"
    std::cout << o.str() << std::endl;
    
    return 0;
}