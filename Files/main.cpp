#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

//#define WRITE_TO_FILE //ctrl - shift - u
#define READ_TO_FILE

int main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	std::ofstream fout;				 //1) создаем поток
	fout.open("file.txt", std::ios_base::app);			 //2) открываем поток
	//app - аppend - дописать в конец файла
	time_t now = time(NULL);
	fout << ctime(&now) << "Hello World!" << endl;  //3) пишем в поток
	fout << ctime(&now) << "Сам привет!\n";
	fout.close();					 //4) закрываем поток
	//После открытия, потоки обязательно нужно закрывать
	system("notepad file.txt");
#endif // WRITE_TO_FILE
	std::ifstream fin("file.txt");
	if (fin.is_open())
	{
		const int SIZE = 256; //размер буффера
		char buffer[SIZE]{};

		while (!fin.eof()) //not end of file
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}

		fin.close();
	}
	else
		cout << "File not found!" << endl;
}