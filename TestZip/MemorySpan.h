#ifndef MEMORY_SPAN_H
#define MEMORY_SPAN_H

#include "shared_ptr.h"
#include "unique_ptr.h"
#include "Sequence/ArraySequence.h"

template <typename Type>
class MemorySpan{

private:
    MutableArraySequence<Type> MutableArray;

public:
    MemorySpan(Type* Items, int Size) : MutableArray(Items, Size){}

    MemorySpan() : MutableArray() {}

    shared_ptr<Type> GetSharedPtr(size_t index)
    {
        return make_shared<Type>(MutableArray[index]);
    }//нельзя так возвращать 

};

#endif