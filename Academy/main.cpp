#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string> 
#include <fstream>
using namespace std;

#define tab "\t"
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
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	//		   Methods:

	virtual void info()const
	{
		cout << last_name << " " << first_name << ", " << age << " y/o" << endl;
	}
	virtual string data()const
	{
		char* buffer = new char[32] {};
		return string(this->last_name + " " + this->first_name + ", " + _itoa(this->age, buffer, 10) + ". ");
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
	~Student() override
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//	      Methods:

	void info()const override //переопределить
	{
		Human::info();
		cout << speciality << ", " << group << ", " << rating << ", " << attendance << endl;
	}
	string data()const override
	{
		char* buffer = new char[32] {};
		return string(Human::data() + this->speciality + ", " + this->group + ", " + _itoa(this->rating, buffer, 10) + ", " + _itoa(this->attendance, buffer, 10));
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
	~Teacher() override
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//			Operators:
	//std::ostream& operator<<(std::ostream& os, Teacher obj)
	//std::ostream& operator<<(std::ostream& os)
	//{
	//	cout << speciality << ", " << experience << " years" << endl;
	//	return os;
	//}
	//			Methods:

	void info()const override
	{
		Human::info();
		cout << speciality << ", " << experience << " years" << endl;
	}
	string data()const override
	{
		char* buffer = new char[32] {};
		return string(Human::data() + this->speciality + ", " + _itoa(this->experience, buffer, 10));
	}
};

class Graduate : public Student
{
	string subject;
public:
	const string& get_subject()const
	{
		return subject;
	}
	void set_subject(const string& subject)
	{
		this->subject = subject;
	}
	//			Constructors:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const string& subject)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS) //student constr
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate() override
	{
		cout << "GDestructor:\t" << this << endl;
	}
	//			Methods:
	void info()const override //без const override не работает, просто с override ошибка
							  //т.к. const тоже засчитывается в прототип функции
							  //т.е, в обязательном порядке, при определении виртуальной функции, ко всем дочерним дописываем override
	{
		Student::info();
		cout << subject << endl;
	}
	string data()const override
	{
		char* buffer = new char[32] {};
		return string(Student::data() + ", " + this->subject);
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	obj.info();
	return os;
}

void save(const string& path, Human* group[], int size)
{
	ofstream fout;
	fout.open(path);
	if (!fout.is_open())
		cout << "Ошибка открытия файла" << endl;
	else
	{
		cout << delimiter << endl;
		for (int i = 0; i < size; i++)
		{
			//group[i]->info();
			cout << *group[i] << endl;
			fout << group[i]->data() << "." << endl;
			cout << delimiter << endl;
		}
	}
	fout.close();
}
void load(const string& path)
{
	//std::istream& operator>>(std::istream & is, Fraction & obj)

	//		1 способ: просто чтение из файла
	string line;
	ifstream fin;
	fin.open("class.txt");
	if (!fin.is_open())
		cout << "Ошибка открытия файла" << endl;
	else
	{
		while (getline(fin, line))
		{
			cout << line << endl;
		}
	}

	//		2 способ: создание объектов из данных в файле (данные нужно упорядочить, убрать y/o)

	const int SIZE = 64;
	//char buffer[SIZE]{};
	getline(fin, line);
	char* buffer = line.data();

	string parameters[8];
	int n = 0;
	const char delimiters[] = " ,.";
	for (char* pch = strtok(line.c_str(), delimiters); pch; pch = strtok(NULL, delimiters))
		//функция strtok изменяет входную строку
		parameters[n++] = pch;
	for (int i = 0; i < n; i++) cout << parameters[i] << tab; cout << endl;

	/*switch (n)
	{
	case 1: obj = Fraction(number[0]); break;
	case 2: obj = Fraction(number[0], number[1]); break;
	case 3: obj = Fraction(number[0], number[1], number[2]); break;
	}*/

	fin.close();
}

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
	//int* arr = new int[3] {1, 2, 3}; //про указатель на group
	//зачем использовать override, если ничего не меняется
	//если не объявлять метод info константным, он не отработает (виртуальность), но если объявить, то будет

	//Human human("Ivanov", "Ivan", 25);
	//Student student("Novikova", "Olga", 38, "College", "A", 5.0, 5.0);
	//cout << sizeof(human.age) << " " << sizeof(2500000000000000000) << delimiter;

	//	Generalization:
	Human* group[] =
	{
		new Student("Novikova", "Olga", 38, "College", "A", 5.0, 5.0),
		new Teacher("White", "Walter", 54, "Chemistry", 25),
		new Student("Ivanov", "Ivan", 25, "Math", "5-в", 97, 98),
		new Graduate("Алексеевна" , "София_Августа_Фредерика_Ангальт-Цербстская", 14, "International_languages", "Alone", 99, 99, "Government_management")
	};

	string path = "class.txt";
	//cin >> path;
	
	save(path, group, sizeof(group) / sizeof(group[0]));

	cout << delimiter;

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
		delete group[i];

	load(path);
}