#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <typename T>
class DynamicArray
{
private:
    int capacity_;
    T* elements_;
public:
    DynamicArray()
    {
        this->capacity_ = 0;
        this->elements_ = nullptr;
    }

    DynamicArray(int size) : DynamicArray()
    {
        if (size < 0)
        {
            throw "Invalid size";
        }
        this->capacity_ = size;
        this->elements_ = new T[size];
    }

    DynamicArray(T* items, int count) : DynamicArray(count)
    {
        if (items == nullptr)
        {
            throw "Invalid argument in constructor";
        }
        for (int i = 0; i < count; i++)
        {
            elements_[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray<T> &dynamicArray) : DynamicArray(dynamicArray.elements_, dynamicArray.capacity_) {}

    ~DynamicArray()
    {
        delete[] this->elements_;
        this->capacity_ = 0;
    }

    T const & Get(int index)
    {
        if (index < 0 || index >= this->capacity_)
        {
            throw "Invalid argument";
        }
        return this->elements_[index];
    }

    int GetCapacity() const noexcept
    {
        return this->capacity_;
    }

    void Set(int index, T const & value)
    {
        if (index < 0 || index >= this->capacity_)
        {
            throw "Invalid argument";
        }
        this->elements_[index] = value;
    }

    void ReCapacity(int newCapacity)
    {
        if (newCapacity < 0)
        {
            throw "Invalid argument";
        }
        T* newElements = new T[newCapacity];
        for (int i = 0; i < (this->capacity_ > newCapacity ? newCapacity : this->capacity_); i++)
        {
            newElements[i] = this->elements_[i];
        }
        delete[] this->elements_;
        this->elements_ = newElements;
        this->capacity_ = newCapacity;
    }

    T &operator[] (int index)
    {
        if (capacity_ <= index)
        {
            throw "Invalid argument";
        }
        return elements_[index];
    }
    void DeleteElement(int index)
    {
        if(index >= capacity_ || index < 0)
            throw "Invalid argument";
        int CurrentCapacity = capacity_ - 1;
        T* NewElements = new T[capacity_ - 1];

        for(int i = 0; i < index; i++)
        {
            NewElements[i] = this->operator[](i);
        }

        for(int i = index; i < (capacity_ - 1); i++)
        {
            NewElements[i] = this->operator[](i + 1);
        }

        this->~DynamicArray();

        this->elements_ = NewElements;
        this->capacity_ = CurrentCapacity;

    }
};

#endif
