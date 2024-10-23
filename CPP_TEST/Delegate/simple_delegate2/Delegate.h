// Delegate.h
#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include <list>
#include <functional>
#include <type_traits> // std::is_void ��� �߰�

template <class R, class... ARGS>
class Delegate
{
public:
    typedef typename std::list<std::function<R(ARGS...)>>::iterator iterator;

    // operator ()�� ���ø����� ����
    template <class T = R>
    typename std::enable_if<!std::is_void<T>::value, T>::type operator () (const ARGS... args)
    {
        // ���� Ÿ���� void�� �ƴ� ���
        decltype(functions.front()(args...)) result {}; // result ������ �� �ʱ�ȭ
        if (!functions.empty()) // �Լ��� ������� ������ Ȯ��
        {
            for (auto& func : functions)
            {
                result = func(args...); // �� �Լ��� ȣ���ϰ� ������� ����
            }
        }
        return result; // ������� ����
    }

    template <class T = R>
    typename std::enable_if<std::is_void<T>::value, void>::type operator () (const ARGS... args)
    {
        // ���� Ÿ���� void�� ���
        for (auto& func : functions)
        {
            func(args...); // �� �Լ��� ȣ�⸸ ��
        }
        return; // ���ϰ� ����
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