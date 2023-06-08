#include <iostream>
#include "delegate.hpp"

// ------------------------------------------
// Test functions/methods for delegates

void globalFunc()
{
    std::cout << "Global function is called.\n";
}

int add(int a, int b)
{
    return a + b;
}

class TestClass
{
public:
    void memberFunc()
    {
        std::cout << "Member function is called.\n";
    }

    int sub(int a, int b)
    {
        return a - b;
    }
};

void printOperationResult(delegate<int, int, int> operHandler)
{
    std::cout << "The result is " << operHandler.invoke(5, 2) << "\n";
}

// ------------------------------------------
// All tests with delegates

int main()
{
    // Class object.
    TestClass testClass;
    
    // Two different types of delegates.
    delegate<void> globalFuncDelegate(globalFunc);
    delegate<void> memberFuncDelegate(&testClass, TestClass::memberFunc);

    // Invoking them.
    globalFuncDelegate.invoke();
    memberFuncDelegate.invoke();

    // Universal delegate demonstration (printOperationResult is able to accept global and member functions).
    // Here you even don't need to specify template arguments of delegate type because of type deduction.
    printOperationResult(delegate(add));
    printOperationResult(delegate(&testClass, TestClass::sub));
    
    // You can even use lambda expression.
    printOperationResult(delegate<int, int, int>([](int a, int b)
    {
        return a * b;
    }));
}
