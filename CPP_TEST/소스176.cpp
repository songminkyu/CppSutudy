#include <vector>
#include <set>
#include <iostream>

namespace ext
{
    template<typename ContainerType>
    concept emplace_back_t = requires (ContainerType container)
    {
        // this is called simple requirement
        container.emplace_back(std::declval<typename ContainerType::value_type>());
    };

    template<typename ContainerType>
    concept emplace_t = requires(ContainerType container)
    {
        container.emplace(std::declval<typename ContainerType::value_type>());
    };

    template<typename ContainerType>
    concept emplaceable_t = emplace_back_t<ContainerType> || emplace_t<ContainerType>;


    // Curiously Recursive Template
    template<emplaceable_t ContainerType>
    class SupportOutput : public ContainerType
    {
    public:

        // we have to declare base class' Constructors
        using ContainerType::ContainerType;

        template<typename T>
        friend SupportOutput& operator<<(SupportOutput& so, T&& arg)
        {
            if constexpr (emplace_back_t<ContainerType>)
            {
                so.emplace_back(std::forward<T>(arg));
            }
            else if constexpr (emplace_t<ContainerType>)
            {
                so.emplace(std::forward<T>(arg));
            }
            return so;
        }
    };
}

void test_support_output()
{
    ext::SupportOutput< std::vector<int> > v1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ext::SupportOutput< std::set<int> > s1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    
    for (auto&& i : v1)
    {
        std::cout << i << std::endl;
    }

    v1 << 10 << 11;

    for (auto&& i : v1)
    {
        std::cout << i << std::endl;
    }
  
 
    s1 << 10 << 11;

    for (auto&& i : s1)
    {
        std::cout << i << std::endl;
    }

}

int main()
{
    test_support_output();  
}
