#pragma once

#include <delegate.h>
#include <iostream>

void GlobalFunc()
{
    std::cout << "Global function is called.\n";
}

int Add(int a, int b)
{
    return a + b;
}

int Multiply(int a, int b)
{
    return a * b;
}

class TestClass
{
public:
    void MemberFunc()
    {
        std::cout << "Member function is called.\n";
    }

    int Substract(int a, int b)
    {
        return a - b;
    }

    int Divide(int a, int b)
    {
        return a / b;
    }
};

void PrintOperationResult(Delegate<int, int, int> operHandler)
{
    std::cout << "The result is " << operHandler.Invoke(10, 2) << "\n";
}
