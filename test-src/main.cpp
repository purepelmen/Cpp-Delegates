#include "test_types.h"
#include <delegate.h>

#include <iostream>

static void TestDelegateClass();
static void TestEventDelegates();

int main()
{
    TestDelegateClass();
    TestEventDelegates();
}

static void TestDelegateClass()
{
    std::cout << "[Tests] Testing Delegate class." << std::endl;

    // Test class object.
    TestClass testClass{};
    
    // Two different types of delegate construction, stored in the same type.
    Delegate<void> globalFunc{ GlobalFunc };
    Delegate<void> memberFunc{ testClass, TestClass::MemberFunc };

    // The two different types can be invoked the same way.
    globalFunc.Invoke();
    memberFunc.Invoke();

    // Universal delegate demonstration (PrintOperationResult is able to accept global and member functions).
    // Here you even don't need to specify template arguments of delegate type because of type deduction.
    PrintOperationResult(Delegate(Add));
    PrintOperationResult(Delegate(testClass, TestClass::Substract));
    PrintOperationResult({ Multiply });
    PrintOperationResult({ testClass, TestClass::Divide });
    
    // You can also use lambda expression.
    PrintOperationResult(Delegate<int, int, int>([](int a, int b)
    {
        return a % b;
    }));

    std::cout << std::endl;
}

static void TestEventDelegates()
{
    std::cout << "[Tests] Testing DelegateEvent class." << std::endl;

    TestClass testClass{};
    DelegateEvent<void> testEvent{};

    testEvent.Add({ testClass, TestClass::MemberFunc });
    testEvent.Add({ GlobalFunc });
    testEvent.Add({ testClass, TestClass::MemberFunc });
    testEvent.Add({ GlobalFunc });

    testEvent.Invoke();

    std::cout << "[Tests] After removing a reference to GlobalFunc." << std::endl;
    testEvent.Remove({ GlobalFunc });
    testEvent.Invoke();

    // Note: this could be useful to do before freeing an object that has been subscribed to some events.
    std::cout << "[Tests] After removing all delegates pointing to TestClass." << std::endl;
    testEvent.RemoveAll(&testClass);
    testEvent.Invoke();

    std::cout << std::endl;
}
