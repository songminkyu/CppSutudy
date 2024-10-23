#include <iostream>
#include <vector>
#include <coroutine>
#include <exception>
#include <cmath>
//co_await�� co_return ����

template <class _Ty>
struct my_routine {
    struct awaitable {
        bool await_ready() { return false; }
        void await_suspend(std::coroutine_handle<> h) { std::cout << "������\n"; }
        void await_resume() { std::cout << "�о\n"; }
    };

    struct promise_type {
        const _Ty* _Value = nullptr;
        std::exception_ptr _Exception{};

        my_routine get_return_object() noexcept { return my_routine{ *this }; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        void _Rethrow_if_exception() {
            if (!_Exception)  return;
            std::rethrow_exception(_Exception);
        }

        void unhandled_exception() noexcept {
            _Exception = std::current_exception();
        }

        std::suspend_always yield_value(const _Ty& _Val) noexcept {
            _Value = std::addressof(_Val);
            return {};
        }

        void return_value(const _Ty& _Val) noexcept {
            _Value = std::addressof(_Val);
        }
    };

    bool call() {
        bool is_end = false;
        do {
            if (!_Coro || _Coro.done()) { is_end = true; break; } // over resume;

            _Coro(); //_Coro.resume(); same command    
            _Coro.promise()._Rethrow_if_exception();
            if (!_Coro.done()) break;
            std::cout << "\t value:" << *(_Coro.promise()._Value) << "\n";
            is_end = true;
        } while (false);
        return is_end;
    }

    explicit my_routine(promise_type& _Prom) noexcept :
        _Coro(std::coroutine_handle<promise_type>::from_promise(_Prom)) { }

    my_routine(const my_routine&) = delete;
    my_routine(my_routine&& ptr) :_Coro{ ptr._Coro } {
        ptr._Coro = nullptr;
    }

    ~my_routine() {
        if (!_Coro) return;
        _Coro.destroy();
        _Coro = nullptr;
    }
private:
    std::coroutine_handle<promise_type> _Coro = nullptr;
};

my_routine<int> routine_call(int cnt) {
    using my_routine = my_routine<int>;
    for (int i = 0; i < cnt - 1; ++i) {
        std::cout << "LOOP CNT:" << i << "\n";
        co_await my_routine::awaitable{};
    }
    std::cout << "LOOP CNT:" << cnt;
    co_return 3;
}

int main() {
    constexpr std::size_t CNT = 3;
    constexpr std::size_t MAX_CNT = 1;
    std::vector< my_routine<int>> data;
    for (std::size_t i = 0; i < MAX_CNT; ++i) {
        data.emplace_back(routine_call(CNT));
    }

    for (int i = 0; i < CNT; ++i) {
        for (auto&& item : data) item.call();
    }

   /* double runiningRate = 0.0001;
    for (int i = 0; i < 10000; i++)
    {
        std::cout << runiningRate << " : "<< std::log(runiningRate) << std::endl;
        runiningRate += 0.0001;
    }       */
}