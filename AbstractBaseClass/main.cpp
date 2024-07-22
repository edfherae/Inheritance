#include "stdafx.h"
#include "Geometry.h"


int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	//Shape shape(Color::CONSOLE_BLUE);
	Geometry::Square square(50, 250, 50, 5, Geometry::Color::BLUE);
	square.info();

	Geometry::Rectangle rect(50, 100, 325, 50, 3, Geometry::Color::GREEN);
	rect.info();

	Geometry::Circle circle(1, 400, 50, 1, Geometry::Color::YELLOW);
	circle.info();

	Geometry::EquilateralTriangle eqTriangle(100, 500, 50, 1, Geometry::Color::RED);
	eqTriangle.info();

	Geometry::IsoscelesTriangle isTriangle(150, 100, 600, 50, 3, Geometry::Color::GREEN);
	isTriangle.info();

	Geometry::RightTriangle rTriangle(30, 100, 700, 50, 3, Geometry::Color::BLUE);
	rTriangle.info();

	cout << "Количество фигур: " << Geometry::Shape::get_count() << endl;
	
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