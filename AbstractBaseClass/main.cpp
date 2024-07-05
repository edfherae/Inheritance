#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

enum tFigure
{
	tCircle = 0,
	tSquare = 1,
	tTriangle = 2,
	tRectangle = 3
};

class Figure
{
public:
	virtual void print()const = 0;
	virtual void draw()const = 0;
	//virtual void initialize() = 0;
	//virtual Figure initialize
};
class Circle : public Figure
{
	int radius;
public:
	Circle(int radius = 0)
	{
		this->radius = radius;
		cout << "DefaultConstructor\t" << this << endl;
	}
	//void initialize(int radius = rand() % 10) override
	void initialize(int radius = rand() % 10)
	{
		this->radius = radius;
	}
	void print()const override
	{
		cout << "Радиус круга: " << radius << endl;
		cout << "Периметр: " << 2 * M_PI * radius << endl;
		cout << "Площадь: " << M_PI * radius * radius << endl;
	}
	void draw()const override
	{

	}
};
class Square : public Figure
{
	int a;
public:
	Square(int a = 0)
	{
		this->a = a;
		cout << "DefaultConstructor\t" << this << endl;
	}
	void initialize(int a = rand() % 10)
	{
		this->a = a;
	}
	void print()const override
	{
		cout << "Длина стороны квадрата: " << a << endl;
		cout << "Периметр: " << a * 4 << endl;
		cout << "Площадь: " << a * a << endl;
	}
	void draw()const override
	{

	}
};
class Triangle : public Figure
{
	int a, b, c;
public:
	Triangle(int a = 0, int b = 0, int c = 0)
	{
		this->a = this->b = this->c = 0;
		cout << "DefaultConstructor\t" << this << endl;
	}
	void initialize(int a = rand() % 100, int b = rand() % 100, int c = rand() % 100)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	void print()const override
	{
		cout << "Длина сторон треугольника:\na = " << a << "\tb = " << b << "\tc = " << c << endl;
		cout << "Периметр: " << a + b + c << endl;
		cout << "Площадь: " << sqrt(sp() * (sp() - a) * (sp() - b) * (sp() - c)) << endl;
	}
	void draw()const override
	{

	}
	double sp()const //semiperimeter
	{
		return (a + b + c) / 2;
	}
};
class Rectangle : public Figure //: public Square
{
	int a;
	int b;
public:
	Rectangle(int a = 0, int b = 0)
	{
		this->a = a;
		this->b = b;
		cout << "DefaultConstructor\t" << this << endl;
	}
	void initialize(int a = rand() % 10, int b = rand() % 10)
	{
		this->a = a;
		this->b = b;
	}
	void print()const override
	{
		cout << "Длина сторон прямоугольника:\na = " << a << "\tb = " << b << endl;
		cout << "Периметр: " << a * 2 + b * 2 << endl;
		cout << "Площадь: " << a * b << endl;
	}
	void draw()const override
	{

	}
};

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{

		switch (rand() % 5) 
		{
		case tCircle:
			{
				Circle temp; //initialization of 'temp' is skipped by 'case' label
				temp.initialize();
				temp.print();
				break;
			}
		case tSquare:
			{
				Square temp;
				temp.initialize();
				temp.print();
				break;
			}
		case tTriangle:
			{
				Triangle temp;
				temp.initialize();
				temp.print();
				break;
			}
		case tRectangle:
			{
				Rectangle temp;
				temp.initialize();
				temp.print();
				break;
			}
		}
	}
}