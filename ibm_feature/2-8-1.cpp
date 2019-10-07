#include <iostream>
using namespace std;

class Person {
public:
    int hand;
    Person* all;
};

int main() 
{
    Person person;

    cout << sizeof(person.hand) << endl;
    cout << sizeof(person.all) << endl;
    cout << sizeof(Person::hand) << endl;
    cout << sizeof(Person::hand) << endl;
    return 0;
}