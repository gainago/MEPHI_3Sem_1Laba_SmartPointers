#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T>
class LinkedList
{
private:
    int size;
    class Node
    {
    public:
        Node *pNext;
        T data;

        Node(T data = T(), Node *pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }
    };
    Node *head;

public:
    LinkedList()
    {
        this->size = 0;
        this->head = nullptr;
    }

    LinkedList(T* items, int count) : LinkedList()
    {
        if (count < 0 || items == nullptr)
        {
            throw "Invalid argument";
        }
        for (int i = 0; i < count; i++)
        {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &list) : LinkedList()
    {
        Node *current = list.head;
        for (int i = 0; i < list.size; i++)
        {
            Append(current->data);
            current = current->pNext;
        }
        this->size = list.size;
    }

    ~LinkedList()
    {
        Node *current = this->head;
        Node *next;
        while (current != nullptr)
        {
            next = current->pNext;
            delete current;
            current = next;
        }
        this->size = 0;
    }

    T const & GetFirst()
    {
        if (this->head == nullptr)
        {
            throw "Index out of range";
        }
        return this->head->data;
    }

    T const &GetLast()
    {
        Node *current = this->head;
        if (this->head == nullptr)
        {
            throw "Index out of range";
        }
        for (int i = 0; i < this->size - 1; i++)
        {
            current = current->pNext;
        }
        return current->data;
    }

    T const & Get(int index)
    {
        Node *current = this->head;
        if (index < 0 || index >= this->size)
        {
            throw "Invalid argument";
        }
        for (int i = 0; i < index; i++)
        {
            current = current->pNext;
        }
        return current->data;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex)
    {
        if (startIndex < 0 || endIndex < 0 || endIndex >= this->size || endIndex < startIndex)
        {
            throw "Invalid argument";
        }
        LinkedList<T> *resultList = new LinkedList<T>();
        for (int i = startIndex; i <= endIndex; i++)
        {
            resultList->Append(this->Get(i));
        }
        return resultList;
    }

    int GetLength()
    {
        return this->size;
    }

    void Append(T item)
    {
        if (this->head == nullptr)
        {
            this->head = new Node(item);
        }
        else
        {
            Node *current = this->head;
            for (int i = 1; i < this->size; i++)
            {
                current = current->pNext;
            }
            current->pNext = new Node(item);
        }
        this->size++;
    }

    void Prepend(T item)
    {
        Node *newHead = new Node(item, this->head);
        this->head = newHead;
        this->size++;
    }

    void InsertAt(T item, int index)
    {
        if (index < 0 || index >= this->size)
        {
            throw "Invalid argument";
        }
        Node *newElement = new Node(item);
        Node *current = this->head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->pNext;
        }
        newElement->pNext = current->pNext;
        current->pNext = newElement;
        this->size++;
    }

    LinkedList<T>* Concat(LinkedList<T> &list)
    {
        LinkedList<T> *resultList = new LinkedList<T>();
        for (int i = 0; i < this->size; i++)
        {
            resultList->Append(this->Get(i));
        }
        for (int i = 0; i < list.size; i++)
        {
            resultList->Append(list.Get(i));
        }
        return resultList;
    }

    T &operator[] (int index)
    {
        if (index > this->size || index < 0)
        {
            throw "Invalid argument";
        }
        Node *result = this->head;
        for (int i = 0; i < index; i++)
        {
            result = result->pNext;
        }
        return result->data;
    }
};

#endif