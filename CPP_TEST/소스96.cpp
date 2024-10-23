#include <iostream>
#include <mutex>

struct A {
    using lock_type = std::mutex;

    lock_type lock{};

    template <class T>
    operator T() { return { lock, *this }; }
};

template<class T, class M>
struct LockMode {
    std::lock_guard<M> lock;
    T& ref;
    LockMode(M& lock, T& ref) :lock{ lock }, ref{ ref } {}
    T* operator->() {
        return &ref;
    }
};
template<class T, class M = T::lock_type>
LockMode(T&)->LockMode<T, M>;

template<class T>
struct UnLockMode {
    T& ref;
    template<class M>
    UnLockMode(M&, T& ref) : ref{ ref } {}
    T* operator->() {
        return &ref;
    }
};

template<class T>
UnLockMode(T&)->UnLockMode<T>;

int main() {
    A a{};
    LockMode p{ a };
    UnLockMode up{ a };
}