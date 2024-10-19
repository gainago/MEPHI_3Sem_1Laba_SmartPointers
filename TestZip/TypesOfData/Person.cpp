#include "MyString.h"
#include <iostream>
#include "Person.h"


    Person::Person() : id(""), firstName(""), middleName(""), lastName("") {}

    Person::Person(PersonID id, MyString firstName, MyString middleName, MyString lastName)
    {
        this->id = id;
        this->firstName = firstName;
        this->middleName = middleName;
        this->lastName = lastName;
    }

    Person::Person(const Person &person)
    {
        this->id = person.id;
        this->firstName = person.firstName;
        this->middleName = person.middleName;
        this->lastName = person.lastName;
    }

    MyString Person::GetId()
    {
        return this->id;
    }

    MyString Person::GetFirstName()
    {
        return this->firstName;
    }

    MyString Person::GetMiddleName()
    {
        return this->middleName;
    }

    MyString Person::GetLastName()
    {
        return this->lastName;
    }

     std::istream & operator>>(std::istream &in, Person &person)
    {
        std::cout << "Enter first name: " << std::endl;
        in >> person.firstName;
        std::cout << "Enter middle name: " << std::endl;
        in >> person.middleName;
        std::cout << "Enter last name: " << std::endl;
        in >> person.lastName;
        std::cout << "Enter id: " << std:: endl;
        in >> person.id;
        return in;
    }

    std::ostream & operator<<(std::ostream &out, const Person &person)
    {
        return out << "Person with " << person.id << " id: " << person.firstName << " " << person.middleName << " " << person.lastName << std::endl;
    }

    bool Person::operator==(Person man)
    {
        return ((id == man.GetId()) && (middleName == man.GetMiddleName()) && (firstName == man.GetFirstName()) &&
            (lastName == man.GetLastName()));
    }

    Person::~Person()
    {
        id.~MyString();
        firstName.~MyString();
        middleName.~MyString();
        lastName.~MyString();
    }

