#pragma once

// Delegate type. Its template parameters define a signature of invokable methods. 
// Has two constructors for creating a delegate to a static or member function.
template<typename Result, typename... Args>
class Delegate
{
private:
    void* target;
    Result(*funcPtr)(...);

public:
    template<typename T>
    Delegate(T& target, Result(T::*funcPtr)(Args...))
    {
        union FuncConv
        {
            Result(T::*memberPtr)(Args...);
            Result(*staticPtr)(...);

            FuncConv(Result(T::*memberPtr)(Args...)) : memberPtr(memberPtr) {}
        };

        FuncConv funcConv{ funcPtr };
        T* targetPtr = &target;

        this->target = targetPtr; 
        this->funcPtr = funcConv.staticPtr;
    }
    
    Delegate(Result(*funcPtr)(Args...))
    {
        this->target = nullptr; 
        this->funcPtr = (Result(*)(...)) funcPtr;
    }

    bool operator==(const Delegate& rhs) const
    {
        return this->target == rhs.target && this->funcPtr == rhs.funcPtr;
    }

    Result operator()(Args... args) const
    {
        return Invoke(args...);
    }

    Result Invoke(Args... args) const
    {
        if (target == nullptr)
            return funcPtr(args...);

        return funcPtr(target, args...);
    }

    void* GetTarget() const { return target; }
};

#ifndef DELEGATE_H_NO_EVENT

#include <algorithm>
#include <vector>

// A kind of C#'s MulticastDelegate class.
template<typename Result, typename... Args>
class DelegateEvent
{
private:
    using CompDelegate = Delegate<Result, Args...>;

    std::vector<CompDelegate> list;

public:
    Result Invoke(Args... args) const
    {
        if (list.size() == 0)
            return;
        
        for (auto i = list.begin(); i != std::prev(list.end()); i++)
        {
            i->Invoke(args...);
        }

        return std::prev(list.end())->Invoke(args...);
    }

    void Add(CompDelegate delegate)
    {
        list.push_back(delegate);
    }

    bool Remove(CompDelegate delegate)
    {
        auto foundPos = std::find(list.begin(), list.end(), delegate);
        if (foundPos == list.end())
            return false;

        list.erase(foundPos);
        return true;
    }

    void RemoveAll(void* target)
    {
        auto newEnd = std::remove_if(list.begin(), list.end(), [target](CompDelegate d) -> bool
        {
            return d.GetTarget() == target;
        });

        list.erase(newEnd, list.end());
    }
};
#endif  // DELEGATE_H_NO_EVENT
