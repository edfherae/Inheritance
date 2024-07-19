#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

enum tFigure
{
	tCircle = 0,
	tSquare = 1,
	tTriangle = 2,
	tRectangle = 3
};
enum Color
{
	//4 байта:
	//alpha blue green red
	RED		 = 0x000000FF,
	GREEN	 = 0x0000FF00,
	BLUE	 = 0x00FF0000,
	YELLOW	 = 0x0000FFFF,

	CONSOLE_BLUE = 0x99, //один байт пытаемся растянуть на 4, этот байт стекается в red
	CONSOLE_GREEN = 0xAA,
	CONSOLE_RED = 0xCC,
	CONSOLE_DEFAULT = 0x07
};

namespace Geometry
{
#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	class Shape
	{
	protected:	//защищенные поля, доступны только внутри класса и внутри его дочерних классов
		Color color;
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
	public:
		Shape(SHAPE_TAKE_PARAMETERS) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		};
		virtual ~Shape() {};

		Color get_color()const { return color; }
		unsigned int get_start_x()const { return start_x; }
		unsigned int get_start_y()const { return start_y; }
		unsigned int get_line_width()const { return line_width; }
		void set_color(Color color) { this->color = color; }
		void set_start_x(unsigned int start_x) { this->start_x = start_x > GetSystemMetrics(SM_CXSCREEN) ? 100 : start_x; }
		void set_start_y(unsigned int start_y) { this->start_y = start_y > GetSystemMetrics(SM_CYSCREEN) ? 100 : start_y; }
		void set_line_width(unsigned int line_width) { this->line_width = line_width; }

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			cout << "Площадь фигуры: " << get_area() << endl;
			draw();
		}
	};
	
	class Rectangle : public Shape //: public Square
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}

		double get_area()const override { return width * height; }
		double get_perimeter()const override { return (width + height) * 2; }
		double get_width()const { return width; }
		double get_height()const { return height; }
		void set_width(double width) { this->width = width; }
		void set_height(double height) { this->height = height; }

		void draw()const override
		{
			//HWND hwnd = FindWindow(NULL, "Inheritance - Microsoft Visual Studio");

			HWND hwnd = GetConsoleWindow();	//1) Получаем дескриптор окна консоли.
			//description
			//HWND - Handler to Window (Обработчик (Дескриптор) окна)
			HDC hdc = GetDC(hwnd);			//2) Получаем контекст устройства (Device Context) окна консоли.
			//	 DC - это то, на чем мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());	//3) Создаем карандаш. pen рисует контур фигуры.
			//PS_SOLID - сплошная линия
			//5 - толщина линии в пикселах

			HBRUSH hBrush = CreateSolidBrush(get_color());

			//5) Выбираем чем и на чем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольник:

			//::Rectangle(hdc, start_x, start_y, 800, 350);
			//start_x, start_y - координаты верхнего левого угла
			//800, 350 - координаты нижнего правого угла
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

			//7) Освобождаем ресурсы:
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << get_width() << endl;
			cout << "Высота: " << get_height() << endl;
			Shape::info();
		}
	};
	
	class Square : public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
		/*void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, get_color());
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
		}*/
	};
	class Circle : public Shape
	{
		double radius;
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) : radius(radius), Shape(SHAPE_GIVE_PARAMETERS) {}
		~Circle() {}

		double get_radius()const { return radius; }
		double get_diameter()const { return 2 * radius; }
		void set_radius(double radius) { this->radius = radius; }
		double get_area()const override { return M_PI * radius * radius; }
		double get_perimeter()const override { return 2 * M_PI * radius; }
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << radius << endl;
			Shape::info();
		}
	};
	class Triangle : public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS) {}
		~Triangle() {}
		virtual double get_height()const = 0;

		//Triangle(int a, int b, int c, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		//{
		//	this->a = a;
		//	this->b = b;
		//	this->c = c;
		//}
		//~Triangle() {}

		//double get_a()const { return a; }
		//double get_b()const { return b; }
		//double get_c()const { return c; }
		//void set_a(double a) { this->a = a; }
		//void set_b(double b) { this->b = b; }
		//void set_c(double c) { this->c = c; }

		//void initialize(int a = rand() % 100, int b = rand() % 100, int c = rand() % 100)
		//{
		//	this->a = a;
		//	this->b = b;
		//	this->c = c;
		//}
		//virtual double get_area()const override { return 0; }
		//virtual double get_perimeter()const override { return 0; }
		//void info()const override
		//{
		//	cout << typeid(this).name() << endl;
		//	cout << "Длина сторон: a = " << a << "\tb = " << b << "\tc = " << c << endl;
		//	Shape::info();
		//}
		//void draw()const override
		//{
		//	HWND hwnd = GetConsoleWindow();
		//	HDC hdc = GetDC(hwnd);
		//	HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());
		//	HBRUSH hBrush = CreateSolidBrush(get_color());
		//	SelectObject(hdc, hPen);
		//	SelectObject(hdc, hBrush);

		//	//::Polygon(hdc, )

		//	DeleteObject(hPen);
		//	DeleteObject(hBrush);
		//	ReleaseDC(hwnd, hdc);
		//}
		//double sp()const //semiperimeter
		//{
		//	return (a + b + c) / 2;
		//}
	};
	class EquilateralTriangle : public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS), side(side) {}
		~EquilateralTriangle() {}

		double get_side()const { return side; }
		double get_height()const override{ return sqrt(side * side - side / 2 * side / 2); }
		void set_side(double side) { this->side = side; }
		double get_area()const override { return side / 2 * get_height(); }
		double get_perimeter()const override { return side * 3; }
		void draw()const override 
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] =
			{
				{start_x + side / 1.2, start_y},
				{start_x, start_y + side / 2},
				{start_x + side, start_y + side}
			};

			::Polygon(hdc, apt, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина сторон = " << get_side() << endl;
			Shape::info();
		}
	};
	class IsoscelesTriangle : public Triangle //Каждый правильный треугольник также является равнобедренным, по-хорошему, нужно наследовать от EquilateralTriangle
	{
		double sides;
		double base;
	public:
		IsoscelesTriangle(double sides, double base, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS), sides(sides), base(base) {}
		~IsoscelesTriangle() {}

		double get_sides()const { return sides; }
		double get_base()const { return base; }
		void set_sides(double side) { this->sides = side; }
		void set_base(double base) { this->base = base; }

		double get_height()const override { return sqrt(sides * sides - base / 2 * base / 2); }
		double get_area()const override { return base / 2 * get_height(); }
		double get_perimeter()const override { return sides * 2 + base; }
		void draw()const override 
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] =
			{
				{start_x + base / 3.5, start_y},
				{start_x, start_y + sqrt(sides * sides - base / 2 * base / 2)},
				{start_x + sqrt(sides * sides - base / 2 * base / 2), start_y + sqrt(sides * sides - base / 2 * base / 2)}
			};

			::Polygon(hdc, apt, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override 
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина равных сторон = " << get_sides() << endl;
			cout << "Длина основания = " << get_base() << endl;
			Shape::info();
		}
	};
	class RightTriangle : public Triangle
	{
		double cathetus1, cathetus2, hypotenuse;
	public:
		RightTriangle(double cathetus1, double cathetus2, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS), cathetus1(cathetus1), cathetus2(cathetus2) 
		{ this->hypotenuse = sqrt(cathetus1 * cathetus1 + cathetus2 * cathetus2); }
		~RightTriangle() {}

		double get_cathetus1()const { return cathetus1; }
		double get_cathetus2()const { return cathetus2; }
		double get_hypotenuse()const { return hypotenuse; }
		void set_cathetus1(double cathetus1) { this->cathetus1 = cathetus1; }
		void set_cathetus2(double cathetus2) { this->cathetus2 = cathetus2; }
		void set_hypotenuse(double hypotenuse) { this->hypotenuse = hypotenuse; }

		double get_area()const override { return cathetus1 * cathetus2 / 2; }
		double get_perimeter()const override { return cathetus1 + cathetus2 + hypotenuse; }
		double get_height()const override { return cathetus1 * cathetus2 / hypotenuse; }
		void draw()const override 
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());

			POINT apt[] =
			{
				{start_x, start_y},
				{start_x, start_y + cathetus1 /*> cathetus2 ? cathetus1 : cathetus2*/},
				{start_x + cathetus1 /*> cathetus2 ? cathetus2 : cathetus1*/, start_y + cathetus1 /*> cathetus2 ? cathetus1 : cathetus2*/}
			};
			::Polygon(hdc, apt, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Катет 1: " << cathetus1 << endl;
			cout << "Катет 2: " << cathetus2 << endl;
			cout << "Гипотенуза: " << hypotenuse << endl;
			Shape::info();
		}
	};
}
int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	//Shape shape(Color::CONSOLE_BLUE);
	Geometry::Square square(50, 250, 50, 5, Color::BLUE);
	square.info();
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата:  " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/

	Geometry::Rectangle rect(150, 80, 350, 50, 3,  Color::GREEN);
	rect.info();

	Geometry::Circle circle(80, 550, 50, 5, Color::YELLOW);
	circle.info();

	Geometry::EquilateralTriangle eqTriangle(80, 350, 150, 3, Color::RED);
	eqTriangle.info();

	Geometry::IsoscelesTriangle isTriangle(80, 100, 350, 250, 3, Color::GREEN);
	isTriangle.info();

	Geometry::RightTriangle rTriangle(100, 60, 350, 320, 2, Color::BLUE);
	rTriangle.info();
	
	//Geometry::Triangle triangle(20, 30, 40, 750, 50, 5, Color::YELLOW);
	//triangle.info();

	//for (int i = 0; i < 5; i++)
	//{

	//	switch (rand() % 5) 
	//	{
	//	case tCircle:
	//		{
	//			Circle temp; //initialization of 'temp' is skipped by 'case' label
	//			temp.initialize();
	//			temp.print();
	//			break;
	//		}
	//	case tSquare:
	//		{
	//			Square temp;
	//			temp.initialize();
	//			temp.print();
	//			break;
	//		}
	//	case tTriangle:
	//		{
	//			Triangle temp;
	//			temp.initialize();
	//			temp.print();
	//			break;
	//		}
	//	case tRectangle:
	//		{
	//			Rectangle temp;
	//			temp.initialize();
	//			temp.print();
	//			break;
	//		}
	//	}
	//}
}