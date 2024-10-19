#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <typename T>
class ListSequence: public Sequence<T>
{
protected:
    LinkedList<T> *list_;
    virtual ListSequence<T> *GetInstance() = 0;
public:
    ListSequence()
    {
        this->list_ = new LinkedList<T>();
    }

    ListSequence(T *items, int count)
    {
        this->list_ = new LinkedList<T>(items, count);
    }

    ListSequence(const ListSequence<T> &seq)
    {
        this->list_ = new LinkedList<T>(*seq.list_);
    }

    ListSequence(const Sequence<T> &seq)
    {
        this->list_ = new LinkedList<T>();
        for (int i = 0; i < seq.GetLength(); i++)
        {
            this->list_->Append(seq.Get(i));
        }
    }

    ListSequence(LinkedList<T> *list)
    {
        this->list_ = new LinkedList<T>(*list);
    }

    ListSequence (const LinkedList<T>& list)
    {
        this->list_ = new LinkedList<T>(list);
    }

    ~ListSequence()
    {
        delete this->list_;
    }

    T const & GetFirst() const override
    {
        return this->list_->GetFirst();
    }

    T const & GetLast() const override
    {
        return this->list_->GetLast();
    }

    T const & Get(int index) const override
    {
        return this->list_->Get(index);
    }

    int GetLength() const override
    {
        return this->list_->GetLength();
    }

    ListSequence<T> *Append(T const & item) override
    {
        ListSequence<T> *result = GetInstance();
        result->list_->Append(item);
        return result;
    }

    ListSequence<T> *Prepend(T const & item) override
    {
        ListSequence<T> *result = GetInstance();
        result->list_->Prepend(item);
        return result;
    }

    ListSequence<T> *InsertAt(T const & item, int index) override
    {
        ListSequence<T> *result = GetInstance();
        result->list_->InsertAt(item, index);
        return result;
    }

    T &operator[] (int index) override
    {
        return (*(this->list_))[index];
        //return GetInstance()->list_->operator[index];
    }
};

template <typename T>
class MutableListSequence : public ListSequence<T>
{
private:
    ListSequence<T> *GetInstance() override
    {
        return static_cast<ListSequence<T> *> (this);
    }

public:
    using ListSequence<T>::ListSequence;

    MutableListSequence<T> *Concat(Sequence<T> const &seq) override
    {
        for (int i = 0; i < seq.GetLength(); i++)
        {
            this->Append(seq.Get(i));
        }
        return this;
    }

    MutableListSequence<T> *GetSubSequence(int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex < 0 || endIndex >= this->list_->GetLength() || endIndex < startIndex)
        {
            throw "Invalid argument";
        }
        LinkedList<T> *resultList = this->list_->GetSubList(startIndex, endIndex);
        MutableListSequence<T> *result = new MutableListSequence<T>(resultList);
        result->list_ = resultList;
        return result;
    }

};

template <typename T>
class ImmutableListSequence : public ListSequence<T>
{
private:
    ListSequence<T> *GetInstance() override
    {
        ImmutableListSequence<T> *instance = new ImmutableListSequence<T> (*this);
        return instance;
    }

public:
    using ListSequence<T>::ListSequence;

    ImmutableListSequence<T> *Concat(Sequence<T> const &seq) override
    {
        LinkedList<T> *resultList = new LinkedList<T>;
        for (int i = 0; i < this->GetLength(); i++)
        {
            resultList->Append(this->Get(i));
        }
        for (int i = 0; i < seq.GetLength(); i++)
        {
            resultList->Append(seq.Get(i));
        }
        ImmutableListSequence<T> *result = new ImmutableListSequence<T>(resultList);
        return result;
    }

    ImmutableListSequence<T> *GetSubSequence(int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex < 0 || endIndex >= this->list_->GetLength() || endIndex < startIndex)
        {
            throw "Invalid argument";
        }
        LinkedList<T> *resultList = this->list_->GetSubList(startIndex, endIndex);
        ImmutableListSequence<T> *result = new ImmutableListSequence<T>(resultList);
        result->list_ = resultList;
        return result;
    }
};

#endif