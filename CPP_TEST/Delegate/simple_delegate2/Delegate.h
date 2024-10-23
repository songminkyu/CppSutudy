// Delegate.h
#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include <list>
#include <functional>
#include <type_traits> // std::is_void 헤더 추가

template <class R, class... ARGS>
class Delegate
{
public:
    typedef typename std::list<std::function<R(ARGS...)>>::iterator iterator;

    // operator ()를 템플릿으로 정의
    template <class T = R>
    typename std::enable_if<!std::is_void<T>::value, T>::type operator () (const ARGS... args)
    {
        // 리턴 타입이 void가 아닌 경우
        decltype(functions.front()(args...)) result {}; // result 변수를 값 초기화
        if (!functions.empty()) // 함수가 비어있지 않은지 확인
        {
            for (auto& func : functions)
            {
                result = func(args...); // 각 함수를 호출하고 결과값을 저장
            }
        }
        return result; // 결과값을 리턴
    }

    template <class T = R>
    typename std::enable_if<std::is_void<T>::value, void>::type operator () (const ARGS... args)
    {
        // 리턴 타입이 void인 경우
        for (auto& func : functions)
        {
            func(args...); // 각 함수를 호출만 함
        }
        return; // 리턴값 없음
    }

    Delegate& operator += (std::function<R(ARGS...)> const& func)
    {
        functions.push_back(func);
        return *this;
    }

    Delegate& operator -= (std::function<R(ARGS...)> const& func)
    {
        void (* const* func_ptr)(ARGS...) = func.template target<void(*)(ARGS...)>();
        const std::size_t func_hash = func.target_type().hash_code();

        if (nullptr == func_ptr)
        {
            for (auto itr = functions.begin(); itr != functions.end(); itr++)
            {
                if (func_hash == (*itr).target_type().hash_code())
                {
                    functions.erase(itr);
                    return *this;
                }
            }
        }
        else
        {
            for (auto itr = functions.begin(); itr != functions.end(); itr++)
            {
                void (* const* delegate_ptr)(ARGS...) = (*itr).template target<void(*)(ARGS...)>();
                if (nullptr != delegate_ptr && *func_ptr == *delegate_ptr)
                {
                    functions.erase(itr);
                    return *this;
                }
            }
        }
        return *this;
    }

    iterator begin() noexcept
    {
        return functions.begin();
    }
    iterator end() noexcept
    {
        return functions.end();
    }
    void clear()
    {
        functions.clear();
    }

private:
    std::list<std::function<R(ARGS...)>> functions;
};

#endif