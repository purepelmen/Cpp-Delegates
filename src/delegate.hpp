// --------------------------------------------------------
// Cpp-Delegates is a single-header file mini-library.
// Written by purepelmen. Use it the way you want.

#pragma once

/// @brief C#-like delegate for C++.
/// @tparam R Result type.
/// @tparam ...Args All delegate arguments.
template<typename R, typename... Args>
class delegate
{
public:
    template<typename T>
    delegate(void* target, R(T::*funcPtr)(Args...))
    {
        funcPtrUnion<R, T, Args...> funcPtrConverter;
        funcPtrConverter.member_ptr = funcPtr;

        this->target = target; 
        this->func_ptr = funcPtrConverter.static_ptr;
    }
    
    delegate(R(*funcPtr)(Args...))
    {
        this->target = nullptr; 
        this->func_ptr = (R(*)(...)) funcPtr;
    }

    /// @brief Invoke a method or function, with or without args if needed.
    /// @param ...args All arguments can be specified here if needed.
    /// @return Return value or void.
    R invoke(Args... args)
    {
        if (target == nullptr)
        {
            return func_ptr(args...);
        }

        return func_ptr(target, args...);
    }

private:
    template<typename R, typename T, typename... Args>
    union funcPtrUnion
    {
        R(T::*member_ptr)(Args...);
        R(*static_ptr)(...);
    };

    void* target;
    R(*func_ptr)(...);
};
