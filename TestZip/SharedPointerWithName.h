#ifndef SHARED_POINTER_WITH_NAME_H
#define SHARED_POINTER_WITH_NAME_H
#include "SharedPtr.h"
#include "TypesOfData/MyString.h"

template<typename Type> class SharedPtrWithName
{
public:
    MyString Name_;
    SharedPtr<Type> Pointer_;

    SharedPtrWithName(MyString Name, SharedPtr<Type>&& Pointer) : Name_(Name), Pointer_(std::forward<SharedPtr<Type>>(Pointer)) {}
    SharedPtrWithName(SharedPtrWithName<Type> const & Other)
    {
        Name_ = Other.Name_;
        Pointer_ = Other.Pointer_;
    }
    SharedPtrWithName() {}
    SharedPtrWithName<Type> operator=(SharedPtrWithName<Type> const & Other)
    {
        if(this->Name_ == Other.Name_ && this->Pointer_ == Other.Pointer_)
            return *this;

        Pointer_ = Other.Pointer_;
        Name_ = Other.Name_;
        return *this;
    }

};
#endif