#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string> 
#include <fstream>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS   const string& last_name, const string& first_name, const unsigned int age
#define HUMAN_GIVE_PARAMETERS   last_name, first_name, age

enum human_type_by_parameters
{
	tHuman = 3,
	tStudent = 4 + tHuman,
	tTeacher = 2 + tHuman,
	tGraduate = 1 + tStudent
};

class Human
{
	static const int HUMAN_TYPE_WIDTH = 15;
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 5;

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
	virtual ostream& info(ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age << " y/o ";
	}
	virtual string data()const
	{
		char* buffer = new char[32] {};
		return string(this->last_name + " " + this->first_name + ", " + _itoa(this->age, buffer, 10) + ". ");
	}
	virtual std::ofstream& write(ofstream& ofs)const
	{
		//ofs << strchr(typeid(*this).name(), ' ') + 1 << ":\t" << last_name << " " << first_name << " " << age;
		ofs.width(HUMAN_TYPE_WIDTH);ofs << left << string(strchr(typeid(*this).name(), ' ') + 1) + ":";
		ofs.width(LAST_NAME_WIDTH);	ofs << left << last_name;
		ofs.width(FIRST_NAME_WIDTH);ofs << left << first_name;
		ofs.width(AGE_WIDTH);		ofs << left << age;
		return ofs;
	}
	virtual ifstream& read(ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}
ofstream& operator<<(ofstream& ofs, const Human& obj)
{
	return obj.write(ofs);
}
ifstream& operator>>(ifstream& is, Human& obj)
{
	return obj.read(is);
}

#define STUDENT_TAKE_PARAMETERS const string& speciality, const string& group, const double rating, const double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student : public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int GROUP_WIDTH = 25;
	static const int RATING_WIDTH = 8;
	static const int ATTENDANCE_WIDTH = 8;

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
	ostream& info(ostream& os)const override
	{
		return Human::info(os) << speciality << " " << group << " " << rating << " " << attendance;
	}
	ofstream& write(ofstream& ofs)const override
	{
		Human::write(ofs);
		ofs.width(SPECIALITY_WIDTH); ofs << speciality;
		ofs.width(GROUP_WIDTH);		 ofs << group;
		ofs.width(RATING_WIDTH);	 ofs << rating;
		ofs.width(ATTENDANCE_WIDTH); ofs << attendance;
		return ofs;
	}
	ifstream& read(ifstream& ifs)override
	{
		Human::read(ifs);
		//char symbol;
		//string buffer;
		//for (int i = 0; i < SPECIALITY_WIDTH /*buffer[i] != ' '*/; i++)
		//{
		//	ifs.get(symbol);
		//	buffer += symbol;
		//}
		//speciality = buffer;
		//ifs >> group >> rating >> attendance;
		char buffer[SPECIALITY_WIDTH]{};
		ifs.read(buffer, SPECIALITY_WIDTH);
		for (int i = SPECIALITY_WIDTH - 1; buffer[i] == ' '; i--)buffer[i] = 0; /*если buffer[i] == " " кавычки, то сравниваются адреса*/
		while (buffer[0] == ' ')for (int i = 0; buffer[i]; i++)buffer[i] = buffer[i + 1];
		this->speciality = buffer;
		ifs >> group >> rating >> attendance;
		return ifs;
	}
};

class Teacher : public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int EXPERIENCE_WIDTH = 5;

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
	ostream& info(ostream& os)const override
	{
		return Human::info(os) << speciality << " " << experience << " years";
	}
	ofstream& write(ofstream& ofs)const override
	{
		Human::write(ofs);
		ofs.width(SPECIALITY_WIDTH); ofs << speciality;
		ofs.width(EXPERIENCE_WIDTH); ofs << experience;
		return ofs;
	}
	ifstream& read(ifstream& ifs)override
	{
		Human::read(ifs);
		//ifs >> speciality >> experience;
		const int SIZE = SPECIALITY_WIDTH;
		char buffer[SIZE] {};
		ifs.read(buffer, SIZE); //f12, передаем char*
		int pos = strrchr(buffer, ' ') - buffer; //нашли, где находится 0 (?) 
												 //strrchr (string reverse character) - находит последнее вхождение указанного символа в указанной строке, strR - reverse
		//buffer[pos] = 0;
		for (int i = SIZE - 1; buffer[i] == ' '; i--)buffer[i] = 0; //0 и есть детерминирующий ноль
		while (buffer[0] == ' ')
		{
			for (int i = 0; buffer[i]; i++)buffer[i] = buffer[i + 1]; //циклический сдвиг массива, двигаем массив, пока не затрём пробел
		}
		this->speciality = buffer;
		ifs >> experience;
		return ifs;
	}
};

