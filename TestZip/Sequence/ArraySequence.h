#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

template <typename T>
class ArraySequence: public Sequence<T>
{
protected:
    DynamicArray<T> *array_;// array capacity is capacity
    int size_{0};
    virtual ArraySequence<T> *GetInstance() = 0;
public:
    ArraySequence()
    { 
        this->array_ = new DynamicArray<T>();
        size_ = array_->GetCapacity();
    }

    ArraySequence(T *items, int count)
    {
        this->array_ = new DynamicArray<T>(items, count);
        size_ = array_->GetCapacity();
    }

    ArraySequence(const ArraySequence<T> &seq)
    {
        this->array_ = new DynamicArray<T>(*seq.array_);
        size_ = array_->GetCapacity();
    }

    ArraySequence(const Sequence<T> &seq)
    {
        this->array_ = new DynamicArray<T>(seq.GetLength());
        for (int i = 0; i < seq.GetLength(); i++)
        {
            this->array_->Set(i, seq.Get(i));
            size_++;
            //this->Append(seq.Get(i));
        }
    }

    ArraySequence(DynamicArray<T> *array)
    {
        this->array_ = new DynamicArray<T>(*array);
        size_ = array->GetCapacity();
    }

    ArraySequence(const DynamicArray<T> &array)
    {
        this->array_ = new DynamicArray<T>(array);
        size_ = array_->GetCapacity();
    }

    virtual ~ArraySequence()
    {
        delete this->array_;
    }

    T const & GetFirst() const override
    {
        return this->array_->Get(0);
    }

    T const & GetLast() const override
    {
        return this->array_->Get(this->GetLength() - 1);
    }

    T const & Get(int const index) const override
    {
        return this->array_->Get(index);
    }

    int GetLength() const override
    {
        //return this->array->GetSize();
        return size_;
    }
    int GetCapacity() const
    {
        return this->array_->GetCapacity();
    }

    ArraySequence<T> *Append(T const & item) override
    {
        ArraySequence<T> *result = GetInstance();
        if(result->size_ == this->array_->GetCapacity())
        {
           
            int TmpSize = size_;
            if(result->array_->GetCapacity() == 0)
            {
                  result->array_->ReCapacity(1);
            }
            else
            {
                result->array_->ReCapacity(result->array_->GetCapacity() * 2);
            }
            result->size_ = TmpSize + 1;
            result->array_->Set(result->GetLength() - 1, item);
            return result;
        }
        else
        {
            
            result->size_++;
            result->array_->Set(result->GetLength() - 1, item);
            return result;
        }
    }

    ArraySequence<T> *Prepend(T const & item) override
    {
        ArraySequence<T> *result = GetInstance();
        if(result->size_ == result->GetCapacity())
        {
            if(result->array_->GetCapacity() == 0)
            {
                result->array_->ReCapacity(1);
            }
            else
                result->array_->ReCapacity(result->array_->GetCapacity() * 2);
            result->size_++;
            //T current = this->array->Get(0);
            for (int i = result->GetLength() - 1; i > 0; i--)
            {
                result->array_->Set(i, result->array_->Get(i - 1));
            }
            result->array_->Set(0, item);
            return result;
        }
        else
        {
            result->size_++;
            
            for (int i = result->GetLength() - 1; i > 0; i--)
            {
                result->array_->Set(i, result->array_->Get(i - 1));
            }
            result->array_->Set(0, item);
            return result;
        }
    }

    ArraySequence<T> *InsertAt(T const & item, int index) override
    {
        ArraySequence<T> *result = GetInstance();
        if(result->size_ == result->GetCapacity())
        {
            result->array_->ReCapacity(this->array_->GetCapacity() * 2);
            result->size_++;
            for (int i = result->size_ - 1; i > index; i--)
            {
                result->array_->Set(i, result->array_->Get(i - 1));
            }
            result->array_->Set(index, item);
            return result;
        }
        else
        {
             result->size_++;
            for (int i = result->size_ - 1; i > index; i--)
            {
                result->array_->Set(i, result->array_->Get(i - 1));
            }
            result->array_->Set(index, item);
            return result;
        }
    }

    T &operator[] (int index) override
    {
        return (*(GetInstance ()->array_))[index];
    }

    ArraySequence<T>* DeleteElement(int index)
    {
        if(index < 0 || index >= size_)
            throw "Invalid index";
        ArraySequence<T>* ReturnArray = GetInstance(); 
        ReturnArray->array_->DeleteElement(index);
        ReturnArray->size_--;

        return ReturnArray;
    }
};

template <typename T>
class MutableArraySequence : public ArraySequence<T>
{
private:
    ArraySequence<T> *GetInstance() override
    {
        return static_cast<ArraySequence<T> *> (this);
    }

public:
    using ArraySequence<T>::ArraySequence;

    MutableArraySequence<T> *Concat (Sequence<T> const  &seq) override
    {
        for (int i = 0; i < seq.GetLength(); i++)
        {
            this->Append(seq.Get(i));
        }
        return this;
    }

    MutableArraySequence<T> *GetSubSequence (int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex < 0 || endIndex >= this->GetLength() || endIndex < startIndex)
        {
            throw "Invalid argument";
        }
        DynamicArray<T> *resultArray = new DynamicArray<T>(endIndex - startIndex + 1);
        for (int i = 0; i < endIndex - startIndex + 1; i++)
        {
            resultArray->Set(i, this->array_->Get(startIndex + i));
        }
        MutableArraySequence<T> *result = new MutableArraySequence<T>(*resultArray);
        result->array_ = resultArray;
        return result;
    }
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T>
{
private:
    ArraySequence<T> *GetInstance() override
    {
        ImmutableArraySequence<T> *instance = new ImmutableArraySequence<T> (*this);
        return instance;
    }

public:
    using ArraySequence<T>::ArraySequence;

    ImmutableArraySequence<T> *Concat(Sequence<T> const & seq) override
    {
        DynamicArray<T> *resultArray = new DynamicArray<T>(this->GetLength() + seq.GetLength());
        for (int i = 0; i < this->GetLength(); i++)
        {
            resultArray->Set(i, this->Get(i));
        }
        for (int i = 0; i < seq.GetLength(); i++)
        {
            resultArray->Set(this->GetLength() + i, seq.Get(i));
        }
        ImmutableArraySequence<T> *result = new ImmutableArraySequence<T>(resultArray);
        return result;
    }

    ImmutableArraySequence<T> *GetSubSequence(int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex < 0 || endIndex >= this->GetLength() || endIndex < startIndex)
        {
            throw "Invalid argument";
        }
        DynamicArray<T> *resultArray = new DynamicArray<T>(endIndex - startIndex + 1);
        for (int i = 0; i < endIndex - startIndex + 1; i++)
        {
            resultArray->Set(i, this->array_->Get(startIndex + i));
        }
        ImmutableArraySequence<T> *result = new ImmutableArraySequence<T>(resultArray);
        result->array_ = resultArray;
        return result;
    }

};

#endif
