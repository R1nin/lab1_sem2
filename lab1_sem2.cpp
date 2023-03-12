#include <iomanip>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <windows.h>
#include <cstdlib>
#include <stdlib.h>

using namespace std;
int DayWeek(int Day, int Month, int Year);
bool LeapYear(int year);

int main(int argc, char* argv[]) {

	do {

		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		setlocale(LC_ALL, "Russian");
		const int num = 12;
		int user_month = 0, user_year = 0, copy = 0;
		bool file = true;
		char filename[30];
		char* a;

		int jan[9]{ 1,2,3,4,5,6,7,8,9 };

		ofstream calend;

		if (argc == 1) {
			do {
				cout << "Enter month: ";
				cin >> user_month;
			} while (user_month > 13);

			do {
				cout << "Enter year: ";
				cin >> user_year;
			} while ((user_year < 1500) && (user_year > 3000));

			cout << "Enter file name: ";
			cin >> filename;
			calend.open(filename);

			cout << endl;
		}
		else {
			for (int i = 1; i < argc; ++i) {
				if ((!strcmp(argv[i], "/M")) && (i + 1 < argc)) {
					user_month = atoi(argv[i + 1]);
				}
				if ((!strcmp(argv[i], "/Y")) && (i + 1 < argc)) {
					int s;
					s = (argv[i + 1][0] - 48) * 1000 + (argv[i + 1][1] - 48) * 100 + (argv[i + 1][2] - 48) * 10 + (argv[i + 1][3] - 48);
					user_year = s;
				}
				if ((!strcmp(argv[i], "/F")) && (i + 1 < argc)) {
					calend.open(argv[i + 1]);
					a = argv[i + 1];
					
				}
				if (!strcmp(argv[i], "/FCON")) {
					file = false;
				}
				if (!strcmp(argv[i], "/?")) {
					cout << "Алексеев Дмитрий\n   ИВТ-43-22\nВывод календаря на 1 год с введеннного месяца и года\n\n";
				}
			}
		}
		copy = user_month;

		// номер дня недели
		int NumOfDay;

		const char list_month[12][20]{ "January", "February", "March", "April", "May", "June",
			"July", "August", "September", "October", "November", "December" };

		char list_days[7][3]{ "Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс" };

		const int week = 6, days = 7;
		int calendar[days][week]{};

		map <string, int> daysOfMonth{
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
			for (int i = 1; i < daysOfMonth[list_month[user_month - 1]] + 1; i++) {

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
			cout << "Odd/Even" << endl;
			calend << "Odd/Even" << endl;
			cout << setw(20) << "        1       2       1       2" << endl;
			calend << setw(20) << "        1       2       1       2" << endl;

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
						}
						else {
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

				if (copy != 1) {
					cout << "\t\t" << user_year << endl;
					cout << "\t" << "Happy New Year!!!" << endl << endl;
					calend << "\t\t" << user_year << endl;
					calend << "\t" << "Happy New Year!!!" << endl << endl;
				}
				else {
					cout << endl;
					calend << endl;
				}
			}
			user_month++;
		}
		
		calend.close();
		char rep;
		cout << endl << "If you want to terminate the program, enter 'Y' (Y/N) :\n";
		cin >> rep;
		if (rep == 'Y')
			exit(1);
	
	}while (true);
	
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
	if (year % 4 != 0 || year % 1000 != 0)
		return false;
	else
		return true;
}
