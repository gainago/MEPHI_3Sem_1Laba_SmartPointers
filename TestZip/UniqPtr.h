#ifndef UNIQ_PTR_H
#define UNIQ_PTR_H


template <typename Type>
class UniqPtr{
private:
    Type* Data_;
public:
    UniqPtr() : Data_(nullptr) {}
    UniqPtr(Type *data) : Data_(data) {}
    UniqPtr(UniqPtr<Type> const & Other) = delete;
    UniqPtr(UniqPtr<Type> && Other) noexcept
    {
        Data_ = Other.Data_;
        Other.Data_ = nullptr;
    }
    Type* Release() noexcept
    {
        Type* ReturnPointer = Data_;
        Data_ = nullptr;
        return ReturnPointer;
    }

    void Reset(Type* pointer) noexcept
    {
        DeleteData();
        Data_ = pointer;
    }

    void Swap(UniqPtr<Type> & pointer) noexcept
    {
        Type* CurrentPointer = Data_;
        Data_ = pointer.Data_;
        pointer.Data_ = CurrentPointer;
    }

    Type& Get() noexcept
    {
        return *Data_;
    }

    UniqPtr<Type> operator=(UniqPtr<Type> ptr) noexcept = delete;

    UniqPtr<Type> operator=(UniqPtr<Type> && Other)
    {
        Data_ = Other.Data_;
        Other.Data_ = nullptr;
    }

    operator bool() const noexcept
    {
        if(Data_ == nullptr)
            return false;
        return true;
    }

    Type& operator*()
    {
        if(Data_ == nullptr)
            throw "nullptr";
        return this->Get();
    }

    Type* operator->()
    {
        if(Data_ == nullptr)
            throw "nullptr";
        return this->Data_;
    }

    void DeleteData()// в приватной секции
    {
        delete Data_;
    }

    ~UniqPtr()
    {
        DeleteData();
    }
};

template<typename Type, typename ... Args>
Type* MakeUniq(Args ... args)
{
    Type * Ptr = new Type(args...);
    if(Ptr == nullptr)
        throw "nullptr";
    
    return Ptr;
}



#endif