class Graduate : public Student
{
	static const int SUBJECT_WIDTH = 32;

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
	ostream& info(ostream& os)const override
	{
		return Student::info(os) << " " << subject;
	}
	ofstream& write(ofstream& ofs)const override
	{
		Student::write(ofs);
		ofs.width(SUBJECT_WIDTH); ofs << subject;
		return ofs;
	}
	ifstream& read(ifstream& ifs)override
	{
		Student::read(ifs);
		getline(ifs, subject);
		return ifs;
	}
};

void Save(Human* group[], const int size, const string& path)
{
	ofstream fout(path);
	if (!fout.is_open())
		cout << "Ошибка открытия файла" << endl;
	else
	{
		cout << delimiter << endl;
		for (int i = 0; i < size; i++)
		{
			//group[i]->info();
			//cout << *group[i] << endl;
			//fout << group[i]->info() << endl;
			fout << *group[i] << endl;
			cout << delimiter << endl;
		}
	}
	fout.close();
	string cmd = "notepad " + path;
	system(cmd.c_str()); //метод c_str() возвращает содержимое объекта string в виде обычной C-string (NULL terminated line)
}
//void Load(const string& path, Human* group[], const int SIZE)
//{
//	ifstream fin;
//	fin.open(path);
//
//	//		1 способ: просто чтение из файла
//
//	/*string line;
//
//	if (!fin.is_open())
//		cout << "Ошибка открытия файла" << endl;
//	else
//	{
//		while (getline(fin, line))
//		{
//			cout << line << endl;
//		}
//	}
//	cout << delimiter << endl;*/
//
//	//		2 способ: создание объектов из данных в файле (данные нужно упорядочить, убрать y/o)
//
//	char* buffer = new char[264] {};
//	Human* obj = nullptr;
//	int human_count = 0;
//
//	for(int i = 0; i < SIZE; i++)
//	{
//		fin.getline(buffer, 264); //getline читает до "\n", разделители можно указать
//		string parameters[8];	//максимум параметров - 8, по количеству параметров определяется тип (уязвимо)
//								//очень чувствительно к ошибкам (трансформация типов, параметры должны быть на своем месте), поэтому load вызывать только после save
//		int n = 0;
//		const char delimiters[] = " ,.";
//		for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
//			parameters[n++] = pch;
//		for (int j = 0; j < n; j++) cout << parameters[j] << tab; cout << endl;
//
//		switch (n) //нечитаемо, доработать
//		{
//			//что будет, если существует два класса с одинаковым количеством переменных, кого куда тогда инициализировать?
//		case tHuman:
//			obj = new Human(parameters[0], parameters[1], stoi(parameters[2])); break;
//		case tTeacher:
//			obj = new Teacher(parameters[0], parameters[1], stoi(parameters[2]), parameters[3], stoi(parameters[4])); break;
//		case tStudent:
//			obj = new Student(parameters[0], parameters[1], stoi(parameters[2]), parameters[3], parameters[4], stod(parameters[5]), stod(parameters[6])); break;
//		case tGraduate:
//			obj = new Graduate(parameters[0], parameters[1], stoi(parameters[2]), parameters[3], parameters[4], stod(parameters[5]), stod(parameters[6]), parameters[7]); break;
//		default:
//			cout << "Нарушена структура данных (или это пустая строка)\n"; 
//			obj = new Human("", "", 0); //чтобы не было ошибок при использовании Print для null
//			break;
//		}
//		group[human_count++] = obj;
//		obj = nullptr;
//	}
//
//	delete[] buffer;
//	fin.close();
//}
Human* HumanFactory(const std::string& type)
{
	Human* human = nullptr;
	if (type == "Human:") human = new Human("", "", 0);
	if (type == "Student:") human = new Student("", "", 0, "", "", 0, 0);
	if (type == "Teacher:") human = new Teacher("", "", 0, "", 0);
	if (type == "Graduate:") human = new Graduate("", "", 0, "", "", 0, 0, "");
	return human;
}
Human** Load(const string& filename, int& n)
{
	Human** group = nullptr;
	ifstream fin(filename);

	cout << fin.tellg() << endl;
	if (fin.is_open())
	{
		//1) считаем количество объектов, оно точно соответствует количеству не пумтых строк в файле
		n = 0;
		while (!fin.eof())
		{
			//const int SIZE = 256;
			//char* buffer[SIZE] {}; //статический массив на SIZE элементов
			//fin.getline(buffer, size); //for NULL-terminated lines (C-Strings - char arrays)

			string buffer;
			getline(fin, buffer);		 //for string global function getline(stream, string) used;
			if (buffer.size() < 16)continue;
			n++;
		}
		cout << "Количество строк в файле: " << n << endl;

		//2) выделяем память под массив
		group = new Human*[n] {};

		//3) Возвращаемся в начало файла
		cout << fin.tellg() << endl;
		fin.clear();  //clear() resets the error flags on a stream(as you can read in the documentation).If you use formatted extraction, then the error flag "fail" will be set if an extraction fails(e.g. if you're trying to read an integer and there isn't anything parsable).So if you're using the error state to terminate the loop, you have to make the stream usable again before going into the next loop.
					  //https://stackoverflow.com/questions/8079333/what-does-clear-do
		fin.seekg(0); // изменение позиции курсора с -1 на 0
		cout << fin.tellg() << endl;

		//4)  выполняем чтение объектов

		for (int i = 0; i < n; i++)
		{
			string type;
			cout << fin.tellg() << endl;
			fin >> type;
			cout << fin.tellg() << endl; //tellg - позиция в файле, не в строке
			group[i] = HumanFactory(type);
			if (group[i])fin >> *group[i];
			else continue;
		}

		fin.close();
	}
	else
		cerr << "Error: File not found!" << endl;

	return group;
}
void Print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
		cout << *group[i] << endl << delimiter << endl;
}
void Clear(Human* group[], const int n) //не работает sizeof, тк передается указатель, а не статический массив
{
	for (int i = 0; i < n; i++)
		delete group[i];
}

