#include <iostream>
#include "MyString.h"

    MyString::MyString()
    {
        str = nullptr;
        length = 0;
    }

    MyString:: MyString(const char* str)
    {
        length = this->StrLen(str);
        this->str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            this->str[i] = str[i];
        }

        this->str[length] = '\0';

    }

    MyString::~MyString()
    {
        delete[] this->str;
        this->str = nullptr;
        this->length = 0;
    }

    int MyString::StrLen(const char* symbols) const
    {
        int size = 0;
        while (symbols[size] != '\0') {
            size++;
        }
        return size;
    }

    void MyString::StrCopy(char *dest, const char* src)
    {
        int i = 0;
        while (src[i] != '\0')
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    MyString::MyString(const MyString& other)
    {
        length = other.StrLen(other.str);
        this->str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            this->str[i] = other.str[i];
        }

        this->str[length] = '\0';
    }

    MyString& MyString::operator=(const MyString& other)
    {
        if(this->str == other.str)
            return *this;

        if (this->str != nullptr)
        {
            delete[] str;
        }

        length = other.StrLen(other.str);
        this->str = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            this->str[i] = other.str[i];
        }
        this->str[length] = '\0';
        return *this;
    }

    MyString MyString::operator+(const MyString& other)
    {
        MyString newStr;
        int thisLength = this->StrLen(this->str);
        int otherLength = other.StrLen(other.str);

        newStr.length = thisLength + otherLength;

        newStr.str = new char[thisLength + otherLength + 1];

        for (int i = 0; i < thisLength; i++)
        {
            newStr.str[i] = this->str[i];
        }

        for (int j = 0; j < otherLength; j++)
        {
            newStr.str[thisLength + j] = other.str[j];
        }

        newStr.str[thisLength + otherLength] = '\0';

        return newStr;
    }

     std::ostream & operator<<(std::ostream &out, const MyString& myString)
    {
        return out << myString.str;
    }

     std::istream & operator>>(std::istream &in, MyString& myString)
    {
        char buffer[1000];
        in >> buffer;
        myString.length = myString.StrLen(buffer);
        delete[] myString.str;
        myString.str = new char[myString.length + 1];
        myString.StrCopy(myString.str, buffer);
        return in;
    }

    int MyString::GetLength() const
    {
        return length;
    }

    bool MyString::operator==(const MyString& other) const
    {
        if (this->length != other.length)
        {
            return false;
        }

        for (int i = 0; i < this->length; i++)
        {
            if (this->str[i] != other.str[i])
            {
                return false;
            }
        }
        return true;
    }

    bool MyString::operator!=(const MyString& other)
    {
        return !(this->operator==(other));
    }

    char& MyString::operator [](int index)
    {
        return this->str[index];
    }

    MyString::MyString(MyString&& other)
    {
        this->length = other.length;
        this->str = other.str;
        other.str = nullptr;
    }


