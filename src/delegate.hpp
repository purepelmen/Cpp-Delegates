// Cpp-Delegates is a single-header file mini-library.
// Written by purepelmen. Use it the way you want.
// --------------------------------------------------------

#pragma once

/// @brief C#-like delegate for C++.
/// @tparam Result Return type.
/// @tparam ...Args All delegate arguments.
template<typename Result, typename... Args>
class delegate
{
public:
    template<typename T>
    delegate(void* target, Result(T::*funcPtr)(Args...))
    {
        converter<T> funcConverter;
        funcConverter.member_ptr = funcPtr;

        this->target = target; 
        this->func_ptr = funcConverter.static_ptr;
    }
    
    delegate(Result(*funcPtr)(Args...))
    {
        this->target = nullptr; 
        this->func_ptr = (Result(*)(...)) funcPtr;
    }

    /// @brief Invoke a method or function, with or without args if needed.
    /// @param ...args All arguments can be specified here if needed.
    /// @return Return value or void.
    Result invoke(Args... args) const
    {
        if (target == nullptr)
        {
            return func_ptr(args...);
        }

        return func_ptr(target, args...);
    }

private:
    template<typename T>
    union converter
    {
        Result(T::*member_ptr)(Args...);
        Result(*static_ptr)(...);
    };

    void* target;
    Result(*func_ptr)(...);
};
