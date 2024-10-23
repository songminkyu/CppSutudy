
#include <utility>
#include <string>
#include <type_traits>

//https://www.youtube.com/watch?v=A3_xrqr5Kdw

template<typename Contained>
struct Optional
{
    union { Contained data; };
    bool initialized = false;

    constexpr Optional& operator=(Contained&& data) {
        this->data = std::move(data);
        initialized = true;
        return *this;
    }

    constexpr ~Optional() requires(!std::is_trivially_destructible_v<Contained>) {
        if (initialized) {
            data.~Contained();
        }
    }

    constexpr ~Optional() = default;

};

int main()
{
    Optional<int> obj;
    obj = 5;

    static_assert(std::is_trivially_destructible_v<Optional<int>>);
    static_assert(!std::is_trivially_destructible_v<Optional<std::string>>);
}