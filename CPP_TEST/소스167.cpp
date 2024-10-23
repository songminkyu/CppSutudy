#include <iostream>
#include <iomanip>
#include <utility>

//라인 외부 Lambda
template<typename Function>
class OutOfLineLambda
{
public:
    explicit OutOfLineLambda(Function function) : function_(function) {}
    
    template< typename Context >
    auto operator()(Context&& context) const
    {            
        if constexpr (std::is_lvalue_reference_v< Context&& >)
        {            
            std::cout << "L &&" << std::endl;
            return [&context, this](auto&&... objects) {return function_(context, std::forward<decltype(objects)>(objects)...); };
        }
        else
        {
            std::cout << "R &&" << std::endl;
            return[context = std::move(context), this](auto&&... objects) {return function_(context, std::forward<decltype(objects)>(objects)...); };
        }
    }


private:
    Function function_;
};

// Before C++17
template<typename Function>
OutOfLineLambda<Function> makeOutOfLineLambda(Function function)
{
    return OutOfLineLambda<Function>(function);
}

int func(int a, int b)
{
    return a + b;
}

int main()
{      
    OutOfLineLambda o([]() {});
    int a = 123;
    const int b = 123;
    o(1); // R value
    o(a); // L value
    o(b); // L value
    o([]() {});
    
   

}