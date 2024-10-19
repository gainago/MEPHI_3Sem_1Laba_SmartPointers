#include "UniqPtr.h"
#include "SharedPtr.h"
#include "WeakPtr.h"
#include "iostream"
#include "Tests.h"
#include "SharedPointerWithName.h"
#include "Sequence/ArraySequence.h"

int main(int argc, char **argv)
{
    /*Tests_shared_ptr();
    Tests_unique_ptr();
    Tests_weak_ptr();*/

    /*SharedPtr<int> Ptr = MakeShared<int>(14);
    WeakPtr<int> WeakPtr1(Ptr);
    SharedPtr<int> Ptr2 = WeakPtr1.lock();*/
     SharedPtr<int> PtrShared0 = MakeShared<int>(0);
    SharedPtr<int> Shared1 = MakeShared<int>(1);
    SharedPtr<int> Shared2 = MakeShared<int>(2);
    SharedPtr<int> Shared3 = Shared2;
    SharedPtrWithName<int> NamedPtr0("First Ptr", std::move(PtrShared0));
    SharedPtrWithName<int> NamedPtr1("Second Ptr", std::move(Shared1));
    SharedPtrWithName<int> NamedPtr2("Third Ptr", std::move(Shared2));
    SharedPtrWithName<int> NamedPtr3("Forth Ptr", std::move(Shared3));
    MutableArraySequence<SharedPtrWithName<int>> Sequence;
    Sequence.Prepend(NamedPtr0);
    Sequence.Prepend(NamedPtr1);
    Sequence.Prepend(NamedPtr2);
    Sequence.Prepend(NamedPtr3);
    Sequence.DeleteElement(0);
    for(int i = 0; i < Sequence.GetLength(); i++)
    {
        SharedPtrWithName<int> Ptr = Sequence.Get(i);
        try
        {
            std::cout << Ptr.Name_.GetLength() << "\t";
        }
        catch(...)
        {
            std::cout << "Error\n";
        }
        
    }

}