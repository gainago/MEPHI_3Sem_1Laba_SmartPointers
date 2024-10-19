#ifndef PERSON_H
#define PERSON_H
#include "MyString.h"

typedef MyString PersonID;

class Person
{
private:
    PersonID id;
    MyString firstName;
    MyString middleName;
    MyString lastName;

public:
    Person();

    Person(PersonID id, MyString firstName, MyString middleName, MyString lastName);

    Person(const Person &person);

    MyString GetId();

    MyString GetFirstName();

    MyString GetMiddleName();

    MyString GetLastName();

    friend std::istream &operator>>(std::istream &in, Person &person);

    friend std::ostream &operator<<(std::ostream &out, const Person &person);

    bool operator==(Person man);

    ~Person();
};

#endif