#include "Tests_weak_ptr.h"
#include "../WeakPtr.h"
#include "../TypesOfData/Person.h"
#include <assert.h>

void Test_weak_reset()
{
    SharedPtr<int> Ptr1 = MakeShared<int>(999);
    WeakPtr<int> Ptr2(Ptr1);
    WeakPtr<int> Ptr3(Ptr1);
    Ptr2.Reset();
    assert(Ptr3.CountWeak() == 1);
}

void Test_weak_swap()
{
    SharedPtr<int> Shared1 = MakeShared<int>(999);
    SharedPtr<int> Shared2 = MakeShared<int>(0);
    WeakPtr<int> Weak1(Shared1);
    WeakPtr<int> Weak2(Shared2);
    Weak1.Swap(Weak2);
    SharedPtr<int> Shared3 = Weak1.lock();
    SharedPtr<int> Shared4 = Weak2.lock();
    assert(Shared3.Get() == 0);
    assert(Shared4.Get() == 999);
}

void Test_weak_use_count()
{
    SharedPtr<int> Shared1 = MakeShared<int>(-1234);
    WeakPtr<int> Weak1(Shared1);
    WeakPtr<int> Weak2(Shared1);
    assert(Weak1.CountWeak() == 2);
}

void Test_weak_expired()
{
    SharedPtr<int> Shared1 = MakeShared<int>(10000);
    WeakPtr<int> Weak1(Shared1);
    WeakPtr<int> Weak2(Shared1);
    assert(!Weak1.IsAlive());
    assert(!Weak2.IsAlive());
}

void Test_weak_lock()
{
    SharedPtr<Person> Shared1 = MakeShared<Person>("123 456", "Ivanov", "Ivan", "Ivanovich");
    WeakPtr<Person> Weak1(Shared1);
    SharedPtr<Person> Shared2 = Weak1.lock();
    assert(Shared2->GetFirstName() == "Ivanov");
}
