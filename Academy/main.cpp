﻿#include <iostream>
#include <string>
using namespace std;

#define delimiter "\n--------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS   const string& last_name, const string& first_name, const unsigned int age
#define HUMAN_GIVE_PARAMETERS   last_name, first_name, age

class Human
{
	string last_name;
	string first_name;
	unsigned int age;
public:
	const string& get_last_name()const
	{
		return last_name;
	}
	const string& get_first_name()const
	{
		return first_name;
	}
	const unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(const unsigned int age)
	{
		this->age = age;
	}

	//      Constructors:

	/*Human()
	{
		this->first_name = "";
		this->last_name = "";
		this->age = 0;
		cout << "HDefaultConstructor:\t" << this << endl;
	}*/
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	//		   Methods:

	virtual void info()const
	{
		cout << last_name << " " << first_name << ", " << age << " y/o" << endl;
	}
};

#define STUDENT_TAKE_PARAMETERS const string& speciality, const string& group, const double rating, const double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student : public Human
{
	string speciality;
	string group;
	double rating;
	double attendance;
public:
	const string& get_spetiality()const
	{
		return speciality;
	}
	const string& get_group()const
	{
		return group;
	}
	const double& get_rating()const
	{
		return rating;
	}
	const double& get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const string& group)
	{
		this->group = group;
	}
	void set_rating(const double& rating)
	{
		this->rating = rating;
	}
	void set_attendance(const double& attendance)
	{
		this->attendance = attendance;
	}

	//	      Constructors:

	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//	      Methods:

	void info()const override //переопределить
	{
		Human::info();
		cout << speciality << ", " << group << ", " << rating << ", " << attendance << endl;
	}
};

class Teacher : public Human
{
	string speciality;
	unsigned int experience;
public:
	const string& get_speciality()const
	{
		return speciality;
	}
	const unsigned int get_experience()const
	{
		return experience;
	}
	void set_speciality(const string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(const unsigned int experience)
	{
		this->experience = experience;
	}

	//			Constructors:

	Teacher
	(
		HUMAN_TAKE_PARAMETERS,
		const string& speciality, const unsigned int experience
	) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//			Methods:

	void info()const
	{
		Human::info();
		cout << speciality << ", " << experience << " years" << endl;
	}
};

//#define INHERITANCE_CHECK

int main()
{
	setlocale(LC_ALL, "");
#ifdef INHERITANCE_CHECK
	Human human("Ivanov", "Ivan", 25);
	human.info();

	Student student("Novikova", "Olga", 38, "College", "A", 5.0, 5.0); // no default constructor exists
	student.info();

	Teacher teacher("White", "Walter", 54, "Chemistry", 25);
	teacher.info();
#endif // INHERITANCE_CHECK
	
	//	Generalization:
	Human* group[] =
	{
		new Student("Novikova", "Olga", 38, "College", "A", 5.0, 5.0),
		new Teacher("White", "Walter", 54, "Chemistry", 25),
		new Student("Ivanov", "Ivan", 25, "Math", "5 B", 97, 98)
	};

	cout << delimiter << endl;
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		group[i]->info();
		cout << delimiter << endl;
	}
}