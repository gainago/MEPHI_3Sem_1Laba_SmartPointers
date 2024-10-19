#ifndef MY_STRING_H
#define MY_STRING_H
#include <iostream>
class MyString
{
private:

    friend class UIClassInt;

    char* str;
    int length;
public:
    MyString();

    MyString(const char* str);

    ~MyString();

    int StrLen(const char* symbols) const;

    void StrCopy(char *dest, const char* src);

    MyString(const MyString& other);

    MyString& operator=(const MyString& other);

    MyString operator+(const MyString& other);

    friend std::ostream &operator<<(std::ostream &out, const MyString& myString);

    friend std::istream &operator>>(std::istream &in, MyString& myString);

    int GetLength() const;

    bool operator==(const MyString& other) const;

    bool operator!=(const MyString& other);

    char& operator [](int index);

    MyString(MyString&& other);
};
std::ostream &operator<<(std::ostream &out, const MyString& myString);
std::istream &operator>>(std::istream &in, MyString& myString);
#endif
