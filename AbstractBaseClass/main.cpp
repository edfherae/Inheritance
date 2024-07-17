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
		void set_start_x(unsigned int start_x) { this->start_x = start_x; }
		void set_start_y(unsigned int start_y) { this->start_y = start_y; }
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
			HWND hwnd = GetConsoleWindow();	//1) Получаем дескриптор окна консоли.
			//description
			//HWND - Handler to Window (Обработчик (Дескриптор) окна)
			HDC hdc = GetDC(hwnd);			//2) Получаем констукст устройства (Device Context) окна консоли.
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
			::Ellipse(hdc, start_x, start_y, start_x + radius, start_y + radius);
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
	//class Triangle : public Shape
	//{
	//	int a, b, c;
	//public:
	//	Triangle(int a = 0, int b = 0, int c = 0)
	//	{
	//		this->a = this->b = this->c = 0;
	//		cout << "DefaultConstructor\t" << this << endl;
	//	}
	//	void initialize(int a = rand() % 100, int b = rand() % 100, int c = rand() % 100)
	//	{
	//		this->a = a;
	//		this->b = b;
	//		this->c = c;
	//	}
	//	void print()const override
	//	{
	//		cout << "Длина сторон треугольника:\na = " << a << "\tb = " << b << "\tc = " << c << endl;
	//		cout << "Периметр: " << a + b + c << endl;
	//		cout << "Площадь: " << sqrt(sp() * (sp() - a) * (sp() - b) * (sp() - c)) << endl;
	//	}
	//	void draw()const override
	//	{
	//
	//	}
	//	double sp()const //semiperimeter
	//	{
	//		return (a + b + c) / 2;
	//	}
	//};

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

	Geometry::Rectangle rect(150, 80, 350, 50, 5,  Color::GREEN);
	rect.info();

	Geometry::Circle circle(80, 550, 50, 5, Color::YELLOW);
	circle.info();

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