//#define INHERITANCE_CHECK
//#define POLYMORPHISM

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
	
#ifdef POLYMORPHISM
	//int* arr = new int[3] {1, 2, 3}; //про указатель на group

//Human human("Ivanov", "Ivan", 25);
//cout << sizeof(human.age) << " " << sizeof(2500000000000000000) << delimiter;

//	Generalization:
	Human* group[] =
	{
		new Human("Ivanov", "Ivan", 25),
		new Student("Novikova", "Olga", 38, "College", "A", 5.0, 5.0),
		new Teacher("White", "Walter", 54, "Chemistry", 25),
		new Student("Ivanov", "Ivan", 25, "Math", "5-в", 97, 98),
		new Graduate("Алексеевна" , "София", 14, "International_languages", "Alone", 99, 99, "Government_management")
	};

	string path = "class.txt";
	//cin >> path;

	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), path);

	//const int SIZE = 5; //количество объектов, записанных в файл
	//Human* group2[SIZE];
	//Load(path, group2, SIZE);
	//Print(group2, sizeof(group2) / sizeof(group2[0]));
	Clear(group, sizeof(group) / sizeof(group[0]));
	//Clear(group2, sizeof(group2) / sizeof(group2[0]));  
#endif // POLYMORPHISM

	int size = 0;
	Human** group = Load("class.txt", size);
	Print(group, size);
	Clear(group, size);
}