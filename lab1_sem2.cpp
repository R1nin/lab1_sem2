// lab1_sem2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <windows.h>
#include <cstdlib>

using namespace std;

int DayWeek(int Day, int Month, int Year);

bool LeapYear(int year);

int main(int args, char *argv[]) {


	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	setlocale(LC_ALL, "Russian");

	int user_month = 0, user_year = 0, num = 12;
	string ios{};

	int jan[9]{ 1,2,3,4,5,6,7,8,9 };

	ofstream calend;
	
	cout << "Select the mode of working with the file: ";
	cin >> ios;
	if (ios == "app")
		calend.open("calendar_app.txt", ios_base::app);
	else if (ios == "trunc")
		calend.open("calendar_trunc.txt", ios_base::trunc);
		
		do {
			cout << "Введите месяц: ";
			cin >> user_month;
		} while (user_month > 13);
		
		do {
			cout << "Ввведите год: ";
			cin >> user_year;
		} while ((user_year < 1500) && (user_year > 3000));
		
		cout << endl;
	

	// номер дня недели
	int NumOfDay;

	const char list_month[12][20]{ "January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December" };

	char list_days[7][3]{ "Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс" };

	const int week = 6, days = 7;
	int calendar[days][week]{};

	map <string, int> daysOfMonth {
		{"January", 31},
		{"February", 28},
		{"March", 31},
		{"April", 30},
		{"May", 31},
		{"June", 30},
		{"July", 31},
		{"August", 31},
		{"September", 30},
		{"October", 31},
		{"November", 30},
		{"December", 31}
	};

	cout << "\t\t" << user_year << endl;
	calend << "Entered year: " << user_year << endl;
	calend << "Entered month: " << user_month << endl;
 
	int count = 1;
	while (count <= 12) {

		NumOfDay = 0;

		// инициализация массива
		for (int i = 0; i < days; i++) {

			for (int j = 0; j < week; j++) {
				calendar[i][j] = 0;
			}
		}

		// поправка на февраль
		if (user_month == 2)
			daysOfMonth["February"] += LeapYear(user_year);

		int j = 0;

		for (int i = 1; i <= daysOfMonth[list_month[user_month - 1]]; i++) {

			NumOfDay = DayWeek(i, user_month, user_year);
			if (NumOfDay == 0)
				NumOfDay = 7;
			calendar[NumOfDay - 1][j] = i;
			if (NumOfDay == 7)
				j++;
		}
		cout << '\t' << '\t' << list_month[user_month - 1] << endl;
		calend << '\t' << '\t' << list_month[user_month - 1] << endl;
		// odd - even 
		cout << setw(20) << "Odd/Even1       2       1       2" << endl;
		calend << setw(20) << "Odd/Even1       2       1       2" << endl;
		
		for (int i = 0; i < 7; i++) {
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			if (i >= 5) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << list_days[i] << ' ';
				calend << list_days[i] << ' ';
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << list_days[i] << ' ';
				calend << list_days[i] << ' ';
			}
			for (int j = 0; j < 6; j++)

				if (calendar[i][j] == 0) {
					cout << ' ' << '\t';
					calend << ' ' << '\t';
				}
				else {
					if (i <= 4) {
						cout << calendar[i][j] << '\t';
						calend << calendar[i][j] << '\t';
					} else {
						//if (user_month == 1 && calendar[i][j] == )
						//выходные дни
						SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
						cout << calendar[i][j] << '\t';
						calend << calendar[i][j] << '\t';
					}
				}
			calend << endl;
			cout << endl;
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}

		count++;
		calend << endl;
		cout << endl;
		
		if (user_month == 12) {
			user_month = 0;
			user_year++;

			if (count == 12) {
				
				cout << endl << "\t\t" << user_year << endl;
				cout  << "\t" << "Happy New Year!!!" << endl << endl;

				calend << endl << "\t\t" << user_year << endl;
				calend << "\t" << "Happy New Year!!!" << endl << endl;
			}
			else {
				cout << endl;
				calend << endl;
			}
			
		}
		user_month++;
	}
	

	return 0;
}

int DayWeek(int Day, int Month, int Year) {

	int DaysInYears, AllDays, DaysInMonths, Weeks, DayWeek;

	if (Month < 3) {
		Month += 12;
		Year -= 1;
	}
	Month += 1;
	DaysInMonths = Month * 30.6;
	DaysInYears = Year * 365.25;
	AllDays = DaysInMonths + DaysInYears + Day - 114;
	Weeks = AllDays / 7;
	DayWeek = AllDays - Weeks * 7;
	return DayWeek;
}

bool LeapYear(int year) {
	if (year % 4 != 0)
		return false;
	else
		return true;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
