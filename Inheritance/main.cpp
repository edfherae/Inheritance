#include <iostream>
using namespace std;

class Human
{
    string last_name;
    string first_name;
    unsigned int age;
public:
    void set_age(unsigned int age)
    {
        this->age = age;
    }
};

class Student : Human
{

};

int main()
{
    Student Oleg;
    Oleg.set_age(22);
}