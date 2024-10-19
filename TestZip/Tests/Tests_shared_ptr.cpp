#include "Tests_shared_ptr.h"
#include <assert.h>//cassert C++
#include "../SharedPtr.h"
#include "../TypesOfData/Person.h"

void Test_shared_reset()
{
    SharedPtr<int> Ptr = MakeShared<int>(999);
    Ptr.Reset(MakeShared<int>(0));
    assert((Ptr.operator*()) == 0);//спорно что явный вызов операторов более читаем
}

void Test_shared_swap()
{
    SharedPtr<int> Ptr1 = MakeShared<int>(234);
    SharedPtr<int> Ptr2 = MakeShared<int>(-111);
    Ptr1.Swap(Ptr2);
    assert(Ptr1.operator*() == -111);
    assert(Ptr2.operator*() == 234);
}

void Test_shared_get()
{
    SharedPtr<int> Ptr1 = MakeShared<int>(1234567);
    assert(((Ptr1.Get())) == 1234567);
}

void Test_shared_use_count()
{
    SharedPtr<int> Ptr1 = MakeShared<int>(-34567);
    SharedPtr<int> Ptr2 = Ptr1;
    SharedPtr<int> Ptr3 = Ptr2;
    assert(Ptr2.Use_count() == 3);
}

void Test_shared_operator_equality()
{
    SharedPtr<int> Ptr1 = MakeShared<int>(-0);//-0 вызывает странные ассоциации
    SharedPtr<int> Ptr2 = Ptr1;
    SharedPtr<int> Ptr3 = Ptr2;
    assert((Ptr1.Get() == Ptr2.Get()));
    assert(Ptr2.Get() == Ptr1.Get());
}

void Test_shared_operator_dereference()
{
    SharedPtr<int> Ptr1 = MakeShared<int>(1);
    SharedPtr<int> Ptr2 = MakeShared<int>(1);
    assert(*Ptr1 == *Ptr2);
}

void Test_shared_operator_dereference2()
{
    SharedPtr<Person> Ptr1 = MakeShared<Person>("123 543", "Ivan",
     "Ivanovich", "Ivanov");
    assert(Ptr1->GetId() == (MyString)"123 543");
    
}
/*//проверять и ловить исключения в тестах
try{
...
assert(false && "Так нельзя (и причина)");
} catch(...)*/
