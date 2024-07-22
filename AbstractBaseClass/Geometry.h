#pragma once
#include "stdafx.h"

namespace Geometry
{
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
		RED = 0x000000FF,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		YELLOW = 0x0000FFFF,

		CONSOLE_BLUE = 0x99, //один байт пытаемся растянуть на 4, этот байт стекается в red
		CONSOLE_GREEN = 0xAA,
		CONSOLE_RED = 0xCC,
		CONSOLE_DEFAULT = 0x07
	};
#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	class Shape
	{
	protected:	//защищенные поля, доступны только внутри класса и внутри его дочерних классов
		Color color;
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		/////////////////////////////////////////////////////////////////////////
		static const int MIN_START_X = 100;
		static const int MAX_START_X = 1000;
		static const int MIN_START_Y = 100;
		static const int MAX_START_Y = 500;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 550;
		static int count;
	public:
		Shape(SHAPE_TAKE_PARAMETERS) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
			count++;
		};
		virtual ~Shape() { count--; };

		Color get_color()const { return color; }
		unsigned int get_start_x()const { return start_x; }
		unsigned int get_start_y()const { return start_y; }
		unsigned int get_line_width()const { return line_width; }
		void set_color(Color color) { this->color = color; }
		void set_start_x(unsigned int start_x)
		{
			//this->start_x = start_x > GetSystemMetrics(SM_CXSCREEN) ? 100 : start_x; 
			if (start_x < MIN_START_X)start_x = MIN_START_X;
			if (start_x > MAX_START_X)start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			//this->start_y = start_y > GetSystemMetrics(SM_CYSCREEN) ? 100 : start_y; 
			if (start_y < MIN_START_Y)start_y = MIN_START_Y;
			if (start_y > MAX_START_Y)start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			//this->line_width = line_width > 5 ? 5 : line_width; 
			if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}
		double filter_size(double size)
		{
			if (size < MIN_SIZE)size = MIN_SIZE;
			if (size > MAX_SIZE)size = MAX_SIZE;
			return size;
		}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			cout << "Площадь фигуры: " << get_area() << endl;
			draw();
		}
		static int get_count() { return count; }
	};
	int Shape::count = 0;

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
		void set_width(double width) { this->width = filter_size(width); }
		void set_height(double height) { this->height = filter_size(height); }

		void draw()const override
		{
			//HWND hwnd = FindWindow(NULL, "Inheritance - Microsoft Visual Studio");

			//HWND hwnd = FindWindow(NULL, /*L*/"Inheritance - Microsoft Visual Studio");
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
		Circle(double radius, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}

		double get_radius()const { return radius; }
		double get_diameter()const { return 2 * radius; }
		void set_radius(double radius) { this->radius = filter_size(radius); }
		double get_area()const override { return M_PI * radius * radius; }
		double get_perimeter()const override { return 2 * M_PI * radius; }
		void draw()const override
		{
			//HWND hwnd = FindWindow(NULL, /*L*/"Inheritance - Microsoft Visual Studio");
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
		void info()const override
		{
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
	class EquilateralTriangle : public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}

		double get_side()const { return side; }
		double get_height()const override { return sqrt(side * side - side / 2 * side / 2); }
		void set_side(double side) { this->side = filter_size(side); }
		double get_area()const override { return side / 2 * get_height(); }
		double get_perimeter()const override { return side * 3; }
		void draw()const override
		{
			//HWND hwnd = FindWindow(NULL, /*L*/"Inheritance - Microsoft Visual Studio");
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
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
			Triangle::info();
		}
	};
	class IsoscelesTriangle : public Triangle //Каждый правильный треугольник также является равнобедренным, по-хорошему, нужно наследовать от EquilateralTriangle
	{
		double sides;
		double base;
	public:
		IsoscelesTriangle(double sides, double base, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_sides(sides), set_base(base);
		}
		~IsoscelesTriangle() {}

		double get_sides()const { return sides; }
		double get_base()const { return base; }
		void set_sides(double side) { this->sides = filter_size(side); }
		void set_base(double base) { this->base = filter_size(base); }

		double get_height()const override { return sqrt(sides * sides - base / 2 * base / 2); }
		double get_area()const override { return base / 2 * get_height(); }
		double get_perimeter()const override { return sides * 2 + base; }
		void draw()const override
		{
			//HWND hwnd = FindWindow(NULL, /*L*/"Inheritance - Microsoft Visual Studio");
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] =
			{
				{start_x, start_y + base},
				{start_x + base, start_y + base},
				{start_x + base / 2, start_y + base - get_height()}
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
			Triangle::info();
		}
	};
	class RightTriangle : public Triangle
	{
		double cathetus1, cathetus2, hypotenuse;
	public:
		RightTriangle(double cathetus1, double cathetus2, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_cathetus1(cathetus1), set_cathetus2(cathetus2);
			this->hypotenuse = sqrt(get_cathetus1() * get_cathetus1() + get_cathetus2() * get_cathetus2());
		}
		~RightTriangle() {}

		double get_cathetus1()const { return cathetus1; }
		double get_cathetus2()const { return cathetus2; }
		double get_hypotenuse()const { return hypotenuse; }
		void set_cathetus1(double cathetus1) { this->cathetus1 = filter_size(cathetus1); }
		void set_cathetus2(double cathetus2) { this->cathetus2 = filter_size(cathetus2); }
		void set_hypotenuse(double hypotenuse) { this->hypotenuse = filter_size(hypotenuse); }

		double get_area()const override { return cathetus1 * cathetus2 / 2; }
		double get_perimeter()const override { return cathetus1 + cathetus2 + hypotenuse; }
		double get_height()const override { return cathetus1 * cathetus2 / hypotenuse; }
		void draw()const override
		{
			//HWND hwnd = FindWindow(NULL, /*L*/"Inheritance - Microsoft Visual Studio");
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			COLORREF color = get_color();
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);

			POINT apt[] =
			{
				{start_x, start_y},
				{start_x, start_y + cathetus1},
				{start_x + cathetus2, start_y + cathetus1}
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
			Triangle::info();
		}
	};
}