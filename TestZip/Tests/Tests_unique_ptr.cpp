#include "Tests_unique_ptr.h"
#include <assert.h>
#include "../UniqPtr.h"
#include "../TypesOfData/Person.h"

void Test_unique_release()
{
    UniqPtr<int> Ptr = MakeUniq<int>(399);
    int *IntPointer = Ptr.Release();
    assert((*IntPointer) == 399);
    assert(Ptr.Release() == nullptr);
    delete IntPointer;

}

void Test_unique_reset()
{
    UniqPtr<int> Ptr = MakeUniq<int>(999);
    Ptr.Reset(MakeUniq<int>(0));
    int *IntPointer = Ptr.Release();
    assert((*IntPointer) == 0);
    delete IntPointer;
}

void Test_unique_swap()
{
    UniqPtr<int> Ptr1 = MakeUniq<int>(25);
    UniqPtr<int> Ptr2 = MakeUniq<int>(-100);
    Ptr1.Swap(Ptr2);
    int *IntPointer1 = Ptr1.Release();
    int *IntPointer2 = Ptr2.Release();
    assert((*IntPointer1) == -100);
    assert((*IntPointer2) == 25);
    delete IntPointer1;
    delete IntPointer2;
}

void Test_unique_get()
{
    UniqPtr<int> Ptr1 = MakeUniq<int>(1234567);
    int IntPointer1 = Ptr1.Get();
    assert(IntPointer1 == 1234567);
    
}

void Test_unique_operator_dereference()
{
    UniqPtr<int> Ptr1 = MakeUniq<int>(-1000);
    assert(*Ptr1 == -1000);
}

void Test_unique_operator_dereference2()
{
    UniqPtr<Person> Ptr1 = MakeUniq<Person>("123 543", "Ivan",
     "Ivanovich", "Ivanov");
    assert(Ptr1->GetId() == (MyString)"123 543");
}
