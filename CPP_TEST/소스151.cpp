#include <iostream>
#include <assert.h>
using namespace std;

template <typename T>
class Container {
    T& actual() { return *static_cast<T*>(this); }
    T const& actual() const { return *static_cast<T const*>(this); }
public:
    decltype(auto) front() { return *actual().begin(); }
    decltype(auto) back() { return *std::prev(actual().end()); }
    decltype(auto) size() const { return std::distance(actual().begin(), actual().end()); }
    decltype(auto) operator[](size_t i) { return *std::next(actual().begin(), i); }
};

template <typename T>
class DynArray : public Container<DynArray<T>> {
    size_t m_size;
    unique_ptr<T[]> m_data;
public:
    DynArray(size_t s) : m_size{ s }, m_data{ make_unique<T[]>(s) } {}
    T* begin() { return m_data.get(); }
    const T* begin() const { return m_data.get(); }
    T* end() { return m_data.get() + m_size; }
    const T* end() const { return m_data.get() + m_size; }
};

void main()
{
    DynArray<int> arr(10);
    arr.front() = 2;
    arr[2] = 5;
    asssert(arr.size() == 10);
}