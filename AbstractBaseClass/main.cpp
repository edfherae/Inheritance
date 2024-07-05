#include <iostream>
using namespace std;

class Animal
{
public:
	virtual void sound() = 0;
};
class Cat : public Animal {};
class Tiger : public Cat
{
public:
	void sound() override
	{
		cout << "RRRRrrrr" << endl;
	}
};
class HomeCat : public Cat
{
public:
	void sound() override
	{
		cout << "Meow" << endl;
	}
};
int main()
{
	setlocale(LC_ALL, "");
	//Animal animal; //object of abstract class type is not allowed
	//Cat cat;
	Tiger tiger;
	tiger.sound();
	HomeCat homecat;
	homecat.sound();
}